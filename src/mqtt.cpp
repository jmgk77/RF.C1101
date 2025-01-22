#include "main.h"

PicoMQTT::Client* mqtt_client;

Ticker mqtt;
bool mqtt_announce = false;

String mqtt_topic_ip;
String mqtt_topic_buttons;
String mqtt_topic_command;
#ifdef DEBUG
String mqtt_topic_reply;
#endif

extern struct eeprom_data eeprom;
extern std::vector<RF_CODE> rf433_codes;

void __callback(const char* payload) {
  unsigned int button = atoi(payload);
  // ! check atoi() error
  if (button < rf433_codes.size()) {
    send_433_enable();
    send_433(*(rf433_codes.begin() + button));
#ifdef DEBUG
    mqtt_client->publish(mqtt_topic_reply, "OK");
#endif
  } else {
#ifdef DEBUG
    mqtt_client->publish(mqtt_topic_reply, "NOK");
#endif
  }
}

void init_mqtt() {
  // mqtt client
  mqtt_client = new PicoMQTT::Client(
      eeprom.mqtt_server_ip, eeprom.mqtt_server_port, eeprom.device_name,
      eeprom.mqtt_server_username, eeprom.mqtt_server_password);
  mqtt_client->begin();

  mqtt_topic_ip = String(eeprom.device_name) + "/IP";
  mqtt_topic_buttons = String(eeprom.device_name) + "/ACCEPT";
  mqtt_topic_command = String(eeprom.device_name) + "/COMMAND";
#ifdef DEBUG
  mqtt_topic_reply = String(eeprom.device_name) + "/STATUS";
#endif

  // periodic announce
  mqtt.attach_scheduled(MQTT_ANNOUNCE_TIMER, []() { mqtt_announce = true; });

  mqtt_client->subscribe(mqtt_topic_command, __callback);
}

void handle_mqtt() {
  // handle mqtt client
  mqtt_client->loop();

  // periodic publish IP
  if (mqtt_announce) {
    mqtt_announce = false;
    mqtt_client->publish(mqtt_topic_ip, WiFi.localIP().toString());

    String s;
    for (auto& c : rf433_codes) {
      s += c.rf433_name;
      s += ";";
    }
    mqtt_client->publish(mqtt_topic_buttons, s);
  }
}