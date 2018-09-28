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
  delay(1000); // wait ril
  get_imei();
  LOG("[APP] IMEI: %s\n", dev.imei);

}

void loop() {
  int stat;
  if (0 == RIL_NW_GetEGPRSState(&stat)) {
    LOG("[APP] CEREG: %d\n", stat);
  }

  LOG("[APP] millis: %d\n", millis());
  delay(5000);
}
