#include "main.h"

Ticker led;

#define LED LED_BUILTIN

uint16_t led_pattern;

uint16_t mask;

void set_led_pattern(uint16_t pattern) {
  mask = 1;
  led_pattern = pattern;
}

void __led_blink() {
  digitalWrite(LED, (led_pattern & mask) == 0 ? 1 : 0);
  mask <<= 1;
  if (!mask) {
    mask = 1;
  };
}

void init_led() {
  pinMode(LED, OUTPUT);
  set_led_pattern(LED_OFF);
  led.attach_ms(1000 / (sizeof(led_pattern) * 8), __led_blink);
}
