#include <stdint.h>
#include <stdbool.h>
#include "primes.h"
#include "../utils/rand.h"

/* 
 * calculates (a * b) % c taking into account that a * b might overflow 
 */
static int_fast64_t mulmod(int_fast64_t a, int_fast64_t b, int_fast64_t mod) {
    int_fast64_t x = 0;
    int_fast64_t y = a % mod;
    
    while (b > 0) {
        if (b % 2 == 1) {
            x = (x + y) % mod;
        }
        y = (y * 2) % mod;
        b /= 2;
    }
    return x % mod;
}

/* 
 * modular exponentiation
 */
static int_fast64_t modulus(int_fast64_t b, int_fast64_t exp, int_fast64_t mod) {
    int_fast64_t x = 1;
    int_fast64_t y = b;
    while (exp > 0) {
        if (exp % 2 == 1)
            x = (x * y) % mod;
        y = (y * y) % mod;
        exp /= 2;
    }
    return x % mod;
}

/*
 * Miller-Rabin Primality test, trials signifies the accuracy
 */
bool check_prime(int_fast64_t p, uint_fast16_t trials) {
    uint_fast16_t i;
    int_fast64_t s;
    if (p < 2) {
        return false;
    }
    if (p != 2 && p % 2 == 0) {
        return false;
    }
    s = p - 1;
    while (s % 2 == 0) {
        s /= 2;
    }
    for (i = 0UL; i < trials; i += 1UL) {
        int_fast64_t a = rand() % (p - 1) + 1, temp = s;
        int_fast64_t mod = modulus(a, temp, p);
        while (temp != p - 1 && mod != 1 && mod != p - 1) {
            mod = mulmod(mod, mod, p);
            temp *= 2;
        }
        if ((mod != p - 1) && temp % 2 == 0) {
            return false;
        }
    }
    return true;
}
