//
// Created by Robert Leonard on 2019-06-23.
//

#include <avr/io.h>

#include "Encoder.h"


// EFFECTS: initializes the rotary encoder
void Encoder_init() {
	// Enable the encoder switch for input with pullup
	PORTD |= _BV(PORTD7);
}

// EFFECTS: returns the state of the rotary encoder. handles debouncing.
uint8_t Encoder_rotary_read() {

}

// EFFECTS: returns the state of the encoder's switch. handles debouncing.
uint8_t Encoder_switch_read() {

}