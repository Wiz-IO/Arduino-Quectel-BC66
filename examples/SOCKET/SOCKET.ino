/*
Created on: 08.10.2018
Author: Georgi Angelov
Note: The example is for extended API      
*/

#include "Socket.h"

Socket soc;

// Select LTE Band 3 (1800 MHz) or?
// First parameter is how many bands will be searched
// Next is valid bands: 1, 2, 3, 5, 8, 12, 13, 17, 18, 19, 20, 26, 28, 66
char CMD_BAND[] = "AT+QBAND=1,3\n";

// Set your APN
#define APN_NAME  "apn-name"
#define APN_USER  "apn-user-name"
#define APN_PASS  "apn-password"

// Site
#define HOST  "wizio.eu"
#define PORT  80
char data[] = "GET /iot.php HTTP/1.1\r\nHost:" HOST "\r\n\r\n";

void setup() {
  int led = 1, rc = 0;
  Serial.begin(115200);
  Serial.println("[APP] Socket Example HTTP GET");
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, 1);
  analogOpen(0, 5, 200);
  while (dev.state[RIL_READY] != 1) {
    delay(200); // wait RIL
    digitalWrite(LED_BUILTIN, ++led ^ 1);
  }

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
  while (OK != pdp_act(APN_NAME, APN_USER, APN_PASS, 5 * 1000))
    delay(5 * 1000);
}

void loop() {
  static sockaddr_in ADDR = { 0 };
  static int count = 0;
  int rc, rb, timeout = 0;
  LOG("[APP] Receive Level: %d,\n", receiveLevel());

  /* resolve host name */
  if (0 == ADDR.sin_addr.s_addr) {
    rc = resolveAddress(HOST, &ADDR);
    if (rc > 0) {
      ADDR.sin_port = lwip_htons(PORT);
      LOG("[APP] Resolved: " HOST " = %u.%u.%u.%u:%d\n",
          (unsigned int )(ADDR.sin_addr.s_addr & 0xFF),
          (unsigned int )(ADDR.sin_addr.s_addr & 0xFF00) >> 8,
          (unsigned int )(ADDR.sin_addr.s_addr & 0xFF0000) >> 16,
          (unsigned int )(ADDR.sin_addr.s_addr & 0xFF000000) >> 24, PORT);
    } else {
      LOG("[ERROR] Resolve address: %s", HOST);
      delay(10 * 1000);
      return;
    }
  }
  LOG("[SOC] Conecting: " HOST "\n");
  soc.connect(ADDR);
  if (soc) {
    LOG("[SOC] Conected: %d\n", count++);
    soc.write((uint8_t*) data, strlen(data)); // simple http get
    delay(1000);
    do {
      while (soc.available() > 0) {
        rb = soc.read(); // read byte
        if (rb > 0)
          Serial.print((char) rb); // print result
        else
          goto end;
      }
      delay(100);
    } while (++timeout < 100); // 100 * 100  mSec timeout
    end: 
    soc.stop();
    LOG("\n[SOC] Close\n");
  } else {
    LOG("[SOC] ERROR\n");
  }
  LOG("[APP] Waithing...\n");
  digitalWrite(LED_BUILTIN, ++count ^ 1);
  delay(60 * 1000);
}
