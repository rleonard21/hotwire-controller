// Debug.c
// Created by Robert Leonard on 10/28/19.
//

#include "Debug.h"
#include "../i2c/i2cmaster.h"

// EFFECTS: writes the value to the I2C line
void debug_write(uint8_t reg, int16_t value) {
#ifndef NO_DEBUG
	uint8_t msb = (uint8_t) (value >> 8);			// extract higher 8 bits
	uint8_t lsb = (uint8_t) ((value << 8) >> 8);	// extract lower 8 bits

	i2c_start(DEBUG_ADDR, I2C_WRITE);
	i2c_write(reg);
	i2c_write(msb);		// send MSB
	i2c_write(lsb);		// send LSB
	i2c_stop();
#endif
}
