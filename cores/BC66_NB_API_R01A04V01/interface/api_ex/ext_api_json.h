/*
 * ext_api_json.h
 *
 *  Created on: 17.10.2018
 *      Author: Georgi Angelov
 */

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdarg.h>


typedef struct cJSON {
	struct cJSON *next;
	struct cJSON *prev;
	struct cJSON *child;
	int type;
	uint8_t * valuestring;
	int valueint;
	double valuedouble;
	uint8_t * string;
} cJSON __attribute__((aligned(8)));

cJSON * cJSON_New_Item(void);
char * cJSON_strdup(const char * str);
void cJSON_free(void *ptr);
void cJSON_Delete(cJSON *c);
char * cJSON_Print(cJSON *item);
void cJSON_AddItemToArray(cJSON *array, cJSON *item);
void cJSON_AddItemToObject(cJSON *object, const char *string, cJSON *item);
cJSON * cJSON_CreateString(const char *string);
cJSON * cJSON_CreateObject(void);
