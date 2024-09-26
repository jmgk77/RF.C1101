#pragma once

#define FORM_SAVE_STRING(VAR)                                  \
  strncpy(VAR,                                                 \
          request->hasParam(#VAR, true)                        \
              ? request->getParam(#VAR, true)->value().c_str() \
              : "",                                            \
          sizeof(VAR));
#define FORM_SAVE_STRING2(VAR)                                                 \
  VAR = request->hasParam(#VAR, true) ? request->getParam(#VAR, true)->value() \
                                      : "";
#define FORM_SAVE_INT(VAR)                                   \
  VAR = request->hasParam(#VAR, true)                        \
            ? request->getParam(#VAR, true)->value().toInt() \
            : 0;
#define FORM_SAVE_BOOL(VAR)                                                   \
  VAR = request->hasParam(#VAR, true)                                         \
            ? (request->getParam(#VAR, true)->value() == "on" ? true : false) \
            : false;

#define FORM_START(URL) \
  s += "<form action='" + String(URL) + "' method='POST'>\n";
#define FORM_ASK_VALUE(VAR, TXT)                                           \
  s += "<label for='" + String(#VAR) + "' name='" + String(#VAR) + "'>" +  \
       String(TXT) + ":</label><input type='text' name='" + String(#VAR) + \
       "' value='" + VAR + "'><br>\n";
#define FORM_ASK_BOOL(VAR, TXT)                                                \
  s += "<label for='" + String(#VAR) + "' name='" + String(#VAR) + "'>" +      \
       String(TXT) + ":</label><input type='checkbox' name='" + String(#VAR) + \
       "' " + String(VAR ? "checked" : "") + "><br>\n";
#define FORM_ASK_BOOL_JS(VAR, TXT, JS)                                         \
  s += "<label for='" + String(#VAR) + "' name='" + String(#VAR) + "'>" +      \
       String(TXT) + ":</label><input type='checkbox' name='" + String(#VAR) + \
       "' " + String(VAR ? "checked " : "") + String(JS) + "><br>\n";
#define FORM_END(BTN)                                                          \
  s +=                                                                         \
      "<input type='hidden' name='s' value='1'><input type='submit' value='" + \
      String(BTN) + "'></form>\n";

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
<body>
)"""";

const char html_footer[] = R""""(
</body>
</html>)"""";

const char html_buttons[] = R""""(
<form action='/' method='POST'><input type='submit' value='MAIN'></form>
<form action='/info' method='POST'><input type='submit' value='INFO'></form>
<form action='/files' method='POST'><input type='submit' value='FILES'></form>
<form action='/config' method='POST'><input type='submit' value='CONFIG'></form>
<form action='/reboot' method='POST'><input type='submit' value='REBOOT'></form>
<form action='/reset' method='POST'><input type='submit' value='RESET'></form>)"""";

const char html_clone[] = R""""(
<script>
window.onbeforeunload=()=>{fetch('/clone_timeout');};
setTimeout(()=>{document.location.href = '/';},30*1000);
a=setInterval(()=>{fetch('/clone_status').then(b=>b.text()).then((r)=>{if(r==='OFF'){clearInterval(a);document.getElementById('a').style.display='none';document.getElementById('b').style.display='block';}})},1000);
</script>
<form action='/clone' method='POST'>
Pressione um botão no controle remoto
<div>
<img id='a' src='data:image/svg+xml,<svg version="1.1" baseProfile="full" width="16" height="16" xmlns="http://www.w3.org/2000/svg"> <circle cx="8" cy="8" r="8" fill="red" /></svg>'/>
<img id='b' src='data:image/svg+xml,<svg version="1.1" baseProfile="full" width="16" height="16" xmlns="http://www.w3.org/2000/svg"> <circle cx="8" cy="8" r="8" fill="green" /></svg>' style='display:none'/>
</div>
<input type='text' name='b' maxlength='31' value=''>
<input type='submit' value='Adicionar'>
</form>
)"""";
