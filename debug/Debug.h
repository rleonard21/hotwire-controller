// Debug.h
// Created by Robert Leonard on 10/28/19.
//

#ifndef HOTWIRE_CONTROLLER_V1_1_DEBUG_H
#define HOTWIRE_CONTROLLER_V1_1_DEBUG_H

#include <stdint.h>

#define DEBUG_ADDR (0x7F)

#define NO_DEBUG

void debug_write(uint8_t reg, int16_t value);

#endif //HOTWIRE_CONTROLLER_V1_1_DEBUG_H
