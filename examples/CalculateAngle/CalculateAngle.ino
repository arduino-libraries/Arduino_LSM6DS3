#include <Arduino_LSM6DS3.h>

float x_error, y_error, z_error;
float angleX, angleY, angleZ;
float time_elapsed, current_time, prev_time;

void setup() {
  Serial.begin(9600);
  float x, y, z;

  if (!IMU.begin()) {
    Serial.println("Failed to initialize IMU!");
    while (1);
  }

  for (uint8_t count = 0; count < 200; count++) {
    if (IMU.gyroscopeAvailable())
      IMU.readGyroscope(x, y, z);
    x_error += x;
    y_error += y;
    z_error += z;
  }

  x_error /= 200;
  y_error /= 200;
  z_error /= 200;

  Serial.print("Gyroscope sample rate = ");
  Serial.print(IMU.gyroscopeSampleRate());
  Serial.println(" Hz");
  Serial.println();

  Serial.println("Angle in degrees");
  Serial.println("X\tY\tZ");
}

void loop() {
  float x, y, z;
  if (IMU.gyroscopeAvailable()) {
    prev_time = current_time;
    current_time = millis();
    time_elapsed = (current_time-prev_time)/1000; // millis to seconds

    IMU.readGyroscope(x, y, z);

    x -= x_error;
    y -= y_error;
    z -= z_error;

    angleX += (x * time_elapsed);
    angleY += (y * time_elapsed);
    angleZ += (z * time_elapsed);

    Serial.print(angleX);
    Serial.print('\t');
    Serial.print(angleY);
    Serial.print('\t');
    Serial.println(angleZ);
  }
}
