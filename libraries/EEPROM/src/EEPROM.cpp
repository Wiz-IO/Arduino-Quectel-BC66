/*  for Quectel BC66
 *  Created on: 01.01.2019
 *      Author: Georgi Angelov
 */

#include "EEPROM.h"

#ifdef __OCPU_RIL_SUPPORT__

EEPROMClass EEPROM;

// cell from 1 & 2
static void ql_eeprom_get_index(u32 address, u8 *cell, u32 *size, u32 *offset)
{
    if (address < 50)
    {
        *cell = 1;
        *size = 50;
        *offset = 0;
        return;
    }
    else
    {
        *cell = 2;
        *size = 50;
        *offset = 50;
    }
}

uint8_t EERef::operator*() const
{
    if (index < _EEPROM_SIZE)
    {
        u8 cell;
        u32 size, offset;
        ql_eeprom_get_index(index, &cell, &size, &offset);
        uint8_t data[size];
        int res = Ql_SecureData_Read(cell, (u8 *)data, size); // RIL
        DEBUG_EEP("Read cell = %d, size = %d, res = %d", cell, size, res);
        if (size == res)
        {
            return data[index - offset];
        }
        else
        {
            DEBUG_EEP("Read failed. Return 0 as value");
        }
    }
    return 0;
}

EERef &EERef::operator=(uint8_t in)
{
    if (index < _EEPROM_SIZE)
    {
        u8 cell;
        u32 size, offset;
        ql_eeprom_get_index(index, &cell, &size, &offset);
        uint8_t data[size];
        int res = Ql_SecureData_Read(cell, (u8 *)data, size); // RIL
        DEBUG_EEP("Write cell = %d, size = %d, res = %d", cell, size, res);
        if (size == res)
        {
            data[index - offset] = in;
            Ql_SecureData_Store(cell, (u8 *)data, size); // RIL
        }
        else
        {
            DEBUG_EEP("Write failed ( %d )", res);
        }
    }
    return *this;
}

#endif
