#include <Arduino.h>

/* APN
  is set/saved as default in NVDM (required once)
  AT*MCGDEFCONT="IP","apn_from_operator"

  Enable scrambling function (required once)
  AT+QSPCHSC=1  
*/

void setup()
{
  int t = millis();
  String imei, mcc_mnc, sim_imsi, sim_iccid, uid;
  Dev.noSleep(); // disable PSM sleep

  Serial.begin(115200);
  Serial.debug(); // enable debug for this port, DBG( work as printf )

  Serial.printf("Arduino      %s\n", Dev.getVersion());
  Dev.getImei(imei);
  Serial.printf("IMEI         %s\n", imei.c_str());
  Dev.getUid(uid);
  Serial.printf("UID          %s\n", uid.c_str());

  Dev.waitSimReady();

  Dev.getMccMnc(mcc_mnc);
  Serial.printf("MCCMNC       %s\n", mcc_mnc.c_str());
  Dev.getImsi(sim_imsi);
  Serial.printf("IMSI         %s\n", sim_imsi.c_str());
  Dev.getIccid(sim_iccid);
  Serial.printf("ICCID        %s\n", sim_iccid.c_str());

  Dev.waitCereg();
  delay(200); // must have some delay, afrer this time next values is available

  Serial.printf("Rx level     %d dbm\n", Dev.getReceiveLevel());
  Serial.printf("Rx quality   %d\n", Dev.getQuality());
  Serial.printf("Rx access    %d\n", Dev.getAccess());
  Serial.printf("Cell cid     %d\n", Dev.getCid());
  Serial.printf("Cell tac     %d\n", Dev.getTac());
  char mlts[322];
  Dev.getMlts(mlts, 322);
  Serial.printf("Cell mlts    %s\n", mlts);
  pinMode(LED, OUTPUT);
  digitalWrite(LED, 1);
  Serial.printf("Elapsed: %d mili seconds\n", millis() - t);
}

void loop()
{
  static int led = 0;
  delay(500);
  Serial.print(">");
  digitalWrite(LED, ++led & 1);
  /* loop must be state machine, dont make long delays */
}

/** RESULT **************************************************************
 * 
    Arduino      BC66NBR01A04
    IMEI         867997030026081
    UID          301C9C77F16D77679784E781D57CF751
    MCCMNC       28401
    IMSI         9284011911698783
    ICCID        89359011870169878300
    Rx level     -68 dbm
    Rx quality   0
    Rx access    6
    Cell cid     9610698
    Cell tac     199
    Cell mlts    "19/04/02,12:20:28+03", "DST +1 in use","A1 BG",0,"A1 BG",0,"+03"
    Elapsed: 2830 mili seconds

***************************************************************/