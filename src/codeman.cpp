#include "main.h"

bool decoding_onoff;
RF_CODE code;

extern std::vector<RF_CODE> rf433_codes;
extern AsyncWebServer server;

String gen_html_codes() {
  String s;
  s += "<div style='border: 1px solid black'>\n<div style='border: 1px solid "
       "black'>\n";

  int i = 0;
  for (auto& c : rf433_codes) {
    s += "<div>";
    s += c.rf433_name;

    s += "<input type='button' value='SEND' "
         "onclick=\"location.href='/send?b=" +
         String(i) + "';\">";
    s += "<input type='button' value='DELETE' "
         "onclick=\"location.href='/delete?b=" +
         String(i) + "';\">";
    s += "<input type='button' value='EDIT' "
         "onclick=\"location.href='/edit?b=" +
         String(i) + "';\">";

    s += "</div>\n";
    i++;
  }

  s += "</div>\n<input type='button' value='ADD' "
       "onclick=\"location.href='/add';\">\n<input type='button' value='CLONE' "
       "onclick=\"location.href='/clone';\">\n</div><br>";
  return s;
}

void __handle_send(AsyncWebServerRequest* request) {
  //***
  request->send(200, "text/plain", "send");
}

void __handle_delete(AsyncWebServerRequest* request) {
  //***
  request->send(200, "text/plain", "delete");
}

void __handle_edit(AsyncWebServerRequest* request) {
  //***
  request->send(200, "text/plain", "edit");
}

void __handle_add(AsyncWebServerRequest* request) {
  //***
  request->send(200, "text/plain", "add");
}

void __clone_off() {
  decoding_onoff = false;
  set_led_pattern(LED_OFF);
}

void __handle_clone(AsyncWebServerRequest* request) {
  if (request->hasParam("b", true)) {
    __clone_off();

    code.rf433_name = request->getParam("b", true)->value();
    add_433(code);
    save_rf_codes();

    request->send(200, "text/html",
                  "<meta http-equiv='refresh' content='0; url=/'/>");
  } else {
    // __clone_on()
    code = {};
    recv_433_enable();
    decoding_onoff = true;
    set_led_pattern(LED_BLINK_FAST);

    request->send(
        200, "text/html",
        String(html_header) + String(html_clone) + String(html_footer));
  }
}

void __handle_clone_status(AsyncWebServerRequest* request) {
  request->send(200, "text/plain", decoding_onoff ? "ON" : "OFF");
}

void __handle_clone_timeout(AsyncWebServerRequest* request) {
#ifdef DEBUG
  Serial.println("TIMEOUT...");
#endif
  __clone_off();
  request->send(200, "text/plain", "OK");
}

void init_codes_manager() {
  server.on("/send", HTTP_ANY, __handle_send);
  server.on("/delete", HTTP_ANY, __handle_delete);
  server.on("/edit", HTTP_ANY, __handle_edit);
  server.on("/add", HTTP_ANY, __handle_add);

  server.on("/clone", HTTP_ANY, __handle_clone);
  server.on("/clone_status", HTTP_ANY, __handle_clone_status);
  server.on("/clone_timeout", HTTP_ANY, __handle_clone_timeout);
  decoding_onoff = false;
}

void handle_codes_manager() {
  if (decoding_onoff) {
    if (recv_433(code)) {
      __clone_off();
    }
  }
}