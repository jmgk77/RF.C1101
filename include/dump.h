#pragma once

const char ESP_INFO[] PROGMEM =
    "ESP8266\n"
    "ESP.getFreeHeap(): %d\n"
    "ESP.getChipId(): %08X\n"
    "ESP.getSdkVersion(): %s\n"
    "ESP.getBootVersion(): %d\n"
    "ESP.getBootMode(): %d\n"
    "ESP.getCpuFreqMHz(): %d\n"
    "ESP.getFlashChipId(): %08X\n"
    "ESP.getFlashChipRealSize(): %d\n"
    "ESP.getFlashChipSize(): %d\n"
    "ESP.getFlashChipSpeed(): %dMHz\n"
    "ESP.getFlashChipSizeByChipId(): %d\n"
    "ESP.getSketchSize(): %d\n"
    "ESP.getFreeSketchSpace(): %d\n"
    "ESP.getResetInfo(): %s\n";

const char FS_INFO[] PROGMEM =
    "FS\n"
    "FS.totalBytes(): %d\n"
    "FS.usedBytes(): %d\n"
    "FS.blockSize(): %d\n"
    "FS.pageSize(): %d\n"
    "FS.maxOpenFiles(): %d\n"
    "FS.maxPathLength(): %d\n";

const char EEPROM_INFO[] PROGMEM =
    "EEPROM\n"
    "EEPROM.sign: %c\n"
    "EEPROM.checksum: %08x\n"
    "EEPROM.device_name: %s\n"
    "EEPROM.mqtt_server_ip: %s\n"
    "EEPROM.mqtt_server_port: %d\n"
    "EEPROM.mqtt_server_username: %s\n"
    "EEPROM.mqtt_server_password: %s\n";

void dump_esp8266();
void dump_fs();
void dump_eeprom();

String html_dump_esp8266();
String html_dump_fs();
String html_dump_eeprom();
