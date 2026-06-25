# Alexa Voice-Controlled LED Scene System 🎙️💡

Control 4 LEDs in smart scenes using Amazon Alexa voice commands,
ESP32-S3 and SinricPro cloud bridge.

> "Alexa, turn on Party Mode" → LEDs chase in sequence

---

## Scenes

| Voice Command | What happens |
|---|---|
| "Alexa, turn on All Lights" | All 4 LEDs ON |
| "Alexa, turn off All Lights" | All 4 LEDs OFF |
| "Alexa, turn on Movie Mode" | LED1 + LED4 only (ambient) |
| "Alexa, turn on Party Mode" | LEDs chase one by one |
| "Alexa, turn off Party Mode" | All LEDs OFF |

---

## How it works

Alexa (voice) → SinricPro cloud → ESP32-S3 (WiFi) → 4 LEDs

---

## Hardware

| Part | Cost |
|---|---|
| ESP32-S3 Dev Board | ₹1100 |
| LEDs x4 (any colour) | ₹20 |
| 220Ω resistors x4 | ₹10 |
| Jumper wires | ₹50 |
| Breadboard | ₹80 |

---

## Wiring

| ESP32-S3 Pin | Component |
|---|---|
| GPIO 5 | 220Ω → LED1 anode |
| GPIO 6 | 220Ω → LED2 anode |
| GPIO 9 | 220Ω → LED3 anode |
| GPIO 10 | 220Ω → LED4 anode |
| GND | All LED cathodes (shared rail) |

---

## Software Setup

### 1. Install Arduino IDE 2
Download from arduino.cc/en/software

### 2. Add ESP32 board support
File → Preferences → Additional boards URL: https://dl.espressif.com/dl/package_esp32_index.json

### 3. Install libraries
Tools → Manage Libraries → install:
- SinricPro by Boris Jaeger (install all dependencies)

### 4. SinricPro setup
- Sign up free at sinric.pro
- Create 3 Switch devices: All Lights, Movie Mode, Party Mode
- Copy App Key, App Secret, all 3 Device IDs

### 5. Configure credentials
- Copy credentials.h template, fill in your values
- Never commit the filled version

### 6. Upload
- Board: ESP32S3 Dev Module
- Hold BOOT → press RST → release BOOT → click Upload
- Press RST after upload completes

---

## Alexa Setup
1. Open Alexa app → More → Skills & Games
2. Search SinricPro → Enable skill
3. Sign in with SinricPro account
4. All 3 scenes appear automatically in Alexa

---

## Tech Stack
- **Hardware:** ESP32-S3
- **Cloud:** SinricPro WebSocket bridge
- **Voice:** Amazon Alexa
- **Protocol:** WiFi, WebSocket
- **IDE:** Arduino IDE 2

---

## Future Upgrades
- [ ] Add relay module to control real AC lamp
- [ ] RGB LED color control by voice
- [ ] DHT11 sensor — auto scene based on temperature
- [ ] OTA firmware updates

---

## Author
**Anuva** — Electronics Engineering | Embedded Systems
📍 Indore, India
[GitHub](https://github.com/Anuva01)
