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
 

#ifndef __QL_TIMER_H__
#define __QL_TIMER_H__
#include "ql_type.h"

/**************************************************************
 * User TIMER ID Definition
 **************************************************************/
#define     TIMER_ID_USER_START    0x100



typedef void(*Callback_Timer_OnTimer)(u32 timerId, void* param);

/*****************************************************************
* Function:     Ql_Timer_Register 
* 
* Description:
*               Register stack timer,each task only supports 10 timer.
*
* Parameters:
*               timerId:
*                       [in] The timer id must be bigger than 0xFF.And make sure that the id is
*                            the only one under opencpu task.Of course, the ID that registered 
*                            by "Ql_Timer_RegisterFast" also cannot be the same with it.
*                            
*              callback_onTimer:
*                       [out] Notify the application when the time of the timer arrives.
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
*               If you register a timer Id in an opencpu task, then you can only start or stop 
*               the timer in the same task.Otherwise,the timer can not be started or stopped.
*    
*****************************************************************/
s32 Ql_Timer_Register(u32 timerId, Callback_Timer_OnTimer callback_onTimer, void* param);

/*****************************************************************
* Function:     Ql_Timer_RegisterFast 
* 
* Description:
*               Register GP timer,only support one timer under opencpu task.
*
* Parameters:
*               timerId:
*                       [in] The timer id must be bigger than 0xFF.And make sure that the id is
*                            not the same with the ID that registered by "Ql_Timer_Register".
*
*              callback_onTimer:
*                       [out] Notify the application when the time of the timer arrives.
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
*               If you register a timer Id in an opencpu task, then you can only start or stop 
*               the timer in the same task.Otherwise,the timer can not be started or stopped.
*    
*****************************************************************/
s32 Ql_Timer_RegisterFast(u32 timerId, Callback_Timer_OnTimer callback_onTimer, void* param);

/*****************************************************************
* Function:     Ql_StartTimer 
* 
* Description:
*               Start up a timer with the specified timer id.
*
* Parameters:
*               timerId:
*                       [in] timer id, bigger than 0xFF,the timer id must be registed.
*               interval:
*                       [in] Set the interval of the timer, unit: ms.
*                            if you start a stack timer, the interval must be 
*                            greater than or equal to 1ms.
*                            if you start a GP timer, the interval must be 
*                            an integer multiple of 10ms.
*               autoRepeat:
*                       [in] TRUE indicates that the timer is executed repeatedly.
*                            FALSE indicates that the timer is executed only once.
* Return:
*               QL_RET_OK indicates register ok;
*               QL_RET_ERR_PARAM indicates the param error.
*               QL_RET_ERR_INVALID_TIMER indicates that the timer ID is already being used  
*               or the timer is started or stopped not in the same task with it registered.
*               QL_RET_ERR_TIMER_FULL indicates all timers are used up.
*               QL_RET_ERR_INVALID_TASK_ID indicates the task invalid.
* Notes:
*               If you register a timer Id in an opencpu task, then you can only start or stop 
*               the timer in the same task.Otherwise,the timer can not be started or stopped.
*    
*****************************************************************/
s32 Ql_Timer_Start(u32 timerId, u32 interval, bool autoRepeat);

/*****************************************************************
* Function:     Ql_StopTimer 
* 
* Description:
*               Stop the timer with the specified timer id.
*
* Parameters:
*               timerId:
*                   [in] the timer id. The timer has been started 
*                   by calling Ql_Timer_Start previously.
* Return:
*               QL_RET_OK indicates register ok;
*               QL_RET_ERR_PARAM indicates the param error.
*               QL_RET_ERR_INVALID_TIMER indicates that the timer ID is already being used  
*               or the timer is started or stopped not in the same task with it registered.
*               QL_RET_ERR_TIMER_FULL indicates all timers are used up.
*               QL_RET_ERR_INVALID_TASK_ID indicates the task invalid.
* Notes:
*               If you register a timer Id in an opencpu task, then you can only start or stop 
*               the timer in the same task.Otherwise,the timer can not be started or stopped.
*    
*****************************************************************/
s32 Ql_Timer_Stop(u32 timerId);

#endif  // End-of __QL_TIMER_H__

