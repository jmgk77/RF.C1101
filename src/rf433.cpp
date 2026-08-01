#include "main.h"

std::vector<RF_CODE> rf433_codes;

RCSwitch rf433 = RCSwitch();

void recv_433_enable() {
  ELECHOUSE_cc1101.SetRx();
  delay(5);
}

void send_433_enable() {
  ELECHOUSE_cc1101.SetTx();
  delay(15);  // Allow CC1101 PLL frequency synthesizer to stabilize and lock
}

void init_433() {
  log_println("INIT 433...");
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
  ELECHOUSE_cc1101.setMHZ(433.92);
  ELECHOUSE_cc1101.setPA(12);  // Set maximum PA transmit power (+12 dBm)

  if (ELECHOUSE_cc1101.getCC1101()) {
    log_println("CC1101 status: OK (433.92 MHz, PA: +12dBm)");
  } else {
    log_println("CC1101 status: NOK (Check SPI/Wiring!)");
  }

  rf433.enableReceive(RF433_RX_PIN);
  rf433.enableTransmit(RF433_TX_PIN);
  rf433.setRepeatTransmit(15);  // Increase default repeat count from 10 to 15
  log_printf("RF433 pins: RX=%d, TX=%d (15 Repeats, Max PA)\n", RF433_RX_PIN, RF433_TX_PIN);
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
  log_printf("# SEND: %s [%ld], len:%d, proto:%d, delay:%d (15 repeats)\n",
             code.rf433_name.c_str(), code.rf433_code, code.rf433_length,
             code.rf433_protocol, code.rf433_delay);
  rf433.setProtocol(code.rf433_protocol);
  rf433.setPulseLength(code.rf433_delay);
  rf433.setRepeatTransmit(15);
  rf433.send(code.rf433_code, code.rf433_length);
  delay(10);
  recv_433_enable();
}

bool recv_433(RF_CODE& code) {
  if (rf433.available()) {
    code = __get_433();
    log_printf("# RECV: %s [%ld], len:%d, proto:%d, delay:%d\n",
               code.rf433_name.c_str(), code.rf433_code, code.rf433_length,
               code.rf433_protocol, code.rf433_delay);
    rf433.resetAvailable();
    return true;
  }
  return false;
}
