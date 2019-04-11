/*
  BC66 - API
    Created on: 01.01.2019
    Author: Georgi Angelov

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA   
 */

#ifndef API_NVDM_H_
#define API_NVDM_H_

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdarg.h>

typedef enum
{
    NVDM_STATUS_INVALID_PARAMETER = 0xFB,
    NVDM_STATUS_ITEM_NOT_FOUND = 0xFC,
    NVDM_STATUS_INSUFFICIENT_SPACE = 0xFD,
    NVDM_STATUS_INCORRECT_CHECKSUM = 0xFE,
    NVDM_STATUS_ERROR = 0xFF,
    NVDM_STATUS_OK = 0x0,
} nvdm_status_t;

typedef enum
{
    NVDM_DATA_ITEM_TYPE_RAW_DATA = 0x1,
    NVDM_DATA_ITEM_TYPE_STRING = 0x2,
} nvdm_data_item_type_t;

nvdm_status_t nvdm_read_data_item(const char *group_name, const char *data_item_name, uint8_t *buffer, uint32_t *size);
nvdm_status_t nvdm_write_data_item(const char *group_name, const char *data_item_name, nvdm_data_item_type_t type, const uint8_t *buffer, uint32_t size);

#endif /* API_NVDM_H_ */