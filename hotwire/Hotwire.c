// Hotwire.h
// Hotwire Controller Project
// Written by Robert Leonard

#include "Hotwire.h"

#include <stdint.h>
#include <avr/io.h>

#define MAX_POWER_SETTING 50

static uint8_t increment_value = 1;
static float power_setting = 0.0;
static uint8_t CS_PRESCALER = ( (1 << CS00) );

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
//	OCR1B = ICR1;
	OCR1B = 0;
}

// EFFECTS: sets the PWM pulse width to the given value
// Note:	value=0 -> min duty cycle, value=65535 -> max duty cycle
void Hotwire_set(uint16_t value) {
	OCR1B = value;
}

// EFFECTS: gets the PWM compare value
uint16_t Hotwire_get() {
	return OCR1B;
}

// EFFECTS: starts PWM signal on the hotwire output
// Note:	Hotwire_set() must be called at least once before starting PWM
void Hotwire_start() {
	// Attach the output pin to the compare register
	TCCR1A |= _BV(COM1B1);

	// Enable the timer
	TCCR1B |= CS_PRESCALER;
}

// EFFECTS: stops the PWM signal on the hotwire output
void Hotwire_stop() {
	// Disable the timer clock
	TCCR1B &= ~CS_PRESCALER;

	// Detach the output pin from the compare register
	TCCR1A &= ~_BV(COM1B1);
}

// EFFECTS: sets the TOP overflow value for PWM, larger TOP means lower frequency
void Hotwire_set_top(uint16_t value) {
	ICR1 = value;
}

// EFFECTS: increments the PWM pulse width
void Hotwire_increment() {
	if(OCR1B < ICR1) {
		OCR1B += 1;
	}
}

// EFFECTS: decrements the PWM pulse width
void Hotwire_decrement() {
	if(OCR1B > 0) {
		OCR1B -= 1;
	}
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

// EFFECTS: sets the prescaler for the PWM timer
void Hotwire_set_prescaler(uint8_t index) {
	switch (index) {
		case 0: // 1
			CS_PRESCALER = ( _BV(CS00) );

		case 1: // 8
			CS_PRESCALER = ( _BV(CS01) );

		case 2: // 64
			CS_PRESCALER = ( _BV(CS01) | _BV(CS00) );

		case 3: // 256
			CS_PRESCALER = ( _BV(CS02) );

		case 4: // 1024
			CS_PRESCALER = ( _BV(CS02) | _BV(CS00) );
	}
}

// EFFECTS: gets the prescaler for the PWM timer
uint8_t Hotwire_get_prescaler() {
	return CS_PRESCALER;
}

// EFFECTS: sets the increment value
void Hotwire_set_increment(uint8_t value) {
	increment_value = value;
}

// EFFECTS: gets the increment value
uint8_t Hotwire_get_increment() {
	return increment_value;
}

// EFFECTS: returns true if the hotwire is running
uint16_t Hotwire_is_running() {
	return (uint16_t) (TCCR1B & CS_PRESCALER);
}

// EFFECTS: returns the percent duty cycle
float Hotwire_get_duty() {
	return (float)(OCR1B) / (float)(HOTWIRE_PWM_MAX) * 100.0;
}

// EFFECTS: returns the power setting
float Hotwire_get_power() {
	return power_setting;
}

// EFFECTS: increments/decrements power setting
void Hotwire_add_power_setting(float setting) {
	if(power_setting + setting <= MAX_POWER_SETTING && power_setting + setting >= 0) {
		power_setting += setting;
	}
}

// EFFECTS: takes the PID controller's output as input, changes timer accordingly
void Hotwire_PID_input(int16_t output) {
	Hotwire_add(output);
}
