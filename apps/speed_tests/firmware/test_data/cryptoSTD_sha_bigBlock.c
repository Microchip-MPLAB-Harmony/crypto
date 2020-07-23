/* cryptoSTD_sha256

  Crypto Speed Test Data File

  Company:
    Microchip Technology Inc.

  Description:
  This package provides standard test cases for SHA256 encryption by supplying
  various data buffers of 'zero' to demonstrate basic SHA operation.
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
#include "cryptoST/cryptoSTE_print.h"
#include "app.h" // for BASE_LINE
#include <wolfssl/wolfcrypt/hash.h>

#define DATA_PACKAGE_NAME "SHA_BB"

#if !defined(NO_SHA256)

/*************************************************************
 * Data limit definitions.
 *************************************************************/
#define ZERO_MIN    (44)
#if defined(__SAML11E16A__) // compiler pre-defined
#define ZERO_MAX    (512*3)
#else
#define ZERO_MAX    (5 * 1024)
#endif


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

static const cryptoST_testDetail_t test_item =
{
    .technique = ET_SHA_256,
    .mode = EM_NONE,
    .recommendedRepetitions = 1000,

    .source = __BASE_FILE__ "(" BASE_LINE ")",
    .pedigree = "Blocks of null data",
    .rawData = &satcZ,
    .io.hash.out.hash = { .data = sramBuffer32, .length = ASIZE(sramBuffer32) },
};

/*************************************************************
 * Helper functions
 *************************************************************/

/*************************************************************
 * API handlers
 *************************************************************/
static const char * openData_func(void)
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

static const char * closeData_func(void)
{
    if (satcZ.vector.data) 
        cryptoSTE_free((void*)satcZ.vector.data);
    satcZ.vector.data = NULL;
    return NULL;
}

static unsigned int zero_test = 0;
#else
#define closeData_func ((void*)0)
#define openData_func  ((void*)0)
#endif // !NO_SHA

#define test_item_count 1 //(sizeof(test_item)/sizeof(cryptoST_testDetail_t))
static const cryptoST_testDetail_t * nextTest(const cryptoST_testDetail_t * old)
{
#if !defined(NO_SHA256)
    // Need to check if "old" is out of bounds.
    if ((old != &test_item)
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
            __conditional_software_breakpoint(satcZ.vector.data);
            __conditional_software_breakpoint(old->io.hash.out.hash.data);
            __conditional_software_breakpoint(32 == old->io.hash.out.hash.length);

            // Let wolfCrypt compute the golden answer
            satcZ.vector.length = zero_test;
            wc_Sha256Hash(satcZ.vector.data,
                          satcZ.vector.length,
                          (uint8_t*)old->io.hash.out.hash.data);
        }
        return old;
    } while (0);
#endif
    return NULL;
}

static const cryptoST_testDetail_t * firstTest(void)
{
#if !defined(NO_SHA256)
    // Assume that #1 is not dynamically built
    zero_test = 0;
    if (satcZ.vector.data)
    {
        return nextTest(&test_item);
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
