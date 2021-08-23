/***************************************************\
|Name: Detecting VBUS                               |
|Programmer: Michael James Salino-Hugg              |
|Date: February 27,2014                             |
|Description: Turns on pin 13 LED, establishes a    |
|             serial connection, and prints "Serial |
|             is connected" every second when VBUS  |
|             is high. It also ends the serial      |
|             connection and turns off the pin 13   |
|             LED when VBUS is low.                 |
\***************************************************/

void setup(){
   pinMode(13,OUTPUT);
   USBCON|=(1<<OTGPADE); //enables VBUS pad
}

void loop(){
   if(USBSTA&(1<<VBUS)){  //checks state of VBUS
      if(!Serial)
         Serial.begin(9600);
      digitalWrite(13,HIGH);
      Serial.println("Serial is connected");
   }
   else {
      if(Serial)
         Serial.end();
      digitalWrite(13,LOW);
   }
   delay(1000);
}
