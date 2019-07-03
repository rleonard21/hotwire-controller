// Hotwire.h
// Hotwire Controller Project
// Written by Robert Leonard

#ifndef _HOTWIRE_LIB_
#define _HOTWIRE_LIB_

#include <stdint.h>

#define HOTWIRE_PWM_MAX 0x0FF

// EFFECTS: initializes the device for PWM on the hotwire output
void Hotwire_init();

// EFFECTS: sets the PWM pulse width
void Hotwire_set(uint16_t value);

// EFFECTS: starts PWM signal on the hotwire output
// Note:	value=0 -> min duty cycle, value=255 -> max duty cycle
void Hotwire_start();

// EFFECTS: stops the PWM signal on the hotwire output
void Hotwire_stop();

// EFFECTS: sets the TOP overflow value for PWM, larger TOP means lower frequency
void Hotwire_set_top(uint16_t value);

// EFFECTS: returns true if the hotwire is running
uint16_t is_hotwire_running();

#endif
