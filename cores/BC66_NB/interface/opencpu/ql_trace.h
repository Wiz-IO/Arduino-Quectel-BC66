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
 *   ql_trace.h 
 *
 * Project:
 * --------
 *   OpenCPU
 *
 * Description:
 * ------------
 *  debug trace API
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
 

#ifndef __QL_TRACE_H__
#define __QL_TRACE_H__
#include "ql_type.h"

typedef enum {
    BASIC_MODE,  /* In basic mode, debug messages from application will be 
                     output to debug serial port as text.
                     */
    ADVANCE_MODE /* Default mode.
                     In advance mode, debug messages from System and application
                     will be output to debug serial port in special format. Only
                     the Catcher Tool can capture and display these debug messages
                     legibly.
                     */
} Enum_DebugMode;

typedef enum{
    PORTNAME_UART0,
    PORTNAME_UART1,
	PORTNAME_UART2,
	PORTNAME_UART3,
	PORTNAME_USB1,
	PORTNAME_USB2
}Enum_PortName;

/*****************************************************************
* Function:     Ql_Debug_Trace 
* 
* Description:
*               This function prints formatted output to 
*               debug serial port. Its function is same to 'sprintf'.
*
* Parameters:
*               fmt:
*                   Pointer to a null-terminated multibyte string 
*                   specifying how to interpret the data.
*                   The maximum string length is 512 bytes.
* Return:        
*               Number of characters printed
*****************************************************************/
extern s32  (*Ql_Debug_Trace)(char* fmt, ...);

#endif  // #end-of __QL_TRACE_H__
