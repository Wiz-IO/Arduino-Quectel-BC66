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
 *   ril_tuil.h 
 *
 * Project:
 * --------
 *   OpenCPU
 *
 * Description:
 * ------------
 *   The file is for some useful definitions and APIs in common.
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
#ifndef __RIL_UTIL_H__
#define __RIL_UTIL_H__
#include "ql_type.h"

typedef enum {
    CHAR_0 = '0',
    CHAR_9 = '9',
    CHAR_A = 'A',
    CHAR_F = 'F',
    END_OF_STR = '\0'
}Enum_Char;
#define IS_NUMBER(alpha_char)   \
    (((alpha_char >= CHAR_0) && (alpha_char <= CHAR_9) ) ? 1 : 0)

extern s32  Ql_StrPrefixMatch(const char* str, const char *prefix);
extern bool Ql_HexStrToInt(u8 *str, u32 *val);
extern char* Ql_StrToUpper(char* str);
/******************************************************************************
* Function:     Ql_RIL_FindString
*  
* Description:
*                This function is used to match string within a specified length.
*                This function is very much like strstr.
*
* Parameters:    
*                line:  
*                    [in]The address of the string.
*                len:   
*                    [in]The length of the string.
*                str:   
*                    [in]The specified item which you want to look for in the string.
*
* Return:  
                The function returns a pointer to the located string,
                or a  null  pointer  if  the specified string is not found.
******************************************************************************/
extern char* Ql_RIL_FindString(char *line, u32 len,char *str);

/******************************************************************************
* Function:     Ql_RIL_FindLine
*  
* Description:
*                This function is used to find the specified character line by line.
*                for example,if you want to find "OK", In fact, we think that you are
*                looking for <CR><LF>OK<CR><LF>,<CR>OK<CR> or <LF>OK<LF>.
*
*
* Parameters:    
*                line:  
*                    [in]The address of the string.
*                len:   
*                    [in]The length of the string.
*                str:   
*                    [in]The specified item which you want to look for in the string.
*
* Return:  
                The function returns a pointer to the located string,
                or a  null  pointer  if  the specified string is not found.
******************************************************************************/
extern char* Ql_RIL_FindLine(char *line, u32 len,char *str);

#endif
