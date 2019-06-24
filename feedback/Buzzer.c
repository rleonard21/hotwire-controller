// Buzzer.c
// Hotwire Controller Project
// Written by Robert Leonard

#include <avr/io.h>
#include <avr/interrupt.h>

#include "Buzzer.h"

#define BUZZER_PRESCALER ( (1 << CS22) | (1 << CS20) )

// EFFECTS:  Counter used for knowing the duration of the note being played
volatile unsigned int num_buzzer_interrupts = 0;
volatile unsigned int max_buzzer_interrupts = 0;

// EFFECTS: The D-Minor blues scale :)
static const uint8_t scale[] = {212, 178, 158, 149, 141, 118, 105};

// EFFECTS: The number of interrupts to play a note for 0.1 seconds
static const uint8_t buzzer_duration[] = {6, 7, 8, 8, 9, 11, 12};

// MODIFIES: Modifies the timer registers and underlying PORTx.
// EFFECTS:  Initializes the buzzer.
void Buzzer_init() {
	DDRD |= _BV(PORTD3);  // set the buzzer to an output
	TCNT2 = 0;            // clear the counter
}

// REQUIRES: 0 <= note <= 6
// Modifies: Modifies the output compare register and the underlying PORTx.
// EFFECTS:	 Makes the buzzer play a note according to the scale.
//			 Duration is the time to play the note, in 0.01 second increments
void Buzzer_play(int note, unsigned int duration) {
	TCCR2A |= _BV(WGM21) | _BV(COM2B0);   // set up the timer for CTC mode, hardware toggle
	TCCR2A &= ~_BV(COM2B1);
	TCCR2B |= BUZZER_PRESCALER;           // set the timer prescaler=64
	TIMSK2 |= _BV(OCIE2A);                // enable the compare interrupt

	OCR2A = scale[note];                  // set the note to be played
	max_buzzer_interrupts = buzzer_duration[note] * duration;
}

// MODIFIES: Modifies the timer registers.
// EFFECTS:  Makes the buzzer stop playing a note.
void Buzzer_stop() {
	TCCR2B &= ~BUZZER_PRESCALER;	// disable the timer (prescaler=0)
	TCCR2A |= _BV(COM2B1);			// clear the buzzer on match
	TCCR2A &= ~_BV(COM2B0);
	TCCR2B |= _BV(FOC2B);			// force match to clear the buzzer
	TCNT2 = 0;						// clear the counter

	num_buzzer_interrupts = 0;
}

// MODIFIES: Modifies the timer registers and the underlying PORTx.
// EFFECTS:  Returns 1 if the buzzer is playing a note
uint8_t Buzzer_is_playing() {
	return (uint8_t) (TCCR2B & BUZZER_PRESCALER);
}

// MODIFIES: Modifies the underlying PORTx.
// EFFECTS:  Toggles the buzzer.
ISR(TIMER2_COMPA_vect) {
	if (num_buzzer_interrupts >= max_buzzer_interrupts) {
		Buzzer_stop();
	} else {
		num_buzzer_interrupts++;
	}
}
