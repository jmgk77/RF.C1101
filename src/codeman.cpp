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
  if (request->hasParam("b")) {
    int button = request->getParam("b")->value().toInt();
    send_433_enable();
    send_433(*(rf433_codes.begin() + button));
  }
  request->send(200, "text/html",
                "<meta http-equiv='refresh' content='0; url=/'/>");
}

void __handle_delete(AsyncWebServerRequest* request) {
  if (request->hasParam("b")) {
    int button = request->getParam("b")->value().toInt();
    rf433_codes.erase(rf433_codes.begin() + button);
    save_rf_codes();
  }
  request->send(200, "text/html",
                "<meta http-equiv='refresh' content='0; url=/'/>");
}

void __handle_edit(AsyncWebServerRequest* request) {
  int button;
  if (request->hasParam("b")) {
    // get
    button = request->getParam("b")->value().toInt();
  } else if (request->hasParam("b", true)) {
    // post
    button = request->getParam("b", true)->value().toInt();
  } else {
    request->send(200, "text/html",
                  "<meta http-equiv='refresh' content='0; url=/'/>");
  }

  if (request->hasParam("s", true)) {
    // read code
    FORM_SAVE_STRING2(code.rf433_name);
    FORM_SAVE_INT(code.rf433_code);
    FORM_SAVE_INT(code.rf433_protocol);
    FORM_SAVE_INT(code.rf433_length);
    FORM_SAVE_INT(code.rf433_delay);

    // save edit to codes list
    *(rf433_codes.begin() + button) = code;
    save_rf_codes();

    request->send(200, "text/html",
                  "<meta http-equiv='refresh' content='0; url=/'/>");
  } else {
    // edit code form
    String s;
    code = *(rf433_codes.begin() + button);

    FORM_START("/edit")
    FORM_ASK_VALUE(code.rf433_name, "Name");
    FORM_ASK_VALUE(code.rf433_code, "Code");
    FORM_ASK_VALUE(code.rf433_protocol, "Protocol");
    FORM_ASK_VALUE(code.rf433_length, "length");
    FORM_ASK_VALUE(code.rf433_delay, "Delay");
    // pass button reference
    s += "<input type='hidden' name='b' value=" + String(button) + "/>\n";
    FORM_END("SALVAR")

    // send edit page
    request->send(200, "text/html", html_header + s + html_footer);
  }
}

void __handle_add(AsyncWebServerRequest* request) {
  if (request->hasParam("s", true)) {
    // read code
    FORM_SAVE_STRING2(code.rf433_name);
    FORM_SAVE_INT(code.rf433_code);
    FORM_SAVE_INT(code.rf433_protocol);
    FORM_SAVE_INT(code.rf433_length);
    FORM_SAVE_INT(code.rf433_delay);
    // save data to codes list
    add_433(code);
    save_rf_codes();

    request->send(200, "text/html",
                  "<meta http-equiv='refresh' content='0; url=/'/>");
  } else {
    // add code form
    String s;
    code = {};
    FORM_START("/add")
    FORM_ASK_VALUE(code.rf433_name, "Name");
    FORM_ASK_VALUE(code.rf433_code, "Code");
    FORM_ASK_VALUE(code.rf433_protocol, "Protocol");
    FORM_ASK_VALUE(code.rf433_length, "length");
    FORM_ASK_VALUE(code.rf433_delay, "Delay");
    FORM_END("SALVAR")

    // send add page
    request->send(200, "text/html", html_header + s + html_footer);
  }
}

void __clone_off() {
  decoding_onoff = false;
  set_led_pattern(LED_OFF);
}

void __clone_on() {
  code = {};
  recv_433_enable();
  decoding_onoff = true;
  set_led_pattern(LED_BLINK_FAST);
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
    __clone_on();

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

#ifdef DEBUG
  dump_rf_codes();
#endif
}

void handle_codes_manager() {
  if (decoding_onoff) {
    if (recv_433(code)) {
      __clone_off();
    }
  }
}