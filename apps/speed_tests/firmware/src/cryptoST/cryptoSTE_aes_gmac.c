/*******************************************************************************
  Crypto Speed Test Source File

  Company:
    Microchip Technology Inc.

  File Name:
    cryptoSTE_aes_gmac.c

  Description:
    Test driver for AES GMAC mode.
 *******************************************************************************
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
#include <stdlib.h> // for malloc()

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

#if !defined(NO_AES_128) \
 && !defined(NO_AES_192) \
 && !defined(NO_AES_256)
/* This is the generic encryption package.
 * The public entry points are defined below.
 *  */
static const char * cryptoSTE_aes_gmac_timed(const cryptoST_testDetail_t * td,
                                      cryptoSTE_testExecution_t * param)
{
    const cryptoST_testVector_t * vector = td->rawData;
    
    if (CSTE_VERBOSE > 2)
    {
        P0_INT( " data=", vector->vector.length);
        cryptoSTE_announceVector(2, vector);
        cryptoSTE_announceDetails(2, td);
    }
            
    // Data validation
    if ( (NULL == td->io.sym.in.key.data)
      || (NULL == td->io.sym.in.ivNonce.data) )
        return "missing vector, key or initialization data" CRLF
               "     AES CBC test not activated." CRLF;

    byte * cipher = malloc(vector->vector.length);
    if (NULL == cipher)
        return "cannot allocate memory (" __BASE_FILE__ " line " BASE_LINE ")";
    else do // so we can use "break"
    {
        Aes enc;
        int ret;
        param->results.encryption.size = vector->vector.length;
    
        ret = wc_AesSetKey(&enc, td->io.sym.in.key.data, td->io.sym.in.key.length,
                                 td->io.sym.in.ivNonce.data, AES_ENCRYPTION);
        if (ret != 0) { param->results.errorMessage = "failed to set key"; break; }

        // Hold off until the serial port is finished
        PRINT_WAIT_WHILE_BUSY();

        // Remove any data noise that is in the target buffer
        XMEMSET(cipher, 0, sizeof(cipher));
        param->results.encryption.iterations = 
                param->parameters.iterationOverride? param->parameters.iterationOverride
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
        param->results.encryption.startStopIsValid = true;

        if (param->parameters.verifyByGoldenCiphertext)
        {
            if (td->io.sym.out.cipher.length == 0)
                param->results.warningMessage = "can't verify cipher: no golden data"; 
            else if (XMEMCMP(cipher, td->io.sym.out.cipher.data, td->io.sym.out.cipher.length))
            { 
                param->results.errorMessage = "computed ciphertext does not match golden data (was iterate==1?)";
                if (CSTE_VERBOSE)
                {
                    cryptoST_PRINT_hexLine(CRLF "..cipher:", cipher, vector->vector.length);
                    cryptoST_PRINT_hexLine(CRLF "..golden:",
                            td->io.sym.out.cipher.data, td->io.sym.out.cipher.length);
                    PRINT_WAIT(CRLF);
                }
                break; 
            }
            // Note: the test above will fail if iterate!=1.
        }

    #ifdef HAVE_AES_DECRYPT
        if (param->parameters.verifyByDecryption)
        {
            if (1 < param->results.encryption.iterations)
            {
                if (CSTE_VERBOSE > 1)
                    PRINT_WAIT("-- verification skipped: cannot recover CBC counter" CRLF);
            }
            else
            {
                byte * plain = malloc(vector->vector.length);
                if (NULL == plain)
                    return "cannot allocate memory (" __BASE_FILE__ " line " BASE_LINE ")";
                else do // so we can use "break"
                {
                    Aes dec;
                    
                    ret = wc_AesSetKey(&dec, td->io.sym.in.key.data, td->io.sym.in.key.length, 
                                             td->io.sym.in.ivNonce.data, AES_DECRYPTION);
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
                free(plain);
                if (NULL != param->results.errorMessage) break; // not really necessary, but etc.
            }
        }
    #endif /* HAVE_AES_DECRYPT */
    } while(0);
    
    free(cipher);
    return param->results.errorMessage;
}
#endif // not-no AES

// *****************************************************************************
// *****************************************************************************
// Section: External API
// *****************************************************************************
// *****************************************************************************

#if defined(WOLFSSL_AES_128) 
#undef TNAME
#define TNAME "WOLF AES CBC 128"
const char * cryptoSTE_aes_gmac_128_timed(const cryptoST_testDetail_t * td,
                                   cryptoSTE_testExecution_t * param)
{
    param->results.testHandler = TNAME;
    if (CSTE_VERBOSE > 1) PRINT(CRLF);

    // Data validation
    if (td->io.sym.in.key.length != 128/8)
        return "incorrect key length";
    else
        return cryptoSTE_aes_gmac_timed(td, param);
}
#endif

#if defined(WOLFSSL_AES_192)
#undef TNAME
#define TNAME "WOLF AES CBC 192"
const char * cryptoSTE_aes_gmac_192_timed(const cryptoST_testDetail_t * td,
                                   cryptoSTE_testExecution_t * param)
{
    param->results.testHandler = TNAME;
    if (CSTE_VERBOSE > 1) PRINT(CRLF);

    // Data validation
    if (td->io.sym.in.key.length != 192/8)
        return "incorrect key length";
    else
        return cryptoSTE_aes_gmac_timed(td, param);
}
#endif

#if defined(WOLFSSL_AES_256)
#undef TNAME
#define TNAME "WOLF AES CBC 256"
const char * cryptoSTE_aes_gmac_256_timed(const cryptoST_testDetail_t * td,
                                   cryptoSTE_testExecution_t * param)
{
    param->results.testHandler = TNAME;
    if (CSTE_VERBOSE > 1) PRINT(CRLF);

    // Data validation
    if (td->io.sym.in.key.length != 256/8)
        return "incorrect key length";
    else
        return cryptoSTE_aes_gmac_timed(td, param);
}
#endif
