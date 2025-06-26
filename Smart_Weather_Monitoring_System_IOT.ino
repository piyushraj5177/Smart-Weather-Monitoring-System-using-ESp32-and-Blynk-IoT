#define BLYNK_TEMPLATE_ID "TMPL37diIJvAO"
#define BLYNK_TEMPLATE_NAME "Smart Weather Monitoring System"
#define BLYNK_AUTH_TOKEN "ps6xU0w293ccSUMKwWUJWAEtwB0A2ihj"

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include "DHT.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Replace with your actual credentials
char auth[] = BLYNK_AUTH_TOKEN;              // Auth Token (from Blynk after creating device)
char ssid[] = "Aagaye Bheek Mangne";               // Your Wi-Fi name
char pass[] = "arrestedinbeauty";           // Your Wi-Fi password

// Sensor and output pins
#define DHTPIN 4
#define DHTTYPE DHT11
#define MQ8PIN 35
#define RAINPIN 34
#define BUZZER 14
#define LED 26

DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(0x27, 16, 2);  // Confirmed I2C address 0x27

void setup() {
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);

  Wire.begin(21, 22);      // Set I2C pins for ESP32
  lcd.init();              // Initialize the LCD (was lcd.begin() before)
  lcd.backlight();         // Turn on LCD backlight

  dht.begin();

  pinMode(BUZZER, OUTPUT);
  pinMode(LED, OUTPUT);

  lcd.setCursor(0, 0);
  lcd.print("Weather Monitor");
  delay(2000);
  lcd.clear();
}

void loop() {
  Blynk.run();

  static unsigned long lastUpdate = 0;
  unsigned long now = millis();

  if (now - lastUpdate >= 2000) {  // Update every 2 seconds
    lastUpdate = now;

    float temp = dht.readTemperature();
    float hum = dht.readHumidity();
    int gasValue = analogRead(MQ8PIN);
    int rainValue = analogRead(RAINPIN);

    if (!isnan(temp) && !isnan(hum)) {
      Blynk.virtualWrite(V1, (double)temp);
      Blynk.virtualWrite(V2, (double)hum);
      Blynk.virtualWrite(V3, gasValue);
      Blynk.virtualWrite(V4, rainValue);
    }

    lcd.setCursor(0, 0);
    lcd.print("T:"); lcd.print(temp, 1);
    lcd.print(" H:"); lcd.print(hum, 1);
    lcd.setCursor(0, 1);
    lcd.print("G:"); lcd.print(gasValue);
    lcd.print(" R:"); lcd.print(rainValue);

    if (gasValue > 2500) {
      digitalWrite(BUZZER, HIGH);
      digitalWrite(LED, HIGH);
      Blynk.logEvent("gas_alert", "High gas level detected!");
    } else {
      digitalWrite(BUZZER, LOW);
      digitalWrite(LED, LOW);
}
}
}