//
// Created by Robert Leonard on 2019-07-03.
//
// An implementation of the Ganssle debounce routine.
// http://www.ganssle.com/debouncing-pt2.htm
// https://hackaday.com/2015/12/10/embed-with-elliot-debounce-your-noisy-buttons-part-ii/
//

#include "Debounce.h"

#include <avr/interrupt.h>

#define NUM_INPUTS 3

struct Button inputs[NUM_INPUTS];

volatile int debounce_num_ticks = 0;
volatile int debounce_max_ticks = 10;

// EFFECTS: starts the debounce service. copies the inputs and enables the overflow interrupt vector.
void Debounce_init(struct Button *inputs_in) {
	for(uint8_t i = 0; i < NUM_INPUTS; i++) {
		inputs[i] = inputs_in[i];
	}

	TIMSK0 |= _BV(TOIE0);
}

// EFFECTS:  reads the button states and updates the histories of the inputs
void Debounce_update_service() {
	for(uint8_t index = 0; index < NUM_INPUTS; index++) {
		inputs[index].history = inputs[index].history << 1;
		inputs[index].history |= Debounce_read(&inputs[index]);
	}
}

// EFFECTS: returns true if the button is in a high state
uint8_t Debounce_is_high(uint8_t button) {
	return inputs[button].history == 0xFF; // checks for bit sequence 0b11111111
}

// EFFECTS: returns true if the button is in a low state
uint8_t Debounce_is_low(uint8_t button) {
	return inputs[button].history == 0x00; // checks for bit sequence 0b00000000
}

// EFFECTS: returns true if the button was just pressed (state has changed)
uint8_t Debounce_is_pressed(uint8_t button) {
	return inputs[button].history == 0x7F; // checks for bit sequence 0b01111111
}

// EFFECTS: returns true if the button was just released (state has changed)
uint8_t Debounce_is_released(uint8_t button) {
	return inputs[button].history == 0x80; // checks for bit sequence 0b10000000
}

// EFFECTS: reads the current state of the button
uint8_t Debounce_read(const struct Button *button) {
	return (*button->port & _BV(button->position)) == 0;
}
