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
 *   ql_time.h 
 *
 * Project:
 * --------
 *   OpenCPU
 *
 * Description:
 * ------------
 *  Time related APIs
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
 

#ifndef __QL_TIME_H__
#define __QL_TIME_H__
#include "ql_type.h"

typedef struct {
    s32 year;    
    s32 month;
    s32 day;
    s32 hour;
    s32 minute;
    s32 second;
    s32 timezone;  // The range is(-11~12).one digit expresses an hour, for example: 8 indicates "GMT+8"
}ST_Time;

/*****************************************************************
* Function:     Ql_SetLocalTime 
* 
* Description:
*               Set the current local date and time.
*
* Parameters:
*               dateTime:
*                       [in] Point to the ST_Time object
* Return:        
*               QL_RET_OK indicates this function is executed successesfully.
*               QL_RET_ERR_PARAM, indicates the parameter is error.
*
*****************************************************************/
s32 Ql_SetLocalTime(ST_Time* dateTime);

/*****************************************************************
* Function:     Ql_GetLocalTime 
* 
* Description:
*               Get the current local date and time.
*
* Parameters:
*               dateTime:
*                       [out] Point  to the ST_Time object
* Return:        
*               if succeed,return the current local date and time
*               , NULL means get failure.
*****************************************************************/
ST_Time* Ql_GetLocalTime(ST_Time* dateTime);

/*****************************************************************
* Function:     Ql_Mktime 
* 
* Description:
*               This function get total seconds elapsed 
*               since 1970.01.01 00:00:00.
*
* Parameters:
*               dateTime:
*                       [in] Point to the ST_Time object
* Return:        
*               The total seconds
*---------------
* Usage:
*               ST_Time systime;
*               Ql_GetLocalTime(&systime);
*               seconds = Ql_Mktime(&systime);
*****************************************************************/
u64 Ql_Mktime(ST_Time* dateTime);

/*****************************************************************
* Function:     Ql_MKTime2CalendarTime 
* 
* Description:
*               This function convert the seconds elapsed since 
*               1970.01.01 00:00:00 to local date and time.
*
* Parameters:
*               seconds:
*                       [in] the seconds elapsed since 
*                            1970.01.01 00:00:00
*               pOutDateTime:
*                       [out] Point to the ST_Time object
* Return:
*               if succeed,return the current local date and time
*               , NULL means operation failure.
*
*---------------
* Usage:
*               ST_Time systime;
*               systime = Ql_MKTime2CalendarTime(seconds, &systime);
*               
*****************************************************************/
ST_Time* Ql_MKTime2CalendarTime(u64 seconds, ST_Time* pOutDateTime);

#endif
