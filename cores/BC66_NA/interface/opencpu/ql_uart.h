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
 *   ql_uart.h 
 *
 * Project:
 * --------
 *   OpenCPU
 *
 * Description:
 * ------------
 *  Uart APIs defines.
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
 

#ifndef __QL_UART_H__
#define __QL_UART_H__
#include "ql_common.h"
#include "ql_system.h"

typedef enum {
    UART_PORT0 = 0,
    UART_PORT1,
    UART_PORT2,
    UART_PORT3,
    UART_PORT_END
}Enum_SerialPort;

typedef enum {
    DB_5BIT = 0,
    DB_6BIT,
    DB_7BIT,
    DB_8BIT
} Enum_DataBits;

typedef enum {
    SB_ONE = 1,
    SB_TWO
} Enum_StopBits;

typedef enum {
    PB_NONE = 0,
    PB_ODD,
    PB_EVEN
} Enum_ParityBits;

typedef enum {
    FC_NONE=1,  // None Flow Control
    FC_HW,      // Hardware Flow Control 
    FC_SW       // Software Flow Control
} Enum_FlowCtrl;

typedef struct {
    u32                 baudrate; 
    Enum_DataBits       dataBits;
    Enum_StopBits       stopBits;
    Enum_ParityBits     parity;
    Enum_FlowCtrl       flowCtrl;
}ST_UARTDCB;

typedef enum {
    EVENT_UART_TRANSACTION_ERROR = 0,
    EVENT_UART_READY_TO_READ,
    EVENT_UART_READY_TO_WRITE,
    EVENT_UART_FE_IND,
    EVENT_UART_RI_IND,
    EVENT_UART_DCD_IND,
    EVENT_UART_DTR_IND
} Enum_UARTEventType;


/*****************************************************************
* Function:     Ql_UART_Register 
* 
* Description:
*               This function registers the callback function for the 
*               specified serial port. 
*               UART callback function used for receiving the UART notification from CORE.
*
* Parameters:
*               [in]port:   
*                       Port name                            
*               [in]callback_uart:     
*                       The pointer of the UART call back function.
*               [in]event:
*                       indication the event type of UART call back, please reference Enum_UARTEventType.
*               [in]pinLevel:
*                       if the event type is EVENT_UART_RI_IND or EVENT_UART_DCD_IND or EVENT_UART_DTR_IND
*                       the level indication the relate pin's current level otherwise this parameter has no meaning, just ignore it.
*               [in]customizePara: 
*                       Customize parameter, if not use just set to NULL.    
*
* Return:        
*               QL_RET_OK indicates success; otherwise failure.
*
*****************************************************************/
typedef void (*CallBack_UART_Notify)( Enum_SerialPort port, Enum_UARTEventType event, bool pinLevel,void *customizePara);
s32 Ql_UART_Register(Enum_SerialPort port, CallBack_UART_Notify callback_uart,void * customizePara);


/*****************************************************************
* Function:     Ql_UART_Open 
* 
* Description:
*               This function opens a specified UART port with the specified 
*               flow control mode. 
*               Which task call this function, which task will own the specified UART port.
*
* Parameters:
*               [in]port:       
*                       Port name
*               [in]baud:      
*                       The baud rate of the UART to be opened
*                       for the physical the baud rate support 75,150,300,600,1200,2400,4800,7200,
*                       9600,14400,19200,28800,38400,57600,115200,230400,460800
*                       for the UART_PORT1 support auto-baud rate, when the baud set to 0.
*
*                       This parameter don't take,effect on the VIRTUAL_PORT1,VIRTUAL_PORT2,just set to 0
*
*               [in]flowCtrl:   
*                       one value of Enum_FlowCtrl, used for the physical UART's flow control.
*                       the hardware flow control(FC_HW)  only supported on the UART_PORT1,
*                       other port not support hardware flow control.
*                       This parameter don't take,effect on the VIRTUAL_PORT1,VIRTUAL_PORT2,just set to FC_NONE
*
* Return:        
*               QL_RET_OK indicates success; otherwise failure.       
*
*****************************************************************/
s32 Ql_UART_Open(Enum_SerialPort port,u32 baudrate, Enum_FlowCtrl flowCtrl);


/*****************************************************************
* Function:     Ql_UART_OpenEx 
* 
* Description:
*               This function opens a specified UART port with the 
*               specified DCB parameters.
*               Which task call this function, which task will own the specified UART port.
*
* Parameters:
*               [in]port:   
*                       Port name
*               [in]dcb:   
*                       The point to the UART dcb struct. 
*                       Include baud rate,data bits,stop bits,parity,and flow control
*                       only physical UART1(UART_PORT1) have the hardware flow control
*
*                       This parameter don't take effect on the VIRTUAL_PORT1,VIRTUAL_PORT2
*                       just set to NULL.
*
* Return:        
*               QL_RET_OK indicates success; otherwise failure.    
*
*****************************************************************/
s32 Ql_UART_OpenEx(Enum_SerialPort port, ST_UARTDCB *dcb);



/*****************************************************************
* Function:     Ql_UART_Write 
* 
* Description:
*               This function is used to send data to the specified UART port. 
*
*               When the number of bytes actually write data is less than that to send,
*               Application should stop sending data, and application will receive an event 
*               EVENT_UART_READY_TO_WRITE later. 
*               After receiving this Event Application can continue to send data, 
*               and previously unsent data should be resend.
*
*               NOTE:
*               The RX/TX buffer size of VIRTUAL_PORT1 and VIRTUAL_PORT2 both are 1024-byte,
*               So the number of bytes to write should generally not more than 1024.
*  
* Parameters:
*               [in] port:
*                       Port name
*               [in]data:
*                       Pointer to data to be send
*               [in]writeLen:
*                       The length of the data to be written
*
* Return:        
*               If >= 0, indicates success, and the return value 
*                        is the length of actual write data length
*               If <  0, indicates failure to read      
*
*****************************************************************/
s32 Ql_UART_Write(Enum_SerialPort port, u8* data, u32 writeLen );


/*****************************************************************
* Function:     Ql_UART_Read 
* 
* Description:
*               This function read data from the specified UART port.
*               When the UART callback is called, and the message type is 
*               EVENT_UART_READ_TO_READ,
*               user need read all of the data in the data buffer 
*               which means the real read len is less than the to be read len,
*               otherwise later the UART data is coming, there will be no such event to notify user get data.
*
* Parameters:
*               [in]port:
*                        Port name
*               [out]data:
*                       Point to the read data
*               [in]readLen:
*			    then length of data want to read
*
* Return:        
*               If >= 0, indicates success, and the return value 
*                        is the length of actual read data length
*               If <  0, indicates failure to read
*
*****************************************************************/
s32 Ql_UART_Read(Enum_SerialPort port, u8* data, u32 readLen);


/*****************************************************************
* Function:     Ql_UART_Close 
* 
* Description:
*               This function close a specified UART port.
* Parameters:
*               [in] port:
*                      Port name
* Return:        
*             NONE  
*
*****************************************************************/
void Ql_UART_Close(Enum_SerialPort port);

#endif  // End-of __QL_UART_H__

