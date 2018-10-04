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
 *   ril_lwm2m.c 
 *
 * Project:
 * --------
 *   OpenCPU
 *
 * Description:
 * ------------
 *   The module implements lwm2m related APIs.
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
#include "ql_common.h"
#include "ril_LwM2M.h"
#include "ril_system.h"
#include "ql_uart.h"

#ifdef __OCPU_RIL_SUPPORT__

#define RIL_LwM2M_DEBUG_ENABLE 0
#if RIL_LwM2M_DEBUG_ENABLE > 0
#define RIL_LwM2M_DEBUG_PORT  UART_PORT2
static char DBG_Buffer[1024];
#define RIL_LwM2M_DEBUG(BUF,...)  QL_TRACE_LOG(RIL_LwM2M_DEBUG_PORT,BUF,1024,__VA_ARGS__)
#else
#define RIL_LwM2M_DEBUG(BUF,...) 
#endif

#define DEBUG_ENABLE 1
#if DEBUG_ENABLE > 0
#define DEBUG_PORT  UART_PORT0
#define DBG_BUF_LEN   1024
static char DBG_BUFFER[DBG_BUF_LEN];
#define APP_DEBUG(FORMAT,...) {\
    Ql_memset(DBG_BUFFER, 0, DBG_BUF_LEN);\
    Ql_sprintf(DBG_BUFFER,FORMAT,##__VA_ARGS__); \
    if (UART_PORT1 == (DEBUG_PORT)) \
    {\
        Ql_Debug_Trace(DBG_BUFFER);\
    } else {\
        Ql_UART_Write((Enum_SerialPort)(DEBUG_PORT), (u8*)(DBG_BUFFER), Ql_strlen((const char *)(DBG_BUFFER)));\
    }\
}
#else
#define APP_DEBUG(FORMAT,...) 
#endif

typedef struct {
	u32 actual_length;
	u32 remain_length;

} ST_Lwm2m_RD_TEMP_Param;

ST_Lwm2m_RD_TEMP_Param lwm2m_rd_temp_param = { 0, 0 };

volatile bool g_LWM2M_RECV_DATA_MODE = LWM2M_DATA_FORMAT_TEXT;
static s32 ATResponse_Handler(char* line, u32 len, void* userData) {
	RIL_LwM2M_DEBUG(DBG_Buffer,"[ATResponse_Handler] %s\r\n", (u8*)line);

	if (Ql_RIL_FindLine(line, len, "OK")) {
		return RIL_ATRSP_SUCCESS;
	} else if (Ql_RIL_FindLine(line, len, "ERROR")) {
		return RIL_ATRSP_FAILED;
	} else if (Ql_RIL_FindString(line, len, "+CME ERROR")) {
		return RIL_ATRSP_FAILED;
	} else if (Ql_RIL_FindString(line, len, "+CMS ERROR:")) {
		return RIL_ATRSP_FAILED;
	}

	return RIL_ATRSP_CONTINUE; //continue wait
}

//static
s32 ATResponse_Open_Handler(char* line, u32 len, void* userData) {
	RIL_LwM2M_DEBUG(DBG_Buffer,"[ATResponse_Handler] %s\r\n", (u8*)line);

	if (Ql_RIL_FindLine(line, len, "CONNECT OK")) {
		return RIL_ATRSP_SUCCESS;
	} else if (Ql_RIL_FindLine(line, len, "ERROR")) {
		return RIL_ATRSP_FAILED;
	} else if (Ql_RIL_FindString(line, len, "+CME ERROR")) {
		return RIL_ATRSP_FAILED;
	} else if (Ql_RIL_FindString(line, len, "+CMS ERROR:")) {
		return RIL_ATRSP_FAILED;
	} else if (Ql_RIL_FindString(line, len, "UPDATE FAIL")) {
		return RIL_ATRSP_FAILED;
	}

	return RIL_ATRSP_CONTINUE; //continue wait
}

static s32 ATResponse_Update_Handler(char* line, u32 len, void* userData) {
	RIL_LwM2M_DEBUG(DBG_Buffer,"[ATResponse_Handler] %s\r\n", (u8*)line);

	if (Ql_RIL_FindLine(line, len, "UPDATE OK")) {
		return RIL_ATRSP_SUCCESS;
	} else if (Ql_RIL_FindLine(line, len, "ERROR")) {
		return RIL_ATRSP_FAILED;
	} else if (Ql_RIL_FindString(line, len, "+CME ERROR")) {
		return RIL_ATRSP_FAILED;
	} else if (Ql_RIL_FindString(line, len, "+CMS ERROR:")) {
		return RIL_ATRSP_FAILED;
	} else if (Ql_RIL_FindString(line, len, "UPDATE FAIL")) {
		return RIL_ATRSP_FAILED;
	}

	return RIL_ATRSP_CONTINUE; //continue wait
}

static s32 ATResponse_Send_Handler(char* line, u32 len, void* userData) {
	//RIL_LwM2M_DEBUG(DBG_Buffer,"[ATResponse_Handler] %s\r\n", (u8*)line);
	APP_DEBUG("%s\r\n", (u8* )line);

	if (Ql_RIL_FindLine(line, len, "SEND OK")) {
		return RIL_ATRSP_SUCCESS;
	} else if (Ql_RIL_FindLine(line, len, "ERROR")) {
		return RIL_ATRSP_FAILED;
	} else if (Ql_RIL_FindString(line, len, "+CME ERROR")) {
		return RIL_ATRSP_FAILED;
	} else if (Ql_RIL_FindString(line, len, "+CMS ERROR:")) {
		return RIL_ATRSP_FAILED;
	} else if (Ql_RIL_FindString(line, len, "SEND FAIL")) {
		return RIL_ATRSP_FAILED;
	}

	return RIL_ATRSP_CONTINUE; //continue wait
}

static s32 ATResponse_Recv_Handler(char* line, u32 len, void* userData) {
	LwM2M_Recv_Param *lwm2m_recv_param = (LwM2M_Recv_Param *) userData;
	char *head = Ql_RIL_FindString(line, len, (char*) lwm2m_recv_param->prefix); //continue wait

	char strTmp[10];
	char* p1 = NULL;
	char* p2 = NULL;
	if (head) {
		p1 = Ql_strstr(head, ":");
		p1 += 1;
		p2 = Ql_strstr(p1, "\r\n");
		*p2 = '\0';
		if (p1) {
			Ql_memset(strTmp, 0x0, sizeof(strTmp));
			QSDK_Get_Str(p1, strTmp, 0);
			lwm2m_rd_temp_param.actual_length = Ql_atoi(strTmp);
			RIL_LwM2M_DEBUG(DBG_Buffer,"[lwm2m_param->length] %d\r\n", lwm2m_rd_temp_param.actual_length);

			if (0 == lwm2m_rd_temp_param.actual_length) //no data
					{
				lwm2m_recv_param->actual_length = 0;
				return RIL_ATRSP_CONTINUE;
			}
			Ql_memset(strTmp, 0x0, sizeof(strTmp));
			QSDK_Get_Str(p1, strTmp, 1);
			lwm2m_rd_temp_param.remain_length = Ql_atoi(strTmp);
			RIL_LwM2M_DEBUG(DBG_Buffer,"[lwm2m_param->remain_length] %d\r\n", lwm2m_rd_temp_param.remain_length);
			return RIL_ATRSP_CONTINUE;
		}
	}

	if (lwm2m_rd_temp_param.actual_length != 0) {
		if (g_LWM2M_RECV_DATA_MODE == LWM2M_DATA_FORMAT_TEXT) {
			//Ql_strncpy(lwm2m_recv_param->buffer,line,lwm2m_rd_temp_param.actual_length);
			Ql_memcpy(lwm2m_recv_param->buffer, line,
					lwm2m_rd_temp_param.actual_length);
		} else if (g_LWM2M_RECV_DATA_MODE == LWM2M_DATA_FORMAT_HEX) {
			Ql_strncpy((char*)lwm2m_recv_param->buffer, line,
					lwm2m_rd_temp_param.actual_length * 2);
		} RIL_LwM2M_DEBUG(DBG_Buffer,"[lwm2m_param->buffer] %s\r\n",lwm2m_recv_param->buffer);

		lwm2m_recv_param->actual_length = lwm2m_rd_temp_param.actual_length;
		lwm2m_recv_param->remain_length = lwm2m_rd_temp_param.remain_length;

		lwm2m_rd_temp_param.actual_length = 0;
		lwm2m_rd_temp_param.remain_length = 0;
		return RIL_ATRSP_CONTINUE;
	}
	head = Ql_RIL_FindLine(line, len, "OK");
	if (head) {
		return RIL_ATRSP_SUCCESS;
	}
	head = Ql_RIL_FindLine(line, len, "ERROR");
	if (head) {
		return RIL_ATRSP_FAILED;
	}
	head = Ql_RIL_FindString(line, len, "+CME ERROR:"); //fail
	if (head) {
		return RIL_ATRSP_FAILED;
	}
	head = Ql_RIL_FindString(line, len, "+CMS ERROR:"); //fail
	if (head) {
		return RIL_ATRSP_FAILED;
	}
	return RIL_ATRSP_CONTINUE; //continue wait
}

static s32 ATResponse_Close_Handler(char* line, u32 len, void* userData) {
	RIL_LwM2M_DEBUG(DBG_Buffer,"[ATResponse_Handler] %s\r\n", (u8*)line);

	if (Ql_RIL_FindLine(line, len, "CLOSE OK")) {
		return RIL_ATRSP_SUCCESS;
	} else if (Ql_RIL_FindLine(line, len, "ERROR")) {
		return RIL_ATRSP_FAILED;
	} else if (Ql_RIL_FindString(line, len, "+CME ERROR")) {
		return RIL_ATRSP_FAILED;
	} else if (Ql_RIL_FindString(line, len, "+CMS ERROR:")) {
		return RIL_ATRSP_FAILED;
	} else if (Ql_RIL_FindString(line, len, "SEND FAIL")) {
		return RIL_ATRSP_FAILED;
	}

	return RIL_ATRSP_CONTINUE; //continue wait
}

static s32 ATResponse_Delete_Handler(char* line, u32 len, void* userData) {
	RIL_LwM2M_DEBUG(DBG_Buffer,"[ATResponse_Handler] %s\r\n", (u8*)line);

	if (Ql_RIL_FindLine(line, len, "OK")) {
		return RIL_ATRSP_SUCCESS;
	} else if (Ql_RIL_FindLine(line, len, "ERROR")) {
		return RIL_ATRSP_FAILED;
	} else if (Ql_RIL_FindString(line, len, "+CME ERROR")) {
		return RIL_ATRSP_FAILED;
	} else if (Ql_RIL_FindString(line, len, "+CMS ERROR:")) {
		return RIL_ATRSP_FAILED;
	}

	return RIL_ATRSP_CONTINUE; //continue wait
}

/********************************************RIL API********************************************/
s32 RIL_QLwM2M_Serv(u8* ip_addr, u32 port) {
	s32 ret = RIL_AT_SUCCESS;
	char strAT[200];

	Ql_memset(strAT, 0, sizeof(strAT));
	Ql_sprintf(strAT, "AT+QLWSERV=\"%s\",%d\n", ip_addr, port);
	ret = Ql_RIL_SendATCmd(strAT, Ql_strlen(strAT), ATResponse_Handler, NULL,
			0);
	RIL_LwM2M_DEBUG(DBG_Buffer,"<-- Send AT:%s, ret = %d -->\r\n",strAT,ret);
	return ret;
}

s32 RIL_QLwM2M_Conf(u8* endpoint) {
	s32 ret = RIL_AT_SUCCESS;
	char strAT[200];

	Ql_memset(strAT, 0, sizeof(strAT));
	Ql_sprintf(strAT, "AT+QLWCONF=\"%s\"\n", endpoint);
	ret = Ql_RIL_SendATCmd(strAT, Ql_strlen(strAT), ATResponse_Handler, NULL,
			0);
	RIL_LwM2M_DEBUG(DBG_Buffer,"<-- Send AT:%s, ret = %d -->\r\n",strAT, ret);
	return ret;
}

s32 RIL_QLwM2M_Addobj(u32 obj_id, u8 ins_id, u8 res_num, u8* res_id) {
	s32 ret = RIL_AT_SUCCESS;
	char strAT[200];

	Ql_memset(strAT, 0, sizeof(strAT));
	if (NULL == res_id) {
		Ql_sprintf(strAT, "AT+QLWADDOBJ=%d,%d\n", obj_id, ins_id);
	} else {
		Ql_sprintf(strAT, "AT+QLWADDOBJ=%d,%d,%d,\"%s\"\n", obj_id, ins_id,
				res_num, res_id);

	}
	ret = Ql_RIL_SendATCmd(strAT, Ql_strlen(strAT), ATResponse_Handler, NULL,
			0);
	RIL_LwM2M_DEBUG(DBG_Buffer,"<--Send AT:%s, ret = %d -->\r\n",strAT, ret);
	return ret;

}

s32 RIL_QLwM2M_Delobj(u8 obj_id) {
	s32 ret = RIL_AT_SUCCESS;
	char strAT[200];

	Ql_memset(strAT, 0, sizeof(strAT));

	Ql_sprintf(strAT, "AT+QLWDELOBJ=%d\n", obj_id);

	ret = Ql_RIL_SendATCmd(strAT, Ql_strlen(strAT), ATResponse_Handler, NULL,
			0);
	RIL_LwM2M_DEBUG(DBG_Buffer,"<--Send AT:%s, ret = %d -->\r\n",strAT, ret);
	return ret;

}

s32 RIL_QLwM2M_Open(Enum_Lwm2m_Access_Mode lwm2m_access_mode) {
	s32 ret = RIL_AT_SUCCESS;
	char strAT[200];

	Ql_memset(strAT, 0, sizeof(strAT));
	Ql_sprintf(strAT, "AT+QLWOPEN=%d\n", lwm2m_access_mode);
	ret = Ql_RIL_SendATCmd(strAT, Ql_strlen(strAT), ATResponse_Handler, NULL,
			0);
	RIL_LwM2M_DEBUG(DBG_Buffer,"<-- Send AT:%s, ret = %d -->\r\n",strAT, ret);
	return ret;

}

s32 RIL_QLwM2M_Update(void) {
	s32 ret = RIL_AT_SUCCESS;
	char strAT[200];

	Ql_memset(strAT, 0, sizeof(strAT));
	Ql_sprintf(strAT, "AT+QLWUPDATE");
	ret = Ql_RIL_SendATCmd(strAT, Ql_strlen(strAT), ATResponse_Update_Handler,
			NULL, 0);
	RIL_LwM2M_DEBUG(DBG_Buffer,"<-- Send AT:%s, ret = %d -->\r\n",strAT, ret);
	return ret;

}

s32 RIL_QLwM2M_Cfg(Enum_Lwm2m_Data_Format send_format,
		Enum_Lwm2m_Data_Format recv_format) {
	s32 ret = RIL_AT_SUCCESS;
	char strAT[200];

	Ql_memset(strAT, 0, sizeof(strAT));
	Ql_sprintf(strAT, "AT+QLWCFG=\"dataformat\",%d,%d\n", send_format,
			recv_format);
	ret = Ql_RIL_SendATCmd(strAT, Ql_strlen(strAT), ATResponse_Handler, NULL,
			0);
	if (ret == RIL_AT_SUCCESS) {
		g_LWM2M_RECV_DATA_MODE = recv_format;

	} RIL_LwM2M_DEBUG(DBG_Buffer,"<-- Send AT:%s, ret = %d -->\r\n",strAT, ret);
	return ret;
}

s32 RIL_QLwM2M_Send(ST_Lwm2m_Send_Param_t *lwm2m_send_param_t) {
	s32 ret = RIL_AT_SUCCESS;
	char strAT[1024 + 100];
	extern bool lwm2m_send_con_result;

	Ql_memset(strAT, 0, sizeof(strAT));
	if (NULL == lwm2m_send_param_t->buffer) {
		return RIL_AT_INVALID_PARAM;
	}

	if (LWM2M_SEND_MODE_NON == lwm2m_send_param_t->lwm2m_send_mode) {
		Ql_sprintf(strAT, "AT+QLWDATASEND=%d,%d,%d,%d,%s,%s\n",
				lwm2m_send_param_t->obj_id, lwm2m_send_param_t->ins_id,
				lwm2m_send_param_t->res_id, lwm2m_send_param_t->send_length,
				lwm2m_send_param_t->buffer, "0x0000");
		ret = Ql_RIL_SendATCmd(strAT, Ql_strlen(strAT), ATResponse_Handler,
				NULL, 0);
		lwm2m_send_con_result = 0;
	} else if (LWM2M_SEND_MODE_CON == lwm2m_send_param_t->lwm2m_send_mode) {
		Ql_sprintf(strAT, "AT+QLWDATASEND=%d,%d,%d,%d,%s,%s\n",
				lwm2m_send_param_t->obj_id, lwm2m_send_param_t->ins_id,
				lwm2m_send_param_t->res_id, lwm2m_send_param_t->send_length,
				lwm2m_send_param_t->buffer, "0x0100");
		ret = Ql_RIL_SendATCmd(strAT, Ql_strlen(strAT), ATResponse_Send_Handler,
				NULL, 0);
		lwm2m_send_con_result = 1;
	}

	RIL_LwM2M_DEBUG(DBG_Buffer,"<-- Send AT:%s, ret = %d -->\r\n",strAT, ret);
	return ret;
}

s32 RIL_QLwM2M_RD(u32 rd_length, u32* actual_length, u32* remain_length, u8* data_buffer) {
	s32 ret = RIL_AT_SUCCESS;
	char strAT[200];
	LwM2M_Recv_Param Lwm2m_recv_param;

	if (rd_length == 0 || data_buffer == NULL) {
		return RIL_AT_INVALID_PARAM;
	}
	Lwm2m_recv_param.prefix = (u8*)"+QLWRD:";
	Lwm2m_recv_param.actual_length = 0;
	Lwm2m_recv_param.buffer = (u8*) Ql_MEM_Alloc(
			sizeof(u8) * LWM2M_RECV_BUFFER_LENGTH);
	if (Lwm2m_recv_param.buffer == NULL) {
		return RIL_AT_FAILED;
	}
	Ql_memset(Lwm2m_recv_param.buffer, 0, LWM2M_RECV_BUFFER_LENGTH);

	Ql_memset(strAT, 0, sizeof(strAT));
	Ql_sprintf(strAT, "AT+QLWRD=%d\n", rd_length);
	ret = Ql_RIL_SendATCmd(strAT, Ql_strlen(strAT), ATResponse_Recv_Handler,
			&Lwm2m_recv_param, 0);
	if (ret == RIL_AT_SUCCESS) {
		*actual_length = Lwm2m_recv_param.actual_length;
		*remain_length = Lwm2m_recv_param.remain_length;
		Ql_memcpy((char*)data_buffer, Lwm2m_recv_param.buffer, Ql_strlen((char*)Lwm2m_recv_param.buffer));
	}
	Ql_MEM_Free(Lwm2m_recv_param.buffer);
	Lwm2m_recv_param.buffer = NULL;
	RIL_LwM2M_DEBUG(DBG_Buffer,"<-- Send AT:%s, ret = %d -->\r\n",strAT, ret);
	return ret;
}

s32 RIL_QLwM2M_Close(void) {
	s32 ret = RIL_AT_SUCCESS;
	char strAT[200];

	Ql_memset(strAT, 0, sizeof(strAT));
	Ql_sprintf(strAT, "AT+QLWCLOSE\n");
	ret = Ql_RIL_SendATCmd(strAT, Ql_strlen(strAT), ATResponse_Close_Handler,
			NULL, 0);
	RIL_LwM2M_DEBUG(DBG_Buffer,"<-- Send AT:%s, ret = %d -->\r\n",strAT, ret);
	return ret;
}

s32 RIL_QLwM2M_Delete(void) {
	s32 ret = RIL_AT_SUCCESS;
	char strAT[200];

	Ql_memset(strAT, 0, sizeof(strAT));
	Ql_sprintf(strAT, "AT+QLWDEL\n");
	ret = Ql_RIL_SendATCmd(strAT, Ql_strlen(strAT), ATResponse_Delete_Handler,
			NULL, 0);
	RIL_LwM2M_DEBUG(DBG_Buffer,"<-- Send AT:%s, ret = %d -->\r\n",strAT, ret);
	return ret;
}

#endif  //__OCPU_RIL_SUPPORT__
