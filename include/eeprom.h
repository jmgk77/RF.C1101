#pragma once

#define EEPROM_SIGNATURE 'J'

struct eeprom_data {
  unsigned char sign = EEPROM_SIGNATURE;
  unsigned int checksum;
  //
  char device_name[32];
  char mqtt_server_ip[64];
  unsigned int mqtt_server_port;
  char mqtt_server_username[64];
  char mqtt_server_password[64];
};

void default_eeprom();
void save_eeprom();
void init_eeprom();