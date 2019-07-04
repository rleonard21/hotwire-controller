//
// Created by Robert Leonard on 2019-07-03.
//
// An implementation of the Ganssle debounce routine.
// http://www.ganssle.com/debouncing-pt2.htm
//

#ifndef HOTWIRE_CONTROLLER_V1_1_DEBOUNCE_H
#define HOTWIRE_CONTROLLER_V1_1_DEBOUNCE_H

#include <stdint.h>

struct Button {
	volatile uint8_t *port;
	uint8_t position;
	uint8_t history;
};

// EFFECTS: starts the debounce service. copies the inputs and enables the overflow interrupt vector.
void Debounce_init(struct Button *inputs_in);

// EFFECTS:  reads the button states and updates the histories of the inputs
void Debounce_update_service();

// EFFECTS: returns true if the button is in a high state
uint8_t Debounce_is_high(uint8_t button);

// EFFECTS: returns true if the button is in a low state
uint8_t Debounce_is_low(uint8_t button);

// EFFECTS: returns true if the button was just pressed (state has changed)
uint8_t Debounce_is_pressed(uint8_t button);

// EFFECTS: returns true if the button was just released (state has changed)
uint8_t Debounce_is_released(uint8_t button);

// EFFECTS: reads the current state of the button
uint8_t Debounce_read(const struct Button *button);

#endif //HOTWIRE_CONTROLLER_V1_1_DEBOUNCE_H
