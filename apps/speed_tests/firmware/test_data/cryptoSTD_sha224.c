/* cryptoSTD_sha224

  This package provides standard test cases for SHA224 encryption.
*/

#include <stdint.h>
#include "./cryptoSpeedTestData.h"
#include "cryptoST/cryptoST_print.h" // for BASE_LINE
#include "configuration.h"

#define CONST /* as nothing */
#define DATA_PACKAGE_NAME "SHA224"

/*************************************************************
 * Raw (input) data definitions.
 *************************************************************/
#if !defined(NO_SHA224) && !defined(NO_SHA256)
static const CPU_CHAR sha_all[] = "Microchip encrypt/decrypt test suite";
static const CPU_CHAR sha_all_description[] =
    "Duplicate of the test case in the Microchip encrypt/decrypt demo package.";

static CONST cryptoST_testVector_t abc_3 =
{
    .name = DATA_PACKAGE_NAME "sha224_abc_3",
    .source = sha_all,
    .description = sha_all_description,
    .vector.data = (uint8_t[]){0x61, 0x62, 0x63}, // "abc"
    .vector.length = 3, // 24 bits
};
static CONST cryptoST_testVector_t abc_56 =
{
    .name = DATA_PACKAGE_NAME "sha224_abc_56",
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
#if !defined(NO_SHA224) && !defined(NO_SHA256)
    {
        .technique = ET_SHA_224,
        .mode = EM_NONE,
        .recommendedRepetitions = 1000,

        .source = __BASE_FILE__ "(" BASE_LINE ")",
        .pedigree = sha_all,
        .rawData = &abc_3,
        .goldenCipher = {
            .length = 28,
            .data = (uint8_t[]){ "\x23\x09\x7D\x22"
                                 "\x34\x05\xD8\x22"
                                 "\x86\x42\xA4\x77"
                                 "\xBD\xA2\x55\xB3"
                                 "\x2A\xAD\xBC\xE4"
                                 "\xBD\xA0\xB3\xF7"
                                 "\xE3\x6C\x9D\xA7",
            },
        },
    },
    {
        .technique = ET_SHA_224,
        .mode = EM_NONE,
        .recommendedRepetitions = 1000,

        .source = __BASE_FILE__ "(" BASE_LINE ")",
        .pedigree = sha_all,
        .rawData = &abc_56,
        .goldenCipher = {
            .length = 28,
            .data = (uint8_t[]){ "\x75\x38\x8B\x16"
                                 "\x51\x27\x76\xCC"
                                 "\x5D\xBA\x5D\xA1"
                                 "\xFD\x89\x01\x50"
                                 "\xB0\xC6\x45\x5C"
                                 "\xB4\xF5\x8B\x19"
                                 "\x52\x52\x25\x25",
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
cryptoST_testAPI_t const microchip_sha224 =
{
    .name = "SHA_" DATA_PACKAGE_NAME,
    .openData = openData_func,
    .firstTest = firstTest,
    .nextTest = nextTest,
    .closeData = closeData_func,
};

