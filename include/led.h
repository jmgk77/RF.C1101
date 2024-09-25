#pragma once

#define LED_ON 0b1111111111111111
#define LED_OFF 0b0000000000000000
#define LED_BLINK 0b1100110011001100
#define LED_BLINK_SLOW 0b1111001111001111
#define LED_BLINK_FAST 0b1010101010101010

void set_led_pattern(uint16_t pattern);
void init_led();