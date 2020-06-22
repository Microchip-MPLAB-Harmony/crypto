/* cryptoSTD_wolfSSL_aes_cbc

  Crypto Speed Test Data File

  Company:
    Microchip Technology Inc.

  Description:
   This package transliterates test data from the wolfSSL test.c file,
   specifically the data for the AES/CBC tests.
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
#ifdef HAVE_CONFIG_H
    #include <config.h>
#endif

#define CONST /* as nothing */
#define ALIGN4 __attribute__((aligned(4)))

#if defined(WOLFSSL_AES_128)
static const cryptoST_testVector_t NowIsTheTime =
{
    .name = "AES_CBC NITT",
    .source = "/wolfssl/wolfcrypt/test/test.c line 6335",
    // .description =  NULL,
    .vector.data = (uint8_t[]){ // test.c 6388
        /* "Now is the time for all " w/o trailing 0 */
        0x6e,0x6f,0x77,0x20,0x69,0x73,0x20,0x74,
        0x68,0x65,0x20,0x74,0x69,0x6d,0x65,0x20,
        0x66,0x6f,0x72,0x20,0x61,0x6c,0x6c,0x20
    },
    .vector.length = 16,
    /* Magic here: if length=24 the CBC encrypter will ignore the
     * final 8, and the decrypter will abort with error.
     * */
};

const CPU_CHAR NIST_800_38A_description[] = {
        "test vectors from "
        "\"Recommendation for Block Cipher Modes of Operation\" "
        "NIST Special Publication 800-38A" };
static const cryptoST_testVector_t Message2 =
{
    .name = "AES_CBC MSG2",
    .source = "/wolfssl/wolfcrypt/test/test.c line 6335",
    .description = NIST_800_38A_description,
    .vector.data = (uint8_t[]){
        0x6b, 0xc1, 0xbe, 0xe2, 0x2e, 0x40, 0x9f, 0x96,
        0xe9, 0x3d, 0x7e, 0x11, 0x73, 0x93, 0x17, 0x2a,
        0xae, 0x2d, 0x8a, 0x57, 0x1e, 0x03, 0xac, 0x9c,
        0x9e, 0xb7, 0x6f, 0xac, 0x45, 0xaf, 0x8e, 0x51
    },
    .vector.length = 32,
};

static const uint8_t bigMessage[] = {
    /* "All work and no play makes Jack a dull boy. " */
    0x41,0x6c,0x6c,0x20,0x77,0x6f,0x72,0x6b,
    0x20,0x61,0x6e,0x64,0x20,0x6e,0x6f,0x20,
    0x70,0x6c,0x61,0x79,0x20,0x6d,0x61,0x6b,
    0x65,0x73,0x20,0x4a,0x61,0x63,0x6b,0x20,
    0x61,0x20,0x64,0x75,0x6c,0x6c,0x20,0x62,
    0x6f,0x79,0x2e,0x20,0x41,0x6c,0x6c,0x20,
    0x77,0x6f,0x72,0x6b,0x20,0x61,0x6e,0x64,
    0x20,0x6e,0x6f,0x20,0x70,0x6c,0x61,0x79,
    0x20,0x6d,0x61,0x6b,0x65,0x73,0x20,0x4a,
    0x61,0x63,0x6b,0x20,0x61,0x20,0x64,0x75,
    0x6c,0x6c,0x20,0x62,0x6f,0x79,0x2e,0x20,
    0x41,0x6c,0x6c,0x20,0x77,0x6f,0x72,0x6b,
    0x20,0x61,0x6e,0x64,0x20,0x6e,0x6f,0x20,
    0x70,0x6c,0x61,0x79,0x20,0x6d,0x61,0x6b,
    0x65,0x73,0x20,0x4a,0x61,0x63,0x6b,0x20,
    0x61,0x20,0x64,0x75,0x6c,0x6c,0x20,0x62,
    0x6f,0x79,0x2e,0x20,0x41,0x6c,0x6c,0x20,
    0x77,0x6f,0x72,0x6b,0x20,0x61,0x6e,0x64,
    0x20,0x6e,0x6f,0x20,0x70,0x6c,0x61,0x79,
    0x20,0x6d,0x61,0x6b,0x65,0x73,0x20,0x4a,
    0x61,0x63,0x6b,0x20,0x61,0x20,0x64,0x75,
    0x6c,0x6c,0x20,0x62,0x6f,0x79,0x2e,0x20,
    0x41,0x6c,0x6c,0x20,0x77,0x6f,0x72,0x6b,
    0x20,0x61,0x6e,0x64,0x20,0x6e,0x6f,0x20,
    0x70,0x6c,0x61,0x79,0x20,0x6d,0x61,0x6b,
    0x65,0x73,0x20,0x4a,0x61,0x63,0x6b,0x20,
    0x61,0x20,0x64,0x75,0x6c,0x6c,0x20,0x62,
    0x6f,0x79,0x2e,0x20,0x41,0x6c,0x6c,0x20,
    0x77,0x6f,0x72,0x6b,0x20,0x61,0x6e,0x64,
    0x20,0x6e,0x6f,0x20,0x70,0x6c,0x61,0x79,
    0x20,0x6d,0x61,0x6b,0x65,0x73,0x20,0x4a,
    0x61,0x63,0x6b,0x20,0x61,0x20,0x64,0x75,
    0x6c,0x6c,0x20,0x62,0x6f,0x79,0x2e,0x20,
    0x41,0x6c,0x6c,0x20,0x77,0x6f,0x72,0x6b,
    0x20,0x61,0x6e,0x64,0x20,0x6e,0x6f,0x20,
    0x70,0x6c,0x61,0x79,0x20,0x6d,0x61,0x6b,
    0x65,0x73,0x20,0x4a,0x61,0x63,0x6b,0x20,
    0x61,0x20,0x64,0x75,0x6c,0x6c,0x20,0x62,
    0x6f,0x79,0x2e,0x20,0x41,0x6c,0x6c,0x20,
    0x77,0x6f,0x72,0x6b,0x20,0x61,0x6e,0x64,
    0x20,0x6e,0x6f,0x20,0x70,0x6c,0x61,0x79,
    0x20,0x6d,0x61,0x6b,0x65,0x73,0x20,0x4a,
    0x61,0x63,0x6b,0x20,0x61,0x20,0x64,0x75,
    0x6c,0x6c,0x20,0x62,0x6f,0x79,0x2e,0x20,
    0x41,0x6c,0x6c,0x20,0x77,0x6f,0x72,0x6b,
    0x20,0x61,0x6e,0x64,0x20,0x6e,0x6f,0x20,
    0x70,0x6c,0x61,0x79,0x20,0x6d,0x61,0x6b,
    0x65,0x73,0x20,0x4a,0x61,0x63,0x6b,0x20
};

static const cryptoST_testVector_t BigMessage =
{
    .name = "AES_CBC big message",
    .source = "/wolfssl/wolfcrypt/test/test.c line 6443",
    .description = "All work and no play makes Jack a dull boy. ",
    .vector.data = (uint8_t*)bigMessage,
    .vector.length = (sizeof(bigMessage)/sizeof(uint8_t)),
};
#endif

static const cryptoST_testDetail_t test_item[] =
{
#if defined(WOLFSSL_AES_128)
    {
        .technique = ET_AES_128,
        .mode = EM_CBC,
        .recommendedRepetitions = 1000,

        .source = __BASE_FILE__,
        .pedigree = "/wolfssl/wolfcrypt/test/test.c line 6330",
        .rawData = &NowIsTheTime, // test.c 6335
        .io.sym.out.cipher = { // aes_cbc_test() does not verify data
            .length = 0,  // refer to aes_test(), line 6374
            .data = 0,
        },
        .io.sym.in.key = { // test.c 6341
            .length = AES128_KEY_SIZE/8,
            .data = (ALIGN4 const uint8_t*)"0123456789abcdef   ",
        },
        .io.sym.in.ivNonce = { // test.c 6341
            .length = 16,
            .data = (ALIGN4 uint8_t*)"1234567890abcdef   ",
        },
    },
    {
        .technique = ET_AES_128,
        .mode = EM_CBC,
        .recommendedRepetitions = 1000,

        .source = __BASE_FILE__,
        .pedigree = "/wolfssl/wolfcrypt/test/test.c line 6395",
        .rawData = &NowIsTheTime,
        .io.sym.out.cipher = { // test.c 6394
            .length = 16,
            .data = (ALIGN4  const uint8_t[]){ 
                0x95,0x94,0x92,0x57,0x5f,0x42,0x81,0x53,
                0x2c,0xcc,0x9d,0x46,0x77,0xa2,0x33,0xcb
              }
        },
        .io.sym.in.key = { // test.c 6341
            .length = AES128_KEY_SIZE/8,
            .data = (ALIGN4 const uint8_t*)"0123456789abcdef   ",
        },
        .io.sym.in.ivNonce = { // test.c 6341
            .length = 16,
            .data = (ALIGN4 const uint8_t*)"1234567890abcdef   ",
        },
    },
    {
        .technique = ET_AES_128,
        .mode = EM_CBC,
        .recommendedRepetitions = 1000,

        .source = __BASE_FILE__,
        .pedigree = "/wolfssl/wolfcrypt/test/test.c line 6494",
        .rawData = &BigMessage,
        .io.sym.out.cipher = { 0, 0 }, // use enc/dec to check
        .io.sym.in.key = {
            .length = AES128_KEY_SIZE/8, // .data is longer
            .data = (ALIGN4 const uint8_t*)"0123456789abcdeffedcba9876543210",
        },
        .io.sym.in.ivNonce = { // test.c 6341
            .length = 16,
            .data = (ALIGN4 const uint8_t*)"1234567890abcdef   ",
        },
        // .authenticateTag =  { 0, NULL },
    },
    {
        .technique = ET_AES_128,
        .mode = EM_CBC,
        .recommendedRepetitions = 1000,

        .source = __BASE_FILE__,
        .pedigree = "/wolfssl/wolfcrypt/test/test.c line 6557",
        .rawData = &Message2,
        .io.sym.out.cipher = { 0, 0 }, // use enc/dec to check
        .io.sym.in.key = {
            .length = AES128_KEY_SIZE/8,
            .data = (ALIGN4 const uint8_t[]){
                0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6,
                0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0x3c
            },
        },
        .io.sym.in.ivNonce = { // test.c 6341
            .length = 16,
            .data = (ALIGN4 const uint8_t[]){ 
                0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
                0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f
            },
        },
        // .authenticateTag =  { 0, NULL },
    },
#endif // WOLFSSL_AES_128
#if defined(WOLFSSL_AES_192)
    {
        .technique = ET_AES_192,
        .mode = EM_CBC,
        .recommendedRepetitions = 1000,

        .source = __BASE_FILE__,
        .pedigree = "/wolfssl/wolfcrypt/test/test.c line 6494",
        .rawData = &BigMessage,
        .io.sym.out.cipher = { 0, 0 }, // use enc/dec to check
        .io.sym.in.key = {
            .length = AES192_KEY_SIZE/8, // .data is longer
            .data = (ALIGN4 const uint8_t*)"0123456789abcdeffedcba9876543210",
        },
        .io.sym.in.ivNonce = { // test.c 6341
            .length = 16,
            .data = (ALIGN4 const uint8_t*)"1234567890abcdef   ",
        },
        // .authenticateTag =  { 0, NULL },
    },
#endif // WOLFSSL_AES_192
#if defined(WOLFSSL_AES_256)
    {
        .technique = ET_AES_256,
        .mode = EM_CBC,
        .recommendedRepetitions = 1000,

        .source = __BASE_FILE__,
        .pedigree = "/wolfssl/wolfcrypt/test/test.c line 6494",
        .rawData = &BigMessage,
        .io.sym.out.cipher = { 0, 0 }, // use enc/dec to check
        .io.sym.in.key = {
            .length = AES256_KEY_SIZE/8,
            .data = (ALIGN4 const uint8_t*)"0123456789abcdeffedcba9876543210",
        },
        .io.sym.in.ivNonce = { // test.c 6341
            .length = 16,
            .data = (ALIGN4 const uint8_t*)"1234567890abcdef   ",
        },
        // .authenticateTag =  { 0, NULL },
    },
#endif // WOLFSSL_AES_256
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
#include "cryptoSTD_wolfSSL_aes_cbc.h"
cryptoST_testAPI_t const wolfSSL_aes_cbc =
{
    .name = "AES_CBC",
    .openData = NULL,
    .firstTest = firstTest,
    .nextTest = nextTest,
    .closeData = NULL,
};

