#ifndef VOTERS_H
#define VOTERS_H
#include <stdint.h>

#include "sensors.h"

int8_t runVoter_A(sensor_t sensorReadings[]);
int8_t runVoter_B(sensor_t sensorReadings[]);
int8_t runStage2Voter();
#endif