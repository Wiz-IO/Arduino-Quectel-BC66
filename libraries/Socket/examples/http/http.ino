#include "Socket.h"

Socket soc;
char CMD_BAND[] = "AT+QBAND=1,3\n";
#define APN_NAME  "iot-test"
#define APN_USER  "user"
#define APN_PASS  "pass"
#define HOST    "wizio.eu"
#define PORT    80
sockaddr_in ADDR = { 0 };

void setup() {
  int led = 1, rc = 0, count = 0;
  Serial.begin(115200);
  Serial.println("[APP] Socket Example");
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, 1);
  analogOpen(0, 5, 200);
  while (dev.state[RIL_READY] != 1) {
    delay(200); // wait RIL
    digitalWrite(LED_BUILTIN, ++led ^ 1);
  }
  LOG("[IMEI] %s\n", dev.imei);
  rc = Ql_RIL_SendATCmd((char*) CMD_BAND, strlen(CMD_BAND), NULL, NULL, 1000); // Select LTE Band 3
  LOG("[BAND] %s, rc = %d\n", CMD_BAND, rc);
  while (dev.state[URC_STATE_NW_EGPRS] != 1) {
    delay(100); // wait Narrow Band (CEREG=1)
    digitalWrite(LED_BUILTIN, ++led ^ 1);
  }
  while (OK != pdp_act(APN_NAME, APN_USER, APN_PASS, 5 * 1000)) {
    delay(1000);
    if(++count > 120) // my bad signal
      Ql_Reset(0);
  }
  LOG("[APP] Narrow Band Level: %d,\n", receiveLevel());
}


char data[] = "GET /iot.php HTTP/1.1\r\nHost:" HOST "\r\n\r\n";
void loop() {
  static int count = 0;
  int rc, rb, timeout = 0;

  /* resolve host name */
  if (0 == ADDR.sin_addr.s_addr) {
    rc = resolveAddress(HOST, &ADDR);
    if (rc > 0) {
      ADDR.sin_port = lwip_htons(PORT);
      LOG("[APP] DNS wizio.eu = %u.%u.%u.%u:%d\n",
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

  LOG("[SOC] Conecting...\n");
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
    } while (++timeout < 100); // 100*100  mSec timeout
    end: soc.stop();
    LOG("\n[SOC] Close\n");
  } else {
    LOG("[SOC] ERROR\n");
  }
  LOG("[APP] waithing...\n");
  digitalWrite(LED_BUILTIN, ++count ^ 1);

//MQTT:
  //MqttBegin();
  //delay(30 * 1000);
  delay(60 * 1000);
}
