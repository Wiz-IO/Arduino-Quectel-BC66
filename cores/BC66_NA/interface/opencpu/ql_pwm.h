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
 *   ql_pwm.h 
 *
 * Project:
 * --------
 *   OpenCPU
 *
 * Description:
 * ------------
 *   PWM  APIs defines.
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
 
#ifndef __QL_PWM_H__
#define __QL_PWM_H__

typedef enum{
    PWMSOURCE_13M= 0,
    PWMSOURCE_32K,
    END_OF_PWMSOURCE
}Enum_PwmSource;

typedef enum{
    PWMSOURCE_DIV2= 1,
    PWMSOURCE_DIV4,
    PWMSOURCE_DIV8,
    END_OF_PWMSOURCE_DIV
}Enum_PwmSourceDiv;


/*****************************************************************
* Function:     Ql_PWM_Init 
* 
* Description:
*               This function initializes the PWM pin. 
*
*               NOTES:
*                   The PWM waveform can't out immediately after Ql_PWM_Init Initialization
*                   you must invoke Ql_PWM_Output function to control PWM waveform on or off
* Parameters:
*               pinName:
*                   Pin name, support three pwm channels, can PINNAME_NETLIGHT/PINNAME_RTS_AUX/PINNAME_GPIO3.
*               pwmSrcClk:
*                   PWM source clock , one value of Enum_PwmSource.
*               pwmDiv:
*                   source clock divide, one value of Enum_PwmSourceDiv
*               lowPulseNum:
*                   set the number of clock cycles to stay at low level. The result
*                   of lowPulseNum plus highPulseNum is less than 8193.
*               highPulseNum:
*                   set the number of clock cycles to stay at high level. The result
*                   of lowPulseNum plus highPulseNum is less than 8193.
* Return:        
*               QL_RET_OK, this function succeeds.
*               QL_RET_ERR_NOSUPPORTPIN, the input pin is invalid. 
*               QL_RET_ERR_PINALREADYSUBCRIBE, the pin is in use in
*               other place. For example this pin has been using as EINT.
*               QL_RET_ERR_NOGPIOMODE, the input pin no PWM mode
*               QL_RET_ERR_NOSUPPORTSET not support this function
*****************************************************************/
s32 Ql_PWM_Init(Enum_PinName pwmPinName,Enum_PwmSource pwmSrcClk,Enum_PwmSourceDiv pwmDiv,u32 lowPulseNum,u32 highPulseNum);

/*****************************************************************
* Function:     Ql_PWM_Uninit 
* 
* Description:
*               This function release a PWM pin.
*
* Parameters:
*               pinName:
*                   Pin name, support three pwm channels, can PINNAME_NETLIGHT/PINNAME_RTS_AUX/PINNAME_GPIO3.
* Return:        
*               QL_RET_OK, this function succeeds.
*               QL_RET_ERR_NOSUPPORTPIN, the input pin is invalid. 
*****************************************************************/
s32 Ql_PWM_Uninit(Enum_PinName pwmPinName);

/*****************************************************************
* Function:     Ql_PWM_Output 
* 
* Description:
*               This function switches on/off PWM waveform output.
*
* Parameters:
*               pinName:
*                   Pin name, support three pwm channels, can PINNAME_NETLIGHT/PINNAME_RTS_AUX/PINNAME_GPIO3.
*               pwmOnOff:
*                   PWM enable. control the PWM waveform output or not output.
*
* Return:        
*               QL_RET_OK, this function succeeds.
*               QL_RET_ERR_NOSUPPORTPIN, the input pin is invalid. 
*               QL_RET_ERR_NORIGHTOPERATE, the PIN not in PWM mode or not init, 
*               QL_RET_ERR_NOSUPPORTCONTROL not support control   
*****************************************************************/
s32 Ql_PWM_Output(Enum_PinName pwmPinName,bool pwmOnOff);

#endif  //__QL_PWM_H__
