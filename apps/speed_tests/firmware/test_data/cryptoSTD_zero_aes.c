/* cryptoSTV_zero_aes.c

  Crypto Speed Test Data File

  Company:
    Microchip Technology Inc.

  Description:
   This package provides NULL data sets of various lengths to
   demonstrate basic operation of AES. In particular, to expose
   the differences between counter modes by revealing the
   progression of the IV and KEY turns.
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

#include <stddef.h>
#include <stdint.h>

#include "./cryptoSpeedTestData.h"
#include "cryptoST/cryptoSTE_print.h" // for BASE_LINE
#include "cryptoST/cryptoSTE_malloc.h"

#ifdef HAVE_CONFIG_H
    #include <config.h>
#else
#include "configuration.h"
#endif
#include <wolfssl/wolfcrypt/settings.h>
#define DATA_PACKAGE_NAME   "AES_NULL"

#if (defined(WOLFSSL_AES_128)  \
  || defined(WOLFSSL_AES_192)  \
  || defined(WOLFSSL_AES_256)) \
 && defined(WOLFSSL_AES_CFB)

#define ALIGN4 __attribute__((aligned(4)))

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
    .io.sym.in.key = {
        .length = AES128_KEY_SIZE/8, // =16
        .data = (ALIGN4 const uint8_t*) // at least 32 bytes
            "Microchip null data test keys for all.",
    },
    .io.sym.in.ivNonce = {
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

static uint test_step = 0;
static const cryptoST_testDetail_t * nextTest(const cryptoST_testDetail_t * old)
{
    // Assume that if its in range, that it is legitimate.
    if (old != &test_item) 
        return NULL;

    /* TODO: make this better
     * This section should discriminate for the different AES key sizes.
     * As is, the vectors are delivered but the drivers may not be available.
     * */
    test_step++;
    switch(test_step)
    {
    case 1:
        test_item.technique = ET_AES_128;
        test_item.mode = EM_CFB;
        test_item.io.sym.in.key.length = 128/8;
        null_vector.vector.length = 16;
        break;
    case 2:
        test_item.technique = ET_AES_192;
        test_item.mode = EM_CFB;
        test_item.io.sym.in.key.length = 192/8;
        null_vector.vector.length = 16;
        break;
    case 3:
        test_item.technique = ET_AES_256;
        test_item.mode = EM_CFB;
        test_item.io.sym.in.key.length = 256/8;
        null_vector.vector.length = 16;
        break;
    case 4:
        test_item.technique = ET_AES_128;
        test_item.mode = EM_CFB;
        test_item.io.sym.in.key.length = 128/8;
        null_vector.vector.length = SIZE_PREALLOCATE;
        break;
    case 5:
        test_item.technique = ET_AES_192;
        test_item.mode = EM_CFB;
        test_item.io.sym.in.key.length = 192/8;
        null_vector.vector.length = SIZE_PREALLOCATE;
        break;
    case 6:
        test_item.technique = ET_AES_256;
        test_item.mode = EM_CFB;
        test_item.io.sym.in.key.length = 256/8;
        null_vector.vector.length = SIZE_PREALLOCATE;
        break;
    default:
        return NULL;
    }
    return old;
}

static const cryptoST_testDetail_t * firstTest(void)
{ return nextTest(&test_item); }

static const char * openData_func(void)
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

static const char * closeData_func(void)
{
    if (null_vector.vector.data)
        cryptoSTE_free((uint8_t*)null_vector.vector.data);
    null_vector.vector.data = NULL;
    return NULL;
}
#else
static const cryptoST_testDetail_t * firstTest(void)
{ return NULL; }
static const cryptoST_testDetail_t * nextTest(const cryptoST_testDetail_t * old)
{ return NULL; }
#define openData_func  ((void*)0)
#define closeData_func ((void*)0)
#endif

/*************************************************************
 * Declaration of the test manager API
 * Obligatory entry points for executing a test
 *************************************************************/
#include "cryptoSTD_zero_aes.h"
cryptoST_testAPI_t const microchip_zero_aes =
{
    .name = DATA_PACKAGE_NAME,
    .openData = openData_func,
    .firstTest = firstTest,
    .nextTest = nextTest,
    .closeData = closeData_func,
};

