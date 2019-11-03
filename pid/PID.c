// PID.c
// Created by Robert Leonard on 10/27/19.
//

#include <avr/eeprom.h>

#include "PID.h"
#include "../hotwire/Hotwire.h"
#include "../sensors/INA219.h"
#include "../debug/Debug.h"

#define MAX_PID    (5000)
#define MIN_PID    (-5000)
#define MAX_GAIN    (99.9)

volatile int pid_num_ticks = 0;
volatile int pid_max_ticks = INA219_UPDATE_DIVISOR;

float P_error = 0.0;
float I_error = 0.0;
float D_error = 0.0;
float last_error = 0.0;
uint8_t PID_enabled = 0;

float P_gain = 1.0;
float I_gain = 1.0;
float D_gain = 1.0;

float EEMEM eeprom_base;
uint8_t EEMEM eeprom_set;
int P_addr = 0x00;
int I_addr = 0x10;
int D_addr = 0x20;
int Set_addr = 0x30;

// EFFECTS: initializes the PID controller
void PID_init() {
	uint8_t set = eeprom_read_byte(&eeprom_set + Set_addr);
	if (set != 0xBB) {
		// Save the default gains to EEPROM if they were unset before
		PID_save_gains();
		eeprom_update_byte(&eeprom_set + Set_addr, 0xBB);
	} else {
		P_gain = eeprom_read_float(&eeprom_base + P_addr);
		I_gain = eeprom_read_float(&eeprom_base + I_addr);
		D_gain = eeprom_read_float(&eeprom_base + D_addr);
	}
}

void PID_P_error(float set, float measure) {
	P_error = set - measure;
}

void PID_I_error() {
	I_error += P_error;

	if (I_error > 50) I_error = 50;     // restrict the output of the I term
	if (I_error < -50) I_error = -50; // "integral windup"
}

void PID_D_error() {
	D_error = P_error - last_error;
	last_error = P_error;
}

// EFFECTS: updates the PID loop
void PID_update_service() {
	if(!PID_enabled) return;

	float set = Hotwire_get_power();
	float measure = INA219_getPower();

	PID_P_error(set, measure);
	PID_I_error();
	PID_D_error();

	float output = (P_error * P_gain + I_error * I_gain + D_error * D_gain);

	if (output > MAX_PID) output = MAX_PID;
	if (output < MIN_PID) output = MIN_PID;

	debug_write(0x50, (int16_t) (output));

	Hotwire_PID_input((int16_t) (output));
}

// EFFECTS: returns the current P gain
float PID_get_p() {
	return P_gain;
}

// EFFECTS: returns the current I gain
float PID_get_i() {
	return I_gain;
}

// EFFECTS: returns the current D gain
float PID_get_d() {
	return D_gain;
}

void add_helper(float *gain, float value) {
	if (*gain + value >= MAX_GAIN) {
		*gain = MAX_GAIN;
	} else if (*gain + value <= 0.0) {
		*gain = 0.0;
	} else {
		*gain += value;
	}
}

// EFFECTS: adds value to P gain
void PID_add_p(float value) {
	add_helper(&P_gain, value);
}

// EFFECTS: adds value to I gain
void PID_add_i(float value) {
	add_helper(&I_gain, value);
}

// EFFECTS: adds value to D gain
void PID_add_d(float value) {
	add_helper(&D_gain, value);
}

// EFFECTS: saves gains to EEPROM
void PID_save_gains() {
	eeprom_update_float(&eeprom_base + P_addr, P_gain);
	eeprom_update_float(&eeprom_base + I_addr, I_gain);
	eeprom_update_float(&eeprom_base + D_addr, D_gain);
}

// EFFECTS: stops the PID controller
void PID_disable() {
	PID_enabled = 0;
}

// EFFECTS: starts the PID controller
void PID_enable() {
	PID_enabled = 1;
}
