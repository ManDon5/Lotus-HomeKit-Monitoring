/*
  LotusDisplay.cpp - Library for displaying Lotus state on
  a Waveshare 2.13 inch b/w eInk display (V3) with a resolution of 255x122.
  Created by Manuel Donaubauer, December 18, 2022.
*/

#ifndef LotusDisplay_h
#define LotusDisplay_h

#include "Arduino.h"
#include "GxEPD2_BW.h"

const long HIBERNATE_INTERVAL = 15000;
const uint16_t DISPLAY_Y_OFFSET = 6;
const uint16_t IMAGE_WIDTH = 30;
const uint16_t IMAGE_HEIGHT = 51;
const uint16_t IMAGE_BORDER_SPACING = 5;
const uint16_t SEPARATOR_LINE_THICKNESS = 1;

class LotusDisplay {

public:
  LotusDisplay(int16_t cs, int16_t dc, int16_t rst, int16_t busy);
  void startUp();
  void showEnvironmentalTemperature(double temperature);
  void showEnvironmentalHumidity(int humidity);
  void showWaterTemperature(double temperature);
  void showWaterPumpOn(boolean isOn);
  void checkHibernate();

private:
  GxEPD2_BW<GxEPD2_213_BN, GxEPD2_213_BN::HEIGHT> *display;

  unsigned long previousMillis = 0;
  boolean isHibernating = false;

  uint16_t verticalSeparatorLineX;
  uint16_t horizontalSeparatorLineY;
  uint16_t leftImageX;
  uint16_t rightImageX;
  uint16_t topImageY;
  uint16_t bottomImageY;
  uint16_t leftTextWindowX;
  uint16_t rightTextWindowX;
  uint16_t topTextWindowY;
  uint16_t bottomTextWindowY;
  uint16_t leftTextWindowWidth;
  uint16_t rightTextWindowWidth;
  uint16_t textWindowHeight;

  String environmentalTemperatureText;
  String environmentalHumidityText;
  String waterTemperatureText;
  String waterPumpOnText;

  enum PartialWindowPosition {
    TOP_LEFT,
    TOP_RIGHT,
    BOTTOM_LEFT,
    BOTTOM_RIGHT
  };

  void updatePartialWindow(String text, PartialWindowPosition position);
};

#endif