/* ----------------------------------------------------------------------
  Blynk Iot Smart Plant Monitoring System
   
   This sketch runs on an ESP8266 (NodeMCU) and uses the Blynk platform
   for remote monitoring and control.
   
   Components:
   - ESP8266 NodeMCU
   - Soil Moisture Sensor (A0)
   - DHT11 Temperature & Humidity Sensor (D4)
   - PIR Motion Sensor (D5)
   - Relay Module (D3)
   - Push Button (D7)
   - I2C LCD 16x2 (SDA: D2, SCL: D1)
   
   Blynk Virtual Pins Used:
   - V0: Temperature
   - V1: Humidity
   - V3: Soil Moisture %
   - V5: PIR Motion LED
   - V6: PIR Sensor Toggle
   - V12: Water Pump Relay Control
----------------------------------------------------------------------*/

#define BLYNK_TEMPLATE_ID "TMPxxxxxx"
#define BLYNK_TEMPLATE_NAME "Device"
#define BLYNK_AUTH_TOKEN "YourAuthToken"

#include <LiquidCrystal_I2C.h>
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>

char ssid[] = "YOUR_WIFI_SSID";
char pass[] = "YOUR_WIFI_PASSWORD";

LiquidCrystal_I2C lcd(0x3F, 16, 2);

#define DHT_PIN D4
#define DHT_TYPE DHT11
DHT dht(DHT_PIN, DHT_TYPE);
BlynkTimer timer;

#define SOIL_SENSOR A0
#define PIR_SENSOR  D5
#define RELAY_PIN   D3
#define BUTTON_PIN  D7
#define VPIN_BUTTON V12

int PIR_ToggleValue = 0;
int relayState = LOW;
int buttonState = HIGH;

void DHT11sensor() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (isnan(h) || isnan(t)) {
    Serial.println("DHT11 Read Error!");
    return;
  }

  Blynk.virtualWrite(V0, t);
  Blynk.virtualWrite(V1, h);

  lcd.setCursor(0, 0);
  lcd.print("T:"); lcd.print(t, 1); lcd.print((char)223); lcd.print("C");

  lcd.setCursor(10, 0);
  lcd.print("H:"); lcd.print(h, 0); lcd.print("%");
}

void soilMoistureSensor() {
  int value = analogRead(SOIL_SENSOR);
  value = map(value, 0, 1024, 100, 0);

  Blynk.virtualWrite(V3, value);

  lcd.setCursor(0, 1);
  lcd.print("S:"); lcd.print(value); lcd.print("% ");
}

void PIRsensor() {
  WidgetLED LED(V5);

  if (PIR_ToggleValue == 0) {
    LED.off();
    return;
  }

  bool value = digitalRead(PIR_SENSOR);

  if (value == HIGH) {
    Blynk.logEvent("pirmotion", "WARNING! Motion Detected!");
    LED.on();
  } else {
    LED.off();
  }
}

BLYNK_WRITE(V6) {
  PIR_ToggleValue = param.asInt();
}

BLYNK_WRITE(VPIN_BUTTON) {
  relayState = param.asInt();
  digitalWrite(RELAY_PIN, relayState);
}

BLYNK_CONNECTED() {
  Blynk.syncVirtual(VPIN_BUTTON);
  Blynk.syncVirtual(V6);
}

void checkPhysicalButton() {
  if (digitalRead(BUTTON_PIN) == LOW) {
    if (buttonState != LOW) {
      relayState = !relayState;
      digitalWrite(RELAY_PIN, relayState);
      Blynk.virtualWrite(VPIN_BUTTON, relayState);
    }
    buttonState = LOW;
  } else {
    buttonState = HIGH;
  }
}

void setup() {
  Serial.begin(115200);

  lcd.begin();
  lcd.backlight();
  lcd.clear();

  pinMode(PIR_SENSOR, INPUT);
  pinMode(RELAY_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  digitalWrite(RELAY_PIN, relayState);

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass, "blynk.cloud", 80);
  dht.begin();

  lcd.setCursor(0, 0); lcd.print(" Smart Plant ");
  lcd.setCursor(0, 1); lcd.print(" Monitoring...");
  delay(2000);
  lcd.clear();

  timer.setInterval(2000L, soilMoistureSensor);
  timer.setInterval(5000L, DHT11sensor);
  timer.setInterval(500L, checkPhysicalButton);
  timer.setInterval(1000L, PIRsensor);
}

void loop() {
  lcd.setCursor(8, 1);
  lcd.print(PIR_ToggleValue ? "M:ON " : "M:OFF");

  lcd.setCursor(12, 1);
  lcd.print(relayState ? "W:ON " : "W:OFF");

  Blynk.run();
  timer.run();
}
