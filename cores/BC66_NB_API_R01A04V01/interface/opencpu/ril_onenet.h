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
 *   ril_onenet.h 
 *
 * Project:
 * --------
 *   OpenCPU
 *
 * Description:
 * ------------
 *   The file declares some API functions, which are related to onenet
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
#ifndef __RIL_OneNet_H__
#define __RIL_OneNet_H__
#include "ql_type.h"

typedef enum
{
    ONENET_ACCESS_MODE_DIRECT = 0,   //Direct push mode   
    ONENET_ACCESS_MODE_BUFFER        // Buffer access mode 
}Enum_ONENET_Access_Mode;

typedef enum
{
    ONENET_RECV_MODE_HEX = 0,   //hex string
    ONENET_RECV_MODE_TEXT        //text string
}Enum_ONENET_Recv_Mode;

typedef enum
{
    ONENET_BS_MODE_DISABLE = 0,   //Disable boostrap.
    ONENET_BS_MODE_ENABLE         //Enable boostrap.default mode
}Enum_ONENET_Bs_Mode;



typedef enum
{
    ONENET_OBJ_FLAG_DISABLE= 0,     //Update without objects list.
    ONENET_OBJ_FLAG_ENABLE          //Update with objects list. 
}Enum_ONENET_Obj_Flag;


typedef enum
{
	ONENET_OBSERVE_RESULT_1= 1,     //2.05 Content, indicate the correct result.
    ONENET_OBSERVE_RESULT_2,        //2.04 Content, indicate the correct result.
    ONENET_OBSERVE_RESULT_11 = 11,  //4.00 Bad Request. 
    ONENET_OBSERVE_RESULT_12 ,      //4.01 Unauthorized.
    ONENET_OBSERVE_RESULT_13,       //4.04 Not Found.
    ONENET_OBSERVE_RESULT_14,       //4.05 Method Not Allowed.
    ONENET_OBSERVE_RESULT_15        //4.06 Not Acceptable.
}Enum_ONENET_Observe_Result;


typedef enum
{
    ONENET_VALUE_TYPE_STRING= 1,     
    ONENET_VALUE_TYPE_OPAQUE,        
    ONENET_VALUE_TYPE_INTEGER,      
    ONENET_VALUE_TYPE_FLOAT,       
    ONENET_VALUE_TYPE_BOOLEAN      
}Enum_ONENET_Value_Type;


typedef enum
{
    EVENT_BOOTSTRAP_START= 1,     
    EVENT_BOOTSTRAP_SUCCESS,        
    EVENT_BOOTSTRAP_FAILED,      
    EVENT_CONNECT_SUCCESS,       
    EVENT_CONNECT_FAILED,
    EVENT_REG_SUCCESS,  
    EVENT_REG_FAILED,  
    EVENT_REG_TIMEOUT,  
    EVENT_LIFETIME_TIMEOUT,  
    EVENT_STATUS_HALT,  
    EVENT_UPDATE_SUCCESS,  
    EVENT_UPDATE_FAILED,  
    EVENT_UPDATE_TIMEOUT, 
    EVENT_UPDATE_NEED, 
    EVENT_DEREG_DONE,//15
    EVENT_RESPONSE_FAILED = 20,
    EVENT_RESPONSE_SUCCESS,
    EVENT_NOTIFY_FAILED =25, 
    EVENT_NOTIFY_SUCCESS,//26
    EVENT_END 
}Enum_ONENET_Event_Evtid;


typedef struct{
 u32 ref;         // Instance ID of OneNET communication suite..
 u32 ins_id;      // Object identifier. If the object ID is not existed, the module will return error..
 u32 obj_id;       //Instance count.           
 u32 ins_count;   //Length of data sent.
 u8* insbitmap;   //Instance bitmap. A string which should be marked with double quotation marks  For example,
                  //if <insCount>=4, and the <insBitmap>="1101", it means the instance ID 0, 1, 3 will be registered, and the instance ID 2 will not be registered.
 u32 attrcount;   //Attribute count, which indicate the count of readable and/or writeable resources.
 u32 actcount;    //Action count, which indicate the count of executable resources.
}ST_ONENET_Obj_Param_t;

typedef struct{
u32 ref;    //Instance ID of OneNET communication suite.
u32 msgid;  //The message identifier, which comes from the URC "+ MIPLOBSERVE:".
Enum_ONENET_Observe_Result  obderve_result;// The result of observe.
}ST_ONENET_Observe_Param_t;


typedef struct{
 Enum_ONENET_Access_Mode  onenet_access_mode;         
 Enum_ONENET_Recv_Mode    onenet_recv_mode;      
 Enum_ONENET_Bs_Mode      onenet_bs_mode;      
 u8* ip;   
 u32 port;  
}ST_ONENET_Config_Param_t;


typedef struct{
 u32 ref;		 // Instance ID of OneNET communication suite..
 u32 msgid;      //The message identifier, which comes from the URC "+ MIPLDISCOVER:"
 u32 result;     //The result of discover operate,
 u32 length;     //The length of <valuestring>.
 u8* value_string; //A string which includes the attributes of the object and should be marked with double quotation marks. 
}ST_ONENET_Discover_Rsp_Param_t;

typedef struct{
 u32 ref;		 // Instance ID of OneNET communication suite..
 u32 msgid;      //The message identifier, which comes from the URC "+MIPLDISCOVER:"
 u32 objid;      //Object identifier.
 u32 insid;      //The instance identifier, which comes from the URC "+MIPLOBSERVE :"
 u32 resid;      //The resource identifier, which comes from the URC "+MIPLOBSERVE :".
 Enum_ONENET_Value_Type value_type; //The value type.
 u32 len;         //The value length.
 u8* value;
 u32 index;      //The index number of the data.
 u32 flag;       //The message indication. The range is 0-2. 
 u32 ackid;      //Integer type, range: 0-65535
 u32 result;     //Integer type. Just for Read Response
}ST_ONENET_Notify_Param_t;


typedef struct{
u32 actual_length;
u32 remain_length;
u8* buffer;
u8* prefix;
u8  errno;

}ST_RIL_Onenet_Param;


/******************************************************************************
* Function:     RIL_QONENET_Create
*  
* Description:
*               Create a OneNET Communication Suite Instance
*
* Parameters:    
*               void.
* Return:  
*                The socket ID, or other Error Codes. 
*                RIL_AT_FAILED, send AT failed.
*                RIL_AT_TIMEOUT,send AT timeout.
*                RIL_AT_BUSY,   sending AT.
*                RIL_AT_INVALID_PARAM, invalid input parameter.
*                RIL_AT_UNINITIALIZED, RIL is not ready, need to wait for MSG_ID_RIL_READY
*                                      and then call Ql_RIL_Initialize to initialize RIL.
******************************************************************************/
s32 RIL_QONENET_Create(void);



/******************************************************************************
* Function:     RIL_QONENET_Delete
*  
* Description:
*                 Delete a OneNET Communication Suite Instance
*
* Parameters:    
*               ref:
*                  Instance ID of OneNET communication suite.
* Return:  
*                The socket ID, or other Error Codes. 
*                RIL_AT_FAILED, send AT failed.
*                RIL_AT_TIMEOUT,send AT timeout.
*                RIL_AT_BUSY,   sending AT.
*                RIL_AT_INVALID_PARAM, invalid input parameter.
*                RIL_AT_UNINITIALIZED, RIL is not ready, need to wait for MSG_ID_RIL_READY
*                                      and then call Ql_RIL_Initialize to initialize RIL.
******************************************************************************/
s32 RIL_QONENET_Delete(u32 ref);



/******************************************************************************
* Function:     RIL_QONENET_Addobj
*  
* Description:
*               Delete a OneNET Communication Suite Instance
*
* Parameters:    
*                 onenet_obj_param_t
*                 [in] 
*                  object param,please refer to ST_ONENET_Obj_Param_t.
* Return:  
*                The socket ID, or other Error Codes. 
*                RIL_AT_FAILED, send AT failed.
*                RIL_AT_TIMEOUT,send AT timeout.
*                RIL_AT_BUSY,   sending AT.
*                RIL_AT_INVALID_PARAM, invalid input parameter.
*                RIL_AT_UNINITIALIZED, RIL is not ready, need to wait for MSG_ID_RIL_READY
*                                      and then call Ql_RIL_Initialize to initialize RIL.
******************************************************************************/
s32 RIL_QONENET_Addobj(ST_ONENET_Obj_Param_t *onenet_obj_param_t);



/******************************************************************************
* Function:     RIL_QONENET_Delobj
*  
* Description:
*                   Delete a LWM2M Object
*
* Parameters: 
*                ref:
*                  [in]
*                  Instance ID of OneNET communication suite.
*               obj_id:
*                   [in] 
*                   Object identifier. If the object ID is not existed, the module will return error.
* Return:  
*                The socket ID, or other Error Codes. 
*                RIL_AT_FAILED, send AT failed.
*                RIL_AT_TIMEOUT,send AT timeout.
*                RIL_AT_BUSY,   sending AT.
*                RIL_AT_INVALID_PARAM, invalid input parameter.
*                RIL_AT_UNINITIALIZED, RIL is not ready, need to wait for MSG_ID_RIL_READY
*                                      and then call Ql_RIL_Initialize to initialize RIL.
******************************************************************************/
s32 RIL_QONENET_Delobj(u32 ref,u32 obj_id);



/******************************************************************************
* Function:     RIL_QONENET_Open
*  
* Description:
*                  Send Register Request
*
* Parameters: 
*                ref:
*                  [in]
*                  Instance ID of OneNET communication suite.
*               lifetime:
*                   [in] 
*                   Lifetime, unit is second. Range is 0 or 15~268435455; "0" means that lifetime is 3600 seconds.
* Return:  
*                The socket ID, or other Error Codes. 
*                RIL_AT_FAILED, send AT failed.
*                RIL_AT_TIMEOUT,send AT timeout.
*                RIL_AT_BUSY,   sending AT.
*                RIL_AT_INVALID_PARAM, invalid input parameter.
*                RIL_AT_UNINITIALIZED, RIL is not ready, need to wait for MSG_ID_RIL_READY
*                                      and then call Ql_RIL_Initialize to initialize RIL.
******************************************************************************/
s32 RIL_QONENET_Open(u32 ref,u32 lifetime );



/******************************************************************************
* Function:     RIL_QONENET_Observer_Rsp
*  
* Description:
*                   Respond the Discover Request
*
* Parameters:    
*                onenet_observe_param_t:
*                  [in]
*                lwm2m send param,please refer to ST_ONENET_Observe_Param_t.
*
*                The socket ID, or other Error Codes. 
*                RIL_AT_FAILED, send AT failed.
*                RIL_AT_TIMEOUT,send AT timeout.
*                RIL_AT_BUSY,   sending AT.
*                RIL_AT_INVALID_PARAM, invalid input parameter.
*                RIL_AT_UNINITIALIZED, RIL is not ready, need to wait for MSG_ID_RIL_READY
*                                      and then call Ql_RIL_Initialize to initialize RIL.
******************************************************************************/
s32 RIL_QONENET_Observer_Rsp(ST_ONENET_Observe_Param_t* onenet_observe_param_t);




/******************************************************************************
* Function:     RIL_QLwM2M_Cfg
*  
* Description:
*               Configure Optional Parameters
*
* Parameters:    
*                 onenet_config_param_t
*                 [in] 
*                 config param,please refer to ST_ONENET_Config_Param_t.
*
*                 server_config_flag
*                 [in] 
*                 TRUE:  the user need to config ip and port 
*                 FALSE: ignore ip and port
*
* Return:  
*                The socket ID, or other Error Codes. 
*                RIL_AT_FAILED, send AT failed.
*                RIL_AT_TIMEOUT,send AT timeout.
*                RIL_AT_BUSY,   sending AT.
*                RIL_AT_INVALID_PARAM, invalid input parameter.
*                RIL_AT_UNINITIALIZED, RIL is not ready, need to wait for MSG_ID_RIL_READY
*                                      and then call Ql_RIL_Initialize to initialize RIL.
******************************************************************************/
s32 RIL_QONENET_Config(ST_ONENET_Config_Param_t* onenet_config_param_t,bool server_config_flag);



/******************************************************************************
* Function:     RIL_QONENET_Discover_Rsp
*  
* Description:
*                   Respond the Discover Request
*
* Parameters:    
*                   onenet_discover_rsp_param_t:
*                   [in] 
*                   lwm2m send param,please refer to ST_Socket_Param_t.
*
*                The socket ID, or other Error Codes. 
*                RIL_AT_FAILED, send AT failed.
*                RIL_AT_TIMEOUT,send AT timeout.
*                RIL_AT_BUSY,   sending AT.
*                RIL_AT_INVALID_PARAM, invalid input parameter.
*                RIL_AT_UNINITIALIZED, RIL is not ready, need to wait for MSG_ID_RIL_READY
*                                      and then call Ql_RIL_Initialize to initialize RIL.
******************************************************************************/
s32 RIL_QONENET_Discover_Rsp(ST_ONENET_Discover_Rsp_Param_t *onenet_discover_rsp_param_t);



/******************************************************************************
* Function:     RIL_QONENET_RD
*  
* Description:
*                read Data from Buffer
*
* Parameters:    
*                   rd_length:
*                   [in] 
*                   The maximum length of data to be retrieved, the range is 1-512
*
*                   actual_length
*                   [out] 
*                   The actual length of received data
*
*                   remain_length:
*                   [out] 
*                   The unread length of received data
*
*                   data_buffer:
*                   [out] 
*                   received data
* Return:  
*                The socket ID, or other Error Codes. 
*                RIL_AT_FAILED, send AT failed.
*                RIL_AT_TIMEOUT,send AT timeout.
*                RIL_AT_BUSY,   sending AT.
*                RIL_AT_INVALID_PARAM, invalid input parameter.
*                RIL_AT_UNINITIALIZED, RIL is not ready, need to wait for MSG_ID_RIL_READY
*                                      and then call Ql_RIL_Initialize to initialize RIL.
******************************************************************************/
s32 RIL_QONENET_RD(u32 rd_length,u32* actual_length,u32* remain_length,u8* data_buffer);


/******************************************************************************
* Function:     RIL_QONENET_Write_Rsp
*  
* Description:
*                   Respond the Write Request
*
* Parameters:    
*                ref:
*                  [in]
*                  Instance ID of OneNET communication suite.
*               msgid:
*                   [in] 
*                  The message identifier, which comes from the URC "+MIPLWRITE:".
*               result:
*                    [in]
*                   The result of observe
*
*                The socket ID, or other Error Codes. 
*                RIL_AT_FAILED, send AT failed.
*                RIL_AT_TIMEOUT,send AT timeout.
*                RIL_AT_BUSY,   sending AT.
*                RIL_AT_INVALID_PARAM, invalid input parameter.
*                RIL_AT_UNINITIALIZED, RIL is not ready, need to wait for MSG_ID_RIL_READY
*                                      and then call Ql_RIL_Initialize to initialize RIL.
******************************************************************************/
s32 RIL_QONENET_Write_Rsp(u32 ref,u32 msgid,u32 result);

s32 RIL_QONENET_Read_Rsp(ST_ONENET_Notify_Param_t* onenet_read_param_t);

s32 RIL_QONENET_Execute_Rsp(u32 ref,u32 msgid,u32 result);


/******************************************************************************
* Function:     RIL_QONENET_Notify
*  
* Description:
*                   Notify the Data to OneNET platform or Application Server
*
* Parameters:    
*                  ST_ONENET_Notify_Param_t:
*                   [in] 
*                   onenet notify param,please refer to ST_ONENET_Notify_Param_t.
**                 ack_flag:
*                   [in] 
*                   FALSE     disable ack id .
*                   TRUE      enalbe ack id .
*                 .
*                The socket ID, or other Error Codes. 
*                RIL_AT_FAILED, send AT failed.
*                RIL_AT_TIMEOUT,send AT timeout.
*                RIL_AT_BUSY,   sending AT.
*                RIL_AT_INVALID_PARAM, invalid input parameter.
*                RIL_AT_UNINITIALIZED, RIL is not ready, need to wait for MSG_ID_RIL_READY
*                                      and then call Ql_RIL_Initialize to initialize RIL.
******************************************************************************/
s32 RIL_QONENET_Notify(ST_ONENET_Notify_Param_t* onenet_notify_param_t,bool ack_flag);



/******************************************************************************
* Function:     RIL_QONENET_Update
*  
* Description:
*                  Send Update Request
*
*                ref:
*                  [in]
*                  Instance ID of OneNET communication suite.
*               lifetime:
*                   [in] 
*                  Updated lifetime value. The range is 0 or 15-268435455 Unit: second. "0" means that lifetime is 3600 seconds.
*               onenet_obj_flag:
*                    [in]            
*                  Whether to update with objects list.
* Return:  
*                The socket ID, or other Error Codes. 
*                RIL_AT_FAILED, send AT failed.
*                RIL_AT_TIMEOUT,send AT timeout.
*                RIL_AT_BUSY,   sending AT.
*                RIL_AT_INVALID_PARAM, invalid input parameter.
*                RIL_AT_UNINITIALIZED, RIL is not ready, need to wait for MSG_ID_RIL_READY
*                                      and then call Ql_RIL_Initialize to initialize RIL.
******************************************************************************/
s32 RIL_QONENET_Update(u32 ref,u32 lifetime,Enum_ONENET_Obj_Flag obj_flag);

/******************************************************************************
* Function:     RIL_QONENET_CLOSE
*  
* Description:
*               Send Deregister Request 
*
*                ref:
*                  [in]
*                  Instance ID of OneNET communication suite.
*
* Return:  
*                The socket ID, or other Error Codes. 
*                RIL_AT_FAILED, send AT failed.
*                RIL_AT_TIMEOUT,send AT timeout.
*                RIL_AT_BUSY,   sending AT.
*                RIL_AT_INVALID_PARAM, invalid input parameter.
*                RIL_AT_UNINITIALIZED, RIL is not ready, need to wait for MSG_ID_RIL_READY
*                                      and then call Ql_RIL_Initialize to initialize RIL.
******************************************************************************/
s32 RIL_QONENET_CLOSE(u32 ref);


/******************************************************************************
* Function:     RIL_QONENET_DELETE
*  
* Description:
*               Delete a OneNET Communication Suite Instance
*
*                ref:
*                  [in]
*                  Instance ID of OneNET communication suite.
*
* Return:  
*                The socket ID, or other Error Codes. 
*                RIL_AT_FAILED, send AT failed.
*                RIL_AT_TIMEOUT,send AT timeout.
*                RIL_AT_BUSY,   sending AT.
*                RIL_AT_INVALID_PARAM, invalid input parameter.
*                RIL_AT_UNINITIALIZED, RIL is not ready, need to wait for MSG_ID_RIL_READY
*                                      and then call Ql_RIL_Initialize to initialize RIL.
******************************************************************************/
s32 RIL_QONENET_DELETE(u32 ref);


#endif // __RIL_NETWORK_H__
