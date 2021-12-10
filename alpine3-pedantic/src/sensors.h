#ifndef SENSORS_H
#define SENSORS_H

#include <stdint.h>

#include "stdLib.h"
#define NR_OF_SENSORS 3

typedef enum {
    SENSOR_OK = 0,
    SENSOR_NOK
} sensorState_en;

typedef struct sensor_t {
    sensorState_en state;
    uint32_t reading;
} sensor_t;

returnType_en readSensors(sensor_t sensorReadings[]);
#endif