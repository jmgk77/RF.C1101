#include "main.h"

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
void __handle_clone(AsyncWebServerRequest* request) {
  //***
  request->send(200, "text/plain", "clone");
}

void init_codes_manager() {
  server.on("/send", HTTP_ANY, __handle_send);
  server.on("/delete", HTTP_ANY, __handle_delete);
  server.on("/edit", HTTP_ANY, __handle_edit);
  server.on("/add", HTTP_ANY, __handle_add);
  server.on("/clone", HTTP_ANY, __handle_clone);
}