

namespace LSM6DS3 {
  /* Bit:    7            6             5        4     3            2           1            0
   * --------------------------------------------------------------------------------------------------
   * |  LPF2_XL_EN  |  HPCF_XL1  |  HPCF_XL0  |  0  |  0  |  HP_SLOPE_XL_EN  |  0  |  LOW_PASS_ON_6D  |
   * --------------------------------------------------------------------------------------------------
   */
  enum AccelerometerFilter {
    NONE = B00000000,
    LOW_PASS_50_HZ = B10000000,
    LOW_PASS_100_HZ = B10100000,
    LOW_PASS_9_HZ = B11000000,
    LOW_PASS_400_HZ = B11100000,
    LOW_PASS_50_HZ_ON_6D = B10000001,
    LOW_PASS_100_HZ_ON_6D = B10100001,
    LOW_PASS_9_HZ_ON_6D = B11000001,
    LOW_PASS_400_HZ_ON_6D = B11100001,
    SLOPE_4_HZ = B00000100,
    HIGH_PASS_100_HZ = B00100100,
    HIGH_PASS_9_HZ = B01000100,
    HIGH_PASS_400_HZ = B01100100
  };


}