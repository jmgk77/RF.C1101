#include "main.h"

void setup() {
#ifdef DEBUG
  Serial.begin(115200, SERIAL_8N1, SERIAL_TX_ONLY, 1);
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

  init_web();

  load_rf_codes();

  init_codes_manager();

  init_time();

  init_433();

  init_led();

  init_buttons();

  //***
}

void loop() {
  handle_web();

  handle_codes_manager();

  handle_buttons();

  //***
}