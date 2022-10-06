/*
  This file is part of the ArduinoIMU library.
  Copyright (c) 2022 Arduino SA. All rights reserved.

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

#ifndef _ARUDINO_IMU_H_
#define _ARUDINO_IMU_H_

#include "Arduino.h"

#if defined __has_include
  #define HAS_INCLUDE_IMU     __has_include("Arduino_LSM6DSOX.h") ||  __has_include("Arduino_LSM6DS3.h") || __has_include("Arduino_LSM9DS1.h")
#endif
#endif

