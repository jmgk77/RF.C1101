#include "main.h"

PicoMQTT::Client* mqtt_client;

Ticker mqtt;
bool mqtt_announce = false;

String mqtt_topic_ip;
String mqtt_topic_buttons;

extern struct eeprom_data eeprom;
extern std::vector<RF_CODE> rf433_codes;

void __callback(const char* payload) {
  unsigned int button = atoi(payload);

  // check atoi() error
  if ((button == 0) && (payload[0] != '0')) {
    return;
  }

  if (button < rf433_codes.size()) {
    send_433_enable();
    send_433(*(rf433_codes.begin() + button));
  }
}

void init_mqtt() {
  // mqtt client
  mqtt_client = new PicoMQTT::Client(
      eeprom.mqtt_server_ip, eeprom.mqtt_server_port, eeprom.device_name,
      eeprom.mqtt_server_username, eeprom.mqtt_server_password);
  mqtt_client->begin();

  // periodic announce
  mqtt.attach_scheduled(MQTT_ANNOUNCE_TIMER, []() { mqtt_announce = true; });

  mqtt_client->subscribe(String(eeprom.device_name) + "/COMMAND", __callback);
}

void handle_mqtt() {
  // handle mqtt client
  mqtt_client->loop();

  // periodic publish IP
  if (mqtt_announce) {
    mqtt_announce = false;

    mqtt_client->publish(
        String(eeprom.device_name) + "/DESCRIPTION",
        String(DEFAULT_DEVICE_NAME) + String(" ") + String(VERSION));

    // send IP
    mqtt_client->publish(String(eeprom.device_name) + "/IP",
                         WiFi.localIP().toString());

    // send rf codes accepted
    String s;
    for (auto& c : rf433_codes) {
      s += c.rf433_name;
      s += ";";
    }
    mqtt_client->publish(String(eeprom.device_name) + "/ACCEPT", s);
  }
}