struct DEV_WaterPumpSwitch : Service::Switch {

  int waterPumpPin;
  int buttonPin;
  SpanCharacteristic *on;
  void (*waterPumpOnUpdated)(boolean isOn);

  DEV_WaterPumpSwitch(int waterPumpPin, int buttonPin, void (*waterPumpOnUpdated)(boolean isOn))
    : Service::Switch() {

    this->waterPumpPin = waterPumpPin;
    this->buttonPin = buttonPin;
    this->waterPumpOnUpdated = waterPumpOnUpdated;

    on = new Characteristic::On(false);
    new SpanButton(buttonPin);

    pinMode(waterPumpPin, OUTPUT);
    digitalWrite(waterPumpPin, LOW);
    waterPumpOnUpdated(false);

    LOG0("DEV_WaterPumpSwitch - configured: waterPumpPin = ");
    LOG0(waterPumpPin);
    LOG0(", buttonPin = ");
    LOG0(buttonPin);
    LOG0("\n");
  }

  boolean update() {
    boolean isCurrentlyOn = on->getVal<boolean>();
    boolean shouldBeOn = on->getNewVal<boolean>();
    boolean shouldBeUpdated = isCurrentlyOn != shouldBeOn;

    LOG1("DEV_WaterPumpSwitch - update: isCurrentlyOn = ");
    LOG1(isCurrentlyOn);
    LOG1(", shouldBeOn = ");
    LOG1(shouldBeOn);
    LOG1(", shouldBeUpdated = ");
    LOG1(shouldBeUpdated);
    LOG1("\n");

    if (shouldBeUpdated) {
      digitalWrite(waterPumpPin, shouldBeOn ? HIGH : LOW);
      on->setVal(shouldBeOn);
      waterPumpOnUpdated(shouldBeOn);
    }

    return (true);
  }

  void button(int pin, int pressType) override {

    if (pin == buttonPin && pressType == SpanButton::SINGLE) {
      boolean isCurrentlyOn = on->getVal<boolean>();
      boolean shouldBeOn = !isCurrentlyOn;

      LOG1("DEV_WaterPumpSwitch - button: isCurrentlyOn = ");
      LOG1(isCurrentlyOn);
      LOG1(", shouldBeOn = ");
      LOG1(shouldBeOn);
      LOG1("\n");

      digitalWrite(waterPumpPin, shouldBeOn ? HIGH : LOW);
      on->setVal(shouldBeOn);
      waterPumpOnUpdated(shouldBeOn);
    }
  }
};