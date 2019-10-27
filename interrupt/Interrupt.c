// Interrupt.c
// Created by Robert Leonard on 10/27/19.
//

#include "Interrupt.h"

#include <avr/interrupt.h>
#include "../encoder/Debounce.h"
#include "../sensors/INA219.h"
#include "../lcd/ViewController.h"
#include "../hotwire/Hotwire.h"
// EFFECTS: inits the system tick
void Interrupt_init() {
	// TODO: move timer start from debounce to here
}

// EFFECTS: executes on overflow of timer0
ISR(TIMER0_OVF_vect) {
	// DEBOUNCE SERVICE
	if(debounce_num_ticks++ > debounce_max_ticks) {
		Debounce_update_service();
		debounce_num_ticks = 0;
	}

	// INA219 SERVICE
	if(ina219_num_ticks++ > ina219_max_ticks) {
		INA219_update_service();
		ina219_num_ticks = 0;
	}

	// LCD SERVICE
	if(vc_num_ticks++ > vc_max_ticks) {
		VC_update_service();
		vc_num_ticks = 0;
	}

	// PID SERVICE
	// TODO
}
