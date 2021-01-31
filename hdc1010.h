/*!
 * @file hdc1010.h
 *
 * This is a library for the HDC1010 I2C Temperature & Humidity Sensor
 *
 * Designed specifically to work with the Oak Development Technologies
 * HDC1010 Acorn
 * ----> urlhere
 *
 * The sensor uses I2C to communicate with additional pins that can be connected
 * to for other operational modes.
 *
 * Writen by Seth Kerr for Oak Development Technologies
 *
 * Please support additional open source libraries and hardware through your
 * purchases from Oak Development Technologies
 *
 * MIT License, can be used, modified, or copied under license terms
 *
 */

#ifndef HDC1010_HDC1010_H
#define HDC1010_HDC1010_H
#include "Arduino.h"

#include <Adafruit_BusIO_Register.h>
#include <Adafruit_I2CDevice.h>
#include <Wire.h>

// I2C Address (permanent, can not be changed)

#define HDC1010_ADDRESS (0x40) ///< default I2C Address
/*!
 * @brief   Alternative i2c addresses
 */
enum alt_i2c_addr {
  HDC1010_ADDR1 = (0x41),
  HDC1010_ADDR2 = (0x42),
  HDC1010_ADDR3 = (0x43),
};

//===========================================

// Registers

/*!
 * @brief   Information addresses for the AT42QT1070
 */

enum chip_info { HDC1010_DEVICE_ID };

/*!
 * @brief   register addresses for Keys
 */

enum {
  HDC1010_TEMP = (0x00),
  HDC1010_HUM = (0x01),
  HDC1010_CONF = (0x02),
  /*
   * Configuration register is set using 16 bit values
   * Bit 15: 0 cleared reset | 1 software reset
   * Bit 14: Reserved, always 0
   * Bit 13: Heat: 0 off/ 1 on
   * Bit 12: Mode
   * ~ 0 Temperature OR Humidity
   * ~ 1 Temperature AND Humidity
   * Bit 11: Battery Status
   * ~ 0 > 2.8V battery voltage
   * ~ 1 < 2.8V Battery voltage
   * Bit 10: Temperature Resolution
   * ~ 0 14 bit
   * ~ 1 11 bit
   * Bit 9/8: Humidity Resolution
   * ~ 00 14 bit
   * ~ 01 11 bit
   * ~ 10 8 bit (this will be default for this)
   * Bit 7: Reserved, always 0
   * Bit 6: Reserved, always 0
   * Bit 5: Reserved, always 0
   * Bit 4: Reserved, always 0
   * Bit 3: Reserved, always 0
   * Bit 2: Reserved, always 0
   * Bit 1: Reserved, always 0
   * Bit 0: Reserved, always 0
   *
   * Reset command value 0x0000000001101001 (0x0059)
   */
};

/*!
 * @brief HDC1010 Class object
 */
class HDC1010 {
public:
  // Hardware I2C
  HDC1010();

  bool begin(uint8_t i2caddr = HDC1010_ADDRESS);

  uint16_t readRegister16(uint8_t reg);
  uint8_t readRegister8(uint8_t reg);
  void writeRegister8(uint8_t reg, uint8_t value);
  void writeRegister16(uint8_t reg, uint16_t value);
  float getTemp(void);
  uint16_t getRawTemp(void);
  float getHum(void);
  uint16_t getRawHum(void);
  void setConfig(uint16_t configVal);

private:
  Adafruit_I2CDevice *i2c_dev = NULL;
};
#endif // HDC1010_HDC1010_H
