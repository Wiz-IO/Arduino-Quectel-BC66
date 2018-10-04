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
 *   ql_adc.h 
 *
 * Project:
 * --------
 *   OpenCPU
 *
 * Description:
 * ------------
 *   The module defines the information, and APIs related to the ADC function.
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
#ifndef __QL_ADC_H__
#define __QL_ADC_H__

typedef enum
{
    PIN_ADC0,
    PIN_ADC_MAX = 2
}Enum_ADCPin;

/*****************************************************************
* Function:     Ql_ADC_Register 
* 
* Description:
*               This function registers an ADC with the ADC pin name,
*               callback function and the customized parameter.
*
* Parameters:
*               adcPin:
*                   ADC pin name, one value of Enum_ADCPin.
*
*               callback_adc:
*                   callback function, which will be invoked when the ADC result comes out.
*
*               customParam:
*                   A customized parameter, which can be used in the ADC interrupt handler. 
*                   It may be NULL if no customized parameter needs to be passed in.
*
*               adcValue:
*                   the average voltage value for the specified sampling times. 
*                   The range is 0~1400mV. Please also see "Ql_ADC_Init".
* Return:        
*               QL_RET_OK, this function succeeds.
*               QL_RET_ERR_NOSUPPORTPIN, the input IO is invalid. 
*               other place. For example this IO has been using as GPIO.
*               QL_RET_ERR_ADC_ALREADY_REGISTERED, this ADC pin is registered already
*****************************************************************/
typedef void (*Callback_ADC)(Enum_ADCPin adcPin, u32 adcValue, void *customParam);
s32 Ql_ADC_Register(Enum_ADCPin adcPin, Callback_ADC callback_adc, void *customParam);

/*****************************************************************
* Function:     Ql_ADC_Init 
* 
* Description:
*               This function configures the sampling parameters, 
*               including sampling count and the interval.
*
*               Note:
*               The ADC sampling result will be reported in the period of 
*               (count * interval)(ms).
*               For example, if Ql_ADC_Init(PIN_ADC0, 5, 400), then the 
*               Callback_ADC function will be triggered in (5*400)ms=2s periodically.
* Parameters:
*               adcPin:
*                   ADC pin name, one value of Enum_ADCPin
*
*               count:
*                   Sampling times for each ADC value, the minimum is 5.
*
*               interval:
*                   Interval of each internal sampling, unit is ms. 
*                   the minimum is 200(ms).
*
*               For example, if Ql_ADC_Init(PIN_ADC0, 5, 200), then
*               |--200ms--->|--200ms--->|--200ms--->|--200ms--->|--200ms--->|...
*               Start---->sample1---->sample2---->sample3---->sample4---->sample5. Then report the average value by callback.
* Return:        
*               QL_RET_OK, this function succeeds.
*               QL_RET_ERR_PARAM, parameter is error.
*               QL_RET_ERR_NOSUPPORTPIN, the input pin is invalid. 
*               QL_RET_ERR_ADC_NOT_REGISTERED, the ADC not registered.
*
*****************************************************************/
s32 Ql_ADC_Init(Enum_ADCPin adcPin, u32 count, u32 interval);

/*****************************************************************
* Function:     Ql_ADC_Sampling 
* 
* Description:
*               this function switches on/off ADC sample.
*
* Parameters:
*               enable:
*                   sample control, TRUE : start to sample.
*                                   FALSE: stop sampling.
*                 
* Return:        
*               QL_RET_OK, this function succeeds.
*               QL_RET_ERR_NOSUPPORTPIN, the input pin is invalid.
*               QL_RET_ERR_ADC_NOT_REGISTERED, the ADC not register
*               QL_RET_ERR_ADC_SAMPLING_ALREADY,the ADC sampling has been started already
*****************************************************************/
s32 Ql_ADC_Sampling(Enum_ADCPin adcPin, bool enable);

#endif  //__QL_ADC_H__
