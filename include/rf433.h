#pragma once

struct RF_CODE {
  String rf433_name;
  unsigned long rf433_code;
  unsigned int rf433_protocol;
  unsigned int rf433_length;
  unsigned int rf433_delay;
};

void init_433();

void send_433(RF_CODE& code);
void send_433_enable();

bool recv_433(RF_CODE& code);
void recv_433_enable();

bool add_433(RF_CODE& code);
