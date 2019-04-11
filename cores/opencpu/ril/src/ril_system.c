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
#include "ril_lwm2m.h"

#include <string.h>

char *wiz_strtok(char *s, const char *delim);
char *wiz_strsep(char **stringp, const char *delim);

#ifdef __OCPU_RIL_SUPPORT__ 


static s32 ATRsp_IMEI_Handler(char* line, u32 len, void* param)
{
    char* pHead = NULL;
    pHead = Ql_RIL_FindLine(line, len, "OK"); // find <CR><LF>OK<CR><LF>, <CR>OK<CR>��<LF>OK<LF>
    if (pHead)
    {  
        return RIL_ATRSP_SUCCESS;
    }

    pHead = Ql_RIL_FindLine(line, len, "ERROR");// find <CR><LF>ERROR<CR><LF>, <CR>ERROR<CR>��<LF>ERROR<LF>
    if (pHead)
    {  
        return RIL_ATRSP_FAILED;
    } 

    pHead = Ql_RIL_FindString(line, len, "+CME ERROR:");//fail
    if (pHead)
    {
        return RIL_ATRSP_FAILED;
    }
	pHead = Ql_RIL_FindString(line, len, "+CGSN:");//fail
    if (pHead)
    {
        char* p1 = NULL;
        char* p2 = NULL;
		
        p1 = Ql_strstr(pHead, ":");
        p2 = Ql_strstr(p1 + 1, "\r\n");
        if (p1 && p2)
        {
            Ql_memcpy((char*)param, p1 + 2, p2 - p1 - 2);
        }
    }
    return RIL_ATRSP_CONTINUE; //continue wait
}

s32 RIL_GetIMEI(char* imei)
{
    char strAT[] = "AT+CGSN=1\n";
    if (NULL == imei)
    {
        return RIL_AT_INVALID_PARAM;
    }
    return Ql_RIL_SendATCmd(strAT, Ql_strlen(strAT), ATRsp_IMEI_Handler,(void*)imei, 0);
}

s32 RIL_QNbiotEvent_Enable(u32 event)
{
    char strAT[] = "AT+QNBIOTEVENT=1,1\n";
    if (PSM_EVENT != event)
    {
        return RIL_AT_INVALID_PARAM;
    }
    return Ql_RIL_SendATCmd(strAT, Ql_strlen(strAT), NULL,NULL, 0);
}


s32 RIL_QNbiotEvent_Disable(u32 event)
{
    char strAT[] = "AT+QNBIOTEVENT=0,1\n";
    if (PSM_EVENT != event)
    {
        return RIL_AT_INVALID_PARAM;
    }
    return Ql_RIL_SendATCmd(strAT, Ql_strlen(strAT), NULL,NULL, 0);
}


//[20180828][Buffer Mode][The custom interface handles data with character 00]
u32 open_socket_rd_param_parse_cmd(const char *cmd_string, u32 recv_length, const char *param_buffer, char *param_list[], u32 param_max_num)
{
    /*----------------------------------------------------------------*/
    /* Local Variables                                                */
    /*----------------------------------------------------------------*/
    int i;
    u32 param_num = 0;
    char* p = (char *)cmd_string, *p2, *ptmp;
    char* param = (char *)param_buffer;
    u32 param_len, len;
	u32 temp_length = 0;
	extern bool recv_data_format;
	char* p_end = p + (recv_length - 2);  // two means last '\r\n'

    /*----------------------------------------------------------------*/
    /* Code Body                                                      */
    /*----------------------------------------------------------------*/
    p = strtok(p, "\r\n");
    while (p != NULL && param_num < param_max_num) 
	{
        // remove leading blanks & tabs
        while (*p == ' ' || *p == '\t')
		{
            p++;
        }
        // remove double quotation
        if (*p == '\"')
		{
            p2 = strchr(++p, '"');
            if (p2 == NULL)
			{
                break;
            }
            len = p2 - p;
            strncpy(param, p, len);
            *(param + len) = '\0';
            p = p2;
            wiz_strsep(&p, ",");
        } else 
        {
			if ( param_num == 2 )  //process json format data
			{
				if ( recv_data_format == 0 ) // text
				{
					Ql_memcpy(param, p, temp_length);
					*(param + temp_length) = '\0';
				}
				else if ( recv_data_format == 1 ) // hex
				{
					Ql_memcpy(param, p, temp_length*2);
					*(param + temp_length*2) = '\0';
				}
				param_list[param_num++] = param;
				return param_num;
			}
			else
			{
				ptmp = Ql_strchr(p, ',');
				if ( ptmp == NULL )  // Last
				{
					Ql_memcpy(param, p, (p_end - p));
					*(param + (p_end - p)) = '\0';
					param_list[param_num++] = param;
					return param_num;
				}
				Ql_memcpy(param, p, (ptmp - p));
				*(param + (ptmp - p)) = '\0';
				p = ptmp + 1;
			}
			
			param_len = strlen(param);
			for (i = param_len - 1; i >= 0; i--)
			{
	            if (*(param + i) == ' ' || *(param + i) == '\t')
				{
	                *(param + i) = '\0';
	            }
				else
	            {
	                break;
	            }
        	}
        }
        // add to param_list
		param_list[param_num++] = param;
	   	if ( param_num == 1 )
	   	{
			temp_length = Ql_atoi(param_list[0]);
		}
		
        param = param + strlen(param) + 1;
    }
    return param_num;
}


//src_string="GPRMC,235945.799,V,,,,,0.00,0.00,050180,,,N" index =1  ����TRUE ,dest_string="235945.799"; index =3������FALSE
bool QSDK_Get_Str(char *src_string,  char *dest_string, unsigned char index)
{
    u32 SentenceCnt = 0;
    u32 ItemSum = 0;
    u32 ItemLen = 0, Idx = 0;
    u32 len = 0;
    unsigned int i = 0;
    
    if (src_string ==NULL)
    {
        return FALSE;
    }
    len = Ql_strlen(src_string);
	for ( i = 0; i < len; i++)
	{
		if (*(src_string + i) == ',')
		{
			ItemLen = i - ItemSum - SentenceCnt;
			ItemSum  += ItemLen;
            if (index == SentenceCnt)
            {
                if (ItemLen == 0)
                {
                    return FALSE;
                }
		        else
                {
                    Ql_memcpy(dest_string, src_string + Idx, ItemLen);
                    *(dest_string + ItemLen) = '\0';
                    return TRUE;
                }
            }
			SentenceCnt++; 	 
			Idx = i + 1;
		}		
	}
    if (index == SentenceCnt && (len - Idx) != 0)
    {
        Ql_memcpy(dest_string, src_string + Idx, len - Idx);
        *(dest_string + len) = '\0';
        return TRUE;
    }
    else 
    {
        return FALSE;
    }
}

u32 open_socket_push_json_param_parse_cmd(const char *cmd_string, u32 recv_length, const char *param_buffer, char *param_list[], u32 param_max_num)
{
	/*----------------------------------------------------------------*/
	/* Local Variables												  */
	/*----------------------------------------------------------------*/
	int i;
	u32 param_num = 0;
	char* p = (char *)cmd_string, *p2, *ptmp;
	char* param = (char *)param_buffer;
	u32 param_len, len;
	u32 temp_length = 0;
	extern bool recv_data_format;
	char* p3 = p + (recv_length - 2);  // two means last '\r\n'
	
	/*----------------------------------------------------------------*/
	/* Code Body													  */
	/*----------------------------------------------------------------*/
	p = strtok(p, "\r\n");
	while (p != NULL && param_num < param_max_num)
	{
		// remove leading blanks & tabs
		while (*p == ' ' || *p == '\t')
		{
			p++;
		}
		
		if ( param_num == 3 && (recv_data_format == 0) )  // Customer parse JSON format data
		{
			Ql_memcpy(param, p, temp_length);
			*(param + temp_length) = '\0';
			param_list[param_num++] = param;
			return param_num;
		}
		else
		{	
			ptmp = Ql_strchr(p, ',');
			if ( ptmp == NULL )  //process last parameter
			{
				if ( param_num == 2 )  // this case is buffer mode recv data URC
				{
					Ql_memcpy(param, p, p3 - p);
					*(param + (p3 - p)) = '\0';
				}
				else if ( param_num == 3 )
				{
					if ( recv_data_format == 1 )  //hex
					{
						Ql_memcpy(param, p, (temp_length * 2));
						*(param + temp_length*2) = '\0';
					}
					else if ( recv_data_format == 0 ) //text
					{
						Ql_memcpy(param, p, temp_length);
						*(param + temp_length) = '\0';
					}
				}
				param_list[param_num++] = param;
				return param_num;
			}
			Ql_memcpy(param, p, ptmp - p);
			*(param + (ptmp - p)) = '\0';
			p = ptmp + 1;

			// remove post blanks & tabs
		    param_len = strlen(param);
		    for ( i = param_len - 1; i >= 0; i-- )
			{
		        if (*(param + i) == ' ' || *(param + i) == '\t')
				{
		            *(param + i) = '\0';
		        } 
				else
				{
		            break;
		        }
		    }
		}

		// add to param_list
		param_list[param_num++] = param;
		if ( param_num == 3 )          // hex/text need to use this parameter
		{
			temp_length = Ql_atoi(param_list[2]);
		}
		param = param + Ql_strlen(param) + 1;
	}

	return param_num;
}

//[Push Mode][The custom interface handles data with character 00]
u32 open_socket_push_param_parse_cmd(const char *cmd_string, const char *param_buffer, char *param_list[], u32 param_max_num)
{
	/*----------------------------------------------------------------*/
	/* Local Variables												  */
	/*----------------------------------------------------------------*/
	int i;
	u32 param_num = 0;
	char* p = (char *)cmd_string, *p2, *ptmp;
	char* param = (char *)param_buffer;
	u32 param_len, len;
	u32 temp_length = 0;
	extern bool recv_data_format;
	
	/*----------------------------------------------------------------*/
	/* Code Body													  */
	/*----------------------------------------------------------------*/
	p = strtok(p, "\r\n");
	while (p != NULL && *p != '\0' && param_num < param_max_num) {
		// remove leading blanks & tabs
		while (*p == ' ' || *p == '\t') {
			p++;
		}
		// remove double quotation
		if (*p == '\"') {
			p2 = strchr(++p, '"');
			if (p2 == NULL) {
				break;
			}
			len = p2 - p;
			strncpy(param, p, len);
			*(param + len) = '\0';
			p = p2;
			wiz_strsep(&p, ",");
		} else {
			ptmp = wiz_strsep(&p, ",");
			if (!ptmp)
			{
				break;
			}
			if ( param_num == 3 && (recv_data_format == 0) )
			{
				Ql_memcpy(param, ptmp, temp_length);
			}
			else
			{
				strcpy(param, ptmp);
			}
			// remove post blanks & tabs 
			if ( param_num == 3 && (recv_data_format == 0) )
			{
				param_len = temp_length;
			}
			else
			{
				param_len = strlen(param);
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
		if ( param_num == 3 && (recv_data_format == 0) )
		{
			param_list[param_num++] = param;
		}
		else
		{
			param_list[param_num++] = param;
			if ( param_num == 3 && (recv_data_format == 0) )
			{
				temp_length = Ql_atoi(param_list[2]);
			}
		}
		param = param + strlen(param) + 1;
	}

	return param_num;
}


//[The custom interface handles data with character 00]
u32 open_lwm2m_param_parse_cmd(const char *cmd_string, const char *param_buffer, char *param_list[], u32 param_max_num)
{
    /*----------------------------------------------------------------*/
    /* Local Variables                                                */
    /*----------------------------------------------------------------*/
    int i;
    u32 param_num = 0;
    char* p = (char *)cmd_string, *p2, *ptmp;
    char* param = (char *)param_buffer;
    u32 param_len, len;
	u32 temp_length = 0;
	extern bool g_LWM2M_RECV_DATA_MODE;
	
    /*----------------------------------------------------------------*/
    /* Code Body                                                      */
    /*----------------------------------------------------------------*/
    p = strtok(p, "\r\n");
    while (p != NULL && *p != '\0' && param_num < param_max_num) {
        // remove leading blanks & tabs
        while (*p == ' ' || *p == '\t') {
            p++;
        }
        // remove double quotation
        if (*p == '\"') {
            p2 = strchr(++p, '"');
            if (p2 == NULL) {
                break;
            }
            len = p2 - p;
            strncpy(param, p, len);
            *(param + len) = '\0';
            p = p2;
            wiz_strsep(&p, ",");
        } else {
            ptmp = wiz_strsep(&p, ",");
            if (!ptmp)
            {
                break;
            }
			if ( param_num == 4 && (g_LWM2M_RECV_DATA_MODE == LWM2M_DATA_FORMAT_TEXT) )
			{
				Ql_memcpy(param, ptmp, temp_length);
			}
			else
			{
            	strcpy(param, ptmp);
			}
            // remove post blanks & tabs 
            if ( param_num == 4 && (g_LWM2M_RECV_DATA_MODE == LWM2M_DATA_FORMAT_TEXT) )
            {
				param_len = temp_length;
            }
			else
			{
            	param_len = strlen(param);
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
		if ( param_num == 4 && (g_LWM2M_RECV_DATA_MODE == LWM2M_DATA_FORMAT_TEXT) )
		{
			param_list[param_num++] = param;
		}
		else
		{
        	param_list[param_num++] = param;
			if ( param_num == 4 && (g_LWM2M_RECV_DATA_MODE == LWM2M_DATA_FORMAT_TEXT) )
			{
				temp_length = Ql_atoi(param_list[3]);
			}
		}
        param = param + strlen(param) + 1;
    }

    return param_num;
}


char* Qstr_seacher_with( const char* line, u32 cmd_buf_len, const char* prefix )
{
	if ( line == NULL || prefix == NULL || prefix == NULL || (int)cmd_buf_len < 0 )
	{
		return NULL;
	}

	char* temp_src = (char*)line;
	int prefix_len = Ql_strlen(prefix);
	int last_possible = cmd_buf_len - prefix_len + 1;

	for ( int i = 0; i < last_possible; i++ ) 
	{
		if ( *temp_src == *prefix) 
		{
			if ( Ql_memcmp(temp_src, prefix, prefix_len) == 0 ) 
			{
				return temp_src;
			}
		}
		temp_src++;
	}
	return NULL;
}


u32 open_param_parse_cmd(const char *cmd_string, const char *param_buffer, char *param_list[], u32 param_max_num)
{
    /*----------------------------------------------------------------*/
    /* Local Variables                                                */
    /*----------------------------------------------------------------*/
    int i;
    u32 param_num = 0;
    char *p = (char *)cmd_string, *p2, *ptmp;
    char *param = (char *)param_buffer;
    u32 param_len, len;

    /*----------------------------------------------------------------*/
    /* Code Body                                                      */
    /*----------------------------------------------------------------*/
    p = strtok(p, "\r\n"); 
    while (p != NULL && *p != '\0' && param_num < param_max_num) {
        // remove leading blanks & tabs
        while (*p == ' ' || *p == '\t') {
            p++;
        }
        // remove double quotation
        if (*p == '\"') {
            p2 = strchr(++p, '"');
            if (p2 == NULL) {
                break;
            }
            len = p2 - p;
            strncpy(param, p, len);
            *(param + len) = '\0';
            p = p2;
            wiz_strsep(&p, ",");
        } else {
            ptmp = wiz_strsep(&p, ","); 
            if (!ptmp)
            {
                break;
            }
            strcpy(param, ptmp);
            // remove post blanks & tabs
            param_len = strlen(param);
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

        param = param + strlen(param) + 1;
    }

    return param_num;
}


#endif  //__OCPU_RIL_SUPPORT__

