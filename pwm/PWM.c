// PWM.h
// Hotwire Controller Project
// Written by Robert Leonard

#include "PWM.h"
#include <avr/io.h>

void PWM_init(struct PWM_16_bit *pwm) {
    pwm->counter = 0;
    pwm->is_running = false;

    // set the MOSFET pin an an output
    // enable the 16 bit timer
    // set the timer prescaler
}

void PWM_set(struct PWM_16_bit *pwm, uint16_t setting) {
    pwm->counter = setting;
}

uint16_t PWM_get(struct PWM_16_bit *pwm) {
    return pwm->counter;
}

bool PWM_is_running(struct PWM_16_bit *pwm) {
    return pwm->is_running;
}

void PWM_start(struct PWM_16_bit *pwm) {
    pwm->is_running = true;
    // set the timer register to pwm->counter
}

void PWM_stop(struct PWM_16_bit *pwm) {
    pwm->is_running = false;
    // set the timer register to zero
}
