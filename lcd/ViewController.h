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

volatile uint32_t vc_num_ticks;
volatile uint32_t vc_max_ticks;

struct VCO {
	uint8_t x;
	uint8_t y;
	uint8_t direction;

	void (*NEXT_VC)();
} VCObject;

// EFFECTS: initializes the view controller
void VC_init();

// EFFECTS: creates a selection cursor at the given coordinate
void VC_set_cursor();

// EFFECTS: creates a blinking cursor at the given coordinate
void VC_set_cursor_blink();

// EFFECTS: stops the blinking cursor
void VC_stop_cursor_blink();

// EFFECTS: displays the startup page
void VC_startup_screen();

// EFFECTS: displays the main menu page
void VC_main_menu();

// EFFECTS: displays the hotwire page
void VC_hotwire_running();

// EFFECTS: displays the main settings page
void VC_settings_main(uint8_t settings_page);

// EFFECTS: displays the LCD settings page
void VC_settings_lcd();

// EFFECTS: displays the PID setitngs page
void VC_settings_pid();

// EFFECTS: prints an error message
void VC_page_incomplete();

// EFFECTS: prints an error message
void VC_page_incomplete_2();

// EFFECTS: updates the screen
void VC_update_service();

#endif //HOTWIRE_CONTROLLER_V1_1_VIEWCONTROLLER_H
