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
 *   custom_gpio_cfg.h
 *
 * Project:
 * --------
 *   OpenCPU
 *
 * Description:
 * ------------
 *   The file intends for GPIO initialization definition. 
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
#ifndef __CUSTOM_GPIO_CFG_H__
#define __CUSTOM_GPIO_CFG_H__

/*========================================================================
| 
| GPIO initialization configurations.
|------------------------------------
| IMPORTANT NOTES:
|------------------
|
| This is the initialization list for GPIOs at the early of module booting.
| Developer can do configuring here if some GPIOs need to be initialized at
| the early booting. For example, some GPIO is used to control the power 
| supply of peripheral.
|
| Besides this config list, developer may call Ql_GPIO_Init() to initialize
| the parameters of I/O interfaces dynamically. But it's later than the 
| previous method on time sequence.
\=========================================================================*/
/*----------------------------------------------------------------------------------------------
{ Pin Name           |         Direction       |       Level         |   Pull Selection         }
 *---------------------------------------------------------------------------------------------*/




#if 0 // If needed, config GPIOs here
GPIO_ITEM(PINNAME_SPI_MISO,       PINDIRECTION_OUT,    PINLEVEL_LOW,  PINPULLSEL_PULLUP)
GPIO_ITEM(PINNAME_SPI_MOSI,       PINDIRECTION_OUT,    PINLEVEL_LOW,  PINPULLSEL_PULLUP)
GPIO_ITEM(PINNAME_SPI_SCLK,       PINDIRECTION_OUT,    PINLEVEL_LOW,  PINPULLSEL_PULLUP)
GPIO_ITEM(PINNAME_SPI_CS,         PINDIRECTION_OUT,    PINLEVEL_LOW,  PINPULLSEL_PULLUP)
GPIO_ITEM(PINNAME_NETLIGHT,       PINDIRECTION_OUT,    PINLEVEL_LOW,  PINPULLSEL_PULLUP)
GPIO_ITEM(PINNAME_RI,             PINDIRECTION_OUT,    PINLEVEL_LOW,  PINPULLSEL_PULLUP)
GPIO_ITEM(PINNAME_DCD,            PINDIRECTION_OUT,    PINLEVEL_LOW,  PINPULLSEL_PULLUP)
GPIO_ITEM(PINNAME_CTS_AUX,        PINDIRECTION_OUT,    PINLEVEL_LOW,  PINPULLSEL_PULLUP)
GPIO_ITEM(PINNAME_RTS_AUX,        PINDIRECTION_OUT,    PINLEVEL_LOW,  PINPULLSEL_PULLUP)
GPIO_ITEM(PINNAME_GPIO1,          PINDIRECTION_OUT,    PINLEVEL_LOW,  PINPULLSEL_PULLUP)
GPIO_ITEM(PINNAME_RXD_AUX,        PINDIRECTION_OUT,    PINLEVEL_LOW,  PINPULLSEL_PULLUP)
GPIO_ITEM(PINNAME_TXD_AUX,        PINDIRECTION_OUT,    PINLEVEL_LOW,  PINPULLSEL_PULLUP)
GPIO_ITEM(PINNAME_GPIO2,          PINDIRECTION_OUT,    PINLEVEL_LOW,  PINPULLSEL_PULLUP)
GPIO_ITEM(PINNAME_GPIO3,          PINDIRECTION_OUT,    PINLEVEL_LOW,  PINPULLSEL_PULLUP)
GPIO_ITEM(PINNAME_GPIO4,          PINDIRECTION_OUT,    PINLEVEL_LOW,  PINPULLSEL_PULLUP)
GPIO_ITEM(PINNAME_GPIO5,          PINDIRECTION_OUT,    PINLEVEL_LOW,  PINPULLSEL_PULLUP)
GPIO_ITEM(PINNAME_RXD_DBG,        PINDIRECTION_OUT,    PINLEVEL_LOW,  PINPULLSEL_PULLUP)
GPIO_ITEM(PINNAME_TXD_DBG,        PINDIRECTION_OUT,    PINLEVEL_LOW,  PINPULLSEL_PULLUP)

#endif

#endif //__CUSTOM_GPIO_CFG_H__
