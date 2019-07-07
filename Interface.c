// Interface.c
// Created by Robert Leonard on 2019-07-04.
//

#include "Interface.h"

#include "lcd/ViewController.h"
#include "encoder/Encoder.h"
#include "hotwire/Hotwire.h"
#include "feedback/Buzzer.h"
#include "lcd/LCDControl.h"

#include "lcd/lcd.h"

#define SWITCH_HOLD_TIME    200000

// EFFECTS: handles the main menu
uint8_t Interface_main_hotwire_off() {
	/* TODO:
	 *  * display the status and prompt (START/STOP)
	 *  * display the voltage
	 *  * display the percent
	 *  * handle the cursor / rotation
	 *  * ~handle the hotwire start/stop
	 *  * ~handle the transition to the settings page
	 */

	// Display the main menu
	// TODO: remain (1,1) with voltage and duty cycle...

	struct Cursor cursor = {0, 0, LCD_INVERTED_LEFT_ARROW};

	VC_main_menu(cursor, 1, 1);

	while (1) {
		if (Encoder_rotary_read() == ROTATE_RIGHT) {
			cursor.y = 1;
			cursor.direction = LCD_INVERTED_RIGHT_ARROW;
			VC_set_cursor(cursor);
		}

		if (Encoder_rotary_read() == ROTATE_LEFT) {
			cursor.y = 0;
			cursor.direction = LCD_INVERTED_LEFT_ARROW;
			VC_set_cursor(cursor);
		}

		if (Encoder_switch_is_pressed()) {
			// Start the hotwire if the button is held
			if (Encoder_switch_is_held(SWITCH_HOLD_TIME)) {
				Hotwire_start();
				Buzzer_play(6, 50);
				return VIEW_MAIN_RUNNING;
			}

			// If the button wasn't held, then either edit the PWM or go to settings
			if (cursor.y) {
				VC_set_cursor_blink(cursor);

				while (!Encoder_switch_is_high()) {
					if (Encoder_rotary_read() == ROTATE_RIGHT) {
						Hotwire_increment();
						VC_main_menu(cursor, 1, 1);
					}

					if (Encoder_rotary_read() == ROTATE_LEFT) {
						Hotwire_decrement();
						VC_main_menu(cursor, 1, 1);
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
	struct Cursor cursor = {0, 0, LCD_NO_CURSOR};

	VC_hotwire_running(cursor);

	while(1) {
		if(Encoder_switch_is_pressed()) {
			Hotwire_stop();
			Buzzer_play(0, 40);
			return VIEW_MAIN_STOPPED;
		}

		if(Encoder_rotary_read() == ROTATE_RIGHT) {
			Hotwire_increment();
			VC_hotwire_running(cursor);
		}

		if(Encoder_rotary_read() == ROTATE_LEFT) {
			Hotwire_decrement();
			VC_hotwire_running(cursor);
		}
	}
}

// EFFECTS: handles the main settings page
uint8_t Interface_settings_main() {
	struct Cursor cursor = {0, 0, LCD_INVERTED_LEFT_ARROW};

	uint8_t setting_number = 0;

	VC_settings_main(cursor, setting_number);

	while(1) {
		if (Encoder_switch_is_pressed()) {
			switch(setting_number) {
				case 0: return VIEW_MAIN_STOPPED;

				case 1: return VIEW_SETTINGS_LCD;

				case 2: return VIEW_SETTINGS_PWM;

				case 3: return VIEW_MAIN_STOPPED;
			}
		}

		if(Encoder_rotary_read() == ROTATE_LEFT) {
			if(setting_number > 0) setting_number--;

			if(!setting_number) cursor.direction = LCD_INVERTED_LEFT_ARROW;

			VC_settings_main(cursor, setting_number);
		}

		if(Encoder_rotary_read() == ROTATE_RIGHT) {
			if(setting_number < NUM_SETTINGS) setting_number++;

			if(setting_number) cursor.direction = LCD_INVERTED_RIGHT_ARROW;

			VC_settings_main(cursor, setting_number);
		}
 	}
}

// EFFECTS: handles the LCD settings page
uint8_t Interface_settings_lcd() {
	struct Cursor cursor = {0, 0, LCD_INVERTED_LEFT_ARROW};

	VC_settings_lcd(cursor);

	while(1) {
		// Handle moving the LCD selection cursor and direction arrow
		if(Encoder_rotary_read() == ROTATE_LEFT) {
			if(cursor.x == 12 && cursor.y == 1) {
				cursor.y--;

			} else if(cursor.x == 12 && cursor.y == 0) {
				cursor.x -= 12;
				cursor.direction = LCD_INVERTED_LEFT_ARROW;
			}

			VC_set_cursor(cursor);
			while(Encoder_rotary_read() != ROTATE_NONE);

		} else if(Encoder_rotary_read() == ROTATE_RIGHT) {
			if(cursor.x == 0 && cursor.y == 0) {
				cursor.x += 12;
				cursor.direction = LCD_INVERTED_RIGHT_ARROW;
			} else if(cursor.x == 12 && cursor.y == 0) {
				cursor.y++;
			}

			VC_set_cursor(cursor);
			while(Encoder_rotary_read() != ROTATE_NONE);
		}

		// Handle the encoder button press
		if(Encoder_switch_is_pressed()) {
			// Back button pressed
			if(cursor.x == 0 && cursor.y == 0) {
				return VIEW_SETTINGS_MAIN;
			}

			// Wait for encoder to be released
			while(!Encoder_switch_is_released());

			// Start blinking the cursor to tell which value is being edited
			VC_set_cursor_blink(cursor);

			// Edit the LCD values until the encoder button is pressed
			while(!Encoder_switch_is_high()) {
				if (Encoder_rotary_read() == ROTATE_RIGHT) {
					if(cursor.y) LCDControl_increment_contrast();
					else LCDControl_increment_backlight();

					VC_settings_lcd(cursor);
				}

				if (Encoder_rotary_read() == ROTATE_LEFT) {
					if(cursor.y) LCDControl_decrement_contrast();
					else LCDControl_decrement_backlight();

					VC_settings_lcd(cursor);
				}
			}

			// Stop blinking after editing
			VC_stop_cursor_blink();
		}
	}
}

// EFFECTS: handles the PWM settings page
// TODO:    implement this function
uint8_t Interface_settings_pwm() {
	struct Cursor cursor = {0, 0};
	VC_settings_pwm(cursor);

	while(1) {
		if(Encoder_switch_is_pressed()) {
			return VIEW_SETTINGS_MAIN;
		}
	}
}
