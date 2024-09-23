#include "main.h"

char boot_time[32];

void init_time() {
  // get internet time (GMT-3)
  configTime("<-03>3", "pool.ntp.org");
  // repeat till get year past 2021...
  int retries = 600;
  while ((time(nullptr) < 1609459200) && (retries--)) {
#ifdef DEBUG
    Serial.print(".");
#endif
    delay(100);
  }

  // get boot time
  time_t t = time(NULL);
  strncpy(boot_time, ctime(&t), sizeof(boot_time));
#ifdef DEBUG
  Serial.print("Current date: ");
  Serial.print(boot_time);
#endif
}