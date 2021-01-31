/*!
 * @file hdc1010.cpp
 *
 * @mainpage Oak Development Technologies hdc1010 Arduino Driver
 *
 * @section intro_sec Introduction
 *
 * This is a library for the TI HDC1010 Temperature & Humidity Sensor
 *
 * Designed specifically to work with the Oak Development Technologies
 * HDC1010 Acorn
 * ----> urlhere
 *
 * The sensor uses I2C to communicate with additional pins that can be connected
 * to for other operational modes.
 *
 * @section author Author
 *
 * Writen by Seth Kerr for Oak Development Technologies
 *
 * Please support additional open source libraries and hardware through your
 * purchases from Oak Development Technologies
 *
 * @section license License
 *
 * MIT License, can be used, modified, or copied under license terms
 *
 */

#include "hdc1010.h"

/*!
 * @brief Default Constructor
 */

HDC1010::HDC1010(){};

/*!
    @brief      initializes the begin function to get us going on i2c.
                We should be able to communicate with the device over i2c
                after this.
    @param      i2caddr
                Is the register address from where we read from
    @return     Returns a boolean value to indicate successful
                initiation.
*/

bool HDC1010::begin(uint8_t i2caddr = HDC1010_ADDRESS) {
  if (i2c_dev) {
    delete i2c_dev;
  }
  i2c_dev = new Adafruit_I2CDevice(i2caddr);

  if (!i2c_dev->begin()) {
    return false;
  }
  // Software Reset the device
  writeRegister16(HDC1010_CONF, 0x0059);
  for (uint8_t i = 0; i < 0x7f; i++)
    ;

  return true;
}

/*!
    @brief      Gets the 16 bit register value from the called register.
                This function requests the register contents over i2c.
    @param      reg
                Is the register address from where we read from
    @return     The 16 bit value of the register read is returned.
*/

uint16_t HDC1010::readRegister16(uint8_t reg) {
  uint16_t read16;
  Adafruit_BusIO_Register read_reg1 =
      Adafruit_BusIO_Register(i2c_dev, regMSB, 2);

  read_reg1.read(&read16);
  return (read16);
}

/*!
    @brief      Gets the 8 bit register value from the called register.
                This function requests the register contents over i2c.
    @param      reg
                Is the register address from where we read from
    @return     The 8 bit value of the register read is returned.
*/

uint8_t HDC1010::readRegister8(uint8_t reg) {
  Adafruit_BusIO_Register read_reg = Adafruit_BusIO_Register(i2c_dev, reg, 1);
  uint8_t r_val;
  return read_reg.read(&r_val, 0x8); // change to value returned from register
}

/*!
    @brief      Gets the 8 bit register value from the called register.
                This function requests the register contents over i2c.
    @param      reg
                Is the register address from where we want to write to
    @param      value
                is the 8 bit value we want to write to the register
*/

void HDC1010::writeRegister8(uint8_t reg, uint8_t value) {
  Adafruit_BusIO_Register write_reg = Adafruit_BusIO_Register(i2c_dev, reg, 1);
  write_reg.write(value, 0x8);
}

/*!
    @brief      Gets the 8 bit register value from the called register.
                This function requests the register contents over i2c.
    @param      reg
                Is the register address from where we read from
    @param      value
                is the value to be written to the 16 bit register
*/

void HDC1010::writeRegister16(uint8_t reg, uint16_t value) {
  Adafruit_BusIO_Register write_reg = Adafruit_BusIO_Register(i2c_dev, reg, 2);
  write_reg.write(value);
}

/*!
    @brief      Gets the raw 16 bit temperature from the device
                and converts it using the formula in the data sheet.
    @return     A float value containing the converted temperature
                value from the device.
*/

float HDC1010::getTemp(void) {
  float conv_temp;
  uint16_t raw_temp = getRawTemp();
  conv_temp =
      (raw_temp / (2 * *16)) * static_cast<float>(165) - static_cast<float>(40);
  return conv_temp;
}

/*!
    @brief      Gets the raw 16 bit temperature value from the device
                to be used in conversion.
    @return     The 16 bit raw temperature value of the device.
*/

uint16_t HDC1010::getRawTemp(void) { return readRegister16(HDC1010_TEMP); }

/*!
    @brief      Gets the converted humidity value and converts it
                based on the equation provided in the data sheet.
    @return     A float value containing the converted humidity
                value from the device.
*/

float HDC1010::getHum(void) {
  float conv_hum;
  uint16_t raw_hum = getRawHum();
  conv_hum = (raw_hum / (2 * *16)) * static_cast<float>(100);
  return conv_hum;
}

/*!
    @brief      Gets the raw humidity value as a unsigned 16 bit
                integer.
    @return     The 16 bit raw value of the register is returned.
*/

uint16_t HDC1010::getRawHum(void) { return readRegister16(HDC1010_HUM); }

/*!
    @brief      Gets the 8 bit register value from the called register.
                This function requests the register contents over i2c.
    @param      configVal
                is used to configure various features on the HDC1010.
*/

void HDC1010::setConfig(uint16_t configVal) {
  writeRegister16(HDC1010_CONF, configVal);
}