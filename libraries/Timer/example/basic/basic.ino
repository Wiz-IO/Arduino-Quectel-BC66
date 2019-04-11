#include <GPTimer.h>

GPTimer T1 = GPTimer(TIMER_FAST); // this timer is independent of the task, only one for task
void onTimerFast(u32 timerId, void *param)
{
  static int state = 0;
  digitalWrite(LED, ++state ^ 1);
}

GPTimer T2 = GPTimer(TIMER_1); // for this timers loop() must be fast
void onTimer(u32 timerId, void *param)
{
  Serial.println("TIMER");
}

void setup()
{
  Dev.noSleep(); // disable PSM sleep
  Serial.begin(115200);
  Serial.debug(); // enable debug for this port, DBG( work as printf )
  Serial.printf("Arduino %s\n", Dev.getVersion());
  pinMode(LED, OUTPUT);
  digitalWrite(LED, 1);
  T1.start(200, 1, onTimerFast);
  T2.start(5000, 1, onTimer);
}

void loop()
{
  // some fast code or state machine
}