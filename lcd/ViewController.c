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

// EFFECTS: displays the startup page
void VC_startup_screen() {
	lcd_gotoxy(0, 0);

	lcd_puts("hotwire v1.1\n");
	lcd_puts("\n");
}

// EFFECTS: displays the main menu page
void VC_main_menu(struct Cursor cursor, uint8_t power, uint8_t voltage) {
	lcd_gotoxy(0, 0);

//	strcpy(next_line_1, "< READY   12.04v\n");
//	strcpy(next_line_2, "> Duty:      73%\n");

	sprintf(next_line_1, "< READY   12.04v\n");
	sprintf(next_line_2, "> Duty:      %d\n", OCR1B);

	update_lcd();
	lcd_gotoxy(cursor.x, cursor.y);
}

// EFFECTS: displays the hotwire page
void VC_hotwire_running(struct Cursor cursor) {
	lcd_gotoxy(0, 0);

	sprintf(next_line_1, "RUNNING    23.1W\n");
	sprintf(next_line_2, "D: %d    11.91v\n", OCR1B);

	update_lcd();
	lcd_gotoxy(cursor.x, cursor.y);
}

// EFFECTS: displays the main settings page
void VC_settings_main(struct Cursor cursor, uint8_t settings_page) {
	lcd_gotoxy(0, 0);

	const char *settings[] = {
			"< main menu     \n",
			"  LCD           \n",
			"  PWM           \n",
			"                \n"
	};

	strcpy(next_line_1, settings[settings_page]);
	strcpy(next_line_2, settings[settings_page + 1]);

	update_lcd();
	lcd_gotoxy(cursor.x, cursor.y);

}

// EFFECTS: displays the LCD settings page
void VC_settings_lcd(struct Cursor cursor) {
	lcd_gotoxy(0, 0);

	sprintf(next_line_1, "< Bright:   >%d\n", OCR0B);
	sprintf(next_line_2, "  Contrast: >%d\n", OCR0A);

	update_lcd();
	lcd_gotoxy(cursor.x, cursor.y);
}

// EFFECTS: displays the PWM settings page
void VC_settings_pwm(struct Cursor cursor) {
	lcd_gotoxy(0, 0);

	sprintf(next_line_1, "< Incr:     >%d\n", 1);
	sprintf(next_line_2, "  Clk div:  >%d\n", 8);

	update_lcd();
	lcd_gotoxy(cursor.x, cursor.y);
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
