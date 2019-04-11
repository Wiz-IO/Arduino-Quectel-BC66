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

#ifndef API_RIL_H_
#define API_RIL_H_

#include <stdint.h>
#include <stddef.h>

typedef enum
{
    RIL_STATUS_INVALID_PARAM = 0xFE,
    RIL_STATUS_FAIL = 0xFF,
    RIL_STATUS_SUCCESS = 0x0,
} ril_status_t;

typedef enum
{
    RIL_EXECUTE_MODE = 0x0,
    RIL_ACTIVE_MODE = 0x1,
    RIL_READ_MODE = 0x2,
    RIL_TEST_MODE = 0x3,
} ril_request_mode_t;

typedef enum {
	RIL_URC_ID_START = 0x0,
	RIL_URC_ID_TEST = 0x1,
	RIL_URC_ID_CREG = 0x2,
	RIL_URC_ID_CTZR = 0x3,
	RIL_URC_ID_CGEV = 0x4,
	RIL_URC_ID_CGREG = 0x5,
	RIL_URC_ID_CEREG = 0x6,
	RIL_URC_ID_CCIOTOPT = 0x7,
	RIL_URC_ID_CEDRXS = 0x8,
	RIL_URC_ID_CSCON = 0x9,
	RIL_URC_ID_CPIN = 0xA,
	RIL_URC_ID_MLTS = 0xB,
	RIL_URC_ID_MSIMINS = 0xC,
	RIL_URC_ID_MGCOUNT = 0xD,
	RIL_URC_ID_MSMEXTRAUNSOL = 0xE,
	RIL_URC_ID_MMGI = 0xF,
	RIL_URC_ID_MSMPUKBLKD = 0x10,
	RIL_URC_ID_MODE = 0x11,
	RIL_URC_ID_MSTC = 0x12,
	RIL_URC_ID_MSTUD = 0x13,
	RIL_URC_ID_MCCST = 0x14,
	RIL_URC_ID_MCSIMLOCK = 0x15,
	RIL_URC_ID_MAPNURI = 0x16,
	RIL_URC_ID_MPLMNURI = 0x17,
	RIL_URC_ID_MPDI = 0x18,
	RIL_URC_ID_IDCFREQ = 0x19,
	RIL_URC_ID_MSQN = 0x1A,
	RIL_URC_ID_MATREADY = 0x1B,
	RIL_URC_ID_MATWAKEUP = 0x1C,
	RIL_URC_ID_MDPDNP = 0x1D,
	RIL_URC_ID_END = 0x1E,
	RIL_URC_ID_INVALID = 0x1E,
} ril_urc_id_t;

typedef enum {
	RIL_CMD_ID_CGMI = 0x1,
	RIL_CMD_ID_CGMM = 0x2,
	RIL_CMD_ID_CGMR = 0x3,
	RIL_CMD_ID_CGSN = 0x4,
	RIL_CMD_ID_CSCS = 0x5,
	RIL_CMD_ID_CIMI = 0x6,
	RIL_CMD_ID_CMUX = 0x7,
	RIL_CMD_ID_CR = 0x8,
	RIL_CMD_ID_CEER = 0x9,
	RIL_CMD_ID_CNUM = 0xA,
	RIL_CMD_ID_CREG = 0xB,
	RIL_CMD_ID_COPS = 0xC,
	RIL_CMD_ID_CLCK = 0xD,
	RIL_CMD_ID_CPWD = 0xE,
	RIL_CMD_ID_CPOL = 0xF,
	RIL_CMD_ID_CPLS = 0x10,
	RIL_CMD_ID_COPN = 0x11,
	RIL_CMD_ID_CFUN = 0x12,
	RIL_CMD_ID_CPIN = 0x13,
	RIL_CMD_ID_CSQ = 0x14,
	RIL_CMD_ID_CCLK = 0x15,
	RIL_CMD_ID_CSIM = 0x16,
	RIL_CMD_ID_CRSM = 0x17,
	RIL_CMD_ID_CMAR = 0x18,
	RIL_CMD_ID_CTZU = 0x19,
	RIL_CMD_ID_CTZR = 0x1A,
	RIL_CMD_ID_CGPIAF = 0x1B,
	RIL_CMD_ID_CPINR = 0x1C,
	RIL_CMD_ID_CSUS = 0x1D,
	RIL_CMD_ID_CESQ = 0x1E,
	RIL_CMD_ID_CMEE = 0x1F,
	RIL_CMD_ID_CGDCONT = 0x20,
	RIL_CMD_ID_CGATT = 0x21,
	RIL_CMD_ID_CGACT = 0x22,
	RIL_CMD_ID_CGDATA = 0x23,
	RIL_CMD_ID_CGPADDR = 0x24,
	RIL_CMD_ID_CGEREP = 0x25,
	RIL_CMD_ID_CGREG = 0x26,
	RIL_CMD_ID_CEREG = 0x27,
	RIL_CMD_ID_CGCONTRDP = 0x28,
	RIL_CMD_ID_CGDEL = 0x29,
	RIL_CMD_ID_CGAUTH = 0x2A,
	RIL_CMD_ID_CIPCA = 0x2B,
	RIL_CMD_ID_CPSMS = 0x2C,
	RIL_CMD_ID_CCIOTOPT = 0x2D,
	RIL_CMD_ID_CEDRXS = 0x2E,
	RIL_CMD_ID_CEDRXRDP = 0x2F,
	RIL_CMD_ID_CGAPNRC = 0x30,
	RIL_CMD_ID_CSCON = 0x31,
	RIL_CMD_ID_CRCES = 0x32,
	RIL_CMD_ID_E = 0x33,
	RIL_CMD_ID_I = 0x34,
	RIL_CMD_ID_O = 0x35,
	RIL_CMD_ID_Q = 0x36,
	RIL_CMD_ID_S3 = 0x37,
	RIL_CMD_ID_S4 = 0x38,
	RIL_CMD_ID_S5 = 0x39,
	RIL_CMD_ID_S7 = 0x3A,
	RIL_CMD_ID_S10 = 0x3B,
	RIL_CMD_ID_V = 0x3C,
	RIL_CMD_ID_X = 0x3D,
	RIL_CMD_ID_Z = 0x3E,
	RIL_CMD_ID_AF = 0x3F,
	RIL_CMD_ID_GCAP = 0x40,
	RIL_CMD_ID_S25 = 0x41,
	RIL_CMD_ID_MLTS = 0x42,
	RIL_CMD_ID_MSIMINS = 0x43,
	RIL_CMD_ID_MSPN = 0x44,
	RIL_CMD_ID_MUNSOL = 0x45,
	RIL_CMD_ID_MGCOUNT = 0x46,
	RIL_CMD_ID_MGSINK = 0x47,
	RIL_CMD_ID_MCGDEFCONT = 0x48,
	RIL_CMD_ID_MGTCSINK = 0x49,
	RIL_CMD_ID_MSACL = 0x4A,
	RIL_CMD_ID_MLACL = 0x4B,
	RIL_CMD_ID_MWACL = 0x4C,
	RIL_CMD_ID_MDACL = 0x4D,
	RIL_CMD_ID_MSMEXTRAINFO = 0x4E,
	RIL_CMD_ID_MSMEXTRAUNSOL = 0x4F,
	RIL_CMD_ID_MSMSTATUS = 0x50,
	RIL_CMD_ID_MMGI = 0x51,
	RIL_CMD_ID_MMGRW = 0x52,
	RIL_CMD_ID_MMGSC_PDU = 0x53,
	RIL_CMD_ID_MMGSC_TXT = 0x54,
	RIL_CMD_ID_MUPIN = 0x55,
	RIL_CMD_ID_MUAPP = 0x56,
	RIL_CMD_ID_MSST = 0x57,
	RIL_CMD_ID_MABORT = 0x58,
	RIL_CMD_ID_MCAL = 0x59,
	RIL_CMD_ID_MNON = 0x5A,
	RIL_CMD_ID_MOPL = 0x5B,
	RIL_CMD_ID_MMUX = 0x5C,
	RIL_CMD_ID_MROUTEMMI = 0x5D,
	RIL_CMD_ID_MCEERMODE = 0x5E,
	RIL_CMD_ID_MFTRCFG = 0x5F,
	RIL_CMD_ID_HVER = 0x60,
	RIL_CMD_ID_MODE = 0x61,
	RIL_CMD_ID_SYSINFO = 0x62,
	RIL_CMD_ID_SYSCONFIG = 0x63,
	RIL_CMD_ID_CARDMODE = 0x64,
	RIL_CMD_ID_SPN = 0x65,
	RIL_CMD_ID_MSTLOCK = 0x66,
	RIL_CMD_ID_MSTPD = 0x67,
	RIL_CMD_ID_MSTMODE = 0x68,
	RIL_CMD_ID_MSTICREC = 0x69,
	RIL_CMD_ID_MSTICIMG = 0x6A,
	RIL_CMD_ID_MSTGC = 0x6B,
	RIL_CMD_ID_MSTCR = 0x6C,
	RIL_CMD_ID_MSTMS = 0x6D,
	RIL_CMD_ID_MSTEV = 0x6E,
	RIL_CMD_ID_MICCID = 0x6F,
	RIL_CMD_ID_MHOMENW = 0x70,
	RIL_CMD_ID_MCSIMLOCK = 0x71,
	RIL_CMD_ID_MEMMREEST = 0x72,
	RIL_CMD_ID_MAPNURI = 0x73,
	RIL_CMD_ID_MPLMNURI = 0x74,
	RIL_CMD_ID_MPDI = 0x75,
	RIL_CMD_ID_MNBIOTDT = 0x76,
	RIL_CMD_ID_MNBIOTRAI = 0x77,
	RIL_CMD_ID_MNVMQ = 0x78,
	RIL_CMD_ID_MNVMAUTH = 0x79,
	RIL_CMD_ID_MNVMW = 0x7A,
	RIL_CMD_ID_MNVMR = 0x7B,
	RIL_CMD_ID_MNVMGET = 0x7C,
	RIL_CMD_ID_MNVMIVD = 0x7D,
	RIL_CMD_ID_MNVMRSTONE = 0x7E,
	RIL_CMD_ID_MNVMRST = 0x7F,
	RIL_CMD_ID_MNVMMDNQ = 0x80,
	RIL_CMD_ID_MNVMMDR = 0x81,
	RIL_CMD_ID_MNVMMDC = 0x82,
	RIL_CMD_ID_IDCFREQ = 0x83,
	RIL_CMD_ID_IDCPWRBACKOFF = 0x84,
	RIL_CMD_ID_IDCTX2GPS = 0x85,
	RIL_CMD_ID_MCALDEV = 0x86,
	RIL_CMD_ID_MATWAKEUP = 0x87,
	RIL_CMD_ID_MBAND = 0x88,
	RIL_CMD_ID_MENGINFO = 0x89,
	RIL_CMD_ID_MFRCLLCK = 0x8A,
	RIL_CMD_ID_MSPCHSC = 0x8B,
	RIL_CMD_ID_MDPDNP = 0x8C,
	RIL_CMD_ID_CUSTOM_CMD = 0x8D,
	RIL_CMD_ID_CUSTOM_CMD_URC = 0x8E,
	RIL_CMD_ID_INVALID = 0x8F,
} ril_cmd_id_t;

typedef enum {
	RIL_MSG_REQUEST = 0x0,
	RIL_MSG_RESPONSE = 0x1,
	RIL_MSG_URC = 0x2,
	RIL_MSG_CHANNEL_ENABLED = 0x3,
	RIL_MSG_CHANNEL_DISABLED = 0x4,
	RIL_MSG_SEND_COMPLETE = 0x5,
	RIL_MSG_DATA_CHANNEL_RESERVED = 0x6,
	RIL_MSG_DATA_CHANNEL_UNRESERVED = 0x7,
} ril_message_type_t;

typedef enum {
	RIL_PARAM_TYPE_INTEGER = 0x0, RIL_PARAM_TYPE_STRING = 0x1, RIL_PARAM_TYPE_VOID = 0x2, RIL_PARAM_TYPE_HEXINTEGER = 0x3, RIL_PARAM_TYPE_DIGITAL_STRING = 0x4, RIL_PARAM_TYPE_NONE = 0x5,
} ril_param_type_t;

typedef enum {
	RIL_CMD_TYPE_AT_DATA = 0x1, RIL_CMD_TYPE_URC = 0x2,
} ril_cmd_type_t;

typedef enum {
	RIL_CHANNEL_STATE_READY = 0x0, RIL_CHANNEL_STATE_BUSY = 0x1, RIL_CHANNEL_STATE_UNAVAILABLE = 0x2, RIL_CHANNEL_STATE_WAIT_TO_WAKEUP = 0x3,
} ril_channel_state_t;

typedef enum
{
    RIL_RESULT_CODE_UNDEFINED = 0xFFFC,
    RIL_RESULT_CODE_RESPONSE_FORMAT_ERROR = 0xFFFD,
    RIL_RESULT_CODE_RESPONSE_TIMEOUT = 0xFFFE,
    RIL_RESULT_CODE_MUX_SEND_ERROR = 0xFFFF,
    START_OF_CME_ERROR_CODES = 0x0,
    RIL_CME_PHONE_FAILURE = 0x0,
    RIL_CME_NO_MS_CONNECTION = 0x1,
    RIL_CME_PHONE_LINK_RESERVED = 0x2,
    RIL_CME_OPERATION_NOT_ALLOWED = 0x3,
    RIL_CME_OPERATION_NOT_SUPPORTED = 0x4,
    RIL_CME_PH_SIM_PIN_REQUIRED = 0x5,
    RIL_CME_FSIM_PIN_REQUIRED = 0x6,
    RIL_CME_FSIM_PUK_REQUIRED = 0x7,
    RIL_CME_SIM_NOT_INSERTED = 0xA,
    RIL_CME_SIM_PIN_REQUIRED = 0xB,
    RIL_CME_SIM_PUK_REQUIRED = 0xC,
    RIL_CME_SIM_FAILURE = 0xD,
    RIL_CME_SIM_BUSY = 0xE,
    RIL_CME_SIM_WRONG = 0xF,
    RIL_CME_INCORRECT_PASSWORD = 0x10,
    RIL_CME_SIM_PIN2_REQUIRED = 0x11,
    RIL_CME_SIM_PUK2_REQUIRED = 0x12,
    RIL_CME_MEMORY_FULL = 0x14,
    RIL_CME_INVALID_INDEX = 0x15,
    RIL_CME_NOT_FOUND = 0x16,
    RIL_CME_MEMORY_FAILURE = 0x17,
    RIL_CME_LONG_TEXT = 0x18,
    RIL_CME_INVALID_TEXT_CHARS = 0x19,
    RIL_CME_LONG_DIALSTRING = 0x1A,
    RIL_CME_INVALID_DIALSTRING_CHARS = 0x1B,
    RIL_CME_NO_NETWORK_SERVICE = 0x1E,
    RIL_CME_NETWORK_TIMEOUT = 0x1F,
    RIL_CME_EMERGENCY_ONLY = 0x20,
    RIL_CME_NET_PIN_REQUIRED = 0x28,
    RIL_CME_NET_PUK_REQUIRED = 0x29,
    RIL_CME_NETSUB_PIN_REQUIRED = 0x2A,
    RIL_CME_NETSUB_PUK_REQUIRED = 0x2B,
    RIL_CME_NETPROV_PIN_REQUIRED = 0x2C,
    RIL_CME_NETPROV_PUK_REQUIRED = 0x2D,
    RIL_CME_CORPORATE_PIN_REQUIRED = 0x2E,
    RIL_CME_CORPORATE_PUK_REQUIRED = 0x2F,
    RIL_CME_HIDDEN_KEY_REQUIRED = 0x30,
    RIL_CME_UNKNOWN = 0x64,
    RIL_CME_ILLEGAL_MS = 0x67,
    RIL_CME_ILLEGAL_ME = 0x6A,
    RIL_CME_PSD_SERVICES_NOT_ALLOWED = 0x6B,
    RIL_CME_PLMN_NOT_ALLOWED = 0x6F,
    RIL_CME_LOCATION_AREA_NOT_ALLOWED = 0x70,
    RIL_CME_ROAMING_NOT_ALLOWED = 0x71,
    RIL_CME_SERVICE_OPTION_NOT_SUPPORTED = 0x84,
    RIL_CME_SERVICE_OPTION_NOT_SUBSCRIBED = 0x85,
    RIL_CME_SERVICE_OPTION_OUT_OF_ORDER = 0x86,
    RIL_CME_UNSPECIFIED_PSD_ERROR = 0x94,
    RIL_CME_PDP_AUTHENTIFICATION_ERROR = 0x95,
    RIL_CME_INVALID_MOBILE_CLASS = 0x96,
    RIL_CME_LAST_PDN_DISCONNECTION_NOT_ALLOWED = 0x97,
    START_OF_RESULT_CODES = 0x2710,
    RIL_RESULT_CODE_OK = 0x2710,
    RIL_RESULT_CODE_CONNECT = 0x2711,
    RIL_RESULT_CODE_RING = 0x2712,
    RIL_RESULT_CODE_NO_CARRIER = 0x2713,
    RIL_RESULT_CODE_ERROR = 0x2714,
    RIL_RESULT_CODE_INV = 0x2715,
    RIL_RESULT_CODE_NO_DIALTONE = 0x2716,
    RIL_RESULT_CODE_BUSY = 0x2717,
    RIL_RESULT_CODE_NO_ANSWER = 0x2718,
    RIL_RESULT_CODE_PROCEEDING = 0x2719,
    RIL_RESULT_CODE_FCERROR = 0x271A,
    RIL_RESULT_CODE_CME_ERROR = 0x271B,
    RIL_RESULT_CODE_CMS_ERROR = 0x271C,
    RIL_RESULT_CODE_CIS_ERROR = 0x271D,
    RIL_RESULT_CODE_NULL = 0x271E,
    END_OF_RESULT_CODES = 0x271F,
} ril_result_code_t;

typedef struct {
	ril_param_type_t data_type;
	union {
		int32_t val;
		uint8_t *str;
	} data;
} ril_param_desc_t;

typedef struct ril_param_node_s {
	ril_param_desc_t param;
	struct ril_param_node_s *next;
} ril_param_node_t;

typedef struct {
	ril_message_type_t msg;
	void *buf;
	uint32_t len;
} ril_message_t;

typedef struct {
	int32_t channel_id;
	ril_cmd_type_t type;
	ril_channel_state_t state;
	uint32_t curr_request_id;
	uint32_t curr_request_mode;
	void *usr_rsp_cb;
	void *usr_data;
	uint32_t timestamp;
	uint32_t elapsed_time;
	uint8_t tx_buf[1032];
	uint8_t *tx_buf_ptr;
	int32_t tx_pos;
	uint8_t rx_buf[1032];
	uint8_t *rx_buf_ptr;
	int32_t rx_pos;
	uint8_t *rx_long_str_ptr;
	int32_t rx_long_str_len;
	int32_t reserved;
} ril_channel_cntx_t;

typedef enum
{
    RIL_NONE = 0x0,
    RIL_PM = 0x1,
    RIL_MM = 0x2,
    RIL_SMS = 0x4,
    RIL_SIM = 0x8,
    RIL_PD = 0x10,
    RIL_EM = 0x20,
    RIL_STK = 0x40,
    RIL_MUX = 0x80,
    RIL_PB = 0x100,
    RIL_ALL = 0xFFFFFFFF,
} ril_func_group_t;

typedef int32_t (*ril_cmd_urc_hdlr_t)(ril_urc_id_t, char *, uint32_t);

typedef struct
{
    ril_urc_id_t event_id;
    char *cmd_head;
    ril_func_group_t func_group;
    ril_cmd_urc_hdlr_t urc_hdlr;
} ril_urc_cmd_item_t;

typedef ril_status_t ril_event_callback_t(ril_urc_id_t, void *, uint32_t);
ril_status_t ril_register_event_callback(uint32_t group_mask, ril_event_callback_t callback);

ril_status_t ril_request_send(ril_request_mode_t mode, ril_cmd_id_t cmd_id, ril_param_node_t *param, void * callback, void * user_data);
ril_status_t ril_request_send_via_channel(ril_request_mode_t mode, ril_cmd_id_t cmd_id, ril_param_node_t *param, void * callback, void * user_data, int32_t channel_id);
ril_channel_cntx_t * ril_get_channel(uint32_t channel_id);
int ril_alloc_channel(ril_cmd_type_t cmd_type);
int ril_free_channel(uint32_t channel_id);
int ril_param_list_create(ril_param_node_t **list_head);
int ril_param_list_delete(int32_t result);
int ril_param_list_add_int(const ril_param_node_t *list_head, int32_t param);
int ril_param_list_add_hexint(const ril_param_node_t *list_head, int32_t param);
int ril_param_list_add_string(const ril_param_node_t *list_head, char *param, uint8_t quotation_mark);
int ril_param_list_add_void(const ril_param_node_t *list_head);
int ril_param_list_add_int_optional(const ril_param_node_t *list_head, int32_t param, int32_t can_be_empty);
int ril_param_list_add_hexint_optional(const ril_param_node_t *list_head, int32_t param, int32_t can_be_empty);
int ril_param_list_add_string_optional(const ril_param_node_t *list_head, char *param, int32_t can_be_empty);
int ril_param_list_add_digital_string_optional(const ril_param_node_t *list_head, char *param, int32_t can_be_empty);
void ril_send_message(ril_message_type_t msg, void *buf, uint32_t len);

typedef struct
{
    ril_cmd_id_t cmd_id;
    ril_request_mode_t mode;
    ril_result_code_t res_code;
    void *cmd_param;
    void *user_data;
    char *test_mode_str;
    uint32_t test_mode_str_len;
} ril_cmd_response_t;
typedef int32_t (*ril_cmd_response_callback_t)(ril_cmd_response_t *);

////////////////////////////////////////////////////////////////////////////
// AT TOK
////////////////////////////////////////////////////////////////////////////

int str_starts_with(const char *line, const char *prefix);
void skip_white_space(char **p_cur);
void skip_next_comma(char **p_cur);
//char * next_tok(char **p_cur);
int at_tok_start(char **p_cur);
int at_tok_nextint_base(char **p_cur, int *p_out, int base, int uns);
int at_tok_nextint(char **p_cur, int *p_out);
int at_tok_nexthexint(char **p_cur, int *p_out);
int at_tok_nextbinint(char **p_cur, int *p_out);
int at_tok_nextstr(char **p_cur, char **p_out);
char * at_get_one_line(char **p_cur);
char at_get_next_packet(const char *buf);

#endif /* API_RIL_H_ */
