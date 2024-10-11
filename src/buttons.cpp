#include "main.h"

OneButton button1;
OneButton button2;

extern std::vector<RF_CODE> rf433_codes;

void button1_press() {
  Serial.println("button1");
  // send first button
  if (rf433_codes.size() >= 1) {
    send_433_enable();
    send_433(*(rf433_codes.begin() + 0));
  } else {
    Serial.println("out of range!");
  }
}

void button2_press() {
  Serial.println("button2");
  // send second button
  if (rf433_codes.size() >= 2) {
    send_433_enable();
    send_433(*(rf433_codes.begin() + 1));
  } else {
    Serial.println("out of range!");
  }
}

void init_buttons() {
  button1.setup(BUTTON1, INPUT_PULLUP, true);
  button2.setup(BUTTON2, INPUT_PULLUP, true);

  button1.attachClick(button1_press);
  button2.attachClick(button2_press);
}

void handle_buttons() {
  button1.tick();
  button2.tick();
}
