#include "main.h"

struct eeprom_data eeprom;

unsigned int __calculate_eeprom_checkum() {
  //
  unsigned char buffer[sizeof(eeprom_data)];
  CRC32 crc;

  // save old checksum
  unsigned int temp_checksum = eeprom.checksum;
  eeprom.checksum = 0;

  // copy eeprom data
  memcpy(buffer, &eeprom, sizeof(eeprom_data));

  for (unsigned int i = 0; i < sizeof(eeprom_data); i++) {
    crc.update(buffer[i]);
  }

  // restore old checksum
  eeprom.checksum = temp_checksum;
  return crc.finalize();
}

void save_eeprom() {
  eeprom.checksum = __calculate_eeprom_checkum();
  EEPROM.put(0, eeprom);
  EEPROM.commit();
}

void __default_eeprom() {
  eeprom = {};
  eeprom.sign = EEPROM_SIGNATURE;
  strcpy(eeprom.device_name, DEFAULT_DEVICE_NAME);
  eeprom.mqtt_server_port = 1883;
  eeprom.checksum = __calculate_eeprom_checkum();
}

bool __verify_eeprom() {
  unsigned int checksum = __calculate_eeprom_checkum();
  if ((eeprom.sign != EEPROM_SIGNATURE) || (eeprom.checksum != checksum)) {
#ifdef DEBUG
    Serial.printf("EEPROM NOK (want %08x has %08x)\n", eeprom.checksum,
                  checksum);
#endif
    return false;
  } else {
#ifdef DEBUG
    Serial.println("EEPROM OK");
#endif
    return true;
  }
}

void init_eeprom() {
  // init eeprom
  EEPROM.begin(sizeof(eeprom_data));

  // if there's valid eeprom config, load it
  EEPROM.get(0, eeprom);
  if (!__verify_eeprom()) {
    __default_eeprom();
  }
}