#include <Arduino.h>
#include <nbClient.h>
#include <PubSubClient.h> // INSTALL LIBRARY

nbClient tcp;
IPAddress server(0, 0, 0, 0); // your mqtt broker 

void callback(char *topic, byte *payload, unsigned int length)
{
  Serial.printf("[RECEIVE] (%s) %.*s\n", topic, length, payload);
}

PubSubClient client(server, 1883, callback, tcp);

void mqtt_setup()
{
  Serial.println("Test MQTT");
  if (client.connect("arduinoClient", "user", "pass"))
  {
    client.publish("outTopic", "hello world");
    Serial.println("publish...");
    client.subscribe("inTopic");
    Serial.println("subscribe...");
  }
}

void setup()
{
  String imei;
  Dev.noSleep();
  Serial.begin(115200);
  Serial.printf("Arduino %s\n", Dev.getVersion());
  pinMode(LED, OUTPUT);
  Dev.getImei(imei);
  Serial.printf("IMEI %s\n", imei.c_str());
  Dev.waitSimReady();
  Serial.println("Sim Ready");
  Dev.waitCereg();
  delay(200); // must
  Serial.println("Net Ready");
  mqtt_setup();
}

void loop()
{
  static int led = 0, cnt = 0;
  if (++cnt % 50 == 0)
  {
    digitalWrite(LED, ++led & 1);
    //Serial.print(".");
  }
  client.loop();
}

/*
  Arduino BC66NBR01A04
  IMEI 867997030026081
  Sim Ready
  Net Ready
  Test MQTT
  publish...
  subscribe...
  [RECEIVE] (inTopic) Hello World
  [RECEIVE] (inTopic) Test 1234
*/
