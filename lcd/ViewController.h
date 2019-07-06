// ViewController.h
// Created by Robert Leonard on 2019-07-04.
//

#ifndef HOTWIRE_CONTROLLER_V1_1_VIEWCONTROLLER_H
#define HOTWIRE_CONTROLLER_V1_1_VIEWCONTROLLER_H

#include <stdint.h>

struct Cursor {
	uint8_t x;
	uint8_t y;
};

// EFFECTS: displays the startup page
void VC_startup_screen();

// EFFECTS: displays the main menu page
void VC_main_menu(struct Cursor cursor, uint8_t power, uint8_t voltage);

// EFFECTS: displays the LCD settings page
void VC_settings_lcd(struct Cursor cursor);

// EFFECTS: prints an error message
void VC_page_incomplete();

// EFFECTS: prints an error message
void VC_page_incomplete_2();

#endif //HOTWIRE_CONTROLLER_V1_1_VIEWCONTROLLER_H
