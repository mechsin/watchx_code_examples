
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
Adafruit_SSD1306 display(OLED_DC, OLED_RESET, OLED_CS);

int xt = 0;

void setup() {
  // Start the serial console because you always
  // should incase you need to debug later
  Serial.begin(9600);

  //  Gen. display voltage from 3.3V
  display.begin(SSD1306_SWITCHCAPVCC);

}

void loop() {
  if (xt == SCREEN_WIDTH) {
    xt = 0;
  }

  xt += 1;
  display.clearDisplay();
  display.fillRect(xt, 0, 2, 2, WHITE);
  display.display();

  Serial.println(xt);
  delay(7);
}
