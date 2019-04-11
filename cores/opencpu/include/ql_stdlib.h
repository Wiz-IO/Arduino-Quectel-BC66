/*****************************************************************************
*  Copyright Statement:
*  --------------------
*  This software is protected by Copyright and the information contained
*  herein is confidential. The software may not be copied and the information
*  contained herein may not be used or disclosed except with the written
*  permission of Quectel Co., Ltd. 2013
*
*****************************************************************************/
/*****************************************************************************
 *
 * Filename:
 * ---------
 *   ql_stdlib.h 
 *
 * Project:
 * --------
 *   OpenCPU
 *
 * Description:
 * ------------
 *   this file provides some Standard library APIs
 *
 * Author:
 * -------
 * -------
 *
 *============================================================================
 *             HISTORY
 *----------------------------------------------------------------------------
 * 
 ****************************************************************************/
 

#ifndef __QL_STDLIB_H__
#define __QL_STDLIB_H__
#include "ql_type.h"

s32    Ql_atoi(const char* s);
double Ql_atof(const char* s);
void* Ql_memset(void* dest, u8 value, u32 size);
void* Ql_memcpy(void* dest, const void* src, u32 size);
s32   Ql_memcmp(const void* dest, const void*src, u32 size);
void* Ql_memmove(void* dest, const void* src, u32 size);
char* Ql_strcpy(char* dest, const char* src);
char* Ql_strncpy(char* dest, const char* src, u32 size);
char* Ql_strcat(char* s1, const char* s2);
char* Ql_strncat(char* s1, const char* s2, u32 size);
s32   Ql_strcmp(const char*s1, const char*s2);
s32   Ql_strncmp(const char* s1, const char* s2, u32 size);
char* Ql_strchr(const char* s1, s32 ch);
u32   Ql_strlen(const char* str);
char* Ql_strstr(const char* s1, const char* s2);
s32   Ql_toupper(s32 c);
s32   Ql_tolower(s32 c);
s32   Ql_isdigit(char c);
extern s32 (*Ql_sprintf)(char *, const char *, ...);
extern s32 (*Ql_snprintf)(char *, u32, const char *, ...);
extern s32 (*Ql_sscanf)(const char*, const char*, ...);
#endif  // __QL_STDLIB_H__
