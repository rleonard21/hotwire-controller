//
// Created by Robert Leonard on 2019-07-03.
//
// An implementation of the Ganssle debounce routine.
// http://www.ganssle.com/debouncing-pt2.htm
//

#include "Debounce.h"

#include <avr/interrupt.h>
#include <stddef.h>

#define NUM_INPUTS 3

volatile int num_ticks = 0;
volatile int max_ticks = 50;

struct Button inputs[NUM_INPUTS];

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
	return inputs[button].history == 0xFF;
}

// EFFECTS: returns true if the button is in a low state
uint8_t Debounce_is_low(uint8_t button) {
	return inputs[button].history == 0x00;
}

// EFFECTS: returns true if the button was just pressed (state has changed)
uint8_t Debounce_is_pressed(uint8_t button) {
	return inputs[button].history == 0x7F;
}

// EFFECTS: returns true if the button was just released (state has changed)
uint8_t Debounce_is_released(uint8_t button) {
	return inputs[button].history == 0x80;
}

// EFFECTS: reads the current state of the button
uint8_t Debounce_read(const struct Button *button) {
	return (*button->port & _BV(button->position)) == 0;
}

// EFFECTS: runs the update service after a certain number of interrupts
ISR(TIMER0_OVF_vect) {
	if(num_ticks++ > max_ticks) {
		Debounce_update_service();
		num_ticks = 0;
	}
}
