# watchx_code_examples
Collection of code personal code examples for WatchX

## I2C Addresses

0x0C -> Magnetometer MLX90393
0x68 -> RTC DS3231
0x69 -> Motion Pak MPU6050
0x76 -> Barometric Pressure and Temperature BMP280

The default address for the MPU6050 is 0x68 so you need to pass 0x69 or define MPU6050_ADDRESS as 0x69. All other devices are at there default addresses.


Screen Size 128x64
