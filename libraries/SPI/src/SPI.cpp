/*
 *  Created on: 01.15.2019
 *      Author: Georgi Angelov
 */

#include <Arduino.h>
#include "SPI.h"

#define DEBUG_SPI /*DBG*/

SPIClass SPI(0); // hardware spi, all other is software

SPISettings::SPISettings(uint32_t clockFrequency, BitOrder bitOrder, SPIDataMode dataMode)
{
    clock = clockFrequency;
    order = bitOrder;
    mode = dataMode;
}

/* default SPI setting */
SPISettings::SPISettings()
{
    clock = 1000;
    order = MSBFIRST;
    mode = SPI_MODE0;
}

////////////////////////////////////////////////////////////////////////////////////////////

void SPIClass::set_hard_pins()
{
    _miso = PINNAME_SPI_MISO; //spi MISO pin, can not change to another pin.
    _mosi = PINNAME_SPI_MOSI; //spi MOSI pin, can not change to another pin.
    _clk = PINNAME_SPI_SCLK;  //spi CLK pin, can not change to another pin.
    _cs = PINNAME_SPI_CS;     //spi CS pin, user can change this pin to annother pin.
    _type = 1;                //spi hardware
    _port = 0;
}

SPIClass::SPIClass()
{
    set_hard_pins();
}

SPIClass::SPIClass(uint32_t port)
{
    _port = port;
    _type = 0;
    if (0 == port)
        set_hard_pins();
}

SPIClass::SPIClass(uint32_t port, int miso, int mosi, int clk, int cs)
{
    _port = port;
    if (0 == port)
    {
        set_hard_pins();
    }
    else
    {
        _type = 0;
        PinDescription *p;

        p = getArduinoPin(miso);
        if (p)
            _miso = (Enum_PinName)p->device;

        p = getArduinoPin(mosi);
        if (p)
            _mosi = (Enum_PinName)p->device;

        p = getArduinoPin(clk);
        if (p)
            _clk = (Enum_PinName)p->device;

        p = getArduinoPin(cs);
        if (p)
        {
            _cs = (Enum_PinName)p->device;
            if (PINNAME_SPI_CS != _cs)                                                 // manual cs
                Ql_GPIO_Init(_cs, PINDIRECTION_OUT, PINLEVEL_HIGH, PINPULLSEL_PULLUP); //CS high
        }
    }
}

void SPIClass::cs(int level)
{
    if (PINNAME_SPI_CS != _cs)
        Ql_GPIO_SetLevel(_cs, (Enum_PinLevel)level);
}

void SPIClass::setBitOrder(BitOrder order)
{
    _order = order;
};

void SPIClass::setDataMode(uint8_t mode)
{
    _cpol = (bool)mode & 2;
    _cpha = (bool)mode & 1;
};

void SPIClass::setFrequency(uint32_t frequency)
{
    _clock = frequency;
};

/* Initializes the SPI bus by setting SCK,
   MOSI, and SS to outputs, pulling SCK and
   MOSI low, and SS high */
void SPIClass::begin()
{
    int res = Ql_SPI_Init(_port, _clk, _miso, _mosi, _cs, _type);
    res = Ql_SPI_Config(_port, /*master*/ 1, _cpol, _cpha, _clock);
}

/* Disables the SPI bus (leaving pin modes unchanged) */
void SPIClass::end()
{
    Ql_SPI_Uninit(_port);
    if (PINNAME_SPI_CS != _cs)
        Ql_GPIO_Uninit(_cs);
}

/* Stop using the SPI bus. Normally this is called after de-asserting the chip select, to allow other libraries to use the SPI bus */
void SPIClass::endTransaction(void)
{
    end();
}

/* Initializes the SPI bus using the defined SPISettings */
void SPIClass::beginTransaction(SPISettings settings)
{
    setFrequency(settings.clock);
    setDataMode(settings.mode);
    setBitOrder(settings.order);
    begin();
}

uint8_t SPIClass::transfer(uint8_t tx)
{
    // Quectel spi_config.bit_order = HAL_SPI_MASTER_MSB_FIRST = 1;
    uint8_t rx;
    if (_order == LSBFIRST)
        tx = __REV(__RBIT(tx));
    int res = Ql_SPI_WriteRead(_port, &tx, 1, &rx, 1);
    return res == 1 ? rx : 0;
}

uint16_t SPIClass::transfer16(uint16_t _data)
{
    union {
        uint16_t val;
        struct
        {
            uint8_t lsb;
            uint8_t msb;
        };
    } t;
    t.val = _data;
    if (_order == LSBFIRST)
    {
        t.lsb = transfer(t.lsb);
        t.msb = transfer(t.msb);
    }
    else
    {
        t.msb = transfer(t.msb);
        t.lsb = transfer(t.lsb);
    }
    return t.val;
}

int SPIClass::transfer(uint8_t *tx, uint32_t wLen)
{

    if (tx && wLen)
    {
        if (_order == MSBFIRST)
        {
            return Ql_SPI_WriteRead(_port, tx, wLen, tx, wLen);
        }
        else
        {
            for (int i = wLen; i; i--)
                tx[i - 1] = transfer(tx[i - 1]);
        }
    }
    return -1;
}

int SPIClass::transfer(uint8_t *tx, uint32_t wLen, uint8_t *rx, uint32_t rLen)
{
    if (tx && rx && wLen && rLen)
    {
        if (_order == MSBFIRST)
        {
            return Ql_SPI_WriteRead(_port, tx, wLen, rx, rLen);
        }
        else
        {
            for (int i = wLen; i; i--)
                rx[i - 1] = transfer(tx[i - 1]);
        }
    }
    return -1;
}
