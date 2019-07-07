// ViewController.h
// Created by Robert Leonard on 2019-07-04.
//

#ifndef HOTWIRE_CONTROLLER_V1_1_VIEWCONTROLLER_H
#define HOTWIRE_CONTROLLER_V1_1_VIEWCONTROLLER_H

#include <stdint.h>

#define NUM_SETTINGS                2

#define LCD_INVERTED_LEFT_ARROW     0x00
#define LCD_INVERTED_RIGHT_ARROW    0x01
#define LCD_NO_CURSOR               0x09

struct Cursor {
	uint8_t x;
	uint8_t y;
	uint8_t direction;
};

// EFFECTS: initializes the view controller
void VC_init();

// EFFECTS: creates a selection cursor at the given coordinate
void VC_set_cursor(struct Cursor cursor);

// EFFECTS: creates a blinking cursor at the given coordinate
void VC_set_cursor_blink(struct Cursor cursor);

// EFFECTS: stops the blinking cursor
void VC_stop_cursor_blink();

// EFFECTS: displays the startup page
void VC_startup_screen();

// EFFECTS: displays the main menu page
void VC_main_menu(struct Cursor cursor, uint8_t power, uint8_t voltage);

// EFFECTS: displays the hotwire page
void VC_hotwire_running(struct Cursor cursor);

// EFFECTS: displays the main settings page
void VC_settings_main(struct Cursor cursor, uint8_t settings_page);

// EFFECTS: displays the LCD settings page
void VC_settings_lcd(struct Cursor cursor);

// EFFECTS: displays the PWM settings page
void VC_settings_pwm(struct Cursor cursor);

// EFFECTS: prints an error message
void VC_page_incomplete();

// EFFECTS: prints an error message
void VC_page_incomplete_2();

#endif //HOTWIRE_CONTROLLER_V1_1_VIEWCONTROLLER_H
