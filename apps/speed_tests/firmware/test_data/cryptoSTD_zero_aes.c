/* cryptoSTV_zero_aes.c

   This package transliterates test data from the wolfSSL test.c file.
   Specifically the data for the AES192 tests.
*/

#include <stddef.h>
#include <stdint.h>

#include "./cryptoSpeedTestData.h"
#include "cryptoST/cryptoST_print.h" // for BASE_LINE
#include "cryptoST/cryptoSTE_malloc.h"

#ifdef HAVE_CONFIG_H
    #include <config.h>
#else
#include "configuration.h"
#endif
#include <wolfssl/wolfcrypt/settings.h>
#define DATA_PACKAGE_NAME   "AES_NULL"

#define CONST /* as nothing */
#define ALIGN4 __attribute__((aligned(4)))

#if defined(WOLFSSL_AES_128) \
 || defined(WOLFSSL_AES_192) \
 || defined(WOLFSSL_AES_256)

static const char source[] = "Microchip speed-test suite";

static cryptoST_testVector_t null_vector =
{
    .name = "ZERO_AES",
    .source = source,
    .description = "Null data to encrypt/decrypt",
    .vector.data = 0, // malloc this later
    .vector.length = 0,
};

static cryptoST_testDetail_t test_item =
{
    .technique = ET_AES_128, // not const
    .mode = EM_CFB,          // not const
    .recommendedRepetitions = 1000,

    .source = __BASE_FILE__ "(" BASE_LINE ")",
    .pedigree = source,
    .rawData = &null_vector,
    // .goldenCipher -- no cipher text
    .in.sym.key = {
        .length = AES128_KEY_SIZE/8, // =16
        .data = (ALIGN4 const uint8_t*) // at least 32 bytes
            "Microchip null data test keys for all.",
    },
    .in.sym.ivNonce = {
        .length = 16,
        .data = (ALIGN4 const uint8_t[]){
            0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,
            0x08,0x09,0x0a,0x0b,0x0c,0x0d,0x0e,0x0f
        }
    },
};

/*************************************************************
 * API handlers
 *************************************************************/
#define SIZE_PREALLOCATE    64

uint test_step = 0;
static cryptoST_testDetail_t * nextTest(cryptoST_testDetail_t * old)
{
    // Assume that if its in range, that it is legitimate.
    if (old != &test_item) 
        return NULL;

    test_step++;
    switch(test_step) // TODO: make this better
    {
    case 1:
        test_item.technique = ET_AES_128;
        test_item.mode = EM_CFB;
        test_item.in.sym.key.length = 128/8;
        null_vector.vector.length = 16;
        break;
    case 2:
        test_item.technique = ET_AES_192;
        test_item.mode = EM_CFB;
        test_item.in.sym.key.length = 192/8;
        null_vector.vector.length = 16;
        break;
    case 3:
        test_item.technique = ET_AES_256;
        test_item.mode = EM_CFB;
        test_item.in.sym.key.length = 256/8;
        null_vector.vector.length = 16;
        break;
    case 4:
        test_item.technique = ET_AES_128;
        test_item.mode = EM_CFB;
        test_item.in.sym.key.length = 128/8;
        null_vector.vector.length = SIZE_PREALLOCATE;
        break;
    case 5:
        test_item.technique = ET_AES_192;
        test_item.mode = EM_CFB;
        test_item.in.sym.key.length = 192/8;
        null_vector.vector.length = SIZE_PREALLOCATE;
        break;
    case 6:
        test_item.technique = ET_AES_256;
        test_item.mode = EM_CFB;
        test_item.in.sym.key.length = 256/8;
        null_vector.vector.length = SIZE_PREALLOCATE;
        break;
    default:
        return NULL;
    }
    return old;
}
#else
static cryptoST_testDetail_t * nextTest(cryptoST_testDetail_t * old)
{ return NULL; }
#define test_item (*((void*)0))
#endif

static cryptoST_testDetail_t * firstTest(void)
{ return nextTest(&test_item); }

static char * openData(void)
{
    test_step = 0;

    /* Allocate the largest required buffer now, because there
     * is no provision for return errors in first() or next().
     * If we can't get it now, we won't get it later, either.
     *  */
    null_vector.vector.data = cryptoSTE_malloc(SIZE_PREALLOCATE); // bytes
    if (NULL == null_vector.vector.data)
        return DATA_PACKAGE_NAME " malloc error " __BASE_FILE__ "(" BASE_LINE ")";
    else
    {
        memset((uint8_t*)null_vector.vector.data,0,SIZE_PREALLOCATE);
        return NULL; // no error
    }
}

static char * closeData(void)
{
    if (null_vector.vector.data)
        cryptoSTE_free((uint8_t*)null_vector.vector.data);
    null_vector.vector.data = NULL;
    return NULL;
}

/*************************************************************
 * Declaration of the test manager API
 * Obligatory entry points for executing a test
 *************************************************************/
#include "cryptoSTD_zero_aes.h"
cryptoST_testAPI_t const microchip_zero_aes =
{
    .name = DATA_PACKAGE_NAME,
    .openData = openData,
    .firstTest = firstTest,
    .nextTest = nextTest,
    .closeData = closeData,
};

