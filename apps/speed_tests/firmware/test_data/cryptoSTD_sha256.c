/* cryptoSTD_sha256

  This package provides standard test cases for SHA256 encryption.
*/

#include <stdint.h>
#include "./cryptoSpeedTestData.h"
#include "cryptoST/cryptoSTE_generate.h"
#include "cryptoST/cryptoSTE_malloc.h"
#include "cryptoST/cryptoST_print.h"
#include "app.h" // for BASE_LINE
#include <wolfssl/wolfcrypt/hash.h>

#define CONST /* as nothing */
#define DATA_PACKAGE_NAME "SHA256"

#define DO_LARGE_ZERO_HASH  0

#if 0
static const CPU_CHAR default_description[] = {
    "For SHA256 exercise with data blocks of various lengths. "
    "Consult the pedigree information for details."};
#endif

/*************************************************************
 * Raw (input) data definitions.
 *************************************************************/
#if !defined(NO_SHA256)
static const CPU_CHAR sha_all[] = 
    "http://csrc.nist.gov/groups/ST/toolkit/documents/Examples/SHA_All.pdf";
static const CPU_CHAR url1[] = "https://www.di-mgt.com.au/sha_testvectors.html";
static const CPU_CHAR sha_all_description[] =
    "NIST Computer Security Division standard test cases.";

static CONST cryptoST_testVector_t satabc =
{
    .name = DATA_PACKAGE_NAME "_satabc",
    .source = sha_all,
    .description = sha_all_description,
    .vector.data = (const uint8_t[]){0x61, 0x62, 0x63}, // "abc"
    .vector.length = 3,
};
static CONST cryptoST_testVector_t satc448 =
{
    .name = DATA_PACKAGE_NAME "_satc448",
    .source = sha_all,
    .description = sha_all_description,
    .vector.data = (const uint8_t[]){
        "abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq"},
    .vector.length = 56, // 448 bits
};
static CONST cryptoST_testVector_t satc896 =
{
    .name = DATA_PACKAGE_NAME "_NULL",
    .source = url1,
    .description = sha_all_description,
    .vector.data = (const uint8_t[]){
        "abcdefghbcdefghicdefghijdefghijkefghijklfghijklmghijklmnhi"
        "jklmnoijklmnopjklmnopqklmnopqrlmnopqrsmnopqrstnopqrstu"},
    .vector.length = 112, // 896 bits
};

/*************************************************************
 * Raw (input) data definitions for run-time defined
 * sequential and random data sets having large block sizes.
 *************************************************************/
static cryptoST_testVector_t satcZ =
{
    .name = DATA_PACKAGE_NAME "_NULL",
    .source = sha_all,
    .description = sha_all_description,
    .vector.data = NULL, // fill this in later using malloc
    .vector.length = 0,  // and this, too
};
#endif // !NO_SHA

/*************************************************************
 * Golden data definitions.
 *************************************************************/
static uint8_t sramBuffer32[32] = { 0 };
#define ASIZE(a) ((sizeof(a)/sizeof(a[0])))
static __attribute__((unused)) CONST cryptoST_testDetail_t test_item[] =
{
#if !defined(NO_SHA256)
    {
        .technique = ET_SHA_256,
        .mode = EM_NONE,
        .recommendedRepetitions = 1000,

        .source = __BASE_FILE__ "(" BASE_LINE ")",
        .pedigree = sha_all,
        .rawData = &satabc,
        .goldenCipher = {
            .length = 32,
            .data = (const uint8_t[]){
                0xba, 0x78, 0x16, 0xbf, 0x8f, 0x01, 0xcf, 0xea, 
                0x41, 0x41, 0x40, 0xde, 0x5d, 0xae, 0x22, 0x23,
                0xb0, 0x03, 0x61, 0xa3, 0x96, 0x17, 0x7a, 0x9c,
                0xb4, 0x10, 0xff, 0x61, 0xf2, 0x00, 0x15, 0xad
                // 0xba7816bf, 0x8f01cfea, 0x414140de, 0x5dae2223, 
                // 0xb00361a3, 0x96177a9c, 0xb410ff61, 0xf20015ad
            },
        },
    },
    {
        .technique = ET_SHA_256,
        .mode = EM_NONE,
        .recommendedRepetitions = 1000,

        .source = __BASE_FILE__ "(" BASE_LINE ")",
        .pedigree = sha_all,
        .rawData = &satc448,
        .goldenCipher = {
            .length = 32,
            .data = (const uint8_t[]){
                0x24, 0x8d, 0x6a, 0x61, 0xd2, 0x06, 0x38, 0xb8, 
                0xe5, 0xc0, 0x26, 0x93, 0x0c, 0x3e, 0x60, 0x39,
                0xa3, 0x3c, 0xe4, 0x59, 0x64, 0xff, 0x21, 0x67,
                0xf6, 0xec, 0xed, 0xd4, 0x19, 0xdb, 0x06, 0xc1 
                // 0x248d6a61, 0xd20638b8, 0xe5c02693, 0x0c3e6039, 
                // 0xa33ce459, 0x64ff2167, 0xf6ecedd4, 0x19db06c1
            },
        },
    },
    {
        .technique = ET_SHA_256,
        .mode = EM_NONE,
        .recommendedRepetitions = 1000,

        .source = __BASE_FILE__ "(" BASE_LINE ")",
        .pedigree = sha_all,
        .rawData = &satc896,
        .goldenCipher = {
            .length = 32,
            .data = (const uint8_t[]){
                0xcf, 0x5b, 0x16, 0xa7, 0x78, 0xaf, 0x83, 0x80,
                0x03, 0x6c, 0xe5, 0x9e, 0x7b, 0x04, 0x92, 0x37,
                0x0b, 0x24, 0x9b, 0x11, 0xe8, 0xf0, 0x7a, 0x51,
                0xaf, 0xac, 0x45, 0x03, 0x7a, 0xfe, 0xe9, 0xd1
                // 0xcf5b16a7, 0x78af8380, 0x036ce59e, 0x7b049237, 
                // 0x0b249b11, 0xe8f07a51, 0xafac4503, 0x7afee9d1
            },
        },
    },
    {
        .technique = ET_SHA_256,
        .mode = EM_NONE,
        .recommendedRepetitions = 1000,

        .source = __BASE_FILE__ "(" BASE_LINE ")",
        .pedigree = "Blocks of null data",
        .rawData = &satcZ,
        .goldenCipher = { .data = sramBuffer32, .length = ASIZE(sramBuffer32) },
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
#define ZERO_MIN    (44)
#if defined(__SAML11E16A__) // compiler pre-defined
#define ZERO_MAX    (512*3)
#else
#define ZERO_MAX    (5 * 1024)
#endif
static __attribute__((unused)) unsigned int zero_test = 0;

static cryptoST_testDetail_t * firstTest(void)
{
    __NOP();
    
#if !defined(NO_SHA256)
    // Assume that #1 is not dynamically built
    zero_test = 0;
    if (satcZ.vector.data)
    {
        return &test_item[0];
    }
    
    // If we get here the data vector is not initialized correctly
    // (e.g., the malloc failed), but main kept going.
    __conditional_software_breakpoint(0);
#endif 
    return NULL;
}
static cryptoST_testDetail_t * nextTest(cryptoST_testDetail_t * old)
{
#if !defined(NO_SHA256)
    __NOP();
    // Assume that if the pointer is in range, that it is legitimate.
    if (old < test_item) 
        ;
    
    // We know that the final (illegitimate) entry has a null technique,
    // but we still need to check if "old" is _way_ out of bounds.
    else if ((old >= &test_item[test_item_count])
            || (ET_NONE == old->technique))
        ;
    else do
    {
        // If we are not already to the magic block, move forward
        if (old->rawData != &satcZ)
            ++old; // repurpose: this is now "new"
        
        // If we are now at the magic block, generate a zero-filled dataset
        if (old->rawData == &satcZ)
        {
            __NOP();
#if DO_LARGE_ZERO_HASH
            old = (void*)0;
#else
            // Note that this is bogus if we've overloaded the WC entry point.
            // Produce a zero-filled block of some length
            __conditional_software_breakpoint(old->rawData);
            cryptoST_testVector_t * raw = old->rawData;

            // This test is about verification of mechanics when the
            // buffer size is near the cross-over from 1 block to 2.
            if (0 == zero_test)
                zero_test = ZERO_MIN;  // get started
            else if (zero_test >= (3*512)) // bigger is optional
                zero_test += 1000;
            else if (zero_test >= 512) // WC anomaly observed at 475 bytes
                zero_test += 25;
            else if (zero_test == 64)   // covers 1-2
                zero_test = 460;       // cover 8 blocks up to 9 blocks
            else
                zero_test++;

            // Make sure we fit in the buffer
            if (zero_test >= ZERO_MAX)
                break;

            // Demonstrate that we are properly configured
            __conditional_software_breakpoint(raw->vector.data);
            __conditional_software_breakpoint(old->goldenCipher.data);
            __conditional_software_breakpoint(32 == old->goldenCipher.length);

            // Let wolfCrypt compute the golden answer
            raw->vector.length = zero_test;
            wc_Sha256Hash(raw->vector.data,
                          raw->vector.length,
                          (uint8_t*)old->goldenCipher.data);
#endif
        }
        return old;
    } while (0);
#endif
    return NULL;
}

#if !defined(NO_SHA256)
static char * openData_func(void)
{
    /* Allocate the largest required buffer now, because there
     * is no provision for return errors in first() or next().
     * If we can't get it now, we won't get it later, either.
     *  */
    satcZ.vector.data = cryptoSTE_malloc(ZERO_MAX);
    if (satcZ.vector.data)
    {
        memset((uint8_t*)satcZ.vector.data,0,ZERO_MAX);
        return NULL;
    }
    else return 
        DATA_PACKAGE_NAME " malloc error " __BASE_FILE__ "(" BASE_LINE ")";
}

static char * closeData_func(void)
{
    if (satcZ.vector.data) 
        cryptoSTE_free((void*)satcZ.vector.data);
    satcZ.vector.data = NULL;
    return NULL;
}
#else
#define openData_func      NULL
#define closeData_func     NULL
#endif

/*************************************************************
 * Declaration of the test manager API
 * Obligatory entry points for executing a test
 *************************************************************/
cryptoST_testAPI_t const microchip_sha256 =
{
    .name = "SHA_" DATA_PACKAGE_NAME,
    .openData = openData_func,
    .firstTest = firstTest,
    .nextTest = nextTest,
    .closeData = closeData_func,
};

