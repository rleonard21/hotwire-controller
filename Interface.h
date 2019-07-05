// Interface.h
// Created by Robert Leonard on 2019-07-04.
//

#ifndef HOTWIRE_CONTROLLER_V1_1_INTERFACE_H
#define HOTWIRE_CONTROLLER_V1_1_INTERFACE_H

#include <stdint.h>

#define VIEW_MAIN           0
#define VIEW_SETTINGS_MAIN  1
#define VIEW_SETTINGS_LCD   2

// EFFECTS: handles the main menu
uint8_t Interface_main();

// EFFECTS: handles the main settings page
uint8_t Interface_settings_main();

// EFFECTS: handles the LCD settings page
uint8_t Interface_settings_lcd();

// TODO:
//  * add other settings pages
//  * add other pages as needed

#endif //HOTWIRE_CONTROLLER_V1_1_INTERFACE_H
