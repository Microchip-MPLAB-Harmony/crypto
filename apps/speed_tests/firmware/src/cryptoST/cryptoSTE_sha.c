/*******************************************************************************
  Crypto Speed Test Source File

  Company:
    Microchip Technology Inc.

  File Name:
    cryptoSTE_sha.c

  Summary:
    SHA mode hash driver

  Description:
    This file contains functions to measure the time required 
    to perform SHA hashing. Time is reported in clock ticks.
 ******************************************************************************
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

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include "cryptoSTE_definitions.h"
#include "cryptoSTE_print.h"
#include "cryptoSTE_announce.h"
#include "cryptoSTE_aes_cbc.h"
#include "../test_data/cryptoSpeedTestData.h"

// theory: one of these "fixes" build-time issues with wolfssl
#include <stddef.h>
#include <string.h>
#include <stdbool.h>
#include "cryptoSTE_malloc.h"
#include <wolfssl/wolfcrypt/types.h>

#include "configuration.h"
#include <wolfssl/wolfcrypt/settings.h>

#define assert_dbug(X) __conditional_software_breakpoint((X))

// *****************************************************************************
// *****************************************************************************
// Section: Local data structures
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
// *****************************************************************************
// Section: Support routines
// *****************************************************************************
// *****************************************************************************

#if !defined(NO_SHA)        \
 || !defined(NO_SHA256)     \
 || defined(WOLFSSL_SHA224) \
 || defined(WOLFSSL_SHA384) \
 || defined(WOLFSSL_SHA512)
/* This is the generic encryption package.
 * The public entry points are defined below.
 *  */
static const char * cryptoSTE_sha(const cryptoST_testDetail_t * td,
                                       cryptoSTE_testExecution_t * param,
                                       cryptoSTE_shaOperator_t * hash_operator)
{
    const cryptoST_testVector_t * vector = td->rawData;
    
    if (CSTE_VERBOSE > 2)
    {
        P0_UINT( " data=", vector->vector.length);
        cryptoSTE_announceVector(2, vector);
        cryptoSTE_announceDetails(2, td);
    }
            
    param->results.encryption.size = vector->vector.length;
    
    // Hold off until the serial port is finished
    PRINT_WAIT_WHILE_BUSY();

    param->results.encryption.iterations = param->parameters.iterationOverride? 
                                    param->parameters.iterationOverride
                                  : td->recommendedRepetitions;

    assert_dbug(0 < td->io.hash.out.hash.length);
    uint32_t hash[td->io.hash.out.hash.length]; // room for expected size
    do
    {
        param->results.encryption.start = SYS_TIME_CounterGet();
        for (int i = param->results.encryption.iterations; i > 0; i--)
        {
            int ret = hash_operator(hash,
                                    vector->vector.data,
                                    vector->vector.length);
            if (0 != ret)
            {
                param->results.errorMessage = "hash operator failed";
                param->results.wolfSSLresult = ret;
                break;
            }
        }
        param->results.encryption.stop = SYS_TIME_CounterGet();
        if (param->results.errorMessage) break; // out of the test routine
        param->results.encryption.startStopIsValid = true;

        if (param->parameters.verifyByGoldenCiphertext)
        {
            if (td->io.hash.out.hash.length == 0)
                param->results.warningCount++,
                param->results.warningMessage = "can't verify cipher: no golden data"; 
            else if (XMEMCMP(hash, td->io.hash.out.hash.data, td->io.hash.out.hash.length))
            { 
                param->results.errorMessage = "computed hash does not match golden data";
                if (CSTE_VERBOSE)
                {
                    cryptoST_PRINT_hexLine(CRLF "..cipher:", 
                            (uint8_t*)hash, sizeof(hash));
                    cryptoST_PRINT_hexLine(CRLF "..golden:",
                            td->io.hash.out.hash.data, td->io.hash.out.hash.length);
                    PRINT_WAIT(CRLF);
                }
                break; 
            }
        }
    } while(0);
    
    return param->results.errorMessage;
}
#endif // SHA is enabled in some form

/* *********************************************************************
   *********************************************************************
   * WolfCrypt software test drivers
   *********************************************************************
   *********************************************************************
 */
#if !defined(NO_SHA) // SHA1
#include "wolfssl/wolfcrypt/hash.h"
static int WC_sha128
    (uint32_t hash[128/32], const uint8_t * data, const size_t length)
{
    return wc_ShaHash(data, length, (uint8_t*)hash);
}
#endif

#if !defined(NO_SHA256)
#include "wolfssl/wolfcrypt/hash.h"
static int WC_sha256
    (uint32_t hash[256/32], const uint8_t * data, const size_t length)
{
    return wc_Sha256Hash(data, length, (uint8_t*)hash);
}

#if defined(WOLFSSL_SHA224)
static int WC_sha224
    (uint32_t hash[224/32], const uint8_t * data, const size_t length)
{
    return wc_Sha224Hash(data, length, (uint8_t*)hash);
}
#endif // !NO_SHA224
#endif // WOLFSSL_SHA224

// #if !defined(NO_SHA384)
#if defined(WOLFSSL_SHA384)
#include "wolfssl/wolfcrypt/sha512.h"
static int WC_sha384
    (uint32_t hash[384/32], const uint8_t * data, const size_t length)
{
    return wc_Sha384Hash(data, length, (uint8_t*)hash);
}
#endif // !NO_SHA256

// #if !defined(NO_SHA512)
#if defined(WOLFSSL_SHA512)
#include "wolfssl/wolfcrypt/sha512.h"
static int WC_sha512
    (uint32_t hash[512/32], const uint8_t * data, const size_t length)
{
    return wc_Sha512Hash(data, length, (uint8_t*)hash);
}
#endif // !NO_SHA512

// *****************************************************************************
// *****************************************************************************
// Section: External API
// *****************************************************************************
// *****************************************************************************
#if defined(WOLFSSL_HAVE_MCHP_HW_CRYPTO_AES_HW_U2803) \
 || defined(WOLFSSL_HAVE_MCHP_HW_CRYPTO_AES_HW_U2805)
#include "crya/crya.h"
#endif

const char * cryptoSTE_crya_sha_timed(const cryptoST_testDetail_t * td,
                                      cryptoSTE_testExecution_t * param)
{
    /* Differential timing is supported only on selected platforms.
     * The hardware-available flag is set when H3 is configured
     * with "Use Hardware Cryptography", but meaningful results can
     * only be obtained when this particular algorithm has HW support
     * disabled, otherwise WC calls are redirected to the hardware.
     */
#if defined(WOLFSSL_HAVE_MCHP_HW_CRYPTO_SHA_HW_11105) \
 || defined(WOLFSSL_HAVE_MCHP_HW_CRYPTO_SHA_HW_U2010)
    // TODO: add E54 support.
#endif
    
#if defined(WOLFSSL_HAVE_MCHP_HW_CRYPTO_AES_HW_U2803) \
 || defined(WOLFSSL_HAVE_MCHP_HW_CRYPTO_AES_HW_U2805)
    if (param->parameters.useLocalDriverEntryPoints)
    {
        switch(td->technique)
        {
#if defined(WOLFSSL_SHA224)
            case ET_SHA_224:
                param->results.testHandler = "CRYA SHA 224";
                return cryptoSTE_sha(td, param, crya_sha224);
#endif
#if !defined(NO_SHA256)
            case ET_SHA_256:
                param->results.testHandler = "CRYA SHA 256";
                return cryptoSTE_sha(td, param, crya_sha256);
#endif
            default:
                param->results.testHandler = "CRYA SHA";
                return "SHA size not supported";
        }
    }
    else
#endif // u2803 or U2805
    {
        switch(td->technique)
        {
#if !defined(NO_SHA) // SHA1
            case ET_SHA_128:
                param->results.testHandler = "WOLF SHA 128";
                return cryptoSTE_sha(td, param, WC_sha128);
#endif //WOLFSSL_SHA1
#if !defined(NO_SHA256)
#if defined(WOLFSSL_SHA224)
            case ET_SHA_224:
                param->results.testHandler = "WOLF SHA 224";
                return cryptoSTE_sha(td, param, WC_sha224);
#endif //WOLFSSL_SHA224
            case ET_SHA_256:
                param->results.testHandler = "WOLF SHA 256";
                return cryptoSTE_sha(td, param, WC_sha256);
#endif //WOLFSSL_SHA256
#if defined(WOLFSSL_SHA384)
            case ET_SHA_384:
                param->results.testHandler = "WOLF SHA 384";
                return cryptoSTE_sha(td, param, WC_sha384);
#endif //WOLFSSL_SHA384
#if defined(WOLFSSL_SHA512)
            case ET_SHA_512:
                param->results.testHandler = "WOLF SHA 512";
                return cryptoSTE_sha(td, param, WC_sha512);
#endif //WOLFSSL_SHA256
            default:
                param->results.testHandler = "SHA (default)";
                return "SHA size not supported";
        }
    }
}
