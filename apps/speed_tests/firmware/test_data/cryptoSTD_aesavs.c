/*******************************************************************************
  Crypto Speed Test Source File

  Company:
    Microchip Technology Inc.

  File Name:
    cryptoSTD_aesavs

  Summary:
    Test data from the Advanced Encryption Standard
    Algorithm Validation Suite (AESAVS) Nov 15, 2002,
    by Lawrence E. Bassham of NIST.

  Description:
    There are 4 test groups (GFSBox, KeySBox, VarText, VarKey) 
    characterized by patterns of specifying key, plain and cipher text. 
    Refer to the individual test generator functions next_aes_XXXX()
    defined below, and to the AESAVS source material.
        
    AESAVS defines test vectors for all AES key sizes, but the data sets
    have been abbreviated here for space and time. Future editions of this
    test may include additional vectors.

    http://csrc.nist.gov/groups/STM/cavp/documents/aes/AESAVS.pdf
 ******************************************************************************
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

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include <stddef.h>
#include <stdint.h>
#include <string.h> // for memset()
#include <assert.h>
#include "./cryptoSpeedTestData.h"
#include "configuration.h"

#if !defined(NO_AES_128) \
 && !defined(NO_AES_192) \
 && !defined(NO_AES_256)

#define CONST /* as nothing */
#define null ((void*)0)

// *****************************************************************************
// *****************************************************************************
// Section: Local data and data structures
// *****************************************************************************
// *****************************************************************************
#define PDF "AESAVF.pdf"
static const CPU_CHAR dataSource[] = PDF ", NIST, 22 Nov 2002";

typedef uint8_t bytes16_t[16];
typedef struct plainCipher_s
{
    bytes16_t plain;
    bytes16_t cipher;
} plainCipher_t;
typedef struct keyCipher_s
{
    bytes16_t key;
    bytes16_t cipher;
} keyCipher_t;

static union
{
    uint8_t buffer16[16];
    uint8_t buffer24[24];
    uint8_t buffer32[32];
} buffer = {{0}};

static const union
{
    uint8_t zero16[16];
    uint8_t zero24[24];
    uint8_t zero32[32];
} zero = {{0}};

// *****************************************************************************
// *****************************************************************************
// Section: AES 128 bit data elements
// *****************************************************************************
// *****************************************************************************
#if defined(WOLFSSL_AES_128)
/* not constant */
static cryptoST_testVector_t GFSBox_KAT128 =
{
    .name = "AESAVS_GFSKAT",
    .source = dataSource,
    .vector.data = (uint8_t[16]){0},
    .vector.length = 16,
};

static const cryptoST_testVector_t KeySBox_KAT128 =
{
    .name = "AESAVS_KeySKAT",
    .source = dataSource,
    .vector.data = (uint8_t[16]){0}, 
    .vector.length = 16,
};

static const cryptoST_testVector_t VarText_KAT128 =
{
    .name = "AESAVS_VarTextKAT",
    .source = dataSource,
    .vector.data = buffer.buffer16, 
    .vector.length = 16,
};

static const cryptoST_testVector_t VarKey_KAT128 =
{
    .name = "AESAVS_VarKeyKAT",
    .source = dataSource,
    .vector.data = (uint8_t[16]){0}, // same for all keys
    .vector.length = 16,
};

/* Tabulations of the various keys and results detailed in the source document. */
/* Appendix B */
static const plainCipher_t GFSBox_detail128[] = {
    {
.plain  = {0xf3,0x44,0x81,0xec,0x3c,0xc6,0x27,0xba,0xcd,0x5d,0xc3,0xfb,0x08,0xf2,0x73,0xe6},
.cipher = {0x03,0x36,0x76,0x3e,0x96,0x6d,0x92,0x59,0x5a,0x56,0x7c,0xc9,0xce,0x53,0x7f,0x5e},
    },
    {
.plain  = {0x97,0x98,0xc4,0x64,0x0b,0xad,0x75,0xc7,0xc3,0x22,0x7d,0xb9,0x10,0x17,0x4e,0x72},
.cipher = {0xa9,0xa1,0x63,0x1b,0xf4,0x99,0x69,0x54,0xeb,0xc0,0x93,0x95,0x7b,0x23,0x45,0x89},
    },
    {
.plain  = {0x96,0xab,0x5c,0x2f,0xf6,0x12,0xd9,0xdf,0xaa,0xe8,0xc3,0x1f,0x30,0xc4,0x21,0x68},
.cipher = {0xff,0x4f,0x83,0x91,0xa6,0xa4,0x0c,0xa5,0xb2,0x5d,0x23,0xbe,0xdd,0x44,0xa5,0x97},
    },
    {
.plain  = {0x6a,0x11,0x8a,0x87,0x45,0x19,0xe6,0x4e,0x99,0x63,0x79,0x8a,0x50,0x3f,0x1d,0x35},
.cipher = {0xdc,0x43,0xbe,0x40,0xbe,0x0e,0x53,0x71,0x2f,0x7e,0x2b,0xf5,0xca,0x70,0x72,0x09},
    },
    // this list is incomplete
};

/* Appendix C */
static const keyCipher_t KeySBox_detail128[] = {
    {
.key    = {0x10,0xa5,0x88,0x69,0xd7,0x4b,0xe5,0xa3,0x74,0xcf,0x86,0x7c,0xfb,0x47,0x38,0x59},
.cipher = {0x6d,0x25,0x1e,0x69,0x44,0xb0,0x51,0xe0,0x4e,0xaa,0x6f,0xb4,0xdb,0xf7,0x84,0x65},
    },
    {
.key    = {0xca,0xea,0x65,0xcd,0xbb,0x75,0xe9,0x16,0x9e,0xcd,0x22,0xeb,0xe6,0xe5,0x46,0x75},
.cipher = {0x6e,0x29,0x20,0x11,0x90,0x15,0x2d,0xf4,0xee,0x05,0x81,0x39,0xde,0xf6,0x10,0xbb},
    },
    {
.key    = {0xa2,0xe2,0xfa,0x9b,0xaf,0x7d,0x20,0x82,0x2c,0xa9,0xf0,0x54,0x2f,0x76,0x4a,0x41},
.cipher = {0xc3,0xb4,0x4b,0x95,0xd9,0xd2,0xf2,0x56,0x70,0xee,0xe9,0xa0,0xde,0x09,0x9f,0xa3},
    },
    {
.key    = {0xb6,0x36,0x4a,0xc4,0xe1,0xde,0x1e,0x28,0x5e,0xaf,0x14,0x4a,0x24,0x15,0xf7,0xa0},
.cipher = {0x5d,0x9b,0x05,0x57,0x8f,0xc9,0x44,0xb3,0xcf,0x1c,0xcf,0x0e,0x74,0x6c,0xd5,0x81},
    },
    // this list is incomplete
};

/* Appendix D */
static const bytes16_t VarText_cipher128[] = { // data is generated algorithmically
    {0x3a,0xd7,0x8e,0x72,0x6c,0x1e,0xc0,0x2b,0x7e,0xbf,0xe9,0x2b,0x23,0xd9,0xec,0x34},
    {0xaa,0xe5,0x93,0x9c,0x8e,0xfd,0xf2,0xf0,0x4e,0x60,0xb9,0xfe,0x71,0x17,0xb2,0xc2},
    {0xf0,0x31,0xd4,0xd7,0x4f,0x5d,0xcb,0xf3,0x9d,0xaa,0xf8,0xca,0x3a,0xf6,0xe5,0x27},
    {0x96,0xd9,0xfd,0x5c,0xc4,0xf0,0x74,0x41,0x72,0x7d,0xf0,0xf3,0x3e,0x40,0x1a,0x36},
    // this list is incomplete
};

/* Appendix E */
static const bytes16_t VarKey_cipher128[] = { // keys are generated algorithmically
    {0x0e,0xdd,0x33,0xd3,0xc6,0x21,0xe5,0x46,0x45,0x5b,0xd8,0xba,0x14,0x18,0xbe,0xc8},
    {0x4b,0xc3,0xf8,0x83,0x45,0x0c,0x11,0x3c,0x64,0xca,0x42,0xe1,0x11,0x2a,0x9e,0x87},
    {0x72,0xa1,0xda,0x77,0x0f,0x5d,0x7a,0xc4,0xc9,0xef,0x94,0xd8,0x22,0xaf,0xfd,0x97},
    {0x97,0x00,0x14,0xd6,0x34,0xe2,0xb7,0x65,0x07,0x77,0xe8,0xe8,0x4d,0x03,0xcc,0xd8},
    // this list is incomplete
};
#endif // WOLFSSL_AES_128

// *****************************************************************************
// *****************************************************************************
// Section: AES 192 bit data elements
// *****************************************************************************
// *****************************************************************************
#if defined(WOLFSSL_AES_192)
// TODO: "Transcribe test data from AESAVS.pdf for AES192"
#endif // WOLFSSL_AES_192

// *****************************************************************************
// *****************************************************************************
// Section: AES 256 bit data elements
// *****************************************************************************
// *****************************************************************************
#if defined(WOLFSSL_AES_256)
// TODO: "Transcribe test data from AESAVS.pdf for AES256"
#endif // WOLFSSL_AES_256

// *****************************************************************************
// *****************************************************************************
// Section: Executable code
// *****************************************************************************
// *****************************************************************************

/*************************************************************
 * Helper functions
 *************************************************************/
static void setHighBitsOf16Bytes(uint8_t * data, int numberOfBits)
{
    assert(numberOfBits <= (16*8));

    memset(data,0,16);

    uint8_t * b = data;
    while(numberOfBits >= 8)
    { *b++ = 0xFF; numberOfBits -= 8; }
    
    if (numberOfBits) // .ge. 1 and .le. 7
    {
        int8_t d = 0x80;      // signed byte will sign-extend
        d >>= numberOfBits-1; // could shift zero times
        *b++ = (uint8_t)d;
    }
}

/* This must never be declared const. */
static cryptoST_testDetail_t testDetail =
{
    .technique = ET_AES_128,
    .mode = EM_ECB,
    .recommendedRepetitions = 1000,

    .source = __BASE_FILE__,
    .pedigree = 0 /* fill in later */,
    .rawData = 0,
    .io.sym.out.cipher = {
        .data = (uint8_t[]){ 0 },
        .length = 16,
    },
    .io.sym.in.key.data = 0,   // buffer & length tbd later
    .io.sym.in.key.length = 0,
    // .io.sym.in.ivNonce = (const cryptoST_testData_t){0},
};
#define mutableKey  testDetail.io.sym.in.key

/***********************************************************************
 * API handlers
 * Each test group (AES128, AES256, etc) has both a detailed test list
 * and specific set-up requirements based on subTest type, and each
 * can be disabled by H3 controls, so we treat them all separately.
 **********************************************************************/
static int detailCounter; // persistant

#if defined(WOLFSSL_AES_128)
static const cryptoST_testVector_t * next_aes_GFSBox_KAT128(const cryptoST_testVector_t * oldData)
{
    if (0 == detailCounter)
    { testDetail.pedigree = PDF " appendix B"; }

    if (ALENGTH(GFSBox_detail128) > detailCounter)
    {
        /* Plain and cipher are provided explicitly; key is constant. */
        const plainCipher_t * newData = &GFSBox_detail128[detailCounter];
        testDetail.io.sym.out.cipher.data = (uint8_t*)(newData->cipher);
        mutableKey.data = (uint8_t*)zero.zero16;
        mutableKey.length = sizeof(buffer.buffer16);
        GFSBox_KAT128.vector.data = (uint8_t*)(newData->plain);
        detailCounter++;
        return(oldData);
    }
    else return 0;
}

static const cryptoST_testVector_t * next_aes_KeySBox_KAT128(const cryptoST_testVector_t * oldData)
{
    if (0 == detailCounter)
    { testDetail.pedigree = PDF " appendix C"; }

    if (ALENGTH(KeySBox_detail128) > detailCounter)
    {
        /* Key and cipher are provided explicitly; data is constant. */
        const keyCipher_t * newData = &KeySBox_detail128[detailCounter];
        testDetail.io.sym.out.cipher.data = (uint8_t*)(newData->cipher);
        mutableKey.data = (uint8_t*)(newData->key);
        detailCounter++;
        return(oldData);
    }
    else return 0;
}

static const cryptoST_testVector_t * next_aes_VarText_KAT128(const cryptoST_testVector_t * oldData)
{
    if (0 == detailCounter)
    { testDetail.pedigree = PDF " appendix D"; }

    if (ALENGTH(VarText_cipher128) > detailCounter)
    {
        /* Cipher is explicit; key is constant zero; 
           data is generated here like 0xFF.E0...00.00 */
        testDetail.io.sym.out.cipher.data =
                (uint8_t*)&VarText_cipher128[detailCounter];
        mutableKey.data = (uint8_t*)zero.zero16;
        mutableKey.length = sizeof(zero.zero16);
        setHighBitsOf16Bytes(buffer.buffer16, detailCounter+1);
        detailCounter++;
        return(oldData);
    }
    else return 0;
}

static const cryptoST_testVector_t * next_aes_VarKey_KAT128(const cryptoST_testVector_t * oldData)
{
    if (0 == detailCounter)
    { testDetail.pedigree = PDF " appendix E"; }

    if (ALENGTH(VarKey_cipher128) > detailCounter)
    {
        /* Cipher is explicit; data is constant zero;
           key is generated here like 0xFF.E0...00.00 */
        testDetail.io.sym.out.cipher.data = 
                (uint8_t*)&VarKey_cipher128[detailCounter];
        mutableKey.data = (uint8_t*)buffer.buffer16;
        mutableKey.length = sizeof(buffer.buffer16);
        setHighBitsOf16Bytes(buffer.buffer16, detailCounter+1);
        detailCounter++;
        return(oldData);
    }
    else return 0;
}
#endif // WOLFSSL_AES_128
#if defined(WOLFSSL_AES_192)
#endif // WOLFSSL_AES_192
#if defined(WOLFSSL_AES_256)
#endif // WOLFSSL_AES_256

/****************************************************************************
 * Test API
 * Each type of test is provided by a custom generator, as discriminated by
 * the testDetail data structure. However, we cannot switch on pointers so
 * all the structures are in a list.
 ****************************************************************************/
typedef const cryptoST_testVector_t * nextData_t(const cryptoST_testVector_t * const);
static struct detailDictionary_s 
{ const cryptoST_testVector_t * const detail; nextData_t * const nextData; }
const detailDictionary[] =
{
#if defined(WOLFSSL_AES_128)
    { &GFSBox_KAT128,  &next_aes_GFSBox_KAT128 },
    { &KeySBox_KAT128, &next_aes_KeySBox_KAT128 },
    { &VarText_KAT128, &next_aes_VarText_KAT128 },
    { &VarKey_KAT128,  &next_aes_VarKey_KAT128 },
#endif // WOLFSSL_AES_128
#if defined(WOLFSSL_AES_192)
#endif // WOLFSSL_AES_192
#if defined(WOLFSSL_AES_256)
#endif // WOLFSSL_AES_256
    { 0,  0 } // end marker
};

static const cryptoST_testDetail_t * nextTest(const cryptoST_testDetail_t * old)
{
    if (&testDetail == old)
    {
        const struct detailDictionary_s * lookup = &detailDictionary[0];
        while(lookup->detail)
        {
            /* This test will fail if we are on a repeat pass through this
             * same data generator. It will pass if we used all the data in
             * the previous generator and looped for a new generator. */
            if (0 == testDetail.rawData)
            {
                testDetail.rawData = lookup->detail;
                detailCounter = 0;
            }

            /* Scan down the list until we get to the "current" detail
             * data structure, then call the corresponding 'next'.
             * If we then get a null, move to the next generator. */
            if (testDetail.rawData == lookup->detail)
            {
                testDetail.rawData = (lookup->nextData)(testDetail.rawData);
                if (testDetail.rawData)
                    return &testDetail;
            }

            lookup++;
        }
    }
    return 0;
}

static const cryptoST_testDetail_t * firstTest(void)
{
    testDetail.rawData = 0;
    return nextTest(&testDetail);
};
#else
static const cryptoST_testDetail_t * firstTest(void)
{ return 0; }
static const cryptoST_testDetail_t * nextTest(const cryptoST_testDetail_t * old)
{ return 0; }
#endif // NO_AES

/*************************************************************
 * Declaration of the test manager API
 * Obligatory entry points for executing a test
 *************************************************************/
#include "cryptoSTD_wolfSSL_aes_cbc.h"
cryptoST_testAPI_t const aesavs_aes128 =
{
    .name = "AESAVS_ECB128",
    .openData = NULL,
    .firstTest = firstTest,
    .nextTest = nextTest,
    .closeData = NULL,
};
