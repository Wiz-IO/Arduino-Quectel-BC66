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

#include "DEV.h"

int getHostByName(const char *host, IPAddress &aResult)
{
    struct sockaddr_in addr;
    if (resolveAddress(host, &addr) < 0)
        aResult = (uint32_t)0;
    else
        aResult = addr.sin_addr.s_addr;
    return (uint32_t)aResult;
}

DeviceClass::DeviceClass()
{
    onMessage = NULL;
    onUrc = NULL;
}

///RTC to time_t
time_t DeviceClass::now()
{
    ST_Time st;
    if (NULL == Ql_GetLocalTime(&st))
        return 0;
    return Ql_Mktime(&st);
}

bool DeviceClass::enterPin(const char *pin)
{
    if (pin)
    {
        char CMD_CPIN[32];
        Ql_sprintf(CMD_CPIN, "AP+CPIN =\"%s\"\n", pin);
        return Ql_RIL_SendATCmd(CMD_CPIN, strlen(CMD_CPIN), NULL, NULL, DEFAULT_AT_TIMEOUT) == RIL_AT_SUCCESS;
    }
    return false;
}

void DeviceClass::waitSimReady(const char *pin)
{
    if (pin)
    {
        if (false == enterPin(pin))
        {
            while (true)
                delayEx(1000); // no exit
        }
    }
    while (getSimStatus() != SIM_READY)
        delayEx(1000);
}

bool DeviceClass::setBand(int band)
{
    char CMD_BAND[32];
    Ql_sprintf(CMD_BAND, "AT+QBAND=1,%d\n", band);
    return Ql_RIL_SendATCmd(CMD_BAND, strlen(CMD_BAND), NULL, NULL, DEFAULT_AT_TIMEOUT) == RIL_AT_SUCCESS;
}

void DeviceClass::waitCreg()
{
    while (1)
    {
        int res = getCreg();
        if (res == 5 || res == 1)
            break;
        delayEx(100);
    }
}

void DeviceClass::waitCereg()
{
    while (1)
    {
        int res = getCereg();
        if (res == 5 || res == 1)
            break;
        delayEx(100);
    }
}

void DeviceClass::getUid(String &str)
{
    char h[3];
    uint8_t b[16];
    memset(b, 0, 16);
    if (getUid(b, 32))
    {
        str.reserve(32);
        for (int i = 0; i < 16; i++)
        {
            sprintf(h, "%02X", b[i] & 0xFF);
            str.concat(h);
        }
    }
    else
        str = "";
}

bool DeviceClass::getImsi(char *buffer, uint32_t size)
{
    if (buffer && size > 8)
    {
        char s[9];
        memset(s, 0, 9);
        memset(buffer, 0, size);
        api_get_imsi(s);
        if (s[0] < 9)
        {
            memcpy(buffer, &s[1], s[0]);
            return 1;
        }
    }
    return 0;
}

void DeviceClass::getImsi(String &str)
{
    char s[9];
    char h[3];
    char b;
    if (getImsi(s, 9))
    {
        str.reserve(16);
        for (int i = 0; i < 8; i++)
        {
            b = s[i] >> 4 | s[i] << 4;
            sprintf(h, "%02X", (int)b & 0xFF);
            str.concat(h);
        }
    }
    else
        str = "";
}

bool DeviceClass::getIccid(char *buffer, uint32_t size)
{
    if (buffer && size > 9)
    {
        char s[10];
        memset(s, 0, 10);
        memset(buffer, 0, size);
        api_get_iccid(s);
        memcpy(buffer, s, 10);
        return 1;
    }
    return 0;
}

void DeviceClass::getIccid(String &str)
{
    char s[10];
    char h[3];
    char b;
    if (getIccid(s, 10))
    {
        str.reserve(20);
        for (int i = 0; i < 10; i++)
        {
            if (i < 9)
                b = s[i] >> 4 | s[i] << 4;
            else
                b = s[i] << 4;
            sprintf(h, "%02X", (int)b & 0xFF);
            str.concat(h);
        }
    }
    else
        str = "";
}

///min len 16
void DeviceClass::getMccMnc(char *buffer, uint32_t size)
{
    if (buffer && size > 15)
    {
        memset(buffer, 0, size);
        int i = api_get_mcc_mnc();
        snprintf(buffer, size, "%03X%02X", i & 0xFFFF, i >> 16);
    }
}

void DeviceClass::getMccMnc(String &s)
{
    char buffer[16];
    memset(buffer, 0, 16);
    getMccMnc(buffer, 16);
    s = buffer;
}

///size must be 16
void DeviceClass::getImei(char *imei, uint32_t size)
{
    if (imei && size)
        api_get_imei(imei, size);
}

void DeviceClass::getImei(String &s)
{
    char buffer[16]; // must be 16
    memset(buffer, 0, 16);
    getImei(buffer, 16);
    s = buffer;
}

void DeviceClass::getLocalIP(IPAddress &IP, unsigned int index)
{
    IP = (uint32_t)api_get_local_ip(index);
}

static int GET_QCGDEFCONT(char *line, u32 len, void *user)
{
    int res = isAtEnd(line, len);
    if (RIL_ATRSP_CONTINUE != res)
        return res;
    char *h = Ql_RIL_FindString(line, len, (char *)"+QCGDEFCONT:");
    if (h && user)
    {
        char *p1 = NULL;
        char *p2 = NULL;
        p1 = Ql_strstr(h, ":");
        p2 = Ql_strstr(p1 + 1, "\r\n");
        if (p1 && p2)
            Ql_memcpy((char *)user, p1 + 2, p2 - p1 - 2);
    }
    return RIL_ATRSP_CONTINUE;
}

///return IP, IPV6, IPV4V6, Non-IP
bool DeviceClass::getDefaultApnType(char *type)
{
    if (type)
    {
        char cmd[16];
        Ql_sprintf(cmd, "AT+QCGDEFCONT?\n");
        return Ql_RIL_SendATCmd(cmd, strlen(cmd), GET_QCGDEFCONT, type, DEFAULT_AT_TIMEOUT) == RIL_AT_SUCCESS;
    }
    return false;
}

bool DeviceClass::saveDefaultApn(const char *type, const char *apn, const char *user, const char *pass)
{ //AT+QCGDEFCONT="IP","apn","user","pass"
    if (NULL == type || NULL == apn)
        return false;
    char cmd[256];
    Ql_sprintf(cmd, "AT+QCGDEFCONT=\"%s\",\"%s\"", type, apn);
    if (user)
    {
        Ql_strcat(cmd, (char *)",\"");
        Ql_strcat(cmd, (char *)user);
        Ql_strcat(cmd, (char *)"\"");
        if (pass)
        {
            Ql_strcat(cmd, (char *)",\"");
            Ql_strcat(cmd, (char *)pass);
            Ql_strcat(cmd, (char *)"\"");
        }
    }
    Ql_strcat(cmd, (char *)"\n");
    return Ql_RIL_SendATCmd(cmd, strlen(cmd), NULL, NULL, DEFAULT_AT_TIMEOUT) == RIL_AT_SUCCESS;
}

bool DeviceClass::send(const char *cmd, u32 timeout, Callback_ATResponse callback, void *user)
{
    return Ql_RIL_SendATCmd((char *)cmd, Ql_strlen(cmd), callback, user, timeout) == RIL_AT_SUCCESS;
}

bool DeviceClass::send(String cmd, u32 timeout, Callback_ATResponse callback, void *user)
{
    return send(cmd.c_str(), timeout, callback, user);
}

DeviceClass Dev;