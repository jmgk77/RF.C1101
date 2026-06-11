# RF C1101 Bridge

A professional-grade ESP8266 gateway for controlling and learning 433MHz RF signals using the CC1101 transceiver. This project bridges physical RF devices with modern protocols like MQTT and provides a rich web interface for management.

## Features

- **RF Transceiver Integration**: Uses the CC1101 module for high-performance 433MHz transmission and reception.
- **Web Interface**: 
  - Real-time RF code management (Add, Edit, Delete, Send).
  - **RF Cloning**: "Learn" mode to capture codes from existing remotes.
  - File manager for local storage (LittleFS).
  - System diagnostics and EEPROM status.
- **MQTT Connectivity**:
  - Remote command execution via MQTT topics.
  - Automatic IP and status announcement.
  - Integration with home automation systems.
- **Physical Controls**: Support for two physical buttons to trigger predefined RF actions.
- **Persistence**: 
  - RF codes stored in `codes.csv` on LittleFS.
  - System configuration (WiFi, MQTT) stored in EEPROM with CRC32 verification.
- **System Services**:
  - NTP Time synchronization.
  - mDNS, LLMNR, and NBNS for easy network discovery.
  - Over-the-Air (OTA) firmware updates via the web UI.
  - Dynamic LED status patterns.

## Hardware Requirements

- **Microcontroller**: ESP8266 (e.g., NodeMCU or Wemos D1 Mini).
- **RF Module**: TI CC1101 Transceiver.
- **Input**: 2x Tactile buttons (configured on `BUTTON1_PIN` and `BUTTON2_PIN`).
- **Feedback**: Built-in LED_PIN for status patterns.

## Software Architecture

- `main.cpp`: System entry point and orchestration.
- `rf433.cpp`: Low-level CC1101 and RCSwitch integration.
- `web.cpp`: Async Web Server and WiFi Manager implementation.
- `mqtt.cpp`: PicoMQTT client handling and topic logic.
- `codeman.cpp`: High-level RF code management logic and web handlers.
- `persistence.cpp`: CSV-based storage logic for RF codes.
- `eeprom.cpp`: Structured configuration storage with integrity checks.
- `led.cpp`: Non-blocking LED pattern controller using Ticker.

## Configuration

Upon first boot, the device will enter Access Point mode. Connect to the broadcasted SSID to configure:
- WiFi Credentials.
- Device Name.
- MQTT Broker IP, Port, and Credentials.

## MQTT API

The device communicates using the configured `device_name`:

| Direction | Topic | Payload | Description |
|-----------|-------|---------|-------------|
| Sub | `{device_name}/COMMAND` | `ID` | Transmits the RF code at the specified index. |
| Pub | `{device_name}/IP` | `IP String` | Announces the local IP address. |
| Pub | `{device_name}/ACCEPT` | `Name1;Name2;...` | List of available RF code names. |
| Pub | `{device_name}/DESCRIPTION`| `Name Version` | Device identification. |

## RF Code Storage

Codes are stored in `LittleFS:/codes.csv` in the following format:
`Code, Protocol, Length, Delay, Name`

You can manually edit this file via the "Files" section of the web interface or through the "Add/Edit" forms.

## Development

This project is built using PlatformIO.

### Key Dependencies
- RCSwitch
- ELECHOUSE_CC1101
- ESPAsyncWebServer
- PicoMQTT