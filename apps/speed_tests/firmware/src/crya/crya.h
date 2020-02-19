/* 
 * File:   crya.h
 * Author: C14102
 *
 * Created on January 7, 2020
 */

#ifndef CRYA_H
#define	CRYA_H

#ifdef	__cplusplus
extern "C" {
#endif

// All CRYA data blocks must be 4-byte aligned
// #define CRYA_ALIGN __align(4) // <<-- this way per CCI, but broken
#define CRYA_ALIGN __attribute__((aligned(4)))
// e.g. CRYA_ALIGN uint8_t key[16];
    
void crya_test_aes();
void crya_test_sha1();
void crya_test_all();

void crya_sha256(uint32_t hash[8], const uint8_t * data, const size_t length);
void crya_sha224(uint32_t hash[8], const uint8_t * data, const size_t length);
void crya_aes128_encrypt
    (const uint8_t *keys, uint32_t key_len, const uint8_t *src, uint8_t *dst);
void crya_aes128_decrypt
    (const uint8_t *keys, uint32_t key_len, const uint8_t *src, uint8_t *dst);

#ifdef	__cplusplus
}
#endif

#endif	/* CRYA_H */

