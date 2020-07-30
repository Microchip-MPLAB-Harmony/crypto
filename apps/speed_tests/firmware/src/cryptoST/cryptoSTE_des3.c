/*******************************************************************************
  Crypto Speed Test Source File

  Company:
    Microchip Technology Inc.

  File Name:
    cryptoST_des3.c

  Summary:
    DES and triple-DES mode encryption driver

  Description:
    This file contains functions to measure the time required 
    to perform DES and triple-DES encryption. Time is reported in clock ticks.
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
#include "cryptoSTE_malloc.h"
#include "cryptoSTE_des3.h"
#include "../test_data/cryptoSpeedTestData.h"

#include "configuration.h"
#include <wolfssl/wolfcrypt/settings.h>
#include <wolfssl/wolfcrypt/des3.h>

#define assert_dbug(X) __conditional_software_breakpoint((X))
#define VERIFY_CONSECUTIVE_DES    1

// *****************************************************************************
// *****************************************************************************
// Section: Helper routines and wrappers
// *****************************************************************************
// *****************************************************************************

#undef NO_DES
#define NO_DES // note: can't overload to support both

// *****************************************************************************
// *****************************************************************************
// Section: Local data structures and wrappers
// *****************************************************************************
// *****************************************************************************

#if !defined(NO_DES3)

/* This information is used to simplify selection of the encryption
 * driver and associated name and keySize verification.
 * Note that the default encryptor returns void.
 */
typedef int (*des3Encrypt_t)(Des3* des, byte* out, const byte* in, word32 size);
typedef int (*des3Decrypt_t)(Des3* des, byte* out, const byte* in, word32 size);
typedef struct desTest_s
{
    const char *  name;
    const int     keySize; // 8B or 24B
    const des3Encrypt_t  encrypt;
    const des3Decrypt_t  decrypt;
} desTest_t;

#if !defined(NO_DES)
static const desTest_t wolf_des_ecb = {
    .name = "WOLF DES ECB",
    .keySize = 64/8,
    .encrypt = wc_Des_EcbEncrypt,
    .decrypt = wc_Des_EcbDecrypt,
};
static const desTest_t wolf_des_cbc = {
    .name = "WOLF DES CBC",
    .keySize = 64/8,
    .encrypt = wc_Des_CbcEncrypt,
    .decrypt = wc_Des_CbcDecrypt,
};
#endif
#if !defined(NO_DES3)
static const desTest_t wolf_des3_cbc = {
    .name = "WOLF DES3 CBC",
    .keySize = (3*64)/8,
    .encrypt = wc_Des3_CbcEncrypt,
    .decrypt = wc_Des3_CbcDecrypt,
};
#if defined(WOLFSSL_DES_ECB)
/* Note: at CRYPTO=3.5.0 this may not be set in configuration.h
 * by Harmony3 and must be added after generating code.
 * */
static const desTest_t wolf_des3_ecb = {
    .name = "WOLF DES3 ECB",
    .keySize = (3*64)/8,
    .encrypt = wc_Des3_EcbEncrypt,
    .decrypt = wc_Des3_EcbDecrypt,
};
#endif // DES_ECB
#endif

// TODO: arrange for HW-accelerated w/o WolfCrypt
static const desTest_t localEntry = {
    .name = "MCHP DES3 NONE",
    .keySize = (3*64)/8,
    .encrypt = ((void*)0),
    .decrypt = ((void*)0),
};

// *****************************************************************************
// *****************************************************************************
// Section: Support routines
// *****************************************************************************
// *****************************************************************************

/* This is the generic encryption package.
 * The public entry points are defined below.
 *  */
static const char * cryptoSTE_des3des_all_timed
      ( const cryptoST_testDetail_t * td,
        cryptoSTE_testExecution_t * param,
        const desTest_t * test )
{
    // Do this prior to possible errors so that it correctly reports.
    const cryptoST_testVector_t * vector = td->rawData;
    param->results.encryption.size = vector->vector.length;
    param->results.encryption.iterations = param->parameters.iterationOverride? 
                                    param->parameters.iterationOverride
                                  : td->recommendedRepetitions;

    if (CSTE_VERBOSE > 2)
    {
        P0_UINT( " data=", vector->vector.length);
        cryptoSTE_announceVector(2, vector);
        cryptoSTE_announceDetails(2, td);
    }

    // Data validation
    if (NULL == td->io.sym.in.key.data)
        return param->results.errorMessage = "missing key or initialization data";

    byte * cipher = cryptoSTE_malloc(vector->vector.length);
    if (NULL == cipher)
        return "cannot allocate memory (" __BASE_FILE__ " line " BASE_LINE ")";
    else do // so we can use "break"
    {
        // Remove any data noise that is in the target buffer
        XMEMSET(cipher, 0, vector->vector.length);

        int ret;
        Des3 enc;
        assert_dbug(24 == td->io.sym.in.key.length);
        ret = wc_Des3_SetKey(&enc, td->io.sym.in.key.data, 
                                   td->io.sym.in.ivNonce.data, DES_ENCRYPTION);
        if (ret != 0)
        {
            param->results.errorMessage = "failed to set key"; break;
        }

        // Hold off until the serial port is finished
        PRINT_WAIT_WHILE_BUSY();

        param->results.encryption.start = SYS_TIME_CounterGet();
        for (int i = param->results.encryption.iterations; i > 0; i--)
        {
            /* Note: if vector.length is not a multiple of 16,
             *       the default encryptor will ignore the remnant. */
            (test->encrypt)(&enc, cipher, vector->vector.data, vector->vector.length);
        }
        param->results.encryption.stop = SYS_TIME_CounterGet();
        if (param->results.errorMessage) break; // out of the test routine
        param->results.encryption.startStopIsValid = true;
        
        if (param->parameters.verifyByGoldenCiphertext)
        {
            if ((NULL == td->io.sym.out.cipher.data) || (0 == td->io.sym.out.cipher.length))
                param->results.warningCount++,
                param->results.warningMessage = "can't verify cipher: no golden data"; 
            else if (XMEMCMP(cipher, td->io.sym.out.cipher.data, td->io.sym.out.cipher.length))
            { 
                param->results.errorMessage = 
                    "computed ciphertext does not match golden data";
                if (CSTE_VERBOSE)
                {
                    cryptoST_PRINT_hexLine(CRLF "..key     :", 
                            td->io.sym.in.key.data, td->io.sym.in.key.length);
                    cryptoST_PRINT_hexLine(CRLF "..ivNonce :", 
                            td->io.sym.in.ivNonce.data, td->io.sym.in.ivNonce.length);
                    cryptoST_PRINT_hexBlock(CRLF "..input   :", 
                            vector->vector.data, vector->vector.length);
                    cryptoST_PRINT_hexBlock(CRLF "..cipher  :", 
                            cipher, td->io.sym.out.cipher.length);
                    cryptoST_PRINT_hexBlock(CRLF "..golden  :",
                            td->io.sym.out.cipher.data, td->io.sym.out.cipher.length);
                    PRINT_WAIT(CRLF);
                }
                break; 
            }
        }
    } while(0);
    
    if (NULL == param->results.errorMessage) do 
    {
        if (param->parameters.verifyByDecryption)
        {
            if (1 < param->results.encryption.iterations)
            {
                param->results.warningCount++;
                param->results.warningMessage = 
                        "verification skipped: cannot recover ??? counter";
                break;
            }
            else
            {
                byte * plain = cryptoSTE_malloc(vector->vector.length);
                if (NULL == plain)
                    return "cannot allocate memory (" __BASE_FILE__ " line " BASE_LINE ")";
                else do
                {
                    Des3 dec;
                    assert_dbug(24 == td->io.sym.in.key.length);
                    if (0 != wc_Des3_SetKey
                        (&dec, td->io.sym.in.key.data, 
                               td->io.sym.in.ivNonce.data, DES_DECRYPTION))
                    { 
                        param->results.errorMessage = "setting decryption key failed"; 
                        break; 
                    }

                    // Conventional decrypt and comparison
                    if (CSTE_VERBOSE > 1) 
                        PRINT_WAIT("-- decrypting and comparing" CRLF)
                    (test->decrypt)(&dec, plain, cipher, vector->vector.length); 

                    if (XMEMCMP(plain, vector->vector.data, vector->vector.length))
                    { 
                        param->results.errorMessage = "recovered data does not match original"; 
                        if (CSTE_VERBOSE)
                        {
                            cryptoST_PRINT_hexBlock(CRLF "..rawData:",
                                    vector->vector.data, vector->vector.length);
                            cryptoST_PRINT_hexBlock(CRLF "..decrypt:",
                                    plain, vector->vector.length);
                            PRINT_WAIT(CRLF);
                        }
                        break; 
                    }
                } while(0);
                cryptoSTE_free(plain);
                if (NULL != param->results.errorMessage) 
                    break; // not really necessary, but etc.
            }
        }
    } while(0);
    
    cryptoSTE_free(cipher);
    return param->results.errorMessage;
}

// *****************************************************************************
// *****************************************************************************
// Section: External API
// *****************************************************************************
// *****************************************************************************

static const char * const badKey = "incorrect key length";
const char * cryptoSTE_des3des_timed(const cryptoST_testDetail_t * td,
                                     cryptoSTE_testExecution_t * param)
{
    param->results.testHandler = "MCHP_DES3"; // establish a default name
    const desTest_t * test = NULL;

    switch(td->technique)
    {
#if !defined(NO_DES)
    case ET_DES:
        if (EM_CBC == td->mode)
            test = (param->parameters.useLocalDriverEntryPoints)?
                    &localEntry : &wolf_des_cbc;
        else if (EM_ECB == td->mode)
            test = (param->parameters.useLocalDriverEntryPoints)?
                    &localEntry : &wolf_des_ecb;
        break;
#endif
#if !defined(NO_DES3)
#if defined(NO_DES)
    case ET_DES: // accept these as well: gives same answer but slower
#endif
    case ET_DES3:
        if (EM_CBC == td->mode)
        {
            assert_dbug(8 == td->io.sym.in.ivNonce.length);
            test = (param->parameters.useLocalDriverEntryPoints)?
                        &localEntry : &wolf_des3_cbc;
        }
#if defined(WOLFSSL_DES_ECB)
        else if (EM_ECB == td->mode)
            test = (param->parameters.useLocalDriverEntryPoints)?
                        &localEntry : &wolf_des3_ecb;
#endif // DES_ECB
        break;
#endif
    default:
        test = NULL;
        break;
    };
    
    if (CSTE_VERBOSE > 1) PRINT(CRLF);
    if ((NULL == test) || (NULL == test->encrypt) || (NULL == test->decrypt))
        return param->results.errorMessage = 
                "DES or DES3 not available for this mode";
    else
    {
        param->results.testHandler = test->name;
        if (td->io.sym.in.key.length != test->keySize)
            return param->results.errorMessage = badKey;
        else
            return cryptoSTE_des3des_all_timed(td, param, test);
    }
}
#endif // NO DES
