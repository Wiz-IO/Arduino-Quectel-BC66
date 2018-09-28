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
 *   ril_socket.h 
 *
 * Project:
 * --------
 *   OpenCPU
 *
 * Description:
 * ------------
 *   The file declares some API functions, which are related to socket
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
#ifndef __RIL_SOCKET_H__
#define __RIL_SOCKET_H__
#include "ql_type.h"





/******************************************************************************
* Function:     RIL_SOC_Create
*  
* Description:
*               This function create socket.
*
* Parameters:    
*               domin:
*                   [in] 
*                    1 :IPv4
*                    2 :IPv6
*               type:
*                   [in]
*
*                   1:TCP
*                   2:UDP
*                   3:RAW
*                protocol:
*                    [in]
*
*                   1:IP
*                   2:ICMP
* Return:  
*                The socket ID, or other Error Codes. 
*                RIL_AT_FAILED, send AT failed.
*                RIL_AT_TIMEOUT,send AT timeout.
*                RIL_AT_BUSY,   sending AT.
*                RIL_AT_INVALID_PARAM, invalid input parameter.
*                RIL_AT_UNINITIALIZED, RIL is not ready, need to wait for MSG_ID_RIL_READY
*                                      and then call Ql_RIL_Initialize to initialize RIL.
******************************************************************************/
s32  RIL_QSOC_Create(u8 domin,u8 type, u8 protocol);



/******************************************************************************
* Function:     RIL_QSOCON
*  
* Description:
*               ThThis function connects to TCP server. The server
*               is specified by an IP address and a port number.
*
* Parameters:    
*               soc_id:
*                   [in] 
*               socket id
*               port:
*                   [in]
*                ip:
*                    [in]
* Return:  
*                RIL_AT_SUCCESS,send AT successfully.
*                RIL_AT_FAILED, send AT failed.
*                RIL_AT_TIMEOUT,send AT timeout.
*                RIL_AT_BUSY,   sending AT.
*                RIL_AT_INVALID_PARAM, invalid input parameter.
*                RIL_AT_UNINITIALIZED, RIL is not ready, need to wait for MSG_ID_RIL_READY
*                                      and then call Ql_RIL_Initialize to initialize RIL.
******************************************************************************/

s32 RIL_QSOC_CONN(u8 soc_id, u32 port,u8* ip); 


/******************************************************************************
* Function:     RIL_QSOSEND
*  
* Description:
*                 The function sends data to a connected TCP socket..
*
* Parameters:    
*               soc_id:
*                   [in] 
*              socket id
*        send_length:
*                   [in]
*                send data length 
*        send_buffer:
*                    [in]
*                send data
* Return:  
*                RIL_AT_SUCCESS,send AT successfully.
*                RIL_AT_FAILED, send AT failed.
*                RIL_AT_TIMEOUT,send AT timeout.
*                RIL_AT_BUSY,   sending AT.
*                RIL_AT_INVALID_PARAM, invalid input parameter.
*                RIL_AT_UNINITIALIZED, RIL is not ready, need to wait for MSG_ID_RIL_READY
*                                      and then call Ql_RIL_Initialize to initialize RIL.
******************************************************************************/

s32 RIL_QSOC_SEND(u8 soc_id, u32 send_length,u8* send_buffer); 


/******************************************************************************
* Function:     RIL_QSOCL
*  
* Description:
*                 This function closes a socket.
*
* Parameters:    
*               soc_id:
*                   [in] 
*              socket id
* Return:  
*                RIL_AT_SUCCESS,send AT successfully.
*                RIL_AT_FAILED, send AT failed.
*                RIL_AT_TIMEOUT,send AT timeout.
*                RIL_AT_BUSY,   sending AT.
*                RIL_AT_INVALID_PARAM, invalid input parameter.
*                RIL_AT_UNINITIALIZED, RIL is not ready, need to wait for MSG_ID_RIL_READY
*                                      and then call Ql_RIL_Initialize to initialize RIL.
******************************************************************************/
s32 RIL_QSOC_CLOSE(u8 soc_id);


#endif // __RIL_NETWORK_H__
