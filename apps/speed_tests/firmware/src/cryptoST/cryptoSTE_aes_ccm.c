/*******************************************************************************
  Crypto Speed Test Source File

  Company:
    Microchip Technology Inc.

  File Name:
    cryptoST_aes_ccm.c

  Summary:
    AES CCM mode encryption driver

  Description:
    This file contains functions to measure the time required 
    to perform AES CCM (CBC-MAC) encryption. Time is reported 
    in clock ticks.
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

#include "cryptoSTE.h"
#include "cryptoST_print.h"
#include "cryptoSTE_announce.h"
#include "cryptoSTE_aes_ccm.h"
#include "cryptoSTE_malloc.h"
#include "../test_data/cryptoSpeedTestData.h"

// theory: one of these "fixes" build-time issues with wolfssl
#include <stddef.h>
#include <string.h>
#include <stdbool.h>

#include <wolfssl/wolfcrypt/settings.h>
// #include <wolfssl/wolfssl/verion.h>
#ifdef USE_FLAT_TEST_H
    #include "test.h"
#else
   // #include "wolfssl/wolfcrypt/test/test.h"
#endif
#include <wolfssl/wolfcrypt/types.h>
#include <wolfssl/wolfcrypt/des3.h>
#include <wolfssl/wolfcrypt/aes.h>
#include <wolfssl/wolfcrypt/wc_encrypt.h>

#ifdef WOLFSSL_STATIC_MEMORY
    static WOLFSSL_HEAP_HINT* HEAP_HINT;
#else
    #define HEAP_HINT NULL
#endif /* WOLFSSL_STATIC_MEMORY */

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

#if CSTE_VERBOSE
static void dumpHex(cryptoST_testDetail_t * td,
                    bool goldCipherToo,
                    cryptoST_testVector_t * input)
{
    cryptoST_PRINT_hexLine(CRLF "..key     :",
            td->key.data, td->key.length);
    cryptoST_PRINT_hexLine(CRLF "..nonce   :",
            td->initVector.data, td->initVector.length); // nonce
    if (input) // original raw data
        cryptoST_PRINT_hexBlock(CRLF "..rawData :",
                        input->vector.data, input->vector.length);
    if (td->additionalAuthData.data)
        cryptoST_PRINT_hexLine(CRLF "..aad     :",
            td->additionalAuthData.data, td->additionalAuthData.length);
    
    if (goldCipherToo && td->goldenCipher.data)
        cryptoST_PRINT_hexBlock(CRLF "goldCipher:",
                td->goldenCipher.data, td->goldenCipher.length);
    if (goldCipherToo && td->goldenTag.data)
        cryptoST_PRINT_hexBlock(CRLF "...goldTag:",
                td->goldenTag.data, td->goldenTag.length);

    PRINT_WAIT(CRLF);
}
#endif // CSTE_VERBOSE
    
#ifdef HAVE_AESCCM

/* This test based on test.c/aesccm_default_test_helper().
 * The public entry points are defined below.
 *   */
static const char * cryptoSTE_aes_ccm_test_timed(
                                cryptoST_testDetail_t * td,
                                cryptoSTE_testExecution_t * param)
{
    /* Data validation
     * Having NULL pointers for rawData, cipher and aad is allowed.
     * Refer to test.c line 7260
     * */
    if ( (NULL == td->key.data)
      || (NULL == td->initVector.data) // the nonce
      || (NULL == td->rawData)
//    || (NULL == td->rawData->vector.data)
//    || (NULL == td->additionalAuthData.data) 
            )
        return param->results.errorMessage = "missing key-init-raw-auth data";
    
    cryptoST_testVector_t * input = td->rawData;
    if (CSTE_VERBOSE > 2)
    {
        P0_UINT( " data=", input->vector.length);
        cryptoSTE_announceVector(2, input);
        cryptoSTE_announceDetails(2, td);
    }

    /* Determine the correct buffer sizes by rounding up to 128 bits.
     * Note that C,T are both required in enc and dec scopes.
     * There is magic here: this depends on AES_BLOCK_SIZE to be power-of-2.
     *  */
    size_t rawSizePadded = 
        (input->vector.length + (AES_BLOCK_SIZE-1))&~(AES_BLOCK_SIZE-1);
    size_t aadSize = 
        (td->additionalAuthData.length + (AES_BLOCK_SIZE-1))&~(AES_BLOCK_SIZE-1);
    byte * resultC = cryptoSTE_malloc(rawSizePadded+aadSize+AES_BLOCK_SIZE);
    const size_t sizeC = rawSizePadded;

    byte resultT[td->goldenTag.length];
    const size_t sizeT = ALENGTH(resultT); // don't do this for the others
    
    if (NULL == resultC) 
        param->results.errorMessage = 
                "cannot allocate memory (" __BASE_FILE__ " line " BASE_LINE ")";
    else do /* once or break */
    {
        Aes enc;
        XMEMSET(resultC, 0, sizeC);
        XMEMSET(resultT, 0, sizeT);

        if (0 != wc_AesInit(&enc, HEAP_HINT, INVALID_DEVID))
        { param->results.errorMessage = "AesInit.enc failed (" BASE_LINE ")"; 
          break; }

        if (0 != wc_AesCcmSetKey(&enc, td->key.data, td->key.length))
        { param->results.errorMessage = "failed to set key"; break; }

        param->results.encryption.iterations = 
                param->parameters.iterationOverride? 
                        param->parameters.iterationOverride
                      : td->recommendedRepetitions;
        param->results.encryption.size = input->vector.length;
        param->results.encryption.start = SYS_TIME_CounterGet();
        for (int i = param->results.encryption.iterations; i > 0; i--)
        {
            int result = wc_AesCcmEncrypt(&enc, resultC,
                    input->vector.data, input->vector.length,
                    td->initVector.data, td->initVector.length, // nonce
                    resultT, sizeT, // a.k.a. td->goldenTag.length
                    td->additionalAuthData.data, td->additionalAuthData.length);
#if defined(WOLFSSL_ASYNC_CRYPT)
            result = wc_AsyncWait(result, &enc.asyncDev, WC_ASYNC_FLAG_NONE);
#endif
            if (0 != result)
            { 
                param->results.errorMessage = "hash failed (" BASE_LINE ")";
                if (CSTE_VERBOSE)
                {
                    dumpHex(td, true, input);
                    cryptoST_PRINT_hexLine(CRLF "..cipher  :", resultC, sizeC);
                }
                break; 
            }
        }
        param->results.encryption.stop = SYS_TIME_CounterGet();
        if (param->results.errorMessage) break; // out of the test routine
        param->results.encryption.startStopIsValid = true;

        if (param->parameters.verifyByGoldenCiphertext)
        {
            if ((NULL == td->goldenCipher.data) || (0 == td->goldenCipher.length))
                param->results.warningCount++,
                param->results.warningMessage = "can't verify cipher: no golden data"; 
            else if (XMEMCMP(resultC, td->goldenCipher.data, td->goldenCipher.length))
            {
                param->results.errorMessage = "computed hash does not match golden data (was iterate==1?)";
                if (CSTE_VERBOSE)
                {
                    dumpHex(td, true, input);
                    cryptoST_PRINT_hexLine(CRLF "..cipher  :", resultC, sizeC);
                    cryptoST_PRINT_hexLine(CRLF "..compTag :", resultT, sizeT);
                }
                break; 
            }
            else if ((NULL == td->goldenTag.data) || (0 == td->goldenTag.length))
                param->results.warningCount++,
                param->results.warningMessage = "can't verify tag: no golden tag"; 
            else if (XMEMCMP(resultT, td->goldenTag.data, td->goldenTag.length))
            {
                param->results.errorMessage = "computed tag does not match golden tag (was iterate==1?)";
                if (CSTE_VERBOSE)
                {
                    dumpHex(td, true, input);
                    cryptoST_PRINT_hexBlock(CRLF "..cipher  :", resultC, sizeC);
                    cryptoST_PRINT_hexLine(CRLF "..compTag :", resultT, sizeT);
                }
                break; 
            }
        }
    } while(0);
    
#if defined(HAVE_AES_DECRYPT)
    if ((NULL == param->results.errorMessage) 
     && (param->parameters.verifyByDecryption)) 
    {
        byte * resultP = NULL;

        if (1 < param->results.encryption.iterations)
            param->results.warningCount++,
            param->results.warningMessage = 
                    "decryption skipped because of multiple iterations";
        else if (NULL == (resultP = cryptoSTE_malloc(rawSizePadded)))
            param->results.errorMessage = 
                    "no memory for decrypt (" __BASE_FILE__ " line " BASE_LINE ")";
        else do /* once or break */
        {
            Aes dec;

            if (0 != wc_AesInit(&dec, HEAP_HINT, INVALID_DEVID))
            { param->results.errorMessage = "AesInit.dec failed (" BASE_LINE ")"; 
              break; }

            if (0 != wc_AesCcmSetKey(&dec, td->key.data, td->key.length))
            { param->results.errorMessage = "failed to set key"; break; }

            if (CSTE_VERBOSE > 1) 
                PRINT_WAIT("-- decrypting and comparing" CRLF)

            XMEMSET(resultP, 0, rawSizePadded);
            param->results.wolfSSLresult = 
                wc_AesCcmDecrypt(&dec, resultP, 
                    resultC, input->vector.length,
                    td->initVector.data, td->initVector.length, // nonce
                    resultT, sizeT, // a.k.a td->additionalAuthData.length,
                    td->additionalAuthData.data, td->additionalAuthData.length);
#if defined(WOLFSSL_ASYNC_CRYPT)
            result = wc_AsyncWait(result, &enc.asyncDev, WC_ASYNC_FLAG_NONE);
#endif
            if (param->results.wolfSSLresult != 0) 
            { 
                param->results.errorMessage = "decryption failed (is length%16 correct?)"; 
                if (CSTE_VERBOSE)
                {
                    dumpHex(td, false, input);
                    cryptoST_PRINT_hexLine(CRLF "..decrypt :",
                            resultP, rawSizePadded);
                    PRINT_WAIT(CRLF);
                }
                break; 
            }

            if (XMEMCMP(resultP, input->vector.data, input->vector.length))
            { 
                param->results.errorMessage = "recovered data does not match original"; 
                if (CSTE_VERBOSE)
                {
                    cryptoST_PRINT_hexLine(CRLF "..rawData :",
                            input->vector.data, input->vector.length);
                    cryptoST_PRINT_hexLine(CRLF "..decrypt :",
                            resultP, rawSizePadded);
                    PRINT_WAIT(CRLF);
                }
                break; 
            }
        } while(0);
        if (resultP) cryptoSTE_free(resultP);
    }
    #endif /* HAVE_AES_DECRYPT */

    if (resultC) cryptoSTE_free(resultC);
    return param->results.errorMessage;
}

// *****************************************************************************
// *****************************************************************************
// Section: External API
// *****************************************************************************
// *****************************************************************************

/* CCM is defined by NIST 800-38D
 * Inputs:  key, initVector (the nonce)     for the underlying CCM
 *          rawData, additionalAuthData     user inputs
 * Outputs: resultC, resultT
 * Compare: goldenResult=resultC, goldenTag=resultT
 * */
const char * cryptoSTE_aes_ccm_timed(
            cryptoST_testDetail_t * td,
            cryptoSTE_testExecution_t * param)
{
    param->results.testHandler = "AES CCM";
    if (CSTE_VERBOSE > 1) PRINT(CRLF);

    // Data validation
    const char * answer = 0;
    if (td->key.length != 128/8)
        answer = "incorrect key length";
    else
        return cryptoSTE_aes_ccm_test_timed(td, param);
    
    return param->results.errorMessage = answer;
}

#endif // HAVE_AESCCM