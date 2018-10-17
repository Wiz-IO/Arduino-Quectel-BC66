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
 *   custom_task_cfg.h
 *
 * Project:
 * --------
 *   OpenCPU
 *
 * Description:
 * ------------
 *   The file intends for multi tasks definition of OpenCPU application. 
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

/**
 ******* TAST CONFIG START ********
 *----------------------------------
 * Task Id Name:
 *    Task id name is a totally customized name. Developer just define the name, and the system
 *    will automatically define and assign value.
 *
 * Task Stack Size:
 *    The stack size of task. Range from 1K to 10K.
 *    
 *
 * Default Value1(2):
 *    Developer doesn't have to specify the value, just use the default definition.
 */

/*----------------------------------------------------------------------------------------------------
 |        Task Entry Function | Task Id Name   | Task Stack Size (Bytes) | Default Value1 | Default Value2 |
 *----------------------------------------------------------------------------------------------------*/
TASK_ITEM(proc_main_task,       main_task_id,   10*1024, DEFAULT_VALUE1, DEFAULT_VALUE2)
TASK_ITEM(proc_reserved1,       reserved1_id,   5*1024, DEFAULT_VALUE1, DEFAULT_VALUE2)
TASK_ITEM(proc_reserved2,       reserved2_id,   5*1024, DEFAULT_VALUE1, DEFAULT_VALUE2)

//TASK_ITEM(proc_arduino,  subtask1_id, 10*1024, DEFAULT_VALUE1, DEFAULT_VALUE2)
//TASK_ITEM(proc_delay,    subtask2_id,    1024, DEFAULT_VALUE1, DEFAULT_VALUE2)

#ifdef __EXAMPLE_MULTITASK__
TASK_ITEM(proc_subtask1,  subtask1_id, 1*1024, DEFAULT_VALUE1, DEFAULT_VALUE2)
TASK_ITEM(proc_subtask2,  subtask2_id, 1*1024, DEFAULT_VALUE1, DEFAULT_VALUE2)
TASK_ITEM(proc_subtask3,  subtask3_id, 1*1024, DEFAULT_VALUE1, DEFAULT_VALUE2)
TASK_ITEM(proc_subtask4,  subtask4_id, 1*1024, DEFAULT_VALUE1, DEFAULT_VALUE2)
TASK_ITEM(proc_subtask5,  subtask5_id, 1*1024, DEFAULT_VALUE1, DEFAULT_VALUE2)
TASK_ITEM(proc_subtask6,  subtask6_id, 1*1024, DEFAULT_VALUE1, DEFAULT_VALUE2)
TASK_ITEM(proc_subtask7,  subtask7_id, 1*1024, DEFAULT_VALUE1, DEFAULT_VALUE2)
TASK_ITEM(proc_subtask8,  subtask8_id, 1*1024, DEFAULT_VALUE1, DEFAULT_VALUE2)
#endif




/**
 ******* TAST CONFIG END ********
 */
