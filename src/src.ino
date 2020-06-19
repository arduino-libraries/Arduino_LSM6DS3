#include "Arduino_LSM6DS3.h"

#define FIFO_READ_BUFFER_SIZE 50
bool useFifo = true;
float values[FIFO_READ_BUFFER_SIZE][6];
size_t length = 0;

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
    int fifoLength = IMU.fifoLength();
    if (IMU.fifoOverrun()) {
      Serial.println("FIFO Overflow! Stopping");
      while (true) {
        delay(100);
      }
    }

    if (fifoLength >= 12) {
      IMU.fifoRead(values, length, fifoLength / 6, FIFO_READ_BUFFER_SIZE);
      for (int i = 0; i < length; ++i) {
        PrintValues(
          values[i][0],
          values[i][1],
          values[i][2],
          values[i][3],
          values[i][4],
          values[i][5]
        );
        Serial.println();
      }
      Serial.println("-----------------------------------------------");
      delay(200);
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
