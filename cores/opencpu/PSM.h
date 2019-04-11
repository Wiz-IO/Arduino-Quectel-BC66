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

#ifndef __PSM_H__
#define __PSM_H__

#include <interface.h>

#define DEBUG_PSM DBG

typedef void (*sleep_callback_t)(void *, uint32_t);

typedef struct
{
  int periodic;
  int active;
  int mode;
} cpsms_t;

class PSMClass
{
private:
  uint32_t m_wakeup_interval;
  static void onLimitCB(TimerHandle_t xTimer);
  static void onSleepCB(void *psm, uint32_t id);

public:
  PSMClass()
  {
    m_wakeup_interval = 0;
  }

  ///Enable/Disable auto deep sleep mode
  inline void Sleep() { Ql_SleepEnable(); }
  inline void noSleep() { Ql_SleepDisable(); }

  ///Register onPin wakeup
  bool pin(Callback_Psm_Eint_Func onPsm, void *param);

  ///Get timers from cell
  int getCellPsmPeriodicTime();
  int getCellPsmActiveTime();

  ///get/set user times, can be ignored form cell
  bool get(int *period, int *active);
  bool set(int periode, int active, int mode = 1);

  ///Register onSleep event - RTC wakeup timer
  bool wakeup(uint32_t interval, sleep_callback_t cb = NULL);

  ///Emergency Reset, default 5 minutes
  bool limit(uint32_t seconds = 300);
};

extern PSMClass Psm;
#endif