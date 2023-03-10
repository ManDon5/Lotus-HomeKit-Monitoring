#ifndef LotusImages_H
#define LotusImages_H

#if defined(ESP8266) || defined(ESP32)
#include <pgmspace.h>
#else
#include <avr/pgmspace.h>
#endif

// 30x51
const unsigned char EnvironmentalTemperatureImage[] PROGMEM = {
  0x00, 0x07, 0x00, 0x00, 0x00, 0x0f, 0x80, 0x00, 0x00, 0x19, 0xc0, 0x00, 0x00, 0x18, 0xc0, 0x00,
  0x00, 0x19, 0xc0, 0x00, 0x00, 0x1f, 0x80, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xe0, 0x00, 0x00, 0x07, 0xf8, 0x00, 0x00, 0x1e, 0x3c,
  0x00, 0x00, 0x18, 0x0c, 0x00, 0x00, 0x38, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00, 0x30, 0x00,
  0x00, 0x00, 0x30, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00, 0x30, 0x00, 0x07, 0xc0, 0x38, 0x08,
  0x0e, 0xe0, 0x1c, 0x1c, 0x18, 0x30, 0x0f, 0xf8, 0x18, 0x30, 0x03, 0xe0, 0x18, 0x30, 0x00, 0x00,
  0x18, 0x30, 0x00, 0x00, 0x18, 0x30, 0x00, 0x00, 0x18, 0x30, 0x00, 0x00, 0x19, 0x30, 0x00, 0x00,
  0x19, 0x30, 0x06, 0x00, 0x19, 0x30, 0x1f, 0x80, 0x19, 0x30, 0x30, 0xc0, 0x19, 0x33, 0xe0, 0x40,
  0x19, 0x36, 0x20, 0x40, 0x19, 0x34, 0x00, 0x70, 0x19, 0x3c, 0x00, 0x08, 0x19, 0x30, 0x00, 0x04,
  0x19, 0x30, 0x00, 0x04, 0x19, 0x30, 0x00, 0x04, 0x39, 0x38, 0x00, 0x08, 0x71, 0x1f, 0xff, 0xf0,
  0x63, 0x8c, 0x00, 0x00, 0xc7, 0xc6, 0x00, 0x00, 0xcf, 0xe6, 0x00, 0x00, 0xcf, 0xe6, 0x00, 0x00,
  0xcf, 0xe6, 0x00, 0x00, 0xc7, 0xc6, 0x00, 0x00, 0x63, 0x8c, 0x00, 0x00, 0x70, 0x1c, 0x00, 0x00,
  0x38, 0x38, 0x00, 0x00, 0x1f, 0xf0, 0x00, 0x00, 0x07, 0xc0, 0x00, 0x00
};

// 30x51
const unsigned char EnvironmentalHumidityImage[] PROGMEM = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x06, 0x00,
  0x00, 0x38, 0x0f, 0x00, 0x00, 0x7c, 0x0f, 0x80, 0x00, 0xc6, 0x19, 0x80, 0x01, 0x87, 0x30, 0xc0,
  0x03, 0x03, 0xe0, 0x60, 0x03, 0x01, 0xe0, 0x30, 0x06, 0x00, 0xc0, 0x30, 0x0c, 0x00, 0x60, 0x18,
  0x1c, 0x00, 0x30, 0x18, 0x18, 0x00, 0x30, 0x0c, 0x30, 0x00, 0x18, 0x0c, 0x31, 0x06, 0x18, 0x0c,
  0x67, 0x84, 0x0c, 0x0c, 0x66, 0xcc, 0x0c, 0x0c, 0xc6, 0xcc, 0x04, 0x08, 0xc7, 0x98, 0x06, 0x18,
  0xc3, 0x18, 0x06, 0x30, 0xc0, 0x10, 0x06, 0xe0, 0xc0, 0x30, 0x07, 0xc0, 0xc0, 0x37, 0xc7, 0x00,
  0xc0, 0x66, 0xc4, 0x00, 0x60, 0x66, 0xcc, 0x00, 0x60, 0x47, 0xcc, 0x00, 0x30, 0xc1, 0x18, 0x00,
  0x38, 0x00, 0x38, 0x00, 0x1c, 0x00, 0x70, 0x00, 0x07, 0x01, 0xc0, 0x00, 0x03, 0xff, 0x80, 0x00,
  0x00, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

// 30x51
const unsigned char WaterTemperatureImage[] PROGMEM = {
  0x00, 0x07, 0x00, 0x00, 0x00, 0x0f, 0x80, 0x00, 0x00, 0x19, 0xc0, 0x00, 0x00, 0x18, 0xc0, 0x00,
  0x00, 0x19, 0xc0, 0x00, 0x00, 0x1f, 0x80, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xe0, 0x00, 0x00, 0x07, 0xf8, 0x00, 0x00, 0x1e, 0x3c,
  0x00, 0x00, 0x18, 0x0c, 0x00, 0x00, 0x38, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00, 0x30, 0x00,
  0x00, 0x00, 0x30, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00, 0x30, 0x00, 0x07, 0xc0, 0x38, 0x08,
  0x0e, 0xe0, 0x1c, 0x1c, 0x18, 0x30, 0x0f, 0xf8, 0x18, 0x30, 0x03, 0xe0, 0x18, 0x30, 0x00, 0x00,
  0x18, 0x30, 0x00, 0x00, 0x18, 0x30, 0x00, 0x00, 0x18, 0x30, 0x00, 0x00, 0x19, 0x30, 0x00, 0x00,
  0x19, 0x30, 0x00, 0x00, 0x19, 0x30, 0x00, 0x00, 0x19, 0x30, 0x00, 0x00, 0x19, 0x30, 0x00, 0x00,
  0x19, 0x30, 0x00, 0x00, 0x19, 0x31, 0xc3, 0x84, 0x19, 0x37, 0x7e, 0xfc, 0x19, 0x3c, 0x18, 0x30,
  0x19, 0x30, 0x00, 0x00, 0x19, 0x30, 0x00, 0x00, 0x39, 0x38, 0x00, 0x00, 0x71, 0x1f, 0xe7, 0xcc,
  0x63, 0x8e, 0x3c, 0x78, 0xc7, 0xc6, 0x00, 0x00, 0xcf, 0xe6, 0x00, 0x00, 0xcf, 0xe6, 0x00, 0x00,
  0xcf, 0xe7, 0xc3, 0x84, 0xc7, 0xc7, 0xef, 0xdc, 0x63, 0x8e, 0x3c, 0x78, 0x70, 0x1c, 0x00, 0x00,
  0x38, 0x38, 0x00, 0x00, 0x1f, 0xf0, 0x00, 0x00, 0x07, 0xc0, 0x00, 0x00
};

// 30x51
const unsigned char WaterPumpImage[] PROGMEM = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1c, 0x00, 0x00,
  0x00, 0x3e, 0x00, 0x00, 0x01, 0xfe, 0x00, 0x00, 0x03, 0xfe, 0x00, 0x00, 0x06, 0x3c, 0x00, 0x00,
  0x04, 0x18, 0x00, 0x00, 0x04, 0x18, 0x00, 0x00, 0x04, 0xff, 0x80, 0x00, 0x04, 0xff, 0x80, 0x00,
  0x04, 0xff, 0xff, 0x00, 0x04, 0xff, 0xff, 0x80, 0x04, 0xff, 0xff, 0xc0, 0x04, 0xff, 0xff, 0xe0,
  0x04, 0xff, 0xff, 0xe0, 0x0c, 0xff, 0x83, 0xe0, 0x0c, 0xff, 0x83, 0xe0, 0x1c, 0x00, 0x07, 0xf8,
  0x18, 0x00, 0x07, 0xf8, 0x30, 0x3e, 0x00, 0x00, 0x70, 0x3e, 0x00, 0x00, 0x60, 0x3e, 0x01, 0xc0,
  0x00, 0x3e, 0x01, 0xc0, 0x00, 0x3e, 0x03, 0xe0, 0x00, 0x3e, 0x03, 0xe0, 0x00, 0x3e, 0x03, 0xe0,
  0x00, 0x3e, 0x01, 0xe0, 0x00, 0x3e, 0x00, 0x00, 0x00, 0x3e, 0x00, 0x00, 0x01, 0xff, 0xc0, 0x00,
  0x01, 0xff, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

#endif
