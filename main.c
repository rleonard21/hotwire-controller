// main.c
// Written by Robert Leonard

#include <avr/io.h>
#include <util/delay.h>

#include "Hotwire.h"

int main(void) {
	Hotwire_init();
	Hotwire_set(90);
	Hotwire_start();

	while(1);
}
