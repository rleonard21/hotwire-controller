// Interface.c
// Created by Robert Leonard on 2019-07-04.
//

#include "Interface.h"

#include "lcd/ViewController.h"
#include "encoder/Encoder.h"
#include "hotwire/Hotwire.h"

#define SWITCH_HOLD_TIME 100

// EFFECTS: handles the main menu
uint8_t Interface_main() {
	/* TODO:
	 *  * display the status and prompt (START/STOP)
	 *  * display the voltage
	 *  * display the percent
	 *  * ~handle the hotwire start/stop
	 *  * ~handle the transition to the settings page
	 */

	// Stop the running hotwire on button press
	if(Encoder_switch_is_pressed() && !Hotwire_is_running()) {
		Hotwire_stop();
		return VIEW_MAIN;
	}

	// Start the paused hotwire on button hold
	if(Encoder_switch_is_pressed() && !Hotwire_is_running()) {
		uint16_t timer = 0;
		while(Encoder_switch_is_high()) timer++;

		if(timer > SWITCH_HOLD_TIME) {
			Hotwire_start();
		} else {
			return VIEW_SETTINGS_MAIN;
		}
	}

	return VIEW_MAIN;
}

// EFFECTS: handles the main settings page
uint8_t Interface_settings_main() {
	VC_page_incomplete();
}

// EFFECTS: handles the LCD settings page
uint8_t Interface_settings_lcd() {
	VC_page_incomplete();
}
