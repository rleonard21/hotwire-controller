// PWM.h
// Hotwire Controller Project
// Written by Robert Leonard

#ifndef _PWM_LIB_
#define _PWM_LIB_

#include <stdint.h>

struct PWM_16_bit {
    uint16_t counter;
    bool is_running;
};

void PWM_init(struct PWM_16_bit *pwm);

void PWM_set(struct PWM_16_bit *pwm, uint16_t setting);
uint16_t PWM_get(struct PWM_16_bit *pwm);

bool PWM_is_running(struct PWM_16_bit *pwm);

void PWM_start(struct PWM_16_bit *pwm);
void PWM_stop(struct PWM_16_bit *pwm);

#endif
