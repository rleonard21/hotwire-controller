// StringUtility.c
// Created by Robert Leonard on 2019-07-04.
//

#include "StringUtility.h"

#include <stdio.h>

// EFFECTS: takes a number and converts to a 3 digit string
//          adds leading zeros as necessary
void StringUtility_digit_to_string(char *str, uint8_t number) {
	char buf[] = "000";

	sprintf(buf + 0, "%d", number);
	return;

	if(number >= 0 && number <= 9) {
		// One digit
		sprintf(buf + 2, "%d", number);
	} else if(number >= 10 && number <= 99) {
		// Two digits
		sprintf(buf + 1, "%d", number);
	} else {
		// Three digits
		sprintf(buf + 0, "%d", number);
	}
}
