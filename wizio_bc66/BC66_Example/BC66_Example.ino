/*
 * INO.cpp
 *  Example
 *  Created on: 02.10.2018
 *      Author: Georgi Angelov
 */
#include "Arduino.h"

static s32 imeiHandler(char* line, u32 len, void* userdata) {
  if (!userdata)
    return RIL_ATRSP_FAILED;
  if ( strlen(line) > 17)
    memcpy(userdata, &line[2], 15);
  if (strstr(line, "OK"))
    return RIL_ATRSP_SUCCESS;
  return RIL_ATRSP_CONTINUE; //continue wait
}

void get_imei() {
  char cmd[] = "AT+GSN\n";
  Ql_RIL_SendATCmd(cmd, strlen(cmd), imeiHandler, &dev.imei, 0);
}

void setup() {
  LOG("[APP] Georgi Angelov 2018\n");
  Serial.begin(115200);
  pinMode(0, OUTPUT);
  delay(2000); // wait ril

  get_imei();
  Serial.print("IMEI    : ");
  Serial.println(dev.imei);
  Serial.print("VERSION : ");
  Serial.println(dev.version);
}

void loop() {
  static int led_state = 0;
  int stat;
  if (0 == RIL_NW_GetEGPRSState(&stat)) {
    LOG("[APP] CEREG: %d\n", stat);
  }
  LOG("[APP] millis: %d mSec\n", millis());

  Serial.print("SERIAL LOOP: ");
  Serial.print(seconds());
  Serial.println(" seconds");

  for (int i = 0; i < 50; i++) {
    digitalWrite(0, ++led_state ^ 1);
    delay(50);
  }
  delay(5000);
}
