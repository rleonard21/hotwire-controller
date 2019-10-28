// Interface.c
// Created by Robert Leonard on 2019-07-04.
//

#include <stddef.h>
#include <avr/interrupt.h>
#include "Interface.h"

#include "lcd/ViewController.h"
#include "encoder/Encoder.h"
#include "hotwire/Hotwire.h"
#include "feedback/Buzzer.h"
#include "lcd/LCDControl.h"

#include "lcd/lcd.h"

#define SWITCH_HOLD_TIME    150000

// EFFECTS: handles the main menu
uint8_t Interface_main_hotwire_off() {
	VCObject.x = 0;
	VCObject.y = 0;
	VCObject.direction = LCD_INVERTED_LEFT_ARROW;
	VCObject.NEXT_VC = &VC_main_menu;

	while(!Encoder_switch_is_low());

	while (1) {
		if (Encoder_rotary_read() == ROTATE_RIGHT) {
			VCObject.y = 1;
			VCObject.direction = LCD_INVERTED_RIGHT_ARROW;
			VC_set_cursor();
		}

		if (Encoder_rotary_read() == ROTATE_LEFT) {
			VCObject.y = 0;
			VCObject.direction = LCD_INVERTED_LEFT_ARROW;
			VC_set_cursor();
		}

		if (Encoder_switch_is_pressed()) {
			// Start the hotwire if the button is held
			if (Encoder_switch_is_held(SWITCH_HOLD_TIME)) {
				Hotwire_start();
				Buzzer_play(6, 50);
				VC_hotwire_running();
				return VIEW_MAIN_RUNNING;
			}

			// If the button wasn't held, then either edit the PWM or go to settings
			if (VCObject.y) {
				VC_set_cursor_blink();

				while (!Encoder_switch_is_high()) {
					if (Encoder_rotary_read() == ROTATE_RIGHT) {
						Hotwire_add_power_setting(0.1);
						VC_main_menu();
					}

					if (Encoder_rotary_read() == ROTATE_LEFT) {
						Hotwire_add_power_setting(-0.1);
						VC_main_menu();
					}
				}

				VC_stop_cursor_blink();

			} else {
				return VIEW_SETTINGS_MAIN;
			}
		}
	}
}

// EFFECTS: handles the main menu when the hotwire is on
uint8_t Interface_main_hotwire_on() {
	VCObject.x = 0;
	VCObject.y = 0;
	VCObject.direction = LCD_NO_CURSOR;
	VCObject.NEXT_VC = &VC_hotwire_running;

//	VC_hotwire_running();

	while (1) {
		if (Encoder_switch_is_pressed()) {
			Hotwire_stop();
			Buzzer_play(0, 40);
			VC_main_menu();
			return VIEW_MAIN_STOPPED;
		}

		if (Encoder_rotary_read() == ROTATE_RIGHT) {
			Hotwire_add_power_setting(0.1);
			VC_hotwire_running();
		}

		if (Encoder_rotary_read() == ROTATE_LEFT) {
			Hotwire_add_power_setting(-0.1);
			VC_hotwire_running();
		}
	}
}

// EFFECTS: handles the main settings page
uint8_t Interface_settings_main() {
	VCObject.x = 0;
	VCObject.y = 0;
	VCObject.direction = LCD_NO_CURSOR;
	VCObject.NEXT_VC = NULL;

	uint8_t setting_number = 0;

	VC_settings_main(setting_number);

	while (1) {
		if (Encoder_switch_is_pressed()) {
			switch (setting_number) {
				case 0:
					VC_main_menu();
					return VIEW_MAIN_STOPPED;

				case 1:
					return VIEW_SETTINGS_LCD;

				case 2:
					VC_main_menu();
					return VIEW_MAIN_STOPPED;
			}
		}

		if (Encoder_rotary_read() == ROTATE_LEFT) {
			if (setting_number > 0) setting_number--;

			if (!setting_number) VCObject.direction = LCD_INVERTED_LEFT_ARROW;

			VC_settings_main(setting_number);
		}

		if (Encoder_rotary_read() == ROTATE_RIGHT) {
			if (setting_number < NUM_SETTINGS) setting_number++;

			if (setting_number) VCObject.direction = LCD_INVERTED_RIGHT_ARROW;

			VC_settings_main(setting_number);
		}
	}
}

// EFFECTS: handles the LCD settings page
uint8_t Interface_settings_lcd() {
	VCObject.x = 0;
	VCObject.y = 0;
	VCObject.direction = LCD_INVERTED_LEFT_ARROW;
	VCObject.NEXT_VC = NULL;

	VC_settings_lcd();

	while (1) {
		// Handle moving the LCD selection cursor and direction arrow
		if (Encoder_rotary_read() == ROTATE_LEFT) {
			if (VCObject.x == 12 && VCObject.y == 1) {
				VCObject.y--;

			} else if (VCObject.x == 12 && VCObject.y == 0) {
				VCObject.x -= 12;
				VCObject.direction = LCD_INVERTED_LEFT_ARROW;
			}

			VC_set_cursor();
			while (Encoder_rotary_read() != ROTATE_NONE);

		} else if (Encoder_rotary_read() == ROTATE_RIGHT) {
			if (VCObject.x == 0 && VCObject.y == 0) {
				VCObject.x += 12;
				VCObject.direction = LCD_INVERTED_RIGHT_ARROW;
			} else if (VCObject.x == 12 && VCObject.y == 0) {
				VCObject.y++;
			}

			VC_set_cursor();
			while (Encoder_rotary_read() != ROTATE_NONE);
		}

		// Handle the encoder button press
		if (Encoder_switch_is_pressed()) {
			// Back button pressed
			if (VCObject.x == 0 && VCObject.y == 0) {
				return VIEW_SETTINGS_MAIN;
			}

			// Wait for encoder to be released
			while (!Encoder_switch_is_released());

			// Start blinking the cursor to tell which value is being edited
			VC_set_cursor_blink();

			// Edit the LCD values until the encoder button is pressed
			while (!Encoder_switch_is_high()) {
				if (Encoder_rotary_read() == ROTATE_RIGHT) {
					if (VCObject.y) LCDControl_increment_contrast();
					else LCDControl_increment_backlight();

					VC_settings_lcd();
				}

				if (Encoder_rotary_read() == ROTATE_LEFT) {
					if (VCObject.y) LCDControl_decrement_contrast();
					else LCDControl_decrement_backlight();

					VC_settings_lcd();
				}
			}

			// Stop blinking after editing
			VC_stop_cursor_blink();
		}
	}
}
