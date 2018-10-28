// GPIO.h
// Hotwire Controller Project
// Written by Robert Leonard

#ifndef _GPIO_LIB_
#define _GPIO_LIB_

#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>

void GPIO_toggle(uint8_t *port, uint8_t position);
void GPIO_blink(uint8_t *port, uint8_t position);
void GPIO_on(uint8_t *port, uint8_t position);
void GPIO_off(uint8_t *port, uint8_t position);

#endif
