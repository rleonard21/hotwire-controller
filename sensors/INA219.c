// ViewController.c
// Created by Robert Leonard on 2019-10-04.
//

#include "INA219.h"
#include "../i2c/i2cmaster.h"
#include "../debug/Debug.h"

#define INA219_CONFIG_VALUE (0x3FFF)
#define INA219_CAL_VALUE (0x3555)
#define CURRENT_LSB (0.0003)
#define POWER_LSB (20 * CURRENT_LSB)

volatile double bus_voltage = 0.0;
volatile double shunt_voltage = 0.0;
volatile double current = 0.0;
volatile double power = 0.0;

volatile int ina219_num_ticks = 0;
volatile int ina219_max_ticks = 2000;

void write_reg(uint8_t reg, uint16_t value) {
	uint8_t msb = (uint8_t) (value >> 8);			// extract higher 8 bits
	uint8_t lsb = (uint8_t) ((value << 8) >> 8);	// extract lower 8 bits

	i2c_start(INA219_ADDRESS, I2C_WRITE);
	i2c_write(reg);		// select register
	i2c_write(msb);		// send MSB
	i2c_write(lsb);		// send LSB
	i2c_stop();
}

int16_t read_reg(uint8_t reg) {
	i2c_start(INA219_ADDRESS, I2C_WRITE);
	i2c_write(reg);	// select register

	i2c_start(INA219_ADDRESS, I2C_READ);
	int16_t value = (i2c_readAck() << 8) | (i2c_readAck()); // read 16 bits
	i2c_stop();

	return value;
}

void INA219_init() {
	i2c_init();
	write_reg(INA219_REG_CONFIG, INA219_CONFIG_VALUE);
	write_reg(INA219_REG_CALIBRATION, INA219_CAL_VALUE);
}

// EFFECTS: returns the last bus voltage
double INA219_getBusVoltage() { return bus_voltage; }

// EFFECTS: returns the last shunt voltage
double INA219_getShuntVoltage() { return shunt_voltage; }

// EFFECTS: returns the last current
double INA219_getCurrent() { return current; }

// EFFECTS: returns the last power
double INA219_getPower() { return power; }

// EFFECTS: sets the bus voltage
void INA219_setBusVoltage() {
	int16_t voltage = read_reg(INA219_REG_BUSVOLTAGE);
	bus_voltage = ((voltage >> 3) * 4) * 0.001;
}

// EFFECTS: sets the shunt voltage
void INA219_setShuntVoltage() {
	int16_t shunt_raw = read_reg(INA219_REG_SHUNTVOLTAGE);
	shunt_voltage = shunt_raw * 0.00001;
}

// EFFECTS: sets the current
void INA219_setCurrent() {
	int16_t current_raw = read_reg(INA219_REG_CURRENT);
	current = current_raw * CURRENT_LSB;
}

// EFFECTS: sets the power
void INA219_setPower() {
	int16_t power_raw = read_reg(INA219_REG_POWER);
	power = power_raw * POWER_LSB;
}

// EFFECTS: updates the registers
void INA219_update_service() {
	INA219_setBusVoltage();
	INA219_setShuntVoltage();
	INA219_setCurrent();
	INA219_setPower();

	debug_write(0x10, (int16_t)(bus_voltage * 1000));
	debug_write(0x20, (int16_t )(current * 1000));
	debug_write(0x30, (int16_t)(power * 1000));
}
