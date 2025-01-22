#include "main.h"

std::vector<RF_CODE> rf433_codes;

RCSwitch rf433 = RCSwitch();

void recv_433_enable() { ELECHOUSE_cc1101.SetRx(); }

void send_433_enable() { ELECHOUSE_cc1101.SetTx(); }

void init_433() {
#ifdef ENABLE_BOGUS_CODES
  //(debug) add bogus codes
  for (int i = 0; i < 5; i++) {
    RF_CODE c;
    c.rf433_name = "TEST#" + (String)rf433_codes.size();
    c.rf433_code = 0x10;
    c.rf433_protocol = 0x20;
    c.rf433_length = 0x30;
    c.rf433_delay = 0x40;
    rf433_codes.push_back(c);
  }
#endif

  // CC1101 Settings
  ELECHOUSE_cc1101.Init();
  // ELECHOUSE_cc1101.setRxBW(812.50);
  // ELECHOUSE_cc1101.setPA(10);
  ELECHOUSE_cc1101.setMHZ(433.92);

  if (ELECHOUSE_cc1101.getCC1101()) {
#ifdef DEBUG
    Serial.println("CC1101 OK");
  } else {
    Serial.println("CC1101 NOK");
#endif
  }

  rf433.enableReceive(RF433_RX_PIN);
  rf433.enableTransmit(RF433_TX_PIN);
}

RF_CODE __get_433() {
  RF_CODE c;
  c.rf433_name = "CODE#" + (String)rf433_codes.size();
  c.rf433_code = rf433.getReceivedValue();
  c.rf433_protocol = rf433.getReceivedProtocol();
  c.rf433_length = rf433.getReceivedBitlength();
  c.rf433_delay = rf433.getReceivedDelay();
  return c;
}

bool add_433(RF_CODE& code) {
  // scan vector for same code
  bool is_new = true;
  for (auto& i : rf433_codes) {
    if (i.rf433_code == code.rf433_code) {
#ifdef DEBUG
      Serial.println("add_433() -> already");
#endif
      is_new = false;
      break;
    }
  }

  // replace forbidden chars
  code.rf433_name.replace(";", "_");

  // add to vector
  if (is_new) {
#ifdef DEBUG
    Serial.println("add_433() -> new");
#endif
    rf433_codes.push_back(code);
  }
  return is_new;
}

void send_433(RF_CODE& code) {
#ifdef DEBUG
  Serial.printf("# SEND: %s [%ld], %d, %d, %d\n", code.rf433_name.c_str(),
                code.rf433_code, code.rf433_length, code.rf433_protocol,
                code.rf433_delay);
#endif
  rf433.setProtocol(code.rf433_protocol);
  rf433.setPulseLength(code.rf433_delay);
  rf433.send(code.rf433_code, code.rf433_length);
}

bool recv_433(RF_CODE& code) {
  if (rf433.available()) {
    code = __get_433();
#ifdef DEBUG
    Serial.printf("# RECV: %s [%ld], %d, %d, %d\n", code.rf433_name.c_str(),
                  code.rf433_code, code.rf433_length, code.rf433_protocol,
                  code.rf433_delay);
#endif
    rf433.resetAvailable();
    return true;
  }
  return false;
}
