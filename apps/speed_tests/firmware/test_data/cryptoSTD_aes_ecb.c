/* cryptoSTD_aes_ecb

  This package provides standard test cases for AES ECB encryption.
*/

#include <assert.h>
#include "./cryptoSpeedTestData.h"
#include "cryptoST/cryptoST_print.h" // for BASE_LINE
#include "cryptoST/cryptoSTE_generate.h"
#include "cryptoST/cryptoSTE_malloc.h"
#include "configuration.h"

#define CONST /* as nothing */
#define DATA_PACKAGE_NAME "AES_ECB"
#define ALIGN4 __attribute__((aligned(4)))
#define DATA_CHAR ALIGN4 const uint8_t

#if defined(__SAML11E16A__) // known to have not-enough memory
#define TEST_SIZE_MAX (2*1024) // must power-of-2
#else // everybodyelse
#define TEST_SIZE_MAX (32*1024) // must power-of-2
#endif

#if !defined(__NOP)
#define __NOP() do{ __asm__ __volatile__ ("nop"); }while(0)
#endif

/*************************************************************
 * Raw (input) data definitions.
 *************************************************************/
#if !defined(NO_AES)
static const CPU_CHAR description[] = 
    "Microchip encrypt/decrypt test suite for large block operations";

static cryptoST_testVector_t softData =
{
    .name = DATA_PACKAGE_NAME "_bigBlocks",
    .source = "Micrchip applications",
    .description = description,
    .vector.data = NULL, // for now
    .vector.length = 0
};
#endif

/*************************************************************
 * Golden data definitions.
 *************************************************************/
static cryptoST_testDetail_t test_item = // one and only
{
    .technique = ET_AES_128,
    .mode = EM_ECB,
    .recommendedRepetitions = 1000,

    .source = __BASE_FILE__,
    .pedigree = description,
    .rawData = &softData,
    .io.sym.out.cipher = {
        .data = ((void*)0), // fill in later
        .length = 16,
    },
    .io.sym.in.key = 
        { .data = (DATA_CHAR*)"abcdefghijklmnop", // 128b = 16B
          .length = 16 },
};

/*************************************************************
 * Helper functions
 *************************************************************/

/*************************************************************
 * API handlers
 *************************************************************/
static size_t testSize = 0;
static const cryptoST_testDetail_t * nextTest(const cryptoST_testDetail_t * old)
{
    __NOP();

    // Validate that we have received the correct pointer.
    if (old != &test_item) 
        return NULL;
    else if (testSize > 18000)
        return NULL;
    else if (testSize > 12000)
        testSize = 18 * 1024;
    else if (testSize > 8000)
        testSize = 12 * 1024;
    else if (testSize > 7000)
        testSize = 8 * 1024;
    else if (testSize > 5000)
        testSize = 7 * 1024;
    else if (testSize > 2000)
        testSize = 5 * 1024;
    else if (testSize > 1000)
        testSize = 2 * 1024;
    else testSize = 1024;

    if (testSize > TEST_SIZE_MAX)
        return NULL;
    else
    {
        softData.vector.length = testSize;
        __conditional_software_breakpoint
            (!cryptoSTE_generatePseudorandomUINT32
                ((uint32_t*)softData.vector.data, 
                    0x31415927, testSize/sizeof(uint32_t)));
    }
    return old;
}

static const cryptoST_testDetail_t * firstTest(void)
{
    __NOP();
    testSize = 0;
    return nextTest(&test_item);
}

#if !defined(NO_AES)
static char * openData_func(void)
{
    /* Allocate the largest required buffer now, because there
     * is no provision for return errors in first() or next().
     * If we can't get it now, we won't get it later, either.
     *  */
    softData.vector.data = cryptoSTE_malloc(TEST_SIZE_MAX);
    if (softData.vector.data)
    {
        memset((uint8_t*)softData.vector.data,0,TEST_SIZE_MAX);
        return NULL;
    }
    else return 
        DATA_PACKAGE_NAME " malloc error " __BASE_FILE__ "(" BASE_LINE ")";
}

static char * closeData_func(void)
{
    if (softData.vector.data) 
        cryptoSTE_free((void*)softData.vector.data);
    softData.vector.data = NULL;
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
cryptoST_testAPI_t const microchip_aes_ecb =
{
    .name = DATA_PACKAGE_NAME,
    .openData = openData_func,
    .firstTest = firstTest,
    .nextTest = nextTest,
    .closeData = closeData_func,
};

