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
 *   ril_init.c 
 *
 * Project:
 * --------
 *   OpenCPU
 *
 * Description:
 * ------------
 *   This file is used for customer to inital RIL interface.
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
#include "custom_feature_def.h"
#include "ril.h"
#include "ql_stdlib.h"
#include "ql_trace.h"
#include "ql_error.h"
#include "ql_system.h"

#ifdef __OCPU_RIL_SUPPORT__ 

/***********************************************************************
*  Initial commands for RIL. g_InitCmds[] will be used by Ql_RIL_Initialize function.
*  Now RIL is implemented based on the following AT commands.
************************************************************************/
const char* g_InitCmds[] = {
    //"ATE0Q0V1\r",   // verbose result codes
    "AT+CMEE=1\r",  // Extended errors. This item is necessary.     
    //"ATS0=0\r",     // No auto-answer.  If customer want auto answer the incoming call , must change this string as "ATS0=n\r" (n=1~255).
    "AT+CEREG=1\r",    // NW registration events . 
    //"AT+CGREG=1\r", // GPRS registration events
    //"AT+CSCON=1\r",  // 
    //"AT+COLP=0\r"   // no connected line identification

//......  More customization setting can add here
};

u32 RIL_GetInitCmdCnt(void)
{
    return NUM_ELEMS(g_InitCmds);
}

/***********************************************************************
*  Limited commands for RIL. 
*  Now RIL is implemented based on the opposite functions of the 
*  following AT commands.
************************************************************************/
const char* g_LimitedCmds[] = {
    "AT+CMEE=0",
    //"AT+CLIP",
};
u32 RIL_GetLimitedCmdCnt(void)
{
    return NUM_ELEMS(g_LimitedCmds);
}

#endif  //__OCPU_RIL_SUPPORT__
