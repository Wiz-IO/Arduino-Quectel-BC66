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
 *   ql_ii.h 
 *
 * Project:
 * --------
 *   OpenCPU
 *
 * Description:
 * ------------
 *   IIC interface APIs defines.
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
#ifndef __QL_IIC_H__
#define __QL_IIC_H__

/** @brief This enum defines the I2C transaction speed.  */
typedef enum {
    I2C_FREQUENCY_50K  = 0,          /**<  50kbps. */
    I2C_FREQUENCY_100K = 1,          /**<  100kbps. */
    I2C_FREQUENCY_200K = 2,          /**<  200kbps. */
    I2C_FREQUENCY_300K = 3,          /**<  300kbps. */
    I2C_FREQUENCY_400K = 4,          /**<  400kbps. */
    I2C_FREQUENCY_1M   = 5,          /**<  1mbps. */
    I2C_FREQUENCY_MAX                /**<  The total number of supported I2C frequencies (invalid I2C frequency).*/
} hal_i2c_frequency_t;


/*****************************************************************
* Function:     Ql_IIC_Init 
* 
* Description:
*               This function initialize the configurations for an IIC channel.
*               including the specified pins for IIC, IIC type, and IIC channel No.
*
* Parameters:
*               chnnlNo:
*                   [In] IIC channel No, the range is 0~254
*               pinSCL:
*                   [In] IIC SCL pin.
*               pinSDA:
*                   [In] IIC SDA pin.
*               IICtype:
*                   [In] IIC type,FALSE means simulate IIC, TRUE means hardware IIC.

* Return:        
*               QL_RET_OK, this function succeeds.
*               QL_RET_ERR_CHANNEL_OUTRANGE, the channel No is out of range.
*               QL_RET_ERR_CHANNEL_USED, the channel No is be used.
*               QL_RET_ERR_FULLI2CBUS, IIC bus is full.
*               QL_RET_ERR_NOSUPPORTPIN, the input pin is invalid.
*               QL_RET_ERR_PINALREADYSUBCRIBE, the pin is in use in
*               other place. For example this pin has been using as EINT or gpio.
*               QL_RET_ERR_I2CHWFAILED, Maybe the hardware have something wrong.
*               QL_RET_ERR_PARAM, IICtype error , or the IICtype = 1, 
*                                 but the  pinSCL and pinSDA pins are not IIC contronller pins 
*****************************************************************/
s32 Ql_IIC_Init(u32 chnnlNo, Enum_PinName pinSCL, Enum_PinName pinSDA, bool IICtype);

/*****************************************************************
* Function:     Ql_IIC_Config 
* 
* Description:
*               This function configuration the IIC interface for one slave.
*         
* Parameters:
*               chnnlNo:
*                   [In] IIC channel No, the No is specified by Ql_IIC_Init function
*               isHost:
*                   [In] must be ture, just support host mode.
*               slaveAddr:
*                   [In] slave address.
*		        IicSpeed:
*		            [In] just used for hardware IIC,and the parameter can be ignored when using simulation IIC.
*               
*
* Return:        
*               QL_RET_OK, this function succeeds.
*               QL_RET_ERR_CHANNEL_NOT_FOUND, can't found the IIC channel, make sure it is initialized already.
*               QL_RET_ERR_IIC_SAME_SLAVE_ADDRESS,the slave address you want to set is already be set,or the address is be used.
*               QL_RET_ERR_PARAM, parameter error.
*               QL_RET_ERR_IIC_SLAVE_TOO_MANY, there too many slave in this channel.(one channel at most support 6 slave)
*****************************************************************/
s32  Ql_IIC_Config(u32 chnnlNo, bool isHost, u8 slaveAddr, u32 IicSpeed);


/*****************************************************************
* Function:     Ql_IIC_Write 
* 
* Description:
*               This function  write data  to specified slave through IIC interface.
*               
* Parameters:
*               chnnlNo:
*                   [In] IIC channel No, the No is specified by Ql_IIC_Init function.
*               slaveAddr:
*                   [In] slave address.
*               pData:
*                   [In] Setting value to slave
*               len:
*                   [In] Number of bytes to write. 
*                   if IICtype=1 ,1<len<8 . because our IIC contronller at most support 8 bytes for one time transaction
* Return:        
*               if no error return, the length of the write data.
*               QL_RET_ERR_PARAM, patameter error.
*               QL_RET_ERR_CHANNEL_NOT_FOUND, can't found the IIC channel, make sure it is initialized already.
*               QL_RET_ERR_I2CHWFAILED, Maybe the hardware have something wrong.
*               QL_RET_ERR_IIC_SLAVE_NOT_FOUND, not found the specified slave.
*****************************************************************/
s32 Ql_IIC_Write(u32 chnnlNo, u8 slaveAddr, u8 *pData, u32 len);

/*****************************************************************
* Function:     Ql_IIC_Read 
* 
* Description:
*               This function read data from specified slave through IIC interface.
*               
* Parameters:
*               chnnlNo:
*                   [In] IIC channel No, the No is specified by Ql_IIC_Init function.
*               slaveAddr:
*                   [In] slave address.
*               pBuffer:
*                   [Out] read buffer of reading the specified register from slave.
*               len:
*                   [In] Number of bytes to read.
*                   if IICtype=1 ,1<len<8 . because our IIC contronller at most support 8 bytes for one time transaction
* Return:        
*               if no error, return the length of the read data.
*               QL_RET_ERR_PARAM, patameter error.
*               QL_RET_ERR_CHANNEL_NOT_FOUND, can't found the IIC channel, make sure it is initialized already.
*               QL_RET_ERR_I2CHWFAILED, Maybe the hardware have something wrong.
*               QL_RET_ERR_IIC_SLAVE_NOT_FOUND, not found the specified slave.
*****************************************************************/
s32 Ql_IIC_Read(u32 chnnlNo, u8 slaveAddr, u8 *pBuffer, u32 len);

/*****************************************************************
* Function:     Ql_IIC_Write_Read 
* 
* Description:
*               This function read data form the specified register(or address) of slave.
*               
* Parameters:
*               chnnlNo:
*                   [In] IIC channel No, the No is specified by Ql_IIC_Init function.
*               slaveAddr:
*                   [In] slave address.
*               pData:
*                   [In] Setting value of the specified register of slave.
*               wrtLen:
*                   [In] Number of bytes to write.
*                          if IICtype=1 ,1<wrtLen<8 . because our IIC contronller at most support 8 bytes for one time transaction
*               pBuffer:
*                   [Out] read buffer of reading the specified register from slave.
*               rdLen:
*                   [In] Number of bytes to read.
*                   if IICtype=1 ,1<rdLen<8 . because our IIC contronller at most support 8 bytes for one time transaction
* Return:        
*               if no error return the length of the read data.
*               QL_RET_ERR_PARAM, parameter error.
*               QL_RET_ERR_CHANNEL_NOT_FOUND, can't found the IIC channel, make sure it is initialized already.
*               QL_RET_ERR_I2CHWFAILED, Maybe the hardware have something wrong.
*               QL_RET_ERR_IIC_SLAVE_NOT_FOUND, not found the specified slave.
*****************************************************************/
s32 Ql_IIC_Write_Read(u32 chnnlNo, u8 slaveAddr, u8 * pData, u32 wrtLen, u8 * pBuffer, u32 rdLen);


/*****************************************************************
* Function:     Ql_IIC_Uninit 
* 
* Description:
*               This function releases the pins.
*               
* Parameters:
*               chnnlNo:
*                   [In] IIC channel No, the No is specified by Ql_IIC_Init function.

* Return:        
*               QL_RET_ERR_CHANNEL_NOT_FOUND, can't found the IIC channel, make sure it is initialized already.
*               QL_RET_ERR_ALREADYUNSUBCRIBE, is released already
*****************************************************************/
s32 Ql_IIC_Uninit(u32 chnnlNo);


#endif  //__QL_IIC_H__
