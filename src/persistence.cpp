#include "main.h"

extern std::vector<RF_CODE> rf433_codes;

void load_rf_codes() {
#ifdef DEBUG
  Serial.print("LOAD CODES ");
#endif
  char buffer[256];
  char buffer2[32];
  RF_CODE c;
  File file = LittleFS.open("codes.csv", "r");
  if (file) {
    // clear old cdes
    rf433_codes.clear();
    // discart header
    file.readBytesUntil('\n', buffer, sizeof(buffer));
    while (file.available()) {
      memset(buffer, 0, sizeof(buffer));
      memset(buffer2, 0, sizeof(buffer2));
      file.readBytesUntil('\n', buffer, sizeof(buffer));
      sscanf(buffer, "%lu,%u,%u,%u,%31[^\n]", &c.rf433_code, &c.rf433_protocol,
             &c.rf433_length, &c.rf433_delay, buffer2);
      c.rf433_name = (String)buffer2;
      rf433_codes.push_back(c);
    }
    file.close();
#ifdef DEBUG
    Serial.println(rf433_codes.size());
  } else {
    Serial.println("NOK");
#endif
  }
}

void save_rf_codes() {
#ifdef DEBUG
  Serial.printf("SAVE CODES %d ", rf433_codes.size());
#endif
  char buffer[256];
  File file = LittleFS.open("codes.csv", "w");
  if (file) {
    file.write("Code, Protocol, Length, Delay, Name\n");
    for (auto& c : rf433_codes) {
      sprintf(buffer, "%lu,%u,%u,%u,%s\n", c.rf433_code, c.rf433_protocol,
              c.rf433_length, c.rf433_delay, c.rf433_name.c_str());
      file.print(buffer);
    }
    file.close();
#ifdef DEBUG
    Serial.println("OK");
  } else {
    Serial.println("NOK");
#endif
  }
}
