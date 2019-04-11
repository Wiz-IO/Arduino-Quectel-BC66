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
 *   custom_sys_cfg.c
 *
 * Project:
 * --------
 *   OpenCPU
 *
 * Description:
 * ------------
 *   The file intends for the system definitions of application. 
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
#include "ril.h"
#include "ql_common.h"

/*========================================================================
| 
| Customized configurations.
|------------------
| Define the working modes of power key pin and 
| specify the GPIO for watchdog (MTK2625 supports internal hardware watchdog).
\=========================================================================*/

/************************************************************************/
/* Configure the enable of application.                                 */
/* The possible values are 'APP_DISABLE' and 'APP_ENABLE', and the      */
/* default value is 'APP_ENABLE'.                                       */
/*   APP_ENABLE: the application will work after downloading into module*/
/*   APP_DISABLE:the application will not work after downloading.In this*/
/*               case, the module still work as a STANDARD module.      */
/************************************************************************/
static const ST_AppEnable appEnableCfg = {
    APP_ENABLE
};

// powerkey and watchdog function is under evaluation
static const ST_PowerKeyCfg pwrkeyCfg = {
    TRUE,  // working mode for power-on on PWRKEY pin
    /*
    Module automatically powers on when feeding a low level to POWER_KEY pin.

    When set to FALSE, the callback that Ql_PwrKey_Register registers will be triggered. Application must
    call Ql_LockPower () to lock power supply, or module will lose power when the level of PWRKEY pin goes high.
    */

    TRUE,  // working mode for power-off on PWRKEY pin
    /*
    Module automatically powers off when feeding a low level to POWER_KEY pin.

    When set to FALSE, the callback that Ql_PwrKey_Register registers will be triggered. 
    Application may do post processing before switches off the module.
    */
};

/************************************************************************/
/* Define the GPIO pin for external watchdog.                           */
/* NOTES:                                                               */
/*     Customer may specify two GPIOs if needed.                        */
/************************************************************************/
static const ST_ExtWatchdogCfg wtdCfg = {
    PINNAME_GPIO1,  // Specify a pin which connects to the external watchdog
    PINNAME_END,   // Specify another pin for watchdog if needed
};
ST_ExtWatchdogCfg* Ql_WTD_GetWDIPinCfg(void)
{
    return (ST_ExtWatchdogCfg*)(&wtdCfg);
}

/************************************************************************/
/* Define the working mode of serial debug port (UART2).                */
/*                                                                      */
/* The serial debug port (UART2) may work as a common serial port, as   */
/* well as work as a special debug port that can debug some issues      */
/* underlay application.                                                */
/* Under the special debug mode, please refer to the document           */
/* "genie_Operation_UGD" for the usage of debug port                  */
/* now only supports BASIC MODE*/
/************************************************************************/
static const ST_DebugPortCfg debugPortCfg = {
     BASIC_MODE      // Set the serial  port  to a common serial port
     //ADVANCE_MODE   // Set the serial  port to a special debug port
};
static const ST_DebugPortSet debugPortSet = {
    PORTNAME_UART2,      // Set the serial debug port (UART2) to GKI log .Can choose UART0/UART1/UART2
    PORTNAME_UART1      // Set the serial debug port (UART1) to HSL log .Can choose UART0/UART1/UART2
};

const ST_SystemConfig SystemCfg[] = {
    {SYS_CONFIG_APP_ENABLE_ID,      SYS_CONFIG_APPENABLE_DATA_SIZE,(void*)&appEnableCfg},
    //{SYS_CONFIG_PWRKEY_DATA_ID,     SYS_CONFIG_PWRKEY_DATA_SIZE,   (void*)&pwrkeyCfg   },
    {SYS_CONFIG_WATCHDOG_DATA_ID,   SYS_CONFIG_WATCHDOG_DATA_SIZE, (void*)&wtdCfg      },
    {SYS_CONFIG_DEBUG_MODE_ID,      SYS_CONFIG_DEBUGMODE_DATA_SIZE,(void*)&debugPortCfg},
    {SYS_CONFIG_DEBUG_SET_ID,       SYS_CONFIG_DEBUGSET_DATA_SIZE, (void*)&debugPortSet},
    {SYS_CONFIG_END, 0, NULL                                                           }
};

