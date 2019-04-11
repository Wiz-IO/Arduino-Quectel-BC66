/*
  BC66 - arduino_main
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

#include <interface.h>
#include <DEV.h>

extern void initVariant();
extern void setup();
extern void loop();

static struct
{
    uint32_t wait;
    TaskHandle_t taskHandle;
    ST_MSG msg;
} arduino = {10 /* default task wait */, 0, {0, 0, 0, 0}};

void arduinoSetWait(u32 wait)
{
    arduino.wait = wait == 0 ? 1 : wait;
}

static inline void arduinoDispatchMessages(void)
{
    switch (arduino.msg.message)
    {
    case MSG_ID_URC_INDICATION:
        Dev.m_Urc(arduino.msg.param1, arduino.msg.param2);
        break;
    default:
        Dev.m_Message(&arduino.msg);
        break;
    }
}

extern "C" int api_get_message(ST_MSG *msg);
void arduinoProcessMessages(unsigned int wait)
{
    u32 id = Ql_OS_GetActiveTaskId();
    if (ARDUINO_TASK_ID == id)
    {
#if 0        
        Ql_OS_GetMessage(&arduino.msg);                    // there is always more than zero
        Ql_OS_SendMessage(id, MSG_PROCESS_MESSAGES, 0, 0); // send one message
#else        
        if (0 == api_get_message(&arduino.msg)) // Plan B, get without wait
#endif
        arduinoDispatchMessages();
    }
    Ql_Sleep(wait);
}

void delayEx(unsigned int ms)
{
#define BLOCK_TIME 100
    unsigned int count = ms / BLOCK_TIME;
    while (count--)
        arduinoProcessMessages(BLOCK_TIME);  // step
    arduinoProcessMessages(ms % BLOCK_TIME); // remain
}

/// Arduino Task
extern "C" void proc_arduino(int taskId)
{
    arduino.taskHandle = xTaskGetCurrentTaskHandle();
    vTaskSuspend(arduino.taskHandle); // wait ril ready
    initVariant();
#if 0     
    Ql_OS_SendMessage(taskId, MSG_PROCESS_MESSAGES, 0, 0); // dont touch
#endif    
    arduinoProcessMessages(arduino.wait);
    setup();
    while (true)
    {
        arduinoProcessMessages(arduino.wait);
        loop();
    }
}

/// Main Task
extern "C" void proc_main_task(int taskId)
{
    if (api_check_api())
    {
        Ql_Debug_Trace("[M] ERROR Firmware not support\n");
        abort();
    }
    __libc_init_array();
    entry_main(taskId); // if function exist - OpenCPU style
    ST_MSG m;
    while (true)
    {
        Ql_OS_GetMessage(&m);
        switch (m.message)
        {
        case MSG_ID_RIL_READY:
            Ql_RIL_Initialize();
            vTaskResume(arduino.taskHandle); // enable arduino
            break;
        case MSG_ID_URC_INDICATION:
            if (m.message > URC_CFUN_STATE_IND)                                    // ignore first urc-s
                Ql_OS_SendMessage(ARDUINO_TASK_ID, m.message, m.param1, m.param2); // re-send to arduino task
            break;
        default:
            Ql_OS_SendMessage(ARDUINO_TASK_ID, m.message, m.param1, m.param2); // re-send to arduino task
            break;
        }
    }
}

