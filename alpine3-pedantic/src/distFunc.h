#ifndef DIST_FUNC_H
#define DIST_FUNC_H
#include <stdint.h>

#include "sensors.h"

int8_t computeDistance_BlockA(sensor_t sensorReadings[]);
int8_t computeDistance_BlockB(sensor_t sensorReadings[]);
#endif