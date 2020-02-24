/*******************************************************************************
  Crypto Speed Test Source File

  Company:
    Microchip Technology Inc.

  File Name:
    cryptoST_aes_cbc.c

  Summary:
    AES CBC mode encryption driver

  Description:
    This file contains functions to measure the time required 
    to perform AES CBC encryption. Time is reported in clock ticks.
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
#include "cryptoSTE_aes_cbc.h"
#include "../test_data/cryptoSpeedTestData.h"

// theory: one of these "fixes" build-time issues with wolfssl
#include <stddef.h>
#include <string.h>
#include <stdbool.h>
#include "cryptoSTE_malloc.h"

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

#define VERIFY_CONSECUTIVE_AES    1

// Debug NOP: add a NOP instruction for breakpoints but only in DEBUG mode.
#if defined(NDEBUG) || !defined(__DEBUG)
#define BP_NOP() /* as nothing */
#else
#define BP_NOP() do{ __asm__ __volatile__ ("nop"); }while(0)
#endif
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

/* This is the generic encryption package.
 * The public entry points are defined below.
 *  */
#if defined(HAVE_AES_CBC)
static const char * cryptoSTE_aes_cbc_timed(cryptoST_testDetail_t * td,
                                      cryptoSTE_testExecution_t * param)
{
    int ret;
    cryptoST_testVector_t * vector = td->rawData;
    
    if (CSTE_VERBOSE > 2)
    {
        P0_UINT( " data=", vector->vector.length);
        cryptoSTE_announceVector(2, vector);
        cryptoSTE_announceDetails(2, td);
    }
            
    // Data validation
    if ( (NULL == td->key->data)
      || (NULL == td->initVector.data) )
        return param->results.errorMessage = "missing key or initialization data";

    byte * cipher = cryptoSTE_malloc(vector->vector.length);
    if (NULL == cipher)
        return "cannot allocate memory (" __BASE_FILE__ " line " BASE_LINE ")";
    else do // so we can use "break"
    {
        Aes enc;
        param->results.encryption.size = vector->vector.length;
        BP_NOP();
        ret = wc_AesSetKey(&enc, td->key->data, td->key->length,
                                 td->initVector.data, AES_ENCRYPTION);
        if (ret != 0) { param->results.errorMessage = "failed to set key"; break; }

        // Hold off until the serial port is finished
        PRINT_WAIT_WHILE_BUSY();

        // Remove any data noise that is in the target buffer
        XMEMSET(cipher, 0, sizeof(cipher));
        param->results.encryption.iterations = param->parameters.iterationOverride? 
                                        param->parameters.iterationOverride
                                      : td->recommendedRepetitions;

        param->results.encryption.start = SYS_TIME_CounterGet();
        for (int i = param->results.encryption.iterations; i > 0; i--)
        {
            /* Note: if vector.length is not a multiple of 16,
             *       the default encryptor will ignore the remnant. */
            ret = wc_AesCbcEncrypt(&enc, cipher, vector->vector.data,
                                                 vector->vector.length); // **
            if (ret != 0) 
            { param->results.errorMessage = "encryption failed"; break; }
        }
        param->results.encryption.stop = SYS_TIME_CounterGet();
        if (param->results.errorMessage) break; // out of the test routine
        param->results.encryption.startStopIsValid = true;
#if 0
        printf("-- %08lx %08lx" CRLF, 
                param->results.encryption.stop,
                param->results.encryption.start);
#elif 0
        printf("-- %08lx %08lx %08lx" CRLF, 
                param->results.encryption.stop,
                param->results.encryption.start,
                param->results.encryption.stop-param->results.encryption.start);
#endif
        
        if (param->parameters.verifyByGoldenCiphertext)
        {
            if (td->goldenCipher.length == 0)
                param->results.warningCount++,
                param->results.warningMessage = "can't verify cipher: no golden data"; 
            else if (XMEMCMP(cipher, td->goldenCipher.data, td->goldenCipher.length))
            { 
                param->results.errorMessage = "computed ciphertext does not match golden data (was iterate==1?)";
                if (CSTE_VERBOSE)
                {
                    cryptoST_PRINT_hexLine(CRLF "..cipher:", cipher, vector->vector.length);
                    cryptoST_PRINT_hexLine(CRLF "..golden:",
                            td->goldenCipher.data, td->goldenCipher.length);
                    PRINT_WAIT(CRLF);
                }
                break; 
            }
            // Note: the test above will fail if iterate!=1.
        }
    } while(0);
    
#if defined(HAVE_AES_DECRYPT)
    if (NULL == param->results.errorMessage) do {
        if (param->parameters.verifyByDecryption)
        {
            if (1 < param->results.encryption.iterations)
            {
                param->results.warningCount++;
                param->results.warningMessage = 
                        "verification skipped: cannot recover CBC counter";
                break;
            }
            else
            {
                byte * plain = cryptoSTE_malloc(vector->vector.length);
                if (NULL == plain)
                    return "cannot allocate memory (" __BASE_FILE__ " line " BASE_LINE ")";
                else do // so we can use "break"
                {
                    Aes dec;
                    
                    ret = wc_AesSetKey(&dec, td->key->data, td->key->length, 
                                             td->initVector.data, AES_DECRYPTION);
                    if (ret != 0) { param->results.errorMessage = "setting decryption key failed"; break; }

                    // Conventional decrypt and comparison
                    if (CSTE_VERBOSE > 1) 
                        PRINT_WAIT("-- decrypting and comparing" CRLF)

                    /* Note: if vector.length is not a multiple of 16,
                     *       this call will bonk. */
                    ret = wc_AesCbcDecrypt(&dec, plain, cipher, 
                                            vector->vector.length);
                    if (ret != 0) 
                    { param->results.errorMessage = "decryption failed (is length%16 correct?)"; break; }

                    if (XMEMCMP(plain, vector->vector.data, vector->vector.length))
                    { 
                        param->results.errorMessage = "recovered data does not match original"; 
                        if (CSTE_VERBOSE)
                        {
                            cryptoST_PRINT_hexLine(CRLF "..rawData:",
                                    vector->vector.data, vector->vector.length);
                            cryptoST_PRINT_hexLine(CRLF "..decrypt:",
                                    plain, vector->vector.length);
                            PRINT_WAIT(CRLF);
                        }
                        break; 
                    }
                } while(0);
                cryptoSTE_free(plain);
                if (NULL != param->results.errorMessage) break; // not really necessary, but etc.
            }
        }
    #endif /* HAVE_AES_DECRYPT */
    } while(0);
    
    cryptoSTE_free(cipher);
    return param->results.errorMessage;
}

// *****************************************************************************
// *****************************************************************************
// Section: External API
// *****************************************************************************
// *****************************************************************************

#undef TNAME
#define TNAME "AES CBC 128"
const char * cryptoSTE_aes_cbc_128_timed(cryptoST_testDetail_t * td,
                                   cryptoSTE_testExecution_t * param)
{
    param->results.testHandler = TNAME;
    if (CSTE_VERBOSE > 1) PRINT(CRLF);

    // Data validation
    if (td->key->length != 128/8)
        return "incorrect key length";
    else
        return cryptoSTE_aes_cbc_timed(td, param);
}

#undef TNAME
#define TNAME "AES CBC 192"
const char * cryptoSTE_aes_cbc_192_timed(cryptoST_testDetail_t * td,
                                   cryptoSTE_testExecution_t * param)
{
    param->results.testHandler = TNAME;
    if (CSTE_VERBOSE > 1) PRINT(CRLF);

    // Data validation
    if (td->key->length != 192/8)
        return "incorrect key length";
    else
        return cryptoSTE_aes_cbc_timed(td, param);
}

#undef TNAME
#define TNAME "AES CBC 256"
const char * cryptoSTE_aes_cbc_256_timed(cryptoST_testDetail_t * td,
                                   cryptoSTE_testExecution_t * param)
{
    param->results.testHandler = TNAME;
    if (CSTE_VERBOSE > 1) PRINT(CRLF);

    // Data validation
    if (td->key->length != 256/8)
        return "incorrect key length";
    else
        return cryptoSTE_aes_cbc_timed(td, param);
}
#endif // HAVE_AES_CBC
