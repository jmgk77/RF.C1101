#pragma once

#if !defined(ESP8266)
#error This code is designed to run on ESP8266 and ESP8266-based boards! Please check your Tools->Board setting.
#endif

#include <Arduino.h>
#include <CRC32.h>
#include <ESP_EEPROM.h>
#include <LittleFS.h>

#include "dump.h"
#include "eeprom.h"
#include "version.h"

#define DEFAULT_DEVICE_NAME "RF_CC1101"

#define DEBUG