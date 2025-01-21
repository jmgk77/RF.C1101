#include "main.h"

PicoMQTT::Client *mqtt_client;

Ticker mqtt;
bool mqtt_announce = false;

String mqtt_topic_ip;

extern struct eeprom_data eeprom;

void init_mqtt() {
  // mqtt client
  mqtt_client = new PicoMQTT::Client(
      eeprom.mqtt_server_ip, eeprom.mqtt_server_port, eeprom.device_name,
      eeprom.mqtt_server_username, eeprom.mqtt_server_password);
  mqtt_client->begin();

  mqtt_topic_ip = String(eeprom.device_name) + "/IP";

  // periodic announce
  mqtt.once_ms_scheduled(MQTT_ANNOUNCE_TIMER, []() { mqtt_announce = true; });
}

void handle_mqtt() {
  // handle mqtt client
  mqtt_client->loop();

  // periodic publish IP
  if (mqtt_announce) {
    mqtt_announce = false;
    mqtt_client->publish(mqtt_topic_ip, WiFi.localIP().toString());
  }
}