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
 *   ril_atResponse.c 
 *
 * Project:
 * --------
 *   OpenCPU
 *
 * Description:
 * ------------
 *   The module handles the AT response in RIL.
 *   Developer may reprogram to cover some special AT commands according to the requirements.
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
#include "ril_util.h"
#include "ql_stdlib.h"
#include "ql_trace.h"

#ifdef __OCPU_RIL_SUPPORT__

static s32 m_iErrCode = 0; // Is used to record the specific error code
                            // 0 indicates success in executing AT
                            // -1 indicats failure in executing AT
                            // other value indicates the specific error code after executing AT failed.
                            //   you can usually find the meaning of error code in ATC document.
s32 Ql_RIL_AT_GetErrCode(void) {return m_iErrCode;}
//
// Developer can call this API to set the error code when resolving the response for AT.
s32 Ql_RIL_AT_SetErrCode(s32 errCode) {m_iErrCode = errCode; return errCode; }

/******************************************************************************
* Function:     Default_atRsp_callback
*  
* Description:
*               If you set the callback parameter of Ql_RIL_SendATCmd to NULL,
*               we will provide you with a default callback function.But we need
*               to clarify that this callback function can only handle simple 
*               response of the AT command.The response of AT command only is 
*               OK or error.
*
* Parameters:    
*               line:  
*                   [in]The address of the string.
*               len:   
*                   [in]The length of the string.
*               userdata: 
*                   [out]Used to transfer the customer's parameter.
* Return:  
*               RIL_ATRSP_SUCCESS : AT command executed successfully.
*               RIL_ATRSP_FAILED : AT command executed failed.
******************************************************************************/
s32 Default_atRsp_callback(char* line, u32 len, void* userdata)
{
    //Ql_Debug_Trace("[Default_atRsp_callback] %s\r\n", (u8*)line);
    
    if (Ql_RIL_FindLine(line, len, "OK"))// find <CR><LF>OK<CR><LF>,OK<CR><LF>, <CR>OK<CR>£¬<LF>OK<LF>
    {
        m_iErrCode = RIL_ATRSP_SUCCESS;
        return  RIL_ATRSP_SUCCESS;
    }
    else if (Ql_RIL_FindLine(line, len, "ERROR")) // find <CR><LF>ERROR<CR><LF>, <CR>ERROR<CR>£¬<LF>ERROR<LF>
    {
        m_iErrCode = RIL_ATRSP_FAILED;
        return  RIL_ATRSP_FAILED;
    }
    else if (Ql_RIL_FindString(line, len, "+CME ERROR:") || 
              Ql_RIL_FindString(line, len, "+CMS ERROR:") ||
              Ql_RIL_FindString(line, len, "+CIS ERROR:"))
    {
        Ql_sscanf(line, "%*[^:]: %d\r\n", &m_iErrCode);
        return  RIL_ATRSP_FAILED;
    }
    return RIL_ATRSP_CONTINUE; //continue wait
}

#endif  //__OCPU_RIL_SUPPORT__

