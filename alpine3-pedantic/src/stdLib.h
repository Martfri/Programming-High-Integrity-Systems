#ifndef STDLIB_H
#define STDLIB_H

#include <pthread.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef enum {
    E_ERROR = -1,
    E_OK = 0,
    E_NOT_OK = 1
} returnType_en;
#endif