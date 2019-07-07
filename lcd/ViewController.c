// ViewController.c
// Created by Robert Leonard on 2019-07-04.
//

#include "ViewController.h"

#include "lcd.h"
#include "StringUtility.h"

#include <string.h>
#include <stdio.h>

// EFFECTS: these two arrays will represent lines 1 and 2 of the LCD
static char current_line_1[] = "................\n";
static char current_line_2[] = "................\n";
static char next_line_1[] = "................\n";
static char next_line_2[] = "................\n";

// EFFECTS: bit mappings for the inverted left/right arrow custom LCD characters
static char inverted_left_arrow[] = {0x1D, 0x1B, 0x17, 0x0F, 0x17, 0x1B, 0x1D, 0x1F};
static char inverted_right_arrow[] = {0x17, 0x1B, 0x1D, 0x1E, 0x1D, 0x1B, 0x17, 0x1F};

// EFFECTS: keeps track of the last location the cursor was written to
static struct Cursor last_cursor = {0, 0};

// EFFECTS: updates the LCD to display lines 1 and 2
static void update_lcd() {
	if (strcmp(current_line_1, next_line_1) ||
	    strcmp(current_line_2, next_line_2)) {

		strcpy(current_line_1, next_line_1);
		strcpy(current_line_2, next_line_2);

		lcd_puts(current_line_1);
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

	lcd_gotoxy(0, 0);
}

// EFFECTS: creates a selection cursor at the given coordinate
void VC_set_cursor(struct Cursor cursor) {
	// Clear the last cursor location
	lcd_gotoxy(last_cursor.x, last_cursor.y);
	lcd_putc(' ');

	lcd_gotoxy(cursor.x, cursor.y);

	// Create the new cursor
	if(cursor.direction) {
		lcd_putc(LCD_INVERTED_RIGHT_ARROW);
	} else {
		lcd_putc(LCD_INVERTED_LEFT_ARROW);
	}

	lcd_gotoxy(cursor.x, cursor.y);

	last_cursor = cursor;
}

// EFFECTS: creates a blinking cursor at the given coordinate
void VC_set_cursor_blink(struct Cursor cursor) {
	lcd_command(LCD_DISP_ON_BLINK);
	VC_set_cursor(cursor);
}

// EFFECTS: stops the blinking cursor
void VC_stop_cursor_blink() {
	lcd_command(LCD_DISP_ON);
}

// EFFECTS: displays the startup page
void VC_startup_screen() {
	lcd_gotoxy(0, 0);

	lcd_puts("hotwire v1.1\n");
	lcd_puts("\n");
}

// EFFECTS: displays the main menu page
void VC_main_menu(struct Cursor cursor, uint8_t power, uint8_t voltage) {
	lcd_gotoxy(0, 0);

	sprintf(next_line_1, "  READY   12.04v\n");
	sprintf(next_line_2, "  Duty:      %d\n", OCR1B);

	update_lcd();
	VC_set_cursor(cursor);
}

// EFFECTS: displays the hotwire page
void VC_hotwire_running(struct Cursor cursor) {
	lcd_gotoxy(0, 0);

	sprintf(next_line_1, "RUNNING    23.1W\n");
	sprintf(next_line_2, "D: %d    11.91v\n", OCR1B);

	update_lcd();
//	VC_set_cursor(cursor);
}

// EFFECTS: displays the main settings page
void VC_settings_main(struct Cursor cursor, uint8_t settings_page) {
	lcd_gotoxy(0, 0);

	const char *settings[] = {
			"  main menu     \n",
			"  LCD           \n",
			"  PWM           \n",
			"                \n"
	};

	strcpy(next_line_1, settings[settings_page]);
	strcpy(next_line_2, settings[settings_page + 1]);

	update_lcd();
	VC_set_cursor(cursor);

}

// EFFECTS: displays the LCD settings page
void VC_settings_lcd(struct Cursor cursor) {
	lcd_gotoxy(0, 0);

	sprintf(next_line_1, "  Bright:    %d\n", OCR0B);
	sprintf(next_line_2, "  Contrast:  %d\n", OCR0A);

	update_lcd();
	VC_set_cursor(cursor);
}

// EFFECTS: displays the PWM settings page
void VC_settings_pwm(struct Cursor cursor) {
	lcd_gotoxy(0, 0);

	sprintf(next_line_1, "  Incr:      %d\n", 1);
	sprintf(next_line_2, "  Clk div:   %d\n", 8);

	update_lcd();
	VC_set_cursor(cursor);
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
