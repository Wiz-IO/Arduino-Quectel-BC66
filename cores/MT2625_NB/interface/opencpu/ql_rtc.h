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
 *   ql_timer.h 
 *
 * Project:
 * --------
 *   OpenCPU
 *
 * Description:
 * ------------
 *  Timer related APIs
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
 

#ifndef __QL_RTC_H__
#define __QL_RTC_H__
#include "ql_type.h"

/**************************************************************
 * User RTC  ID Definition
 **************************************************************/
#define     RTC_ID_USER_START    0x200



typedef void(*Callback_Rtc_Func)(u32 rtcId, void* param);
typedef void (*Callback_Psm_Eint_Func)(void *user_data);



/*****************************************************************
* Function:     Ql_Rtc_RegisterFast 
* 
* Description:
*               Register rtc,only support 15 RTC under opencpu task.
*
* Parameters:
*               timerId:
*                       [in] The rtc id must be bigger than 0xFF.And make sure that the id is
*                            not the same with the ID that registered by "Ql_Rtc_RegisterFast".
*
*              callback_onTimer:
*                       [out] Notify the application when the time of the rtc arrives.
*               param:
*                       [in] Used to pass parameters of customers.
* Return:
*               QL_RET_OK indicates register ok;
*               QL_RET_ERR_PARAM indicates the param error.
*               QL_RET_ERR_INVALID_TIMER indicates that the timer ID is already being used  
*               or the timer is started or stopped not in the same task with it registered.
*               QL_RET_ERR_TIMER_FULL indicates all timers are used up.
*               QL_RET_ERR_INVALID_TASK_ID indicates the task invalid.
* Notes:
*
*    
*****************************************************************/
s32 Ql_Rtc_RegisterFast(u32 rtcId, Callback_Rtc_Func callback_onTimer, void* param);

/*****************************************************************
* Function:     Ql_Rtc_Start 
* 
* Description:
*               Start up a rtc with the specified rtc id.
*
* Parameters:
*               timerId:
*                       [in] rtc id, bigger than 0xFF,the timer id must be registed.
*               interval:
*                       [in] Set the interval of the timer, unit: ms.
*                           this value must be is the multiple of 100ms
*               autoRepeat:
*                       [in] TRUE indicates that the rtc is executed repeatedly.
*                            FALSE indicates that the rtc is executed only once.
* Return:
*               QL_RET_OK indicates register ok;
*               QL_RET_ERR_PARAM indicates the param error.
*               QL_RET_ERR_INVALID_TIMER indicates that the timer ID is already being used  
*               or the timer is started or stopped not in the same task with it registered.
*               QL_RET_ERR_TIMER_FULL indicates all timers are used up.
*               QL_RET_ERR_INVALID_TASK_ID indicates the task invalid.
* Notes:
*    
*****************************************************************/
s32 Ql_Rtc_Start(u32 rtcId, u32 interval, bool autoRepeat);

/*****************************************************************
* Function:     Ql_Rtc_Stop 
* 
* Description:
*               Stop the rtc with the specified rtc id.
*
* Parameters:
*               timerId:
*                   [in] the rtc id. The rtc has been started 
*                   by calling Ql_rtc_Start previously.
* Return:
*               QL_RET_OK indicates register ok;
*               QL_RET_ERR_PARAM indicates the param error.
*               QL_RET_ERR_INVALID_TIMER indicates that the timer ID is already being used  
*               or the timer is started or stopped not in the same task with it registered.
*               QL_RET_ERR_TIMER_FULL indicates all timers are used up.
*               QL_RET_ERR_INVALID_TASK_ID indicates the task invalid.
* Notes:
*    
*****************************************************************/
s32 Ql_Rtc_Stop(u32 rtcId);


/*****************************************************************
* Function:     Ql_Psm_Eint_Register 
* 
* Description:
*               Register the callback of PSM_EINT
*
* Parameters:
*               Callback_Psm_Eint_Func:
*                    [out] Notify the application when the PSM_EINT event occuerd.
* Return:
*               QL_RET_OK indicates register ok;
*               QL_RET_ERR_PARAM indicates the param error.
* Notes:
*    
*****************************************************************/
s32 Ql_Psm_Eint_Register(Callback_Psm_Eint_Func  callback_psm_eint,void* param);


#endif  // End-of __QL_TIMER_H__

