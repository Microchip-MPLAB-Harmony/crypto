/* cryptoSTV_wolfSSL_AES_GCM

  Crypto Speed Test Data File

  Company:
    Microchip Technology Inc.

  Description:
   This package transliterates test data from the wolfSSL test.c file.
   Specifically the data for the AES tests. In addition, large random and 
 * sequential data sets are defined.
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

#include <stdint.h>
#include "./cryptoSpeedTestData.h"
#include "cryptoST/cryptoSTE_generate.h"
#include "cryptoST/cryptoSTE_malloc.h"
#include "cryptoST/cryptoSTE_print.h" // for BASE_LINE
#include "cryptoSTD_wolfSSL_aes_gcm.h"

#define CONST /* as nothing */
#define DATA_PACKAGE_NAME "GCM"
#define ALIGN4 __attribute__((aligned(4)))

const CPU_CHAR AES_GCM_default_description[] = {
        "Vectors are from NIST SP 800-38D "
        "using 12 byte IV and 16 or less byte AAD "
        "https://csrc.nist.gov/Projects/Cryptographic-Algorithm-Validation-Program/CAVP-TESTING-BLOCK-CIPHER-MODES" };

/*************************************************************
 * Raw (input) data definitions providing small-block constants.
 *************************************************************/
static const cryptoST_testVector_t dt1 =
{
    .name = DATA_PACKAGE_NAME "_DEF1",
    .source = "/wolfssl/wolfcrypt/test/test.c line 7181",
    .description = AES_GCM_default_description,
    .vector.data = (uint8_t[]){
        0xcc, 0x38, 0xbc, 0xcd, 0x6b, 0xc5, 0x36, 0xad,
        0x91, 0x9b, 0x13, 0x95, 0xf5, 0xd6, 0x38, 0x01,
        0xf9, 0x9f, 0x80, 0x68, 0xd6, 0x5c, 0xa5, 0xac,
        0x63, 0x87, 0x2d, 0xaf, 0x16, 0xb9, 0x39, 0x01
    },
    .vector.length = 32,
};
static const cryptoST_testVector_t dt2 =
{
    .name = DATA_PACKAGE_NAME "_DEF2",
    .source = "/wolfssl/wolfcrypt/test/test.c line 7216",
    .description = AES_GCM_default_description,
    .vector.data = (uint8_t[]){
        0x4b, 0x34, 0xa9, 0xec, 0x57, 0x63, 0x52, 0x4b,
        0x19, 0x1d, 0x56, 0x16, 0xc5, 0x47, 0xf6, 0xb7
    },
    .vector.length = 16,
};
static const cryptoST_testVector_t dt3 =
{
    .name = DATA_PACKAGE_NAME "_NULL",
    .source = "/wolfssl/wolfcrypt/test/test.c line 7261",
    .description = AES_GCM_default_description,
    .vector.data = NULL, // legal for GCM
    .vector.length = 0,
};

static const char appGCM_description[] =
    "Test Case 16 of Galois/Counter Mode of Operation (GCM) by McGrew and Viega";
static const char appGCM_source[] = "encrypt-decrypt-test/app.c line 1273";
static const cryptoST_testVector_t appGCM =
{
    .name = DATA_PACKAGE_NAME "_APPGCM",
    .source = appGCM_source,
    .description = appGCM_description,
    .vector.data = (ALIGN4 const uint8_t[]){
        0xd9, 0x31, 0x32, 0x25, 0xf8, 0x84, 0x06, 0xe5,
        0xa5, 0x59, 0x09, 0xc5, 0xaf, 0xf5, 0x26, 0x9a,
        0x86, 0xa7, 0xa9, 0x53, 0x15, 0x34, 0xf7, 0xda,
        0x2e, 0x4c, 0x30, 0x3d, 0x8a, 0x31, 0x8a, 0x72,
        0x1c, 0x3c, 0x0c, 0x95, 0x95, 0x68, 0x09, 0x53,
        0x2f, 0xcf, 0x0e, 0x24, 0x49, 0xa6, 0xb5, 0x25,
        0xb1, 0x6a, 0xed, 0xf5, 0xaa, 0x0d, 0xe6, 0x57,
        0xba, 0x63, 0x7b, 0x39
    },
    .vector.length = (7*8)+4,
}; //  -- for app.c 192 and 256 bit tests

static const cryptoST_testVector_t appGCM128 =
{
    .name = DATA_PACKAGE_NAME "_APPGCM",
    .source = "encrypt-decrypt-test/app.c line 1375",
    .description = appGCM_description,
    /* The following is an interesting test case from the example
     * FIPS test vectors for AES-GCM. IVlen = 1 uint8_t */
    .vector.data = (ALIGN4 const uint8_t[]){
        0x57, 0xce, 0x45, 0x1f, 0xa5, 0xe2, 0x35, 0xa5,
        0x8e, 0x1a, 0xa2, 0x3b, 0x77, 0xcb, 0xaf, 0xe2
    },
    .vector.length = (2*8)+0,
}; //  -- for app.c 128 bit tests

static ALIGN4 const uint8_t appAAD[] = { // app.c 1285
    0xfe, 0xed, 0xfa, 0xce, 0xde, 0xad, 0xbe, 0xef,
    0xfe, 0xed, 0xfa, 0xce, 0xde, 0xad, 0xbe, 0xef,
    0xab, 0xad, 0xda, 0xd2 // sic: 2nd row is the same
}; //  -- for app.c 192 and 256 bit tests

/*************************************************************
 * Raw (input) data definitions for run-time defined
 * sequential and random data sets having large block sizes.
 *************************************************************/
#define SIZE4K     (2944)  // 0xB80
#define SIZE_PREALLOCATE    SIZE4K  // must be the largest
static cryptoST_testVector_t seq4k =
{
    .name = DATA_PACKAGE_NAME "_SEQ4K",
    .source = __BASE_FILE__ "(" BASE_LINE ")",
    .description = "Sequential data generated on-the-fly",
    .vector.data = NULL, // fill in later
    .vector.length = SIZE4K,
};
static cryptoST_testVector_t pr4k =
{
    .name = DATA_PACKAGE_NAME "_PR4K",
    .source = __BASE_FILE__ "(" BASE_LINE ")",
    .description = "PseudoRandom data generated on-the-fly",
    .vector.data = NULL, // fill in later
    .vector.length = SIZE4K,
};

/*************************************************************
 * Key and AAD inputs and golden data and tag result definitions.
 *************************************************************/
static const cryptoST_testDetail_t test_item[] =
{
    {
        .technique = ET_AES_GCM,
        .mode = EM_NONE,
        .recommendedRepetitions = 1000,

        .source = __BASE_FILE__ "(" BASE_LINE ")",
        .pedigree = "/wolfssl/wolfcrypt/test/test.c line 7171",
        .rawData = &dt1,
        .io.sym.in.key = { // test.c 7171
            .length = 16,
            .data = (ALIGN4 const uint8_t[]){
                0x29, 0x8e, 0xfa, 0x1c, 0xcf, 0x29, 0xcf, 0x62,
                0xae, 0x68, 0x24, 0xbf, 0xc1, 0x95, 0x57, 0xfc
            },
        },
        .io.sym.in.ivNonce = { // test.c 7177
            .length = 12,
            .data = (ALIGN4 const uint8_t[]){
                0x6f, 0x58, 0xa9, 0x3f, 0xe1, 0xd2, 0x07, 0xfa,
                0xe4, 0xed, 0x2f, 0x6d
            },
        },
        .io.sym.in.additionalAuthData = { // test.c 7188
            .length = 16,
            .data = (ALIGN4 const uint8_t[]){
                0x02, 0x1f, 0xaf, 0xd2, 0x38, 0x46, 0x39, 0x73,
                0xff, 0xe8, 0x02, 0x56, 0xe5, 0xb1, 0xc6, 0xb1
            },
        },
        .io.sym.out.cipher = { // test.c 7183
            .length = 32,
            .data = (ALIGN4 const uint8_t[]){
                0xdf, 0xce, 0x4e, 0x9c, 0xd2, 0x91, 0x10, 0x3d,
                0x7f, 0xe4, 0xe6, 0x33, 0x51, 0xd9, 0xe7, 0x9d,
                0x3d, 0xfd, 0x39, 0x1e, 0x32, 0x67, 0x10, 0x46,
                0x58, 0x21, 0x2d, 0xa9, 0x65, 0x21, 0xb7, 0xdb
            }
        },
        .io.sym.out.tag = { // test.c 7200
            .length = 16,
            .data = (ALIGN4 const uint8_t[]){
                0x54, 0x24, 0x65, 0xef, 0x59, 0x93, 0x16, 0xf7,
                0x3a, 0x7a, 0x56, 0x05, 0x09, 0xa2, 0xd9, 0xf2
            },
        },
    },
    {
        .technique = ET_AES_GCM,
        .mode = EM_NONE,
        .recommendedRepetitions = 1000,

        .source = __BASE_FILE__ "(" BASE_LINE ")",
        .pedigree = "/wolfssl/wolfcrypt/test/test.c line 7171",
        .rawData = &dt2,
        .io.sym.in.key = { // test.c 7207
            .length = 16,
            .data = (ALIGN4 const uint8_t[]){
                0x01, 0x6d, 0xbb, 0x38, 0xda, 0xa7, 0x6d, 0xfe,
                0x7d, 0xa3, 0x84, 0xeb, 0xf1, 0x24, 0x03, 0x64
            },
        },
        .io.sym.in.ivNonce = { // test.c 7212
            .length = 12,
            .data = (ALIGN4 const uint8_t[]){
                0x07, 0x93, 0xef, 0x3a, 0xda, 0x78, 0x2f, 0x78,
                0xc9, 0x8a, 0xff, 0xe3
            },
        },
        .io.sym.in.additionalAuthData = { // test.c 7256
            .length = 0,
            .data = NULL,
        },
        .io.sym.out.cipher = { // test.c 7221
            .length = 16,
            .data = (ALIGN4 const uint8_t[]){
                0x60, 0x9a, 0xa3, 0xf4, 0x54, 0x1b, 0xc0, 0xfe,
                0x99, 0x31, 0xda, 0xad, 0x2e, 0xe1, 0x5d, 0x0c
            }
        },
        .io.sym.out.tag = { // test.c 7226
            .length = 16,
            .data = (ALIGN4 const uint8_t[]){
                0x33, 0xaf, 0xec, 0x59, 0xc4, 0x5b, 0xaf, 0x68,
                0x9a, 0x5e, 0x1b, 0x13, 0xae, 0x42, 0x36, 0x19
            },
        },
    },
    {
        .technique = ET_AES_GCM,
        .mode = EM_NONE,
        .recommendedRepetitions = 1000,
        .expectError = true,   /* ******** */

        .source = __BASE_FILE__ "(" BASE_LINE ")",
        .pedigree = "/wolfssl/wolfcrypt/test/test.c line 7231",
        .rawData = &dt3, // null data
        .io.sym.in.key = { // test.c 7231
            .length = 16,
            .data = (ALIGN4 const uint8_t[]){
                0xb0, 0x1e, 0x45, 0xcc, 0x30, 0x88, 0xaa, 0xba,
                0x9f, 0xa4, 0x3d, 0x81, 0xd4, 0x81, 0x82, 0x3f
            },
        },
        .io.sym.in.ivNonce = { // test.c 7236
            .length = 12,
            .data = (ALIGN4 const uint8_t[]){
                0x5a, 0x2c, 0x4a, 0x66, 0x46, 0x87, 0x13, 0x45,
                0x6a, 0x4b, 0xd5, 0xe1
            },
        },
        .io.sym.in.additionalAuthData = { // test.c 7261
            .length = 0,
            .data = (ALIGN4 const uint8_t[]){
                0x60, 0x9a, 0xa3, 0xf4, 0x54, 0x1b, 0xc0, 0xfe,
                0x99, 0x31, 0xda, 0xad, 0x2e, 0xe1, 0x5d, 0x0c
            },
        },
        .io.sym.out.cipher = { // test.c 7261
            .length = 0,
            .data = NULL,
        },
        .io.sym.out.tag = { // test.c 7241
            .length = 12,
            .data = (ALIGN4 const uint8_t[]){
                0x01, 0x42, 0x80, 0xf9, 0x44, 0xf5, 0x3c, 0x68,
                0x11, 0x64, 0xb2, 0xff
            },
        },
    },
    {
        .technique = ET_AES_GCM,
        .mode = EM_NONE,
        .recommendedRepetitions = 100, /* *** */

        .source = __BASE_FILE__ "(" BASE_LINE ")",
        .pedigree = "MCHP sequential big block",
        .rawData = &seq4k,
        .io.sym.in.key = { // test.c 7231
            .length = 16,
            .data = (ALIGN4 const uint8_t[]){
                0xb0, 0x1e, 0x45, 0xcc, 0x30, 0x88, 0xaa, 0xba,
                0x9f, 0xa4, 0x3d, 0x81, 0xd4, 0x81, 0x82, 0x3f
            },
        },
        .io.sym.in.ivNonce = { // test.c 7236
            .length = 12,
            .data = (ALIGN4 const uint8_t[]){
                0x5a, 0x2c, 0x4a, 0x66, 0x46, 0x87, 0x13, 0x45,
                0x6a, 0x4b, 0xd5, 0xe1
            },
        },
        .io.sym.in.additionalAuthData = { // test.c 7177
            .length = 16,
            .data = (ALIGN4 const uint8_t[]){
                0x33, 0xaf, 0xec, 0x59, 0xc4, 0x5b, 0xaf, 0x68,
                0x9a, 0x5e, 0x1b, 0x13, 0xae, 0x42, 0x36, 0x19
            },
        },
        .io.sym.out.cipher = { // no data
            .length = 0,
            .data = NULL,
        },
        .io.sym.out.tag = { // no data
            .length = 0,
            .data = NULL,
        },
    },
    {
        .technique = ET_AES_GCM,
        .mode = EM_NONE,
        .recommendedRepetitions = 100, /* *** */

        .source = __BASE_FILE__ "(" BASE_LINE ")",
        .pedigree = "MCHP pseudoRandom big block",
        .rawData = &pr4k,
        .io.sym.in.key = { // test.c 7231
            .length = 16,
            .data = (ALIGN4 const uint8_t[]){
                0xb0, 0x1e, 0x45, 0xcc, 0x30, 0x88, 0xaa, 0xba,
                0x9f, 0xa4, 0x3d, 0x81, 0xd4, 0x81, 0x82, 0x3f
            },
        },
        .io.sym.in.ivNonce = { // test.c 7236
            .length = 12,
            .data = (ALIGN4 const uint8_t[]){
                0x5a, 0x2c, 0x4a, 0x66, 0x46, 0x87, 0x13, 0x45,
                0x6a, 0x4b, 0xd5, 0xe1
            },
        },
        .io.sym.in.additionalAuthData = { // test.c 7177
            .length = 16,
            .data = (ALIGN4 const uint8_t[]){
                0x33, 0xaf, 0xec, 0x59, 0xc4, 0x5b, 0xaf, 0x68,
                0x9a, 0x5e, 0x1b, 0x13, 0xae, 0x42, 0x36, 0x19
            },
        },
        .io.sym.out.cipher = { // no data
            .length = 0,
            .data = NULL,
        },
        .io.sym.out.tag = { // no data
            .length = 0,
            .data = NULL,
        },
    },
    {
        .technique = ET_AES_GCM,  // ------------------- 128 bit key
        .mode = EM_NONE,
        .recommendedRepetitions = 100, /* *** */

        .source = __BASE_FILE__ "(" BASE_LINE ")",
        .pedigree = appGCM_source,
        .rawData = &appGCM128,
        .io.sym.in.additionalAuthData = {
            .length = (2*8),
            .data = (ALIGN4 const uint8_t[]){ // app.c line 1398
                0x40, 0xfc, 0xdc, 0xd7, 0x4a, 0xd7, 0x8b, 0xf1,
                0x3e, 0x7c, 0x60, 0x55, 0x50, 0x51, 0xdd, 0x54
            },
        },
        .io.sym.in.key = { 
            .length = (2*8),
            .data = (ALIGN4 const uint8_t[]){ // app.c line 1335
                0xbb, 0x01, 0xd7, 0x03, 0x81, 0x1c, 0x10, 0x1a,
                0x35, 0xe0, 0xff, 0xd2, 0x91, 0xba, 0xf2, 0x4b
            },
        },
        .io.sym.in.ivNonce = {
            .length = 1,
            .data = (ALIGN4 const uint8_t[]){ // app.c lne 1387
                0xca
            },
        },
        .io.sym.out.cipher = { 
            .length = (2*8)+0,
            .data = (ALIGN4 const uint8_t[]){ // app.c line 1394
                0x6b, 0x5f, 0xb3, 0x9d, 0xc1, 0xc5, 0x7a, 0x4f,
                0xf3, 0x51, 0x4d, 0xc2, 0xd5, 0xf0, 0xd0, 0x07
            },
        },
        .io.sym.out.tag = {
            .length = (2*8)+0,
            .data = (ALIGN4 const uint8_t[]){ // app.c line 1404
                0x06, 0x90, 0xed, 0x01, 0x34, 0xdd, 0xc6, 0x95,
                0x31, 0x2e, 0x2a, 0xf9, 0x57, 0x7a, 0x1e, 0xa6
            },
        },
    },
    {
        .technique = ET_AES_GCM,  // ------------------- 192 bit key
        .mode = EM_NONE,
        .recommendedRepetitions = 100, /* *** */

        .source = __BASE_FILE__ "(" BASE_LINE ")",
        .pedigree = appGCM_source,
        .rawData = &appGCM,
        .io.sym.in.additionalAuthData = {
            .length = ALENGTH(appAAD), // (8*2)+4,
            .data = appAAD,
        },
        .io.sym.in.key = { 
            .length = 24,
            .data = (ALIGN4 const uint8_t[]){ // app.c line 1335
                0xfe, 0xff, 0xe9, 0x92, 0x86, 0x65, 0x73, 0x1c,
                0x6d, 0x6a, 0x8f, 0x94, 0x67, 0x30, 0x83, 0x08,
                0xfe, 0xff, 0xe9, 0x92, 0x86, 0x65, 0x73, 0x1c
            },
        },
        .io.sym.in.ivNonce = {
            .length = (8*7)+4,
            .data = (ALIGN4 const uint8_t[]){ // app.c lne 1342
                0x93, 0x13, 0x22, 0x5d, 0xf8, 0x84, 0x06, 0xe5,
                0x55, 0x90, 0x9c, 0x5a, 0xff, 0x52, 0x69, 0xaa,
                0x6a, 0x7a, 0x95, 0x38, 0x53, 0x4f, 0x7d, 0xa1,
                0xe4, 0xc3, 0x03, 0xd2, 0xa3, 0x18, 0xa7, 0x28,
                0xc3, 0xc0, 0xc9, 0x51, 0x56, 0x80, 0x95, 0x39,
                0xfc, 0xf0, 0xe2, 0x42, 0x9a, 0x6b, 0x52, 0x54,
                0x16, 0xae, 0xdb, 0xf5, 0xa0, 0xde, 0x6a, 0x57,
                0xa6, 0x37, 0xb3, 0x9b
            },
        },
        .io.sym.out.cipher = { 
            .length = (8*7)+4,
            .data = (ALIGN4 const uint8_t[]){ // app.c line 1356
                0xd2, 0x7e, 0x88, 0x68, 0x1c, 0xe3, 0x24, 0x3c,
                0x48, 0x30, 0x16, 0x5a, 0x8f, 0xdc, 0xf9, 0xff,
                0x1d, 0xe9, 0xa1, 0xd8, 0xe6, 0xb4, 0x47, 0xef,
                0x6e, 0xf7, 0xb7, 0x98, 0x28, 0x66, 0x6e, 0x45,
                0x81, 0xe7, 0x90, 0x12, 0xaf, 0x34, 0xdd, 0xd9,
                0xe2, 0xf0, 0x37, 0x58, 0x9b, 0x29, 0x2d, 0xb3,
                0xe6, 0x7c, 0x03, 0x67, 0x45, 0xfa, 0x22, 0xe7,
                0xe9, 0xb7, 0x37, 0x3b
            },
        },
        .io.sym.out.tag = {
            .length = (8*2),
            .data = (ALIGN4 const uint8_t[]){ // app.c line 1366
                0xdc, 0xf5, 0x66, 0xff, 0x29, 0x1c, 0x25, 0xbb,
                0xb8, 0x56, 0x8f, 0xc3, 0xd3, 0x76, 0xa6, 0xd9
            },
        },
    },
    {
        .technique = ET_AES_GCM,  // ------------------- 256 bit key
        .mode = EM_NONE,
        .recommendedRepetitions = 100, /* *** */

        .source = __BASE_FILE__ "(" BASE_LINE ")",
        .pedigree = appGCM_source,
        .rawData = &appGCM,
        .io.sym.in.additionalAuthData = {
            .length = ALENGTH(appAAD), // (8*2)+4,
            .data = appAAD,
        },
        .io.sym.in.key = { 
            .length = 32,
            .data = (ALIGN4 const uint8_t[]){ // app.c line 1293
                0xfe, 0xff, 0xe9, 0x92, 0x86, 0x65, 0x73, 0x1c,
                0x6d, 0x6a, 0x8f, 0x94, 0x67, 0x30, 0x83, 0x08,
                0xfe, 0xff, 0xe9, 0x92, 0x86, 0x65, 0x73, 0x1c,
                0x6d, 0x6a, 0x8f, 0x94, 0x67, 0x30, 0x83, 0x08
            },
        },
        .io.sym.in.ivNonce = {
            .length = (1*8)+4,
            .data = (ALIGN4 const uint8_t[]){ // app.c lne 1301
                0xca, 0xfe, 0xba, 0xbe, 0xfa, 0xce, 0xdb, 0xad,
                0xde, 0xca, 0xf8, 0x88
            },
        },
        .io.sym.out.cipher = { 
            .length = (8*7)+4,
            .data = (ALIGN4 const uint8_t[]){ // app.c line 1307
                0x52, 0x2d, 0xc1, 0xf0, 0x99, 0x56, 0x7d, 0x07,
                0xf4, 0x7f, 0x37, 0xa3, 0x2a, 0x84, 0x42, 0x7d,
                0x64, 0x3a, 0x8c, 0xdc, 0xbf, 0xe5, 0xc0, 0xc9,
                0x75, 0x98, 0xa2, 0xbd, 0x25, 0x55, 0xd1, 0xaa,
                0x8c, 0xb0, 0x8e, 0x48, 0x59, 0x0d, 0xbb, 0x3d,
                0xa7, 0xb0, 0x8b, 0x10, 0x56, 0x82, 0x88, 0x38,
                0xc5, 0xf6, 0x1e, 0x63, 0x93, 0xba, 0x7a, 0x0a,
                0xbc, 0xc9, 0xf6, 0x62
            },
        },
        .io.sym.out.tag = {
            .length = (8*2),
            .data = (ALIGN4 const uint8_t[]){ // app.c line 1320
                0x76, 0xfc, 0x6e, 0xce, 0x0f, 0x4e, 0x17, 0x68,
                0xcd, 0xdf, 0x88, 0x53, 0xbb, 0x2d, 0x55, 0x1b
            },
        },
    },
    {}
};
#define test_item_count (sizeof(test_item)/sizeof(cryptoST_testDetail_t))

/*************************************************************
 * Helper functions
 *************************************************************/

// Persistent storage reference for run-time-defined data sets.
static uint32_t * dynamicBuffer = NULL;

/*************************************************************
 * API handlers
 *************************************************************/
static const cryptoST_testDetail_t * firstTest(void)
{
    // Assume that #1 is not dynamically built
    return test_item;
}
static const cryptoST_testDetail_t * nextTest(const cryptoST_testDetail_t * old)
{
    // Assume that if the pointer is in range, that it is legitimate.
    if (old < test_item) 
        return NULL;
    old++; // repurpose: this is now "new"
    
    // We know that the final (illegitimate) entry has a null technique,
    // but we still need to check if "old" is _way_ out of bounds.
    if ((old >= &test_item[test_item_count])
            || (ET_NONE == old->technique))
        return NULL;
    else
    {
        /* The dynamic buffers must be filled.
         * We do each explicitly because it is more simple.
         *  */
        __conditional_software_breakpoint(old->rawData);
        if (&seq4k == old->rawData)
        {
            __conditional_software_breakpoint
                    (old->rawData->vector.length <= SIZE_PREALLOCATE);
            cryptoSTE_generateSequentialUINT32
                (dynamicBuffer, 0xFA123456, 
                    old->rawData->vector.length/sizeof(uint32_t));
            seq4k.vector.data = (void*)dynamicBuffer;
        }
        else if (&pr4k == old->rawData)
        {
            __conditional_software_breakpoint
                    (old->rawData->vector.length <= SIZE_PREALLOCATE);
            cryptoSTE_generatePseudorandomUINT32
                (dynamicBuffer, 0xFA123456, 
                    old->rawData->vector.length/sizeof(uint32_t));
            pr4k.vector.data = (void*)dynamicBuffer;
        }

        return old;
    }
}

static const char * openData(void)
{
    /* Allocate the largest required buffer now, because there
     * is no provision for return errors in first() or next().
     * If we can't get it now, we won't get it later, either.
     *  */
    dynamicBuffer = cryptoSTE_malloc(SIZE_PREALLOCATE); // bytes
    return dynamicBuffer? NULL :
        DATA_PACKAGE_NAME " malloc error " __BASE_FILE__ "(" BASE_LINE ")";
}

static const char * closeData(void)
{
    if (dynamicBuffer) cryptoSTE_free(dynamicBuffer);
    dynamicBuffer = NULL;
    return NULL;
}

/*************************************************************
 * Declaration of the test manager API
 * Obligatory entry points for executing a test
 *************************************************************/
cryptoST_testAPI_t const wolfSSL_aes_gcm =
{
    .name = "AES_" DATA_PACKAGE_NAME,
    .openData = openData,
    .firstTest = firstTest,
    .nextTest = nextTest,
    .closeData = closeData,
};

