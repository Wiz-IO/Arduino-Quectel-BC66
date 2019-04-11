/*
  BC66 - psm
    Created on: 01.01.2019
    Author: Georgi Angelov

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA   
 */

#include "PSM.h"

#define DEBUG_PSM DBG

static void uint_to_binary_str(uint32_t num, char *str, int str_size, int bit_cnt)
{
    //https://github.com/ARMmbed/mbed-os/blob/be4bb9f610917be9bc87026e61608e29a29496d4/features/cellular/framework/common/CellularUtil.cpp
    if (!str || str_size < bit_cnt)
        return;
    int tmp, pos = 0;
    for (int i = 31; i >= 0; i--)
    {
        tmp = num >> i;
        if (i < bit_cnt)
        {
            if (tmp & 1)
                str[pos] = 1 + '0';
            else
                str[pos] = 0 + '0';
            pos++;
        }
    }
}

static uint32_t tau_seconds[8] = {
    10 * 600,
    3600,  // 1 hour
    36000, // 10 hours
    2,
    30,
    60,
    320 * 3600,
    (uint32_t)-1,
};
static inline uint32_t tauToSeconds(uint8_t tau)
{
    return (tau & 31) * tau_seconds[tau >> 5];
}

static uint32_t act_seconds[8] = {2, 60, 6 * 60, 60, 60, 60, 60, 60};
static inline uint32_t actToSeconds(uint8_t act)
{
    return (act & 31) * act_seconds[act >> 5];
}

static int GET_CPSMS(char *line, u32 len, void *user)
{
    char *h = Ql_RIL_FindLine(line, len, (char *)"OK");
    if (h)
        return RIL_ATRSP_SUCCESS;
    h = Ql_RIL_FindLine(line, len, (char *)"ERROR");
    if (h)
        return RIL_ATRSP_FAILED;
    h = Ql_RIL_FindString(line, len, (char *)"+CPSMS:");
    if (h) // +CPSMS: 1,,,"00100011","00100010"
    {
        if (NULL == user)
            return RIL_ATRSP_FAILED;
        cpsms_t *p = (cpsms_t *)user;
        p->periodic = 0;
        p->active = 0;
        p->mode = 0;
        //DEBUG_DEV("[PSM] Response: %s", line);
        if (at_tok_start(&h) < 0)
            return RIL_ATRSP_FAILED;
        if (at_tok_nextint(&h, &p->mode) < 0)
            return RIL_ATRSP_FAILED;
        skip_next_comma(&h);
        skip_next_comma(&h);
        if (at_tok_nextbinint(&h, &p->periodic) < 0)
            return RIL_ATRSP_FAILED;
        if (at_tok_nextbinint(&h, &p->active) < 0)
            return RIL_ATRSP_FAILED;
    }
    return RIL_ATRSP_CONTINUE; //continue wait
}

typedef void (*reset_vector_jump)(void);              //exactly as you've done
#define RESET_VECTOR_ADDRESS ((uint32_t *)0x00000004) // a pointer to uint32_t

/*static*/ void PSMClass::onLimitCB(TimerHandle_t xTimer)
{
    DEBUG_PSM("\n[PSM] RESET");
    for (int i = 0; i < 20000; i++)
        asm volatile("nop");
    //Ql_Reset(0);
    ((reset_vector_jump)*RESET_VECTOR_ADDRESS)();
}

///Default 5 minutes
bool PSMClass::limit(uint32_t seconds)
{
    if (seconds)
    {
        seconds *= 100; // one tick = 10 ms
        TimerHandle_t H = xTimerCreate("arduino_max_time", seconds, 0, 0, onLimitCB);
        if (H)
            return xTimerStart(H, 0);
    }
    return false; // error
}

// default callback
/*static*/ void PSMClass::onSleepCB(void *THIS, uint32_t mode)
{
    if (THIS && mode >= 4)
    {
        PSMClass *p = (PSMClass *)THIS;
        if (p->m_wakeup_interval)
        {
            
            api_rtc_start(p->m_wakeup_interval, 0); // one shot
            DEBUG_PSM("\n[PSM] Wakeup timer %lu ms\n", p->m_wakeup_interval);
        }
    }
}

///Register onSleep event - RTC wakeup timer ID = 0x200
bool PSMClass::wakeup(uint32_t seconds, sleep_callback_t userCB)
{
    m_wakeup_interval = seconds * 1000;
    if (m_wakeup_interval)
    {
        api_rtc_register(NULL, NULL);
        if (userCB)
            hal_sleep_manager_register_suspend_callback(userCB, this, 0xC);
        else
        {
            hal_sleep_manager_register_suspend_callback(onSleepCB, this, 0xC);
        }
        return true;
    }
    return false; // error
}

///Register EINT wakeup
bool PSMClass::pin(Callback_Psm_Eint_Func onEintPsm, void *param)
{
    int res = -1;
    if (onEintPsm)
    {
        res = Ql_Psm_Eint_Register(onEintPsm, param);
        DEBUG_PSM("[PSM] Ql_Psm_Eint_Register = %d\n", res);
    }
    return res == QL_RET_OK;
}

int PSMClass::getCellPsmPeriodicTime()
{
    int t = api_get_psm_periodic();
    if (t)
        return tauToSeconds(t);
    return 0;
}
int PSMClass::getCellPsmActiveTime() {
      int t = api_get_psm_active();
    if (t)
        return actToSeconds(t);
    return 0;  
}

///Get user PSM, return mode or error -1
bool PSMClass::get(int *period, int *active)
{
    bool res = false;
    if (period && active)
    {
        cpsms_t c;
        res = Ql_RIL_SendATCmd((char *)"AT+CPSMS?\n", 10, GET_CPSMS, &c, 1000) == RIL_AT_SUCCESS;
        if (res)
        {
            *period = tauToSeconds(c.periodic);
            *active = actToSeconds(c.active);
            res = c.mode;
        }
    }
    return res;
}

///Set user PSM, Depends on the network, true = ok
bool PSMClass::set(int periodic_time, int active_time, int mode)
{
    //https://github.com/ARMmbed/mbed-os/blob/e6c2a1de400046eebbf322f2a15a1a0c40b15542/features/cellular/framework/AT/AT_CellularDevice.cpp
    char cmd[64];
    if (periodic_time == 0 && active_time == 0)
        mode = 0;
    if (mode == 0 || mode == 2)
    {
        snprintf(cmd, sizeof(cmd), "AT+CPSMS=%d\n", mode);
        return Ql_RIL_SendATCmd(cmd, Ql_strlen(cmd), NULL, NULL, 1000) == RIL_AT_SUCCESS;
    }
    else
    {
        mode = 1;
        char pt[8 + 1]; // timer value encoded as 3GPP IE
        const int ie_value_max = 0x1f;
        static const int PSMTimerBits = 5;
        uint32_t periodic_timer = 0;
        if (periodic_time <= 2 * ie_value_max)
        { // multiples of 2 seconds
            periodic_timer = periodic_time / 2;
            strcpy(pt, "01100000");
        }
        else
        {
            if (periodic_time <= 30 * ie_value_max)
            { // multiples of 30 seconds
                periodic_timer = periodic_time / 30;
                strcpy(pt, "10000000");
            }
            else
            {
                if (periodic_time <= 60 * ie_value_max)
                { // multiples of 1 minute
                    periodic_timer = periodic_time / 60;
                    strcpy(pt, "10100000");
                }
                else
                {
                    if (periodic_time <= 10 * 60 * ie_value_max)
                    { // multiples of 10 minutes
                        periodic_timer = periodic_time / (10 * 60);
                        strcpy(pt, "00000000");
                    }
                    else
                    {
                        if (periodic_time <= 60 * 60 * ie_value_max)
                        { // multiples of 1 hour
                            periodic_timer = periodic_time / (60 * 60);
                            strcpy(pt, "00100000");
                        }
                        else
                        {
                            if (periodic_time <= 10 * 60 * 60 * ie_value_max)
                            { // multiples of 10 hours
                                periodic_timer = periodic_time / (10 * 60 * 60);
                                strcpy(pt, "01000000");
                            }
                            else
                            { // multiples of 320 hours
                                int t = periodic_time / (320 * 60 * 60);
                                if (t > ie_value_max)
                                    t = ie_value_max;
                                periodic_timer = t;
                                strcpy(pt, "11000000");
                            }
                        }
                    }
                }
            }
        }
        uint_to_binary_str(periodic_timer, &pt[3], sizeof(pt) - 3, PSMTimerBits);
        pt[8] = '\0';
        char at[8 + 1];
        uint32_t active_timer; // timer value encoded as 3GPP IE
        if (active_time <= 2 * ie_value_max)
        { // multiples of 2 seconds
            active_timer = active_time / 2;
            strcpy(at, "00000000");
        }
        else
        {
            if (active_time <= 60 * ie_value_max)
            { // multiples of 1 minute
                active_timer = (1 << 5) | (active_time / 60);
                strcpy(at, "00100000");
            }
            else
            { // multiples of decihours
                int t = active_time / (6 * 60);
                if (t > ie_value_max)
                    t = ie_value_max;
                active_timer = t;
                strcpy(at, "01000000");
            }
        }
        uint_to_binary_str(active_timer, &at[3], sizeof(at) - 3, PSMTimerBits);
        pt[8] = '\0';
        snprintf(cmd, sizeof(cmd), "AT+CPSMS=1,,,\"%s\",\"%s\"\n", pt, at);
        DEBUG_PSM("[PSM] AtCommand\n%s", cmd);
        return Ql_RIL_SendATCmd(cmd, strlen(cmd), NULL, NULL, 1000) == RIL_AT_SUCCESS;
    }
}

PSMClass Psm;