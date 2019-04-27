// Hotwire.h
// Hotwire Controller Project
// Written by Robert Leonard

#ifndef _HOTWIRE_LIB_
#define _HOTWIRE_LIB_

#include <stdint.h>

// EFFECTS: initializes the device for PWM on the hotwire output
void Hotwire_init();

// EFFECTS: sets the PWM pulse width
void Hotwire_set(uint8_t value);

// EFFECTS: starts PWM signal on the hotwire output
// Note:	value=0 -> min duty cycle, value=255 -> max duty cycle
void Hotwire_start();

// EFFECTS: stops the PWM signal on the hotwire output
void Hotwire_stop();

// EFFECTS: returns true if the hotwire is running
uint8_t is_hotwire_running();

#endif
