#include "Arduino_LSM6DS3.h"

#define FIFO_READ_BUFFER_SIZE 50
bool useFifo = true;
float values[FIFO_READ_BUFFER_SIZE][FIFO_DATASET_WIDTH];
size_t length = 0;

#define MAX_SAMPLE_COUNT 100
int currentSampleCount = 0;

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
  Serial.println("Enabling FIFO in 3 seconds");
  delay(3000);

  if (useFifo)
    IMU.enableFifo();
}
void loop() {
  if (currentSampleCount >= MAX_SAMPLE_COUNT) {
    Serial.println("Passed the max sample count. Stopping to make the log easier to read.");
    while (true) {
        delay(100);
    }
  }
  float gX, gY, gZ, aX, aY, aZ;

  if (useFifo) {
    int fifoLength = IMU.fifoLength();
    if (IMU.fifoOverrun()) {
      Serial.println("FIFO Overflow! Stopping");
      while (true) {
        delay(100);
      }
    }
    if (fifoLength >= 24) {
      IMU.fifoRead(values, length, fifoLength / FIFO_DATASET_WIDTH, FIFO_READ_BUFFER_SIZE);
      for (int i = 0; i < length; ++i) {
        PrintValues(
          values[i],
          FIFO_DATASET_WIDTH
        );
        Serial.println();
        currentSampleCount++;
      }
      Serial.println("-----------------------------------------------");
      delay(100);
    }
  } else {
    if (IMU.accelerationAvailable() && IMU.gyroscopeAvailable()) {
      IMU.readAcceleration(aX, aY, aZ);
      IMU.readGyroscope(gX, gY, gZ);
      PrintValues(aX, aY, aZ, gX, gY, gZ);
      Serial.println();
      currentSampleCount++;
    }
  }
}

void PrintValues(float values[], size_t length) {
  for (int i = 0; i < length; ++i) {
    if (values[i] >= 0)
      Serial.print(" ");
    Serial.print(String(values[i]) + "\t");
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
