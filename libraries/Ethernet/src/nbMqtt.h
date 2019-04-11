#include <interface.h>
#include <WString.h>
#include <IPAddress.h>

#define DEBUG_MQTT DBG

class nbMqtt
{
  public:
    ~nbMqtt()
    {
        stop();
        free(tx);
        free(rx);
    }

    nbMqtt(size_t size = 64)
    {
        if (size > 1024)
            size = 1024;
        if (0 == size)
            size = 64;
        tx = (uint8_t *)malloc(size);
        rx = (uint8_t *)malloc(size);
        memset(&n, 0, sizeof(MqttNetwork));
        memset(&c, 0, sizeof(MqttClient));
    }

    //typedef void (*mqtt_on_disconnect)(void);
    //mqtt_on_disconnect onDisconnect;
    static void on_disconnect_callback(MqttNetwork *p)
    {
        DEBUG_MQTT("[MQTT] Disconnect\n");
    }

    int begin()
    {
        if (NULL == tx || NULL == rx || c.isconnected)
            return -1;
        memset(&n, 0, sizeof(MqttNetwork));
        memset(&c, 0, sizeof(MqttClient));
        memset(&connectData, 0, sizeof(MQTTPacket_connectData));
        connectData.MQTTVersion = 3;
        connectData.struct_id[0] = 'M';
        connectData.struct_id[1] = 'Q';
        connectData.struct_id[2] = 'T';
        connectData.struct_id[3] = 'C';
        options();
        n.mqttread = mqtt_read;
        n.mqttwrite = mqtt_write;
        n.disconnect = mqtt_disconnect;
        NewNetwork(&n);
        n.on_disconnect_callback = on_disconnect_callback;
        return 0;
    }

    bool isConnected()
    {
        return c.isconnected;
    }

    int disconnect(bool full = false)
    {
        if (c.isconnected)
        {
            DEBUG_MQTT("[MQTT] MQTTDisconnect\n");
            return MQTTDisconnect(&c);
        }
        if (full)
            n.disconnect(&n);
        return 0;
    }

    void will(MQTTPacket_willOptions *will, uint8_t willFlag = 0)
    {
        if (will)
        {
            memset(&connectData.will, 0, sizeof(MQTTPacket_willOptions));
            memcpy(&connectData.will, will, sizeof(MQTTPacket_willOptions));
            connectData.willFlag = willFlag;
        }
    }

    void options(uint16_t keepAliveSeconds = 60, uint8_t cleansession = 1)
    {
        connectData.keepAliveInterval = keepAliveSeconds;
        connectData.cleansession = cleansession;
    }

    int client(String client_id, String name, String pass)
    {
        return client((const char *)client_id.c_str(), (const char *)name.c_str(), (const char *)pass.c_str());
    }

    int client(const char *client_id, const char *name = NULL, const char *pass = NULL)
    {
        int res;
        if (NULL == client_id)
            return -1;
        else
            connectData.clientID.cstring = (char *)client_id;
        if (NULL == name)
            connectData.username.cstring = (char *)"n";
        else
            connectData.username.cstring = (char *)name;
        if (NULL == pass)
            connectData.password.cstring = (char *)"p";
        else
            connectData.password.cstring = (char *)pass;
        return 0;
    }

    int connect(IPAddress ip, unsigned int port, unsigned int command_timeout_ms = 1000)
    {
        char host[64];
        if (4 != sprintf(host, "%d.%d.%d.%d", ip[3], ip[2], ip[1], ip[0]))
            return -1;
        char prt[16];
        if (1 != sprintf(prt, "%u", port))
            return -1;
        return connect((const char *)host, (const char *)prt, command_timeout_ms);
    }

    int connect(const char *host, const char *port, unsigned int command_timeout_ms = 1000)
    {
        int res = -1;
        if (command_timeout_ms < 100)
            command_timeout_ms = 100;
        if (host && port && tx && rx)
        {
            res = ConnectNetwork(&n, (char *)host, (char *)port);
            DEBUG_MQTT("[MQTT] ConnectNetwork: %d\n", res);
            if (0 == res)
            {
                MQTTClient(&c, &n, command_timeout_ms, tx, 1024, rx, 1024);
                res = MQTTConnect(&c, &connectData);
            }
        }
        DEBUG_MQTT("[MQTT] MQTTConnect: %d\n", res);
        return res;
    }

    int publish(String topic, String str, QoS qos = QOS0)
    {
        return publish((const char *)topic.c_str(), (const char *)str.c_str(), qos);
    }

    int publish(const char *topic, const char *str, QoS qos = QOS0)
    {
        int res = -1;
        if (c.isconnected && topic && str)
        {
            MQTTMessage m;
            memset(&m, 0, sizeof(MQTTMessage));
            m.payload = (void *)str;
            m.payloadlen = strlen(str);
            m.qos = qos;
            res = MQTTPublish(&c, topic, &m);
        }
        DEBUG_MQTT("[MQTT] MQTTPublish: %d\n", res);
        return res;
    }

    int publish(const char *topic, MQTTMessage *message)
    {
        int res = -1;
        if (c.isconnected && message && topic)
            int res = MQTTPublish(&c, topic, message);
        DEBUG_MQTT("[MQTT] MQTTPublish: %d\n", res);
        return res;
    }

    int subscribe(String topic, messageHandler onMessage, QoS qos = QOS0)
    {
        return subscribe((const char *)topic.c_str(), onMessage, qos);
    }

    int subscribe(const char *topic, messageHandler onMessage, QoS qos = QOS0)
    {
        int res = -1;
        if (c.isconnected && onMessage && topic)
            res = MQTTSubscribe(&c, topic, qos, onMessage);
        DEBUG_MQTT("[MQTT] MQTTSubscribe: %d\n", res);
        return res;
    }

    int unsubscribe(String topic)
    {
        return unsubscribe((const char *)topic.c_str());
    }

    int unsubscribe(const char *topic)
    {
        int res = -1;
        if (c.isconnected && topic)
            res = MQTTUnsubscribe(&c, topic);
        DEBUG_MQTT("[MQTT] MQTTSubscribe: %d\n", res);
        return res;
    }

    int yield(uint32_t ms = 1000)
    {
        int res = -1;
        if (c.isconnected)
        {
            if (ms < 100)
                ms = 100;
            res = MQTTYield(&c, ms);
        }
        return res;
    }

  private:
    uint8_t *tx;
    uint8_t *rx;
    MqttNetwork n;
    MqttClient c;
    MQTTPacket_connectData connectData;
};