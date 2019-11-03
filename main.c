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
#include "sensors/INA219.h"
#include "pid/PID.h"

int main(void) {
	sei();

	LCDControl_init();
	LCDControl_set_contrast(185);
	LCDControl_set_backlight(255);

	lcd_init(LCD_DISP_ON);
	lcd_clrscr();

	VC_init();
	VC_startup_screen();

	Hotwire_init();
	Encoder_init();
	Buzzer_init();
	INA219_init();
	PID_init();

	_delay_ms(500);

	uint8_t next_view = VIEW_MAIN_STOPPED;

	while (1) {
		switch (next_view) {
			case VIEW_MAIN_STOPPED: {
				next_view = Interface_main_hotwire_off();
				break;
			}

			case VIEW_MAIN_RUNNING: {
				next_view = Interface_main_hotwire_on();
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

			case VIEW_SETTINGS_PID: {
				next_view = Interface_settings_pid();
				break;
			}

			default: {
				break;
			}
		}
	}
}
