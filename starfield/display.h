/*
 * This is a header file for the WatchX display
 * it contains the correct settings for the 
 * display.
 */

// Both the RTC and OLED need the following
// header files
#include <Wire.h>

// Headers needed by the OLED
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// SPI Setup for OLED and create display object
#define OLED_DC     A3
#define OLED_CS     A5
#define OLED_RESET  A4
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &SPI, OLED_DC, OLED_RESET, OLED_CS);

void setDisplayText(){
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
}
