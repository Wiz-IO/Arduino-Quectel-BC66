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
#include "ql_common.h"

#ifdef __OCPU_RIL_SUPPORT__

#define RIL_FTP_DEBUG_ENABLE 0
#if RIL_FTP_DEBUG_ENABLE > 0
#define RIL_FTP_DEBUG_PORT  UART_PORT0
static char DBG_Buffer[100];
#define RIL_FTP_DEBUG(BUF,...)  QL_TRACE_LOG(RIL_FTP_DEBUG_PORT,BUF,100,__VA_ARGS__)
#else
#define RIL_FTP_DEBUG(BUF,...) 
#endif


static s32 ATResponse_Handler(char* line, u32 len, void* userData)
{
    RIL_FTP_DEBUG(DBG_Buffer,"[ATResponse_Handler] %s\r\n", (u8*)line);
    
    if (Ql_RIL_FindLine(line, len, "OK"))
    {  
        return  RIL_ATRSP_SUCCESS;
    }
    else if (Ql_RIL_FindLine(line, len, "ERROR"))
    {  
        return  RIL_ATRSP_FAILED;
    }
    else if (Ql_RIL_FindString(line, len, "+CME ERROR"))
    {
        return  RIL_ATRSP_FAILED;
    }
    else if (Ql_RIL_FindString(line, len, "+CMS ERROR:"))
    {
        return  RIL_ATRSP_FAILED;
    }
    
    return RIL_ATRSP_CONTINUE; //continue wait
}

static s32 ATRsp_Soc_Create_Handler(char* line, u32 len, void* userdata)
{  
    char *head = Ql_RIL_FindString(line, len, "\r\n+QSOC="); //continue wait
    if(head)
    {
         u8 *p = NULL;
		 s32 *state = (s32 *)userdata;
         p = (u8*)head + Ql_strlen("\r\n+QSOC=");
		 *(p+1) = '\0';
         *state = Ql_atoi((const char*)p);
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


s32  RIL_QSOC_Create(u8 domin,u8 type, u8 protocol)
{

    s32 retRes = 0;
	s32 socid = 0;
    char strAT[200] ;

    Ql_memset(strAT,0x00, sizeof(strAT));
    Ql_sprintf(strAT,"AT+QSOC=%d,%d,%d\n",domin,type,protocol);

        
    retRes = Ql_RIL_SendATCmd(strAT,Ql_strlen(strAT), ATRsp_Soc_Create_Handler,&socid,0);
	
	RIL_FTP_DEBUG(DBG_Buffer,"<-- Send AT:%s, ret = %d -->\r\n",strAT,retRes);
	if (RIL_AT_SUCCESS == retRes)
    {
        return socid;
    }else{
        return retRes;
    }

}



s32 RIL_QSOC_CONN(u8 soc_id, u32 port,u8* ip) 
{
    s32 ret = RIL_AT_SUCCESS;
    char strAT[200];
	
	
    Ql_memset(strAT, 0, sizeof(strAT));
	Ql_sprintf(strAT,"AT+QSOCON=%d,%d,\"%s\"\n",soc_id,port,ip);
    ret = Ql_RIL_SendATCmd(strAT,Ql_strlen(strAT),ATResponse_Handler,0,0);
	RIL_FTP_DEBUG(DBG_Buffer,"<-- Send AT:%s, ret = %d -->\r\n",strAT, ret);
    return ret;
    
}

s32 RIL_QSOC_SEND(u8 soc_id, u32 send_length,u8* send_buffer) 
{
    s32 ret = RIL_AT_SUCCESS;
    char strAT[200];
	
    Ql_memset(strAT, 0, sizeof(strAT));
    Ql_sprintf(strAT, "AT+QSOSEND=%d,%d,%s\n",soc_id,send_length, send_buffer);
    ret = Ql_RIL_SendATCmd(strAT,Ql_strlen(strAT),ATResponse_Handler,0,0);
	
	RIL_FTP_DEBUG(DBG_Buffer,"<--Send AT:%s, ret = %d -->\r\n",strAT, ret);
    return ret;
    
}


s32 RIL_QSOC_CLOSE(u8 soc_id) 
{
    s32 ret = RIL_AT_SUCCESS;
    char strAT[200];

    Ql_memset(strAT, 0, sizeof(strAT));
    Ql_sprintf(strAT, "AT+QSOCL=%d\n",soc_id);
    ret = Ql_RIL_SendATCmd(strAT,Ql_strlen(strAT),ATResponse_Handler,0,0);

	RIL_FTP_DEBUG(DBG_Buffer,"<-- Send AT:%s, ret = %d -->\r\n",strAT, ret);
    return ret;
}

#endif  //__OCPU_RIL_SUPPORT__

