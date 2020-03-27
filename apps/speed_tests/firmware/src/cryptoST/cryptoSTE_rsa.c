/*******************************************************************************
  Crypto Speed Test Source File

  Company:
    Microchip Technology Inc.

  File Name:
    cryptoST_rsa

  Summary:
    RSA encryption driver for testing execution speed

  Description:
    This file contains functions to measure the time required 
    to perform RSA encryption. Time is reported in clock ticks.
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
#include "cryptoSTE_malloc.h"
#include "cryptoSTE_rsa.h"
#include "../test_data/cryptoSpeedTestData.h"

#include <string.h> // for memcmp()

#include "configuration.h"
#include <wolfssl/wolfcrypt/settings.h>
#include <wolfssl/wolfcrypt/rsa.h>
#include <wolfssl/wolfcrypt/sha.h>

#define VERIFY_CONSECUTIVE_DES    1
#define assert_dbug(X) __conditional_software_breakpoint((X))

// *****************************************************************************
// *****************************************************************************
// Section: Helper routines and wrappers
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
// *****************************************************************************
// Section: Local data structures and wrappers
// *****************************************************************************
// *****************************************************************************

#if !defined(NO_RSA)

/* This information is used to simplify selection of the encryption
 * driver and associated name and keySize verification.
 * Note that the default encripter returns void.
 */
typedef struct rsaTest_s rsaTest_t;
typedef const char * rsa_timer_t
      ( const cryptoST_testDetail_t * const td,
        cryptoSTE_testExecution_t * const param,
        const rsaTest_t * const test );
typedef const char * rsa_sha_t(const cryptoST_testData_t *, uint8_t *);

typedef struct rsaTest_s
{
    const char * name;
    rsa_timer_t * timer;
    rsa_sha_t * hash;
} rsaTest_t;

// *****************************************************************************
// *****************************************************************************
// Section: Support routines
// *****************************************************************************
// *****************************************************************************
static void printAll(const cryptoST_testDetail_t * const td)
{
    cryptoST_PRINT_hexLine(CRLF ".........n:", 
            td->io.rsav.in.n->data, td->io.rsav.in.n->length);
    cryptoST_PRINT_hexLine(CRLF ".........e:",
            td->io.rsav.in.e->data, td->io.rsav.in.e->length);
    cryptoST_PRINT_hexLine(CRLF "........em:", 
            td->io.rsav.in.em->data, td->io.rsav.in.em->length);
    cryptoST_PRINT_hexLine(CRLF ".......raw:",
            td->rawData->vector.data, td->rawData->vector.length);
    PRINT_WAIT(CRLF);
}

static const char * rsa_sha256
        (const cryptoST_testData_t * readOnly, uint8_t * hash)
{
    Sha256 sha256;
    const char * answer = 0;
    
    if ((0 != wc_InitSha256(&sha256))
     || (0 != wc_Sha256Update(&sha256,
                readOnly->data, readOnly->length))
     || (0 != wc_Sha256Final(&sha256, hash)))
    { answer = "error during hash construction"; }

    wc_Sha256Free(&sha256);
    return answer;
}

// *****************************************************************************
// *****************************************************************************
// Section: Timed driver
// *****************************************************************************
// *****************************************************************************
__attribute__((used))
static const char * cryptoSTE_rsa_verify_timed
                ( const cryptoST_testDetail_t * const td,
                    cryptoSTE_testExecution_t * const param,
                              const rsaTest_t * const test )
{
    /* Instantiate permanently because RsaKey is a 4k object that
     * is obscure and could overflow the stack for the unwary.
     * The biggest penalty is that other objects are beyond
     * SP+4000 which requires the use of double-word 
     * opcodes (.W) for pointers.
     * */
    static RsaKey rsaKey;
    
    // Do this prior to possible errors so that it reports correctly.
    const cryptoST_testVector_t * vector = td->rawData;
    param->results.encryption.size = vector->vector.length;
    param->results.encryption.iterations = param->parameters.iterationOverride? 
                                    param->parameters.iterationOverride
                                  : td->recommendedRepetitions;

    /* There is magic here. The WC algorithm builds a full
     * ASN.1 encoding of the recovered hash. So we fake the
     * header and put our hash in line with it, but rig
     * it so that the header comes from non-volatile memory. */
    const uint8_t asn1_header[] = { // read-only
        0x30, 0x31, 0x30, 0x0D, 0x06, 0x09, 0x60, 0x86,
        0x48, 0x01, 0x65, 0x03, 0x04, 0x02, 0x01, 0x05,
        0x00, 0x04, 0x20 }; // 19 bytes
    uint8_t hashSignature[sizeof(asn1_header) + WC_SHA256_DIGEST_SIZE] = {0};
    memcpy(hashSignature, asn1_header, ALENGTH(asn1_header));
    
    /* Instantiate buffer before entering the timed loop. */
    uint8_t rsaSignature[ALENGTH(hashSignature)] = {0};
    int decSigLen = 0;

    param->results.encryption.start = SYS_TIME_CounterGet();
    for (int i = param->results.encryption.iterations; i > 0; i--)
    {
        /* Calculate hash digest of the plaintext message */
        assert_dbug(test->hash);
        param->results.errorMessage = 
            (test->hash)(&vector->vector, &hashSignature[ALENGTH(asn1_header)]);
        if (0 == param->results.errorMessage)
        {
            if ((0 != wc_InitRsaKey(&rsaKey, NULL))
             || (0 != mp_read_unsigned_bin(&rsaKey.n,
                td->io.rsav.in.n->data, td->io.rsav.in.n->length))
             || (0 != mp_read_unsigned_bin(&rsaKey.e,
                td->io.rsav.in.e->data, td->io.rsav.in.e->length)))
            { param->results.errorMessage = "key construction failed"; }
            else /* Use n,e,em to compute the (supposedly) same info. */
            {
                decSigLen = wc_RsaSSL_Verify( 
                        td->io.rsav.in.em->data, td->io.rsav.in.em->length,
                        rsaSignature, ALENGTH(rsaSignature),
                        &rsaKey);
                if (decSigLen < 0)
                {
                    param->results.errorMessage = "signature recovery failed";
                    decSigLen = ALENGTH(rsaSignature); // self protection
                }
            }

            wc_FreeRsaKey(&rsaKey);
        }

        param->results.encryption.stop = SYS_TIME_CounterGet();
        if (param->results.errorMessage) break; // out of the test routine
        param->results.encryption.startStopIsValid = true;
    } // END TIMED LOOP
    
    /* Success is when the recovered result matches the SHA result
     * in both length and content.   */
    if (0 == param->results.errorMessage)
    {
        if (decSigLen != sizeof(hashSignature))
        { param->results.errorMessage = "incorrect computed length"; }
        else if (0 != memcmp(hashSignature, rsaSignature, decSigLen))
        { param->results.errorMessage = "computed signature mismatch"; }
    }
    // else param->results.errorMessage = "no error";
    
    if (0 != param->results.errorMessage)
    {
        printf(CRLF "%s", param->results.errorMessage);
        printf(CRLF "sizeof decSigLen:%d         hash:%d", 
                decSigLen, sizeof(hashSignature));
        printAll(td);
        cryptoST_PRINT_hexBlock(CRLF "..computed:", rsaSignature, decSigLen);
        cryptoST_PRINT_hexBlock(CRLF "......hash:", hashSignature, ALENGTH(hashSignature));
        printf(CRLF);
    }
        
    __NOP();
    return param->results.errorMessage;
}

__attribute__((used))
static const char * cryptoSTE_rsa_sign_timed
      ( const cryptoST_testDetail_t * const td,
        cryptoSTE_testExecution_t * const param,
        const rsaTest_t * const test )
{
    // Do this prior to possible errors so that it correctly reports.
    const cryptoST_testVector_t * vector = td->rawData;
    param->results.encryption.size = vector->vector.length;
    param->results.encryption.iterations = param->parameters.iterationOverride? 
                                    param->parameters.iterationOverride
                                  : td->recommendedRepetitions;

    RsaKey key;
    int irk = wc_InitRsaKey(&key, ((void*)0));
    int res = wc_RsaEncryptSize(&key);

    // int mrk = wc_MakeRsaKey(key, int size, long e, WC_RNG *rng);
    int rpkdr = wc_RsaPublicKeyDecodeRaw(
        td->io.rsas.in.n->data, td->io.rsas.in.n->length,
        td->io.rsas.in.e->data, td->io.rsas.in.e->length,
        &key);	
    res = wc_RsaEncryptSize(&key);

#if 1 // VERIFY_KEYS    
    byte * e = malloc(td->io.rsas.in.e->length);
    uint eSize = td->io.rsas.in.e->length; // in/out parameter
    byte * n = malloc(td->io.rsas.in.n->length);
    uint nSize = td->io.rsas.in.n->length; // in/out parameter
    int rfpk = wc_RsaFlattenPublicKey(&key,
            e, &eSize, n, &nSize);

    // Returned values are sometimes shortened, but never longer
    if(memcmp(e, &td->io.rsas.in.e->data[td->io.rsas.in.e->length-eSize], eSize)
    || memcmp(n, &td->io.rsas.in.n->data[td->io.rsas.in.n->length-nSize], nSize))
    {
        param->results.errorMessage = "Oops key";
        cryptoST_PRINT_hexBlock(CRLF ".........e:",
                td->io.rsas.in.e->data, td->io.rsas.in.e->length);
        cryptoST_PRINT_hexBlock(CRLF ".....new.e:", e, eSize);
        cryptoST_PRINT_hexBlock(CRLF ".........n:", 
                td->io.rsas.in.n->data, td->io.rsas.in.n->length);
        cryptoST_PRINT_hexBlock(CRLF ".....new.n:", n, nSize);
        PRINT_WAIT(CRLF);
    }
#endif // VERIFY_KEYS    

#define SHA256_SIZE (256/8) // bits/(bits-per-byte)
    uint8_t hash[SHA256_SIZE] = {0};
    wc_Sha256Hash(vector->vector.data, vector->vector.length, hash);
    
    size_t cipherSize = 256;
    uint8_t * cipher = malloc(cipherSize);

    RNG rng; // necessary evil?
    wc_InitRng(&rng);
        int rpe = wc_RsaPublicEncrypt(
        hash, SHA256_SIZE, 
        cipher, cipherSize,
        &key, &rng);
    __NOP();
    if (memcmp(cipher, td->io.rsas.out.cipher.data, cipherSize))
    {
        param->results.errorMessage = "Cipher text does not match golden data";
        cryptoST_PRINT_hexBlock(CRLF "....  hash:", hash, SHA256_SIZE);
        cryptoST_PRINT_hexBlock(CRLF "....cipher:", cipher, cipherSize);
        cryptoST_PRINT_hexLine(CRLF "....golden:",
                td->io.rsas.out.cipher.data, td->io.rsas.out.cipher.length);
        cryptoST_PRINT_hexLine(CRLF ".........n:", 
                td->io.rsas.in.n->data, td->io.rsas.in.n->length);
        cryptoST_PRINT_hexLine(CRLF ".........e:",
                td->io.rsas.in.e->data, td->io.rsas.in.e->length);
        cryptoST_PRINT_hexLine(CRLF "....vector:",
                vector->vector.data, vector->vector.length);
        PRINT_WAIT(CRLF);
    }
        
    __NOP();
    free(cipher);
    int frk = wc_FreeRsaKey(&key);


    (void)rfpk;
    (void)rpe;
    (void)irk;
    (void)res;
    (void)rpkdr;
    (void)frk;
    return param->results.errorMessage;


#if 0
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
            { param->results.errorMessage = "failed to set key"; break; }

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
#endif
}

// *****************************************************************************
// *****************************************************************************
// Section: External API
// *****************************************************************************
// *****************************************************************************
#define NAME    "WOLF RSA"
const char * cryptoSTE_rsa_timed(const cryptoST_testDetail_t * td,
                                   cryptoSTE_testExecution_t * param)
{
    __NOP();
    rsaTest_t test = {0};
    
#if !defined(NO_RSA)
    switch(td->technique)
    {
    case ET_PK_RSA_SIGN:
       //     test.timer = cryptoSTE_rsa_sign_timed;
        switch(td->io.rsas.in.hashmode)
        {
        case ET_SHA_224:
            test.name = NAME " VERIFY224";
            // test.hash = rsa_sha256;
            break;
        case ET_SHA_256:
            test.name = NAME " VERIFY256";
            // test.hash = rsa_sha256;
            break;
        default:
            break;
        };
        break;

    case ET_PK_RSA_VERIFY:
        test.timer = cryptoSTE_rsa_verify_timed;
        switch(td->io.rsav.in.hashmode)
        {
        case ET_SHA_224:
            test.name = NAME " SIGN224";
            // test.hash = rsa_sha224;
            break;
        case ET_SHA_256:
            test.name = NAME " SIGN256";
            test.hash = rsa_sha256;
            break;
        default:
            break;
        };
        break;

    default:
        break;
    };
#endif
    
    if (test.timer && test.hash && test.name)
    {
        param->results.testHandler = test.name;
        return (test.timer)(td, param, &test);
    }
    else
    {
        param->results.testHandler = "RSA";
        return param->results.errorMessage = 
                "RSA not available for this mode";
    }
}
#endif // NO DES
