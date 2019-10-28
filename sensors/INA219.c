// ViewController.c
// Created by Robert Leonard on 2019-10-04.
//

#include "INA219.h"
#include "../i2c/i2cmaster.h"

volatile float bus_voltage = 0.0;
volatile float shunt_voltage = 0.0;
volatile float current = 1.0;
volatile float power = 0.0;

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
	write_reg(INA219_REG_CONFIG, 0x219F);
	write_reg(INA219_REG_CALIBRATION, 0x5000);
	// todo: write to calibration register
}

// EFFECTS: returns the last bus voltage
float INA219_getBusVoltage() { return bus_voltage; }

// EFFECTS: returns the last shunt voltage
float INA219_getShuntVoltage() { return shunt_voltage; }

// EFFECTS: returns the last current
float INA219_getCurrent() { return current; }

// EFFECTS: returns the last power
float INA219_getPower() { return power; }

// EFFECTS: sets the bus voltage
void INA219_setBusVoltage() {
	int16_t voltage = read_reg(INA219_REG_BUSVOLTAGE);
	bus_voltage = ((voltage >> 3) * 4) * 0.001;
}

// EFFECTS: sets the shunt voltage
void INA219_setShuntVoltage() { shunt_voltage =  0; }

// EFFECTS: sets the current
void INA219_setCurrent() {
	int16_t current_raw = read_reg(INA219_REG_CURRENT);
	current = current_raw * 0.2 / 1000.0;
}

// EFFECTS: sets the power
void INA219_setPower() { power = 0; }

// EFFECTS: updates the registers
void INA219_update_service() {
	INA219_setBusVoltage();
	INA219_setShuntVoltage();
	INA219_setCurrent();
	INA219_setPower();
}
