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
 *   ril_system.c 
 *
 * Project:
 * --------
 *   OpenCPU
 *
 * Description:
 * ------------
 *   The module defines the information, and APIs related to RIL.
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
#include "ril_system.h"
#include "ql_stdlib.h"
#include "ql_trace.h"
#include "ql_error.h"
#include "ql_system.h"
#include "ql_stdlib.h"
#include "ql_common.h"
#include "ql_uart.h"
#include "ql_type.h"
#include "ril_onenet.h"
#include "ril_lwm2m.h"
#include "ril_system.h"

#ifdef __OCPU_RIL_SUPPORT__ 

static s32 ATRsp_IMEI_Handler(char* line, u32 len, void* param) {
	char* pHead = NULL;
	pHead = Ql_RIL_FindLine(line, len, "OK"); // find <CR><LF>OK<CR><LF>, <CR>OK<CR>，<LF>OK<LF>
	if (pHead) {
		return RIL_ATRSP_SUCCESS;
	}

	pHead = Ql_RIL_FindLine(line, len, "ERROR"); // find <CR><LF>ERROR<CR><LF>, <CR>ERROR<CR>，<LF>ERROR<LF>
	if (pHead) {
		return RIL_ATRSP_FAILED;
	}

	pHead = Ql_RIL_FindString(line, len, "+CME ERROR:"); //fail
	if (pHead) {
		return RIL_ATRSP_FAILED;
	}
	pHead = Ql_RIL_FindString(line, len, "+CGSN:"); //fail
	if (pHead) {
		char* p1 = NULL;
		char* p2 = NULL;

		p1 = Ql_strstr(pHead, ":");
		p2 = Ql_strstr(p1 + 1, "\r\n");
		if (p1 && p2) {
			Ql_memcpy((char*) param, p1 + 2, p2 - p1 - 2);
		}
	}
	return RIL_ATRSP_CONTINUE; //continue wait
}

s32 RIL_GetIMEI(char* imei) {
	char strAT[] = "AT+CGSN=1\n";
	if (NULL == imei) {
		return RIL_AT_INVALID_PARAM;
	}
	return Ql_RIL_SendATCmd(strAT, Ql_strlen(strAT), ATRsp_IMEI_Handler,
			(void*) imei, 0);
}

//[20180828][Buffer Mode][The custom interface handles data with character 00]
u32 open_socket_rd_param_parse_cmd(const char *cmd_string,
		const char *param_buffer, char *param_list[], u32 param_max_num) {
	/*----------------------------------------------------------------*/
	/* Local Variables                                                */
	/*----------------------------------------------------------------*/
	int i;
	u32 param_num = 0;
	char* p = (char *) cmd_string, *p2, *ptmp;
	char* param = (char *) param_buffer;
	u32 param_len, len;
	u32 temp_length = 0;
	extern bool recv_data_format;

	/*----------------------------------------------------------------*/
	/* Code Body                                                      */
	/*----------------------------------------------------------------*/
	p = Ql_strtok(p, "\r\n");
	while (p != NULL && *p != '\0' && param_num < param_max_num) {
		// remove leading blanks & tabs
		while (*p == ' ' || *p == '\t') {
			p++;
		}
		// remove double quotation
		if (*p == '\"') {
			p2 = Ql_strchr(++p, '"');
			if (p2 == NULL) {
				break;
			}
			len = p2 - p;
			Ql_strncpy(param, p, len);
			*(param + len) = '\0';
			p = p2;
			Ql_strsep(&p, ",");
		} else {
			ptmp = Ql_strsep(&p, ",");
			if (!ptmp) {
				break;
			}
			if (param_num == 2 && (recv_data_format == 0)) {
				Ql_memcpy(param, ptmp, temp_length);
			} else {
				Ql_strcpy(param, ptmp);
			}
			// remove post blanks & tabs
			if (param_num == 2 && (recv_data_format == 0)) {
				param_len = temp_length;
			} else {
				param_len = Ql_strlen(param);
				for (i = param_len - 1; i >= 0; i--) {
					if (*(param + i) == ' ' || *(param + i) == '\t') {
						*(param + i) = '\0';
					} else {
						break;
					}
				}
			}
		}
		// add to param_list
		if (param_num == 2 && (recv_data_format == 0)) {
			param_list[param_num++] = param;
		} else {
			param_list[param_num++] = param;
			if (param_num == 1 && (recv_data_format == 0)) {
				temp_length = Ql_atoi(param_list[0]);
			}
		}
		param = param + Ql_strlen(param) + 1;
	}
	return param_num;
}

//src_string="GPRMC,235945.799,V,,,,,0.00,0.00,050180,,,N" index =1  返回TRUE ,dest_string="235945.799"; index =3，返回FALSE
bool QSDK_Get_Str(char *src_string, char *dest_string, unsigned char index) {
	u32 SentenceCnt = 0;
	u32 ItemSum = 0;
	u32 ItemLen = 0, Idx = 0;
	u32 len = 0;
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
//[20180829][Randy][Push Mode][The custom interface handles data with character 00]
u32 open_socket_push_param_parse_cmd(const char *cmd_string,
		const char *param_buffer, char *param_list[], u32 param_max_num) {
	/*----------------------------------------------------------------*/
	/* Local Variables												  */
	/*----------------------------------------------------------------*/
	int i;
	u32 param_num = 0;
	char* p = (char *) cmd_string, *p2, *ptmp;
	char* param = (char *) param_buffer;
	u32 param_len, len;
	u32 temp_length = 0;
	extern bool recv_data_format;

	/*----------------------------------------------------------------*/
	/* Code Body													  */
	/*----------------------------------------------------------------*/
	p = Ql_strtok(p, "\r\n");
	while (p != NULL && *p != '\0' && param_num < param_max_num) {
		// remove leading blanks & tabs
		while (*p == ' ' || *p == '\t') {
			p++;
		}
		// remove double quotation
		if (*p == '\"') {
			p2 = Ql_strchr(++p, '"');
			if (p2 == NULL) {
				break;
			}
			len = p2 - p;
			Ql_strncpy(param, p, len);
			*(param + len) = '\0';
			p = p2;
			Ql_strsep(&p, ",");
		} else {
			ptmp = Ql_strsep(&p, ",");
			if (!ptmp) {
				break;
			}
			if (param_num == 3 && (recv_data_format == 0)) {
				Ql_memcpy(param, ptmp, temp_length);
			} else {
				Ql_strcpy(param, ptmp);
			}
			// remove post blanks & tabs 
			if (param_num == 3 && (recv_data_format == 0)) {
				param_len = temp_length;
			} else {
				param_len = Ql_strlen(param);
				for (i = param_len - 1; i >= 0; i--) {
					if (*(param + i) == ' ' || *(param + i) == '\t') {
						*(param + i) = '\0';
					} else {
						break;
					}
				}
			}
		}
		// add to param_list
		if (param_num == 3 && (recv_data_format == 0)) {
			param_list[param_num++] = param;
		} else {
			param_list[param_num++] = param;
			if (param_num == 3 && (recv_data_format == 0)) {
				temp_length = Ql_atoi(param_list[2]);
			}
		}
		param = param + Ql_strlen(param) + 1;
	}

	return param_num;
}

//[20180821][Randy][The custom interface handles data with character 00]
u32 open_lwm2m_param_parse_cmd(const char *cmd_string, const char *param_buffer,
		char *param_list[], u32 param_max_num) {
	/*----------------------------------------------------------------*/
	/* Local Variables                                                */
	/*----------------------------------------------------------------*/
	int i;
	u32 param_num = 0;
	char* p = (char *) cmd_string, *p2, *ptmp;
	char* param = (char *) param_buffer;
	u32 param_len, len;
	u32 temp_length = 0;
	extern bool g_LWM2M_RECV_DATA_MODE;

	/*----------------------------------------------------------------*/
	/* Code Body                                                      */
	/*----------------------------------------------------------------*/
	p = Ql_strtok(p, "\r\n");
	while (p != NULL && *p != '\0' && param_num < param_max_num) {
		// remove leading blanks & tabs
		while (*p == ' ' || *p == '\t') {
			p++;
		}
		// remove double quotation
		if (*p == '\"') {
			p2 = Ql_strchr(++p, '"');
			if (p2 == NULL) {
				break;
			}
			len = p2 - p;
			Ql_strncpy(param, p, len);
			*(param + len) = '\0';
			p = p2;
			Ql_strsep(&p, ",");
		} else {
			ptmp = Ql_strsep(&p, ",");
			if (!ptmp) {
				break;
			}
			if (param_num == 4
					&& (g_LWM2M_RECV_DATA_MODE == LWM2M_DATA_FORMAT_TEXT)) {
				Ql_memcpy(param, ptmp, temp_length);
			} else {
				Ql_strcpy(param, ptmp);
			}
			// remove post blanks & tabs
			if (param_num == 4
					&& (g_LWM2M_RECV_DATA_MODE == LWM2M_DATA_FORMAT_TEXT)) {
				param_len = temp_length;
			} else {
				param_len = Ql_strlen(param);
				for (i = param_len - 1; i >= 0; i--) {
					if (*(param + i) == ' ' || *(param + i) == '\t') {
						*(param + i) = '\0';
					} else {
						break;
					}
				}
			}
		}
		// add to param_list
		if (param_num == 4
				&& (g_LWM2M_RECV_DATA_MODE == LWM2M_DATA_FORMAT_TEXT)) {
			param_list[param_num++] = param;
		} else {
			param_list[param_num++] = param;
			if (param_num == 4
					&& (g_LWM2M_RECV_DATA_MODE == LWM2M_DATA_FORMAT_TEXT)) {
				temp_length = Ql_atoi(param_list[3]);
			}
		}
		param = param + Ql_strlen(param) + 1;
	}

	return param_num;
}

//[20180829][Randy]新增查找指定字符的接口，来避免由于strstr导致的字符00截断
char* Qstr_seacher_with(const char* line, u32 cmd_buf_len, const char* prefix) {
	if (line == NULL || prefix == NULL || *prefix == '\0' || (int)cmd_buf_len < 0) {
		return NULL;
	}

	char* temp_src = (char*)line;
	int prefix_len = Ql_strlen(prefix);
	int last_possible = cmd_buf_len - prefix_len + 1;

	for (int i = 0; i < last_possible; i++) {
		if (*temp_src == *prefix) {
			if (Ql_memcmp(temp_src, prefix, prefix_len) == 0) {
				return temp_src;
			}
		}
		temp_src++;
	}
	return NULL;
}

//[20180829][Randy][The custom interface handles data with character 00]
u32 open_onenet_push_param_parse_cmd(const char *cmd_string, u32 length,
		const char *param_buffer, char *param_list[], u32 param_max_num) {
	/*----------------------------------------------------------------*/
	/* Local Variables                                                */
	/*----------------------------------------------------------------*/
	int i;
	u32 param_num = 0;
	char* p = (char *) cmd_string, *p2, *ptmp, *p3;
	char* param = (char *) param_buffer;
	u32 param_len, len;
	u32 temp_length = 0;
	extern bool g_ONENET_PUSH_RECV_MODE;

	/*----------------------------------------------------------------*/
	/* Code Body                                                      */
	/*----------------------------------------------------------------*/
	p3 = Qstr_seacher_with(p, length, "\r\n");

	while (p != NULL && param_num < param_max_num) {
		// remove leading blanks & tabs
		while (*p == ' ' || *p == '\t') {
			p++;
		}
		// remove double quotation
		if (*p == '\"') {
			p2 = Ql_strchr(++p, '"');
			if (p2 == NULL) {
				break;
			}
			len = p2 - p;
			Ql_strncpy(param, p, len);
			*(param + len) = '\0';
			p = p2;
			Ql_strsep(&p, ",");
		} else {
			ptmp = Qstr_seacher_with(p, length, ",");
			if (ptmp == NULL) //Last
			{
				Ql_memcpy(param, p, p3 - p);

				param_len = Ql_strlen(param);
				for (i = param_len - 1; i >= 0; i--) {
					if (*(param + i) == ' ' || *(param + i) == '\t') {
						*(param + i) = '\0';
					} else {
						break;
					}
				}

				param_list[param_num++] = param;
				return param_num;
			}

			length -= (ptmp - p + 1);
			if (ptmp) {
				if (param_num == 7
						&& (g_ONENET_PUSH_RECV_MODE == ONENET_RECV_MODE_TEXT)) {
					Ql_memcpy(param, p, temp_length);
					p = ptmp + 1;
				} else {
					int u = ptmp - p;
					Ql_memcpy(param, p, u);
					p = ptmp + 1;
				}
			} else {
				break;
			}

			// remove post blanks & tabs
			if (param_num == 7
					&& (g_ONENET_PUSH_RECV_MODE == ONENET_RECV_MODE_TEXT)) {
				param_len = temp_length;
			} else {
				param_len = Ql_strlen(param);
				for (i = param_len - 1; i >= 0; i--) {
					if (*(param + i) == ' ' || *(param + i) == '\t') {
						*(param + i) = '\0';
					} else {
						break;
					}
				}
			}
		}
		// add to param_list
		if (param_num == 7
				&& (g_ONENET_PUSH_RECV_MODE == ONENET_RECV_MODE_TEXT)) {
			param_list[param_num++] = param;
			param = param + temp_length + 1;
		} else {
			param_list[param_num++] = param;
			if (param_num == 7
					&& (g_ONENET_PUSH_RECV_MODE == ONENET_RECV_MODE_TEXT)) {
				temp_length = Ql_atoi(param_list[6]);
			}
			param = param + Ql_strlen(param) + 1;
		}

	}

	return param_num;
}

u32 open_param_parse_cmd(const char *cmd_string, const char *param_buffer,
		char *param_list[], u32 param_max_num) {
	/*----------------------------------------------------------------*/
	/* Local Variables                                                */
	/*----------------------------------------------------------------*/
	int i;
	u32 param_num = 0;
	char *p = (char *) cmd_string, *p2, *ptmp;
	char *param = (char *) param_buffer;
	u32 param_len, len;

	/*----------------------------------------------------------------*/
	/* Code Body                                                      */
	/*----------------------------------------------------------------*/
	p = Ql_strtok(p, "\r\n");
	while (p != NULL && *p != '\0' && param_num < param_max_num) {
		// remove leading blanks & tabs
		while (*p == ' ' || *p == '\t') {
			p++;
		}
		// remove double quotation
		if (*p == '\"') {
			p2 = Ql_strchr(++p, '"');
			if (p2 == NULL) {
				break;
			}
			len = p2 - p;
			Ql_strncpy(param, p, len);
			*(param + len) = '\0';
			p = p2;
			Ql_strsep(&p, ",");
		} else {
			ptmp = Ql_strsep(&p, ",");
			if (!ptmp) {
				break;
			}
			Ql_strcpy(param, ptmp);
			// remove post blanks & tabs
			param_len = Ql_strlen(param);
			for (i = param_len - 1; i >= 0; i--) {
				if (*(param + i) == ' ' || *(param + i) == '\t') {
					*(param + i) = '\0';
				} else {
					break;
				}
			}
		}
		// add to param_list
		param_list[param_num++] = param;

		param = param + Ql_strlen(param) + 1;
	}

	return param_num;
}

#endif  //__OCPU_RIL_SUPPORT__
