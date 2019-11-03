// ViewController.c
// Created by Robert Leonard on 2019-07-04.
//

#include "ViewController.h"

#include "lcd.h"
#include "StringUtility.h"

#include "../sensors/INA219.h"
#include "../hotwire/Hotwire.h"
#include "../pid/PID.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

volatile uint32_t vc_num_ticks = 0;
volatile uint32_t vc_max_ticks = 90000;

// EFFECTS: these two arrays will represent lines 1 and 2 of the LCD
static char current_line_1[] = "................\n\n";
static char current_line_2[] = "................\n\n";
static char next_line_1[] = "................\n\n";
static char next_line_2[] = "................\n\n";

// EFFECTS: bit mappings for the inverted left/right arrow custom LCD characters
static char inverted_left_arrow[] = {0x1D, 0x1B, 0x17, 0x0F, 0x17, 0x1B, 0x1D, 0x1F};
static char inverted_right_arrow[] = {0x17, 0x1B, 0x1D, 0x1E, 0x1D, 0x1B, 0x17, 0x1F};

// EFFECTS: keeps track of the last location the cursor was written to
static struct VCO last_cursor = {0, 0, 0, NULL};

// EFFECTS: updates the LCD to display lines 1 and 2
static void update_lcd() {
	if (strcmp(current_line_1, next_line_1) != 0 ||
	    strcmp(current_line_2, next_line_2) != 0) {

		strcpy(current_line_1, next_line_1);
		strcpy(current_line_2, next_line_2);

		lcd_gotoxy(0, 0);
		lcd_puts(current_line_1);
		lcd_gotoxy(0, 1);
		lcd_puts(current_line_2);
	}
}

// EFFECTS: send the bit mappings of a custom character to the LCD
static void create_custom_char(char *char_array, uint8_t addr) {
	// Select the address
	lcd_command(0x40 + addr * 8);

	// Send the data to create the char
	for(char *ptr = char_array; ptr < char_array + 8; ptr++) {
		lcd_data(*ptr);
	}
}

// EFFECTS: initializes the view controller
void VC_init() {
	create_custom_char(inverted_left_arrow, LCD_INVERTED_LEFT_ARROW);
	create_custom_char(inverted_right_arrow, LCD_INVERTED_RIGHT_ARROW);

	VCObject.x = 0;
	VCObject.y = 0;
	VCObject.direction = 0;
	VCObject.NEXT_VC = &VC_startup_screen;

	lcd_gotoxy(0, 0);
}

// EFFECTS: creates a selection cursor at the given coordinate
void VC_set_cursor() {
	// Clear the last cursor location
	lcd_gotoxy(last_cursor.x, last_cursor.y);
	lcd_putc(' ');

	lcd_gotoxy(VCObject.x, VCObject.y);

	// Create the new cursor
	if(VCObject.direction) {
		lcd_putc(LCD_INVERTED_RIGHT_ARROW);
	} else {
		lcd_putc(LCD_INVERTED_LEFT_ARROW);
	}

	lcd_gotoxy(VCObject.x, VCObject.y);

	last_cursor = VCObject;
}

// EFFECTS: creates a blinking cursor at the given coordinate
void VC_set_cursor_blink() {
	lcd_command(LCD_DISP_ON_BLINK);
	VC_set_cursor();
}

// EFFECTS: stops the blinking cursor
void VC_stop_cursor_blink() {
	lcd_command(LCD_DISP_ON);
}

// EFFECTS: displays the startup page
void VC_startup_screen() {
	lcd_gotoxy(0, 0);

	lcd_puts("hotwire v1.1.0\n");
	lcd_puts("\n");
}

// EFFECTS: displays the main menu page
void VC_main_menu() {
	lcd_gotoxy(0, 0);

	char voltage[6];
	char powerSetting[6];

	StringUtility_fixed_float(voltage, INA219_getBusVoltage());
	StringUtility_fixed_float(powerSetting, Hotwire_get_power());

	sprintf(next_line_1, "  READY    %sv\n", voltage);
	sprintf(next_line_2, "  Set:   (%sw)\n", powerSetting);

	update_lcd();
	VC_set_cursor();
}

// EFFECTS: displays the hotwire page
void VC_hotwire_running() {
	lcd_gotoxy(0, 0);

	char voltage[6];
	char current[6];
	char power[6];
	char powerSetting[6];

	StringUtility_fixed_float(voltage, INA219_getBusVoltage());
	StringUtility_fixed_float(current, INA219_getCurrent());
	StringUtility_fixed_float(power, INA219_getPower());
	StringUtility_fixed_float(powerSetting, Hotwire_get_power());

	sprintf(next_line_1, "RUNNING    %sA\n", current);
	sprintf(next_line_2, "(%sw)    %sw\n", powerSetting, power);

	update_lcd();
}

// EFFECTS: displays the main settings page
void VC_settings_main(uint8_t settings_page) {
	lcd_gotoxy(0, 0);

	const char *settings[] = {
			"  main menu     \n",
			"  LCD           \n",
			"  PID           \n",
			"                \n"
	};

	strcpy(next_line_1, settings[settings_page]);
	strcpy(next_line_2, settings[settings_page + 1]);

	update_lcd();
	VC_set_cursor();
}

// EFFECTS: displays the LCD settings page
void VC_settings_lcd() {
	lcd_gotoxy(0, 0);

	sprintf(next_line_1, "  Bright:    %d\n", OCR0B);
	sprintf(next_line_2, "  Contrast:  %d\n", OCR0A);

	update_lcd();
	VC_set_cursor();
}

// EFFECTS: displays the PID setitngs page
void VC_settings_pid() {
	lcd_gotoxy(0, 0);

	char p[6];
	char i[6];
	char d[6];

	StringUtility_fixed_float(p, PID_get_p());
	StringUtility_fixed_float(i, PID_get_i());
	StringUtility_fixed_float(d, PID_get_d());

	sprintf(next_line_1, "  P:%s I:%s\n", p, i);
	sprintf(next_line_2, "  D:%s        \n", d);

	update_lcd();
	VC_set_cursor();
}

// EFFECTS: prints an error message
void VC_page_incomplete() {
	lcd_gotoxy(0, 0);

	strcpy(next_line_1, "Page incomplete.\n");
	strcpy(next_line_2, "...............1\n");

	update_lcd();
}

// EFFECTS: prints an error message
void VC_page_incomplete_2() {
	lcd_gotoxy(0, 0);

	strcpy(next_line_1, "Page incomplete.\n");
	strcpy(next_line_2, "...............2\n");

	update_lcd();
}

// EFFECTS: updates the screen
void VC_update_service() {
	if(VCObject.NEXT_VC) {
		(*VCObject.NEXT_VC)();
	}
}
