#ifndef API_FOTA_H_
#define API_FOTA_H_

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

typedef enum
{
    FOTA_HTTP_DL_OK = 0x0,
    FOTA_HTTP_DL_ERROR = 0x1,
    FOTA_HTTP_DL_CANCELLED = 0x2,
    FOTA_HTTP_DL_NO_ENOUGH_MEMORY = 0x3,
    FOTA_HTTP_DL_INCOMPLETED = 0x4,
    FOTA_HTTP_DL_DATA_NOT_FOUND = 0x5,
    FOTA_HTTP_DL_HTTPCLIENT_ERROR_PARSE = 0x6,
    FOTA_HTTP_DL_HTTPCLIENT_UNRESOLVED_DNS = 0x7,
    FOTA_HTTP_DL_HTTPCLIENT_ERROR_PRTCL = 0x8,
    FOTA_HTTP_DL_HTTPCLIENT_CLOSED = 0x9,
    FOTA_HTTP_DL_HTTPCLIENT_ERROR_CONN = 0xA,
} fota_http_dl_result_t;

typedef enum
{
    FOTA_HTTP_DL_DATA_EVENT = 0x0,
    FOTA_HTTP_DL_DATA_TOTAL_LEN_EVENT = 0x1,
} fota_http_dl_event_t;

typedef enum
{
    FOTA_OK = 0x0,
    FOTA_COMMON_ERROR = 0x1,
    FOTA_BUSY = 0x2,
    FOTA_ERROR_LOADING_HEADER = 0x3,
    FOTA_ERROR_HEADER_FORMAT = 0x4,
    FOTA_ERROR_LOADING_BODY = 0x5,
    FOTA_ERROR_WRITE_TO_PARTITON = 0x6,
    FOTA_ERROR_LOADING_CHECKSUM = 0x7,
    FOTA_ERROR_CHECKSUM_VERIFY = 0x8,
    FOTA_ERROR_LOADING_MARKER = 0x9,
    FOTA_ERROR_ERASE_MARKER = 0xA,
    FOTA_ERROR_SEC_CHECK_ERROR = 0xB,
    FOTA_ERROR_DOWNLOAD_FAILED = 0xC,
    FOTA_ERROR_NW_DEACTIVE = 0xD,
    FOTA_ERROR_OPERATION_INVALID = 0xE,
    FOTA_ERROR_PARAMETER_INVALID = 0xF,
    FOTA_ERROR_WRONG_PACKAGE = 0x10,
    FOTA_ERROR_SW_VERSION_INVALID = 0x11,
    FOTA_ERROR_BROM_ERROR = 0x12,
    FOTA_ERROR_DA_ERROR = 0x13,
    FOTA_ERROR_NW_ACTIVEING = 0x14,
} fota_result_t;

typedef enum
{
    FOTA_MAIN_BIN = 0x1,
    FOTA_GNSS_BIN = 0x2,
    FOTA_ALL_BIN = 0x3,
    FOTA_INVLID_BIN = 0xFF,
} fota_image_t;

typedef enum
{
    FOTA_MSG_DOWNLOAD_START_IND = 0x0,
    FOTA_MSG_DOWNLOAD_PROGRESS_IND = 0x1,
    FOTA_MSG_DOWNLOAD_RESULT_IND = 0x2,
    FOTA_MSG_UPGRADE_START_IND = 0x3,
    FOTA_MSG_UPGRADE_PROGRESS_IND = 0x4,
    FOTA_MSG_UPGRADE_RESULT_IND = 0x5,
} fota_msg_event_t;

typedef enum
{
    FOTA_BL_ERROR_NONE = 0x0,
    FOTA_BL_ERROR_LOADING_HEADER = 0x1,
    FOTA_BL_ERROR_HEADER_FORMAT = 0x2,
    FOTA_BL_ERROR_LOADING_BODY = 0x3,
    FOTA_BL_ERROR_WRITE_TO_PARTITON = 0x4,
    FOTA_BL_ERROR_LOADING_CHECKSUM = 0x5,
    FOTA_BL_ERROR_CHECKSUM_VERIFY = 0x6,
    FOTA_BL_ERROR_LOADING_MARKER = 0x7,
    FOTA_BL_ERROR_ERASE_MARKER = 0x8,
    FOTA_BL_ERROR_SEC_CHECK_ERROR = 0x9,
} fota_bl_status_t;

typedef enum
{
    FOTA_NW_DEACTIVED = 0x0,
    FOTA_NW_ACTIVED = 0x1,
    FOTA_NW_ACTIVING = 0x2,
} fota_nw_status_t;

typedef struct
{
    uint32_t total_len;
    uint32_t received_len;
    uint32_t erased_len;
    uint32_t md5_len;
    uint8_t *p_md5_data;
} fota_download_context_t;

typedef enum
{
    FOTA_IDLE = 0x0,
    FOTA_DOWNLOAD = 0x1,
    FOTA_UPGRADE = 0x2,
    FOTA_REBOOTING = 0x3,
    FOTA_REGISTER_NW = 0x4,
} fota_state_t;

typedef enum
{
    FOTA_MSG_DOWNLOAD_IMAGE_REQ = 0x0,
    FOTA_MSG_TRIGGER_UPGRADE_REQ = 0x1,
    FOTA_MSG_TRIGGER_REBOOT = 0x2,
} fota_internal_msg_event_t;

typedef struct
{
    uint8_t *p_buf;
    uint32_t buf_len;
} fota_http_dl_data_event_t;

typedef struct
{
    int recv_len;
    int total_len;
} fota_http_dl_totalLen_event_t;

typedef uint8_t (*fota_http_dl_event_call_back_t)(fota_http_dl_event_t, const void *);
typedef uint8_t (*fota_http_dl_set_parameter_t)(void *, const unsigned char *, fota_http_dl_event_call_back_t);

typedef fota_http_dl_result_t (*fota_http_dl_run_t)(void *);
typedef void (*fota_http_dl_cancel_t)(void *);

typedef struct
{
    fota_http_dl_set_parameter_t fota_http_dl_set_parameter;
    fota_http_dl_run_t fota_http_dl_run;
    fota_http_dl_cancel_t fota_http_dl_cancel;
} fota_http_dl_t;

typedef fota_http_dl_t fota_http_dl_t_0;

typedef union {
    uint32_t progress;
    fota_result_t fota_result;
} fota_msg_event_info_t;

typedef uint32_t fota_event_handle_t;

typedef void (*fota_event_indication_t)(fota_msg_event_t, fota_msg_event_info_t *);

typedef struct
{
    fota_image_t image_type;
    uint32_t uri_len;
    uint8_t *p_uri;
} fota_image_info_t;

typedef union {
    fota_image_t image_type;
    fota_image_info_t image_info;
} fota_event_info_union;

typedef struct
{
    fota_internal_msg_event_t event;
    fota_event_info_union fota_event_info;
} fota_internal_msg_t;

typedef struct
{
    uint32_t m_ver;
    uint32_t m_error_code;
    uint32_t m_behavior;
    uint32_t m_is_read;
    unsigned char m_marker[32];
    uint32_t reserved[4];
} fota_update_info_t;

typedef struct
{
    uint32_t m_bin_offset;
    uint32_t m_bin_start_addr;
    uint32_t m_bin_length;
    uint32_t m_partition_length;
    uint32_t m_sig_offset;
    uint32_t m_sig_length;
    uint32_t m_is_compressed;
    uint32_t m_version_info[16];
    uint32_t m_bin_type;
    uint8_t m_bin_reserved[4];
} fota_bin_info_t;

typedef struct
{
    uint32_t m_magic_ver; //0x4D4D4D
    uint32_t m_bin_num;
    fota_bin_info_t m_bin_info[4];
} fota_header_info_t;

#if 0

typedef struct
{
    SemaphoreHandle_t fota_mutex;
    QueueHandle_t msg_queue;
    fota_state_t current_state;
    fota_event_indication_t event_ind[8];
} fota_context_t;

typedef struct
{
    void *this;
    fota_http_dl_t_0 downloader_handler;
    unsigned char *p_http_url;
    fota_http_dl_event_call_back_t caller_callback;
    uint8_t cancelled;
    httpclient_t http_client;
} fota_http_dl_context_t;

typedef struct __attribute__((aligned(4)))
{
    fota_nw_status_t nw_status;
    uint8_t cpin_ready;
    tel_conn_mgr_pdp_type_enum pdp_type;
    tel_conn_mgr_pdp_type_enum actived_pdp_type;
    unsigned char *apn;
    unsigned char *username;
    unsigned char *password;
    tel_conn_mgr_register_handle_t reg_handle;
    uint32_t app_id;
    uint8_t need_auto_connect_nw;
} fota_nw_manager_context_t;
#endif

#endif