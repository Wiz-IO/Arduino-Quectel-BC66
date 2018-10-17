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
 *   ql_memory.h 
 *
 * Project:
 * --------
 *   OpenCPU
 *
 * Description:
 * ------------
 *   Memory APIs defines.
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


#ifndef __QL_MEMORY_H__
#define __QL_MEMORY_H__


/*****************************************************************
* Function:     Ql_MEM_Alloc 
* 
* Description:
*               Allocates memory with the specified size in the memory heap.
* Parameters:
*               Size: 
*                  [in]Number of bytes of memory to be allocated.
* Return:        
*               A pointer of void type to the allocated space.
*****************************************************************/
void* Ql_MEM_Alloc (u32 size);

/*****************************************************************
* Function:     Ql_MEM_Free 
* 
* Description:
*               Free memory 
* Parameters:
*               Ptr: 
*                  [in]Previously allocated memory block to be freed. 
* Return:        
*               none
*               
*****************************************************************/
void Ql_MEM_Free (void *ptr);

#endif  // End-of __QL_MEMORY_H__

