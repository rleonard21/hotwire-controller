#ifndef _INA219_LIB_
#define _INA219_LIB_

#include <stdint.h>

#define INA219_ADDRESS                          (0x40)
#define INA219_REG_CONFIG                       (0x00)
#define INA219_UPDATE_DIVISOR                    (4350)

#define INA219_REG_SHUNTVOLTAGE                 (0x01)
#define INA219_REG_BUSVOLTAGE                   (0x02)
#define INA219_REG_POWER                        (0x03)
#define INA219_REG_CURRENT                      (0x04)
#define INA219_REG_CALIBRATION                  (0x05)

volatile int ina219_num_ticks;
volatile int ina219_max_ticks;

// EFFECTS: Initializes the sensor and I2C bus
void INA219_init();

// EFFECTS: returns the last bus voltage
double INA219_getBusVoltage();

// EFFECTS: returns the last shunt voltage
double INA219_getShuntVoltage();

// EFFECTS: returns the last current
double INA219_getCurrent();

// EFFECTS: returns the last current
double INA219_getPower();

// EFFECTS: updates the registers
void INA219_update_service();

#endif
