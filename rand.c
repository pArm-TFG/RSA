/*
 * Copyright (C) 2020 - present | pArm-S2 by Javinator9889
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see https://www.gnu.org/licenses/.
 *
 * Created by Javinator9889 on 2020 - pArm-S1.
 */

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

void RAND_init(void) {
    _ns = 0ULL;
    //TMR6 0; 
    TMR6 = 0x00;
    //Period = 0.000000217 s; Frequency = 59904000 Hz; PR6 12; 
    PR6 = 0x0C;
    //TCKPS 1:1; T32 16 Bit; TON enabled; TSIDL disabled; TCS FOSC/2; TGATE disabled; 
    T6CON = 0x8000;
    // Enable interrupt
    IFS2bits.T6IF = 0;
    IEC2bits.T6IE = 1;
}

void RAND_init_seed(void) {
    srand(_ns);
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

void __attribute__((interrupt, no_auto_psv)) _T6Interrupt(void) {
    _ns += 217ULL;
    IFS2bits.T6IF = 0;
}