
#include "display.h"

void drawStarField(int numStars) {
  int k;
  int xpos, ypos;
  // put your main code here, to run repeatedly:
  display.clearDisplay();
  for (k=0; k < numStars; k++) {
    xpos = random(0, SCREEN_WIDTH);
    ypos = random(0, SCREEN_HEIGHT);
    display.drawPixel(xpos, ypos, WHITE);
  }
  display.display();
}
  

void setup() {
  // Start the serial console because you always
  // should in case you need to debug later
  Serial.begin(9600);

  // Generate display voltage at 3.3V
  display.begin(SSD1306_SWITCHCAPVCC);
  drawStarField(250);
}

void loop() {

}
