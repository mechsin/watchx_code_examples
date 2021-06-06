/*
 * Basic WatchX Watch Display
 * This program should display the current RTC time
 * on the OLED.
 */

// Both the RTC and OLED need the following 
// header files 
#include <Wire.h>

// Headers needed by the OLED
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// Headers needed by the RTC
#include <RTClib.h>

// This sets up the RTC I2C and other parameters
RTC_DS3231 rtc;

// SPI Setup for OLED
#define OLED_DC     A3
#define OLED_CS     A5
#define OLED_RESET  A4
Adafruit_SSD1306 display(OLED_DC, OLED_RESET, OLED_CS);

char timebuf[9];

void setDisplayText(){
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
}

void displaytime() {
  
  DateTime now = rtc.now();
  sprintf(timebuf, "%02i:%02i:%02i", now.hour(), now.minute(), now.second());

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println(timebuf);   
  display.display();
}

void setup() {  

  // Start the serial console because you always
  // should incase you need to debug later
  Serial.begin(9600);

  //  Gen. display voltage from 3.3V
  display.begin(SSD1306_SWITCHCAPVCC);

  if (! rtc.begin()) {
    display.clearDisplay();
    setDisplayText();
    display.println("Couldn't find RTC");
    while (1);
  }
  // If the RTC lost power then we set the RTC time 
  // to the date and time the sketch was compiled
  if (rtc.lostPower()) {
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    display.clearDisplay();
    setDisplayText();
    display.println("RTC lost power");
    display.display();
    delay(2000);
    
  }
  
}

void loop() {
  displaytime();
  delay(1000);
}
