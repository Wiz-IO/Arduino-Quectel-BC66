/*
  BC66 - rtc
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

#include <Arduino.h>
#include "RTC.h"

#define DEBUG_RTC DBG

RTCClass RTC;

unsigned long long rtc_seconds(void)
{
    unsigned long long seconds = 0;
    ST_Time T;
    if (Ql_GetLocalTime(&T))
        seconds = Ql_Mktime(&T);
    return seconds;
}

unsigned long long RTCClass::get()
{
    unsigned long long seconds = 0;
    ST_Time T;
    if (Ql_GetLocalTime(&T))
    {
        m_year = T.year;
        m_month = T.month;
        m_day = T.day;
        m_hour = T.hour;
        m_minute = T.minute;
        m_second = T.second;
        m_timezone = T.timezone;
        seconds = Ql_Mktime(&T);
    }
    return seconds;
}

int RTCClass::timezone()
{
    return m_timezone;
}

int RTCClass::year()
{
    return m_year;
}

int RTCClass::month()
{
    return m_month;
}

int RTCClass::day()
{
    return m_day;
}

int RTCClass::hour()
{
    return m_hour;
}

int RTCClass::minute()
{
    return m_minute;
}

int RTCClass::second()
{
    return m_second;
}

///result: Wed Feb 13 08:27:10 2019
extern "C" char *asctime(const struct tm *timeptr);
char *RTCClass::m_asctime(char *buffer, u32 size)
{
    time_t rawtime = rtc_seconds();
    struct tm *t = localtime(&rawtime);
    char *p = asctime(t);
    if (p && size)
    {
        Ql_memset(buffer, 0, size);
        Ql_strncpy(buffer, p, size);
        return buffer;
    }
    return NULL;
}

char *RTCClass::ascTime(char *buffer, u32 size)
{
    return m_asctime(buffer, size);
}

size_t RTCClass::printTo(Print &p) const
{
    char b[32];
    const char *c = (const char *)m_asctime(b, 32);
    return p.print(c);
}
