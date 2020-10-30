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
 * File: rsa.c
 * Author: Javinator9889
 * Comments: RSA file with necessary functions
 * Revision history: v1.1
 */

/*******************************************************************************
    RSA Algorithm
    Reminder: ((m**e)**d) % n = m
    e: encryption, d: decryption
    Encryption: ciphertext = message**e	% n
    Decryption: (c**d == (m**e)**d == m )	% n

    RSA Key Generation
    p and q, two distrinct prime numbers
    n = pq
    fi is Euler's Totient Function
    fi(n) = fi(p) * fi(q) = (p - 1) * (q - 1) = n - (p + q - 1)

    chose e, the public key:
        - 1 < e < fi(n)
        - gcd(e, fi(n)) == 1 (i.e. e and fi(n) are coprime
    chose d, the private key:
        - d == e**-1 (mod fi(n))
        -> d is the modular multiplicative inverse of e (modulo(fi(n)))
 ******************************************************************************/

#include <stdint.h>
#include <stdbool.h>
#include <math.h>
#include "rand.h"
#include "zeros.h"
#include "rsa.h"
#include "primes.h"

static int_fast64_t gcd(int_fast64_t u, int_fast64_t v) {
    int_fast64_t shift;
    if (u == 0ULL)
        return v;
    if (v == 0ULL)
        return u;

    shift = ctz(u | v);
    u >>= ctz(u);

    do {
        v >>= ctz(v);
        if (u > v) {
            int_fast64_t temp = v;
            v = u;
            u = temp;
        }
        v -= u;
    } while (v != 0ULL);

    return u << shift;
}

// Returns modulo inverse of a with respect
// to m using extended Euclid Algorithm
// Assumption: a and m are coprimes, i.e.,
// gcd(a, m) = 1
static int_fast64_t mod_inverse(int_fast64_t a, int_fast64_t b) {
    int_fast64_t m0 = b;
    int_fast64_t x = 1;
    int_fast64_t y = 0;

    if (b == 1)
        return 0ULL;

    while (a > 1) {
        int_fast64_t quotient = (int_fast64_t) (a / b);
        int_fast64_t temp = b;

        b = a % b;
        a = temp;
        temp = y;

        y = x - quotient * y;
        x = temp;
    }

    if (x < 0)
        x += m0;

    return x;
}

static int_fast64_t right_to_left(
        int_fast64_t value,
        int_fast64_t exp,
        int_fast64_t mod) {
    int_fast64_t ret = 1ULL;

    if (mod == 1ULL)
        return 0ULL;

    value %= mod;

    while (exp > 0ULL) {
        if (exp % 2 == 1) {
            ret = (ret * value) % mod;
        }
        exp >>= 1;
        value = (value * value) % mod;
    }

    return ret;
}

static bool is_valid_key(rsa_t *key) {
    if (key->d <= 0LL) {
        return false;
    }

    static const char *test_msg = "RSATEST";
    static const int_fast8_t length = 8;
    bool keys_ok = true;
    int_fast64_t enc_msg[8] = {0LL};
    for (int_fast8_t i = 0; i < length; ++i) {
        enc_msg[i] = RSA_encrypt(test_msg[i], key);
    }

    for (int_fast8_t i = 0; (i < length) && (keys_ok == true); ++i) {
        char dec_char = RSA_decrypt(enc_msg[i], key);
        keys_ok = (dec_char == test_msg[i]);
    }

    return keys_ok;
}

rsa_t RSA_keygen() {
    rsa_t ret = {0LL};
    ret.e = 65537LL;
    int_fast64_t p;
    int_fast64_t q;
    int_fast64_t n;
    int_fast64_t phi;

    do {
        do {
            do {
                do {
                    p = RAND(MIN_PRIME_NUMBER, MAX_PRIME_NUMBER);
                } while (check_prime(p, 5) == false);
                do {
                    q = RAND(MIN_PRIME_NUMBER, MAX_PRIME_NUMBER);
                } while (check_prime(q, 5) == false);
            } while (gcd(p, q) != 1ULL);
            n = p * q;
            phi = (p - 1ULL) * (q - 1ULL);
        } while (gcd(ret.e, phi) != 1ULL);
        ret.n = n;
        ret.phi = phi;
        ret.d = mod_inverse(ret.e, ret.phi);
    } while (!is_valid_key(&ret));

    return ret;
}

inline int_fast64_t RSA_encrypt(int_fast64_t msg, rsa_t *key) {
    return right_to_left(msg, key->e, key->n);
}

inline int_fast64_t RSA_sign(int_fast64_t msg, rsa_t *key) {
    return RSA_decrypt(msg, key);
}

inline int_fast64_t RSA_decrypt(int_fast64_t text, rsa_t *key) {
    return right_to_left(text, key->d, key->n);
}
