#include "LED.h"

void LED_blink(struct LED, int delay) {
    while(1) {
        LED_toggle(LED);
        delay(delay);
    }
}

void LED_toggle(struct LED) {
    bool pinValue; // change to reading the register

    LED_set(LED, !pinValue);
}

void LED_set(struct LED, bool value) {
    *LED->reg |= _BV(value);
}

static void LED_delay(uint16_t milliseconds) {
    while(n--) {
        _delay_ms(1);
    }
}
