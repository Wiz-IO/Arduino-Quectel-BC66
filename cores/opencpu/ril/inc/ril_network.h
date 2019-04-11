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
 *   ril_network.h 
 *
 * Project:
 * --------
 *   OpenCPU
 *
 * Description:
 * ------------
 *   The file declares some API functions, which are related to network, including
 *   SIM state, GSM/GPRS network state and signal strength, and so forth.
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
#ifndef __RIL_NETWORK_H__
#define __RIL_NETWORK_H__
#include "ql_type.h"

/****************************************************************************
 * Definition for SIM Card State
 ***************************************************************************/
typedef enum {
    SIM_STAT_NOT_INSERTED = 0,
    SIM_STAT_READY,
    SIM_STAT_PIN_REQ,
    SIM_STAT_PUK_REQ,
    SIM_STAT_PH_PIN_REQ,
    SIM_STAT_PH_PUK_REQ,
    SIM_STAT_PIN2_REQ,
    SIM_STAT_PUK2_REQ,
    SIM_STAT_BUSY,
    SIM_STAT_NOT_READY,
    SIM_STAT_UNSPECIFIED
 }Enum_SIMState;

/****************************************************************************
 * Definition for network State
 ***************************************************************************/
typedef enum {
    NW_STAT_NOT_REGISTERED = 0,    // Not register to network
    NW_STAT_REGISTERED,            // The normal network state
    NW_STAT_SEARCHING,             // Searching network
    NW_STAT_REG_DENIED,            // The register request is denied
    NW_STAT_UNKNOWN,
    NW_STAT_REGISTERED_ROAMING     //Registered and Roaming state
}Enum_NetworkState;

/******************************************************************************
* Function:     RIL_NW_GetGPRSState
*  
* Description:
*               This function gets the GPRS network register state. 
*
* Parameters:    
*               stat:
*                   [out]GPRS State.
* Return:  
*               One value of Enum_NetworkState: network register state code.
*               -1 : fail to get the network state.
******************************************************************************/
s32  RIL_NW_GetEGPRSState(s32 *stat);

#endif // __RIL_NETWORK_H__
