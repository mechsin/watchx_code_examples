
#include <Wire.h>
#include <MPU6050.h>

MPU6050 mpu;
Vector reading;

void setup() 
{
  Serial.begin(115200);

  Serial.println("Initialize MPU6050");

  while(!mpu.begin(MPU6050_SCALE_2000DPS, MPU6050_RANGE_2G, 0x69))
  {
    Serial.println("Could not find a valid MPU6050 sensor, check wiring!");
    delay(500);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  reading = mpu.readScaledAccel();
  if (0.3 < reading.XAxis && reading.XAxis < 0.8) {
    digitalWrite(13, HIGH);
  } else {
    digitalWrite(13, LOW);
  }
//  Serial.print(reading.XAxis);
//  Serial.print(",");
//  Serial.print(reading.YAxis);
//  Serial.print(",");
//  Serial.println(reading.ZAxis);
//  
//  delay(1000);
}
