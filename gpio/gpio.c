#include "gpio.h"

// MODIFIES: Modifies the underlying DDRx port.
// EFFECTS:  Sets the position of the DDRx port to input or output according
// 			 to page 101 of the 328P datasheet.
void GPIO_init(volatile uint8_t *ddr, volatile uint8_t *port, uint8_t position, uint8_t type) {
	switch(type) {
		case OUTPUT_SINK:
			*ddr |= _BV(position);
			*port &= ~_BV(position);
			break;

		case OUTPUT_SOURCE:
			*ddr |= _BV(position);
			*port |= _BV(position);
			break;

		case INPUT:
			*ddr &= ~_BV(position);
			*port |= _BV(position);
			// need to set PUD to zero.
			break;

		case INPUT_PULLUP:
			*ddr &= ~_BV(position);
			*port |= _BV(position);
			// need to set PUD to one.
			break;

			default:
			break;
	}
}


// MODIFIES: Modifies the underlying PORTx.
// EFFECTS:  Generates an infinite blink signal on the GPIO.
void GPIO_blink(volatile uint8_t *port, uint8_t position, uint8_t interval) {
	while (1) {
		*port ^= _BV(position);
		delay(interval);
	}
}


// MODIFIES: Modifies the underlying PORTx.
// EFFECTS:  Toggles the position bit on PORTx.
void GPIO_toggle(volatile uint8_t *port, uint8_t position) {
	*port ^= _BV(position);
}


// MODIFIES: Modifies the underlying PORTx.
// EFFECTS:  Writes a 1 at the position bit on PORTx.
void GPIO_on(volatile uint8_t *port, uint8_t position) {
	*port |= _BV(position);
}


// MODIFIES: Modifies the underlying PORTx.
// EFFECTS:  Writes a 0 at the position bit on PORTx.
void GPIO_off(volatile uint8_t *port, uint8_t position) {
	*port &= ~_BV(position);
}


// EFFECTS:  A simple obstructive delay implementation.
static void delay(uint16_t interval) {
	while(interval--) _delay_ms(1);
}