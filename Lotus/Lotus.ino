#include <HomeSpan.h>

#include "DEV_Identify.h"
#include "DEV_WaterTemperatureSensor.h"
#include "DEV_EnvironmentalSensor.h"
#include "DEV_WaterPumpSwitch.h"

#include "src/LotusDisplay/LotusDisplay.h"

const int HOMESPAN_STATUS_PIN = 2;
const int HOMESPAN_CONTROL_PIN = 32;

const int DISPLAY_CS_PIN = 26;
const int DISPLAY_DC_PIN = 25;
const int DISPLAY_RST_PIN = 33;
const int DISPLAY_BUSY_PIN = 27;

const int WATER_TEMPERATURE_SENSOR_PIN = 13;
const int WATER_PUMP_PIN = 16;
const int BUTTON_PIN = 4;

LotusDisplay lotusDisplay(DISPLAY_CS_PIN, DISPLAY_DC_PIN, DISPLAY_RST_PIN, DISPLAY_BUSY_PIN);

void setup() {
  // Serial.begin(115200);

  lotusDisplay.startUp();

  delay(5000);

  homeSpan.setStatusPin(HOMESPAN_STATUS_PIN);
  homeSpan.setControlPin(HOMESPAN_CONTROL_PIN);
  homeSpan.enableOTA();
  homeSpan.begin(Category::Other, "Lotus");

  new SpanAccessory();
    new DEV_Identify("Wassertemperatursensor", "HomeSpan", "0001", "DS18B20", "1.0", 5);
    new Service::HAPProtocolInformation();
      new Characteristic::Version("1.1.0");
    new DEV_WaterTemperatureSensor(WATER_TEMPERATURE_SENSOR_PIN, waterTemperatureUpdated);
    new DEV_WaterPumpSwitch(WATER_PUMP_PIN, BUTTON_PIN, waterPumpOnUpdated);

  new SpanAccessory();
    new DEV_Identify("Umgebungssensor", "HomeSpan", "0001", "HTU21D", "1.0", 10);
    new Service::HAPProtocolInformation();
      new Characteristic::Version("1.1.0");
    new DEV_EnvironmentalTemperatureSensor(environmentalTemperatureUpdated);
    new DEV_EnvironmentalHumiditySensor(environmentalHumidityUpdated);
}

void loop() {
  homeSpan.poll();
  lotusDisplay.checkHibernate();
}

void environmentalTemperatureUpdated(float temperature) {
  lotusDisplay.showEnvironmentalTemperature(temperature);
}

void environmentalHumidityUpdated(int humidity) {
  lotusDisplay.showEnvironmentalHumidity(humidity);
}

void waterTemperatureUpdated(float temperature) {
  lotusDisplay.showWaterTemperature(temperature);
}

void waterPumpOnUpdated(boolean isOn) {
  lotusDisplay.showWaterPumpOn(isOn);
}