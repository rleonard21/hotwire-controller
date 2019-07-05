// ViewController.c
// Created by Robert Leonard on 2019-07-04.
//

#include "ViewController.h"

#include "lcd.h"
#include "StringUtility.h"

// EFFECTS: these two arrays will represent lines 1 and 2 of the LCD
static char line1[] = "................\n";
static char line2[] = "................\n";

// EFFECTS: updates the LCD to display lines 1 and 2
static void update_lcd() {
	lcd_puts(line1);
	lcd_puts(line2);
}

// EFFECTS: displays the startup page
void VC_startup_screen() {
	lcd_puts("hotwire v1.1\n");
	lcd_puts("\n");
}

// EFFECTS: prints an error message
void VC_page_incomplete() {
	lcd_puts("Page incomplete.\n\n");
}
