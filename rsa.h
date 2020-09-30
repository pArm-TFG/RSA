/* Microchip Technology Inc. and its subsidiaries.  You may use this software 
 * and any derivatives exclusively with Microchip products. 
 * 
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS".  NO WARRANTIES, WHETHER 
 * EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED 
 * WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A 
 * PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION 
 * WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION. 
 *
 * IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
 * INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
 * WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS 
 * BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE 
 * FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS 
 * IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF 
 * ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 * MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE 
 * TERMS. 
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
    int_fast64_t n;
    int_fast64_t phi;
    int_fast64_t e;
    int_fast64_t d;
} rsa_t;

rsa_t RSA_keygen(void);
int_fast64_t RSA_encrypt(int_fast64_t msg, rsa_t *key);
int_fast64_t RSA_decrypt(int_fast64_t text, rsa_t *key);
int_fast64_t RSA_sign(int_fast64_t msg, rsa_t *key);

#endif	/* RSA_H */
