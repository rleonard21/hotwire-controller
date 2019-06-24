// Buzzer.c
// Hotwire Controller Project
// Written by Robert Leonard

#include <avr/io.h>
#include <avr/interrupt.h>

#include "Buzzer.h"

// EFFECTS:  Counter used for knowing the duration of the note being played
volatile unsigned int num_buzzer_interrupts = 0;
volatile unsigned int max_buzzer_interrupts = 0;

// EFFECTS: The D-Minor blues scale :)
static const uint16_t scale[] = {426, 358, 319, 301, 284, 239, 213};

// EFFECTS: The number of interrupts to play a note for 0.1 seconds
// TODO: calculate these values
static const uint16_t buzzer_duration[] = {0, 0, 0, 0, 0, 0, 0};

// MODIFIES: Modifies the timer registers and underlying PORTx.
// EFFECTS:  Initializes the buzzer.
void Buzzer_init() {
	DDRD |= _BV(PORTD3);  // set the buzzer to an output
	TCNT2 = 0;            // clear the counter
}

// REQUIRES: 0 <= note <= 6
// Modifies: Modifies the output compare register and the underlying PORTx.
// EFFECTS:	 Makes the buzzer play a note according to the scale.
//			 Duration is the time to play the note, in 0.1 second increments
void Buzzer_play(int note, unsigned int duration) {
	TCCR2A |= _BV(WGM21);   // set up the timer for CTC mode
	TCCR2B |= _BV(CS22);    // set the timer prescaler=64
	TIMSK2 |= _BV(OCIE2B);  // enable the compare interrupt

	OCR2B = scale[note];	// set the note to be played
	max_buzzer_interrupts = buzzer_duration[note] * duration;
}

// MODIFIES: Modifies the timer registers.
// EFFECTS:  Makes the buzzer stop playing a note.
void Buzzer_stop() {
	TCCR2B &= ~_BV(CS22);   // disable the timer (prescaler=0)
	PORTD &= ~_BV(PORTD3);	// clear the buzzer pin
	TCNT2 = 0;			    // clear the counter

	num_buzzer_interrupts = 0;
}

// MODIFIES: Modifies the underlying PORTx.
// EFFECTS:  Toggles the buzzer.
ISR(TIMER1_COMPA_vect) {
	if(num_buzzer_interrupts >= max_buzzer_interrupts) {
		Buzzer_stop();
	} else {
		PORTD ^= _BV(PORTD3);
		num_buzzer_interrupts++;
	}
}
