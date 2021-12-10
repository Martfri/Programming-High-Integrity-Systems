#ifndef DIST_FUNC_H
#define DIST_FUNC_H
#include <stdint.h>

#include "sensors.h"

returnType_en computeDistance_BlockA(sensor_t sensorReadings[], uint32_t* distance);
returnType_en computeDistance_BlockB(sensor_t sensorReadings[]);
#endif