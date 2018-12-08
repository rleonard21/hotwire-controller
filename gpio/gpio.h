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

#define OUTPUT_SINK 	0
#define OUTPUT_SOURCE 	1
#define INPUT			2
#define INPUT_PULLUP 	3

// MODIFIES: Modifies the underlying DDRx port.
// EFFECTS:  Sets the position of the DDRx port to input or output according
// 			 to page 101 of the 328P datasheet.
void GPIO_init(volatile uint8_t *ddr, volatile uint8_t *port, uint8_t position, uint8_t type);


// MODIFIES: Modifies the underlying PORTx.
// EFFECTS:  Generates an infinite blink signal on the GPIO.
void GPIO_blink(volatile uint8_t *port, uint8_t position, uint8_t interval);


// MODIFIES: Modifies the underlying PORTx.
// EFFECTS:  Toggles the position bit on PORTx.
void GPIO_toggle(volatile uint8_t *port, uint8_t position);


// MODIFIES: Modifies the underlying PORTx.
// EFFECTS:  Writes a 1 at the position bit on PORTx.
void GPIO_on(volatile uint8_t *port, uint8_t position);


// MODIFIES: Modifies the underlying PORTx.
// EFFECTS:  Writes a 0 at the position bit on PORTx.
void GPIO_off(volatile uint8_t *port, uint8_t position);


// EFFECTS:  A simple obstructive delay implementation.
static void delay(uint16_t interval);

#endif
