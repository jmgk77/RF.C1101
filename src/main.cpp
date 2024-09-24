#include "main.h"

void setup() {
#ifdef DEBUG
  Serial.begin(115200);
  delay(1000);
  Serial.println();
  Serial.println(String(DEFAULT_DEVICE_NAME) + " " + VERSION);
#endif

  init_eeprom();
  LittleFS.begin();

#ifdef DEBUG
  dump_esp8266();
  dump_eeprom();
  dump_fs();
#endif

  load_rf_codes();

  init_web();

  init_time();

  init_433();

  //***
}

RF_CODE code;

void loop() {
  handle_web();

  //***
}