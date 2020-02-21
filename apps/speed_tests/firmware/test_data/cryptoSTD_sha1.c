/* cryptoSTD_sha1

  This package provides standard test cases for SHA1 encryption.
*/

#include <stdint.h>
#include "./cryptoSpeedTestData.h"
#include "cryptoST/cryptoST_print.h" // for BASE_LINE
#include "configuration.h"

#define CONST /* as nothing */
#define DATA_PACKAGE_NAME "SHA1"

/*************************************************************
 * Raw (input) data definitions.
 *************************************************************/
#if !defined(NO_SHA) // SHA1
static const CPU_CHAR sha_all[] = // "Microchip encrypt/decrypt test suite";
    "NIST FIPS 180-2 - Secure Hash Standard test cases (SHA1.pdf).";
static const CPU_CHAR sha_all_description[] =
    "NIST FIPS 180-2 - Secure Hash Standard test cases (SHA1.pdf).";

static CONST cryptoST_testVector_t abc_3 =
{
    .name = DATA_PACKAGE_NAME "sha1_abc_3",
    .source = sha_all,
    .description = sha_all_description,
    .vector.data = (uint8_t[]){0x61, 0x62, 0x63}, // "abc"
    .vector.length = 3, // 24 bits
};
static CONST cryptoST_testVector_t abc_56 =
{
    .name = DATA_PACKAGE_NAME "sha1_abc_56",
    .source = sha_all,
    .description = sha_all_description,
    .vector.data = (uint8_t[]){
        "abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq"},
    .vector.length = 56, // 448 bits
};
#endif // !NO_SHA

/*************************************************************
 * Golden data definitions.
 *************************************************************/
static __attribute__((unused)) CONST cryptoST_testDetail_t test_item[] =
{
#if !defined(NO_SHA) // SHA1
    {
        .technique = ET_SHA_128,
        .mode = EM_NONE,
        .recommendedRepetitions = 1000,

        .source = __BASE_FILE__ "(" BASE_LINE ")",
        .pedigree = sha_all,
        .rawData = &abc_3,
        .goldenCipher = {
            .length = 20,
            .data = (uint8_t[]){ "\xA9\x99\x3E\x36" 
                                 "\x47\x06\x81\x6A" 
                                 "\xBA\x3E\x25\x71"
                                 "\x78\x50\xC2\x6C"
                                 "\x9C\xD0\xD8\x9D"
            },
        },
    },
    {
        .technique = ET_SHA_128,
        .mode = EM_NONE,
        .recommendedRepetitions = 1000,

        .source = __BASE_FILE__ "(" BASE_LINE ")",
        .pedigree = sha_all,
        .rawData = &abc_56,
        .goldenCipher = {
            .length = 20,
            .data = (uint8_t[]){ "\x84\x98\x3E\x44" 
                                 "\x1C\x3B\xD2\x6E"
                                 "\xBA\xAE\x4A\xA1"
                                 "\xF9\x51\x29\xE5"
                                 "\xE5\x46\x70\xF1"
            },
        },
    },
#endif // !NO_SHA
    {}
};
#define test_item_count (sizeof(test_item)/sizeof(cryptoST_testDetail_t))

/*************************************************************
 * Helper functions
 *************************************************************/

/*************************************************************
 * API handlers
 *************************************************************/
static cryptoST_testDetail_t * firstTest(void)
{
    __NOP();
    return &test_item[0];
}

static cryptoST_testDetail_t * nextTest(cryptoST_testDetail_t * old)
{
    __NOP();
    // Assume that if the pointer is in range, that it is legitimate.
    if (old < test_item) 
        ;
    
    // We know that the final (illegitimate) entry has a null technique,
    // but we still need to check if "old" is _way_ out of bounds.
    else if ((++old >= &test_item[test_item_count])
            || (ET_NONE == old->technique))
        ;
    else return old;

    return NULL;
}

#define openData_func      NULL
#define closeData_func     NULL

/*************************************************************
 * Declaration of the test manager API
 * Obligatory entry points for executing a test
 *************************************************************/
cryptoST_testAPI_t const microchip_sha1 =
{
    .name = "SHA_" DATA_PACKAGE_NAME,
    .openData = openData_func,
    .firstTest = firstTest,
    .nextTest = nextTest,
    .closeData = closeData_func,
};

