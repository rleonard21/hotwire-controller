// LED.h
// Hotwire Controller Project
// Written by Robert Leonard

#ifndef _LED_LIB_
#define _LED_LIB_

#include <avr/io.h>

struct LED {
    uint16_t *reg;
    char position;
};

void LED_blink(struct LED, int delay);
void LED_toggle(struct LED);
void LED_set(struct LED, bool value);

static void LED_delay(uint16_t milliseconds);

#endif
