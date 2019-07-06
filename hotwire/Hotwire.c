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

	// Enable inverting fast PWM, ICR TOP, with hardware toggle for OC1B
	TCCR1A |= _BV(COM1B1) | _BV(WGM11);
	TCCR1B |= _BV(WGM13) | _BV(WGM12);

	// Set TOP to 256, modelling an 8-bit timer. Max frequency @ 62.5kHz
	ICR1 = HOTWIRE_PWM_MAX;

	// Set OCR1B such that the PWM is constantly zero until Hotwire_set()
	OCR1B = ICR1;
}

// EFFECTS: sets the PWM pulse width to the given value
// Note:	value=0 -> min duty cycle, value=65535 -> max duty cycle
void Hotwire_set(uint16_t value) {
	OCR1B = value;
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

// EFFECTS: sets the TOP overflow value for PWM, larger TOP means lower frequency
void Hotwire_set_top(uint16_t value) {
	ICR1 = value;
}

// EFFECTS: increments the PWM pulse width
void Hotwire_set_increment() {
	if(OCR1B < ICR1) {
		OCR1B++;
	}
}

// EFFECTS: decrements the PWM pulse width
void Hotwire_set_decrement() {
	if(OCR1B > 0) {
		OCR1B--;
	}
}

// EFFECTS: returns true if the hotwire is running
uint16_t Hotwire_is_running() {
	return (uint16_t) (TCCR1B & CS_PRESCALER);
}
