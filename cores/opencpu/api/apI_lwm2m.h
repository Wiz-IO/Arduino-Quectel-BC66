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

#ifndef API_LWM2M_H_
#define API_LWM2M_H_

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdarg.h>
#include <time.h>
#include "lwip/lwipopts.h"
#include "lwip/sockets.h"
#include "lwip/netdb.h"
#include "lwip/inet.h"

typedef enum
{
    STATE_INITIAL = 0x0,
    STATE_BOOTSTRAP_REQUIRED = 0x1,
    STATE_BOOTSTRAPPING = 0x2,
    STATE_REGISTER_REQUIRED = 0x3,
    STATE_REGISTERING = 0x4,
    STATE_READY = 0x5,
} lwm2m_client_state_t;

typedef enum
{
    BINDING_UNKNOWN = 0x0,
    BINDING_U = 0x1,
    BINDING_UQ = 0x2,
    BINDING_S = 0x3,
    BINDING_SQ = 0x4,
    BINDING_US = 0x5,
    BINDING_UQS = 0x6,
} lwm2m_binding_t;

typedef enum
{
    STATE_DEREGISTERED = 0x0,
    STATE_REG_PENDING = 0x1,
    STATE_REGISTERED = 0x2,
    STATE_REG_FAILED = 0x3,
    STATE_REG_UPDATE_PENDING = 0x4,
    STATE_REG_UPDATE_NEEDED = 0x5,
    STATE_REG_FULL_UPDATE_NEEDED = 0x6,
    STATE_DEREG_PENDING = 0x7,
    STATE_BS_HOLD_OFF = 0x8,
    STATE_BS_INITIATED = 0x9,
    STATE_BS_PENDING = 0xA,
    STATE_BS_FINISHING = 0xB,
    STATE_BS_FINISHED = 0xC,
    STATE_BS_FAILING = 0xD,
    STATE_BS_FAILED = 0xE,
} lwm2m_status_t;

typedef enum
{
    CLIENT_MODE = 0x0,
    SERVER_MODE = 0x1,
} lwm2m_mode_t;

typedef enum
{
    LWM2M_NOTIFY_TYPE_REGING = 0x0,
    LWM2M_NOTIFY_TYPE_REG = 0x1,
    LWM2M_NOTIFY_TYPE_OBSERVE = 0x2,
    LWM2M_NOTIFY_TYPE_UPDATE = 0x3,
    LWM2M_NOTIFY_TYPE_UPDATE_CONFIRM = 0x4,
    LWM2M_NOTIFY_TYPE_PING = 0x5,
    LWM2M_NOTIFY_TYPE_DEREGING = 0x6,
    LWM2M_NOTIFY_TYPE_DEREG = 0x7,
    LWM2M_NOTIFY_TYPE_SEND = 0x8,
    LWM2M_NOTIFY_TYPE_SEND_CONFIRM = 0x9,
    LWM2M_NOTIFY_TYPE_RECVRSP = 0xA,
    LWM2M_NOTIFY_TYPE_RECVRSP_CONFIRM = 0xB,
    LWM2M_NOTIFY_TYPE_PSM = 0xC,
    LWM2M_NOTIFY_TYPE_LWSTATUS = 0xD,
} lwm2m_notify_type_t;

typedef enum
{
    LWM2M_NOTIFY_CODE_SUCCESS = 0x0,
    LWM2M_NOTIFY_CODE_PSM_STATUS_CHANGED = 0x0,
    LWM2M_NOTIFY_CODE_LWM2M_SESSION_INVALID = 0x0,
    LWM2M_NOTIFY_CODE_TIMEOUT = 0x1,
    LWM2M_NOTIFY_CODE_PACKET_NOT_SENT = 0x2,
    LWM2M_NOTIFY_CODE_RST = 0x9,
    LWM2M_NOTIFY_CODE_BAD_REQUEST = 0xA,
    LWM2M_NOTIFY_CODE_FORBIDDEN = 0xD,
    LWM2M_NOTIFY_CODE_NOT_FOUND = 0xE,
    LWM2M_NOTIFY_CODE_PRECONDITION_FAILED = 0x16,
} lwm2m_notify_code_t;

typedef enum
{
    LWM2M_TYPE_UNDEFINED = 0x0,
    LWM2M_TYPE_OBJECT = 0x1,
    LWM2M_TYPE_OBJECT_INSTANCE = 0x2,
    LWM2M_TYPE_MULTIPLE_RESOURCE = 0x3,
    LWM2M_TYPE_STRING = 0x4,
    LWM2M_TYPE_OPAQUE = 0x5,
    LWM2M_TYPE_INTEGER = 0x6,
    LWM2M_TYPE_FLOAT = 0x7,
    LWM2M_TYPE_BOOLEAN = 0x8,
    LWM2M_TYPE_OBJECT_LINK = 0x9,
} lwm2m_data_type_t;

typedef struct
{
    uint8_t *block1buffer;
    size_t block1bufferSize;
    uint16_t lastmid;
} lwm2m_block1_data_t __attribute__((aligned(4)));

typedef struct _lwm2m_server_
{
    struct _lwm2m_server_ *next;
    uint16_t secObjInstID;
    uint16_t shortID;
    time_t lifetime;
    time_t registration;
    lwm2m_binding_t binding;
    void *sessionH;
    lwm2m_status_t status;
    char *location;
    uint8_t dirty;
    lwm2m_block1_data_t *block1Data;
} lwm2m_server_t;

typedef struct _lwm2m_list_t
{
    struct _lwm2m_list_t *next;
    uint16_t id;
} lwm2m_list_t __attribute__((aligned(4)));

typedef struct lwm2m_data
{
    lwm2m_data_type_t type;
    uint16_t id;
    union {
        uint8_t asBoolean;
        int64_t asInteger;
        double asFloat;
        struct
        {
            size_t length;
            uint8_t *buffer;
        } asBuffer;
        struct
        {
            size_t count;
            struct lwm2m_data *array;
        } asChildren;
        struct
        {
            uint16_t objectId;
            uint16_t objectInstanceId;
        } asObjLink;
    } value;
} lwm2m_data_t;

struct lwm2m_object;
typedef uint8_t (*lwm2m_read_callback_t)(uint16_t, int *, lwm2m_data_t **, struct lwm2m_object *);
typedef uint8_t (*lwm2m_write_callback_t)(uint16_t, int, lwm2m_data_t *, struct lwm2m_object *);
typedef uint8_t (*lwm2m_execute_callback_t)(uint16_t, uint16_t, uint8_t *, int, struct lwm2m_object *);
typedef uint8_t (*lwm2m_create_callback_t)(uint16_t, int, lwm2m_data_t *, struct lwm2m_object *);
typedef uint8_t (*lwm2m_delete_callback_t)(uint16_t, struct lwm2m_object *);
typedef uint8_t (*lwm2m_discover_callback_t)(uint16_t, int *, lwm2m_data_t **, struct lwm2m_object *);

typedef struct lwm2m_object
{
    struct _lwm2m_object_t *next;
    uint16_t objID;
    lwm2m_list_t *instanceList;
    lwm2m_read_callback_t readFunc;
    lwm2m_write_callback_t writeFunc;
    lwm2m_execute_callback_t executeFunc;
    lwm2m_create_callback_t createFunc;
    lwm2m_delete_callback_t deleteFunc;
    lwm2m_discover_callback_t discoverFunc;
    void *userData;
} lwm2m_object_t;

typedef struct
{
    uint8_t flag;
    uint16_t objectId;
    uint16_t instanceId;
    uint16_t resourceId;
} lwm2m_uri_t;

typedef struct
{
    uint8_t toSet;
    uint8_t toClear;
    uint32_t minPeriod;
    uint32_t maxPeriod;
    double greaterThan;
    double lessThan;
    double step;
} lwm2m_attributes_t;

typedef struct lwm2m_watcher
{
    struct lwm2m_watcher *next;
    uint8_t active;
    uint8_t update;
    lwm2m_server_t *server;
    lwm2m_attributes_t *parameters;
    uint8_t token[8];
    size_t tokenLen;
    time_t lastTime;
    uint32_t counter;
    uint16_t lastMid;
    union {
        int64_t asInteger;
        double asFloat;
    } lastValue;
} lwm2m_watcher_t;

typedef struct _lwm2m_observed_
{
    struct lwm2m_observed_ *next;
    lwm2m_uri_t uri;
    lwm2m_watcher_t *watcherList;
} lwm2m_observed_t;

struct lwm2m_transaction;
typedef void (*lwm2m_transaction_callback_t)(struct lwm2m_transaction *, void *);

typedef struct lwm2m_transaction
{
    struct lwm2m_transaction *next;
    uint16_t mID;
    void *peerH;
    uint8_t ack_received;
    time_t response_timeout;
    uint8_t retrans_counter;
    time_t retrans_time;
    char objStringID[6];
    char instanceStringID[6];
    char resourceStringID[6];
    void *message;
    uint16_t buffer_len;
    uint8_t *buffer;
    lwm2m_transaction_callback_t callback;
    void *userData;
    void *contextP;
} lwm2m_transaction_t;

typedef uint8_t (*lwm2m_observer_callback_t)(uint16_t, uint16_t, lwm2m_uri_t *, void *);
typedef uint8_t (*lwm2m_parameter_callback_t)(lwm2m_uri_t *, lwm2m_attributes_t *, void *);
typedef void *(*lwm2m_connect_server_callback_t)(uint16_t, void *);
typedef void (*lwm2m_close_connection_callback_t)(void *, void *);
typedef void (*lwm2m_notify_callback_t)(lwm2m_notify_type_t, lwm2m_notify_code_t, uint16_t);

typedef struct
{
    lwm2m_client_state_t state;
    char *endpointName;
    char *msisdn;
    char *altPath;
    lwm2m_server_t *bootstrapServerList;
    lwm2m_server_t *serverList;
    lwm2m_object_t *objectList;
    lwm2m_observed_t *observedList;
    lwm2m_mode_t mode;
    uint16_t nextMID;
    lwm2m_transaction_t *transactionList;
    void *userData;
    uint8_t ext_reg_update;
    lwm2m_observer_callback_t observe_callback;
    void *observe_userdata;
    lwm2m_parameter_callback_t parameter_callback;
    lwm2m_connect_server_callback_t connect_server_callback;
    lwm2m_close_connection_callback_t close_connection_callback;
    lwm2m_notify_callback_t notify_callback;
} lwm2m_context_t;

typedef struct connection_s
{
    struct connection_s *next;
    int sock;
    struct sockaddr_in6 addr;
    size_t addrLen;
} connection_t;

typedef struct
{
    lwm2m_object_t *securityObjP;
    lwm2m_object_t *serverObject;
    int sock;
    connection_t *connList;
    int addressFamily;
} client_data_t;

lwm2m_context_t *lwm2m_init(void *data);
int lwm2m_configure(lwm2m_context_t *contextP, const char *endpointName, const char *msisdn, const char *altPath, uint16_t numObject, lwm2m_object_t **objectList);
int create_socket(const char *portStr, int addressFamily);
void init_value_change(lwm2m_context_t *lwm2m);

#endif /* API_LWM2M_H_ */