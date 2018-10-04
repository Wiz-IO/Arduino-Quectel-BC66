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
#include "ql_type.h"
#include "ril.h"
#include "ril_util.h"
#include "ql_system.h"
#include "ql_common.h"

#ifdef __OCPU_RIL_SUPPORT__

/************************************************************************/
/* Definition for URC receive task id.                                  */
/************************************************************************/
#define URC_RCV_TASK_ID  0 /*main_task_id*/
#define RECV_BUFFER_LENGTH  256
u8 recv_buffer[RECV_BUFFER_LENGTH];

/************************************************************************/
/* Declarations for URC handler.                                        */
/************************************************************************/
static void OnURCHandler_Network(const char* strURC, void* reserved);
static void OnURCHandler_SIM(const char* strURC, void* reserved);
static void OnURCHandler_CFUN(const char* strURC, void* reserved);

//static void OnURCHandler_InitStat(const char* strURC, void* reserved);

static void OnURCHandler_RECV_DATA(const char* strURC, void* reserved);

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
const static ST_URC_HDLENTRY m_SysURCHdlEntry[] = {

//Network status unsolicited response
//{"\r\n+CREG:",                                OnURCHandler_Network},
		{ "\r\n+CEREG:", OnURCHandler_Network },

		//SIM card unsolicited response
		{ "\r\n+CPIN:", OnURCHandler_SIM },

		//CFUN unsolicited response
		{ "\r\n+CFUN:", OnURCHandler_CFUN }, { "\r\n+QSONMI", OnURCHandler_RECV_DATA },

};

/****************************************************/
/* Definitions for AT URCs and the handler          */
/****************************************************/
const static ST_URC_HDLENTRY m_AtURCHdlEntry[] = {
//HTTP unsolicited response
// {"\r\n+QBTSCAN:",                             OnURCHandler_BTScan},

		};

//src_string="GPRMC,235945.799,V,,,,,0.00,0.00,050180,,,N" index =1  ¡¤¦Ì??TRUE ,dest_string="235945.799"; index =3¡ê?¡¤¦Ì??FALSE
char QSDK_Get_Str(char *src_string, char *dest_string, unsigned char index) {
	char SentenceCnt = 0;
	char ItemSum = 0;
	char ItemLen = 0, Idx = 0;
	char len = 0;
	unsigned int i = 0;

	if (src_string == NULL) {
		return FALSE;
	}
	len = Ql_strlen(src_string);
	for (i = 0; i < len; i++) {
		if (*(src_string + i) == ',') {
			ItemLen = i - ItemSum - SentenceCnt;
			ItemSum += ItemLen;
			if (index == SentenceCnt) {
				if (ItemLen == 0) {
					return FALSE;
				} else {
					Ql_memcpy(dest_string, src_string + Idx, ItemLen);
					*(dest_string + ItemLen) = '\0';
					return TRUE;
				}
			}
			SentenceCnt++;
			Idx = i + 1;
		}
	}
	if (index == SentenceCnt && (len - Idx) != 0) {
		Ql_memcpy(dest_string, src_string + Idx, len - Idx);
		*(dest_string + len) = '\0';
		return TRUE;
	} else {
		return FALSE;
	}
}
static void OnURCHandler_RECV_DATA(const char* strURC, void* reserved) {
	char* p1 = NULL;
	char* p2 = NULL;
	//s32 len;

	p1 = Ql_strstr(strURC, "+QSONMI=");
	p2 = Ql_strstr(p1, "\r\n");
	*p2 = '\0';
	if (p1) {
		Ql_memset(recv_buffer, 0x0, RECV_BUFFER_LENGTH);
		QSDK_Get_Str(p1, (char*)recv_buffer, 2);
		Ql_OS_SendMessage(URC_RCV_TASK_ID, MSG_ID_URC_INDICATION, URC_SOCKET_RECV_DATA, (u32)recv_buffer);

	}

}

static void OnURCHandler_SIM(const char* strURC, void* reserved) {
	char* p1 = NULL;
	char* p2 = NULL;
	char strTmp[20];
	s32 len;
	extern s32 RIL_SIM_GetSimStateByName(char* simStat, u32 len);

	Ql_memset(strTmp, 0x0, sizeof(strTmp));
	len = Ql_sprintf(strTmp, "\r\n+CPIN: ");
	if (Ql_StrPrefixMatch(strURC, strTmp)) {
		p1 = Ql_strstr(strURC, "\r\n+CPIN: ");
		p1 += len;
		p2 = Ql_strstr(p1, "\r\n");
		if (p1 && p2) {
			u32 cpinStat;
			Ql_memset(strTmp, 0x0, sizeof(strTmp));
			Ql_memcpy(strTmp, p1, p2 - p1);
			cpinStat = (u32) RIL_SIM_GetSimStateByName(strTmp, p2 - p1);
			Ql_OS_SendMessage(URC_RCV_TASK_ID, MSG_ID_URC_INDICATION, URC_SIM_CARD_STATE_IND, cpinStat);
		}
	}
}
static void OnURCHandler_Network(const char* strURC, void* reserved) {
	char* p1 = NULL;
	char* p2 = NULL;
	char strTmp[10];

	if (Ql_StrPrefixMatch(strURC, "\r\n+CREG: ")) {
		u32 nwStat;
		p1 = Ql_strstr(strURC, "\r\n+CREG: ");
		p1 += Ql_strlen("\r\n+CREG: ");
		if (*(p1 + 1) == 0x2C)          //Active query network status without reporting URCS
				{
			return;
		}
		p2 = Ql_strstr(p1, "\r\n");
		if (p1 && p2) {
			Ql_memset(strTmp, 0x0, sizeof(strTmp));
			Ql_memcpy(strTmp, p1, p2 - p1);
			nwStat = Ql_atoi(strTmp);
			Ql_OS_SendMessage(URC_RCV_TASK_ID, MSG_ID_URC_INDICATION, URC_GSM_NW_STATE_IND, nwStat);
		}
	} else if (Ql_StrPrefixMatch(strURC, "\r\n+CGREG: ")) {
		u32 nwStat;
		p1 = Ql_strstr(strURC, "\r\n+CGREG: ");
		p1 += Ql_strlen("\r\n+CGREG: ");
		if (*(p1 + 1) == 0x2C)          //Active query network status without reporting URCS
				{
			return;
		}
		p2 = Ql_strstr(p1, "\r\n");
		if (p1 && p2) {
			Ql_memset(strTmp, 0x0, sizeof(strTmp));
			Ql_memcpy(strTmp, p1, p2 - p1);
			nwStat = Ql_atoi(strTmp);
			Ql_OS_SendMessage(URC_RCV_TASK_ID, MSG_ID_URC_INDICATION, URC_GPRS_NW_STATE_IND, nwStat);
		}
	} else if (Ql_StrPrefixMatch(strURC, "\r\n+CEREG: ")) {
		u32 nwStat;
		p1 = Ql_strstr(strURC, "\r\n+CEREG: ");
		p1 += Ql_strlen("\r\n+CEREG: ");
		if (*(p1 + 1) == 0x2C)          //Active query network status without reporting URCS
				{
			return;
		}
		p2 = Ql_strstr(p1, "\r\n");
		if (p1 && p2) {
			Ql_memset(strTmp, 0x0, sizeof(strTmp));
			Ql_memcpy(strTmp, p1, p2 - p1);
			nwStat = Ql_atoi(strTmp);
			Ql_OS_SendMessage(URC_RCV_TASK_ID, MSG_ID_URC_INDICATION, URC_EGPRS_NW_STATE_IND, nwStat);
		}
	}
}

#if 0
static void OnURCHandler_InitStat(const char* strURC, void* reserved) {
	u32 sysInitStat = SYS_STATE_START;

	if (Ql_strstr(strURC, "\r\nCall Ready\r\n") != NULL) {
		sysInitStat = SYS_STATE_PHBOK;
	} else if (Ql_strstr(strURC, "\r\nSMS Ready\r\n") != NULL) {
		sysInitStat = SYS_STATE_SMSOK;
	}
	Ql_OS_SendMessage(URC_RCV_TASK_ID, MSG_ID_URC_INDICATION, URC_SYS_INIT_STATE_IND, sysInitStat);
}
#endif

static void OnURCHandler_CFUN(const char* strURC, void* reserved) {
	char* p1 = NULL;
	char* p2 = NULL;
	char strTmp[10];
	s32 len;
	u32 cfun;

	len = Ql_strlen("\r\n+CFUN: ");
	p1 = Ql_strstr(strURC, "\r\n+CFUN: ");
	p1 += len;
	p2 = Ql_strstr(p1, "\r\n");
	if (p1 && p2) {
		Ql_memset(strTmp, 0x0, sizeof(strTmp));
		Ql_memcpy(strTmp, p1, 1);
		cfun = Ql_atoi(strTmp);
		Ql_OS_SendMessage(URC_RCV_TASK_ID, MSG_ID_URC_INDICATION, URC_CFUN_STATE_IND, cfun);
	}
}

static void OnURCHandler_Undefined(const char* strURC, void* reserved) {
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
void OnURCHandler(const char* strURC, void* reserved) {
	s32 i;

	if (NULL == strURC) {
		return;
	}

	// For system URCs
	for (i = 0; i < NUM_ELEMS(m_SysURCHdlEntry); i++) {
		if (Ql_strstr(strURC, m_SysURCHdlEntry[i].keyword)) {
			m_SysURCHdlEntry[i].handler(strURC, reserved);
			return;
		}
	}

	// For AT URCs
	for (i = 0; i < NUM_ELEMS(m_AtURCHdlEntry); i++) {
		if (Ql_strstr(strURC, m_AtURCHdlEntry[i].keyword)) {
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
s32 Ql_RIL_IsURCStr(const char* strRsp) {
	s32 i;
	for (i = 0; i < NUM_ELEMS(m_SysURCHdlEntry); i++) {
		if (Ql_strstr(strRsp, m_SysURCHdlEntry[i].keyword)) {
			return 1;
		}
	}
	for (i = 0; i < NUM_ELEMS(m_AtURCHdlEntry); i++) {
		if (Ql_strstr(strRsp, m_AtURCHdlEntry[i].keyword)) {
			return 1;
		}
	}
	return 0;
}

#endif  // __OCPU_RIL_SUPPORT__
