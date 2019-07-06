//
// LCDControl.c
// Created by Robert Leonard on 4/28/19.
//

#include "LCDControl.h"

#include <stdint.h>
#include <avr/io.h>

#define OCR_CONTRAST    OCR0A
#define OCR_BACKLIGHT   OCR0B

// EFFECTS: Initializes PWM output for dimming the LCD backlight/contrast
void LCDControl_init() {
	// Setup OC0A/B for output
	DDRD |= _BV(PORTD5) | _BV(PORTD6);

	// Setup OC0A/B for hardware toggle, non-inverting mode
	TCCR0A |= _BV(COM0A1) | _BV(COM0B1);

	// Setup the wave generator for fast PWM, 0xFF top
	TCCR0A |= _BV(WGM01) | _BV(WGM00);

	// Setup the clock for no prescaler
	TCCR0B |= _BV(CS00);
}

// EFFECTS: Sets the LCD contrast to the given value (255 => max contrast)
void LCDControl_set_contrast(uint8_t value) {
	OCR_CONTRAST = value;
}

// EFFECTS: Sets the LCD backlight brightness to the given value (255 => max brightness)
void LCDControl_set_backlight(uint8_t value) {
	OCR_BACKLIGHT = value;
}

// EFFECTS: increments the contrast
void LCDControl_increment_contrast() {
	if(OCR_CONTRAST < 0xFF) {
		OCR_CONTRAST++;
	}
}

// EFFECTS: decrements the contrast
void LCDControl_decrement_contrast() {
	if(OCR_CONTRAST > 0) {
		OCR_CONTRAST--;
	}
}

// EFFECTS: increments the backlight
void LCDControl_increment_backlight() {
	if(OCR_BACKLIGHT < 0xFF) {
		OCR_BACKLIGHT++;
	}
}

// EFFECTS: decrements the backlight
void LCDControl_decrement_backlight() {
	if(OCR_BACKLIGHT > 0) {
		OCR_BACKLIGHT--;
	}
}
