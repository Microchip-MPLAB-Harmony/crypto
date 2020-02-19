/* cryptoSTV_wolfSSL_AES_CTR

   This package transliterates test data from the wolfSSL test.c file.
   Specifically the data for the AES192 tests.
*/

#include <stdint.h>
#include "./cryptoSpeedTestData.h"
#include "cryptoST/cryptoSTE_malloc.h"
#include "cryptoST/cryptoST_print.h" // for BASE_LINE
#ifdef HAVE_CONFIG_H
    #include <config.h>
#endif

#define CONST /* as nothing */

#if defined(WOLFSSL_AES_128) \
 || defined(WOLFSSL_AES_192) \
 || defined(WOLFSSL_AES_256)
static const CPU_CHAR nist_800_38A_description[] = {
        "test vectors from " // test.c line 6623
        "\"Recommendation for Block Cipher Modes of Operation\" "
        "NIST Special Publication 800-38A" };

static uint8_t nist_800_38A_iv[] = // test.c line 6626
        (uint8_t[]){ 0xf0,0xf1,0xf2,0xf3,0xf4,0xf5,0xf6,0xf7,
                     0xf8,0xf9,0xfa,0xfb,0xfc,0xfd,0xfe,0xff
                   };

static uint8_t nist_800_38A_ctrPlain[] = { // test.c line 6632
    0x6b,0xc1,0xbe,0xe2,0x2e,0x40,0x9f,0x96,
    0xe9,0x3d,0x7e,0x11,0x73,0x93,0x17,0x2a,
    0xae,0x2d,0x8a,0x57,0x1e,0x03,0xac,0x9c,
    0x9e,0xb7,0x6f,0xac,0x45,0xaf,0x8e,0x51,
    0x30,0xc8,0x1c,0x46,0xa3,0x5c,0xe4,0x11,
    0xe5,0xfb,0xc1,0x19,0x1a,0x0a,0x52,0xef,
    0xf6,0x9f,0x24,0x45,0xdf,0x4f,0x9b,0x17,
    0xad,0x2b,0x41,0x7b,0xe6,0x6c,0x37,0x10
};

#if 0
/* A note about oddCipher....
 * In test.c this file is used for a second round of data
 * encryption, using the updated ctr. Not sure how to
 * represent that here. For the moment we wil simply
 * ignore it. */
static uint8_t oddCipher[] = {
    0xb9,0xd7,0xcb,0x08,0xb0,0xe1,0x7b,0xa0,
    0xc2
};
#endif

static CONST cryptoST_testVector_t NIST_800_38A =
{
    .name = "AES_CTR Message2",
    .source = "/wolfssl/wolfcrypt/test/test.c line 6632",
    .description = nist_800_38A_description,
    .vector.data = nist_800_38A_ctrPlain,
    .vector.length = sizeof(nist_800_38A_ctrPlain),
};
#endif // all the AES sizes

static CONST cryptoST_testDetail_t test_item[] =
{
    /* **************************************************************
     * test vectors from "Recommendation for Block Cipher Modes of
     * Operation" NIST Special Publication 800-38A 
     */
#if defined(WOLFSSL_AES_128)
    {
        .technique = ET_AES_128,
        .mode = EM_CTR,
        .recommendedRepetitions = 1000,

        .source = __BASE_FILE__ "(" BASE_LINE ")",
        .pedigree = "/wolfssl/wolfcrypt/test/test.c line 6657",
        .rawData = &NIST_800_38A,
        .goldenCipher = {
            .length = 64,
            .data = (uint8_t[]) // line 6657 ctr128Cipher
            {   0x87,0x4d,0x61,0x91,0xb6,0x20,0xe3,0x26,
                0x1b,0xef,0x68,0x64,0x99,0x0d,0xb6,0xce,
                0x98,0x06,0xf6,0x6b,0x79,0x70,0xfd,0xff,
                0x86,0x17,0x18,0x7b,0xb9,0xff,0xfd,0xff,
                0x5a,0xe4,0xdf,0x3e,0xdb,0xd5,0xd3,0x5e,
                0x5b,0x4f,0x09,0x02,0x0d,0xb0,0x3e,0xab,
                0x1e,0x03,0x1d,0xda,0x2f,0xbe,0x03,0xd1,
                0x79,0x21,0x70,0xa0,0xf3,0x00,0x9c,0xee
            },
        },
        .key = { // line 6651 ctr128Key
            .length = AES128_KEY_SIZE/8,
            .data = (uint8_t[]){
                0x2b,0x7e,0x15,0x16,0x28,0xae,0xd2,0xa6,
                0xab,0xf7,0x15,0x88,0x09,0xcf,0x4f,0x3c
            },
        },
        .initVector = {
            .data = nist_800_38A_iv,
            .length = ALENGTH(nist_800_38A_iv)
        },
        // .authenticateTag =  { 0, NULL },
    },
#endif /* WOLFSSL_AES_128 */
#if defined(WOLFSSL_AES_192)
    {
        .technique = ET_AES_192,
        .mode = EM_CTR,
        .recommendedRepetitions = 1000,

        .source = __BASE_FILE__ "(" BASE_LINE ")",
        .pedigree = "/wolfssl/wolfcrypt/test/test.c line 6671",
        .rawData = &NIST_800_38A,
        .goldenCipher = {
            .length = 64,
            .data = (uint8_t[]){ // line 6678 ctr192Cipher
                0x1a,0xbc,0x93,0x24,0x17,0x52,0x1c,0xa2,
                0x4f,0x2b,0x04,0x59,0xfe,0x7e,0x6e,0x0b,
                0x09,0x03,0x39,0xec,0x0a,0xa6,0xfa,0xef,
                0xd5,0xcc,0xc2,0xc6,0xf4,0xce,0x8e,0x94,
                0x1e,0x36,0xb2,0x6b,0xd1,0xeb,0xc6,0x70,
                0xd1,0xbd,0x1d,0x66,0x56,0x20,0xab,0xf7,
                0x4f,0x78,0xa7,0xf6,0xd2,0x98,0x09,0x58,
                0x5a,0x97,0xda,0xec,0x58,0xc6,0xb0,0x50
            },
        },
        .key = { // line 6671 ctr192Key
            .length = AES192_KEY_SIZE/8,
            .data = (uint8_t[]){ 
                0x8e,0x73,0xb0,0xf7,0xda,0x0e,0x64,0x52,
                0xc8,0x10,0xf3,0x2b,0x80,0x90,0x79,0xe5,
                0x62,0xf8,0xea,0xd2,0x52,0x2c,0x6b,0x7b
            },
        },
        .initVector = {
            .data = nist_800_38A_iv,
            .length = ALENGTH(nist_800_38A_iv)
        },
    },
#endif
#if defined(WOLFSSL_AES_256)
    {
        .technique = ET_AES_256,
        .mode = EM_CTR,
        .recommendedRepetitions = 1000,

        .source = __BASE_FILE__ "(" BASE_LINE ")",
        .pedigree = "/wolfssl/wolfcrypt/test/test.c line 6690",
        .rawData = &NIST_800_38A,
        .goldenCipher = {
            .length = 64,
            .data = (uint8_t[]){ // line 6699 ctr256Cipher
                0x60,0x1e,0xc3,0x13,0x77,0x57,0x89,0xa5,
                0xb7,0xa7,0xf5,0x04,0xbb,0xf3,0xd2,0x28,
                0xf4,0x43,0xe3,0xca,0x4d,0x62,0xb5,0x9a,
                0xca,0x84,0xe9,0x90,0xca,0xca,0xf5,0xc5,
                0x2b,0x09,0x30,0xda,0xa2,0x3d,0xe9,0x4c,
                0xe8,0x70,0x17,0xba,0x2d,0x84,0x98,0x8d,
                0xdf,0xc9,0xc5,0x8d,0xb6,0x7a,0xad,0xa6,
                0x13,0xc2,0xdd,0x08,0x45,0x79,0x41,0xa6
            }
        },
        .key = { // line 6691 ctr256Key
            .length = AES256_KEY_SIZE/8,
            .data = (uint8_t[]){   
                0x60,0x3d,0xeb,0x10,0x15,0xca,0x71,0xbe,
                0x2b,0x73,0xae,0xf0,0x85,0x7d,0x77,0x81,
                0x1f,0x35,0x2c,0x07,0x3b,0x61,0x08,0xd7,
                0x2d,0x98,0x10,0xa3,0x09,0x14,0xdf,0xf4
            },
        },
        .initVector = {
            .data = nist_800_38A_iv,
            .length = ALENGTH(nist_800_38A_iv),
        },
    },
#endif
    {}
};
#define test_item_count (ALENGTH(test_item))

/*************************************************************
 * API handlers
 *************************************************************/
static cryptoST_testDetail_t * firstTest(void)
{
    return test_item;
}
static cryptoST_testDetail_t * nextTest(cryptoST_testDetail_t * old)
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
#include "cryptoSTD_wolfSSL_aes_ctr.h"
cryptoST_testAPI_t const wolfSSL_aes_ctr =
{
    .name = "AES_CTR",
    .openData = NULL,
    .firstTest = firstTest,
    .nextTest = nextTest,
    .closeData = NULL,
};

