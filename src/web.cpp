#include "main.h"

DNSServer dns;
AsyncWebServer server(80);
AsyncWiFiManager wm(&server, &dns);
ESPAsyncHTTPUpdateServer updateServer;

extern struct eeprom_data eeprom;
extern char boot_time[32];

String __add_buttons() { return String(html_buttons); }

void __handle_root(AsyncWebServerRequest* request) {
  String s;
  //
  s += "IP: <i>" + WiFi.localIP().toString() + "</i><br>";
  s += "Data de ínicio: <i>" + String(boot_time) + "</i><br>";
  // version
  s += "Versão: " + String(VERSION) +
#ifdef DEBUG
       "<FONT color=red><b> DEBUG</b></FONT>" +
#endif
       "<br><br>";

  //***

  // buttons
  s += __add_buttons();
  // send root page
  request->send(200, "text/html", html_header + s + html_footer);
}

void __handle_info(AsyncWebServerRequest* request) {
  String s;
  s += html_dump_esp8266();
  s += html_dump_eeprom();
  s += html_dump_fs();

  // buttons
  s += __add_buttons();
  // send root page
  request->send(200, "text/html", html_header + s + html_footer);
}

void __handle_config(AsyncWebServerRequest* request) {
  //
  if (request->hasParam("s", true)) {
    // read options
    FORM_SAVE_STRING(device_name)
    FORM_SAVE_STRING(mqtt_server_ip)
    FORM_SAVE_INT(mqtt_server_port)
    FORM_SAVE_STRING(mqtt_server_username)
    FORM_SAVE_STRING(mqtt_server_password)
    // save data to eeprom
    save_eeprom();
    dump_eeprom();
    request->send(200, "text/html",
                  "<meta http-equiv='refresh' content='0; url=/config'/>");
  } else {
    String s;
    FORM_START("/config")
    FORM_ASK_VALUE(device_name, "Device name")
    FORM_ASK_VALUE(mqtt_server_ip, "MQTT Broker fixed IP")
    FORM_ASK_VALUE(mqtt_server_port, "MQTT Broker Port")

    FORM_ASK_VALUE(mqtt_server_username, "MQTT remote username")
    FORM_ASK_VALUE(mqtt_server_password, "MQTT remote password")

    FORM_END("SALVAR")
    // update
    s +=
        "<br><form action='/update?name=firmware'enctype=multipart/form-data "
        "method=POST>Firmware:<br><input type=file accept=.bin,.bin.gz "
        "name=firmware> <input type=submit value='Update Firmware'></form><br>";

    // buttons
    s += __add_buttons();

    // send config page
    request->send(200, "text/html", html_header + s + html_footer);
  }
}

void __handle_reboot(AsyncWebServerRequest* request) {
  request->send(200, "text/html",
                "<meta http-equiv='refresh' content='15; url=/' />");
  delay(1 * 1000);
  ESP.restart();
  delay(2 * 1000);
}

void __handle_reset(AsyncWebServerRequest* request) {
  // erase eeprom
  default_eeprom();
  save_eeprom();
  // reset wifi
  wm.resetSettings();
  __handle_reboot(request);
}

void __handle_404(AsyncWebServerRequest* request) {
  request->send(404, "text/plain", "Not found");
}

void init_web() {
  // connect to internet
  WiFi.mode(WIFI_STA);
  delay(10);
  wm.setDebugOutput(false);
  WiFi.hostname(eeprom.device_name);
  wm.setConfigPortalTimeout(180);
  WiFi.setAutoReconnect(true);
  WiFi.persistent(true);

  // captive portal
  if (!wm.autoConnect(eeprom.device_name)) {
    ESP.restart();
    delay(1 * 1000);
  }
#ifdef DEBUG
  Serial.println("Got IP: " + WiFi.localIP().toString());
#endif
  // install www handlers
  server.onNotFound(__handle_404);
  server.on("/", HTTP_ANY, __handle_root);
  server.on("/config", HTTP_ANY, __handle_config);
  server.on("/info", HTTP_ANY, __handle_info);
  server.on("/reboot", HTTP_ANY, __handle_reboot);
  server.on("/reset", HTTP_ANY, __handle_reset);
  updateServer.setup(&server, "/update");
  server.begin();

  // discovery protocols
  MDNS.begin(eeprom.device_name);
  MDNS.addService("http", "tcp", 80);
}

void handle_web() { MDNS.update(); }
