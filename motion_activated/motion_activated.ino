// Simple example of how to turn on the LED
// When motion in a certian range is detected
// by the accelerometer.

#include <Wire.h>
#include <MPU6050.h>

MPU6050 mpu;
Vector reading;
unsigned long activateDuration, activateTime = millis();

void setup()
{
  Serial.begin(115200);

  Serial.println("Initialize MPU6050");

  while (!mpu.begin(MPU6050_SCALE_2000DPS, MPU6050_RANGE_2G, 0x69))
  {
    Serial.println("Could not find a valid MPU6050 sensor, check wiring!");
    delay(500);
  }
}

void loop() {

  activateDuration = millis() - activateTime;
  if (activateDuration > 2000) {
    digitalWrite(13, LOW);
  }

  reading = mpu.readScaledAccel();
  if (0.3 < reading.XAxis && reading.XAxis < 0.8) {
    activateTime = millis();
    digitalWrite(13, HIGH);
  }

  //  Serial.print(reading.XAxis);
  //  Serial.print(",");
  //  Serial.print(reading.YAxis);
  //  Serial.print(",");
  //  Serial.println(reading.ZAxis);
  //
  //  delay(1000);
}
