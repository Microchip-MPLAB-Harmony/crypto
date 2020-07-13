/* cryptoSTV_wolfSSL_aes_cfb.c

  Crypto Speed Test Data File

  Company:
    Microchip Technology Inc.

  Description:
   This package transliterates test data from the wolfSSL test.c file,
   specifically the data for the AES/CFB tests.
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

#include <stddef.h>
#include <stdint.h>
#include "./cryptoSpeedTestData.h"
#include "cryptoST/cryptoSTE_print.h" // for BASE_LINE
#ifdef HAVE_CONFIG_H
    #include <config.h>
#endif

#define CONST /* as nothing */
#define ALIGN4 __attribute__((aligned(4)))

#if defined(WOLFSSL_AES_128) \
 || defined(WOLFSSL_AES_192) \
 || defined(WOLFSSL_AES_256)
static const cryptoST_testVector_t test_vector =
{
    .name = "AES_CFB",
    .source = "/wolfssl/wolfcrypt/test/test.c line 5447",
    // .description =  NULL,
    .vector.data = (ALIGN4 const uint8_t[]){
        0x6b,0xc1,0xbe,0xe2,0x2e,0x40,0x9f,0x96,
        0xe9,0x3d,0x7e,0x11,0x73,0x93,0x17,0x2a,
        0xae,0x2d,0x8a,0x57,0x1e,0x03,0xac,0x9c,
        0x9e,0xb7,0x6f,0xac,0x45,0xaf,0x8e,0x51,
        0x30,0xc8,0x1c,0x46,0xa3,0x5c,0xe4,0x11,
        0xe5,0xfb,0xc1,0x19,0x1a,0x0a,0x52,0xef,
        0xf6,0x9f,0x24,0x45,0xdf,0x4f,0x9b,0x17,
        0xad,0x2b,0x41,0x7b,0xe6,0x6c,0x37,0x10
    },
    .vector.length = 64,
};
#endif

static const cryptoST_testDetail_t test_item[] =
{
    // Keys and results for AES CFB 128, 192, 256
#if defined(WOLFSSL_AES_128)
    {
        .technique = ET_AES_128,
        .mode = EM_CFB,
        .recommendedRepetitions = 1000,

        .source = __BASE_FILE__ "(" BASE_LINE ")",
        .pedigree = "/wolfssl/wolfcrypt/test/test.c line 5464",
        .rawData = &test_vector,
        .io.sym.out.cipher = {
            .length = 48,
            .data = (ALIGN4 const uint8_t[]){
                0x3b,0x3f,0xd9,0x2e,0xb7,0x2d,0xad,0x20,
                0x33,0x34,0x49,0xf8,0xe8,0x3c,0xfb,0x4a,
                0xc8,0xa6,0x45,0x37,0xa0,0xb3,0xa9,0x3f,
                0xcd,0xe3,0xcd,0xad,0x9f,0x1c,0xe5,0x8b,
                0x26,0x75,0x1f,0x67,0xa3,0xcb,0xb1,0x40,
                0xb1,0x80,0x8c,0xf1,0x87,0xa4,0xf4,0xdf
            }
        },
        .io.sym.in.key = {
            .length = AES128_KEY_SIZE/8,
            .data = (ALIGN4 const uint8_t[]){
            0x2b,0x7e,0x15,0x16,0x28,0xae,0xd2,0xa6,
            0xab,0xf7,0x15,0x88,0x09,0xcf,0x4f,0x3c
            }
        },
        .io.sym.in.ivNonce = {
            .length = 16,
            .data = (ALIGN4 const uint8_t[]){
                0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,
                0x08,0x09,0x0a,0x0b,0x0c,0x0d,0x0e,0x0f
            }
        },
    },
#endif
#if defined(WOLFSSL_AES_192)
    {
        .technique = ET_AES_192,
        .mode = EM_CFB,
        .recommendedRepetitions = 1000,

        .source = __BASE_FILE__ "(" BASE_LINE ")",
        .pedigree = "/wolfssl/wolfcrypt/test/test.c line 5447",
        .rawData = &test_vector,
        .io.sym.out.cipher = {
            .length = 64,
            .data = (ALIGN4 const uint8_t[]){
                0xcd,0xc8,0x0d,0x6f,0xdd,0xf1,0x8c,0xab,
                0x34,0xc2,0x59,0x09,0xc9,0x9a,0x41,0x74,
                0x67,0xce,0x7f,0x7f,0x81,0x17,0x36,0x21,
                0x96,0x1a,0x2b,0x70,0x17,0x1d,0x3d,0x7a,
                0x2e,0x1e,0x8a,0x1d,0xd5,0x9b,0x88,0xb1,
                0xc8,0xe6,0x0f,0xed,0x1e,0xfa,0xc4,0xc9,
                0xc0,0x5f,0x9f,0x9c,0xa9,0x83,0x4f,0xa0,
                0x42,0xae,0x8f,0xba,0x58,0x4b,0x09,0xff
            }
        },
        .io.sym.in.key = {
            .length = AES192_KEY_SIZE/8,
            .data = (ALIGN4 const uint8_t[]){ 
                0x8e,0x73,0xb0,0xf7,0xda,0x0e,0x64,0x52,
                0xc8,0x10,0xf3,0x2b,0x80,0x90,0x79,0xe5,
                0x62,0xf8,0xea,0xd2,0x52,0x2c,0x6b,0x7b }
            },
        .io.sym.in.ivNonce = {
            .length = 16,
            .data = (ALIGN4 const uint8_t[]){
                0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,
                0x08,0x09,0x0a,0x0b,0x0c,0x0d,0x0e,0x0f
            },
        }
    },
#endif
#if defined(WOLFSSL_AES_256)
    {
        .technique = ET_AES_256,
        .mode = EM_CFB,
        .recommendedRepetitions = 1000,

        .source = __BASE_FILE__ "(" BASE_LINE ")",
        .pedigree = "/wolfssl/wolfcrypt/test/test.c line 5526",
        .rawData = &test_vector,
        .io.sym.out.cipher = {
            .length = 64,
            .data = (ALIGN4 const uint8_t[]){
                0xdc,0x7e,0x84,0xbf,0xda,0x79,0x16,0x4b,
                0x7e,0xcd,0x84,0x86,0x98,0x5d,0x38,0x60,
                0x39,0xff,0xed,0x14,0x3b,0x28,0xb1,0xc8,
                0x32,0x11,0x3c,0x63,0x31,0xe5,0x40,0x7b,
                0xdf,0x10,0x13,0x24,0x15,0xe5,0x4b,0x92,
                0xa1,0x3e,0xd0,0xa8,0x26,0x7a,0xe2,0xf9,
                0x75,0xa3,0x85,0x74,0x1a,0xb9,0xce,0xf8,
                0x20,0x31,0x62,0x3d,0x55,0xb1,0xe4,0x71
            }
        },
        .io.sym.in.key = {
            .length = AES256_KEY_SIZE/8,
            .data = (ALIGN4 const uint8_t[]){
                0x60,0x3d,0xeb,0x10,0x15,0xca,0x71,0xbe,
                0x2b,0x73,0xae,0xf0,0x85,0x7d,0x77,0x81,
                0x1f,0x35,0x2c,0x07,0x3b,0x61,0x08,0xd7,
                0x2d,0x98,0x10,0xa3,0x09,0x14,0xdf,0xf4
            },
        },
        .io.sym.in.ivNonce = {
            .length = 16,
            .data = (ALIGN4 const uint8_t[]){
                0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,
                0x08,0x09,0x0a,0x0b,0x0c,0x0d,0x0e,0x0f
            },
        }
    },
#endif
    {}
};
#define test_item_count (sizeof(test_item)/sizeof(cryptoST_testDetail_t))

/*************************************************************
 * API handlers
 *************************************************************/
static const cryptoST_testDetail_t * firstTest(void)
{
    return test_item;
}
static const cryptoST_testDetail_t * nextTest(const cryptoST_testDetail_t * old)
{
    // Assume that if its in range, that it is legitimate.
    if (old < test_item) 
        return NULL;
    old++; // repurpose: this is now "new"
    
    // We know that the final (illegitimate) entry has a null name,
    // but we still need to check if "old" is _way_ out of bounds.
    if ((old >= &test_item[test_item_count])
            || (ET_NONE == old->technique))
        return NULL;
    return old;
}

/*************************************************************
 * Declaration of the test manager API
 * Obligatory entry points for executing a test
 *************************************************************/
#include "cryptoSTD_wolfSSL_aes_cfb.h"
cryptoST_testAPI_t const wolfSSL_aes_cfb =
{
    .name = "AES_CFB",
    .openData = NULL,
    .firstTest = firstTest,
    .nextTest = nextTest,
    .closeData = NULL,
};

