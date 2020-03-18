/*
  Arduino LSM6DS3 - Simple Gyroscope

  This example reads the temperature values from the LSM6DS3
  sensor and continuously prints them to the Serial Monitor
  or Serial Plotter.

  The circuit:
  - Arduino Uno WiFi Rev 2 or Arduino Nano 33 IoT

  created 15 Mar 2020
  by Alex Hoppe

  This example code is in the public domain.
*/

#include <Arduino_LSM6DS3.h>

void setup() {
  Serial.begin(9600);
  while (!Serial);

  if (!IMU.begin()) {
    Serial.println("Failed to initialize IMU!");

    while (1);
  }

  Serial.print("Temperature sensor sample rate = ");
  Serial.print(IMU.temperatureSampleRate());
  Serial.println(" Hz");
  Serial.println();
  Serial.println("Temperature reading in degrees C");
  Serial.println("T");
}

void loop() {
  float t;

  if (IMU.temperatureAvailable()) {
    // after IMU.readTemperature() returns, t will contain the temperature reading
    IMU.readTemperature(t);

    Serial.println(t);
  }
}
