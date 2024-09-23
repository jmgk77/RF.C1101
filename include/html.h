#pragma once

#define FORM_SAVE_STRING(VAR)                                  \
  strncpy(eeprom.VAR,                                          \
          request->hasParam(#VAR, true)                        \
              ? request->getParam(#VAR, true)->value().c_str() \
              : "",                                            \
          sizeof(eeprom.VAR));
#define FORM_SAVE_INT(VAR)                                          \
  eeprom.VAR = request->hasParam(#VAR, true)                        \
                   ? request->getParam(#VAR, true)->value().toInt() \
                   : 0;
#define FORM_SAVE_BOOL(VAR)                                                 \
  eeprom.VAR =                                                              \
      request->hasParam(#VAR, true)                                         \
          ? (request->getParam(#VAR, true)->value() == "on" ? true : false) \
          : false;

#define FORM_START(URL) \
  s += "<form action='" + String(URL) + "' method='POST'>";
#define FORM_ASK_VALUE(VAR, TXT)                                           \
  s += "<label for='" + String(#VAR) + "' name='" + String(#VAR) + "'>" +  \
       String(TXT) + ":</label><input type='text' name='" + String(#VAR) + \
       "' value='" + eeprom.VAR + "'><br>";
#define FORM_ASK_BOOL(VAR, TXT)                                                \
  s += "<label for='" + String(#VAR) + "' name='" + String(#VAR) + "'>" +      \
       String(TXT) + ":</label><input type='checkbox' name='" + String(#VAR) + \
       "' " + String(eeprom.VAR ? "checked" : "") + "><br>";
#define FORM_ASK_BOOL_JS(VAR, TXT, JS)                                         \
  s += "<label for='" + String(#VAR) + "' name='" + String(#VAR) + "'>" +      \
       String(TXT) + ":</label><input type='checkbox' name='" + String(#VAR) + \
       "' " + String(eeprom.VAR ? "checked " : "") + String(JS) + "><br>";
#define FORM_END(BTN)                                                          \
  s +=                                                                         \
      "<input type='hidden' name='s' value='1'><input type='submit' value='" + \
      String(BTN) + "'></form>";

const char html_header[] = R""""(
<!DOCTYPE html>
<html lang='pt-br'>
<head>
<meta charset='UTF-8'>
<meta name='viewport' content='width=device-width, initial-scale=1'>
<meta http-equiv='cache-control' content='no-cache, no-store, must-revalidate'>
<meta http-equiv='refresh' content='600'/>
<title>RF_CC1101</title>
</head>
<body>)"""";

const char html_footer[] = R""""(
</body>
</html>)"""";

const char html_buttons[] = R""""(
<form action='/' method='POST'><input type='submit' value='MAIN'></form>
<form action='/info' method='POST'><input type='submit' value='INFO'></form>
<form action='/config' method='POST'><input type='submit' value='CONFIG'></form>
<form action='/reboot' method='POST'><input type='submit' value='REBOOT'></form>
<form action='/reset' method='POST'><input type='submit' value='RESET'></form>)"""";