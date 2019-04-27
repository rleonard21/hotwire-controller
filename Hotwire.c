// Hotwire.h
// Hotwire Controller Project
// Written by Robert Leonard

#include "Hotwire.h"

// EFFECTS: initializes the device for PWM on the hotwire output
void Hotwire_init() {
	// TODO: setup the ports to enable PWM
}

// EFFECTS: sets the PWM pulse width
void Hotwire_set() {
	// TODO: set the OCxy value here
}

// EFFECTS: starts PWM signal on the hotwire output
void Hotwire_start() {
	// TODO: enable the clock source on the PWM
}

// EFFECTS: stops the PWM signal on the hotwire output
void Hotwire_stop() {
	// TODO: disable the clock source on the PWM
}

// EFFECTS: returns true if the hotwire is running
uint8_t is_hotwire_running() {
	// TODO: return true if the clock source is set
}
