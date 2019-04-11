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
 *   ql_spi.h 
 *
 * Project:
 * --------
 *   OpenCPU
 *
 * Description:
 * ------------
 *   SPI APIs definition.
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
#ifndef __QL_SPI_H__
#define __QL_SPI_H__

/*****************************************************************
* Function:     Ql_SPI_Init 
* 
* Description:
*               This function initialize the configurations for a SPI channel.
*               including the specified pins for SPI, SPI type, and SPI channel No.
*
* Parameters:
*               chnnlNo:
*                   [In] SPI channel No, the range is 0~254
*               pinClk:
*                   [In] SPI CLK pin.
*               pinMiso:
*                   [In] SPI MISO pin.
*               pinMosi:
*                   [In] SPI MOSI pin.
*               pinCs:
*                   [In] SPI CS pin.
*               spiType:
*                   [In] SPI type, 1 for hardware SPI and 0 for simulation SPI.

* Return:        
*               QL_RET_OK, this function succeeds.
*               QL_RET_ERR_PARAM, parameter error.
*               QL_RET_ERR_CHANNEL_OUTRANGE, the channel No is out of range.
*               QL_RET_ERR_CHANNEL_USED, the channel No is used already.
*               QL_RET_ERR_FULLSPIBUS, SPI bus is full.
*======================
* Example:
*======================
*   you could use this api like this for H/W SPI:
*   Ql_SPI_Init(    1,                  //spi channel select.
                    PINNAME_PCM_IN,     //spi CLK pin, can not change to another pin.
                    PINNAME_PCM_SYNC,   //spi MISO pin, can not change to another pin.
                    PINNAME_PCM_OUT,    //spi MOSI pin, can not change to another pin.
                    PINNAME_PCM_CLK,    //spi CS pin, user can change this pin to annother pin.
                    					//if user chose another pin, user should init the pin and must maintain the level by self.
                    1					//for H/W SPI.
                );

*   you could use this api like this for S/W SPI:
*   Ql_SPI_Init(    1,                  //spi channel select.
                    PINNAME_PCM_IN,     //spi CLK pin, user could those another pin.
                    PINNAME_PCM_SYNC,   //spi MISO pin, user could those another pin.
                    PINNAME_PCM_OUT,    //spi MOSI pin, user could those another pin.
                    PINNAME_PCM_CLK,    //Iglore it. User could chose another pin and init it, maintain the level by self.
                    0					//for S/W SPI.
                );                
*****************************************************************/
s32 Ql_SPI_Init(u32 chnnlNo, Enum_PinName pinClk, Enum_PinName pinMiso, Enum_PinName pinMosi, Enum_PinName pinCs, bool spiType);

/*****************************************************************
* Function:     Ql_SPI_Config 
* 
* Description:
*               This function configures the SPI interface.
*
* Parameters:
*               chnnlNo:
*                   [In] SPI channel No, the range is 0~254
*               isHost:
*                   [In] must be 'TRUE', not support salve mode .
*               cpol:
*                   [In] Clock Polarity
*               cpha:
*                   [In] Clock Phase
*               clkSpeed:
*                   [In] just used for hardware SPI,and the parameter can be ignored when using simulation SPI.
*                        the range of SPI speed is from 30kbps to 52Mbps.
* Return:        
*               QL_RET_OK, this function succeeds.
*               QL_RET_ERR_PARAM, parameter error.
*               QL_RET_ERR_CHANNEL_OUTRANGE, the channel No is out of range.
*               QL_RET_ERR_CHANNEL_USED, the channel No is used already.
*======================
* Example:
*======================
*   you could use this api like this :
*   Ql_SPI_Config(  1,      //spi channel select, now only supports 1.
                    1,      //spi master/slave select, now only supports master feature.
                    0,      //spi clock polarity, can be 1 or 0;
                    0,      //spi clock phase, can be 1 or 0;
                    300,  //spi clock speed, the unit is KHz.
                );
*****************************************************************/
s32 Ql_SPI_Config(u32 chnnlNo, bool isHost, bool cpol, bool cpha, u32 clkSpeed);

/*****************************************************************
* Function:     Ql_SPI_Write 
* 
* Description:
*               This function writes data to the specified slave.
*               
* Parameters:
*               chnnlNo:
*                   [In] SPI channel No, the No is specified by Ql_SPI_Init function.
*               pData:
*                   [In] Setting value to slave
*               len:
*                   [In] Number of bytes to write.
* Return:        
*               if no error return the length of the write data.
*               QL_RET_ERR_PARAM, parameter error.
*               QL_RET_ERR_CHANNEL_NOT_FOUND, can't found the SPI channel, make sure it is initialized already.
*****************************************************************/
s32 Ql_SPI_Write(u32 chnnlNo, u8 * pData, u32 len);

/*****************************************************************
* Function:     Ql_SPI_WriteRead 
* 
* Description:
*               This function is used for SPI full-duplex communication 
*               
* Parameters:
*               chnnlNo:
*                   [In] SPI channel No, the No is specified by Ql_SPI_Init function.
*               pData:
*                   [In] Setting value to slave.
*               wrtLen:
*                   [In] Number of bytes to write.
*               pBuffer:
*                   [Out] read buffer of reading from slave.
*               rdLen:
*                   [In] Number of bytes to read.
*
*               Notes:
*                   if (wrtLen > rdLen) , the other read buffer data will be set 0xff;
*                   if (rdLen > wrtLen) , the other write buffer data will be set 0xff;
* Return:        
*               if no error, return the length of the read data.
*               QL_RET_ERR_PARAM, parameter error.
*               QL_RET_ERR_CHANNEL_NOT_FOUND, can't found the SPI channel, make sure it is initialized already.
*****************************************************************/
s32 Ql_SPI_WriteRead(u32 chnnlNo, u8 *pData, u32 wrtLen, u8 * pBuffer, u32 rdLen);
/*****************************************************************
* Function:     Ql_SPI_WriteRead_Ex
* 
* Description:
*               This function is used for SPI full-duplex communication with callback function, only hardware SPI.
*               
* Parameters:
*               chnnlNo:
*                   [In] SPI channel No, the No is specified by Ql_SPI_Init function.
*               pData:
*                   [In] Setting value to slave.
*               wrtLen:
*                   [In] Number of bytes to write.
*               rdLen:
*                   [In] Number of bytes to read.
*               callback_spi:
*                   [In] callback function,which can get recieved data.
*
* Return:        
*               if no error, return 0.
*               QL_RET_ERR_PARAM, parameter error.
*               QL_RET_ERR_CHANNEL_NOT_FOUND, can't found the SPI channel, make sure it is initialized already.
*****************************************************************/

s32 Ql_SPI_Uninit(u32 chnnlNo);

#endif  //__QL_SPI_H__
