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
#define DATA_PACKAGE_NAME "SHA_BB"

#define DO_LARGE_ZERO_HASH  0

#if !defined(NO_SHA256)

/*************************************************************
 * Raw (input) data definitions.
 *************************************************************/

/*************************************************************
 * Raw (input) data definitions for run-time defined
 * sequential and random data sets having large block sizes.
 *************************************************************/
static cryptoST_testVector_t satcZ =
{
    .name = DATA_PACKAGE_NAME "_NULL",
    .source = "Microchip",
    .description = "Pseudo-generated data sets of various sizes",
    .vector.data = NULL, // fill this in later using malloc
    .vector.length = 0,  // and this, too
};

/*************************************************************
 * Golden data definitions.
 *************************************************************/
static uint8_t sramBuffer32[32] = { 0 };
#define ASIZE(a) ((sizeof(a)/sizeof(a[0])))

static CONST cryptoST_testDetail_t test_item =
{
    .technique = ET_SHA_256,
    .mode = EM_NONE,
    .recommendedRepetitions = 1000,

    .source = __BASE_FILE__ "(" BASE_LINE ")",
    .pedigree = "Blocks of null data",
    .rawData = &satcZ,
    .goldenCipher = { .data = sramBuffer32, .length = ASIZE(sramBuffer32) },
};

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
static unsigned int zero_test = 0;

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
#define closeData_func ((void*)0)
#define openData_func  ((void*)0)
#endif // !NO_SHA

#define test_item_count 1 //(sizeof(test_item)/sizeof(cryptoST_testDetail_t))
static cryptoST_testDetail_t * nextTest(cryptoST_testDetail_t * old)
{
    __NOP();

#if !defined(NO_SHA256)
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

static cryptoST_testDetail_t * firstTest(void)
{
    __NOP();
    
#if !defined(NO_SHA256)
    // Assume that #1 is not dynamically built
    zero_test = 0;
    if (satcZ.vector.data)
    {
        return nextTest(&test_item[0]);
    }
    
    // If we get here the data vector is not initialized correctly
    // (e.g., the malloc failed), but main kept going.
    __conditional_software_breakpoint(0);
#endif
    return NULL;
}

/*************************************************************
 * Declaration of the test manager API
 * Obligatory entry points for executing a test
 *************************************************************/
cryptoST_testAPI_t const microchip_sha_bigBlock =
{
    .name = DATA_PACKAGE_NAME,
    .openData = openData_func,
    .firstTest = firstTest,
    .nextTest = nextTest,
    .closeData = closeData_func,
};
