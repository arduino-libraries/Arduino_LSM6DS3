#include <Arduino_LSM6DS3.h>

#define MAX_SAMPLE_COUNT 100
int currentSampleCount = 0;

#define FIFO_READ_BUFFER_SIZE 50
// FIFO_SAMPLE_WIDTH defined in LSM6DS3.h
float buffer[FIFO_READ_BUFFER_SIZE][FIFO_SAMPLE_WIDTH];
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
  //IMU.setGyroOffsets(0.0, 0.0, 0.0); // Uncomment this line to set offsets back to 0

  IMU.enableFifo();
}

void loop() {
  // Do something that takes a lot of time. In this case, nothing.
  delay(100);
  // Read any gyro/accelerometer values missed while busy
  CheckIMU();
}

void CheckIMU() {
  // Stop if we've reached the max sample count.
  if (currentSampleCount >= MAX_SAMPLE_COUNT) {
    Serial.println("Passed the max sample count. Stopping to make the log easier to read.");
    while (true) {
      delay(100);
    }
  }

  // Check if the fifo has overrun
  // call IMU.fifoReset() to reset the fifo if your usecase permits the loss of data
  if (IMU.fifoOverrun()) {
    Serial.println("FIFO Overrun! Stopping!");
    while (true) {
      delay(100);
    }
  }

  // Read as many sample sets will fit in our buffer
  length = IMU.fifoRead(buffer, FIFO_READ_BUFFER_SIZE);

  if (length > 0) {
    // Print tab delimited header
    Serial.println("gX\tgY\tgZ\taX\taY\taZ");

    // Loop through each sample set and print them
    for (int i = 0; i < length; ++i) {
      PrintValues(buffer[i], FIFO_SAMPLE_WIDTH);
      Serial.println();
      currentSampleCount++;
    } 
    Serial.println("-----------------------------------------------");
  }
}

void PrintValues(float values[], size_t length) {
  for (int i = 0; i < length; ++i) {
    if (values[i] >= 0)
      Serial.print(" ");
    Serial.print(String(values[i]) + "\t");
  }
}
