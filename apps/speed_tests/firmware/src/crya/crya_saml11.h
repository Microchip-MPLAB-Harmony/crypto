/* 
 * File:   crya_saml11.h
 * Author: C14102
 *
 * Created on January 7, 2020, 9:40 AM
 * 
 * Entry points for the CRYA functions.
 *   SAML11 Omega DS60001513
 * 
 */

#ifndef CRYA_SAML11_H
#define	CRYA_SAML11_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <stdint.h>
    
/* Requirements:
   1. Only callable from Secure execution environment
   2. All pointers are 32b aligned (4-byte alignment)
   3. Entry-point names are taken from the data sheet,
      but with bit-counts noted to future-proof the names
*/
// FIPS Publication 180-4
typedef void (*crya_sha256_process_t)
    (uint32_t hash_in_out[8], const uint8_t data[64], uint32_t ram_buf[64]);
#define secure_crya_sha256_process ((crya_sha256_process_t ) (0x02001900 | 0x1))
 
// FIPS Publication 197 -- key must be 128b (16B)
typedef void (*crya_aes128_encrypt_t)
    (const uint8_t *keys, uint32_t key_len, const uint8_t *src, uint8_t *dst);
typedef void (*crya_aes128_decrypt_t)
    (const uint8_t *keys, uint32_t key_len, const uint8_t *src, uint8_t *dst);
#define secure_crya_aes128_encrypt ((crya_aes128_encrypt_t ) (0x02001904 | 0x1))
#define secure_crya_aes128_decrypt ((crya_aes128_decrypt_t ) (0x02001908 | 0x1))
 
// NIST Special Publication 800-38D -- GCM mode inner loop
typedef void (*crya_gf_mult128_t)
    (const uint32_t *block1, const uint32_t *block2, uint32_t *dst);
#define secure_crya_gf_mult128 ((crya_gf_mult128_t ) (0x0200190C | 0x1))


#ifdef	__cplusplus
}
#endif

#endif	/* CRYA_SAML11_H */

