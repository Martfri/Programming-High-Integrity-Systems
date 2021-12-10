#ifndef VOTERS_H
#define VOTERS_H
#include <stdint.h>

#include "sensors.h"

returnType_en runVoter_A(sensor_t sensorReadings[], int32_t *bestValue);
returnType_en runVoter_B(sensor_t sensorReadings[]);
returnType_en runStage2Voter();
#endif