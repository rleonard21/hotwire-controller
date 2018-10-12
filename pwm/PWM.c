// PWM.c
// Hotwire Controller Project
// Written by Robert Leonard

#include "PWM.h"
#include <avr/io.h>

void PWM_init(struct PWM_16_bit *pwm, uint16_t *output_register) {
    pwm->reg = ouput_register;
    pwm->counter = 0;
    pwm->is_running = false;

    // set the MOSFET pin an an output
    // enable the 16 bit timer
    // set the timer prescaler
    // set the timer to 0...?
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
    // todo: set the timer register to pwm->counter
    pwm->is_running = true;
}

void PWM_stop(struct PWM_16_bit *pwm) {
    // todo: set the timer register to zero
    pwm->is_running = false;
}
