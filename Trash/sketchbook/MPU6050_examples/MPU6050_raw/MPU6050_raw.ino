#include "I2Cdev.h"
#include "MPU6050.h"

#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
#include "Wire.h"
#endif

MPU6050 accelgyro;

int16_t ax, ay, az;
int16_t gx, gy, gz;

int16_t old_ax, old_ay, old_az;
int16_t old_gx, old_gy, old_gz;

void setup() 
{
  old_ax = -1;
  old_ay = -1;
  old_az = -1;

  old_gx = -1;
  old_gy = -1;
  old_gz = -1;

#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
  Wire.begin();
#elif I2CDEV_IMPLEMENTATION == I2CDEV_BUILTIN_FASTWIRE
  Fastwire::setup(400, true);
#endif

  Serial.begin(9600);

  Serial.println("Initializing I2C devices...");
  accelgyro.initialize();

  Serial.println("Testing device connections...");
  Serial.println(accelgyro.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");
}

void loop() 
{
  accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

  if(ax != old_ax)
  {
    old_ax = ax;
    Serial.print("ax = ");
    Serial.println(ax);
  }
  if(ay != old_ay)
  {
    old_ay = ay;
    Serial.print("ay = ");
    Serial.println(ay);
  }
  if(az != old_az)
  {
    old_az = az;
    Serial.print("az = ");
    Serial.println(az);
  }

  if(gx != old_gx)
  {
    old_gx = gx;
    Serial.print("gx = ");
    Serial.println(gx);
  }
  if(gy != old_gy)
  {
    old_gy = gy;
    Serial.print("gy = ");
    Serial.println(gy);
  }
  if(gz != old_gz)
  {
    old_gz = gz;
    Serial.print("gz = ");
    Serial.println(gz);
  }
  delay(1000);
}


