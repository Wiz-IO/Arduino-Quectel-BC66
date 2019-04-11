#define MTK_NVDM_ENABLE
#ifdef MTK_NVDM_ENABLE

#include <Arduino.h>
#include <NVDM.h>

NVDMClass NVDM;

static NVDMStatus _convert_status_code(nvdm_status_t code)
{
    NVDMStatus result;

    switch (code)
    {
        case NVDM_STATUS_INVALID_PARAMETER:
            result = NVDM_INVALID_PARAMETER;
            break;
        case NVDM_STATUS_ITEM_NOT_FOUND:
            result = NVDM_ITEM_NOT_FOUND;
            break;
        case NVDM_STATUS_INSUFFICIENT_SPACE:
            result = NVDM_INSUFFICIENT_SPACE;
            break;
        case NVDM_STATUS_INCORRECT_CHECKSUM:
            result = NVDM_INCORRECT_CHECKSUM;
            break;
        case NVDM_STATUS_ERROR:
            result = NVDM_ERROR;
            break;
        case NVDM_STATUS_OK:
            result = NVDM_OK;
            break;
        default:
            result = NVDM_ERROR;
    }

    return result;
}

/* write data into the flash
   [IN] sectionName  - The name of the data section
   [IN] propertyName - The name of the property inside the data section specified above
   [IN] dataType     - The data type to be stored
   [IN] buffer       - The buffer which contains the data
   [IN] data_size    - The size of the data
*/
NVDMStatus NVDMClass::write(const char *sectionName, const char *propertyName, NVDMDataType dataType, const uint8_t *buffer, uint32_t data_size)
{
    nvdm_status_t ret;

    ret = nvdm_write_data_item(
        sectionName,
        propertyName,
        (dataType == NVDM_RAW_DATA)? NVDM_DATA_ITEM_TYPE_RAW_DATA: NVDM_DATA_ITEM_TYPE_STRING,
        buffer,
        data_size);
    return _convert_status_code(ret);
}

/* read data from the flash
   [IN]     sectionName  - The name of the data section
   [IN]     propertyName - The name of the property inside the data section specified above
   [IN]     buffer       - The buffer to contain the data
   [IN/OUT] data_size    - as input: the size of the buffer. as output: the size of the read-out data
*/
NVDMStatus NVDMClass::read(const char *sectionName, const char *propertyName, uint8_t *buffer, uint32_t *size)
{
    nvdm_status_t ret;
    ret = nvdm_read_data_item(sectionName, propertyName, buffer, size);
    return _convert_status_code(ret);
}

#endif

