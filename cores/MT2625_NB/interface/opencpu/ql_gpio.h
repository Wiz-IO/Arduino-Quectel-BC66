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
 *   ql_gpio.h 
 *
 * Project:
 * --------
 *   OpenCPU
 *
 * Description:
 * ------------
 *   GPIO API defines.
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


#ifndef __QL_GPIO_H__
#define __QL_GPIO_H__

/****************************************************************************
 * Enumeration for GPIO Pins available.
 ***************************************************************************/
typedef enum{
    PINNAME_SPI_MISO = 0,
    PINNAME_SPI_MOSI,
    PINNAME_SPI_SCLK,
    PINNAME_SPI_CS,
    PINNAME_NETLIGHT,
    PINNAME_RI,
    PINNAME_DCD,
    PINNAME_CTS_AUX,
    PINNAME_RTS_AUX,
    PINNAME_GPIO1,
    PINNAME_RXD_AUX,
    PINNAME_TXD_AUX,
    PINNAME_GPIO2,
    PINNAME_GPIO3,
    PINNAME_GPIO4,
    PINNAME_GPIO5,
    PINNAME_RXD_DBG,
    PINNAME_TXD_DBG,
    PINNAME_END
}Enum_PinName;

typedef enum{
    PINDIRECTION_IN  = 0,
    PINDIRECTION_OUT = 1
}Enum_PinDirection;

typedef enum{
    PINLEVEL_LOW  = 0,
    PINLEVEL_HIGH = 1
}Enum_PinLevel;

typedef enum{
    PINPULLSEL_DISABLE  = 0,    // Disable pull selection
    PINPULLSEL_PULLDOWN = 1,    // Pull-down 
    PINPULLSEL_PULLUP   = 2     // Pull-up 
}Enum_PinPullSel;


/****************************************************************************
 * GPIO Config Items
 ***************************************************************************/
typedef struct{
    Enum_PinName           pinName;
    Enum_PinDirection      pinDirection;  
    Enum_PinLevel          pinLevel;
    Enum_PinPullSel        pinPullSel;
}ST_GPIOConfig;

/*****************************************************************
* Function:     Ql_GPIO_Init 
* 
* Description:
*               This function enables the GPIO function of the specified pin,
*               and initialize the configurations, including direction,
*               level and pull selection.
*
* Parameters:
*               pinName:
*                   Pin name, one value of Enum_PinName.
*               dir:
*                   The initial direction of GPIO, one value of Enum_PinDirection.
*               level:
*                   The initial level of GPIO, one value of Enum_PinLevel. 
*               pullSel:
*                   Pull selection, one value of Enum_PinPullSel.
* Return:        
*               QL_RET_OK, this function succeeds.
*               QL_RET_ERR_NOSUPPORTPIN, the input GPIO is invalid. 
*               QL_RET_ERR_PINALREADYSUBCRIBE, the GPIO is in use in
*               other place. For example this GPIO has been using as EINT.
*****************************************************************/
s32 Ql_GPIO_Init(Enum_PinName       pinName, 
                 Enum_PinDirection  dir, 
                 Enum_PinLevel      level, 
                 Enum_PinPullSel    pullSel
                 );

/*****************************************************************
* Function:     Ql_GPIO_SetLevel 
* 
* Description:
*               This function sets the level of the specified GPIO.
*
* Parameters:
*               pinName:
*                   Pin name, one value of Enum_PinName.
*               level:
*                   The initial level of GPIO, one value of Enum_PinLevel. 
* Return:        
*               QL_RET_OK, this function succeeds.
*               QL_RET_ERR_NOSUPPORTPIN, the input GPIO is invalid. 
*               QL_RET_ERR_NORIGHTOPERATE, can't operate,Maybe the GPIO not Init
*               QL_RET_ERR_NOGPIOMODE, the input GPIO is not GPIO mode
*****************************************************************/
s32 Ql_GPIO_SetLevel(Enum_PinName pinName, Enum_PinLevel level);

/*****************************************************************
* Function:     Ql_GPIO_GetLevel 
* 
* Description:
*               This function gets the level of the specified GPIO.
*
* Parameters:
*               pinName:
*                   Pin name, one value of Enum_PinName.
* Return:        
*               The level value of the specified GPIO, which is 
*               nonnegative integer.
*               QL_RET_ERR_NOSUPPORTPIN, the input GPIO is invalid. 
*****************************************************************/
s32 Ql_GPIO_GetLevel(Enum_PinName pinName);

/*****************************************************************
* Function:     Ql_GPIO_SetDirection 
* 
* Description:
*               This function sets the direction of the specified GPIO.
*
* Parameters:
*               pinName:
*                   Pin name, one value of Enum_PinName.
*               dir:
*                   The initial direction of GPIO, one value of Enum_PinDirection.
* Return:        
*               QL_RET_OK indicates this function successes.
*               QL_RET_ERR_NOSUPPORTPIN, the input GPIO is invalid. 
*               QL_RET_ERR_NORIGHTOPERATE, can't operate,Maybe the GPIO not Init
*               QL_RET_ERR_NOGPIOMODE, the input GPIO is not GPIO mode
*****************************************************************/
s32 Ql_GPIO_SetDirection(Enum_PinName pinName, Enum_PinDirection dir);

/*****************************************************************
* Function:     Ql_GPIO_GetDirection 
* 
* Description:
*               This function gets the direction of the specified GPIO.
*
* Parameters:
*               pinName:
*                   Pin name, one value of Enum_PinName.
* Return:        
*               The direction of the specified GPIO, which is 
*               nonnegative integer..
*               QL_RET_ERR_NOSUPPORTPIN, the input GPIO is invalid. 
*               QL_RET_ERR_NORIGHTOPERATE, can't operate,Maybe the GPIO not Init
*               QL_RET_ERR_NOGPIOMODE, the input GPIO is not GPIO mode
*****************************************************************/
s32 Ql_GPIO_GetDirection(Enum_PinName pinName);

/*****************************************************************
* Function:     Ql_GPIO_SetPullSelection 
* 
* Description:
*               This function sets the pull selection of the specified GPIO.
*
* Parameters:
*               pinName:
*                   Pin name, one value of Enum_PinName.
*               Enum_PinPullSel:
*                   Pull selection, one value of Enum_PinPullSel.
* Return:        
*               QL_RET_OK indicates this function successes.
*               QL_RET_ERR_NOSUPPORTPIN, the input GPIO is invalid. 
*               QL_RET_ERR_NORIGHTOPERATE, can't operate,Maybe the GPIO not Init
*               QL_RET_ERR_NOGPIOMODE, the input GPIO is not GPIO mode
*****************************************************************/
s32 Ql_GPIO_SetPullSelection(Enum_PinName pinName, Enum_PinPullSel pullSel);


/*****************************************************************
* Function:     Ql_GPIO_Uninit 
* 
* Description:
*               This function releases the specified GPIO that was 
*               initialized by calling Ql_GPIO_Init() previously.
*               After releasing, the GPIO can be used for other purpose.
* Parameters:
*               pinName:
*                   Pin name, one value of Enum_PinName.
* Return:        
*               QL_RET_OK, this function succeeds.
*               QL_RET_ERR_NOSUPPORTPIN, the input GPIO is invalid. 
*               QL_RET_ERR_BUSSUBBUSY, the GPIO not used as GPIO, 
*               Maby is used by IIC or SPI,this function can't release it
*****************************************************************/
s32 Ql_GPIO_Uninit(Enum_PinName pinName);

#endif  // __QL_GPIO_H__
