#include <OneWire.h>
#include <DallasTemperature.h>

struct DEV_WaterTemperatureSensor : Service::TemperatureSensor {

  const long TEMPERATURE_INTERVAL = 600000;  // 10 minutes

  DallasTemperature *temperatureSensor;
  SpanCharacteristic *temperatureCharacteristic;
  void (*waterTemperatureUpdated)(float temperature);

  unsigned long previousMillis = 0;

  DEV_WaterTemperatureSensor(int sensorPin, void (*waterTemperatureUpdated)(float temperature))
    : Service::TemperatureSensor() {

    OneWire *oneWire;
    oneWire = new OneWire(sensorPin);
    this->temperatureSensor = new DallasTemperature(oneWire);
    this->waterTemperatureUpdated = waterTemperatureUpdated;

    temperatureSensor->begin();

    float currentSensorTemperature = getCurrentSensorTemperature();

    temperatureCharacteristic = new Characteristic::CurrentTemperature(currentSensorTemperature);
    temperatureCharacteristic->setRange(-30, 100, 0.1);
    waterTemperatureUpdated(currentSensorTemperature);

    LOG0("DEV_WaterTemperatureSensor - configured: sensorPin = ");
    LOG0(sensorPin);
    LOG0("\n");
  }

  void loop() {
    unsigned long currentMillis = millis();

    if (currentMillis - previousMillis >= TEMPERATURE_INTERVAL) {
      previousMillis = currentMillis;

      float currentSensorTemperature = getCurrentSensorTemperature();
      float currentCharacteristicTemperature = temperatureCharacteristic->getVal<float>();
      boolean shouldBeUpdated = abs(currentCharacteristicTemperature - currentSensorTemperature) >= 0.1;

      LOG1("DEV_WaterTemperatureSensor - loop: currentSensorTemperature = ");
      LOG1(currentSensorTemperature);
      LOG1(", currentCharacteristicTemperature = ");
      LOG1(currentCharacteristicTemperature);
      LOG1(", shouldBeUpdated = ");
      LOG1(shouldBeUpdated);
      LOG1("\n");

      if (shouldBeUpdated) {
        temperatureCharacteristic->setVal(currentSensorTemperature);
        waterTemperatureUpdated(currentSensorTemperature);
      }
    }
  }

  float getCurrentSensorTemperature() {
    temperatureSensor->requestTemperatures();
    return temperatureSensor->getTempCByIndex(0);
  }
};