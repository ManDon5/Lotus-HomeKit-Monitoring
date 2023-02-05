struct DEV_Identify : Service::AccessoryInformation {

  SpanCharacteristic *identify;
  int nBlinks;

  DEV_Identify(
    const char *name,
    const char *manufacturer,
    const char *serialNumber,
    const char *model,
    const char *firmwareRevision,
    int nBlinks)
    : Service::AccessoryInformation() {

    new Characteristic::Name(name);
    new Characteristic::Manufacturer(manufacturer);
    new Characteristic::SerialNumber(serialNumber);
    new Characteristic::Model(model);
    new Characteristic::FirmwareRevision(firmwareRevision);
    identify = new Characteristic::Identify();

    this->nBlinks = nBlinks;

    pinMode(homeSpan.getStatusPin(), OUTPUT);
  }

  boolean update() {

    for (int i = 0; i < nBlinks; i++) {
      digitalWrite(homeSpan.getStatusPin(), LOW);
      delay(250);
      digitalWrite(homeSpan.getStatusPin(), HIGH);
      delay(250);
    }

    return (true);
  }
};