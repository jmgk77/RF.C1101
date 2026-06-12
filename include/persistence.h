#pragma once

struct config_data {
  char device_name[32];
  char mqtt_server_ip[64];
  unsigned int mqtt_server_port;
  char mqtt_server_username[64];
  char mqtt_server_password[64];
};

#define CODES_FILE_NAME "codes.csv"
#define CONFIG_FILE_NAME "config.json"

void load_rf_codes();
void save_rf_codes();

void default_config();
void save_config();
void init_config();
