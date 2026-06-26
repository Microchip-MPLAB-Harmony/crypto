/* 
  Crypto Framework Library Source

  Company:
    Microchip Technology Inc.

  File Name:
    crypt_crya_saml11.h

  Summary:
    Crypto Framework Library interface file for CRYA hardware in SAML11

  Description:
    This file contains the interface that is required when using the
    AES and SHA accelerators in SAML11CM'SA as described in DS60001513.
 */

//DOM-IGNORE-BEGIN
/*
Copyright (C) 2013-2026, Microchip Technology Inc., and its subsidiaries. All rights reserved.

The software and documentation is provided by microchip and its contributors
"as is" and any express, implied or statutory warranties, including, but not
limited to, the implied warranties of merchantability, fitness for a particular
purpose and non-infringement of third party intellectual property rights are
disclaimed to the fullest extent permitted by law. In no event shall microchip
or its contributors be liable for any direct, indirect, incidental, special,
exemplary, or consequential damages (including, but not limited to, procurement
of substitute goods or services; loss of use, data, or profits; or business
interruption) however caused and on any theory of liability, whether in contract,
strict liability, or tort (including negligence or otherwise) arising in any way
out of the use of the software and documentation, even if advised of the
possibility of such damage.

Except as expressly permitted hereunder and subject to the applicable license terms
for any third-party software incorporated in the software and any applicable open
source software license terms, no license or other rights, whether express or
implied, are granted under any patent or other intellectual property rights of
Microchip or any third party.
*/

//DOM-IGNORE-END

#ifndef CRYPTO_CRYA_SAML11_H
#define	CRYPTO_CRYA_SAML11_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <stdint.h>
    
/* Requirements:
   1. Only callable from Secure execution environment
   2. All pointers are 32b aligned (4-byte alignment)
   3. Entry-point names are derived from the data sheet,
      but with bit-counts noted to future-proof the names
*/
// FIPS Publication 180-4
typedef void (*crya_sha256_process_t)
    (uint32_t hash_in_out[8], const uint8_t data[64], uint32_t ram_buf[64]);
#define secure_crya_sha256_process_hw ((crya_sha256_process_t ) (0x02001900 | 0x1))
 
// FIPS Publication 197 -- key must be 128b (16B)
typedef void (*crya_aes128_encrypt_t)
    (const uint8_t *keys, uint32_t key_len, const uint8_t *src, uint8_t *dst);
typedef void (*crya_aes128_decrypt_t)
    (const uint8_t *keys, uint32_t key_len, const uint8_t *src, uint8_t *dst);
#define secure_crya_aes128_encrypt_hw ((crya_aes128_encrypt_t ) (0x02001904 | 0x1))
#define secure_crya_aes128_decrypt_hw ((crya_aes128_decrypt_t ) (0x02001908 | 0x1))
 
// NIST Special Publication 800-38D -- GCM mode inner loop
typedef void (*crya_gf_mult128_t)
    (const uint32_t *block1, const uint32_t *block2, uint32_t *dst);
#define secure_crya_gf_mult128_hw ((crya_gf_mult128_t ) (0x0200190C | 0x1))


#ifdef	__cplusplus
}
#endif

#endif	/* CRYPTO_CRYA_SAML11_H */

