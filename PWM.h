// PWM.h
// Hotwire Controller Project
// Written by Robert Leonard

#ifndef _PWM_LIB_
#define _PWM_LIB_

#include <stdint.h>

struct PWM {

};

void PWM_init(PWM *pwm);
void PWM_set(PWM *pwm, uint16_t counter);
void PWM_start(PWM *pwm);
void PWM_stop(PWM *pwm);

#endif
