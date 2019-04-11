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

//// https://github.com/zhcg/linkit_sdk/tree/5c5fe1591e4fe2cf00d3234c82892406cee1d50c/middleware/third_party/cjson

#ifndef API_JSON_H_
#define API_JSON_H_

#include <string.h>
#include <stdio.h>
#include <math.h>  
#include <stdlib.h>
#include <float.h>
#include <limits.h>
#include <ctype.h>
#include <stdint.h>

#define CJSON_PUBLIC(type) type

/* project version */
#define CJSON_VERSION_MAJOR 1
#define CJSON_VERSION_MINOR 7
#define CJSON_VERSION_PATCH 1

/* cJSON Types: */
#define cJSON_Invalid (0)
#define cJSON_False 0
#define cJSON_True 1
#define cJSON_NULL 2
#define cJSON_Number 3
#define cJSON_String 4
#define cJSON_Array 5
#define cJSON_Object 6
#define cJSON_Raw 7 /* raw json */

#define cJSON_IsReference 256
#define cJSON_StringIsConst 512

typedef struct cJSON
{
	struct cJSON *next;
	struct cJSON *prev;
	struct cJSON *child;
	int type;
	char *valuestring;
	int valueint;
	double valuedouble;
	char *string;
} cJSON __attribute__((aligned(8)));

typedef int cJSON_bool;

void *cJSON_malloc(size_t sz);
void cJSON_free(void *ptr);
char *cJSON_strdup(const char *str);

cJSON *cJSON_New_Item(void);
void cJSON_Delete(cJSON *c);
char *cJSON_Print(cJSON *item);
void cJSON_AddItemToArray(cJSON *array, cJSON *item);
void cJSON_AddItemToObject(cJSON *object, const char *string, cJSON *item);
cJSON *cJSON_CreateString(const char *string);
cJSON *cJSON_CreateObject(void);
char *print_value(cJSON *item, int depth, int fmt);
char *print_string_ptr(const char *str);

extern cJSON *cJSON_Parse(const char *value);
extern char *cJSON_PrintUnformatted(cJSON *item);
extern int cJSON_GetArraySize(cJSON *array);
extern cJSON *cJSON_GetArrayItem(cJSON *array, int item);
extern cJSON *cJSON_GetObjectItem(cJSON *object, const char *string);
extern const char *cJSON_GetErrorPtr(void);
extern cJSON *cJSON_CreateNull(void);
extern cJSON *cJSON_CreateTrue(void);
extern cJSON *cJSON_CreateFalse(void);
extern cJSON *cJSON_CreateBool(int b);
extern cJSON *cJSON_CreateNumber(double num);
extern cJSON *cJSON_CreateString(const char *string);
extern cJSON *cJSON_CreateArray(void);
extern cJSON *cJSON_CreateObject(void);
extern cJSON *cJSON_CreateIntArray(const int *numbers, int count);
extern cJSON *cJSON_CreateFloatArray(const float *numbers, int count);
extern cJSON *cJSON_CreateDoubleArray(const double *numbers, int count);
extern cJSON *cJSON_CreateStringArray(const char **strings, int count);
extern void cJSON_AddItemToArray(cJSON *array, cJSON *item);
extern void cJSON_AddItemToObject(cJSON *object, const char *string, cJSON *item);
extern void cJSON_AddItemReferenceToArray(cJSON *array, cJSON *item);
extern void cJSON_AddItemReferenceToObject(cJSON *object, const char *string, cJSON *item);
extern cJSON *cJSON_DetachItemFromArray(cJSON *array, int which);
extern void cJSON_DeleteItemFromArray(cJSON *array, int which);
extern cJSON *cJSON_DetachItemFromObject(cJSON *object, const char *string);
extern void cJSON_DeleteItemFromObject(cJSON *object, const char *string);
extern void cJSON_ReplaceItemInArray(cJSON *array, int which, cJSON *newitem);
extern void cJSON_ReplaceItemInObject(cJSON *object, const char *string, cJSON *newitem);
extern cJSON *cJSON_Duplicate(cJSON *item, int recurse);
extern cJSON *cJSON_ParseWithOpts(const char *value, const char **return_parse_end, int require_null_terminated);
extern void cJSON_Minify(char *json);

/* Macros for creating things quickly. */
#define cJSON_AddNullToObject(object, name) cJSON_AddItemToObject(object, name, cJSON_CreateNull())
#define cJSON_AddTrueToObject(object, name) cJSON_AddItemToObject(object, name, cJSON_CreateTrue())
#define cJSON_AddFalseToObject(object, name) cJSON_AddItemToObject(object, name, cJSON_CreateFalse())
#define cJSON_AddBoolToObject(object, name, b) cJSON_AddItemToObject(object, name, cJSON_CreateBool(b))
#define cJSON_AddNumberToObject(object, name, n) cJSON_AddItemToObject(object, name, cJSON_CreateNumber(n))
#define cJSON_AddStringToObject(object, name, s) cJSON_AddItemToObject(object, name, cJSON_CreateString(s))
#define cJSON_SetIntValue(object, val) ((object) ? (object)->valueint = (object)->valuedouble = (val) : (val))

////////////////////////////////////////////

typedef enum
{
	JSMN_UNDEFINED = 0x0,
	JSMN_OBJECT = 0x1,
	JSMN_ARRAY = 0x2,
	JSMN_STRING = 0x3,
	JSMN_PRIMITIVE = 0x4,
} jsmntype_t;

typedef struct
{
	unsigned int pos;
	unsigned int toknext;
	int toksuper;
} jsmn_parser;

typedef struct
{
	jsmntype_t type;
	int start;
	int end;
	int size;
	int parent;
} jsmntok_t;

void jsmn_init(jsmn_parser *parser);
int jsmn_parse(jsmn_parser *parser, const char *js, uint32_t len, jsmntok_t *tokens, unsigned int num_tokens);
int tc_iot_json_find_token(const char *json, const jsmntok_t *root_token, int count, const char *path, char *result, int result_len);

int tc_iot_json_unescape(char *dest, int dest_len, const char *src, int src_len);
int tc_iot_unicode_to_utf8(char *output, int output_len, unsigned int code);
int tc_iot_jsoneq_len(const char *json, const jsmntok_t *tok, const char *s, int len);


#endif /* API_JSON_H_ */