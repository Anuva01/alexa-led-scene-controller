/*
 * Alexa Voice-Controlled LED Scene System
 * Hardware : ESP32-S3
 * Cloud    : SinricPro + Amazon Alexa
 * Scenes   : All Lights / Movie Mode / Party Mode
 * Author   : Anuva (github.com/Anuva01)
 *
 * Setup: Copy credentials.h template, fill in your values
 */

#ifdef ESP32
  #include <WiFi.h>
#else
  #include <ESP8266WiFi.h>
#endif
#include "SinricPro.h"
#include "SinricProSwitch.h"
#include "credentials.h"

// LED pins
#define LED1 5
#define LED2 6
#define LED3 9
#define LED4 10

bool partyModeActive = false;

// ── SCENE FUNCTIONS ─────────────────────────

void allLightsOn() {
  digitalWrite(LED1, HIGH);
  digitalWrite(LED2, HIGH);
  digitalWrite(LED3, HIGH);
  digitalWrite(LED4, HIGH);
  Serial.println("Scene: ALL LIGHTS ON");
}

void allLightsOff() {
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
  digitalWrite(LED3, LOW);
  digitalWrite(LED4, LOW);
  Serial.println("Scene: ALL LIGHTS OFF");
}

void movieModeOn() {
  digitalWrite(LED1, HIGH);
  digitalWrite(LED2, LOW);
  digitalWrite(LED3, LOW);
  digitalWrite(LED4, HIGH);
  Serial.println("Scene: MOVIE MODE ON");
}

void movieModeOff() {
  allLightsOff();
  Serial.println("Scene: MOVIE MODE OFF");
}

// ── CALLBACKS ───────────────────────────────

bool onAllLights(const String &deviceId, bool &state) {
  partyModeActive = false;
  if (state) allLightsOn();
  else allLightsOff();
  return true;
}

bool onMovieMode(const String &deviceId, bool &state) {
  partyModeActive = false;
  if (state) movieModeOn();
  else movieModeOff();
  return true;
}

bool onPartyMode(const String &deviceId, bool &state) {
  partyModeActive = state;
  if (!state) allLightsOff();
  Serial.println(state ? "Scene: PARTY MODE ON"
                       : "Scene: PARTY MODE OFF");
  return true;
}

// ── PARTY MODE CHASE EFFECT ─────────────────

void handlePartyMode() {
  static int currentLed = 0;
  static unsigned long lastBlink = 0;

  if (millis() - lastBlink > 150) {
    allLightsOff();
    int pins[] = {LED1, LED2, LED3, LED4};
    digitalWrite(pins[currentLed], HIGH);
    currentLed = (currentLed + 1) % 4;
    lastBlink = millis();
  }
}

// ── WIFI ────────────────────────────────────

void setupWiFi() {
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected! IP: "
                 + WiFi.localIP().toString());
}

// ── SINRICPRO ───────────────────────────────

void setupSinricPro() {
  SinricPro[DEVICE_ALL_LIGHTS].onPowerState(onAllLights);
  SinricPro[DEVICE_MOVIE_MODE].onPowerState(onMovieMode);
  SinricPro[DEVICE_PARTY_MODE].onPowerState(onPartyMode);
  SinricPro.begin(APP_KEY, APP_SECRET);
  Serial.println("SinricPro connected!");
}

// ── SETUP ───────────────────────────────────

void setup() {
  Serial.begin(115200);

  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);

  allLightsOff();

  setupWiFi();
  setupSinricPro();

  Serial.println("Ready! Say: Alexa, turn on Party Mode");
}

// ── LOOP ────────────────────────────────────

void loop() {
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("WiFi lost, reconnecting...");
    setupWiFi();
  }

  SinricPro.handle();

  if (partyModeActive) {
    handlePartyMode();
  }

  delay(10);
}
