// Buzzer.h
// Hotwire Controller Project
// Written by Robert Leonard

#ifndef _BUZZER_LIB_
#define _BUZZER_LIB_

#include <stdint.h>

// MODIFIES: Modifies the timer registers and underlying PORTx.
// EFFECTS:  Initializes the buzzer.
void Buzzer_init();

// REQUIRES: 0 <= note <= 6
// Modifies: Modifies the output compare register and the underlying PORTx.
// EFFECTS:	 Makes the buzzer play a note according to the scale.
//			 Duration is the time to play the note, in 0.1 second increments
void Buzzer_play(int note, unsigned int duration);

// MODIFIES: Modifies the timer registers and the underlying PORTx.
// EFFECTS:  Makes the buzzer stop playing a note.
void Buzzer_stop();

#endif
