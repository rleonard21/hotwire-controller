//
// Created by Robert Leonard on 2019-06-23.
//

#ifndef HOTWIRE_CONTROLLER_V1_1_ENCODER_H
#define HOTWIRE_CONTROLLER_V1_1_ENCODER_H

#include <stdint.h>

#define ROT_NONE		0
#define ROT_LEFT		1
#define ROT_RIGHT		2

#define SW_LOW			0
#define SW_HIGH			1

// EFFECTS: initializes the rotary encoder
void Encoder_init();

// EFFECTS: returns the state of the rotary encoder. handles debouncing.
uint8_t Encoder_rotary_read();

// EFFECTS: returns the state of the encoder's switch. handles debouncing.
uint8_t Encoder_switch_read();

#endif //HOTWIRE_CONTROLLER_V1_1_ENCODER_H
