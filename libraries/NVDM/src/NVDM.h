#ifndef __NVDM_H__
#define __NVDM_H__

#define MTK_NVDM_ENABLE
#ifdef MTK_NVDM_ENABLE

#include <Arduino.h>

typedef enum
{
    NVDM_RAW_DATA,
    NVDM_STRING_DATA
} NVDMDataType;

typedef enum
{
    NVDM_INVALID_PARAMETER = -5,  /**< The user parameter is invalid. */
    NVDM_ITEM_NOT_FOUND = -4,     /**< The data item wasn't found.  */
    NVDM_INSUFFICIENT_SPACE = -3, /**< No space is available in the flash. */
    NVDM_INCORRECT_CHECKSUM = -2, /**< Found a checksum error when reading the data item. */
    NVDM_ERROR = -1,              /**< An unknown error occurred. */
    NVDM_OK = 0                   /**< The operation was successful. */
} NVDMStatus;

class NVDMClass
{
  public:
    NVDMClass(){};

    /* write data into the flash
       [IN] sectionName  - The name of the data section
       [IN] propertyName - The name of the property inside the data section specified above
       [IN] dataType     - The data type to be stored
       [IN] buffer       - The buffer which contains the data
       [IN] data_size    - The size of the data
    */
    NVDMStatus write(
        const char *sectionName,
        const char *propertyName,
        NVDMDataType dataType,
        const uint8_t *buffer,
        uint32_t dataSize);

    /* read data from the flash
       [IN]     sectionName  - The name of the data section
       [IN]     propertyName - The name of the property inside the data section specified above
       [IN]     buffer       - The buffer to contain the data
       [IN/OUT] data_size    - as input: the size of the buffer. as output: the size of the read-out data
    */
    NVDMStatus read(const char *sectionName, const char *propertyName, uint8_t *buffer, uint32_t *size);

  private:
};

extern NVDMClass NVDM;

#else
#error "MTK_NVDM_ENABLE not defined."
#endif

#endif
