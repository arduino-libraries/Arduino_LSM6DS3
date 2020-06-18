/*
  This file is part of the Arduino_LSM6DS3 library.
  Copyright (c) 2019 Arduino SA. All rights reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>


class LSM6DS3Class {
  public:
    LSM6DS3Class(TwoWire& wire, uint8_t slaveAddress);
    LSM6DS3Class(SPIClass& spi, int csPin, int irqPin);
    virtual ~LSM6DS3Class();

    int begin(bool useFIFO = false);
    bool calibrate(int calibrationTimeMs);
    void end();

    // Accelerometer
    virtual int readAcceleration(float& x, float& y, float& z); // Results are in G (earth gravity).
    virtual float accelerationSampleRate(); // Sampling rate of the sensor.
    virtual int accelerationAvailable(); // Check for available data from accerometer

    // Gyroscope
    virtual int readGyroscope(float& x, float& y, float& z); // Results are in degrees/second.
    virtual float gyroscopeSampleRate(); // Sampling rate of the sensor.
    virtual int gyroscopeAvailable(); // Check for available data from gyroscopeAvailable

    // FIFO
    virtual int unreadFifoSampleCount();
    virtual bool readFifo();
    virtual bool fifoOverrun();
    virtual void clearFifoFlags();


  private:
    int readRegister(uint8_t address);
    int readRegisters(uint8_t address, uint8_t* data, size_t length);
    int writeRegister(uint8_t address, uint8_t value);


  private:
    TwoWire* _wire;
    SPIClass* _spi;
    uint8_t _slaveAddress;
    int _csPin;
    int _irqPin;
    
    bool _fifoEnabled = false;
    bool _fifoOverRunFlag = false;

    float _gyroXDrift = 0.0;
    float _gyroYDrift = 0.0;
    float _gyroZDrift = 0.0;

    SPISettings _spiSettings;
};

extern LSM6DS3Class IMU;
