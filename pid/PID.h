// PID.h
// Created by Robert Leonard on 10/27/19.
//

#ifndef HOTWIRE_CONTROLLER_V1_1_PID_H
#define HOTWIRE_CONTROLLER_V1_1_PID_H

#include <stdint.h>

volatile int pid_num_ticks;
volatile int pid_max_ticks;

// EFFECTS: initializes the PID controller
void PID_init();

// EFFECTS: updates the PID loop
void PID_update_service();

// EFFECTS: returns the current P gain
float PID_get_p();

// EFFECTS: returns the current I gain
float PID_get_i();

// EFFECTS: returns the current D gain
float PID_get_d();

// EFFECTS: adds value to P gain
void PID_add_p(float value);

// EFFECTS: adds value to I gain
void PID_add_i(float value);

// EFFECTS: adds value to D gain
void PID_add_d(float value);

// EFFECTS: saves gains to EEPROM
void PID_save_gains();

// EFFECTS: stops the PID controller
void PID_disable();

// EFFECTS: starts the PID controller
void PID_enable();

#endif //HOTWIRE_CONTROLLER_V1_1_PID_H
