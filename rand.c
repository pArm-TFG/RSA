/* 
 * File: rand.c
 * Author: Javinator9889
 * Comments: Generate random numbers using the elapsed time in ns.
 * Revision history: v1.0
 */

#include <xc.h>
#include <stdint.h>
#include <stdbool.h>
#include <p33EP512GM604.h>
#include "rand.h"

static volatile time_t _ns;
// Package utils/time.h
extern time_t TIME_now_us(void);
static bool _rand_init = false;

void RAND_init_seed(void) {
    srand(TIME_now_us());
    _rand_init = true;
}

void RAND_stop(void) {
    T6CONbits.TON = 0;
    _ns = 0ULL;
    _rand_init = false;
}

int_fast64_t RAND(int_fast64_t min, int_fast64_t max) {
    if (!_rand_init)
        return 0ULL;
    return (int_fast64_t) (min + ((int_fast64_t) rand()) /
            (((int_fast64_t) RAND_MAX) / (max - min + 1LL) + 1LL));
}

inline int RAND_random(void) {
    if (!_rand_init)
        return 0;
    return rand();
}