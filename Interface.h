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

// EFFECTS: handles the main menu when the hotwire is off
uint8_t Interface_main_hotwire_off(uint8_t next_view);

// EFFECTS: handles the main menu when the hotwire is on
uint8_t Interface_main_hotwire_on(uint8_t next_view);

// EFFECTS: handles the main settings page
uint8_t Interface_settings_main(uint8_t next_view);

// EFFECTS: handles the LCD settings page
uint8_t Interface_settings_lcd(uint8_t next_view);

// TODO:
//  * add other settings pages
//  * add other pages as needed

#endif //HOTWIRE_CONTROLLER_V1_1_INTERFACE_H
