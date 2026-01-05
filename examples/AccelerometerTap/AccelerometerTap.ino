/*
  Arduino LSM6DS3 - Accelerometer Tap

  this code is to detect tap
  using IMU.accelerationAvailable()
*/

#include <Arduino_LSM6DS3.h>

float tapThreshold  ;
float xi, yi , zi ; 

void setup() {
  
  Serial.begin(9600);

  while (!Serial);
  
  while (!IMU.begin()) {
    Serial.println("Failed to initialize IMU!");
    delay(3000); // wait for 3 sec and check if it can be initialized again
  }
  
  if (IMU.accelerationAvailable()) {
    IMU.readAcceleration(xi, yi, zi); //To set initial values of acceleration, including gravity and some zero error.
  }
  
  tapThreshold  = 0.05; //0.05 g acceleration in some direction is considered as tap. it can be changed for the required sensitivity.
}

void loop() {
  float x, y, z;
  if (IMU.accelerationAvailable()) {
    IMU.readAcceleration(x, y, z);
    
    // works on the difference from initial acceleration to the current acceleration
    if (x -xi > tapThreshold || x-xi < -tapThreshold){
      Serial.println("Tap detected across X-axis");
    }

    if (y-yi > tapThreshold || y-yi < -tapThreshold){
      Serial.println("Tap detected across Y-axis");
    }

    if (z-zi > tapThreshold || z-zi < -tapThreshold)   {
      Serial.println("Tap detected across Z-axis");
    }
  }
}
