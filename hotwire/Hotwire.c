// Hotwire.h
// Hotwire Controller Project
// Written by Robert Leonard

#include "Hotwire.h"
#include "../pid/PID.h"

#include <stdint.h>
#include <avr/io.h>


#define MAX_POWER_SETTING 50

static float power_setting = 0.0;
static uint8_t CS_PRESCALER = ((1 << CS00));

// EFFECTS: initializes the device for PWM on the hotwire output
void Hotwire_init() {
	// Enable the PWM pin as an output
	DDRB |= _BV(PORTB2);

	// Set the output pin low (pin will be connected to compare register later)
	PORTB &= ~_BV(PORTB2);

	// Enable fast PWM, ICR TOP (hardware toggle setup in start function)
	TCCR1A |= _BV(WGM11);
	TCCR1B |= _BV(WGM13) | _BV(WGM12);

	// Set TOP to 256, modelling an 8-bit timer. Max frequency @ 62.5kHz
	ICR1 = HOTWIRE_PWM_MAX;

	// Set OCR1B such that the PWM is constantly zero until Hotwire_set()
	OCR1B = 0;
}

// EFFECTS: starts PWM signal on the hotwire output
// Note:	Hotwire_set() must be called at least once before starting PWM
void Hotwire_start() {
	// Attach the output pin to the compare register
	TCCR1A |= _BV(COM1B1);

	// Enable the timer
	TCCR1B |= CS_PRESCALER;

	// Enable the PID controller
	PID_enable();
}

// EFFECTS: stops the PWM signal on the hotwire output
void Hotwire_stop() {
	// Disable the PID controller
	PID_disable();

	// Disable the timer clock
	TCCR1B &= ~CS_PRESCALER;

	// Detach the output pin from the compare register
	TCCR1A &= ~_BV(COM1B1);

	// Reset the compare value
	OCR1B = 0;
}

// EFFECTS: increases/decreases timer compare by input
void Hotwire_add(int16_t value) {
	if ((long) (OCR1B) + (long) (value) >= (long) (HOTWIRE_PWM_MAX)) {
		OCR1B = HOTWIRE_PWM_MAX - 1;
	} else if ((long) (OCR1B) + (long) (value) <= 0) {
		OCR1B = 0;
	} else {
		OCR1B += value;
	}
}

// EFFECTS: returns the power setting
float Hotwire_get_power() {
	return power_setting;
}

// EFFECTS: increments/decrements power setting
void Hotwire_add_power_setting(float setting) {
	if (power_setting + setting <= MAX_POWER_SETTING && power_setting + setting >= 0) {
		power_setting += setting;
	}
}

// EFFECTS: takes the PID controller's output as input, changes timer accordingly
void Hotwire_PID_input(int16_t output) {
	Hotwire_add(output);
}
