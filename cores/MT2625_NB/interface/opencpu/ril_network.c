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
 *   ril_network.c 
 *
 * Project:
 * --------
 *   OpenCPU
 *
 * Description:
 * ------------
 *   The module implements network related APIs.
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
#include "ril_network.h"
#include "ril.h"
#include "ril_util.h"
#include "ql_stdlib.h"
#include "ql_trace.h"
#include "ql_error.h"
#include "ql_system.h"
#include "ql_trace.h"

#ifdef __OCPU_RIL_SUPPORT__


s32 RIL_SIM_GetSimStateByName(char* simStat, u32 len)
{
    s32 ss = SIM_STAT_UNSPECIFIED;
    if (Ql_strncmp(simStat, "READY", len) == 0)
    {
        ss = SIM_STAT_READY;
    }
    else if (Ql_strncmp(simStat, "NOT INSERTED", len) == 0)
    {
        ss = SIM_STAT_NOT_INSERTED;
    }
    else if (Ql_strncmp(simStat, "SIM PIN", len) == 0)
    {
        ss = SIM_STAT_PIN_REQ;
    }
    else if (Ql_strncmp(simStat, "SIM PUK", len) == 0)
    {
        ss = SIM_STAT_PUK_REQ;
    }
    else if (Ql_strncmp(simStat, "PH-SIM PIN", len) == 0)
    {
        ss = SIM_STAT_PH_PIN_REQ;
    }
    else if (Ql_strncmp(simStat, "PH-SIM PUK", len) == 0)
    {
        ss = SIM_STAT_PH_PUK_REQ;
    }
    else if (Ql_strncmp(simStat, "SIM PIN2", len) == 0)
    {
        ss = SIM_STAT_PIN2_REQ;
    }
    else if (Ql_strncmp(simStat, "SIM PUK2", len) == 0)
    {
        ss = SIM_STAT_PUK2_REQ;
    }
    else if (Ql_strncmp(simStat, "SIM BUSY", len) == 0)
    {
        ss = SIM_STAT_BUSY;
    }
    else if (Ql_strncmp(simStat, "NOT READY", len) == 0)
    {
        ss = SIM_STAT_NOT_READY;
    }
    return ss;
}

/******************************************************************************
* Function:     ATResponse_CEREG_Handler
*  
* Description:
*               This function is used to deal with the response of the AT+CEREG command.
*
* Parameters:    
*                line:  
*                    [in]The address of the string.
*                len:   
*                    [in]The length of the string.
*                userdata: 
*                    [out]Used to transfer the customer's parameter.
*                       
* Return:  
*               RIL_ATRSP_SUCCESS, indicates AT executed successfully..
*               RIL_ATRSP_FAILED, indicates AT executed failed. 
*               RIL_ATRSP_CONTINUE,indicates continue to wait for the response
*               of the AT command.
* Notes:
*               1.Can't send any new AT commands in this function.
*               2.RIL handle the AT response line by line, so this function may 
*                 be called multiple times.
******************************************************************************/
static s32 ATResponse_CEREG_Handler(char* line, u32 len, void* userdata)
{
    char *head = Ql_RIL_FindString(line, len, "+CEREG:"); //continue wait
    if(head)
    {
        s32 n = 0;
        s32 *state = (s32 *)userdata;
        Ql_sscanf(head,"%*[^ ]%d,%d,%[^\r\n]",&n,state);
        return  RIL_ATRSP_CONTINUE;
    }

   head = Ql_RIL_FindLine(line, len, "OK"); // find <CR><LF>OK<CR><LF>, <CR>OK<CR>£¬<LF>OK<LF>
   if(head)
   {  
       return  RIL_ATRSP_SUCCESS;
   }

    head = Ql_RIL_FindLine(line, len, "ERROR");// find <CR><LF>ERROR<CR><LF>, <CR>ERROR<CR>£¬<LF>ERROR<LF>
    if(head)
    {  
        return  RIL_ATRSP_FAILED;
    } 

    head = Ql_RIL_FindString(line, len, "+CME ERROR:");//fail
    if(head)
    {
        return  RIL_ATRSP_FAILED;
    }

    return RIL_ATRSP_CONTINUE; //continue wait
}

s32  RIL_NW_GetEGPRSState(s32 *stat)
{
    s32 retRes = -1;
    s32 nStat = 0;
    char strAT[] = "AT+CEREG?\0";

    retRes = Ql_RIL_SendATCmd(strAT, Ql_strlen(strAT), ATResponse_CEREG_Handler, &nStat, 0);
    if(RIL_AT_SUCCESS == retRes)
    {
       *stat = nStat; 
    }
    return retRes;
}

#endif  //__OCPU_RIL_SUPPORT__

