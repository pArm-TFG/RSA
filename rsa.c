/* 
 * File: rsa.c
 * Author: Javinator9889
 * Comments: RSA file with necessary functions
 * Revision history: v1.0
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
#include "../utils/rand.h"
#include "rsa.h"


/*static uint64_t gcd(uint64_t a, uint64_t b) {
    uint64_t q, r1, r2, r;
    
    if (a > b) {
        r1 = a;
        r2 = b;
    } else {
        r1 = b;
        r2 = a;
    }
    
    while (r2 > 0) {
        q = r1 / r2;
        r = r1 - q * r2;
        r1 = r2;
        r2 = r;
    }
    
    return r1;
}*/

static const uint64_t e = (uint64_t) ((2 << 15) + 1ULL);

static uint64_t gcd(uint64_t u, uint64_t v) {
    uint64_t shift;
    if (u == 0ULL) return v;
    if (v == 0ULL) return u;
    
    shift = __builtin_ctzll(u | v);
    u >>= __builtin_ctzll(u);
    
    do {
        v >>= __builtin_ctzll(v);
        if (u > v) {
            uint64_t temp = v;
            v = u;
            u = temp;
        }
        v -= u;
    } while (v != 0ULL);
    
    return u << shift;
}

static inline bool check_valid_phi(uint64_t *phi) {
    return gcd(e, *phi) != 1ULL;
}

// Returns modulo inverse of a with respect 
// to m using extended Euclid Algorithm 
// Assumption: a and m are coprimes, i.e., 
// gcd(a, m) = 1 
static uint64_t mod_inverse(uint64_t a, uint64_t b) {
    uint64_t m0 = b;
    uint64_t x = 1;
    uint64_t y = 0;
    
    if (b == 1)
        return 0ULL;
    
    while (a > 1) {
        uint64_t quotient = (uint64_t) (a / b);
        uint64_t temp = b;
        
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

rsa_t RSA_keygen() {
    rsa_t ret = { 0ULL };
    uint32_t p;
    uint32_t q;
    
    do {
        p = (uint32_t) RAND(MIN_PRIME_NUMBER, MAX_PRIME_NUMBER);
    } while (p % 2 == 0 && p % e == 1);
    
    do {
        q = (uint32_t) RAND(MIN_PRIME_NUMBER, MAX_PRIME_NUMBER);
    } while (q % 2 == 0 && q % e == 1);
    
    ret.n = (p * q);
    ret.phi = (p - 1) * (q - 1);
    ret.d = mod_inverse(ret.e, ret.phi);
    
    return ret;
}
