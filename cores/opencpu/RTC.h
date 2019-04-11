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

#ifndef __RTC_H__
#define __RTC_H__

#include <Arduino.h>
#include <time.h>

#define RTC_TIMER_ID 0x202

class RTCClass : public Printable
{
public:
  RTCClass()
  {
    m_id = 0;
    timer_started = 0;
  };
  int timezone();
  int year();
  int month();
  int day();
  int hour();
  int minute();
  int second();
  unsigned long long get();
  void set(int year, int month, int day, int hour, int minute, int second){};

  char *ascTime(char *buffer, u32 size);
  virtual size_t printTo(Print &p) const;

  bool timer_started;
  bool timer_begin(Callback_Rtc_Func callback, void *param = NULL)
  {
    if (callback)
      m_id = (Ql_Rtc_RegisterFast(RTC_TIMER_ID, callback, param) == 0) ? RTC_TIMER_ID : 0;
    else
      m_id = 0;
    return m_id > 0;
  }

  bool timer_stop()
  {
    bool res = false;
    if (m_id)
    {
      res = Ql_Rtc_Stop(m_id) == QL_RET_OK;
      timer_started = res ? 0 : 1;
    }
    return res;
  }

  bool timer_start(uint32_t interval, bool autoRepeat = false)
  {
    bool res = false;
    if (m_id)
    {
      if (timer_started)
        timer_stop();
      res = Ql_Rtc_Start(m_id, interval, autoRepeat) == QL_RET_OK;
      timer_started = res;
    }
    return res;
  }

  operator bool() { return timer_started; }

private:
  int m_year;
  int m_month;
  int m_day;
  int m_hour;
  int m_minute;
  int m_second;
  int m_timezone;
  static char *m_asctime(char *buffer, u32 size);
  uint32_t m_id;
};

extern RTCClass RTC;

#endif