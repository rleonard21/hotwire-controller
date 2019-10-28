// PID.c
// Created by Robert Leonard on 10/27/19.
//

#include "PID.h"
#include "../hotwire/Hotwire.h"
#include "../sensors/INA219.h"
#include "../debug/Debug.h"

#define MAX_PID (3000)
#define MIN_PID (-3000)

volatile int pid_num_ticks = 0;
volatile int pid_max_ticks = 2000;

float P_error = 0.0;
float I_error = 0.0;
float D_error = 0.0;
float last_error = 0.0;

static const float P_gain = 50.0;
static const float I_gain = 1.0;
static const float D_gain = 1.0;

void PID_P_error(float set, float measure) {
	P_error = set - measure;
}

void PID_I_error(float set, float measure) {
	I_error += P_error;

	if(I_error > 50) I_error = 50;	 // restrict the output of the I term
	if(I_error < -50) I_error = -50; // "integral windup"
}

void PID_D_error(float set, float measure) {
	D_error = P_error - last_error;
	last_error = P_error;
}

// EFFECTS: updates the PID loop
void PID_update_service() {
	float set = Hotwire_get_power();
	float measure = INA219_getPower();

	PID_P_error(set, measure);
	PID_I_error(set, measure);
	PID_D_error(set, measure);

	float output = (P_error * P_gain + I_error * I_gain + D_error * D_gain);

	if(output > MAX_PID) output = MAX_PID;
	if(output < MIN_PID) output = MIN_PID;

	debug_write(0x50, (int16_t)(output));

	Hotwire_PID_input((int16_t)(output));
}
