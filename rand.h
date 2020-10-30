/*
 * 2020 | pArm-S2 by Javinator9889
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
 * File: rand.h
 * Author: Javinator9889
 * Comments: Generate random numbers using the elapsed time in ns.
 * Revision history: v1.0
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef RAND_H
#define	RAND_H

#include <stdlib.h>
#include <stdint.h>

#ifndef time_t
typedef uint64_t time_t;
#define time_t time_t
#endif

/**
 * Initializes the pseudo-random number generator machine. Must be called
 * before any other function in this class.
 */
void RAND_init(void);

/**
 * Initializes a new random seed. Useful for generating non-deterministic
 * pseudo-random numbers.
 */
void RAND_init_seed(void);

/**
 * Stops the pseudo-random machine.
 */
void RAND_stop(void);

/**
 * Generates a pseudo-random number in between the given range.
 * 
 * @param min - the minimum number allowed to be generated.
 * @param max - the maximum number allowed to be generated.
 * @return the pseudo-random value.
 */
int_fast64_t RAND(int_fast64_t min, int_fast64_t max);

/**
 * Generates a simple pseudo-random number.
 * 
 * @return the pseudo-random value.
 */
int RAND_random(void);

/**
 * Pseudo-random machine custom generator.
 */
void __attribute__((interrupt, no_auto_psv)) _T6Interrupt(void);

#endif	/* RAND_H */

