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

#define SWITCH_HOLD_TIME 200000

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

	struct Cursor cursor = {0, 0};

	Hotwire_set(100);

	lcd_command(LCD_DISP_ON_BLINK);
	VC_main_menu(cursor, 1, 1);

	while (1) {
		if (Encoder_rotary_read() == ROTATE_RIGHT) {
			cursor.y = 1;
			lcd_gotoxy(cursor.x, cursor.y);
		}

		if (Encoder_rotary_read() == ROTATE_LEFT) {
			cursor.y = 0;
			lcd_gotoxy(cursor.x, cursor.y);
		}

		if (Encoder_switch_is_pressed()) {
			if (Encoder_switch_is_held(SWITCH_HOLD_TIME)) {
				Hotwire_start();
				Buzzer_play(1, 50);
				return VIEW_SETTINGS_LCD;
			}

			if (cursor.y) {
				while (!Encoder_switch_is_high()) {
					if (Encoder_rotary_read() == ROTATE_RIGHT) {
						Hotwire_set_increment();
						VC_main_menu(cursor, 1, 1);
					}

					if (Encoder_rotary_read() == ROTATE_LEFT) {
						Hotwire_set_decrement();
						VC_main_menu(cursor, 1, 1);
					}
				}
			} else {
				return VIEW_SETTINGS_MAIN;
			}
		}
	}
}

// EFFECTS: handles the main settings page
uint8_t Interface_settings_main() {
	VC_page_incomplete();

	if (Encoder_switch_is_pressed()) {
		return VIEW_MAIN_STOPPED;
	}

	return VIEW_SETTINGS_MAIN;
}

// EFFECTS: handles the LCD settings page
uint8_t Interface_settings_lcd() {
	struct Cursor cursor = {0, 0};

	VC_settings_lcd(cursor);

	while(1) {
		// Handle moving the LCD selection cursor
		if(Encoder_rotary_read() == ROTATE_LEFT) {
			if(cursor.x && cursor.y)
				cursor.y--;
			else if(cursor.x == 12 && cursor.y == 0)
				cursor.x -= 12;

			lcd_gotoxy(cursor.x, cursor.y);
			while(Encoder_rotary_read() != ROTATE_NONE);

		} else if(Encoder_rotary_read() == ROTATE_RIGHT) {
			if(!cursor.x && !cursor.y)
				cursor.x += 12;
			else if(cursor.x && !cursor.y)
				cursor.y++;

			lcd_gotoxy(cursor.x, cursor.y);
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
		}
	}
}
