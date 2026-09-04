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
<link rel="icon" type="image/png" href="/favicon.ico">
<link rel="apple-touch-icon" href="/favicon.ico">
<link rel="manifest" href="/manifest.json">
<meta name="theme-color" content="#333333">
<meta charset='UTF-8'>
<meta name='viewport' content='width=device-width, initial-scale=1'>
<meta http-equiv='cache-control' content='no-cache, no-store, must-revalidate'>
<meta http-equiv='refresh' content='600'/>
<title>RF_CC1101</title>
<style>
  :root { --primary:#1a73e8; --danger:#d93025; --bg:#f5f6f7; --card:#fff; --ink:#202124; }
  html { -webkit-text-size-adjust:100%; }
  body { margin:0; padding:12px; background:var(--bg); color:var(--ink);
         font:16px/1.4 system-ui,-apple-system,'Segoe UI',Roboto,Arial,sans-serif; }
  .rf-title { font-size:1.1rem; color:#5f6368; font-weight:600; margin:6px 2px 10px; }
  .rf-list { display:flex; flex-direction:column; gap:10px; }
  .rf-row { display:flex; flex-direction:column; gap:6px; }
  .rf-send {
    display:flex; align-items:center; justify-content:center;
    min-height:64px; padding:14px; border-radius:14px; background:var(--primary);
    color:#fff; text-decoration:none; font-size:1.15rem; font-weight:600;
    text-align:center; -webkit-user-select:none; user-select:none; cursor:pointer;
    box-shadow:0 1px 2px rgba(0,0,0,.25); }
  .rf-send:active { filter:brightness(.92); }
  .rf-row > .rf-send:first-child { flex:1; }
  .rf-admin { display:flex; gap:8px; justify-content:center; font-size:.85rem; }
  .rf-admin a { color:#5f6368; background:#e8eaed; text-decoration:none;
                padding:4px 12px; border-radius:8px; }
  .rf-admin a.rf-del { color:var(--danger); background:#fce8e6; }
  .rf-manage { display:inline-block; margin-top:14px; font-weight:600;
               color:#5f6368; background:#e8eaed; text-decoration:none;
               padding:10px 16px; border-radius:12px; }
  .rf-nav { margin-top:14px; text-align:center; }
  .rf-nav form { display:inline-block; margin:2px; }
  @media (max-width:600px){
    body { padding:8px; }
    .rf-meta, .rf-nav { display:none; } /* phone sees only the repeat buttons */
    .rf-send { min-height:56px; font-size:1.05rem; }
    .rf-admin { display:none; }      /* edit/delete kept out of one-hand view */
    .rf-manage { font-size:.85rem; padding:7px 12px; }
  }
</style>
</head>
<body>
)"""";

const char html_footer[] = R""""(
</body>
</html>)"""";

const char html_buttons[] = R""""(
<form action='/' method='POST'><input type='submit' value='MAIN'></form>
<form action='/info' method='POST'><input type='submit' value='INFO'></form>
<form action='/logs' method='POST'><input type='submit' value='LOGS'></form>
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
<input type='submit' value='SALVAR'>
</form>
<form action='/clone_timeout' method='POST'><input type='submit' value='CANCELAR'></form>
)"""";
