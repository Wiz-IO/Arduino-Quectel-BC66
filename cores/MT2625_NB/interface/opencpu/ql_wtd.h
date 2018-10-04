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
 *   ql_wtd.h 
 *
 * Project:
 * --------
 *   OpenCPU
 *
 * Description:
 * ------------
 *  watch dog APIs defines.
 *
 *
 * Attention:
 * ------------
 * When calling Ql_WTD_Init to start a GPTimer,module can not enter to sleep mode
 *
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


#ifndef __WATCHDOG_H__
#define __WATCHDOG_H__
#include "ql_type.h"
#include "ql_gpio.h"


/*****************************************************************
* Function:     Ql_WTD_Init
*
* Description:
*               This function starts a base H/W timer, which is responsible for feed the external watchdog. And specify the I/O pin and feeding interval. 
*               Besides, this function may specify the reset mode (H/W reset or S/W reset) when the watchdog overflows.
*               H/W reset means the external watchdog chip resets the module.
*
* Parameters:
*               resetMode:
*                    [in] Must be zero, H/W reset.
*               wtdPin:
*                    [in]I/O pin that connects to the WDI pin of external watchdog chip.
*               interval: 
*                    [in]the interval for feeding external watchdog.the min value of interval is 200. Unit in ms.
*
*               Example:
*                   Ql_WTD_Init(0,PINNAME_RI,600);// start an external watchdog,set RI to feed dog within 600ms
*                  
*
* Return:
*               QL_RET_OK indicates success in starting watch dog service.
*               QL_RET_ERR_PARAM indicates the param invalid.
*****************************************************************/
s32 Ql_WTD_Init(s32 resetMode, Enum_PinName wtdPin, u32 interval);



/*****************************************************************
* Function:     Ql_WTD_Start
*
* Description:
*               The function starts an internal watchdog. If needed, every task may call this function to start an interval watchdog service.
* Parameters:
*               interval:
*                   [in]the interval for feeding internal watchdog.the min value of interval is 400. Unit in ms.
*                       
*
*               Example:
*                   Ql_WTD_Start(2000);
*                   If not call Ql_WTD_Feed within 2000ms ,the module will automatically reset.
*                                    
* Return:
*               Success return Watchdog ID
*               QL_RET_ERR_PARAM indicates the param invalid.
*****************************************************************/
s32 Ql_WTD_Start(u32 interval);


/*****************************************************************
* Function:     Ql_WTD_Feed
*
* Description:
*               This function feeds the  watchdog that is started by Ql_WTD_Start().
* Parameters:
*               wtdID:
*                   [in] watchdog ID, which is returned by Ql_WTD_Start().
*                                    
* Return:
*           None
*****************************************************************/
void Ql_WTD_Feed(s32 wtdID);


/*****************************************************************
* Function:     Ql_WTD_Stop
*
* Description:
*              This function stops a watchdog that is started by Ql_WTD_Start(). 
* Parameters:
*               wtdID:
*               [in]watchdog ID, which is returned by Ql_WTD_Start().
*
* Return:
*               None
*****************************************************************/
void Ql_WTD_Stop(s32 wtdID);

#endif
