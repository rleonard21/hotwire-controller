// Buzzer.h
// Hotwire Controller Project
// Written by Robert Leonard

#ifndef _BUZZER_LIB_
#define _BUZZER_LIB_

#include <stdint.h>

// The D-Minor blues scale :)
static const uint16_t scale[] = {426, 358, 319, 301, 284, 239, 213};



// MODIFIES: Modifies the timer registers.
//			 Modifies the underlying PORTx.
// EFFECTS:  Creates a buzzer using timer 1 on pin 5.
void Buzzer_init();

// REQUIRES: 0 <= note <= 6
// Modifies: Modifies the output compare register and the underlying PORTx.
// EFFECTS:	 Makes the buzzer play a note according to the scale.
void Buzzer_play(int note, unsigned int duration);

// MODIFIES: Modifies the timer registers and the underlying PORTx.
// EFFECTS:  Makes the buzzer stop playing a note.
void Buzzer_stop();

#endif
