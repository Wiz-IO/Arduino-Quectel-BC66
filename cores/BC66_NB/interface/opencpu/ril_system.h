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
 *   ril_system.h 
 *
 * Project:
 * --------
 *   OpenCPU
 *
 * Description:
 * ------------
 *   The file is for OpenCPU RIL sytem definitions and APIs.
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
#ifndef __RIL_SYSTEM_H__
#define __RIL_SYSTEM_H__



/*****************************************************************
* Function:     RIL_GetIMEI 
* 
* Description:
*               Retrieves the IMEI number of module.
*
* Parameters:       
*               imei:
*                   [Out] buffer to store the imei number. The length 
*                         of buffer should be at least 15-byte.
* Return:        
*                RIL_AT_SUCCESS,send AT successfully.
*                RIL_AT_FAILED, send AT failed.
*                RIL_AT_TIMEOUT,send AT timeout.
*                RIL_AT_BUSY,   sending AT.
*                RIL_AT_INVALID_PARAM, invalid input parameter.
*                RIL_AT_UNINITIALIZED, RIL is not ready, need to wait for MSG_ID_RIL_READY
*                                      and then call Ql_RIL_Initialize to initialize RIL.
*****************************************************************/
s32 RIL_GetIMEI(char* imei);


/*****************************************************************
* Function:     QSDK_Get_Str 
* 
* Description:
*               This function get strings based on the location of comma.
* Parameters:
*               None.
* Return:        
*               
*
*eg:src_string="GPRMC,235945.799,V,,,,,0.00,0.00,050180,,,N"
*index =1 ,dest_string="235945.799"; return TRUE
*index =,return FALSE
*****************************************************************/
bool QSDK_Get_Str(char *src_string,  char *dest_string, unsigned char index);

u32 open_param_parse_cmd(const char *cmd_string, const char *param_buffer, char *param_list[], u32 param_max_num);
u32 open_onenet_push_param_parse_cmd(const char *cmd_string, u32 length, const char *param_buffer, char *param_list[], u32 param_max_num);

u32 open_lwm2m_param_parse_cmd(const char *cmd_string, const char *param_buffer, char *param_list[], u32 param_max_num);
u32 open_socket_rd_param_parse_cmd(const char *cmd_string, const char *param_buffer, char *param_list[], u32 param_max_num);
u32 open_socket_push_param_parse_cmd(const char *cmd_string, const char *param_buffer, char *param_list[], u32 param_max_num);
char* Qstr_seacher_with( const char* line, u32 cmd_buf_len, const char* prefix );


#endif  //__RIL_SYSTEM_H__

