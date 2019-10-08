// ViewController.c
// Created by Robert Leonard on 2019-10-04.
//

#include "INA219.h"
#include "../i2c/i2cmaster.h"

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
	write_reg(0x00, 0x219F);
	// todo: write to calibration register
}


float INA219_getBusVoltage() {
	int16_t voltage = read_reg(INA219_REG_BUSVOLTAGE);
	return ((voltage >> 3) * 4) * 0.001;
}

float INA219_getShuntVoltage() { return 0; }

float INA219_getCurrent() { return 0; }

float INA219_getPower() { return 0; }
