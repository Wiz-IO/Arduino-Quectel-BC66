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
 *   ril_urc.c 
 *
 * Project:
 * --------
 *   OpenCPU
 *
 * Description:
 * ------------
 *   The module handles URC in RIL.
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
#include "ql_stdlib.h"
#include "ril.h"
#include "ril_util.h"
#include "ql_system.h"
#include "ql_common.h"
#include "ql_uart.h"
#include "ql_type.h"
#include "ril_lwm2m.h"
#include "ril_socket.h"
#include "ril_system.h"

#ifdef __OCPU_RIL_SUPPORT__


#define RIL_URC_DEBUG_ENABLE 1
#if RIL_URC_DEBUG_ENABLE > 0
#define RIL_URC_DEBUG_PORT  UART_PORT0
static char DBG_Buffer[1024];
#define RIL_URC_DEBUG(BUF,...)  QL_TRACE_LOG(RIL_URC_DEBUG_PORT,BUF,1024,__VA_ARGS__)
#else
#define RIL_URC_DEBUG(BUF,...) 
#endif


/************************************************************************/
/* Definition for URC receive task id.                                  */
/************************************************************************/
#define URC_RCV_TASK_ID  main_task_id

Socket_Recv_Param_t socket_recv_param= {{0},0,0,0};

Lwm2m_Urc_Param_t  lwm2m_urc_param = {0,0,0,0,{0},0,0};
							

/************************************************************************/
/* Declarations for URC handler.                                        */
/************************************************************************/
static void OnURCHandler_Network(const char* strURC, void* reserved);
static void OnURCHandler_SIM(const char* strURC, void* reserved);
static void OnURCHandler_CFUN(const char* strURC, void* reserved);
static void OnURCHandler_InitStat(const char* strURC, void* reserved);
static void OnURCHandler_NbiotEvent(const char* strURC, void* reserved);
/*************** ***TCP &&UDP********************************************/
static void OnURCHandler_QIURC_DATA(const char* strURC, void* reserved);

/*************** ***LWM2M********************************************/
static void OnURCHandler_LwM2M_RECV_DATA(const char* strURC, void* reserved);
static void OnURCHandler_LwM2M_OBSERVE(const char* strURC, void* reserved);



/************************************************************************/
/* Customer ATC URC callback                                          */
/************************************************************************/

/******************************************************************************
* Definitions for URCs and the handler.
* -------------------------------------
* -------------------------------------
* In OpenCPU RIL, URC contains two types: system URC and AT URC.
*   - System URCs indicate the various status of module.
*   - AT URC serves some specific AT command. 
*     For example, some AT command responses as below:
*         AT+QABC     (send at command)
*
*         OK          (response1)
*         +QABC:xxx   (response2) --> this is the final result which is reported by URC.
*     When calling Ql_RIL_SendATCmd() to send such AT command, the return value of 
*     Ql_RIL_SendATCmd indicates the response1, and the response2 may be reported
*     via the callback function. Especially for some AT commands that the time span
*     between response1 and response2 is very long, such as AT+QHTTPDL, AT+QFTPGET.
******************************************************************************/
/****************************************************/
/* Definitions for system URCs and the handler      */
/****************************************************/
static const ST_URC_HDLENTRY m_SysURCHdlEntry[] = {


    //Network status unsolicited response
    {"\r\n+CEREG:",                               OnURCHandler_Network},

    //SIM card unsolicited response
    {"\r\n+CPIN:",                                OnURCHandler_SIM},                       

    //CFUN unsolicited response
    {"\r\n+CFUN:",                                OnURCHandler_CFUN},
	//PSM EVENT unsolicited response
    {"\r\n+QNBIOTEVENT:",                         OnURCHandler_NbiotEvent},

};

/****************************************************/
/* Definitions for AT URCs and the handler          */
/****************************************************/
static const ST_URC_HDLENTRY m_AtURCHdlEntry[] = {
	{"\r\n+QIURC:",                               OnURCHandler_QIURC_DATA},
	{"\r\n+QLWDATARECV:",                         OnURCHandler_LwM2M_RECV_DATA},
	{"\r\n+QLWOBSERVE:",						  OnURCHandler_LwM2M_OBSERVE},
};

static void OnURCHandler_QIURC_DATA(const char* strURC, void* reserved)
{
    /*----------------------------------------------------------------*/
    /* Local Variables                                                */
    /*----------------------------------------------------------------*/
    u8* p1 = NULL;
	s32 ret;
	u8 strTmp[10];
	u32 recv_length = *(char*)reserved;
    p1 = Ql_strstr(strURC, "+QIURC:");
	p1 += Ql_strlen("+QIURC: ");
	recv_length -= (Ql_strlen("+QIURC: ") + 2);   // two means head '\r\n'
	char* param_buffer = (u8*)Ql_MEM_Alloc(SOCKET_RECV_BUFFER_LENGTH);
	char* param_list[20];
	
	/*----------------------------------------------------------------*/
	/* Code Body													  */
	/*----------------------------------------------------------------*/
    if (p1)
    {
		extern bool recv_data_format;		
		u32 param_num = open_socket_push_json_param_parse_cmd(p1, recv_length, param_buffer, param_list, 20); 
		char* prefix = param_list[0];   //  recv
		
		Ql_memset(strTmp, 0x0,  sizeof(strTmp));
	    ret = QSDK_Get_Str(p1,strTmp,0);
		if(Ql_memcmp(strTmp,"\"recv\"",Ql_strlen("\"recv\"")) == 0)
		{
			socket_recv_param.connectID = Ql_atoi(param_list[1]);
			socket_recv_param.recv_length = Ql_atoi(param_list[2]);
			if ( param_num == 4)
			{
				char* recv_buffer = param_list[3];
				Ql_memset(socket_recv_param.recv_buffer, 0x0, SOCKET_RECV_BUFFER_LENGTH);
				if ( recv_data_format == 0 ) //text
				{
					Ql_memcpy(socket_recv_param.recv_buffer, recv_buffer, socket_recv_param.recv_length);
				}
				else if ( recv_data_format == 1 ) //hex
				{
					Ql_memcpy(socket_recv_param.recv_buffer, recv_buffer, socket_recv_param.recv_length*2);
				}
				socket_recv_param.access_mode = SOCKET_ACCESS_MODE_DIRECT;
			}
			else 
			{
				socket_recv_param.access_mode = SOCKET_ACCESS_MODE_BUFFER;
			}
			Ql_OS_SendMessage(URC_RCV_TASK_ID, MSG_ID_URC_INDICATION, URC_SOCKET_RECV_DATA, (u32)&socket_recv_param);
		}
		else if(Ql_memcmp(strTmp,"\"closed\"",Ql_strlen("\"closed\"")) == 0)
		{
			Ql_memset(strTmp, 0x0,  sizeof(strTmp));
		    QSDK_Get_Str(p1,strTmp,1);
			socket_recv_param.connectID = Ql_atoi(strTmp);
	
			Ql_OS_SendMessage(URC_RCV_TASK_ID, MSG_ID_URC_INDICATION, URC_SOCKET_CLOSE,socket_recv_param.connectID);
		}

    }

	if ( param_buffer != NULL )
	{
		Ql_MEM_Free(param_buffer);
		param_buffer = NULL;
	}
}


static void OnURCHandler_LwM2M_RECV_DATA(const char* strURC, void* reserved)
{
    /*----------------------------------------------------------------*/
    /* Local Variables                                                */
    /*----------------------------------------------------------------*/
    char* p1 = NULL;
    p1 = Ql_strstr(strURC, "\r\n+QLWDATARECV:");
	p1 += Ql_strlen("\r\n+QLWDATARECV:");
	p1++;
	char* param_buffer = (u8*)Ql_MEM_Alloc(LWM2M_RECV_BUFFER_LENGTH);
	char* param_list[20];
	
	/*----------------------------------------------------------------*/
	/* Code Body													  */
	/*----------------------------------------------------------------*/
    if (p1)
    {				
		u32 param_num = open_lwm2m_param_parse_cmd(p1, param_buffer, param_list, 20); 
		lwm2m_urc_param.obj_id = Ql_atoi(param_list[0]);
		lwm2m_urc_param.ins_id = Ql_atoi(param_list[1]);
		lwm2m_urc_param.res_num = Ql_atoi(param_list[2]);
		lwm2m_urc_param.recv_length = Ql_atoi(param_list[3]);
		if ( param_num == 5 )
		{
			char* recv_buffer = param_list[4];
			extern bool g_LWM2M_RECV_DATA_MODE;	
			
			Ql_memset(lwm2m_urc_param.recv_buffer, 0x0, LWM2M_RECV_BUFFER_LENGTH);
			if ( g_LWM2M_RECV_DATA_MODE == LWM2M_DATA_FORMAT_TEXT )
			{
				Ql_memcpy(lwm2m_urc_param.recv_buffer, recv_buffer, lwm2m_urc_param.recv_length);
			}
			else if ( g_LWM2M_RECV_DATA_MODE == LWM2M_DATA_FORMAT_HEX )
			{
				Ql_memcpy(lwm2m_urc_param.recv_buffer, recv_buffer, Ql_strlen(recv_buffer) );
			}
			lwm2m_urc_param.access_mode = LWM2M_ACCESS_MODE_DIRECT;
		}
		else 
		{
			lwm2m_urc_param.access_mode = LWM2M_ACCESS_MODE_BUFFER;
		}
		Ql_OS_SendMessage(URC_RCV_TASK_ID, MSG_ID_URC_INDICATION, URC_LwM2M_RECV_DATA, (u32)&lwm2m_urc_param);  
    }

	if ( param_buffer != NULL )
	{
		Ql_MEM_Free(param_buffer);
		param_buffer = NULL;
	}
}

static void OnURCHandler_LwM2M_OBSERVE(const char* strURC, void* reserved)
{
    char* p1 = NULL;
	char* p2 = NULL;
    s32 res_id;
	char strTmp[10];
    p1 = Ql_strstr(strURC, "\r\n+QLWOBSERVE:");
	p1 += Ql_strlen("\r\n+QLWOBSERVE:");
	p1++;
	p2 = Ql_strstr(p1, "\r\n");
	*p2 = '\0';
    if (p1)
    {
		  Ql_memset(strTmp, 0x0,  sizeof(strTmp));
		  QSDK_Get_Str(p1,strTmp,0);
		  lwm2m_urc_param.observe_flag= Ql_atoi(strTmp);

		  Ql_memset(strTmp, 0x0,  sizeof(strTmp));
		  QSDK_Get_Str(p1,strTmp,1);
		  lwm2m_urc_param.obj_id= Ql_atoi(strTmp);

		  Ql_memset(strTmp, 0x0,  sizeof(strTmp));
		  QSDK_Get_Str(p1,strTmp,2);
		  lwm2m_urc_param.ins_id= Ql_atoi(strTmp);

		  Ql_memset(strTmp, 0x0,  sizeof(strTmp));
		  QSDK_Get_Str(p1,strTmp,3);
		  lwm2m_urc_param.res_num= Ql_atoi(strTmp);
          Ql_OS_SendMessage(URC_RCV_TASK_ID, MSG_ID_URC_INDICATION, URC_LwM2M_OBSERVE, (u32)&lwm2m_urc_param);
    }

}


static void OnURCHandler_SIM(const char* strURC, void* reserved)
{
    char* p1 = NULL;
    char* p2 = NULL;
    char strTmp[20];
    s32 len;
    extern s32 RIL_SIM_GetSimStateByName(char* simStat, u32 len);

    Ql_memset(strTmp, 0x0, sizeof(strTmp));
    len = Ql_sprintf(strTmp, "\r\n+CPIN: ");
    if (Ql_StrPrefixMatch(strURC, strTmp))
    {
        p1 = Ql_strstr(strURC, "\r\n+CPIN: ");
        p1 += len;
        p2 = Ql_strstr(p1, "\r\n");
        if (p1 && p2)
        {
            u32 cpinStat;
            Ql_memset(strTmp, 0x0, sizeof(strTmp));
            Ql_memcpy(strTmp, p1, p2 - p1);
            cpinStat = (u32)RIL_SIM_GetSimStateByName(strTmp, p2 - p1);
            Ql_OS_SendMessage(URC_RCV_TASK_ID, MSG_ID_URC_INDICATION, URC_SIM_CARD_STATE_IND, cpinStat);
        }
    }
}




static void OnURCHandler_Network(const char* strURC, void* reserved)
{
    char* p1 = NULL;
    char* p2 = NULL;
    char strTmp[10];
    
    if (Ql_StrPrefixMatch(strURC, "\r\n+CEREG: "))
    {
        u32 nwStat;
        p1 = Ql_strstr(strURC, "\r\n+CEREG: ");
        p1 += Ql_strlen("\r\n+CEREG: ");
		if(*(p1+1) == 0x2C)          //Active query network status without reporting URCS
		{
		   return;
		}
        p2 = Ql_strstr(p1, "\r\n");
        if (p1 && p2)
        {
            Ql_memset(strTmp, 0x0, sizeof(strTmp));
            Ql_memcpy(strTmp, p1, p2 - p1);
            nwStat = Ql_atoi(strTmp);
            Ql_OS_SendMessage(URC_RCV_TASK_ID, MSG_ID_URC_INDICATION, URC_EGPRS_NW_STATE_IND, nwStat);
        }
    }
}

static void OnURCHandler_InitStat(const char* strURC, void* reserved)
{
    u32 sysInitStat = SYS_STATE_START;
    
    if (Ql_strstr(strURC, "\r\nCall Ready\r\n") != NULL)
    {
        sysInitStat = SYS_STATE_PHBOK;
    }
    else if(Ql_strstr(strURC, "\r\nSMS Ready\r\n") != NULL)
    {
        sysInitStat = SYS_STATE_SMSOK;
    }
    Ql_OS_SendMessage(URC_RCV_TASK_ID, MSG_ID_URC_INDICATION, URC_SYS_INIT_STATE_IND, sysInitStat);
}

static void OnURCHandler_CFUN(const char* strURC, void* reserved)
{
    char* p1 = NULL;
    char* p2 = NULL;
    char strTmp[10];
    s32 len;
    u32 cfun;

    len = Ql_strlen("\r\n+CFUN: ");
    p1 = Ql_strstr(strURC, "\r\n+CFUN: ");
    p1 += len;
    p2 = Ql_strstr(p1, "\r\n");
    if (p1 && p2)
    {
        Ql_memset(strTmp, 0x0, sizeof(strTmp));
        Ql_memcpy(strTmp, p1, 1);
        cfun = Ql_atoi(strTmp);
        Ql_OS_SendMessage(URC_RCV_TASK_ID, MSG_ID_URC_INDICATION, URC_CFUN_STATE_IND, cfun);
    }
}


static void OnURCHandler_NbiotEvent(const char* strURC, void* reserved)
{
    Enum_PSM_State psm_state = END_PSM;

	
	RIL_URC_DEBUG(DBG_Buffer,"OnURCHandler_NbiotEvent(%s)\r\n", strURC);
	
	if (Ql_strstr(strURC, "\r\n+QNBIOTEVENT: \"ENTER PSM\"") != NULL)
	{
		psm_state = ENTER_PSM;
	}
	else if (Ql_strstr(strURC, "\r\n+QNBIOTEVENT: \"EXIT PSM\"") != NULL)
	
	{
		psm_state= EXIT_PSM;
	}
	Ql_OS_SendMessage(URC_RCV_TASK_ID, MSG_ID_URC_INDICATION, URC_PSM_EVENT, psm_state);
}


static void OnURCHandler_Undefined(const char* strURC, void* reserved)
{

    Ql_OS_SendMessage(URC_RCV_TASK_ID, MSG_ID_URC_INDICATION, URC_END, 0);
}

/*****************************************************************
* Function:     OnURCHandler 
* 
* Description:
*               This function is the entrance for Unsolicited Result Code (URC) Handler.
*
* Parameters:
*               strURC:      
*                   [IN] a URC string terminated by '\0'.
*
*               reserved:       
*                   reserved, can be NULL.
* Return:        
*               The function returns "ptrUrc".
*****************************************************************/
void OnURCHandler(const char* strURC, void* reserved)
{
    s32 i;
    
    if (NULL == strURC)
    {
        return;
    }

    // For system URCs
    for (i = 0; i < NUM_ELEMS(m_SysURCHdlEntry); i++)
    {
        if (Ql_strstr(strURC, m_SysURCHdlEntry[i].keyword))
        {
            m_SysURCHdlEntry[i].handler(strURC, reserved);
            return;
        }
    }

    // For AT URCs
    for (i = 0; i < NUM_ELEMS(m_AtURCHdlEntry); i++)
    {
        if (Ql_strstr(strURC, m_AtURCHdlEntry[i].keyword))
        {
            m_AtURCHdlEntry[i].handler(strURC, reserved);
            return;
        }
    }

    // For undefined URCs
    OnURCHandler_Undefined(strURC, reserved);
}

/******************************************************************************
* Function:     Ql_RIL_IsURCStr
*  
* Description:
*               This function is used to check whether a string is URC information
*               you defined.
.
* Parameters:    
*               strRsp: 
*                     [in]a string for the response of the AT command.
* Return:  
*               0 : not URC information
*               1 : URC information
******************************************************************************/
s32 Ql_RIL_IsURCStr(const char* strRsp)
{
    s32 i;
    for (i = 0; i < NUM_ELEMS(m_SysURCHdlEntry); i++) 
    {
        if (Ql_strstr(strRsp, m_SysURCHdlEntry[i].keyword)) 
        {
            return 1;
        }
    }
    for (i = 0; i < NUM_ELEMS(m_AtURCHdlEntry); i++) 
    {
        if (Ql_strstr(strRsp, m_AtURCHdlEntry[i].keyword)) 
        {
            return 1;
        }
    }
    return 0;
}

#endif  // __OCPU_RIL_SUPPORT__
