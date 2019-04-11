#include <Arduino.h>

#define EEP_DBG

#include "SYS_EEPROM.h"

#ifdef MTK_NVDM_ENABLE

EEPROMClass EEPROM;

#define _SECTOR_SIZE (16)

#define PROPERTY_NAME "ARDUINO"
#define STRING_SIZE (8)

#define GET_OFFSET(x) ((x) % _SECTOR_SIZE)

void _get_entry_name(int index, char *buffer)
{
    sprintf(buffer, "%d", index / _SECTOR_SIZE);
}

uint8_t EERef::operator*() const
{
    nvdm_status_t ret;
    char name[STRING_SIZE];

    if (index < _EEPROM_SIZE)
    {
        uint8_t data[_SECTOR_SIZE];
        uint32_t data_size = _SECTOR_SIZE;

        _get_entry_name(index, name);

        ret = nvdm_read_data_item(PROPERTY_NAME, name, data, &data_size);

        if (ret == NVDM_STATUS_OK)
        {
            // only read the needed byte
            return data[GET_OFFSET(index)];
        }
        else
        {
            EEP_DBG("EEPROM read failed. Return 0 as the read value\n");
        }
    }

    return 0;
}

EERef &EERef::operator=(uint8_t in)
{
    nvdm_status_t ret;
    char name[STRING_SIZE];

    if (index < _EEPROM_SIZE)
    {
        uint8_t data[_SECTOR_SIZE];
        uint32_t data_size = _SECTOR_SIZE;

        _get_entry_name(index, name);

        // read out the data first
        ret = nvdm_read_data_item(PROPERTY_NAME, name, data, &data_size);

        // reading a position not written before would cause a NOT_FOUND error
        if (ret == NVDM_STATUS_OK || ret == NVDM_STATUS_ITEM_NOT_FOUND)
        {
            // only modify the byte needs to be updated
            data[GET_OFFSET(index)] = in;

            nvdm_write_data_item(PROPERTY_NAME, name, NVDM_DATA_ITEM_TYPE_RAW_DATA, data, _SECTOR_SIZE);
        }
        else
        {
            EEP_DBG("EEPROM write failed (%d)\n", ret);
        }
    }

    return *this;
}

#endif