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
 * File: zeros.c
 * Author: Javinator9889
 * Comments: Utils for counting both trailing and leading zeros.
 * Revision history: v1.0
 */
#include <stdint.h>
#include "zeros.h"

const unsigned char clz_8b[256] = {
    8,
    7,
    REPEAT_2x(6),
    REPEAT_4x(5),
    REPEAT_8x(4),
    REPEAT_16x(3),
    REPEAT_32x(2),
    REPEAT_64x(1),
    REPEAT_128x(0)
};

int_fast64_t clz(int_fast64_t x) {
    int_fast64_t b, ms_oct;

    if (x & 0xFFFFFFFF00000000U)
        if (x & 0xFFFF000000000000U)
            if (x & 0xFF00000000000000U)
                b = 0, ms_oct = x >> 56;
            else
                b = 8, ms_oct = x >> 48;
        else
            if (x & 0x0000FF0000000000U)
            b = 16, ms_oct = x >> 40;
        else
            b = 24, ms_oct = x >> 32;
    else
        if (x & 0x00000000FFFF0000U)
        if (x & 0x00000000FF000000U)
            b = 32, ms_oct = x >> 24;
        else
            b = 40, ms_oct = x >> 16;
    else
        if (x & 0x000000000000FF00U)
        b = 48, ms_oct = x >> 8;
    else
        b = 56, ms_oct = x >> 0;

    return b + clz_8b[ms_oct];
}

int_fast64_t ctz(int_fast64_t x) {
    x &= -x;
    return 63LL - clz(x);
}
