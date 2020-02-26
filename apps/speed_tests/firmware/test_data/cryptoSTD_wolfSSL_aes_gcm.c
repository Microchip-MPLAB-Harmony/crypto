/* cryptoSTV_wolfSSL_AES_GCM

   This package transliterates test data from the wolfSSL test.c file.
   Specifically the data for the AES tests. In addition, large random and 
 * sequential data sets are defined.
*/

#include <stdint.h>
#include "./cryptoSpeedTestData.h"
#include "cryptoST/cryptoSTE_generate.h"
#include "cryptoST/cryptoSTE_malloc.h"
#include "cryptoST/cryptoST_print.h" // for BASE_LINE

#define CONST /* as nothing */
#define DATA_PACKAGE_NAME "GCM"

const CPU_CHAR AES_GCM_default_description[] = {
        "Vectors are from NIST SP 800-38D "
        "using 12 byte IV and 16 or less byte AAD "
        "https://csrc.nist.gov/Projects/Cryptographic-Algorithm-Validation-Program/CAVP-TESTING-BLOCK-CIPHER-MODES" };

/*************************************************************
 * Raw (input) data definitions providing small-block constants.
 *************************************************************/
static CONST cryptoST_testVector_t dt1 =
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
static CONST cryptoST_testVector_t dt2 =
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
static CONST cryptoST_testVector_t dt3 =
{
    .name = DATA_PACKAGE_NAME "_NULL",
    .source = "/wolfssl/wolfcrypt/test/test.c line 7261",
    .description = AES_GCM_default_description,
    .vector.data = NULL, // legal for GCM
    .vector.length = 0,
};

/*************************************************************
 * Raw (input) data definitions for run-time defined
 * sequential and random data sets having large block sizes.
 *************************************************************/
#define SIZE4K     (3072)
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
static CONST cryptoST_testDetail_t test_item[] =
{
    {
        .technique = ET_AES_GCM,
        .mode = EM_NONE,
        .recommendedRepetitions = 1000,

        .source = __BASE_FILE__ "(" BASE_LINE ")",
        .pedigree = "/wolfssl/wolfcrypt/test/test.c line 7171",
        .rawData = &dt1,
        .key = &(cryptoST_testData_t){ // test.c 7171
            .length = 16,
            .data = (const uint8_t[]){
                0x29, 0x8e, 0xfa, 0x1c, 0xcf, 0x29, 0xcf, 0x62,
                0xae, 0x68, 0x24, 0xbf, 0xc1, 0x95, 0x57, 0xfc
            },
        },
        .ivNonce = { // test.c 7177
            .length = 12,
            .data = (uint8_t[]){
                0x6f, 0x58, 0xa9, 0x3f, 0xe1, 0xd2, 0x07, 0xfa,
                0xe4, 0xed, 0x2f, 0x6d
            },
        },
        .additionalAuthData = { // test.c 7188
            .length = 16,
            .data = (uint8_t[]){
                0x02, 0x1f, 0xaf, 0xd2, 0x38, 0x46, 0x39, 0x73,
                0xff, 0xe8, 0x02, 0x56, 0xe5, 0xb1, 0xc6, 0xb1
            },
        },
        .goldenCipher = { // test.c 7183
            .length = 32,
            .data = (uint8_t[]){
                0xdf, 0xce, 0x4e, 0x9c, 0xd2, 0x91, 0x10, 0x3d,
                0x7f, 0xe4, 0xe6, 0x33, 0x51, 0xd9, 0xe7, 0x9d,
                0x3d, 0xfd, 0x39, 0x1e, 0x32, 0x67, 0x10, 0x46,
                0x58, 0x21, 0x2d, 0xa9, 0x65, 0x21, 0xb7, 0xdb
            }
        },
        .goldenTag = { // test.c 7200
            .length = 16,
            .data = (uint8_t[]){
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
        .key = &(cryptoST_testData_t){ // test.c 7207
            .length = 16,
            .data = (const uint8_t[]){
                0x01, 0x6d, 0xbb, 0x38, 0xda, 0xa7, 0x6d, 0xfe,
                0x7d, 0xa3, 0x84, 0xeb, 0xf1, 0x24, 0x03, 0x64
            },
        },
        .ivNonce = { // test.c 7212
            .length = 12,
            .data = (uint8_t[]){
                0x07, 0x93, 0xef, 0x3a, 0xda, 0x78, 0x2f, 0x78,
                0xc9, 0x8a, 0xff, 0xe3
            },
        },
        .additionalAuthData = { // test.c 7256
            .length = 0,
            .data = NULL,
        },
        .goldenCipher = { // test.c 7221
            .length = 16,
            .data = (uint8_t[]){
                0x60, 0x9a, 0xa3, 0xf4, 0x54, 0x1b, 0xc0, 0xfe,
                0x99, 0x31, 0xda, 0xad, 0x2e, 0xe1, 0x5d, 0x0c
            }
        },
        .goldenTag = { // test.c 7226
            .length = 16,
            .data = (uint8_t[]){
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
        .key = &(cryptoST_testData_t){ // test.c 7231
            .length = 16,
            .data = (const uint8_t[]){
                0xb0, 0x1e, 0x45, 0xcc, 0x30, 0x88, 0xaa, 0xba,
                0x9f, 0xa4, 0x3d, 0x81, 0xd4, 0x81, 0x82, 0x3f
            },
        },
        .ivNonce = { // test.c 7236
            .length = 12,
            .data = (uint8_t[]){
                0x5a, 0x2c, 0x4a, 0x66, 0x46, 0x87, 0x13, 0x45,
                0x6a, 0x4b, 0xd5, 0xe1
            },
        },
        .additionalAuthData = { // test.c 7261
            .length = 0,
            .data = (uint8_t[]){
                0x60, 0x9a, 0xa3, 0xf4, 0x54, 0x1b, 0xc0, 0xfe,
                0x99, 0x31, 0xda, 0xad, 0x2e, 0xe1, 0x5d, 0x0c
            },
        },
        .goldenCipher = { // test.c 7261
            .length = 0,
            .data = NULL,
        },
        .goldenTag = { // test.c 7241
            .length = 12,
            .data = (uint8_t[]){
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
        .key = &(cryptoST_testData_t){ // test.c 7231
            .length = 16,
            .data = (const uint8_t[]){
                0xb0, 0x1e, 0x45, 0xcc, 0x30, 0x88, 0xaa, 0xba,
                0x9f, 0xa4, 0x3d, 0x81, 0xd4, 0x81, 0x82, 0x3f
            },
        },
        .ivNonce = { // test.c 7236
            .length = 12,
            .data = (uint8_t[]){
                0x5a, 0x2c, 0x4a, 0x66, 0x46, 0x87, 0x13, 0x45,
                0x6a, 0x4b, 0xd5, 0xe1
            },
        },
        .additionalAuthData = { // test.c 7177
            .length = 16,
            .data = (uint8_t[]){
                0x33, 0xaf, 0xec, 0x59, 0xc4, 0x5b, 0xaf, 0x68,
                0x9a, 0x5e, 0x1b, 0x13, 0xae, 0x42, 0x36, 0x19
            },
        },
        .goldenCipher = { // no data
            .length = 0,
            .data = NULL,
        },
        .goldenTag = { // no data
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
        .key = &(cryptoST_testData_t){ // test.c 7231
            .length = 16,
            .data = (const uint8_t[]){
                0xb0, 0x1e, 0x45, 0xcc, 0x30, 0x88, 0xaa, 0xba,
                0x9f, 0xa4, 0x3d, 0x81, 0xd4, 0x81, 0x82, 0x3f
            },
        },
        .ivNonce = { // test.c 7236
            .length = 12,
            .data = (uint8_t[]){
                0x5a, 0x2c, 0x4a, 0x66, 0x46, 0x87, 0x13, 0x45,
                0x6a, 0x4b, 0xd5, 0xe1
            },
        },
        .additionalAuthData = { // test.c 7177
            .length = 16,
            .data = (uint8_t[]){
                0x33, 0xaf, 0xec, 0x59, 0xc4, 0x5b, 0xaf, 0x68,
                0x9a, 0x5e, 0x1b, 0x13, 0xae, 0x42, 0x36, 0x19
            },
        },
        .goldenCipher = { // no data
            .length = 0,
            .data = NULL,
        },
        .goldenTag = { // no data
            .length = 0,
            .data = NULL,
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
static cryptoST_testDetail_t * firstTest(void)
{
    // Assume that #1 is not dynamically built
    return test_item;
}
static cryptoST_testDetail_t * nextTest(cryptoST_testDetail_t * old)
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
            old->rawData->vector.data = (void*)dynamicBuffer;
        }
        else if (&pr4k == old->rawData)
        {
            __conditional_software_breakpoint
                    (old->rawData->vector.length <= SIZE_PREALLOCATE);
            cryptoSTE_generatePseudorandomUINT32
                (dynamicBuffer, 0xFA123456, 
                    old->rawData->vector.length/sizeof(uint32_t));
            old->rawData->vector.data = (void*)dynamicBuffer;
        }

        return old;
    }
}

static char * openData(void)
{
    /* Allocate the largest required buffer now, because there
     * is no provision for return errors in first() or next().
     * If we can't get it now, we won't get it later, either.
     *  */
    dynamicBuffer = cryptoSTE_malloc(SIZE_PREALLOCATE); // bytes
    return dynamicBuffer? NULL :
        DATA_PACKAGE_NAME " malloc error " __BASE_FILE__ "(" BASE_LINE ")";
}

static char * closeData(void)
{
    if (dynamicBuffer) cryptoSTE_free(dynamicBuffer);
    dynamicBuffer = NULL;
    return NULL;
}

/*************************************************************
 * Declaration of the test manager API
 * Obligatory entry points for executing a test
 *************************************************************/
#include "cryptoSTD_wolfSSL_aes_gcm.h"
cryptoST_testAPI_t const wolfSSL_aes_gcm =
{
    .name = "AES_" DATA_PACKAGE_NAME,
    .openData = openData,
    .firstTest = firstTest,
    .nextTest = nextTest,
    .closeData = closeData,
};

