// Hotwire.h
// Hotwire Controller Project
// Written by Robert Leonard

#ifndef _HOTWIRE_LIB_
#define _HOTWIRE_LIB_

#include <stdint.h>

#define HOTWIRE_PWM_MAX 0xFF

// EFFECTS: initializes the device for PWM on the hotwire output
void Hotwire_init();

// EFFECTS: starts PWM signal on the hotwire output
// Note:	value=0 -> min duty cycle, value=255 -> max duty cycle
void Hotwire_start();

// EFFECTS: stops the PWM signal on the hotwire output
void Hotwire_stop();

// EFFECTS: returns the power setting
float Hotwire_get_power();

// EFFECTS: increments/decrements power setting
void Hotwire_add_power_setting(float setting);

// EFFECTS: takes the PID controller's output as input, changes timer accordingly
void Hotwire_PID_input(int16_t output);

#endif
