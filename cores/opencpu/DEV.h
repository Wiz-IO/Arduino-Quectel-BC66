/*
  BC66 - device
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

#ifndef __DEV_H__
#define __DEV_H__

#include <interface.h>
#include "WString.h"
#include "IPAddress.h"

#define DEBUG_DEV DBG

int getHostByName(const char *host, IPAddress &aResult);

typedef void (*vCallback)(void);
typedef void (*uCallback)(u32, u32);
typedef void (*mCallback)(ST_MSG *msg);

#define DEFAULT_AT_TIMEOUT 1000

class DeviceClass
{

  public:
    DeviceClass();

    mCallback onMessage;
    void m_Message(ST_MSG *m)
    {
        if (onMessage)
            onMessage(m);
    }

    uCallback onUrc;
    void m_Urc(u32 urc, u32 data)
    {
        if (onUrc)
            onUrc(urc, data);
    }

    const char *getVersion() { return api_get_version(); }
    void getVersion(String &s) {s = api_get_version();}
    inline bool getUid(uint8_t *buffer, uint32_t size) { return api_get_uid(buffer, size); }
    void getUid(String &s);
    bool getImsi(char *buffer, uint32_t size);
    void getImsi(String &s);
    bool getIccid(char *buffer, uint32_t size);
    void getIccid(String &s);
    void getMccMnc(char *imsi, uint32_t size);
    void getMccMnc(String &s);
    void getImei(char *imei, uint32_t size);
    void getImei(String &s);

    inline int getSimStatus() { return api_get_sim_status(); }
    inline bool isSimReady() { return api_get_sim_status() == SIM_READY; }
    bool enterPin(const char *pin);
    void waitSimReady(const char *pin = NULL);

    inline int getCreg() { return api_get_creg(); }
    void waitCreg();
    inline int getCereg() { return api_get_cereg(); }
    void waitCereg();

    inline int getReceiveLevel() { return api_get_receive_level(); }
    inline int getQuality() { return api_get_quality(); }
    inline int getAccess() { return api_get_access(); }
    inline uint16_t getTac() { return api_get_cell_tac(); }
    inline uint32_t getCid() { return api_get_cell_cid(); }
    void getLocalIP(IPAddress &IP, unsigned int index = 1);

    //"19/03/14,07:20:05+02",,"A1 BG",0,"A1 BG",0,"+02"
    void getMlts(char *buf, unsigned int size) { api_get_mlts_string(buf, size); }

    inline void reset() { Ql_Reset(0); }
    void powerOff()
    {
        int irq = api_SaveAndSetIRQMask();
        hal_rtc_enter_forced_shut_down_mode(irq, 1);
    }
    inline int powerReason() { return Ql_GetPowerOnReason(); }

    inline void Sleep() { Ql_SleepEnable(); }
    inline void noSleep() { Ql_SleepDisable(); }

    bool getDefaultApnType(char *type);
    bool saveDefaultApn(const char *type, const char *apn, const char *user, const char *pass);
    bool setBand(int band);

    bool send(const char *cmd, u32 timeout = DEFAULT_AT_TIMEOUT, Callback_ATResponse callback = NULL, void *user = NULL);
    bool send(String cmd, u32 timeout = DEFAULT_AT_TIMEOUT, Callback_ATResponse callback = NULL, void *user = NULL);

    time_t now();
};

extern DeviceClass Dev;

#endif //__DEV_H__