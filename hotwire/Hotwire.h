// Hotwire.h
// Hotwire Controller Project
// Written by Robert Leonard

#ifndef _HOTWIRE_LIB_
#define _HOTWIRE_LIB_

#include <stdint.h>

#define HOTWIRE_PWM_MAX 0xFF

// EFFECTS: initializes the device for PWM on the hotwire output
void Hotwire_init();

// EFFECTS: sets the PWM pulse width
void Hotwire_set(uint16_t value);

// EFFECTS: gets the PWM compare value
uint16_t Hotwire_get();

// EFFECTS: starts PWM signal on the hotwire output
// Note:	value=0 -> min duty cycle, value=255 -> max duty cycle
void Hotwire_start();

// EFFECTS: stops the PWM signal on the hotwire output
void Hotwire_stop();

// EFFECTS: sets the TOP overflow value for PWM, larger TOP means lower frequency
void Hotwire_set_top(uint16_t value);

// EFFECTS: increments the PWM pulse width
void Hotwire_increment();

// EFFECTS: decrements the PWM pulse width
void Hotwire_decrement();

// EFFECTS: sets the prescaler for the PWM timer
void Hotwire_set_prescaler(uint8_t index);

// EFFECTS: gets the prescaler for the PWM timer
uint8_t Hotwire_get_prescaler();

// EFFECTS: sets the increment value
void Hotwire_set_increment(uint8_t value);

// EFFECTS: gets the increment value
uint8_t Hotwire_get_increment();

// EFFECTS: returns true if the hotwire is running
uint16_t Hotwire_is_running();

// EFFECTS: returns the percent duty cycle
float Hotwire_get_duty();

#endif
