
#include "display.h"

char*  reminderList [] = {
          "One",
          "Two",
          "Three",
          "Four",
          "Five",
          "Six",
          "Seven",
          "Eight",
          "Nine",
          "Ten"
};

void setup() {
  int k;
  // Start the serial console because you always
  // should in case you need to debug later
  Serial.begin(9600);

  // Generate display voltage at 3.3V
  display.begin(SSD1306_SWITCHCAPVCC);
  
  // put your setup code here, to run once:
  display.clearDisplay();
  setDisplayText();
  for (k = 0; k < sizeof(reminderList) / sizeof(*reminderList); k++) {
  display.println(reminderList[k]);
  };
   
  display.display();

}

void loop() {
  // put your main code here, to run repeatedly:

}
