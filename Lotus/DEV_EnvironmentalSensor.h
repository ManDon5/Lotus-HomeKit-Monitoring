#include <Wire.h>
#include <HTU2xD_SHT2x_Si70xx.h>

struct DEV_EnvironmentalTemperatureSensor : Service::TemperatureSensor {

  const long TEMPERATURE_INTERVAL = 600000;  // 10 minutes
  const float TEMPERATURE_DEVIATION = -0.7;

  HTU2xD_SHT2x_SI70xx ht2x = HTU2xD_SHT2x_SI70xx();
  SpanCharacteristic *temperatureCharacteristic;
  void (*environmentalTemperatureUpdated)(float temperature);

  unsigned long previousMillis = 0;

  DEV_EnvironmentalTemperatureSensor(void (*environmentalTemperatureUpdated)(float temperature))
    : Service::TemperatureSensor() {

    this->environmentalTemperatureUpdated = environmentalTemperatureUpdated;
    ht2x.begin();

    float currentSensorTemperature = ht2x.readTemperature() + TEMPERATURE_DEVIATION;

    temperatureCharacteristic = new Characteristic::CurrentTemperature(currentSensorTemperature);
    temperatureCharacteristic->setRange(-30, 100, 0.1);
    environmentalTemperatureUpdated(currentSensorTemperature);

    LOG0("DEV_EnvironmentalTemperatureSensor - configured");
    LOG0("\n");
  }

  void loop() {
    unsigned long currentMillis = millis();

    if (currentMillis - previousMillis >= TEMPERATURE_INTERVAL) {
      previousMillis = currentMillis;

      float currentSensorTemperature = ht2x.readTemperature() + TEMPERATURE_DEVIATION;
      float currentCharacteristicTemperature = temperatureCharacteristic->getVal<float>();
      boolean shouldBeUpdated = abs(currentCharacteristicTemperature - currentSensorTemperature) >= 0.1;

      LOG1("DEV_EnvironmentalTemperatureSensor - loop: currentSensorTemperature = ");
      LOG1(currentSensorTemperature);
      LOG1(", currentCharacteristicTemperature = ");
      LOG1(currentCharacteristicTemperature);
      LOG1(", shouldBeUpdated = ");
      LOG1(shouldBeUpdated);
      LOG1("\n");

      if (shouldBeUpdated) {
        temperatureCharacteristic->setVal(currentSensorTemperature);
        environmentalTemperatureUpdated(currentSensorTemperature);
      }
    }
  }
};

struct DEV_EnvironmentalHumiditySensor : Service::HumiditySensor {

  const int HUMIDITY_HEATING_THRESHOLD = 80;
  const long HUMIDITY_INTERVAL = 600000;                               // 10 minutes
  const long HEATING_INTERVAL = 60000;                                 // 1 minute
  const long COOLING_INTERVAL = HUMIDITY_INTERVAL - HEATING_INTERVAL;  // 9 minutes
  const long COOLING_START_INTERVAL = 20000;                           // 20 seconds

  HTU2xD_SHT2x_SI70xx ht2x = HTU2xD_SHT2x_SI70xx();
  SpanCharacteristic *humidityCharacteristic;
  void (*environmentalHumidityUpdated)(int humidity);
  boolean isHeating = false;

  long coolingInterval = COOLING_START_INTERVAL;
  unsigned long previousMillis = 0;
  unsigned long previousHeatingMillis = 0;

  DEV_EnvironmentalHumiditySensor(void (*environmentalHumidityUpdated)(int humidity))
    : Service::HumiditySensor() {

    this->environmentalHumidityUpdated = environmentalHumidityUpdated;
    ht2x.begin();

    int currentSensorHumidity = getCurrentCompensatedSensorHumidity();

    humidityCharacteristic = new Characteristic::CurrentRelativeHumidity(currentSensorHumidity);
    humidityCharacteristic->setRange(0, 100, 1);
    environmentalHumidityUpdated(currentSensorHumidity);

    LOG0("DEV_EnvironmentalHumiditySensor - configured");
    LOG0("\n");
  }

  void loop() {
    unsigned long currentMillis = millis();

    handleHeating(currentMillis);

    if (currentMillis - previousMillis >= HUMIDITY_INTERVAL) {
      previousMillis = currentMillis;

      int currentSensorHumidity = getCurrentCompensatedSensorHumidity();
      int currentCharacteristicHumidity = humidityCharacteristic->getVal<int>();
      boolean shouldBeUpdated = abs(currentCharacteristicHumidity - currentSensorHumidity) >= 1;

      LOG1("DEV_EnvironmentalHumiditySensor - loop: currentSensorHumidity = ");
      LOG1(currentSensorHumidity);
      LOG1(", currentCharacteristicHumidity = ");
      LOG1(currentCharacteristicHumidity);
      LOG1(", shouldBeUpdated = ");
      LOG1(shouldBeUpdated);
      LOG1("\n");

      if (shouldBeUpdated) {
        humidityCharacteristic->setVal(currentSensorHumidity);
        environmentalHumidityUpdated(currentSensorHumidity);
      }
    }
  }

  int getCurrentCompensatedSensorHumidity() {
    float temperature = ht2x.readTemperature();
    return (int)ht2x.getCompensatedHumidity(temperature);
  }

  void handleHeating(unsigned long currentMillis) {

    if (isHeating && (currentMillis - previousHeatingMillis >= HEATING_INTERVAL)) {
      previousHeatingMillis = currentMillis;
      isHeating = false;
      ht2x.setHeater(isHeating);

      LOG2("DEV_EnvironmentalHumiditySensor - handleHeating: stop heating, isHeating = ");
      LOG2(isHeating);
      LOG2("\n");
    } else if (!isHeating && (currentMillis - previousHeatingMillis >= coolingInterval)) {
      previousHeatingMillis = currentMillis;

      int currentSensorHumidity = getCurrentCompensatedSensorHumidity();
      String heatingState;

      if (currentSensorHumidity >= HUMIDITY_HEATING_THRESHOLD) {
        coolingInterval = COOLING_INTERVAL;
        isHeating = true;
        heatingState = "start heating";
        ht2x.setHeater(isHeating);
      } else {
        coolingInterval = HUMIDITY_INTERVAL;
        heatingState = "no heating needed";
      }

      LOG2("DEV_EnvironmentalHumiditySensor - handleHeating: ");
      LOG2(heatingState);
      LOG2(", isHeating = ");
      LOG2(isHeating);
      LOG2(", currentSensorHumidity: ");
      LOG2(currentSensorHumidity);
      LOG2("\n");
    }
  }
};