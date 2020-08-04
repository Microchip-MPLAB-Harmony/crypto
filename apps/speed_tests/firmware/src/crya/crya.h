/*******************************************************************************
  Crypto Speed Test Source File

  Company:
    Microchip Technology Inc.

  File Name:
    crya.h

  Description:
 * Entry points for the CRYA functions.
 *   see also datasheet SAML11 Omega DS60001513
 *******************************************************************************
 */

//DOM-IGNORE-BEGIN
/*****************************************************************************
 Copyright (C) 2013-2020 Microchip Technology Inc. and its subsidiaries.

Microchip Technology Inc. and its subsidiaries.

Subject to your compliance with these terms, you may use Microchip software 
and any derivatives exclusively with Microchip products. It is your 
responsibility to comply with third party license terms applicable to your 
use of third party software (including open source software) that may 
accompany Microchip software.

THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED 
WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A PARTICULAR 
PURPOSE.

IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS 
BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE 
FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN 
ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY, 
THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
*****************************************************************************/

//DOM-IGNORE-END

#ifndef CRYA_H
#define	CRYA_H

#ifdef	__cplusplus
extern "C" {
#endif

// All CRYA data blocks must be 4-byte aligned
// #define CRYA_ALIGN __align(4) // <<-- this way per CCI, but broken
#define CRYA_ALIGN __attribute__((aligned(4)))
// e.g. CRYA_ALIGN uint8_t key[16];
    
void crya_test_aes(void);
void crya_test_sha1(void);
void crya_test_all(void);

int crya_sha256(uint32_t hash[8], const uint8_t * data, const size_t length);
void crya_sha224(uint32_t hash[8], const uint8_t * data, const size_t length);
void crya_aes128_encrypt
    (const uint8_t *keys, uint32_t key_len, const uint8_t *src, uint8_t *dst);
void crya_aes128_decrypt
    (const uint8_t *keys, uint32_t key_len, const uint8_t *src, uint8_t *dst);

#ifdef	__cplusplus
}
#endif

#endif	/* CRYA_H */

