// Hotwire.h
// Hotwire Controller Project
// Written by Robert Leonard

#include "Hotwire.h"

#include <stdint.h>
#include <avr/io.h>

// Prescaler used for setting the frequency of the hotwire PWM
#define CS_PRESCALER ( (1 << CS01) )

// EFFECTS: initializes the device for PWM on the hotwire output
void Hotwire_init() {
	// Enable the PWM pin as an output
	DDRD |= _BV(PORTD6);

	// Enable inverted phase-correct PWM with hardware toggle for OC0A
	TCCR0A |= _BV(WGM00) | _BV(COM0A1) | _BV(COM0A0);

	// Set OCR0 such that the PWM is constantly zero until Hotwire_set()
	OCR0A = 255;
}

// EFFECTS: sets the PWM pulse width to the given value
// Note:	value=0 -> min duty cycle, value=255 -> max duty cycle
void Hotwire_set(uint8_t value) {
	OCR0A = (uint8_t) (255) - value;
}

// EFFECTS: starts PWM signal on the hotwire output
// Note:	Hotwire_set() must be called at least once before starting PWM
void Hotwire_start() {
	TCCR0B |= CS_PRESCALER;
}

// EFFECTS: stops the PWM signal on the hotwire output
void Hotwire_stop() {
	TCCR0B &= ~CS_PRESCALER;
}

// EFFECTS: returns true if the hotwire is running
uint8_t is_hotwire_running() {
	return (uint8_t) (TCCR0B & CS_PRESCALER);
}
