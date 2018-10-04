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
#include "ril_system.h"
#include "ql_stdlib.h"
#include "ql_trace.h"
#include "ql_error.h"
#include "ql_system.h"
#include "ql_trace.h"
#include "ql_common.h"
#include "ql_uart.h"
#include "ril_socket.h"
#ifdef __OCPU_RIL_SUPPORT__

#define RIL_SOCKET_DEBUG_ENABLE 0
#if RIL_SOCKET_DEBUG_ENABLE > 0
#define RIL_SOCKET_DEBUG_PORT  UART_PORT2
static char DBG_Buffer[1024];
#define RIL_SOCKET_DEBUG(BUF,...)  QL_TRACE_LOG(RIL_SOCKET_DEBUG_PORT,BUF,1024,__VA_ARGS__)
#else
#define RIL_SOCKET_DEBUG(BUF,...) 
#endif

#define RECV_BUFFER_LENGTH   1200//512
volatile bool recv_data_format = FALSE;
volatile bool send_data_format = FALSE;

NV_DATA_FORMAT TEMP_DATA_FORMAT = { 0, 0 };

static s32 ATResponse_Handler(char* line, u32 len, void* userData) {

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

static s32 ATRsp_Soc_Qiopen_Handler(char* line, u32 len, void* userdata) {
	ST_RIL_SocketParam *ril_socket_param_t = (ST_RIL_SocketParam *) userdata;
	char *head = Ql_RIL_FindString(line, len,
			(char*) ril_socket_param_t->prefix); //continue wait

	if (head) {
		char strTmp[10];
		char* p1 = NULL;
		char* p2 = NULL;
		Ql_memset(strTmp, 0x0, sizeof(strTmp));
		p1 = Ql_strstr(head, ":");
		p1 += 1;
		p2 = Ql_strstr(p1, "\r\n");
		*p2 = '\0';
		QSDK_Get_Str(p1, strTmp, 0);
		ril_socket_param_t->connectID = Ql_atoi(strTmp); //connextid

		Ql_memset(strTmp, 0x0, sizeof(strTmp));
		QSDK_Get_Str(p1, strTmp, 1);
		ril_socket_param_t->errorno = Ql_atoi(strTmp);  //errorno

		return RIL_ATRSP_SUCCESS;
	}
	head = Ql_RIL_FindLine(line, len, "OK");
	if (head) {
		return RIL_ATRSP_CONTINUE;
	}
	head = Ql_RIL_FindLine(line, len, "ERROR");
	if (head) {
		return RIL_ATRSP_FAILED;
	}
	head = Ql_RIL_FindString(line, len, "+CME ERROR:");  //fail
	if (head) {
		return RIL_ATRSP_FAILED;
	}
	head = Ql_RIL_FindString(line, len, "+CMS ERROR:");  //fail
	if (head) {
		return RIL_ATRSP_FAILED;
	}
	return RIL_ATRSP_CONTINUE; //continue wait
}

static s32 ATRsp_Soc_Qisend_Handler(char* line, u32 len, void* userData) {

	if (Ql_RIL_FindLine(line, len, "SEND OK")) {
		return RIL_ATRSP_SUCCESS;
	} else if (Ql_RIL_FindLine(line, len, "ERROR")) {
		return RIL_ATRSP_FAILED;
	} else if (Ql_RIL_FindString(line, len, "+CME ERROR")) {
		return RIL_ATRSP_FAILED;
	} else if (Ql_RIL_FindString(line, len, "SEND FAIL")) {
		return RIL_ATRSP_FAILED;
	}

	return RIL_ATRSP_CONTINUE; //continue wait
}

static s32 ATRsp_Soc_Qird_Handler(char* line, u32 len, void* userdata) {
	/*----------------------------------------------------------------*/
	/* Local Variables                                                */
	/*----------------------------------------------------------------*/
	ST_RIL_SocketParam *socket_param = (ST_RIL_SocketParam *) userdata;
	char *head = Ql_RIL_FindString(line, len, (char*) socket_param->prefix); //continue wait
	char* param_buffer = (char*) Ql_MEM_Alloc(1200);
	char* param_list[20];

	/*----------------------------------------------------------------*/
	/* Code Body													  */
	/*----------------------------------------------------------------*/
	if (head) {
//char strTmp[10];
		char* p1 = NULL;

		p1 = Ql_strstr(head, ":");
		p1 += 1;
		if (p1) {
			//[20180829][Randy]there need to read data format from nv
			extern NV_DATA_FORMAT TEMP_DATA_FORMAT;
			Ql_SecureData_Read(1, (u8*) &TEMP_DATA_FORMAT,
					sizeof(NV_DATA_FORMAT));	//[20180829][Randy]
			RIL_SOCKET_DEBUG(DBG_Buffer, "TEMP_DATA_FORMAT.temp_send_data_format = %d TEMP_DATA_FORMAT.temp_recv_data_format = %d\r\n", TEMP_DATA_FORMAT.temp_send_data_format, TEMP_DATA_FORMAT.temp_recv_data_format);
			recv_data_format = TEMP_DATA_FORMAT.temp_recv_data_format;

			u32 param_num = open_socket_rd_param_parse_cmd(p1, param_buffer,
					param_list, 20);
			socket_param->length = Ql_atoi(param_list[0]);
			RIL_SOCKET_DEBUG(DBG_Buffer,"param_num = %d [socket_param->length] %d\r\n", param_num, socket_param->length);
			if (param_num == 3) {
				socket_param->remain_length = Ql_atoi(param_list[1]);
				RIL_SOCKET_DEBUG(DBG_Buffer,"[socket_param->length] %d\r\n", socket_param->remain_length);
				char* recv_buffer = param_list[2];
				RIL_SOCKET_DEBUG(DBG_Buffer,"recv_buf = %s\r\n", recv_buffer);

				socket_param->buffer = (u8*) Ql_MEM_Alloc(1200);
				Ql_memset(socket_param->buffer, 0x0, 1200);

				RIL_SOCKET_DEBUG(DBG_Buffer,"recv_data_format = %d \r\n", recv_data_format);
				if (recv_data_format == 0) {
					Ql_memcpy(socket_param->buffer, recv_buffer,
							socket_param->length);
					RIL_SOCKET_DEBUG(DBG_Buffer,"111recv_data_format = %d [socket_param->buffer] %s\r\n",recv_data_format, socket_param->buffer);
				} else if (recv_data_format == 1) {
					Ql_strncpy((char*) socket_param->buffer, recv_buffer,
							socket_param->length * 2);
					RIL_SOCKET_DEBUG(DBG_Buffer,"222recv_data_format = %d [socket_param->buffer] %s\r\n",recv_data_format, socket_param->buffer);
				}
			}
		}
		return RIL_ATRSP_SUCCESS;
	}
	head = Ql_RIL_FindLine(line, len, "OK");
	if (head) {
		return RIL_ATRSP_CONTINUE;
	}
	head = Ql_RIL_FindLine(line, len, "ERROR");
	if (head) {
		return RIL_ATRSP_FAILED;
	}
	head = Ql_RIL_FindString(line, len, "+CME ERROR:");	//fail
	if (head) {
		return RIL_ATRSP_FAILED;
	}
	head = Ql_RIL_FindString(line, len, "+CMS ERROR:");	//fail
	if (head) {
		return RIL_ATRSP_FAILED;
	}
	return RIL_ATRSP_CONTINUE; //continue wait
}

static s32 ATRsp_Soc_Qiclose_Handler(char* line, u32 len, void* userData) {

	if (Ql_RIL_FindLine(line, len, "CLOSE OK")) {
		return RIL_ATRSP_SUCCESS;
	} else if (Ql_RIL_FindLine(line, len, "ERROR")) {
		return RIL_ATRSP_FAILED;
	} else if (Ql_RIL_FindString(line, len, "+CME ERROR")) {
		return RIL_ATRSP_FAILED;
	} else if (Ql_RIL_FindString(line, len, "SEND FAIL")) {
		return RIL_ATRSP_FAILED;
	}

	return RIL_ATRSP_CONTINUE; //continue wait
}

s32 RIL_SOC_QIOPEN(ST_Socket_Param_t* socket_param_t) {
	s32 ret = RIL_AT_SUCCESS;
	char strAT[200];
	ST_RIL_SocketParam ril_socket_param;

	Ql_memset(strAT, 0, sizeof(strAT));
	Ql_sprintf(strAT, "AT+QICFG=\"%s\",1\n", "viewmode");
	ret = Ql_RIL_SendATCmd(strAT, Ql_strlen(strAT), NULL, NULL, 0);
	RIL_SOCKET_DEBUG(DBG_Buffer,"<-- Send AT:%s, ret = %d -->\r\n",strAT, ret);
	if (RIL_AT_SUCCESS != ret) {
		return ret;
	}

	Ql_memset(strAT, 0, sizeof(strAT));
	Ql_sprintf(strAT, "AT+QICFG=\"%s\",1\n", "showlength");
	ret = Ql_RIL_SendATCmd(strAT, Ql_strlen(strAT), NULL, NULL, 0);
	RIL_SOCKET_DEBUG(DBG_Buffer,"<-- Send AT:%s, ret = %d -->\r\n",strAT, ret);
	if (RIL_AT_SUCCESS != ret) {
		return ret;
	}

	Ql_memset(strAT, 0, sizeof(strAT));
	if (socket_param_t->service_type == SOCKET_SERVICE_TYPE_TCP) {
		Ql_sprintf(strAT, "AT+QIOPEN=%d,%d,\"%s\",\"%s\",%d,%d,%d,%d\n",
				socket_param_t->contextID, socket_param_t->connectID, "TCP",
				socket_param_t->address, socket_param_t->remote_port,
				socket_param_t->local_port, socket_param_t->access_mode,
				socket_param_t->protocol_type);
	} else if (socket_param_t->service_type == SOCKET_SERVICE_TYPE_UDP) {
		Ql_sprintf(strAT, "AT+QIOPEN=%d,%d,\"%s\",\"%s\",%d,%d,%d,%d\n",
				socket_param_t->contextID, socket_param_t->connectID, "UDP",
				socket_param_t->address, socket_param_t->remote_port,
				socket_param_t->local_port, socket_param_t->access_mode,
				socket_param_t->protocol_type);
	}
	ril_socket_param.prefix = (u8*) "+QIOPEN:";
	ril_socket_param.errorno = 255;
	ril_socket_param.connectID = -1;

	ret = Ql_RIL_SendATCmd(strAT, Ql_strlen(strAT), ATRsp_Soc_Qiopen_Handler,
			&ril_socket_param, 0);
	RIL_SOCKET_DEBUG(DBG_Buffer,"<-- Send AT:%s, ret = %d -->\r\n",strAT, ret);
	if (RIL_AT_SUCCESS != ret) {
		RIL_SOCKET_DEBUG(DBG_Buffer,"\r\n<-- send AT command failure -->\r\n");
		return ret;
	} else if (0 != ril_socket_param.errorno) // socket open failed!!!
			{
		RIL_SOCKET_DEBUG(DBG_Buffer,"\r\n<-- socket OPEN get failure(%d) -->\r\n", ril_socket_param.errorno);
		return (ril_socket_param.errorno);
	} else if (0 == ril_socket_param.errorno) {
		return (ril_socket_param.connectID);
	}
	return ret;

}

s32 RIL_SOC_QISEND(u8 connectID, u32 send_length, u8* send_buffer) {
	s32 ret = RIL_AT_SUCCESS;
	char strAT[2048];

	Ql_memset(strAT, 0, sizeof(strAT));
	Ql_sprintf(strAT, "AT+QISEND=%d,%d,%s\n", connectID, send_length,
			send_buffer);
	ret = Ql_RIL_SendATCmd(strAT, Ql_strlen(strAT), ATRsp_Soc_Qisend_Handler, 0,
			0);

	RIL_SOCKET_DEBUG(DBG_Buffer,"<--Send AT:%s, ret = %d -->\r\n",strAT, ret);
	return ret;
}

s32 RIL_SOC_QISENDEX(u8 connectID, u32 send_length, u8* send_hex_buffer) {
	s32 ret = RIL_AT_SUCCESS;
	char strAT[2048];

	Ql_memset(strAT, 0, sizeof(strAT));
	Ql_sprintf(strAT, "AT+QISENDEX=%d,%d,%s\n", connectID, send_length,
			send_hex_buffer);
	ret = Ql_RIL_SendATCmd(strAT, Ql_strlen(strAT), ATRsp_Soc_Qisend_Handler, 0,
			0);

	RIL_SOCKET_DEBUG(DBG_Buffer,"<--Send AT:%s, ret = %d -->\r\n",strAT, ret);
	return ret;
}

s32 RIL_SOC_QIRD(u8 connectID, u32 read_length, s32* recv_actual_length, s32* recv_remain_length, u8* recv_buffer) {
	s32 ret = RIL_AT_SUCCESS;
	char strAT[200];
	ST_RIL_SocketParam socket_Param;
	socket_Param.prefix = (u8*) "+QIRD:";
	socket_Param.buffer = (u8*) Ql_MEM_Alloc(sizeof(u8) * RECV_BUFFER_LENGTH);
	Ql_memset(strAT, 0, sizeof(strAT));
	socket_Param.length = 255;
	Ql_memset(socket_Param.buffer, 0, RECV_BUFFER_LENGTH);
	Ql_sprintf(strAT, "AT+QIRD=%d,%d\n", connectID, read_length);
	ret = Ql_RIL_SendATCmd(strAT, Ql_strlen(strAT), ATRsp_Soc_Qird_Handler, &socket_Param, 0);

	*recv_actual_length = socket_Param.length;
	*recv_remain_length = socket_Param.remain_length;
	//RIL_SOCKET_DEBUG(DBG_Buffer,"<--socket_Param.buffer:%s-->\r\n",socket_Param.buffer);
	if (socket_Param.buffer != NULL) {
		if (recv_data_format == 0) //text
				{
			Ql_memcpy(recv_buffer, socket_Param.buffer, *recv_actual_length);
		} else if (recv_data_format == 1) //hex
				{
			Ql_memcpy((char*) recv_buffer, socket_Param.buffer, Ql_strlen((char*)socket_Param.buffer));
		}
		Ql_MEM_Free(socket_Param.buffer);
		socket_Param.buffer = NULL;
	}
	RIL_SOCKET_DEBUG(DBG_Buffer,"<--Send AT:%s, ret = %d -->\r\n",strAT, ret);
	return ret;
}

s32 RIL_SOC_QISWTMD(u8 connectID, Enum_Socket_Access_Mode access_mode)

{
	s32 ret = RIL_AT_SUCCESS;
	char strAT[200];

	Ql_memset(strAT, 0, sizeof(strAT));
	Ql_sprintf(strAT, "AT+QISWTMD=%d,%d\n", connectID, access_mode);
	ret = Ql_RIL_SendATCmd(strAT, Ql_strlen(strAT), ATResponse_Handler, 0, 0);

	RIL_SOCKET_DEBUG(DBG_Buffer,"<--Send AT:%s, ret = %d -->\r\n",strAT, ret);
	return ret;
}

s32 RIL_SOC_QICFG_FORMAT(bool send_format, bool recv_format)

{
	s32 ret = RIL_AT_SUCCESS;
	char strAT[200];

	Ql_memset(strAT, 0, sizeof(strAT));
	Ql_sprintf(strAT, "AT+QICFG=\"dataformat\",%d,%d\n", send_format,
			recv_format);
	ret = Ql_RIL_SendATCmd(strAT, Ql_strlen(strAT), ATResponse_Handler, 0, 0);

	RIL_SOCKET_DEBUG(DBG_Buffer,"<--Send AT:%s, ret = %d -->\r\n",strAT, ret);
	return ret;
}

s32 RIL_SOC_QICLOSE(u8 connectID) {
	s32 ret = RIL_AT_SUCCESS;
	char strAT[200];

	Ql_memset(strAT, 0, sizeof(strAT));
	Ql_sprintf(strAT, "AT+QICLOSE=%d\n", connectID);
	ret = Ql_RIL_SendATCmd(strAT, Ql_strlen(strAT), ATRsp_Soc_Qiclose_Handler,
			0, 0);

	RIL_SOCKET_DEBUG(DBG_Buffer,"<--Send AT:%s, ret = %d -->\r\n",strAT, ret);
	return ret;
}

#endif  //__OCPU_RIL_SUPPORT__
