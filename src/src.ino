#include "Arduino_LSM6DS3.h"

void setup() {
  Serial.begin(9600);
  while (!Serial);

  if (!IMU.begin(true)) {
    Serial.println("Failed to initialize IMU!");
    while (1);
  }

  // Measure the gyro's average drift over 250 ms and use that for correcting data later
  IMU.calibrate(500);

  Serial.print("Gyroscope sample rate = ");
  Serial.print(IMU.gyroscopeSampleRate());
  Serial.println(" Hz");
  Serial.print("Accelerometer sample rate = ");
  Serial.print(IMU.accelerationSampleRate());
  Serial.println(" Hz");
  Serial.println();
  Serial.println("Acceleration in G's: X, Y, Z, Gyroscope in degrees/second: X, Y, Z");
  delay(2000);
}

void loop() {
  float gX, gY, gZ, aX, aY, aZ;

  int count = IMU.unreadFifoSampleCount();
  if (IMU.fifoOverrun()) {
    Serial.println("FIFO Overflow! Stopping");
    while (true) {
      delay(100);
    }
  }
  /*
  if (IMU.accelerationAvailable()) {
    IMU.readAcceleration(aX, aY, aZ);
    Serial.println("\t" + String(aX) + "\t" + String(aY) + "\t" + String(aZ));
  }
  */
  if (count >= 6) {
      Serial.print(String(count) + "\t");
      IMU.readFifo();
      count = IMU.unreadFifoSampleCount();
      Serial.println(count);
  }
  // Serial.println(count);
  //IMU.readFifo();

  /*
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
  //*/
  
}
