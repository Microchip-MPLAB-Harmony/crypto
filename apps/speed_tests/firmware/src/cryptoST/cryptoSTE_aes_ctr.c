/*******************************************************************************
  Crypto Speed Test Source File

  Company:
    Microchip Technology Inc.

  File Name:
    cryptoST_aes_ctr.c

  Summary:
    AES CTR mode encryption driver

  Description:
    This file contains functions to measure the time required 
    to perform AES CTR encryption. Time is reported in clock ticks.
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
#include "cryptoSTE_aes_ctr.h"
#include "../../test_data/cryptoSpeedTestData.h"

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

#if defined(WOLFSSL_AES_COUNTER)

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
static const char * cryptoSTE_aes_ctr_timed(const cryptoST_testDetail_t * td,
                                      cryptoSTE_testExecution_t * param)
{
    const cryptoST_testVector_t * vector = td->rawData;
    
    if (CSTE_VERBOSE > 2)
    {
        P0_UINT( " data=", vector->vector.length);
        cryptoSTE_announceVector(2, vector);
        cryptoSTE_announceDetails(2, td);
    }
            
    // Data validation
    if ( (NULL == td->io.sym.in.key.data)
      || (NULL == td->io.sym.in.ivNonce.data) )
        return "missing vector, key or initialization data" CRLF
               "     AES CTR test not activated." CRLF;
    
    Aes enc;
    int ret = 0;
    byte cipher[AES_BLOCK_SIZE * 4];
    if (vector->vector.length > ALENGTH(cipher))
        return "input too big (" __BASE_FILE__ " line " BASE_LINE ")";
    
    ret = wc_AesSetKeyDirect(&enc, td->io.sym.in.key.data, td->io.sym.in.key.length,
                                td->io.sym.in.ivNonce.data, AES_ENCRYPTION);
    if (ret != 0) return "failed to set key";
    
    // Hold off until the serial port is finished
    PRINT_WAIT_WHILE_BUSY();
    
    /* If the golden ciphertext is shorter than the given data,
     * use only that amount of data. This is a special test case
     * for truncating the input buffer.
     * */
    size_t testLength = vector->vector.length;
    if (td->io.sym.out.cipher.data && td->io.sym.out.cipher.length)
    { 
        if (td->io.sym.out.cipher.length < testLength)
            testLength = td->io.sym.out.cipher.length;
    }
    
    // Remove any data noise that is in the target buffer
    XMEMSET(cipher, 0, sizeof(cipher));
    param->results.encryption.iterations = param->parameters.iterationOverride? 
                                param->parameters.iterationOverride
                                  : td->recommendedRepetitions;
    param->results.encryption.size = vector->vector.length;
    param->results.encryption.start = SYS_TIME_CounterGet();
    for (int i = param->results.encryption.iterations; i > 0; i--)
    {
        ret = wc_AesCtrEncrypt(&enc, cipher, vector->vector.data, testLength);
        if (ret != 0) return "encryption failed (" BASE_LINE ")";
    }
    param->results.encryption.stop = SYS_TIME_CounterGet();
    param->results.encryption.startStopIsValid = true;

    if (param->parameters.verifyByGoldenCiphertext)
    {
        if ((NULL == td->io.sym.out.cipher.data) || (0 == td->io.sym.out.cipher.length))
            param->results.warningCount++,
            param->results.warningMessage = "can't verify cipher: no golden data"; 
        else if (XMEMCMP(cipher, td->io.sym.out.cipher.data, td->io.sym.out.cipher.length))
        {
            if (CSTE_VERBOSE)
            {
                P0_UINT(CRLF "test length = ", testLength);
                cryptoST_PRINT_hexLine(CRLF "key   : ",
                        td->io.sym.in.key.data, td->io.sym.in.key.length);
                cryptoST_PRINT_hexLine(CRLF "initV : ",
                        td->io.sym.in.ivNonce.data, td->io.sym.in.ivNonce.length);
                cryptoST_PRINT_hexLine(CRLF "given : ",
                        vector->vector.data, vector->vector.length);
                cryptoST_PRINT_hexLine(CRLF "cipher: ",
                        cipher, ALENGTH(cipher));
                cryptoST_PRINT_hexLine(CRLF "gold  : ",
                        td->io.sym.out.cipher.data, td->io.sym.out.cipher.length);
                PRINT(CRLF);
            }
            return "computed ciphertext does not match golden data (was iterate==1?)";
        }
        // Note: the test above will fail if iterate!=1.
    }

    if (param->parameters.verifyByDecryption)
    {
        Aes dec;
        byte plain[AES_BLOCK_SIZE * 4]; // trouble here?

        /* decrypt uses AES_ENCRYPTION */
        ret = wc_AesSetKeyDirect(&dec, td->io.sym.in.key.data, td->io.sym.in.key.length, 
                                    td->io.sym.in.ivNonce.data, AES_ENCRYPTION);
        if (ret != 0) return "setting decryption key failed";

        // Conventional decrypt and comparison
        if (CSTE_VERBOSE > 1) 
            PRINT_WAIT("-- decrypting and comparing" CRLF)

        /* no such thing as wc_AesCtrDecrypt() */
        ret = wc_AesCtrEncrypt(&dec, plain, cipher, AES_BLOCK_SIZE * 4);
        if (ret != 0) return "decryption failed (" BASE_LINE ")";

        if (XMEMCMP(plain, vector->vector.data, AES_BLOCK_SIZE))
        {
            if (CSTE_VERBOSE)
            {
                cryptoST_PRINT_hexLine(CRLF "key   : ", 
                        td->io.sym.in.key.data, td->io.sym.in.key.length);
                cryptoST_PRINT_hexLine(CRLF "initV : ", 
                        td->io.sym.in.ivNonce.data, td->io.sym.in.ivNonce.length);
                cryptoST_PRINT_hexLine(CRLF "given : ", 
                        vector->vector.data, vector->vector.length);
                cryptoST_PRINT_hexLine(CRLF "plain : ", 
                        plain, ALENGTH(plain));
                PRINT(CRLF);
            }
            return "recovered data does not match original";
        }
    }
    return 0;
}

// *****************************************************************************
// *****************************************************************************
// Section: External API
// *****************************************************************************
// *****************************************************************************

#undef TNAME
#define TNAME "WOLF AES CTR 128"
const char * cryptoSTE_aes_ctr_128_timed(const cryptoST_testDetail_t * td,
                                   cryptoSTE_testExecution_t * param)
{
    param->results.testHandler = TNAME;
    if (CSTE_VERBOSE > 1) PRINT(CRLF);

    // Data validation
    if (td->io.sym.in.key.length != 128/8)
        return "incorrect key length" CRLF
               "     " TNAME " test not activated." CRLF;
    else
        return cryptoSTE_aes_ctr_timed(td, param);
}

#undef TNAME
#define TNAME "WOLF AES CTR 192"
const char * cryptoSTE_aes_ctr_192_timed(const cryptoST_testDetail_t * td,
                                   cryptoSTE_testExecution_t * param)
{
    param->results.testHandler = TNAME;
    if (CSTE_VERBOSE > 1) PRINT(CRLF);

    // Data validation
    if (td->io.sym.in.key.length != 192/8)
        return "incorrect key length" CRLF
               "     " TNAME " test not activated." CRLF;
    else
        return cryptoSTE_aes_ctr_timed(td, param);
}

#undef TNAME
#define TNAME "WOLF AES CTR 256"
const char * cryptoSTE_aes_ctr_256_timed(const cryptoST_testDetail_t * td,
                                   cryptoSTE_testExecution_t * param)
{
    param->results.testHandler = TNAME;
    if (CSTE_VERBOSE > 1) PRINT(CRLF);

    // Data validation
    if (td->io.sym.in.key.length != 256/8)
        return "incorrect key length" CRLF
               "     " TNAME " test not activated." CRLF;
    else
        return cryptoSTE_aes_ctr_timed(td, param);
}

#endif // WOLFSSL_AES_COUNTER
