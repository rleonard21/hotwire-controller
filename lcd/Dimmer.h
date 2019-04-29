// Dimmer.h
// Created by Robert Leonard on 4/28/19.
//

#ifndef HPA_FCU_DIMMER_H
#define HPA_FCU_DIMMER_H

#include <stdint.h>

// EFFECTS: Initializes PWM output for dimming the LCD backlight/contrast
void Dimmer_init();

// EFFECTS: Sets the LCD contrast to the given value
void set_lcd_contrast(uint16_t value);

// EFFECTS: Sets the LCD backlight brightness to the given value
void set_lcd_backlight(uint16_t value);

#endif //HPA_FCU_DIMMER_H
