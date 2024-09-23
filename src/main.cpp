#include "main.h"

void setup() {
#ifdef DEBUG
  Serial.begin(115200);
  while (!Serial) {
  };
#endif

  init_eeprom();
  LittleFS.begin();

#ifdef DEBUG
  Serial.println();
  Serial.println(String(DEFAULT_DEVICE_NAME) + " " + VERSION);
  dump_esp8266();
  dump_eeprom();
  dump_fs();
#endif
}

void loop() {
  // put your main code here, to run repeatedly:
}
