/*******************************************************************************
  Crypto Speed Test Source File

  Company:
    Microchip Technology Inc.

  File Name:
    cryptoST_aes_ecb.c

  Summary:
    AES ECB mode encryption driver

  Description:
    This file contains functions to measure the time required 
    to perform AES EBC encryption. Time is reported in clock ticks.

    Electronic Code Book (ECB) mode is notable because 
    an initialization vector (IV) is not required.
 
    The useLocalDriverEntryPoints option is supported
    and provides both WC and CRYA-direct interfaces. Note that if
    WC is configured with UseHardwareCryptography=TRUE, the
    WC interface will invoke the CRYA HW in all cases.
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
#include "cryptoSTE_aes_ecb.h"
#include "../test_data/cryptoSpeedTestData.h"

// theory: one of these "fixes" build-time issues with wolfssl
#include <stddef.h>
#include <string.h>
#include <stdbool.h>
#include "cryptoSTE_malloc.h"

#include "configuration.h"
#include <wolfssl/wolfcrypt/settings.h>
#include <wolfssl/wolfcrypt/aes.h>

#define VERIFY_CONSECUTIVE_AES    1

// *****************************************************************************
// *****************************************************************************
// Section: Helper routines and wrappers
// *****************************************************************************
// *****************************************************************************

/* Differential timing is supported only on selected platforms.
 * The hardware-available flag is set when H3 is configured
 * with "Use Hardware Cryptography", but meaningful results can
 * only be obtained when this particular algorithm has HW support
 * disabled, otherwise WC calls are redirected to the hardware.
 */

#if defined(WOLFSSL_HAVE_MCHP_HW_CRYPTO_AES_HW_U2238)
// TODO: add HW support for E54
#endif

#if defined(WOLFSSL_HAVE_MCHP_HW_CRYPTO_AES_HW_U2803) \
 || defined(WOLFSSL_HAVE_MCHP_HW_CRYPTO_AES_HW_U2805)
#include "crya/crya.h"

// Wrappers to fix the parameter signature
__attribute__((used)) static int crya_aes_128_encrypt
            (Aes* aes, byte* out, const byte* in, word32 size)
{
    size_t blocks = size / AES_BLOCK_SIZE; // truncate if non-multiple

    while(blocks > 0) 
    {
        crya_aes128_encrypt((uint8_t*)aes->key, aes->keylen, in, out);
        out += AES_BLOCK_SIZE;
        in  += AES_BLOCK_SIZE;
        blocks--;
    }
    return 0;
}
__attribute__((used)) static int crya_aes_128_decrypt
            (Aes* aes, byte* out, const byte* in, word32 size)
{
    size_t blocks = size / AES_BLOCK_SIZE; // truncate if non-multiple

    while(blocks > 0) 
    {
        crya_aes128_decrypt((uint8_t*)aes->key, aes->keylen, in, out);
        out += AES_BLOCK_SIZE;
        in  += AES_BLOCK_SIZE;
        blocks--;
    }
    return 0;
}
#endif // U2803 or U2805

#if defined(WOLFSSL_HAVE_MCHP_HW_CRYPTO_AES_HW_U2805)
// Wrappers to fix the parameter signature
#error TODO: add the wrappers
#endif // U2805

// *****************************************************************************
// *****************************************************************************
// Section: Local data structures and wrappers
// *****************************************************************************
// *****************************************************************************

#if defined(HAVE_AES_ECB)
/* This information is used to simplify selection of the encryption
 * driver and associated name and keySize verification.
 * Note that the default encryptor returns void.
 */
typedef int (*ecbSetKey_t)(Aes* aes, const byte* userKey, word32 keylen,
                                     const byte* iv, int dir);
typedef int (*ecbEncrypt_t)(Aes* aes, byte* out, const byte* in, word32 size);
typedef int (*ecbDecrypt_t)(Aes* aes, byte* out, const byte* in, word32 size);
typedef struct ecbTest_s
{
    const char *  name;
    const int     keySize;
    const ecbSetKey_t   setKey;
    const ecbEncrypt_t  encrypt;
    const ecbDecrypt_t  decrypt;
} ecbTest_t;

#if defined(WOLFSSL_AES_128) \
 && (defined(WOLFSSL_HAVE_MCHP_HW_CRYPTO_AES_HW_U2803) \
  || defined(WOLFSSL_HAVE_MCHP_HW_CRYPTO_AES_HW_U2805))
/* This is necessary because WolfCrypt sometimes transposes the key
 * and sometimes it does not, depending on the HW-enable, but CRYA
 * needs the key to be little-endian every time. 
 */
#if 0
static uint32_t endian32(const uint32_t input)
{
    return input;
    uint32_t answer;
    uint32_t value = input; // make sure the source is in RAM
    
    uint8_t * A = (uint8_t*)&answer;
    uint8_t * V = ((uint8_t*)(&value))+sizeof(value)-1;
    for (int i = 0; i < sizeof(answer); i++)
        *A++ = *V--;
    
    return answer;
}

int crya_ecb_SetKey(Aes* aes, const byte* userKey, word32 keylen,
                                     const byte* iv, int dir)
{
    assert_dbug(keylen <= sizeof(aes->devKey));
    aes->keylen = keylen;
    // ignore iv and dir for crya

    // Endian swap here because CRYA is big-endian and we are not.
    uint32_t * dk = (uint32_t *)aes->key;
    assert_dbug(dk && (0 == ((uint32_t)dk%4)));
    uint32_t * uk = (uint32_t *)userKey;
    assert_dbug(uk && (0 == ((uint32_t)uk%4)));
    
    for (int i = 0; i < keylen/sizeof(*uk); i++)
        dk[i] = endian32(uk[i]);
    return 0;
}
#else
// For SAML11-CRYA do not re-order the bytes
int crya_ecb_SetKey(Aes* aes, const byte* userKey, word32 keylen,
                                     const byte* iv, int dir)
{ 
    memcpy(aes->key, userKey, keylen); 
    aes->keylen = keylen;
    return 0;
}
#endif

static const ecbTest_t cyra_128 = {
    .name = "CRYA AES ECB 128",
    .keySize = 128/8,
    .setKey  = crya_ecb_SetKey,
    .encrypt = crya_aes_128_encrypt,
    .decrypt = crya_aes_128_decrypt,
};
#else
#define cyra_128    (*((ecbTest_t*)0))
#endif

#if defined(WOLFSSL_HAVE_MCHP_HW_CRYPTO_AES_HW_U2805)
// Not supported in SAML11
static const ecbTest_t cyra_192 = {
    .name = "CRYA AES ECB 192",
    .keySize = 192/8,
    .setKey  = crya_ecb_SetKey,
    .encrypt = crya_aes_192_encrypt,
    .decrypt = crya_aes_192_decrypt,
};

static const ecbTest_t crya_256 = {
    .name = "CRYA AES ECB 256",
    .keySize = 256/8,
    .setKey  = crya_aes_SetKey,
    .encrypt = crya_aes_256_encrypt,
    .decrypt = crya_aes_256_decrypt,
};
#else
#define crya_192    (*((ecbTest_t*)0))
#define crya_256    (*((ecbTest_t*)0))
#endif

#if defined(WOLFSSL_AES_128)
static const ecbTest_t wolf_128 = {
    .name = "WOLF AES ECB 128",
    .keySize = 128/8,
    .setKey  = wc_AesSetKey,
    .encrypt = wc_AesEcbEncrypt,
    .decrypt = wc_AesEcbDecrypt,
};
#endif
#if defined(WOLFSSL_AES_192)
static const ecbTest_t wolf_192 = {
    .name = "WOLF AES ECB 128",
    .keySize = 192/8,
    .setKey  = wc_AesSetKey,
    .encrypt = wc_AesEcbEncrypt,
    .decrypt = wc_AesEcbDecrypt,
};
#endif
#if defined(WOLFSSL_AES_256)
static const ecbTest_t wolf_256 = {
    .name = "WOLF AES ECB 128",
    .keySize = 256/8,
    .setKey  = wc_AesSetKey,
    .encrypt = wc_AesEcbEncrypt,
    .decrypt = wc_AesEcbDecrypt,
};
#endif

// *****************************************************************************
// *****************************************************************************
// Section: Support routines
// *****************************************************************************
// *****************************************************************************

/* This is the generic encryption package.
 * The public entry points are defined below.
 *  */
static const char * cryptoSTE_aes_ecb_all_timed(const cryptoST_testDetail_t * td,
                                      cryptoSTE_testExecution_t * param,
                                      const ecbTest_t * test)
{
    const cryptoST_testVector_t * vector = td->rawData;
    
    if (CSTE_VERBOSE > 2)
    {
        P0_UINT( " data=", vector->vector.length);
        cryptoSTE_announceVector(2, vector);
        cryptoSTE_announceDetails(2, td);
    }

    // Do this prior to possible errors so that it correctly reports
    // with any error message.
    param->results.encryption.size = vector->vector.length;
    param->results.encryption.iterations = param->parameters.iterationOverride? 
                                    param->parameters.iterationOverride
                                  : td->recommendedRepetitions;

    // Data validation
    if (NULL == td->io.sym.in.key.data)
        return param->results.errorMessage = "missing key or initialization data";

    byte * cipher = cryptoSTE_malloc(vector->vector.length);
    if (NULL == cipher)
        return "cannot allocate memory (" __BASE_FILE__ " line " BASE_LINE ")";
    else do // so we can use "break"
    {
        if (NULL != td->io.sym.in.ivNonce.data)
            param->results.warningCount++,
            param->results.warningMessage = "IV provided but not required"; 

        int ret;
        Aes enc;
        ret = (test->setKey)(&enc, td->io.sym.in.key.data, td->io.sym.in.key.length,
                                 NULL, AES_ENCRYPTION);
        if (ret != 0) 
            { param->results.errorMessage = "failed to set key"; break; }

        // Hold off until the serial port is finished
        PRINT_WAIT_WHILE_BUSY();

        // Remove any data noise that is in the target buffer
        XMEMSET(cipher, 0, sizeof(cipher));

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
                    "computed ciphertext does not match golden data (was iterate==1?)";
                if (CSTE_VERBOSE)
                {
                    cryptoST_PRINT_hexLine(CRLF "..input :", 
                            vector->vector.data, vector->vector.length);
                    cryptoST_PRINT_hexLine(CRLF "..cipher:", 
                            cipher, vector->vector.length);
                    cryptoST_PRINT_hexLine(CRLF "..golden:",
                            td->io.sym.out.cipher.data, td->io.sym.out.cipher.length);
                    cryptoST_PRINT_hexLine(CRLF "..key   :", 
                            td->io.sym.in.key.data, td->io.sym.in.key.length);
                    PRINT_WAIT(CRLF);
                }
                break; 
            }
        }
    } while(0);
    
#if defined(HAVE_AES_DECRYPT)
    if (NULL == param->results.errorMessage) do 
    {
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
                    param->results.errorMessage = 
                        "cannot allocate memory (" __BASE_FILE__ " line " BASE_LINE ")";
                else do
                {
                    Aes dec;
                    if (0 != (test->setKey)(&dec, 
                                             td->io.sym.in.key.data, td->io.sym.in.key.length, 
                                             NULL, AES_DECRYPTION))
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
                            cryptoST_PRINT_hexLine(CRLF "..rawData:",
                                    vector->vector.data, vector->vector.length);
                            cryptoST_PRINT_hexLine(CRLF "..decrypt:",
                                    plain, vector->vector.length);
                            PRINT_WAIT(CRLF);
                        }
                        break; 
                    }
                } while(0);
                if (plain)
                    cryptoSTE_free(plain);
                if (NULL != param->results.errorMessage) 
                    break; // not really necessary, but etc.
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

static const char * badKey = "incorrect key length";
const char * cryptoSTE_aes_ecb_timed(const cryptoST_testDetail_t * td,
                                     cryptoSTE_testExecution_t * param)
{
    if (EM_ECB != td->mode)
        return "test invoked for incorrect mode";

    param->results.testHandler = "MCHP AES_ECB"; // establish a default name
    const ecbTest_t * test = NULL;

    switch(td->technique)
    {
#if defined(WOLFSSL_AES_128)
    case ET_AES_128:
        test = (param->parameters.useLocalDriverEntryPoints)?
                    &cyra_128 : &wolf_128;
        break;
#endif
#if defined(WOLFSSL_AES_192)
    case ET_AES_192:
        test = (param->parameters.useLocalDriverEntryPoints)?
                    &crya_192 : &wolf_192;
        break;
#endif
#if defined(WOLFSSL_AES_256)
    case ET_AES_256:
        test = (param->parameters.useLocalDriverEntryPoints)?
                    &crya_256 : &wolf_256;
        break;
#endif
    default:
        test = NULL;
        break;
    };
    
    if (CSTE_VERBOSE > 1) PRINT(CRLF);    
    if (NULL == test)
        return param->results.errorMessage = 
                "AES_ECB not available for this key size";
    else
    {
        param->results.testHandler = test->name;
        if (td->io.sym.in.key.length != test->keySize)
            return param->results.errorMessage = badKey;
        else
            return cryptoSTE_aes_ecb_all_timed(td, param, test);
    }
}
#endif // HAVE_AES_ECB
