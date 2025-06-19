#ifndef FSM_H
#define FSM_H

#include "globals.h"

enum FSMState {
    FSM_DHT20,
    FSM_SOIL_LIGHT,
    FSM_DISTANCE,
};

void initFSM();
#endif