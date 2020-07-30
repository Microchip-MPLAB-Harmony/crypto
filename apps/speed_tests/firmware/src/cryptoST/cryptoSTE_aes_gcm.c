/*******************************************************************************
  Crypto Speed Test Source File

  Company:
    Microchip Technology Inc.

  File Name:
    cryptoST_aes_gcm.c

  Summary:
    AES GCM mode encryption driver

  Description:
    This file contains functions to measure the time required 
    to perform AES GCM encryption. Time is reported in clock ticks.
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
#include "cryptoSTE_aes_gcm.h"
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

#ifdef HAVE_AESGCM

// *****************************************************************************
// *****************************************************************************
// Section: Local data structures
// *****************************************************************************
// *****************************************************************************

struct localData_s
{
    cryptoST_softData_t C;
    cryptoST_softData_t T;
    cryptoST_softData_t P;
    size_t rawSizePadded;
    size_t aadSize;
    size_t Csize;
};

static struct localData_s resultsBuffers;
    
// *****************************************************************************
// *****************************************************************************
// Section: Support routines
// *****************************************************************************
// *****************************************************************************
static void printAll(const cryptoST_testVector_t * input,
                     const cryptoST_testDetail_t * td,
                     struct localData_s * results)
{
    cryptoST_PRINT_hexLine(CRLF "..input   :", 
        input->vector.data, input->vector.length);
    cryptoST_PRINT_hexLine(CRLF "..key     :", 
        td->io.sym.in.key.data, td->io.sym.in.key.length);
    cryptoST_PRINT_hexLine(CRLF "..nonce   :", 
        td->io.sym.in.ivNonce.data, td->io.sym.in.ivNonce.length);
    cryptoST_PRINT_hexLine(CRLF "..authData:",
            td->io.sym.in.additionalAuthData.data, 
                    td->io.sym.in.additionalAuthData.length);

    cryptoST_PRINT_hexLine(CRLF "..cipher  :", 
            results->C.data, results->C.length);
    cryptoST_PRINT_hexLine(CRLF "..goldData:",
            td->io.sym.out.cipher.data, td->io.sym.out.cipher.length);
    cryptoST_PRINT_hexLine(CRLF "..resultT :", 
            results->T.data, results->T.length);
    cryptoST_PRINT_hexLine(CRLF "..goldTag :",
            td->io.sym.out.tag.data, td->io.sym.out.tag.length);
    cryptoST_PRINT_hexLine(CRLF "..resultP :", 
            results->P.data, results->P.length);
    PRINT_WAIT(CRLF);

    printf("rawSizePadded: %lu" CRLF, \
            (long unsigned int)results->rawSizePadded);
    printf("      aadSize: %lu" CRLF, 
            (long unsigned int)results->aadSize);
    printf("        Csize: %lu" CRLF, 
            (long unsigned int)results->Csize);
}

/* This test based on test.c/aesgcm_default_test_helper().
 * The public entry points are defined below.
 *   */
static const char * cryptoSTE_aes_gcm_test_timed(
                                const cryptoST_testDetail_t * td,
                                cryptoSTE_testExecution_t * param)
{
    // Do this prior to possible errors so that it correctly reports
    // with any error message.
    const cryptoST_testVector_t * input = td->rawData;
    param->results.encryption.size = input->vector.length;
    param->results.encryption.iterations = param->parameters.iterationOverride? 
                                    param->parameters.iterationOverride
                                    : td->recommendedRepetitions;
    /* Data validation
     * Having NULL pointers for rawData, cipher and aad is allowed.
     * Refer to test.c line 7260
     * */
    if ( (NULL == td->io.sym.in.key.data)
      || (NULL == td->io.sym.in.ivNonce.data)
      || (NULL == td->rawData)
//    || (NULL == td->rawData->vector.data)
//    || (NULL == td->additionalAuthData.data) 
            )
        return param->results.errorMessage = "missing key-init-raw-auth data";
    
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
    register struct localData_s * const results = &resultsBuffers;

    results->rawSizePadded = 
        (input->vector.length + (AES_BLOCK_SIZE-1))&~(AES_BLOCK_SIZE-1);
    results->aadSize = 
        (td->io.sym.in.additionalAuthData.length + (AES_BLOCK_SIZE-1))&~(AES_BLOCK_SIZE-1);
    results->Csize = results->rawSizePadded
                   + results->aadSize 
                   + AES_BLOCK_SIZE;

    results->C.data = cryptoSTE_malloc(results->Csize);
    results->C.length = input->vector.length; // rawSizePadded;
    results->T.data = (byte[AES_BLOCK_SIZE]){};
    results->T.length = AES_BLOCK_SIZE;
    
    if (NULL == results->C.data) 
        param->results.errorMessage = 
                "cannot allocate memory at " __FILE__ "(" BASE_LINE ")";
    else do /* once or break */
    {
        Aes enc;
        XMEMSET(results->C.data, 0, results->C.length);
        XMEMSET(results->T.data, 0, results->T.length);

        if (0 != wc_AesInit(&enc, HEAP_HINT, INVALID_DEVID))
        { param->results.errorMessage = "AesInit.enc failed (" BASE_LINE ")"; 
          break; }

        if (0 != wc_AesGcmSetKey(&enc, td->io.sym.in.key.data, td->io.sym.in.key.length))
        { param->results.errorMessage = "failed to set key"; break; }

        param->results.encryption.start = SYS_TIME_CounterGet();
        for (int i = param->results.encryption.iterations; i > 0; i--)
        {
            int result = wc_AesGcmEncrypt(&enc, results->C.data,
                    input->vector.data, input->vector.length,
                    td->io.sym.in.ivNonce.data, td->io.sym.in.ivNonce.length,
                    results->T.data, results->T.length,
                    td->io.sym.in.additionalAuthData.data, 
                            td->io.sym.in.additionalAuthData.length);
            // additional authentication data
#if defined(WOLFSSL_ASYNC_CRYPT)
            results = wc_AsyncWait(results, &enc.asyncDev, WC_ASYNC_FLAG_NONE);
#endif
            if (0 != result)
            { 
                param->results.errorMessage = "hash failed (" BASE_LINE ")";
                if (CSTE_VERBOSE)
                    printAll(input, td, results);
                break; 
            }
        }
        param->results.encryption.stop = SYS_TIME_CounterGet();
        if (param->results.errorMessage) break; // out of the test routine
        param->results.encryption.startStopIsValid = true;

        if (param->parameters.verifyByGoldenCiphertext)
        {
            if ((NULL == td->io.sym.out.cipher.data) || (0 == td->io.sym.out.cipher.length))
                param->results.warningCount++,
                param->results.warningMessage = "can't verify cipher: no golden data"; 
            else if (XMEMCMP(results->C.data, td->io.sym.out.cipher.data, td->io.sym.out.cipher.length))
            {
                param->results.errorMessage = "computed hash does not match golden data (was iterate==1?)";
                if (CSTE_VERBOSE)
                    printAll(input, td, results);
                break; 
            }
            else if ((NULL == td->io.sym.out.tag.data) || (0 == td->io.sym.out.tag.length))
                param->results.warningCount++,
                param->results.warningMessage = "can't verify tag: no golden tag"; 
            else if (XMEMCMP(results->T.data, td->io.sym.out.tag.data, td->io.sym.out.tag.length))
            {
                param->results.errorMessage = "computed tag does not match golden tag (was iterate==1?)";
                if (CSTE_VERBOSE)
                    printAll(input, td, results);
                break; 
            }
        }
    } while(0);
    
#if defined(HAVE_AES_DECRYPT)
    if ((NULL == param->results.errorMessage) 
     && (param->parameters.verifyByDecryption)) 
    {
        results->P.data = NULL;
        results->P.length = results->rawSizePadded;

        if (1 < param->results.encryption.iterations)
            param->results.warningCount++,
            param->results.warningMessage = 
                    "decryption skipped because of multiple iterations";
        else if (NULL == (results->P.data = cryptoSTE_malloc(results->P.length)))
            param->results.errorMessage = 
                "no memory for decrypt (" __BASE_FILE__ " line " BASE_LINE ")";
        else do /* once or break */
        {
            Aes dec;

            if (0 != wc_AesInit(&dec, HEAP_HINT, INVALID_DEVID))
                param->results.errorMessage = "AesInit.dec failed (" BASE_LINE ")"; 
            else if (0 != wc_AesGcmSetKey(&dec, td->io.sym.in.key.data, td->io.sym.in.key.length))
                param->results.errorMessage = "failed SetKey.dec"; 
            else
            {
                if (CSTE_VERBOSE > 1) 
                    PRINT_WAIT("-- decrypting and comparing" CRLF)

                XMEMSET(results->P.data, 0, results->P.length);
                param->results.wolfSSLresult = wc_AesGcmDecrypt(&dec, 
                            results->P.data, results->C.data, results->C.length,
                            td->io.sym.in.ivNonce.data, td->io.sym.in.ivNonce.length,
                            results->T.data, results->T.length,// td->additionalAuthData.length,
                            td->io.sym.in.additionalAuthData.data, 
                                td->io.sym.in.additionalAuthData.length);
                #if defined(WOLFSSL_ASYNC_CRYPT)
                results = wc_AsyncWait(results, &enc.asyncDev, WC_ASYNC_FLAG_NONE);
                #endif
                if (param->results.wolfSSLresult != 0) 
                { 
                    param->results.errorMessage = "decryption failed (is length%16 correct?)"; 
                    if (CSTE_VERBOSE)
                        printAll(input, td, results);
                }
                else if (XMEMCMP(results->P.data, input->vector.data, input->vector.length))
                { 
                    param->results.errorMessage = "recovered data does not match original"; 
                    if (CSTE_VERBOSE)
                        printAll(input, td, results);
                }
                // else printAll(input, td, results);
            }
            cryptoSTE_free(results->P.data);
        } while(0);
    }
    #endif /* HAVE_AES_DECRYPT */

    if (results->C.data) cryptoSTE_free(results->C.data);
    return param->results.errorMessage;
}

// *****************************************************************************
// *****************************************************************************
// Section: External API
// *****************************************************************************
// *****************************************************************************

/* GCM is defined by NIST 800-38D
 * Inputs:  key, ivNonce                 for the underlying GCM
 *          rawData, additionalAuthData     user inputs
 * Outputs: resultC, resultT
 * Compare: io.sym.out.cipher=resultC, io.sym.out.tag=resultT
 * */
const char * cryptoSTE_aes_gcm_timed(
            const cryptoST_testDetail_t * td,
            cryptoSTE_testExecution_t * param)
{
    if (CSTE_VERBOSE > 1) PRINT(CRLF);

    // Data validation
    const char * answer = 0;
    switch(td->io.sym.in.key.length)
    {
    case 128/8:
        param->results.testHandler = "WOLF AES GCM 128";
        return cryptoSTE_aes_gcm_test_timed(td, param);
        break;
    case 192/8:
        param->results.testHandler = "WOLF AES GCM 192";
        return cryptoSTE_aes_gcm_test_timed(td, param);
        break;
    case 256/8:
        param->results.testHandler = "WOLF AES GCM 256";
        return cryptoSTE_aes_gcm_test_timed(td, param);
        break;
    default:
        param->results.testHandler = "WOLF AES GCM (no key)";
        answer = "incorrect key length";
        break;
    }
    
    return param->results.errorMessage = answer;
}

#endif // HAVE_AESGCM
