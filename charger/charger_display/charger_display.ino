


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
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT,
  &SPI, OLED_DC, OLED_RESET, OLED_CS);

// Setup Battery Pins
#define BATTERY_PIN A11


// These functions help move the
// dot back and forth across the screen
// We xt is the location to move to
// Direction is a function pointer to either
// the left or right function
int xt = 0;
int (*direction)(int*);

int left(int *val) {
  *val -= 1;
}

int right(int *val) {
  *val += 1;
}

// Variables for battery reading
char buf[6];
float battVoltage = 0;
unsigned int lastReading = 0;
unsigned int currentReading = 0;

// Function that updates float pointer with the
// current percentage of charge on the battery
void readBattery(float *reading) {

  digitalWrite(4, HIGH);
  *reading = analogRead(BATTERY_PIN);
  *reading = (*reading / 1024) * 3.35;
  *reading = *reading * (20000 / 10000);
  digitalWrite(4, LOW);

  return 0;
}

void setup() {
  // Start the serial console because you always
  // should incase you need to debug later
  Serial.begin(9600);

  // Generate display voltage from 3.3V
  display.begin(SSD1306_SWITCHCAPVCC);

}

void loop() {

  // If the current position of the dot is at the
  // end of the screen (right) start moving left
  if (xt == SCREEN_WIDTH) {
    direction = &left;
  }

  // If the current position of the dot is at the
  // end of the screen (left) then start moving right
  if (xt == 0) {
    direction = &right;
  }

  // Update the dot xt and draw the dot
  direction(&xt);
  display.clearDisplay();
  display.fillRect(xt, 0, 2, 2, WHITE);

  // Write the battery reading closer to the
  // center of the screen
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);

  if (((unsigned int) millis() - lastReading) > 1000) {
    lastReading = millis();
    readBattery(&battVoltage);
    dtostrf((100 / 4.2) * battVoltage, 3, 1, buf);
  }
  display.println(buf);

  // Display the dot and the battery reading
  display.display();

  // Delay at bit so the dot doesn't move to fast
  delay(2.5);
}
