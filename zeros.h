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
 * File: zeros.h
 * Author: Javinator9889
 * Comments: Utils for counting both trailing and leading zeros.
 * Revision history: v1.0
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef ZEROS_H
#define	ZEROS_H

#include <stdint.h>

#define REPEAT_2x(X) (X), (X)
#define REPEAT_4x(X) REPEAT_2x(X), REPEAT_2x(X)
#define REPEAT_8x(X) REPEAT_4x(X), REPEAT_4x(X)
#define REPEAT_16x(X) REPEAT_8x(X), REPEAT_8x(X)
#define REPEAT_32x(X) REPEAT_16x(X), REPEAT_16x(X)
#define REPEAT_64x(X) REPEAT_32x(X), REPEAT_32x(X)
#define REPEAT_128x(X) REPEAT_64x(X), REPEAT_64x(X)

extern const unsigned char clz_8b[256];

int_fast64_t clz(int_fast64_t x);
int_fast64_t ctz(int_fast64_t x);

#endif	/* ZEROS_H */

