// PID.h
// Created by Robert Leonard on 10/27/19.
//

#ifndef HOTWIRE_CONTROLLER_V1_1_PID_H
#define HOTWIRE_CONTROLLER_V1_1_PID_H

#include <stdint.h>

volatile int pid_num_ticks;
volatile int pid_max_ticks;

// EFFECTS: updates the PID loop
void PID_update_service();

#endif //HOTWIRE_CONTROLLER_V1_1_PID_H
