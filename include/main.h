#pragma once

#if !defined(ESP8266)
#error This code is designed to run on ESP8266 and ESP8266-based boards! Please check your Tools->Board setting.
#endif

#include <Arduino.h>
#include <ArduinoJson.h>
#include <ELECHOUSE_CC1101_SRC_DRV.h>
#include <ESP8266LLMNR.h>
#include <ESP8266NetBIOS.h>
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <ESPAsyncHTTPUpdateServer.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <ESPAsyncWiFiManager.h>
#include <LittleFS.h>
#include <OneButton.h>
#include <PicoMQTT.h>
#include <RCSwitch.h>
#include <Ticker.h>

#include "buttons.h"
#include "codeman.h"
#include "datetime.h"
#include "dump.h"
#include "favicon.h"
#include "html.h"
#include "led.h"
#include "logger.h"
#include "mqtt.h"
#include "persistence.h"
#include "rf433.h"
#include "version.h"
#include "web.h"

#define DEFAULT_DEVICE_NAME "RF_CC1101"

// #define RF433_TX_PIN 3   // RX
#define RF433_TX_PIN 5   // D1
#define RF433_RX_PIN 16  // D0

#define BUTTON1_PIN 2  // D4
#define BUTTON2_PIN 0  // D3

#define LED_PIN LED_BUILTIN  // D4

#define DEBUG
#define ENABLE_EXTRA_DISCOVERY
// #define ENABLE_BOGUS_CODES
// #define ENABLE_LEDS
// #define ENABLE_BUTTONS
