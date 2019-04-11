/*
 *  Created on: 01.15.2019
 *      Author: Georgi Angelov
 */

#include "variant.h"

PinDescription pinsMap[18] = {
    {0, PINNAME_SPI_MISO, NULL},
    {1, PINNAME_SPI_MOSI, NULL},
    {2, PINNAME_SPI_SCLK, NULL},
    {3, PINNAME_SPI_CS, NULL},
    {4, PINNAME_NETLIGHT, NULL},
    {5, PINNAME_RI, NULL},
    {6, PINNAME_DCD, NULL},
    {7, PINNAME_CTS_AUX, NULL},
    {8, PINNAME_RTS_AUX, NULL},
    {9, PINNAME_GPIO1, NULL},
    {10, PINNAME_RXD_AUX, NULL},
    {11, PINNAME_TXD_AUX, NULL},
    {12, PINNAME_GPIO2, NULL},
    {13, PINNAME_GPIO3, NULL},
    {14, PINNAME_GPIO4, NULL},
    {15, PINNAME_GPIO5, NULL},
    {16, PINNAME_RXD_DBG, NULL},
    {17, PINNAME_TXD_DBG, NULL},
};
