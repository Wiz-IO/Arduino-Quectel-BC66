/*
 *  Created on: 08.10.2018
 *    Author: Georgi Angelov
 *      
 *  Show result: 
 *    http://quectel.slimfitdesign.com/nb-iot/mqtt/
 */

#include "Socket.h"

Socket soc;

// Select LTE Band 3 (1800 MHz) or? 
// First parameter is how many bands will be searched
// Next is valid bands: 1, 2, 3, 5, 8, 12, 13, 17, 18, 19, 20, 26, 28, 66
char CMD_BAND[] = "AT+QBAND=1,3\n"; 

void setup() {
  int led = 1, rc = 0;
  Serial.begin(115200);
  Serial.println("[APP] MQTT Simple Example");
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, 1);
  analogOpen(0, 5, 200);
  while (dev.state[RIL_READY] != 1) {
    delay(200); // wait RIL
    digitalWrite(LED_BUILTIN, ++led ^ 1);
  }
  LOG("[IMEI] %s\n", dev.imei); // used for MQTT ClientID
  rc = Ql_RIL_SendATCmd((char*) CMD_BAND, strlen(CMD_BAND), NULL, NULL, 1000); 
  LOG("[BAND] %s, rc = %d\n", CMD_BAND, rc);
  
  /* waithing for narrow band, CEREG=1 */
  while (dev.state[URC_STATE_NW_EGPRS] != 1) {
    delay(100); // wait connect to Narrow Band (URC value from CEREG = 1)
    digitalWrite(LED_BUILTIN, ++led ^ 1);
    if (led > 1000) {
      LOG("[ERROR] Bad Signal...\n");
      delay(10 * 1000);
      Ql_Reset(0);
    }
  }
  while (OK != pdp_act("apn_name", "apn_user", "apn_pass", 5 * 1000)) // <-------- write your APN
    delay(5 * 1000);
}

uint8_t tx[1024];
uint8_t rx[1024];
char payload[512];

void loop() {
  LOG("\n[APP] Narrow Band Level: %d,\n", receiveLevel());
  
  static int count = 0;
  int rc;
  MqttNetwork n = { 0 };
  MqttClient c = { 0 };
  MQTTPacket_connectData options = MQTTPacket_connectData_initializer;
  MQTTMessage message;
  n.mqttread = mqtt_read;
  n.mqttwrite = mqtt_write;
  n.disconnect = mqtt_disconnect;
  NewNetwork(&n);
  rc = ConnectNetwork(&n, (char*) "m15.cloudmqtt.com", (char*) "13717"); // or IP  "34.238.150.50"
  if (rc != 0) {
    LOG("[ERROR] ConnectNetwork( %d )\n", rc);
    goto END;
  }
  LOG("[APP] MQTT Connected\n");
  MQTTClient(&c, &n, 5000, tx, 1024, rx, 1024);
  options.MQTTVersion = 3;
  options.clientID.cstring = (char*) dev.imei;
  options.username.cstring = (char*) "cbimusme";
  options.password.cstring = (char*) "gc5-N2fucr_y";
  options.keepAliveInterval = 60;
  options.cleansession = 1;
  rc = MQTTConnect(&c, &options); // error?
  LOG("[API] MQTTConnect( %d )\n", rc);
  message.qos = QOS0;
  snprintf(payload, 256, "{\"text\":\"BC66 OpenCPU + Arduino = Love\",\"rssi\":\"%d dBm\",\"status\":\"connected\",\"ai\":\"%d mV\",\"di\":\"%s\"}\0",
           receiveLevel(),
           analogRead(0),
           ++count % 2 == 0 ? "ON" : "OFF"
          );
  message.payload = payload;
  message.payloadlen = strlen((char*) message.payload);
  rc = MQTTPublish(&c, (char*) "bc66-mqtt-demo", &message); // error?
  LOG("[APP] MQTTPublish( %d )\n", rc);
  MQTTDisconnect(&c);
  LOG("[APP] MQTT Disconnected\n");

END:
  LOG("[APP] Waithing...\n");
  delay(60 * 1000);
}
