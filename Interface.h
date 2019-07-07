// Interface.h
// Created by Robert Leonard on 2019-07-04.
//

#ifndef HOTWIRE_CONTROLLER_V1_1_INTERFACE_H
#define HOTWIRE_CONTROLLER_V1_1_INTERFACE_H

#include <stdint.h>

#define VIEW_MAIN_STOPPED   0
#define VIEW_MAIN_RUNNING   1
#define VIEW_SETTINGS_MAIN  2
#define VIEW_SETTINGS_LCD   3
#define VIEW_SETTINGS_PWM   4

// EFFECTS: handles the main menu when the hotwire is off
uint8_t Interface_main_hotwire_off();

// EFFECTS: handles the main menu when the hotwire is on
uint8_t Interface_main_hotwire_on();

// EFFECTS: handles the main settings page
uint8_t Interface_settings_main();

// EFFECTS: handles the LCD settings page
uint8_t Interface_settings_lcd();

// EFFECTS: handles the PWM settings page
uint8_t Interface_settings_pwm();

// TODO:
//  * add other settings pages
//  * add other pages as needed

#endif //HOTWIRE_CONTROLLER_V1_1_INTERFACE_H
