/*****************************************************************************
*  Copyright Statement:
*  --------------------
*  This software is protected by Copyright and the information contained
*  herein is confidential. The software may not be copied and the information
*  contained herein may not be used or disclosed except with the written
*  permission of Quectel Co., Ltd. 2013
*
*****************************************************************************/
/*****************************************************************************
 *
 * Filename:
 * ---------
 *   ql_common.h 
 *
 * Project:
 * --------
 *   OpenCPU
 *
 * Description:
 * ------------
 *   The module defines the information.
 *
 * Author:
 * -------
 * -------
 *
 *============================================================================
 *             HISTORY
 *----------------------------------------------------------------------------
 * 
 ****************************************************************************/


#ifndef __QL_COMMON_H__
#define __QL_COMMON_H__
#include "custom_feature_def.h"
#include "ql_type.h"
#include "ql_gpio.h"
#include "ql_trace.h"

#define  SYS_CONFIG_PWRKEY_DATA_SIZE    (2)
#define  SYS_CONFIG_WATCHDOG_DATA_SIZE  (8)
#define  SYS_CONFIG_APPENABLE_DATA_SIZE (4)
#define  SYS_CONFIG_DEBUGMODE_DATA_SIZE (4)
#define  SYS_CONFIG_DEBUGSET_DATA_SIZE  (8)

typedef enum{
    SYS_CONFIG_PWRKEY_DATA_ID,      // For PWRKEY pin setting
    SYS_CONFIG_WATCHDOG_DATA_ID,    // For external watchdog setting
    SYS_CONFIG_APP_ENABLE_ID,       // For application enable setting
    SYS_CONFIG_DEBUG_MODE_ID,       // For serial mode setting  
    SYS_CONFIG_DEBUG_SET_ID,        //For  genie log port setting
    SYS_CONFIG_END = 0x7FFFFFFF
}Enum_SysCfgId;

typedef enum{
    APP_DISABLE = 0,
    APP_ENABLE  = 1
}Enum_AppEnable;

typedef struct{
    void (*proc_taskEntry)(s32 TaskId);  // Task Entrance Procedure
    s32  TaskId;
    u32  TaskStackSize;     // The stack size of subtask. Range from 1K to 10K. 
    u32  rev1;              // Reserved parameter, must be DEFAULT_VALUE1.
    u32  rev2;              // Reserved parameter, must be DEFAULT_VALUE2.
}ST_TaskConfig;

typedef struct{
    bool autoPowerOn;       // If module automatically power on when pressing POWER_KEY
    bool autoPowerOff;      // If module automatically power off when pressing POWER_KEY
}ST_PowerKeyCfg;

typedef struct{
    Enum_PinName pinWtd1;   // Specify a pin which connects to the external watchdog
    Enum_PinName pinWtd2;   // Specify another pin for watchdog if needed
}ST_ExtWatchdogCfg;

typedef struct{
    s32 appEnable;          // Specify the working mode of serial debug port (UART2)
}ST_AppEnable;

typedef struct{
    Enum_DebugMode dbgPortMode;
}ST_DebugPortCfg;

typedef struct{
    Enum_PortName dbgPort_gki;
    Enum_PortName dbgPort_hsl;
}ST_DebugPortSet;
/****************************************************************************
 * Customized configuration structure
 ***************************************************************************/
typedef struct{
    Enum_SysCfgId itemId;   // Data item ID
    u32           size;     // Size of one record
    void*         pValue;   // Pointer to config data
}ST_SystemConfig;

#define QL_TRACE_LOG(PORT,BUF,BUF_LEN,...) \
    Ql_memset((char *)(BUF), 0, BUF_LEN); \
    Ql_sprintf((char *)(BUF),__VA_ARGS__); \
    if (UART_PORT1 == (PORT)) \
    {\
        Ql_Debug_Trace(BUF);\
    } else {\
        Ql_UART_Write((Enum_SerialPort)(PORT), (u8*)(BUF), Ql_strlen((const char *)(BUF)));\
    }

#endif  // __QL_COMMON_H__


#if (defined(TASK_FUNC_DECLARATION) && defined(TASK_ID_DEF))
#error [ Conflict I ]
#endif
#if (defined(TASK_FUNC_DECLARATION) && defined(TASK_DEFINITION))
#error [ Conflict II ]
#endif
#if (defined(TASK_DEFINITION) && defined(TASK_ID_DEF))
#error [ Conflict III ]
#endif


#undef TASK_DEFINITION_BEGIN
#undef TASK_ITEM
#undef TASK_DEFINITION_END

#ifdef GPIO_DEFINITION
#define GPIO_DEFINITION_BEGIN  const ST_GPIOConfig GpioConfigTbl[] = {
#define GPIO_ITEM(PINNAME, PINDIRECTION, PINLEVEL, PINPULLSEL) {PINNAME, PINDIRECTION, PINLEVEL, PINPULLSEL},
#define GPIO_DEFINITION_END  {PINNAME_END, 0, 0, 0}  }; 
#endif


#if defined( TASK_DEFINITION)
#define TASK_DEFINITION_BEGIN  const ST_TaskConfig TaskConfig[] = {
#define TASK_ITEM(EntryFunc,TaskId,TaskStackSize,P1,P2) {EntryFunc, TaskId, TaskStackSize, P1, P2},
#define TASK_DEFINITION_END    {NULL, 0, 0, 0, 0}};
#elif defined(TASK_ID_DEF)
#define TASK_DEFINITION_BEGIN typedef enum{
#define TASK_ITEM(EntryFunc,TaskId,TaskStackSize,P1,P2) TaskId,
#define TASK_DEFINITION_END  TaskId_End } Enum_TaskId;
#elif defined(TASK_FUNC_DECLARATION)
#define TASK_DEFINITION_BEGIN
#define TASK_ITEM(EntryFunc,TaskId,TaskStackSize,P1,P2) extern void EntryFunc(s32);
#define TASK_DEFINITION_END
#else
#undef TASK_DEFINITION_BEGIN
#undef TASK_ITEM
#undef TASK_DEFINITION_END
#endif
