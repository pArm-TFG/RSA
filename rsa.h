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
 * File: rsa.h
 * Author: Javinator9889
 * Comments: RSA header file which common types and functions
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
#ifndef RSA_H
#define	RSA_H

// Custom type definitions
#include <stdint.h>

/**
 * Prime number limits
 */
#define MIN_PRIME_NUMBER 12049ULL
#define MAX_PRIME_NUMBER 1299827ULL

typedef struct {
    /**
     * In RSA, 'n' stands for the module.
     */
    int_fast64_t n;
    
    /**
     * In RSA, 'phi' equals: (p - 1) * (q - 1)
     */
    int_fast64_t phi;
    
    /**
     * In RSA, 'e' stands for "exponent".
     */
    int_fast64_t e;
    
    /**
     * In RSA, 'd' is the private key.
     */
    int_fast64_t d;
} 
/**
 * Custom structure containing all the RSA required information.
 */
rsa_t;

/**
 * Generates new pseudo-random RSA keys. Those keys may be considered safe
 * as they are composed upon prime numbers but their length is very small
 * (32 bits).
 * 
 * @return rsa_t containing the new keys.
 */
rsa_t RSA_keygen(void);

/**
 * Encrypts the given message by using an already existing key.
 * 
 * @param msg - the message to be encrypted.
 * @param key - the key used to encrypt the message.
 * @return int_fast64_t representing the encrypted message.
 */
int_fast64_t RSA_encrypt(int_fast64_t msg, rsa_t *key);

/**
 * Decrypts the given message by using an already existing key.
 * 
 * @param text - the text to be decrypted.
 * @param key - the key used to decrypt the message.
 * @return int_fast64_t representing the decrypted message.
 */
int_fast64_t RSA_decrypt(int_fast64_t text, rsa_t *key);

/**
 * Digitally signs a given message by using the private key.
 * 
 * @param msg - the message to be signed.
 * @param key - the key used to sign the message.
 * @return int_fast64_t representing the signed message.
 */
int_fast64_t RSA_sign(int_fast64_t msg, rsa_t *key);

#endif	/* RSA_H */
