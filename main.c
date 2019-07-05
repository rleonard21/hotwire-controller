// main.c
// Written by Robert Leonard

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdint.h>
#include <stdio.h>

#include "lcd/LCDControl.h"
#include "lcd/lcd.h"
#include "lcd/ViewController.h"
#include "hotwire/Hotwire.h"
#include "encoder/Encoder.h"
#include "encoder/Debounce.h"
#include "feedback/Buzzer.h"
#include "Interface.h"


int main(void) {
	sei();

	LCDControl_init();
	LCDControl_set_contrast(55);
	LCDControl_set_backlight(150);

	lcd_init(LCD_DISP_ON);
	lcd_clrscr();
	VC_startup_screen();

	Buzzer_init();
	Encoder_init();

	/* TODO:
	 *  * INA219 init
	 */

	_delay_ms(500);

	uint8_t next_view = VIEW_MAIN;

	while(1) {
		switch(next_view) {
			case VIEW_MAIN: {
				next_view = Interface_main();
				break;
			}

			case VIEW_SETTINGS_MAIN: {
				next_view = Interface_settings_main();
				break;
			}

			case VIEW_SETTINGS_LCD: {
				next_view = Interface_settings_lcd();
				break;
			}
		}
 	}
}
