// Buzzer.c
// Hotwire Controller Project
// Written by Robert Leonard

#include <avr/io.h>
#include <avr/interrupt.h>

#include "Buzzer.h"

// MODIFIES: Modifies the timer registers.
//			 Modifies the underlying PORTx.
// EFFECTS:  Creates a buzzer using timer 1 on pin 5.
void Buzzer_init() {
	DDRD |= _BV(5); // set PORTD5 to an output
	TCNT1 = 0x00;   // clear the counter
}

// REQUIRES: 0 <= note <= 6
// Modifies: Modifies the output compare register and the underlying PORTx.
// EFFECTS:	 Makes the buzzer play a note according to the scale.
void Buzzer_play(int note) {
	// set up the timer for CTC mode, prescaler = 64
	TCCR1B |= _BV(WGM12) | _BV(CS11) | _BV(CS10);
	TIMSK1 |= _BV(OCIE1A);  // ennable the compare interrupt
	OCR1A = scale[note];	// set the note to be played
}

// MODIFIES: Modifies the timer registers. Disables
// EFFECTS:  Makes the buzzer stop playing a note.
void Buzzer_stop() {
	TCCR1B &= 0xf8;		// disable the timer
	TCCR1A = 0x00;		// disconnect the output pin
	TCNT1 = 0;			// clear the counter
	PORTD &= ~_BV(5);	// clear the pin
}

// MODIFIES: Modifies the underlying PORTx.
// EFFECTS:  Toggles PORTD5.
ISR(TIMER1_COMPA_vect) {
	PORTD ^= _BV(5);
}
