// StringUtility.h
// Created by Robert Leonard on 2019-07-04.
//

#ifndef HOTWIRE_CONTROLLER_V1_1_STRINGUTILITY_H
#define HOTWIRE_CONTROLLER_V1_1_STRINGUTILITY_H

#include <stdint.h>

// NOTE: All functions assume strings <= 18 characters long (16 + newline + null)

// EFFECTS: merges two strings to one 16 character wide string
//          adds space padding in the middle.
void StringUtility_fit_16(char *str1, char *str2, char *str_out);

// EFFECTS: takes a number and converts to a 3 digit string
//          adds leading zeros as necessary
void StringUtility_digit_to_string(char *str, uint8_t number);

#endif //HOTWIRE_CONTROLLER_V1_1_STRINGUTILITY_H
