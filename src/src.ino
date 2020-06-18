#include "Arduino_LSM6DS3.h"

bool useFifo = true;

void setup() {
  Serial.begin(9600);
  while (!Serial);

  if (!IMU.begin()) {
    Serial.println("Failed to initialize IMU!");
    while (1);
  }

  // Measure the gyro's average drift over 250 ms and use that for correcting data later
  IMU.calibrate(250);
  float cgX, cgY, cgZ;
  IMU.getGyroOffsets(cgX, cgY, cgZ);
  Serial.println("Gyro offsets =>\tX: " + String(cgX) + " \tY: " + String(cgY) + "\tZ: " + String(cgZ));
  //IMU.setGyroOffsets(0.0, 0.0, 0.0);

  if (useFifo)
    IMU.enableFifo();
}
void loop() {
  float gX, gY, gZ, aX, aY, aZ;

  if (useFifo) {
    int fifoLength = IMU.unreadFifoSampleCount();
    if (IMU.fifoOverrun()) {
      Serial.println("FIFO Overflow! Stopping");
      while (true) {
        delay(100);
      }
    }

    if (fifoLength >= 6) {
      Serial.print(String(fifoLength) + "\t"); // Count in FIFO before reading
      IMU.readFifo(); // Prints tab seperated values from FIFO
      Serial.println(IMU.unreadFifoSampleCount()); // Count in FIFO after reading
    }
  } else {
    if (IMU.accelerationAvailable() && IMU.gyroscopeAvailable()) {
      IMU.readAcceleration(aX, aY, aZ);
      IMU.readGyroscope(gX, gY, gZ);
      PrintValues(aX, aY, aZ, gX, gY, gZ);
      Serial.println();
    }
  }
}

void PrintValues(float aX, float aY, float aZ, float gX, float gY, float gZ) {
  if(aX >= 0)
    Serial.print(" ");
  Serial.print(String(aX) + "\t");

  if(aY >= 0)
    Serial.print(" ");
  Serial.print(String(aY) + "\t");

  if(aZ >= 0)
    Serial.print(" ");
  Serial.print(String(aZ) + "\t");

  if(gX >= 0)
    Serial.print(" ");
  Serial.print(String(gX) + "\t");

  if(gY >= 0)
    Serial.print(" ");
  Serial.print(String(gY) + "\t");

  if(gZ >= 0)
    Serial.print(" ");
  Serial.print(String(gZ));
}
