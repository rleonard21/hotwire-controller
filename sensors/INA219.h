// INA219.h
// Hotwire Controller Project
// Adapted from Adafruit INA219 C++ Library
// Written by Robert Leonard

#ifndef _INA219_LIB_
#define _INA219_LIB_

#include <stdint.h>

#define INA219_ADDRESS  (0x40)

// todo: define all the register addresses for the INA219...

struct INA219 {
    uint8_t addr = INA219_ADDRESS;
};

void INA219_init(INA219 *ina);
int16_t INA219_getBusVoltage(INA219 *ina);
int16_t INA219_getShuntVoltage(INA219 *ina);
int16_t INA219_getCurrent(INA219 *ina);
int16_t INA219_getPower(INA219 *ina);

#endif
