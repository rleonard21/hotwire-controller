//
// LCDControl.c
// Created by Robert Leonard on 4/28/19.
//

#include "LCDControl.h"

#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>

// EFFECTS: Initializes PWM output for dimming the LCD backlight/contrast
void LCDControl_init() {
	// Setup OC0A/B for output
	DDRD |= _BV(PORTD5) | _BV(PORTD6);

	// Setup OC0A and OC0B for hardware toggle, non-inverting mode
	TCCR0A |= _BV(COM0A1) | _BV(COM0B1);

	// Setup the wage generator for fast PWM, OCR0A top
	TCCR0A |= _BV(WGM01) | _BV(WGM00);

	// Setup the clock for no prescaler
	TCCR0B |= _BV(CS00);
}

// EFFECTS: Sets the LCD contrast to the given value (255 => max contrast)
void LCDControl_set_contrast(uint8_t value) {
	OCR0A = value;
}

// EFFECTS: Sets the LCD backlight brightness to the given value (255 => max brightness)
void LCDControl_set_backlight(uint8_t value) {
	OCR0B = value;
}
