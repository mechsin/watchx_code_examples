// EnableInterrupt Simple example sketch. Demonstrates operation on a single pin of your choice.
// See https://github.com/GreyGnome/EnableInterrupt and the README.md for more information.
#include <EnableInterrupt.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <avr/sleep.h>
#include "RTClib.h"
#include <Wire.h>
#include <MPU6050.h>
#include "watchx_display.h"

// Uncomment this block to use hardware SPI
#define BUTTON1 8
#define R1 10000
#define R2 10000
#define VOLTAGEDIV 0.5
#define BATTERYENERGY 4
#define BATTERYINPUT A11
//
//#define BLE_REQ               A2
//#define BLE_RDY              0
//#define BLE_RST              A1    // Optional but recommended, set to -1 if unused
//
//BLEPeripheral           blePeripheral        = BLEPeripheral(BLE_REQ, BLE_RDY, BLE_RST);
//Adafruit_BluefruitLE_SPI ble(BLUEFRUIT_SPI_CS, BLUEFRUIT_SPI_IRQ, BLUEFRUIT_SPI_RST);
RTC_DS3231 rtc;
MPU6050 mpu;
int interruptCount=0;
int count=0;
DateTime usbtime;
DateTime now;
void interruptFunction() {
 interruptCount++;
 display.ssd1306_command(SSD1306_DISPLAYON);
}
void setup() {
 rtc.begin();
 rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
 display.begin(SSD1306_SWITCHCAPVCC);
 pinMode(BUTTON1, INPUT_PULLUP);
 // turn off accelerometer
 mpu.begin(MPU6050_SCALE_2000DPS, MPU6050_RANGE_2G);
 mpu.setSleepEnabled(true);
 display.setTextSize(2);
 display.setTextColor(WHITE);
}
float batteryLevel=0;
float usbbatteryLevel=0;
void showBattery(){
 digitalWrite(BATTERYENERGY, HIGH);
 delay(50);
 float voltage = analogRead(BATTERYINPUT);
 voltage = (voltage / 1024) * 3.35;
 voltage = voltage / VOLTAGEDIV;
 delay(50);
 digitalWrite(BATTERYENERGY, LOW);
 batteryLevel = (voltage - 3.38) / 0.0084;
 display.setCursor(0, 20);
 display.print("Bat:");
 display.print((int) batteryLevel);
 display.print("%");
 int minsinceusb = 60 * (now.hour()-usbtime.hour()) + now.minute()-usbtime.minute();
 display.setCursor(0, 40);
//  display.print(minsinceusb);
 float batdiff = (usbbatteryLevel - batteryLevel);
 if (batdiff > 0 && minsinceusb > 0){
   float minleft = batteryLevel*minsinceusb/batdiff;
   display.print(" Min:");
   display.print((int) minleft);
 }
}
void showTime(){
 char timebuf[9];
 now = rtc.now();
 sprintf(timebuf, "%02i:%02i:%02i", now.hour(), now.minute(), now.second());
 display.print(timebuf);
}
bool IsUSBConnected(){
 return(UDADDR & _BV(ADDEN));
}
void loop() {
 display.clearDisplay();
 display.setCursor(0,0);
 showTime();
 showBattery();
  if (IsUSBConnected()){  // check if USB is connected.
       display.print("C");
       usbtime= rtc.now();
       usbbatteryLevel = batteryLevel;
      if (count >= 100) {
         count = 0;
         display.ssd1306_command(SSD1306_DISPLAYOFF);
     }
     if (digitalRead(BUTTON1) == 0) {
         display.ssd1306_command(SSD1306_DISPLAYON);
     }
  }else{
   if (count >= 20) {
     delay(500);     // this delay is needed, the sleep
     count = 0;
     sleepNow();     // sleep function called here
   }
 }
 count++;
 count = count % 1000;
 display.display();
}
void sleepNow()         // here we put the arduino to sleep
{
   display.ssd1306_command(SSD1306_DISPLAYOFF);
   /* Now is the time to set the sleep mode. In the Atmega8 datasheet
    * http://www.atmel.com/dyn/resources/prod_documents/doc2486.pdf on page 35
    * there is a list of sleep modes which explains which clocks and
    * wake up sources are available in which sleep mode.
    *
    * In the avr/sleep.h file, the call names of these sleep modes are to be found:
    *
    * The 5 different modes are:
    *     SLEEP_MODE_IDLE         -the least power savings
    *     SLEEP_MODE_ADC
    *     SLEEP_MODE_PWR_SAVE
    *     SLEEP_MODE_STANDBY
    *     SLEEP_MODE_PWR_DOWN     -the most power savings
    *
    * For now, we want as much power savings as possible, so we
    * choose the according
    * sleep mode: SLEEP_MODE_PWR_DOWN
    *
    */
   set_sleep_mode(SLEEP_MODE_PWR_DOWN);   // sleep mode is set here
   sleep_enable();          // enables the sleep bit in the mcucr register
                            // so sleep is possible. just a safety pin
   /* Now it is time to enable an interrupt. We do it here so an
    * accidentally pushed interrupt button doesn't interrupt
    * our running program. if you want to be able to run
    * interrupt code besides the sleep function, place it in
    * setup() for example.
    *
    * In the function call attachInterrupt(A, B, C)
    * A   can be either 0 or 1 for interrupts on pin 2 or 3.
    *
    * B   Name of a function you want to execute at interrupt for A.
    *
    * C   Trigger mode of the interrupt pin. can be:
    *             LOW        a low level triggers
    *             CHANGE     a change in level triggers
    *             RISING     a rising edge of a level triggers
    *             FALLING    a falling edge of a level triggers
    *
    * In all but the IDLE sleep modes only LOW can be used.
    */
  enableInterrupt(BUTTON1, interruptFunction, CHANGE);
   sleep_mode();            // here the device is actually put to sleep!!
                            // THE PROGRAM CONTINUES FROM HERE AFTER WAKING UP
   sleep_disable();         // first thing after waking from sleep:
                            // disable sleep...
   disableInterrupt(BUTTON1);      // disables interrupt 0 on pin 2 so the
                            // wakeUpNow code will not be executed
                            // during normal running time.
}
