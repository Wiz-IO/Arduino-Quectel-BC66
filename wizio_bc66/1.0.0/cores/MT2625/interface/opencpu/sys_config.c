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
 *   sys_config.c
 *
 * Project:
 * --------
 *   OpenCPU
 *
 * Description:
 * ------------
 *   The file is for some common system definition. Developer don't have to
 *   care.
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
#include "custom_feature_def.h"
#include "ql_type.h"
#include "ril.h"
#include "ql_system.h"
#include "custom_heap_cfg.h"

#define  DEFAULT_VALUE1   (200)
#define  DEFAULT_VALUE2   (30)


//const u32 HeapMemSize = HEAP_MEMSIZE;
//u8 OpenCPUHeapSpace[HEAP_MEMSIZE];


/*
*--------------------------
* Task Configuration
*--------------------------
* TaskStackSize:
*    The stack size of task. Range from 1K to 10K.
*    If there are any file operations to do in task, 
*    the stack size of this task must be set to at least 4K.
*****************************************************************/

#ifdef TASK_ID_DEF
#undef TASK_ID_DEF
#endif
#ifdef TASK_DEFINITION
#undef TASK_DEFINITION
#endif
#define TASK_FUNC_DECLARATION
#include "ql_common.h"
TASK_DEFINITION_BEGIN
#include "custom_task_cfg.h"
TASK_DEFINITION_END
#undef TASK_FUNC_DECLARATION



#ifdef TASK_FUNC_DECLARATION
#undef TASK_FUNC_DECLARATION
#endif
#ifdef TASK_ID_DEF
#undef TASK_ID_DEF
#endif
#define TASK_DEFINITION
#include "ql_common.h"
TASK_DEFINITION_BEGIN
#include "custom_task_cfg.h"
TASK_DEFINITION_END
#undef TASK_DEFINITION



#define GPIO_DEFINITION
#include "ql_common.h"
GPIO_DEFINITION_BEGIN
#include "custom_gpio_cfg.h"
GPIO_DEFINITION_END
#undef GPIO_DEFINITION
