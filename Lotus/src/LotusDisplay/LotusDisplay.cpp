/*
  LotusDisplay.cpp - Library for displaying Lotus state on
  a Waveshare 2.13 inch b/w eInk display (V3) with a resolution of 255x122.
  Created by Manuel Donaubauer, December 18, 2022.
*/

#include "Arduino.h"
#include "LotusDisplay.h"
#include "LotusImages.h"
#include "GxEPD2_BW.h"
#include "Fonts/FreeSansBold18pt7b.h"

LotusDisplay::LotusDisplay(int16_t cs, int16_t dc, int16_t rst, int16_t busy) {
  display = new GxEPD2_BW<GxEPD2_213_BN, GxEPD2_213_BN::HEIGHT>(GxEPD2_213_BN(cs, dc, rst, busy));

  display->init(115200);
  display->setRotation(1);
  display->setFont(&FreeSansBold18pt7b);
  display->setTextColor(GxEPD_BLACK);

  verticalSeparatorLineX = display->width() / 2;                                             // = 125
  horizontalSeparatorLineY = (display->height() - DISPLAY_Y_OFFSET) / 2 + DISPLAY_Y_OFFSET;  // = 67

  leftImageX = display->width() / 2 - IMAGE_BORDER_SPACING - IMAGE_WIDTH;                            // = 90
  rightImageX = display->width() - IMAGE_BORDER_SPACING - IMAGE_WIDTH;                               // = 215
  topImageY = DISPLAY_Y_OFFSET + IMAGE_BORDER_SPACING;                                               // = 11
  bottomImageY = topImageY + (display->height() - DISPLAY_Y_OFFSET) / 2 + SEPARATOR_LINE_THICKNESS;  // = 73

  leftTextWindowX = 0;
  rightTextWindowX = display->width() / 2 + SEPARATOR_LINE_THICKNESS;                                           // = 126
  topTextWindowY = DISPLAY_Y_OFFSET + IMAGE_BORDER_SPACING;                                                     // = 11
  bottomTextWindowY = topTextWindowY + (display->height() - DISPLAY_Y_OFFSET) / 2 + SEPARATOR_LINE_THICKNESS;   // = 73
  leftTextWindowWidth = display->width() / 2 - IMAGE_BORDER_SPACING - IMAGE_WIDTH;                              // = 90
  rightTextWindowWidth = leftTextWindowWidth - SEPARATOR_LINE_THICKNESS;                                        // = 84
  textWindowHeight = (display->height() - DISPLAY_Y_OFFSET) / 2 - IMAGE_BORDER_SPACING - IMAGE_BORDER_SPACING;  // = 51
}

void LotusDisplay::startUp() {
  String placeholder = "--";
  int16_t tbx, tby;
  uint16_t tbw, tbh;
  display->getTextBounds(placeholder, 0, 0, &tbx, &tby, &tbw, &tbh);
  uint16_t leftTextX = leftTextWindowWidth / 2 - tbw / 2;
  uint16_t topTextY = topTextWindowY + textWindowHeight / 2 + tbh / 2;
  uint16_t rightTextX = rightTextWindowX + rightTextWindowWidth / 2 - tbw / 2;
  uint16_t bottomTextY = bottomTextWindowY + textWindowHeight / 2 + tbh / 2;

  display->setFullWindow();
  display->firstPage();

  do {
    display->fillScreen(GxEPD_WHITE);

    // Draw separator lines
    display->drawLine(0, horizontalSeparatorLineY, display->width(), horizontalSeparatorLineY, GxEPD_BLACK);
    display->drawLine(verticalSeparatorLineX, 0, verticalSeparatorLineX, display->height(), GxEPD_BLACK);

    // Draw images
    display->drawBitmap(leftImageX, topImageY, EnvironmentalTemperatureImage, IMAGE_WIDTH, IMAGE_HEIGHT, GxEPD_BLACK);
    display->drawBitmap(rightImageX, topImageY, EnvironmentalHumidityImage, IMAGE_WIDTH, IMAGE_HEIGHT, GxEPD_BLACK);
    display->drawBitmap(leftImageX, bottomImageY, WaterTemperatureImage, IMAGE_WIDTH, IMAGE_HEIGHT, GxEPD_BLACK);
    display->drawBitmap(rightImageX, bottomImageY, WaterPumpImage, IMAGE_WIDTH, IMAGE_HEIGHT, GxEPD_BLACK);

    // Print placeholder text
    display->setCursor(leftTextX, topTextY);
    display->print(placeholder);
    display->setCursor(rightTextX, topTextY);
    display->print(placeholder);
    display->setCursor(leftTextX, bottomTextY);
    display->print(placeholder);
    display->setCursor(rightTextX, bottomTextY);
    display->print(placeholder);
  } while (display->nextPage());

}

void LotusDisplay::showEnvironmentalTemperature(double temperature) {
  String temperatureText = String(temperature, 1);
  if (environmentalTemperatureText == temperatureText) { return; }
  environmentalTemperatureText = temperatureText;
  updatePartialWindow(temperatureText, TOP_LEFT);
}

void LotusDisplay::showEnvironmentalHumidity(int humidity) {
  String humidityText = String(humidity);
  if (environmentalHumidityText == humidityText) { return; }
  environmentalHumidityText = humidityText;
  updatePartialWindow(humidityText, TOP_RIGHT);
}

void LotusDisplay::showWaterTemperature(double temperature) {
  String temperatureText = String(temperature, 1);
  if (waterTemperatureText == temperatureText) { return; }
  waterTemperatureText = temperatureText;
  updatePartialWindow(temperatureText, BOTTOM_LEFT);
}

void LotusDisplay::showWaterPumpOn(boolean isOn) {
  String isOnText = isOn ? "EIN" : "AUS";
  if (waterPumpOnText == isOnText) { return; }
  waterPumpOnText = isOnText;
  updatePartialWindow(isOnText, BOTTOM_RIGHT);
}

void LotusDisplay::checkHibernate() {
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= HIBERNATE_INTERVAL && !isHibernating) {
    previousMillis = currentMillis;
    display->hibernate();
    isHibernating = true;
  }
}

void LotusDisplay::updatePartialWindow(String text, PartialWindowPosition position) {
  uint16_t textWindowX;
  uint16_t textWindowY;
  uint16_t textWindowWidth;

  switch (position) {
    case TOP_LEFT:
      textWindowX = leftTextWindowX;
      textWindowY = topTextWindowY;
      textWindowWidth = leftTextWindowWidth;
      break;
    case TOP_RIGHT:
      textWindowX = rightTextWindowX;
      textWindowY = topTextWindowY;
      textWindowWidth = rightTextWindowWidth;
      break;
    case BOTTOM_LEFT:
      textWindowX = leftTextWindowX;
      textWindowY = bottomTextWindowY;
      textWindowWidth = leftTextWindowWidth;
      break;
    case BOTTOM_RIGHT:
      textWindowX = rightTextWindowX;
      textWindowY = bottomTextWindowY;
      textWindowWidth = rightTextWindowWidth;
      break;
  }
  int16_t tbx, tby;
  uint16_t tbw, tbh;
  display->getTextBounds(text, 0, 0, &tbx, &tby, &tbw, &tbh);
  uint16_t textX = textWindowX + textWindowWidth / 2 - tbw / 2;
  uint16_t textY = textWindowY + textWindowHeight / 2 + tbh / 2;

  display->setPartialWindow(textWindowX, textWindowY, textWindowWidth, textWindowHeight);
  display->firstPage();

  do {
    display->fillScreen(GxEPD_WHITE);
    display->setCursor(textX, textY);
    display->print(text);
  } while (display->nextPage());

  unsigned long currentMillis = millis();
  previousMillis = currentMillis;
  isHibernating = false;
}