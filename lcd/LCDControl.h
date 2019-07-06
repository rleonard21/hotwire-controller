//
// LCDControl.h
// Created by Robert Leonard on 4/28/19.
//

#ifndef LCD_CONTROL_H
#define LCD_CONTROL_H

#include <stdint.h>

// EFFECTS: Initializes PWM output for dimming the LCD backlight/contrast
void LCDControl_init();

// EFFECTS: Sets the LCD contrast to the given value (255 => max contrast)
void LCDControl_set_contrast(uint8_t value);

// EFFECTS: Sets the LCD backlight brightness to the given value (255 => max brightness)
void LCDControl_set_backlight(uint8_t value);

// EFFECTS: increments the contrast
void LCDControl_increment_contrast();

// EFFECTS: decrements the contrast
void LCDControl_decrement_contrast();

// EFFECTS: increments the backlight
void LCDControl_increment_backlight();

// EFFECTS: decrements the backlight
void LCDControl_decrement_backlight();

#endif // LCD_CONTROL_H
