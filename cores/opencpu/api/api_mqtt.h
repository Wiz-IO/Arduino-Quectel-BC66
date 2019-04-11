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

#ifndef API_MQTT_H_
#define API_MQTT_H_

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdarg.h>
#include "api_ssl.h"

typedef enum
{
	QOS0 = 0x0,
	QOS1 = 0x1,
	QOS2 = 0x2,
} QoS;

typedef struct
{
	int len;
	uint8_t *data;
} MQTTLenString;

typedef struct
{
	char *cstring;
	MQTTLenString lenstring;
} MQTTString;

typedef struct
{
	QoS qos;
	uint8_t retained;
	uint8_t dup;
	uint16_t id;
	void *payload;
	size_t payloadlen;
} MQTTMessage;

typedef struct
{
	MQTTMessage *message;
	MQTTString *topicName;
} MessageData;

typedef struct
{
	const uint8_t *topicFilter;
	void (*fp)(MessageData *);
} MessageHandlers;

typedef void (*messageHandler)(MessageData *);

typedef struct
{
	uint8_t struct_id[4];
	int struct_version;
	MQTTString topicName;
	MQTTString message;
	uint8_t retained;
	uint8_t qos;
} MQTTPacket_willOptions __attribute__((aligned(4)));

typedef struct
{
	uint8_t struct_id[4];
	int struct_version;
	uint8_t MQTTVersion;
	MQTTString clientID;
	uint16_t keepAliveInterval;
	uint8_t cleansession;
	uint8_t willFlag;
	MQTTPacket_willOptions will;
	MQTTString username;
	MQTTString password;
} MQTTPacket_connectData;

typedef struct
{
	unsigned int systick_period;
	unsigned int end_time;
} mqttTimer;

typedef struct MqttNetwork
{
	int my_socket;
	int (*mqttread)(struct MqttNetwork *, uint8_t *, int, int);
	int (*mqttwrite)(struct MqttNetwork *, uint8_t *, int, int);
	void (*disconnect)(struct MqttNetwork *);
	void (*on_disconnect_callback)(struct MqttNetwork *);
	mbedtls_ssl_context ssl;
	mbedtls_net_context fd;
	mbedtls_ssl_config conf;
	mbedtls_x509_crt cacertl;
	mbedtls_x509_crt clicert;
	mbedtls_pk_context pkey;
} MqttNetwork;

typedef struct
{
	unsigned int next_packetid;
	unsigned int command_timeout_ms;
	size_t buf_size;
	size_t readbuf_size;
	uint8_t *buf;
	uint8_t *readbuf;
	unsigned int keepAliveInterval;
	uint8_t ping_outstanding;
	int isconnected;
	int isvalid;
	MessageHandlers messageHandlers[5];
	void (*defaultMessageHandler)(MessageData *);
	MqttNetwork *ipstack;
	mqttTimer ping_timer;
} MqttClient;

typedef enum
{
	CONNECT = 0x1,
	CONNACK = 0x2,
	PUBLISH = 0x3,
	PUBACK = 0x4,
	PUBREC = 0x5,
	PUBREL = 0x6,
	PUBCOMP = 0x7,
	SUBSCRIBE = 0x8,
	SUBACK = 0x9,
	UNSUBSCRIBE = 0xA,
	UNSUBACK = 0xB,
	PINGREQ = 0xC,
	PINGRESP = 0xD,
	DISCONNECT = 0xE,
} msgTypes;

#define MQTTPacket_willOptions_initializer                                  \
	{                                                                       \
		{'M', 'Q', 'T', 'W'}, 0, {NULL, {0, NULL}}, {NULL, {0, NULL}}, 0, 0 \
	}
#define MQTTPacket_connectData_initializer                         \
	{                                                              \
		{'M', 'Q', 'T', 'C'}, 0, 4, {NULL, {0, NULL}}, 60, 1, 0,   \
			MQTTPacket_willOptions_initializer, {NULL, {0, NULL}}, \
		{                                                          \
			NULL, { 0, NULL }                                      \
		}                                                          \
	}

void MQTTClient(MqttClient *c, MqttNetwork *MqttNetwork, unsigned int command_timeout_ms, uint8_t *buf, size_t buf_size, uint8_t *readbuf, size_t readbuf_size);
int MQTTConnect(MqttClient *c, MQTTPacket_connectData *options);
int MQTTDisconnect(MqttClient *c);
int MQTTSubscribe(MqttClient *c, const char *topicFilter, QoS qos, messageHandler messageHandler);
int MQTTUnsubscribe(MqttClient *c, const char *topicFilter);
int MQTTPublish(MqttClient *c, const char *topicName, MQTTMessage *message);
int MQTTYield(MqttClient *c, int timeout_ms);

int waitfor(MqttClient *c, int packet_type, mqttTimer *timer);
int cycle(MqttClient *c, mqttTimer *timer);
int keepalive(MqttClient *c);
int getNextPacketId(MqttClient *c);
int sendPacket(MqttClient *c, int length, mqttTimer *timer);
int readPacket(MqttClient *c, mqttTimer *timer);
int decodePacket(MqttClient *c, int *value, int timeout);
int deliverMessage(MqttClient *c, MQTTString *topicName, MQTTMessage *message);
uint8_t isTopicMatched(uint8_t *topicFilter, MQTTString *topicName);

void InitTimer(mqttTimer *timer);
unsigned int left_ms(mqttTimer *timer);
void countdown(mqttTimer *timer, unsigned int timeout);
void countdown_ms(mqttTimer *timer, unsigned int timeout);
uint8_t expired(mqttTimer *timer);

void mqtt_disconnect(MqttNetwork *n);
int mqtt_write(MqttNetwork *n, uint8_t *buffer, int len, int timeout_ms);
int mqtt_read(MqttNetwork *n, uint8_t *buffer, int len, int timeout_ms);

void NewNetwork(MqttNetwork *n);
int ConnectNetwork(MqttNetwork *n, char *addr, char *port);

//////////////////////////////////////////////////////////////////////////////////

typedef struct
{
	uint8_t is_used;
	uint8_t is_connected;
	uint32_t mqtt_id;
	MqttNetwork *network;
	MqttClient *client;
	messageHandler message_handler;
} mqtt_at_context_t;

// "+EMQDISCON: %d" ID
// "+EMQPUB: %d, \"%s\", %d, %d, %d, %d, \""

#endif /* API_MQTT_H_ */
