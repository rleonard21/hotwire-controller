// PWM.h
// Hotwire Controller Project
// Written by Robert Leonard

#ifndef _PWM_LIB_
#define _PWM_LIB_

#include <stdint.h>

struct PWM_16_bit {
    uint16_t counter;
};

void PWM_init(struct PWM_16_bit *pwm);
void PWM_set(struct PWM_16_bit *pwm, uint16_t counter);
void PWM_start(struct PWM_16_bit *pwm);
void PWM_stop(struct PWM_16_bit *pwm);

#endif
