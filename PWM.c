// PWM.h
// Hotwire Controller Project
// Written by Robert Leonard

#include "PWM.h"
#include <avr/io.h>

void PWM_init(struct PWM_16_bit *pwm) {
    pwm->counter = 0;
}


void PWM_start(struct PWM_16_bit *pwm) {
    PORTD = 0x00;
}
