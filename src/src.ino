#include "Arduino_LSM6DS3.h"

void setup() {
  Serial.begin(9600);
  while (!Serial);

  if (!IMU.begin()) {
    Serial.println("Failed to initialize IMU!");

    while (1);
  }

  Serial.print("Gyroscope sample rate = ");
  Serial.print(IMU.gyroscopeSampleRate());
  Serial.println(" Hz");
  Serial.print("Accelerometer sample rate = ");
  Serial.print(IMU.accelerationSampleRate());
  Serial.println(" Hz");
  Serial.println();
  Serial.println("Acceleration in G's: X, Y, Z, Gyroscope in degrees/second: X, Y, Z");
}

void loop() {
  float gX, gY, gZ, aX, aY, aZ;

  if (IMU.gyroscopeAvailable() && IMU.accelerationAvailable()) {
    IMU.readAcceleration(aX, aY, aZ);
    IMU.readGyroscope(gX, gY, gZ);

    Serial.print(aX);
    Serial.print('\t');
    Serial.print(aY);
    Serial.print('\t');
    Serial.print(aZ);
    Serial.print('\t');
    Serial.print(gX);
    Serial.print('\t');
    Serial.print(gY);
    Serial.print('\t');
    Serial.println(gZ);
  }
}
