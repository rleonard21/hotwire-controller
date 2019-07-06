//
// Created by Robert Leonard on 2019-06-23.
//

#ifndef HOTWIRE_CONTROLLER_V1_1_ENCODER_H
#define HOTWIRE_CONTROLLER_V1_1_ENCODER_H

#include <stdint.h>

#define ROTATE_NONE		0
#define ROTATE_LEFT		1
#define ROTATE_RIGHT    2

#define SW_LOW			0
#define SW_HIGH			1

// EFFECTS: initializes the rotary encoder
void Encoder_init();

// EFFECTS: returns the state of the rotary encoder. handles debouncing.
uint8_t Encoder_rotary_read();

// EFFECTS: returns true if the button was just pressed
uint8_t Encoder_switch_is_pressed();

// EFFECTS: returns true if the button was just released
uint8_t Encoder_switch_is_released();

// EFFECTS: returns true if the button is being held low
uint8_t Encoder_switch_is_low();

// EFFECTS: returns true if the button is being held high
uint8_t Encoder_switch_is_high();

// EFFECTS: returns true if the button is held for at least timer long
uint8_t Encoder_switch_is_held(uint32_t timer_min);

#endif //HOTWIRE_CONTROLLER_V1_1_ENCODER_H
