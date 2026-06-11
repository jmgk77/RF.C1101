# IDEAS.md – 433 MHz Remote Repeater/Cloner (Active Ideas)

## Project: ESP8266 + CC1101 – Web Controlled 433MHz Repeater/Cloner

This document lists only the features we kept discussing after your initial review.  
Implemented already: cloning, manual add, code management, MQTT, OTA, web UI.

---

## 🔧 RF & Hardware Features (In Development or Planned)

### 1. Signal Analyzer / Live Spectrum Viewer
- Scan 433.80–434.20 MHz in 20 kHz steps
- Measure RSSI per channel → bar graph or waterfall in web UI
- Use case: find interference, debug range issues, choose cleanest channel
- Implementation: loop `setChannel()` + `halRfReadRssi()`

### 2. RSSI‑Based Repeater Filtering
- Store a minimum RSSI threshold for each remote code
- Only repeat a code if received signal strength > threshold
- Prevents distant / outside remotes from triggering your community gateway

### 3. Dedicated Repeater Mode
- Listen continuously for a stored remote code
- Immediately retransmit same code (RX→TX switching)
- Add blind time (e.g., 100 ms) after transmit to avoid infinite loop
- Web UI toggle per remote to enable/disable repeating
- Already confirmed possible: CC1101 can do this with ~1‑2ms switching latency

### 4. Advanced Jamming Modes (Educational / Self‑Test Only)
> ⚠️ Only use on your own devices, at low power, respecting Anatel regulations.

| Mode | Description |
|------|-------------|
| Pulse jammer | 50% duty cycle carrier – blocks simple receivers |
| Code replay jammer | Retransmit captured code repeatedly |
| Sweep jammer | Rapidly hop frequencies while transmitting |
| Protocol‑aware jammer | Send valid sync word + random bits to corrupt packets |

You already have `send rnd()` – these are more interesting patterns.

### 5. OLED + 3‑Button Interface (In Progress)
- Standalone operation without web UI
- Up / Down / Send buttons
- Show stored codes, select, transmit

---

## 📡 Capture & Export

### 6. URH (Universal Radio Hacker) Export
- Export captured signals as raw binary + bit rate
- Create `.sr` or `.csv` files for analysis on a PC
- Use case: reverse‑engineer unknown protocols
- Implementation: just dump what you already have in a new format

---

## 🤖 Automation & Smart Home

### 7. Advanced Scheduler / Timeline
- Store cron‑like rules in SPIFFS
- Trigger RF commands at specific times (e.g., open gate at 7:00)
- Integration with web UI for setting up timers

### 8. Activity Logging & Favorites
- Log every transmitted/received signal with timestamp
- Searchable history
- “Star” or favorite frequently used codes (easy web UI addition)

### 9. Voice Assistant Integration (Future / Next Version)
- Publish to Alexa, Google Assistant, or Siri Shortcuts
- Voice control of RF devices (e.g., “Alexa, turn on garden lights”)

---

## 💻 Web & User Experience

### 10. Backup / Restore – Make More User Friendly
- You already have this; improve web UI for easy export/import of code database + settings

### 11. Experimental Feature Tab
- Dedicated web UI tab for experimental/unsafe features (e.g., jamming)
- Keep stable features separate

### 12. REST API (Optional)
- Documented HTTP endpoints for external scripting
- Example: `GET /send?code=123&protocol=ev1527`
- Useful for integration with other automation systems

---

## ✅ Next Steps (Suggested Order)

1. **Repeater mode** – most useful for your community gateway  
2. **RSSI threshold filtering** – security + reduce false triggers  
3. **Activity log + favorites** – easy win, great UX  
4. **Spectrum scanner** – debug interference  
5. **Scheduler** – automation without extra hardware  
6. **Finish OLED + buttons** – standalone control  

---

## ❌ Removed Ideas (Discarded or Overkill)

- Multi‑frequency support (Brazil is mostly 433 MHz)  
- Rolling code cloning (illegal / impractical for car remotes)  
- Full relay attack mitigation (not your scope)  
- Online protocol database (too heavy for ESP8266)  
- Mobile spectrum mapper (device is fixed at gateway)  
- Ollama / local AI assistant (removed per your request)  

---

*Last updated: 2026‑06‑11 – based on our discussion after the first suggestion.*