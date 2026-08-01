#include "main.h"

void setup() {
#ifdef DEBUG
  Serial.begin(115200, SERIAL_8N1, SERIAL_TX_ONLY, 1);
  delay(1000);
  Serial.println();
#endif

  init_logger();
  log_printf("=== STARTING %s %s ===\n", DEFAULT_DEVICE_NAME, VERSION);

  log_println("[1/8] init_config()");
  init_config();

  log_println("--- System Dumps ---");
  dump_esp8266();
  dump_config();
  dump_fs();

  log_println("[2/8] init_web()");
  init_web();

  log_println("[3/8] load_rf_codes()");
  load_rf_codes();

  log_println("[4/8] init_codes_manager()");
  init_codes_manager();

  log_println("[5/8] init_time()");
  init_time();

  log_println("[6/8] init_433()");
  init_433();

#ifdef ENABLE_LEDS
  log_println("[7/8] init_led()");
  init_led();
#endif

#ifdef ENABLE_BUTTONS
  log_println("[7/8] init_buttons()");
  init_buttons();
#endif

  log_println("[8/8] init_mqtt()");
  init_mqtt();

  log_println("=== INITIALIZATION COMPLETE ===");
}

void loop() {
  handle_web();

  handle_codes_manager();

#ifdef ENABLE_BUTTONS
  handle_buttons();
#endif

  handle_mqtt();
}