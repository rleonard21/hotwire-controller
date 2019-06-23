// Hotwire.h
// Hotwire Controller Project
// Written by Robert Leonard

#include "Hotwire.h"

#include <stdint.h>
#include <avr/io.h>

// Prescaler used for setting the frequency of the hotwire PWM
// Currently set for no prescaling
#define CS_PRESCALER ( (1 << CS10) )

// EFFECTS: initializes the device for PWM on the hotwire output
void Hotwire_init() {
	// Enable the PWM pin as an output
	DDRB |= _BV(PORTB2);

	// Enable inverting fast PWM with hardware toggle for OC1B
	TCCR1A |= _BV(COM1B1) | _BV(COM1B0) | _BV(WGM13) | _BV(WGM12) | _BV(WGM11) | _BV(WGM10);

	// Set OCR1B such that the PWM is constantly zero until Hotwire_set()
	OCR1B = 255;
}

// EFFECTS: sets the PWM pulse width to the given value
// Note:	value=0 -> min duty cycle, value=65535 -> max duty cycle
void Hotwire_set(uint16_t value) {
	OCR1B = (uint16_t) (65535) - value;
}

// EFFECTS: starts PWM signal on the hotwire output
// Note:	Hotwire_set() must be called at least once before starting PWM
void Hotwire_start() {
	TCCR1B |= CS_PRESCALER;
}

// EFFECTS: stops the PWM signal on the hotwire output
void Hotwire_stop() {
	TCCR1B &= ~CS_PRESCALER;
}

// EFFECTS: returns true if the hotwire is running
uint16_t is_hotwire_running() {
	return (uint16_t) (TCCR1B & CS_PRESCALER);
}
