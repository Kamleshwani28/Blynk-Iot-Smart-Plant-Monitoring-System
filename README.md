# Blynk-Iot-Smart-Plant-Monitoring-System
# 🌱 IoT Smart Plant Monitoring System  
**Developer:** Kamlesh Wani  
**Tech Used:** ESP8266, Blynk, Soil Moisture Sensor,PIR Motion Sensor, DHT11, Arduino IDE  

## 📌 Project Overview  
This IoT-based Smart Plant Monitoring System measures **soil moisture**, **Motion**, **temperature**, and **humidity** in real-time using ESP8266.  
Data is sent to the **Blynk IoT App**, where users can monitor plant health and automate watering.

## 🚀 Features  
- 🌡️ Real-time temperature & humidity monitoring  
- 🌱 Soil moisture measurement
- 🏃 Motion Sensor 
- 📲 Live dashboard on Blynk  
- 💧 Automated irrigation (optional)  
- 📡 WiFi-enabled IoT connectivity  

## 🧰 Components Used  
- ESP8266 NodeMCU  
- Soil Moisture Sensor
- PIR Motion Sensor
- DHT11 Sensor
- Water Pump
- Jumper Wires  
- Relay Module (optional for pump)  
- Power Supply  

## 🛠️ Circuit Diagram  
(Add circuit diagram image here)  
```
images/c901e7_8ce6589b43264e76ab364ecf26f2842c~mv2 (2).png
```

## 📲 Blynk Setup  
1. Create a new template  
2. Add virtual pins for DHT11 and Soil Moisture  
3. Copy **Blynk Auth Token**  
4. Paste it into the code  

## 🧾 How It Works  
- ESP8266 reads data from sensors  
- Sends data to Blynk via WiFi  
- App displays values  
- Optional relay turns on pump if moisture is low  

## 📁 Files in this Repository  
| File | Description |
|------|-------------|
| `SmartPlantMonitoring.ino` | Main project code |
| `README.md` | Project documentation |
| `/images` | Circuit diagram, screenshots |

## ▶️ How to Upload Code  
1. Open Arduino IDE  
2. Select **ESP8266 NodeMCU** board  
3. Paste the `.ino` code  
4. Upload  

## 📸 Screenshots  
(Add your Blynk and circuit images here)

```
/images/blynk-dashboard.jpg
/images/plant-setup.jpg
```

## 🧑‍💻 Developer  
**Kamlesh Wani**  
Embedded & IoT Engineer (Fresher)
