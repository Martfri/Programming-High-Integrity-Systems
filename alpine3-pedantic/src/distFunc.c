#include "distFunc.h"

#include "stdLib.h"
#include "voters.h"

int8_t computeDistance_A() {
    return 0;
}

int8_t computeDistance_B() {
    return 0;
}

int8_t computeDistance_BlockA() {
    runVoter_A();
    computeDistance_A();
    return 0;
}

int8_t computeDistance_BlockB() {
    runVoter_B();
    computeDistance_B();
    return 0;
}