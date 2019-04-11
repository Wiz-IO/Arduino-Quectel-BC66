#include <Arduino.h>
#include "GPTimer.h"

#define DEBUG_TMR 
//DBG

GPTimer::GPTimer(TimerID id)
{
    m_id = id;
    if (id < TIMER_FAST || id > TIMER_END)
        m_id = 0;
}

int GPTimer::start(uint32_t interval, bool mode, Callback_Timer_OnTimer callback, void *user)
{
    int res = -1;
    if (callback && m_id)
    {
        if (TIMER_FAST == m_id)
        {
            res = Ql_Timer_RegisterFast(m_id, callback, user);
        }
        else
        {
            res = Ql_Timer_Register(m_id, callback, user); 
        }
        DEBUG_TMR("Ql_Timer_Register( %X, %p ) = %d\n", (int)m_id, callback, res);
        if (QL_RET_OK == res)
        {
            res = Ql_Timer_Start(m_id, interval, mode == TIMER_REPEAT_MODE);
            DEBUG_TMR("Ql_Timer_Start( %X ) = %d\n", (int)m_id, res);
        }
    }
    return res == QL_RET_OK;
}

int GPTimer::stop()
{
    int res = -1;
    if (m_id)
        res = Ql_Timer_Stop(m_id);
    return res == QL_RET_OK;
}
