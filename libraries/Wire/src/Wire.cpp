/*
 * TWI/I2C library for Arduino Zero
 * Copyright (c) 2015 Arduino LLC. All rights reserved.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */

#include <Arduino.h>
#include "Wire.h"

#define DEBUG_I2C /*DBG*/

#define IIC_TYPE (i2c_port == 1)

#define SLC0 PINNAME_GPIO4
#define SDA0 PINNAME_GPIO5

TwoWire::TwoWire(uint8_t port, uint8_t address, u32 brg)
{
	i2c_port = port;
	slaveAddress = address;
	i2c_speed = brg;
	transmissionBegun = false;
}

void TwoWire::begin(void)
{
	int res;
	if (1 == i2c_port)
	{
		res = Ql_IIC_Init(i2c_port, PINNAME_RI, PINNAME_DCD, IIC_TYPE);
		DEBUG_I2C("[I2C] Init HW: %d\n", res);
	}
	else
	{
		res = Ql_IIC_Init(i2c_port, SLC0, SDA0, IIC_TYPE);
		DEBUG_I2C("[I2C] Init SW: %d\n", res);
	}
	res = Ql_IIC_Config(i2c_port, TRUE, slaveAddress, i2c_speed); // set default speed
	DEBUG_I2C("[I2C] Config: %d\n", res);
}

void TwoWire::setClock(uint32_t baudrate)
{
	int res = -1;
	switch (baudrate)
	{
	case 1000000:
		res = Ql_IIC_Config(i2c_port, TRUE, I2C_FREQUENCY_1M, IIC_TYPE);
		break;
	case 400000:
		res = Ql_IIC_Config(i2c_port, TRUE, I2C_FREQUENCY_400K, IIC_TYPE);
		break;
	case 200000:
		res = Ql_IIC_Config(i2c_port, TRUE, I2C_FREQUENCY_200K, IIC_TYPE);
		break;
	case 100000:
		res = Ql_IIC_Config(i2c_port, TRUE, I2C_FREQUENCY_100K, IIC_TYPE);
		break;
	case 50000:
	default:
		res = Ql_IIC_Config(i2c_port, TRUE, I2C_FREQUENCY_50K, IIC_TYPE);
		break;
	}
	i2c_speed = baudrate;
	DEBUG_I2C("[I2C] Config: %d\n", res);
	return;
}

void TwoWire::end()
{
	Ql_IIC_Uninit(i2c_port);
}

uint8_t TwoWire::requestFrom(uint8_t address, size_t quantity, bool stopBit)
{
	int res = -1;
	if (quantity == 0)
		return 0;
	if (!stopBit)
		return 0;
	rxBuffer.clear();
	res = Ql_IIC_Read(i2c_port, address, (uint8_t *)(rxBuffer._aucBuffer), (uint32_t)quantity);
	if (res < 0)
	{
		DEBUG_I2C("[I2C] Ql_IIC_Read: %d\n", res);
		quantity = 0;
	}
	rxBuffer._iHead = quantity;
	return rxBuffer.available();
}

uint8_t TwoWire::requestFrom(uint8_t address, size_t quantity)
{
	return requestFrom(address, quantity, true);
}

void TwoWire::beginTransmission(uint8_t address)
{
	txAddress = address;
	txBuffer.clear();
	transmissionBegun = true;
}

// Errors:
//  0 : Success
//  1 : Data too long
//  2 : NACK on transmit of address
//  3 : NACK on transmit of data
//  4 : Other error
uint8_t TwoWire::endTransmission(bool stopBit)
{
	if (!stopBit)
		return 4;
	transmissionBegun = false;
	if (txBuffer.available() == 0)
		return 0;
	int res = Ql_IIC_Write(i2c_port, txAddress, (uint8_t *)(txBuffer._aucBuffer), (uint32_t)txBuffer.available());
	if (res < 0)
	{
		DEBUG_I2C("[I2C] Ql_IIC_Write: %d\n", res);
		return 4;
	}
	return 0;
}

uint8_t TwoWire::endTransmission()
{
	return endTransmission(true);
}

size_t TwoWire::write(uint8_t ucData)
{
	if (!transmissionBegun || txBuffer.isFull())
		return 0;
	txBuffer.store_char(ucData);
	return 1;
}

size_t TwoWire::write(const uint8_t *data, size_t quantity)
{
	for (size_t i = 0; i < quantity; ++i)
	{
		if (!write(data[i]))
			return i;
	}
	return quantity;
}

int TwoWire::available(void)
{
	return rxBuffer.available();
}

int TwoWire::read(void)
{
	return rxBuffer.read_char();
}

int TwoWire::peek(void)
{
	return rxBuffer.peek();
}

void TwoWire::flush(void)
{
	// Do nothing, use endTransmission(..) to force data transfer.
}
