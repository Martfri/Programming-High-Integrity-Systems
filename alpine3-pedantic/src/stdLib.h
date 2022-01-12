/**
 * @file stdLib.h
 * @brief Implementats standard datatype for the whole project.
 *
 * @note
 */
#ifndef STDLIB_H
#define STDLIB_H

#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#ifndef STDINT_H
#define STDINT_H
/*
    Header file 'FileName' repeatedly included but does not have a
    standard include guard  -- The file named in the message has
    already been included in the current module.  Moreover it has
    been determined that this header does not have a standard include
    guard.*/
#include <stdint.h>  //lint !e537 !e451
#endif

/**
 * @brief Enables debug mode
 */
#ifndef TEST
#define DEBUG
#endif

/**
 * @brief returnType enumeration
 *
 */
typedef enum {
    E_OK = 0,
    E_NOT_OK = 1
} returnType_en;
#endif
