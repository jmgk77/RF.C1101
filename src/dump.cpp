#include "main.h"

extern struct eeprom_data eeprom;

String __dump_esp8266() {
  char buf[1024];
  snprintf(buf, sizeof(buf), ESP_INFO, ESP.getFreeHeap(), ESP.getChipId(),
           ESP.getSdkVersion(), ESP.getBootVersion(), ESP.getBootMode(),
           ESP.getCpuFreqMHz(), ESP.getFlashChipId(),
           ESP.getFlashChipRealSize(), ESP.getFlashChipSize(),
           ESP.getFlashChipSpeed() / 1000000, ESP.getFlashChipSizeByChipId(),
           ESP.getSketchSize(), ESP.getFreeSketchSpace(),
           ESP.getResetInfo().c_str());
  return String(buf);
}

String __dump_fs() {
  char buf[1024];
  FSInfo fs_info;
  LittleFS.info(fs_info);
  snprintf(buf, sizeof(buf), FS_INFO, fs_info.totalBytes, fs_info.usedBytes,
           fs_info.blockSize, fs_info.pageSize, fs_info.maxOpenFiles,
           fs_info.maxPathLength);
  return String(buf);
}

String __dump_eeprom() {
  char buf[1024];
  snprintf(buf, sizeof(buf), EEPROM_INFO, eeprom.sign, eeprom.checksum,
           eeprom.device_name, eeprom.mqtt_server_ip, eeprom.mqtt_server_port,
           eeprom.mqtt_server_username, eeprom.mqtt_server_password);
  return String(buf);
}

void dump_esp8266() { Serial.print(__dump_esp8266()); }
void dump_fs() { Serial.print(__dump_fs()); }
void dump_eeprom() { Serial.print(__dump_eeprom()); }

String html_dump_esp8266() {
  String s = __dump_esp8266();
  s.replace("\n", "<br>");
  return s;
}

String html_dump_fs() {
  String s = __dump_fs();
  s.replace("\n", "<br>");
  return s;
}

String html_dump_eeprom() {
  String s = __dump_eeprom();
  s.replace("\n", "<br>");
  return s;
}