#include "main.h"

extern std::vector<RF_CODE> rf433_codes;

struct config_data config;

void load_rf_codes() {
#ifdef DEBUG
  Serial.print("LOAD CODES ");
#endif
  char buffer[256];
  char buffer2[32];
  RF_CODE c;
  File file = LittleFS.open(CODES_FILE_NAME, "r");
  if (file) {
    // clear old cdes
    rf433_codes.clear();
    // discart header
    file.readBytesUntil('\n', buffer, sizeof(buffer));
    while (file.available()) {
      memset(buffer, 0, sizeof(buffer));
      memset(buffer2, 0, sizeof(buffer2));
      file.readBytesUntil('\n', buffer, sizeof(buffer));
      sscanf(buffer, "%lu,%u,%u,%u,%31[^\n]", &c.rf433_code, &c.rf433_protocol,
             &c.rf433_length, &c.rf433_delay, buffer2);
      c.rf433_name = (String)buffer2;
      rf433_codes.push_back(c);
    }
    file.close();
#ifdef DEBUG
    Serial.println(rf433_codes.size());
  } else {
    Serial.println("NOK");
#endif
  }
}

void save_rf_codes() {
#ifdef DEBUG
  Serial.printf("SAVE CODES %d ", rf433_codes.size());
#endif
  char buffer[256];
  File file = LittleFS.open("codes.csv", "w");
  if (file) {
    file.write("Code, Protocol, Length, Delay, Name\n");
    for (auto& c : rf433_codes) {
      sprintf(buffer, "%lu,%u,%u,%u,%s\n", c.rf433_code, c.rf433_protocol,
              c.rf433_length, c.rf433_delay, c.rf433_name.c_str());
      file.print(buffer);
    }
    file.close();
#ifdef DEBUG
    Serial.println("OK");
  } else {
    Serial.println("NOK");
#endif
  }
}

void default_config() {
  // Zero-initialize all fields
  config = {};
  strlcpy(config.device_name, DEFAULT_DEVICE_NAME, sizeof(config.device_name));
  config.mqtt_server_port = 1883;
}

void save_config() {
  // save json
  JsonDocument doc;
  doc["device_name"] = config.device_name;
  doc["mqtt_server_ip"] = config.mqtt_server_ip;
  doc["mqtt_server_port"] = config.mqtt_server_port;
  doc["mqtt_server_username"] = config.mqtt_server_username;
  doc["mqtt_server_password"] = config.mqtt_server_password;

  File file = LittleFS.open(CONFIG_FILE_NAME, "w");
  if (file) {
    serializeJson(doc, file);
    file.close();
  }
}

void init_config() {
#ifdef DEBUG
  Serial.print("CONFIG ");
#endif

  LittleFS.begin();

  // load config
  if (LittleFS.exists(CONFIG_FILE_NAME)) {
    // load json
    File file = LittleFS.open(CONFIG_FILE_NAME, "r");
    if (file) {
      JsonDocument doc;
      DeserializationError error = deserializeJson(doc, file);
      if (error) {
        default_config();
#ifdef DEBUG
        Serial.println("NOK");
#endif
      } else {
        strlcpy(config.device_name, doc["device_name"] | DEFAULT_DEVICE_NAME,
                sizeof(config.device_name));
        strlcpy(config.mqtt_server_ip, doc["mqtt_server_ip"] | "",
                sizeof(config.mqtt_server_ip));
        config.mqtt_server_port = doc["mqtt_server_port"] | 1883;
        strlcpy(config.mqtt_server_username, doc["mqtt_server_username"] | "",
                sizeof(config.mqtt_server_username));
        strlcpy(config.mqtt_server_password, doc["mqtt_server_password"] | "",
                sizeof(config.mqtt_server_password));
#ifdef DEBUG
        Serial.println("OK");
#endif
      }
      file.close();
    }
  } else {
    // if there's valid config file, load it
    default_config();
#ifdef DEBUG
    Serial.println("NOK");
#endif
  }
}
