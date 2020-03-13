/* 
  Arduino LSM6DS3 - Accelerometer Tap

  this code is to detect tap

  usign IMU.accelerationAvailable()

  Made by
  tanmay khabia

*/

#include <Arduino_LSM6DS3.h>

void setup() {
  Serial.begin(9600);

  while (!Serial);

  while (!IMU.begin()) {

    Serial.println("Failed to initialize IMU!");

    delay (3000); // wait for 3 sec and check if it can be initialize again

  }

}

float tapThreshold  = 0.05 ; //0.05g acceleration in some direction is considered as tap. it can be change for the required sensitivity.

void loop() {

  float x, y, z;

  if (IMU.accelerationAvailable()) {

    IMU.readAcceleration(x, y, z);

    if (x > tapThreshold || x < -tapThreshold) {

      Serial.println("Tap detected across X-axis");
    }
    if (y > tapThreshold || y < -tapThreshold) {

      Serial.println("Tap detected across Y-axis");
    }
    if (z > tapThreshold || z < -tapThreshold) {

      Serial.println("Tap detected across Z-axis");
    }
  }

}
