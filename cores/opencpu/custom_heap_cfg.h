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
 *   custom_heap_cfg.h
 *
 * Project:
 * --------
 *   OpenCPU
 *
 * Description:
 * ------------
 *   The file intends for heap space definition of OpenCPU application. 
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
#ifndef __CUSTOM_HEAP_CFG_H__
#define __CUSTOM_HEAP_CFG_H__

/*========================================================================
| 
| Heap Configuration.
|------------------
| Predefine a block of memory, and the o.s will allocate the memory from 
| the predefined memory when calling Ql_MEM_Alloc().
| Min value is 1, and max value depends one the max memory available.
| Unit in byte.
\=========================================================================*/
/*========================================================================
| 
| Note.
|------------------
| This method is no longer used On the new platform,the o.s will allocate 
| the memory from the system memory when calling Ql_MEM_Alloc().
| The size of the "system memory about 300KB.
| Unit in byte.
\=========================================================================*/

//#define HEAP_MEMSIZE (300 * 1024)

#endif //__CUSTOM_HEAP_CFG_H__
