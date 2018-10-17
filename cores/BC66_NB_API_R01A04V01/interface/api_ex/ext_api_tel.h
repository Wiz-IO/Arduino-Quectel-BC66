/*
 * ext_api_tel.h
 *
 *  Created on: 17.10.2018
 *      Author: Georgi Angelov
 */

#ifndef EXT_API_TEL_H_
#define EXT_API_TEL_H_

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

typedef enum {
	TEL_CONN_MGR_RET_OK = 0x0,
	TEL_CONN_MGR_RET_ERROR = 0xFF,
	TEL_CONN_MGR_RET_WOULDBLOCK = 0xFE,
	TEL_CONN_MGR_RET_IS_HOLD = 0xFD,
	TEL_CONN_MGR_RET_DUPLICATION = 0xFC,
	TEL_CONN_MGR_RET_NOT_FOUND = 0xFB,
	TEL_CONN_MGR_RET_INVALID_PARAM = 0xFA,
	TEL_CONN_MGR_RET_LIMIT_RESOURCE = 0xF9,
	TEL_CONN_MGR_RET_NOT_ENOUGH_MEMORY = 0xF8,
	TEL_CONN_MGR_RET_INCOMPATIBLE = 0xF7,
	TEL_CONN_MGR_RET_WRONG_STATE = 0xF6,
	TEL_CONN_MGR_RET_UNKNOWN = 0xF5,
	TEL_CONN_MGR_RET_CANCELED = 0xF4,
} tel_conn_mgr_ret_enum;

typedef enum {
	TEL_CONN_MGR_BEARER_TYPE_NONE = 0x0,
	TEL_CONN_MGR_BEARER_TYPE_NBIOT = 0x1,
	TEL_CONN_MGR_BEARER_TYPE_MAX = 0x2,
} tel_conn_mgr_bearer_type_enum;

typedef	enum {
	TEL_CONN_MGR_SIM_ID_NONE = 0x0,
	TEL_CONN_MGR_SIM_ID_1 = 0x1,
	TEL_CONN_MGR_SIM_ID_MAX = 0x2,
} tel_conn_mgr_sim_id_enum;

typedef	enum  {
	TEL_CONN_MGR_PDP_TYPE_NONE = 0x0,
	TEL_CONN_MGR_PDP_TYPE_IP = 0x1,
	TEL_CONN_MGR_PDP_TYPE_IPV6 = 0x2,
	TEL_CONN_MGR_PDP_TYPE_IPV4V6 = 0x3,
	TEL_CONN_MGR_PDP_TYPE_NIDD = 0x4,
	TEL_CONN_MGR_PDP_TYPE_MAX = 0x5,
} tel_conn_mgr_pdp_type_enum;

typedef enum {
	TEL_CONN_MGR_INFO_TYPE_NONE = 0x0,
	TEL_CONN_MGR_INFO_TYPE_ACTIVATION = 0x1,
	TEL_CONN_MGR_INFO_TYPE_ACTIVE_DEACTIVATION = 0x2,
	TEL_CONN_MGR_INFO_TYPE_PASSIVE_DEACTIVATION = 0x3,
	TEL_CONN_MGR_INFO_TYPE_MAX = 0x4,
} tel_conn_mgr_info_type_enum;

typedef enum {
	TEL_CONN_MGR_ERR_CAUSE_NONE = 0x0,
	TEL_CONN_MGR_ERR_CAUSE_UNKNOWN = 0x1,
	TEL_CONN_MGR_ERR_CAUSE_INIT_FAILED = 0x2,
	TEL_CONN_MGR_ERR_CAUSE_MODEM_EXCEPTION = 0x3,
	TEL_CONN_MGR_ERR_CAUSE_AT_CMD_EXCEPTION = 0x4,
	TEL_CONN_MGR_ERR_CAUSE_NW_DETACH = 0x5,
	TEL_CONN_MGR_ERR_CAUSE_ME_DETACH = 0x6,
	TEL_CONN_MGR_ERR_CAUSE_NW_DEACT = 0x7,
	TEL_CONN_MGR_ERR_CAUSE_ME_DEACT = 0x8,
	TEL_CONN_MGR_ERR_CAUSE_NW_REGISTRATION_FAILED = 0x9,
	TEL_CONN_MGR_ERR_CAUSE_DEACT_REQ = 0xA,
	TEL_CONN_MGR_ERR_CAUSE_ACT_REQ = 0xB,
	TEL_CONN_MGR_ERR_CAUSE_TIMEOUT = 0xC,
	TEL_CONN_MGR_ERR_CAUSE_PDP_TYPE_NOT_SUPPORTED = 0xD,
	TEL_CONN_MGR_ERR_CAUSE_PDP_TYPE_NOT_COMPATIBLE = 0xE,
	TEL_CONN_MGR_ERR_CAUSE_MAX = 0xF,
} tel_conn_mgr_err_cause_enum;

typedef uint8_t tel_conn_mgr_bool;
typedef int * tel_conn_mgr_register_handle_t;
typedef void * tel_conn_mgr_queue_hdl_t;
typedef void (*tel_conn_mgr_cb)(unsigned int, tel_conn_mgr_info_type_enum, tel_conn_mgr_bool, tel_conn_mgr_err_cause_enum, tel_conn_mgr_pdp_type_enum);

tel_conn_mgr_register_handle_t tel_conn_mgr_register_callback(tel_conn_mgr_cb callback);
tel_conn_mgr_ret_enum tel_conn_mgr_deactivate(unsigned int app_id);
tel_conn_mgr_ret_enum tel_conn_mgr_activate_int(
		tel_conn_mgr_bearer_type_enum bearer_type,
		tel_conn_mgr_sim_id_enum sim_id,
		tel_conn_mgr_pdp_type_enum pdp_type,
		char *apn,
		char *username,
		char *password,
		tel_conn_mgr_queue_hdl_t queue_hdl,
		void *reg_hdl,
		unsigned int *app_id,
		tel_conn_mgr_pdp_type_enum *activated_pdp_type
);

#endif /* EXT_API_TEL_H_ */
