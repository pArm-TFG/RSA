/*
 * File:   rsa2.c
 * Author: javinator9889
 *
 * Created on August 31, 2020, 11:49 AM
 */
#include <math.h>
#include "../utils/rand.h"

#define MIN_PRIME_NUMBER 104395301ULL
#define MAX_PRIME_NUMBER 982451653ULL
#define E                ((2 << 15) + 1)

char check_prime(int number) {
    int n = number - 1;
    int k = 0;
    int j, m, T;

    while (n % 2 == 0) {
        k++;
        n = n / 2;
    }

    m = n;
    T = find_t(2, m, number);

    if (T == 1 || T == number - 1)
        return 1;

    for (j = 0; j < k; j++) {
        T = find_t(T, 2, number);
        if (T == 1)
            return 0;
        if (T == number - 1)
            return 1;
    }
    return 0;
}

int find_t(int a, int m, int n) {
    int r;
    int y = 1;

    while (m > 0) {
        r = m % 2;
        fast_exponentiation(r, n, &y, &a);
        m = m / 2;
    }
    return y;
}

void fast_exponentiation(int bit, int n, int* y, int* a) {
    if (bit == 1)
        *y = (*y * (*a)) % n;

    *a = (*a) * (*a) % n;
}

int gcd(int a, int b) {
    int q, r1, r2, r;

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
}

int inverse(int a, int b) {
    int inv;
    int q, r, r1 = a, r2 = b, t, t1 = 0, t2 = 1;

    while (r2 > 0) {
        q = r1 / r2;
        r = r1 - q * r2;
        r1 = r2;
        r2 = r;

        t = t1 - q * t2;
        t1 = t2;
        t2 = t;
    }

    if (r1 == 1)
        inv = t1;

    if (inv < 0)
        inv = inv + a;

    return inv;
}


void RSA_generate_pq(void) {
    uint64_t p, q, n, phi_n, e, d;
    
    do {
        do {
            p = RAND(MIN_PRIME_NUMBER, MAX_PRIME_NUMBER);
        } while (p % 2 == 0);
    } while (!check_prime(p));
    
    do {
        do {
            q = RAND(MIN_PRIME_NUMBER, MAX_PRIME_NUMBER);
        } while (q % 2 == 0 && q == p);
    } while (!check_prime(q));
    
    n = p * q;
    phi_n = (p - 1) * (q - 1);
    
    e = E;
    
    do {
        e = (e + 1) % (phi_n - 1);
    } while (gcd(e, phi_n) != 1);
    
    d = inverse(phi_n, e);
}