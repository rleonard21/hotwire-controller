//
// Created by Robert Leonard on 2019-06-23.
//

#include "Encoder.h"
#include "Debounce.h"

#include <avr/io.h>
#include <avr/interrupt.h>

#define SWITCH      0
#define CHANNEL_A   1
#define CHANNEL_B   2

// EFFECTS: initializes the rotary encoder
void Encoder_init() {
	// Enable the encoder switch for input with pullup
	PORTD |= _BV(PORTD7);

	// Create local button objects to be copied over to the debounce service
	struct Button encoder_switch = {&PIND, 7, 0};
	struct Button encoder_a = {&PINB, 1, 0};
	struct Button encoder_b = {&PINB, 0, 0};

	struct Button inputs[3] = {encoder_switch, encoder_a, encoder_b};

	// Initialize the debounce service
	Debounce_init(inputs);
}

// EFFECTS: returns the state of the rotary encoder. handles debouncing.
uint8_t Encoder_rotary_read() {
	// Channel A leads channel B
	if(Debounce_is_pressed(CHANNEL_A) && Debounce_is_low(CHANNEL_B)) {
		return ROTATE_RIGHT;
	}

	// Channel B leads channel A
	if(Debounce_is_pressed(CHANNEL_B) && Debounce_is_low(CHANNEL_A)) {
		return ROTATE_LEFT;
	}

	return ROTATE_NONE;
}

// EFFECTS: returns true if the button was just pressed
uint8_t Encoder_switch_is_pressed() {
	return Debounce_is_pressed(SWITCH);
}

// EFFECTS: returns true if the button was just released
uint8_t Encoder_switch_is_released() {
	return Debounce_is_released(SWITCH);
}

// EFFECTS: returns true if the button is being held low
uint8_t Encoder_switch_is_low() {
	return Debounce_is_low(SWITCH);
}

// EFFECTS: returns true if the button is being held high
uint8_t Encoder_switch_is_high() {
	return Debounce_is_high(SWITCH);
}
