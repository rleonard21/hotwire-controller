#include "gpio.h"

void GPIO_blink(uint8_t *port, uint8_t position) {
    while(1) {
        *port ^= _BV(position);
        _delay_ms(100);
    }
}

void GPIO_toggle(uint8_t *port, uint8_t position) {
    *port ^= _BV(position);
}

void GPIO_on(uint8_t *port, uint8_t position) {
    *port |= _BV(position);
}

void GPIO_off(uint8_t *port, uint8_t position) {
    *port &= ~_BV(position);
}
