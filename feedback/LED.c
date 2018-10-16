#include "LED.h"

void LED_init(struct LED, unsigned char *reg, unsigned char position) {
    LED->reg = reg;
    LED->position = position;
}

void LED_blink(struct LED, int delay) {
    while(1) { // obstructive blink function for debug purposes
        LED_toggle(LED);
        delay(delay);
    }
}

void LED_toggle(struct LED) {
    *LED->reg ^= _BV(LED->position);
}

void LED_on(struct LED) {
    *LED->reg |= _BV(LED->position);
}

void LED_off(struct LED) {
    *LED->reg &= ~_BV(LED->position);
}

static void LED_delay(uint16_t milliseconds) {
    while(n--) {
        _delay_ms(1);
    }
}
