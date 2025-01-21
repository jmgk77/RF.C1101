#pragma once

#if !defined(ESP8266)
#error This code is designed to run on ESP8266 and ESP8266-based boards! Please check your Tools->Board setting.
#endif

#include <Arduino.h>
#include <CRC32.h>
#include <ELECHOUSE_CC1101_SRC_DRV.h>
#include <ESP8266LLMNR.h>
#include <ESP8266NetBIOS.h>
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <ESPAsyncHTTPUpdateServer.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <ESPAsyncWiFiManager.h>
#include <ESP_EEPROM.h>
#include <LittleFS.h>
#include <OneButton.h>
#include <PicoMQTT.h>
#include <RCSwitch.h>
#include <Ticker.h>

#include "buttons.h"
#include "codeman.h"
#include "datetime.h"
#include "dump.h"
#include "eeprom.h"
#include "html.h"
#include "led.h"
#include "mqtt.h"
#include "persistence.h"
#include "rf433.h"
#include "version.h"
#include "web.h"

#define DEFAULT_DEVICE_NAME "RF_CC1101"

#define RF433_RX_PIN 4  // D2
#define RF433_TX_PIN 5  // D1

// #define DEBUG
// #define ENABLE_EXTRA_DISCOVERY
// #define ENABLE_BOGUS_CODES