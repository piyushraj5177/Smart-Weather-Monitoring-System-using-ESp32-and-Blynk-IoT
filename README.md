# 🌦️ Smart Weather Monitoring System using ESP32 and Blynk Cloud

This project is an IoT-based Smart Weather Monitoring System using ESP32 that tracks **temperature, humidity, hydrogen gas levels, and rainfall**. It displays real-time data on an I2C LCD and sends updates to the **Blynk Cloud**, enabling remote monitoring through the Blynk mobile app. It also includes a buzzer and LED to provide **instant alerts when gas levels are hazardous**.

---

## 🚀 Features

- Monitors temperature, humidity, rain level, and gas concentration
- Displays data on a 16x2 I2C LCD
- Sends sensor data to Blynk Cloud (mobile & web dashboard)
- Triggers buzzer, LED, and mobile notifications for gas alerts
- Updates every 2 seconds using Wi-Fi

---

## 🛠️ Components Used

- ESP32 Development Board  
- DHT11 Temperature & Humidity Sensor  
- MQ-8 Hydrogen Gas Sensor  
- Rain Sensor Module  
- I2C 16x2 LCD Display  
- Buzzer  
- LED  
- Jumper Wires, Breadboard  
- Power Bank (optional)

---

## 🔌 Circuit Connections

| Component     | Pin         | ESP32 GPIO | Notes                            |
|--------------|-------------|------------|----------------------------------|
| DHT11        | VCC         | 3.3V       | Power                            |
|              | GND         | GND        | Ground                           |
|              | DATA        | GPIO 4     | Data output                      |
| MQ-8 Sensor  | VCC         | 5V         | Requires 5V                      |
|              | GND         | GND        | Ground                           |
|              | AO          | GPIO 35    | Analog gas reading               |
| Rain Sensor  | VCC         | 3.3V/5V    | Power supply                     |
|              | GND         | GND        | Ground                           |
|              | AO          | GPIO 34    | Analog rain detection            |
| Buzzer       | + (VCC)     | GPIO 14    | Buzzer control                   |
|              | - (GND)     | GND        | Ground                           |
| LED          | Anode (+)   | GPIO 26    | Use 220Ω resistor in series      |
|              | Cathode (-) | GND        | Ground                           |
| I2C LCD      | VCC         | 5V         | Power                            |
|              | GND         | GND        | Ground                           |
|              | SDA         | GPIO 21    | I2C data                         |
|              | SCL         | GPIO 22    | I2C clock                        |
---

## 📲 Blynk Integration

- **Virtual Pins**:  
  - `V1` → Temperature  
  - `V2` → Humidity  
  - `V3` → Gas Level  
  - `V4` → Rain Sensor

- **Push Notification**:  
  - Triggered when gas level exceeds `2500` via Blynk `logEvent()`.

---

## 🧠 How It Works

1. ESP32 reads sensor data every 2 seconds.
2. Displays real-time values on the LCD screen.
3. Sends data to Blynk IoT cloud for remote access.
4. Triggers buzzer and LED if gas crosses threshold.
5. Sends mobile notification via Blynk app.

---
## 💡 LCD Display & Output Summary
### 📺 LCD Output Format
Line 1: T:<temperature> H:<humidity>
Line 2: G:<gas_value> R:<rain_value>

### ✅ Example Output
T:28.3 H:67.1
G:3120 R:1023

### 🧪 Results

- All sensor readings are accurately displayed on both LCD and Blynk dashboard.
- Gas alert triggers were successfully tested at >2500 sensor value.
- Mobile notifications were sent without delay using Blynk’s `logEvent()`.
- System proved reliable and responsive in real-time monitoring.

---

## 🧪 Code Logic Snapshot

```cpp
float temp = dht.readTemperature();
float hum = dht.readHumidity();
int gasValue = analogRead(MQ8PIN);
int rainValue = analogRead(RAINPIN);

if (gasValue > 2500 && !alertSent) {
  digitalWrite(BUZZER, HIGH);
  digitalWrite(LED, HIGH);
  Blynk.logEvent("gas_alert", "High gas level detected!");
  alertSent = true;
}
```

### 📋 Summary

This Smart Weather Monitoring System is built using ESP32 along with DHT11, MQ-8, and a rain sensor to measure temperature, humidity, gas levels, and rainfall. The data is displayed locally on an I2C LCD and sent to the Blynk Cloud for remote monitoring. If hydrogen gas levels exceed a safe threshold, the system activates a buzzer and LED for alerts and sends a push notification via the Blynk app. This project provides an efficient, real-time solution for weather tracking and gas hazard alerts, making it suitable for smart home, industrial, or educational use.







