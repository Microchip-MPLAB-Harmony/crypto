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

#include <stdint.h>
#include <string.h> // for memcmp()

#include "configuration.h"
#include "cryptoSTE_definitions.h"
#include "cryptoSTE_print.h"
#include "cryptoSTE_announce.h"
#include "cryptoSTE_malloc.h"
#include "cryptoSTE_rsa.h"
#include "../test_data/cryptoSpeedTestData.h"

#include <wolfssl/wolfcrypt/settings.h>
#include <wolfssl/wolfcrypt/rsa.h>
#include <wolfssl/wolfcrypt/sha.h>

#define VERIFY_KEYS // optional feature
#define assert_dbug(X) __conditional_software_breakpoint((X))

// *****************************************************************************
// *****************************************************************************
// Section: Helper routines and wrappers
// *****************************************************************************
// *****************************************************************************

/* Optimize what buffer space might be required. */
#if defined(WOLFSSL_SHA512)
#define SHA_BUFFER_SIZE     (512/8)
#define SHA_HEADER_SIZE     19
#elif defined(WOLFSSL_SHA384)
#define SHA_BUFFER_SIZE     (384/8)
#define SHA_HEADER_SIZE     19
#elif !defined(NO_SHA256)
#define SHA_BUFFER_SIZE     (256/8)
#define SHA_HEADER_SIZE     19
#elif !defined(NO_SHA224)
#define SHA_BUFFER_SIZE     (224/8)
#define SHA_HEADER_SIZE     19
#endif

/* This may need to be tweaked for low-memory devices. */
#define RSA_SIGNATURE_SIZE  4096

// *****************************************************************************
// *****************************************************************************
// Section: Local data structures and wrappers
// *****************************************************************************
// *****************************************************************************

#if !defined(NO_RSA)

/* This information is used to simplify selection of the encryption
 * driver and associated name and keySize verification.
 */
typedef struct rsaTest_s rsaTest_t;
typedef const char * rsa_timer_t
      ( const cryptoST_testDetail_t * const td,
        cryptoSTE_testExecution_t * const param,
        const rsaTest_t * const test );
typedef const char * rsa_sha_t(const cryptoST_testData_t *, uint8_t *);

typedef struct rsaTest_s
{
    const char    * name;
    rsa_timer_t   * timer;
    rsa_sha_t     * hash;
    uint            hashSize;
    const uint8_t * asn1_header;
    const size_t    asn1_size;
} rsaTest_t;

// *****************************************************************************
// *****************************************************************************
// Section: Support routines
// *****************************************************************************
// *****************************************************************************
static void printAll_verify(const cryptoST_testDetail_t * const td)
{
    cryptoST_PRINT_hexLine(CRLF ".........n:", 
            td->io.rsav.in.n->data, td->io.rsav.in.n->length);
    if (td->io.rsav.in.e)
        cryptoST_PRINT_hexLine(CRLF ".........e:",
                td->io.rsav.in.e->data, td->io.rsav.in.e->length);
    if (td->io.rsav.in.d)
        cryptoST_PRINT_hexLine(CRLF ".........d:",
                td->io.rsav.in.d->data, td->io.rsav.in.d->length);
    cryptoST_PRINT_hexLine(CRLF "........em:", 
            td->io.rsav.in.em->data, td->io.rsav.in.em->length);
    cryptoST_PRINT_hexLine(CRLF ".......raw:",
            td->rawData->vector.data, td->rawData->vector.length);
    PRINT_WAIT(CRLF);
}

static void printAll_sign(const cryptoST_testDetail_t * const td)
{
    /* Its not illegal to dereference a null pointer in MIPS hdwe. */
    if (0 == td->io.rsas.in.der) printf(CRLF "der == null");
    else cryptoST_PRINT_hexLine(CRLF ".......der:", 
            td->io.rsas.in.der->data, td->io.rsas.in.der->length);
    if (0 == td->rawData) printf(CRLF "raw == null");
    else cryptoST_PRINT_hexLine(CRLF ".......raw:",
            td->rawData->vector.data, td->rawData->vector.length);
    PRINT_WAIT(CRLF);
}

#if !defined(NO_SHA224)
static const char * rsa_sha224
        (const cryptoST_testData_t * readOnly, uint8_t * hash)
{
    Sha224 sha224;
    const char * answer = 0;
    
    if (0 != wc_InitSha224(&sha224))
    { answer = "unable to initialize SHA224"; }
    else
    {
        if ((0 != wc_Sha224Update(&sha224,
                   readOnly->data, readOnly->length))
         || (0 != wc_Sha224Final(&sha224, hash)))
       { answer = "error during SHA224 construction"; }

       wc_Sha224Free(&sha224);
    }
    return answer;
}
#endif // SHA224

#if !defined(NO_SHA256)
static const char * rsa_sha256
        (const cryptoST_testData_t * readOnly, uint8_t * hash)
{
    Sha256 sha256;
    const char * answer = 0;
    
    if (0 != wc_InitSha256(&sha256))
    { answer = "unable to initialize SHA256"; }
    else
    {
        if ((0 != wc_Sha256Update(&sha256,
                   readOnly->data, readOnly->length))
         || (0 != wc_Sha256Final(&sha256, hash)))
       { answer = "error during SHA256 construction"; }

       wc_Sha256Free(&sha256);
    }
    return answer;
}
#endif // SHA256

/* RSA Signature Primitive of PKCS#1 using N,D key elements.
   This function mimics the wc_RsaSSL_Sign() parameter order. */
static int RSASP1_ND(
        const uint8_t * const input, const size_t inputLength,
              uint8_t * const output, const size_t outputLength,
               RsaKey * key, const char ** const cryptSTerror)
{
    int wolfSSLresult;
    const char * answer = 0;
    mp_int base, computed; // ~140 words on the stack

    do
    {
        /* Perform the calculation using little-endian structures. */
        if (MP_OKAY != (wolfSSLresult = mp_read_unsigned_bin(
                    &base, input, inputLength)))
        { answer = "input encoding failed"; break; }
        else if (MP_OKAY != (wolfSSLresult = mp_exptmod(
                    &base, &key->d, &key->n, &computed)))
        { answer = "exponentiation failed"; break; }

        const size_t finalLength = computed.used * sizeof(computed.dp[0]);

        /* Convert the results to big-endian order for posterity. */
        if (finalLength > outputLength)
        { answer = "imminent buffer overflow"; break; }
        else if (MP_OKAY != (wolfSSLresult = mp_to_unsigned_bin(&computed, output)))
        { answer = "final conversion failure"; break; }

        return finalLength;
    } while (0);
    
    *cryptSTerror = answer;
    return wolfSSLresult;
}

/* EMSA-PKCS1-v1_5 reqiures that the given hash value be padded to a
   fixed size block before encryption. */
static uint8_t * PKCSpadding(uint8_t * bufferPtr, size_t PS)
{
    PS -= 3; // don't count the non-FF
    assert_dbug(PS > 8); // rule from EMSA-PKCS1-v1_5

    *bufferPtr++ = 0x00;
    *bufferPtr++ = 0x01;
    for (int i = PS; i > 0; i--)
        *bufferPtr++ = 0xFF;
    *bufferPtr++ = 0x00;
    return bufferPtr;
}

// *****************************************************************************
// *****************************************************************************
// Section: Timed drivers
// *****************************************************************************
// *****************************************************************************
#if !defined(NO_RSA) && defined(SHA_BUFFER_SIZE)
/* Instantiated statically because RsaKey is a 4kB object that
 * is obscure and could overflow the stack for the unwary.
 * */
static RsaKey rsaKey;

// *****************************************************************************
// Driver using N,D and explicit exponentiation
// *****************************************************************************
__attribute__((used))
static const char * cryptoSTE_rsa_exptmod_timed
                ( const cryptoST_testDetail_t * const td,
                    cryptoSTE_testExecution_t * const param,
                              const rsaTest_t * const test )
{
    // Do this prior to possible errors so that it reports in all cases.
    const cryptoST_testVector_t * const vector = td->rawData;
    param->results.errorMessage = 0;
    param->results.encryption.size = vector->vector.length;
    param->results.encryption.iterations = param->parameters.iterationOverride? 
                                    param->parameters.iterationOverride
                                  : td->recommendedRepetitions;

    /* Statically defined to avoid overloading the stack. */
    static uint8_t rsaSignature[RSA_SIGNATURE_SIZE/8];
    memset(rsaSignature, 0, ALENGTH(rsaSignature));
    size_t rsaSize = 0;

    /* Initialize the buffers including the ANS1 header
     * before entering the timed loop. 
     * See the comment below about ASN1 header magic. */
    assert_dbug(SHA_BUFFER_SIZE >= test->hashSize);
    assert_dbug(SHA_HEADER_SIZE >= test->asn1_size);
    #define RSA_EXPTMOD_PADDED_SIZE   (RSA_SIGNATURE_SIZE/8)

    size_t ans1_exptmod_header_size = 0;
    uint8_t hashed[RSA_EXPTMOD_PADDED_SIZE];
    uint8_t * DER_data_ptr = hashed; // real data starts here

    if (0 != (param->results.wolfSSLresult = wc_InitRsaKey(&rsaKey, NULL)))
    { param->results.errorMessage = "key initialization failed"; }
    else
    {
        /* Load the key structure with N and D before starting the timer. */
        if ((0 != mp_read_unsigned_bin(&rsaKey.n,
            td->io.rsav.in.n->data, td->io.rsav.in.n->length))
            || (0 != mp_read_unsigned_bin(&rsaKey.d,
            td->io.rsav.in.d->data, td->io.rsav.in.d->length)))
        { param->results.errorMessage = "key construction failed"; 
        param->results.wolfSSLresult = -1; }
        else
        {
            if (test->hash)
            {
                memset(hashed, 0, ALENGTH(hashed));

                /* There are three components to the completed hash buffer:
                * <  PKCS#1 header  >< DER header ><hash result>
                * <0x00|0x01|PS|0x00><given string>< hashSize  >
                * We need to build all three before applying encryption.
                * PS pads the buffer to be same size as the finished 
                * message, which is the same as the key length. */
                const size_t notPKCS = wc_RsaEncryptSize(&rsaKey) // emLength
                            - (test->asn1_size + test->hashSize); // tLen
                DER_data_ptr = PKCSpadding(hashed, notPKCS);

                /* Append the DER header as well. */
                assert_dbug(test->asn1_header); // verify a header is provided
                memcpy(DER_data_ptr, test->asn1_header, test->asn1_size);
                ans1_exptmod_header_size = (DER_data_ptr - hashed) + test->asn1_size;
            }

            param->results.encryption.start = SYS_TIME_CounterGet();
            for (int i = param->results.encryption.iterations; i > 0; i--)
            {
                /* Optionally calculate hash digest of the plaintext message.
                Required for RSASSA-PKCS1-V1_5-SIGN but not RSASP1. */
                if (0 == test->hash)
                {
                    /* Encrypt the given message. */
                    param->results.wolfSSLresult = RSASP1_ND(
                            td->io.rsav.in.em->data, td->io.rsav.in.em->length,
                            rsaSignature, ALENGTH(rsaSignature),
                            &rsaKey, &param->results.errorMessage);
                }
                else
                {
                    /* Hash the message first..... */
                    param->results.errorMessage = (test->hash)(
                            td->io.rsav.in.em, 
                            &hashed[ans1_exptmod_header_size]);
                    if (param->results.errorMessage) break;

                    /* ....then encrypt header and all. */
                    param->results.wolfSSLresult = RSASP1_ND(
                            hashed, ans1_exptmod_header_size + test->hashSize,
                            rsaSignature, ALENGTH(rsaSignature),
                            &rsaKey, &param->results.errorMessage); 
                }

                /* For either path, mask any non-error results. */
                if (param->results.wolfSSLresult > 0)
                {
                    rsaSize = param->results.wolfSSLresult;
                    param->results.wolfSSLresult = 0;
                }

                if (param->results.errorMessage) break;
            } // END TIMED LOOP
            param->results.encryption.stop = SYS_TIME_CounterGet();
            param->results.encryption.startStopIsValid =
                    (0 == param->results.errorMessage);
        }

        /* Success is when the recovered result matches the given result */
        const cryptoST_testData_t * const compare = &td->rawData->vector;
        if (0 == param->results.errorMessage)
        {
            if (compare->length != rsaSize)
            { param->results.errorMessage = "computed size is incorrect"; }
            else if (0 != memcmp(compare->data, rsaSignature, compare->length))
            { param->results.errorMessage = "computed signature mismatch"; }
        }

        /* Decrypt the encrypted message to verify over-and-back. */
        if (param->parameters.verifyByDecryption && td->io.rsav.in.e)
        {
            assert_dbug(td->io.rsav.in.e->data && td->io.rsav.in.e->length);

            /* Add the rest of the public key to the mix. */
            if ((0 != mp_read_unsigned_bin(&rsaKey.e,
                    td->io.rsav.in.e->data, td->io.rsav.in.e->length)))
            { param->results.errorMessage = "could not add e to key"; }
            else 
            {
                uint8_t decoded[RSA_EXPTMOD_PADDED_SIZE];
                memset(decoded,0,ALENGTH(decoded));

                /* Use n,e to regenerate the original message. */
                param->results.wolfSSLresult = wc_RsaSSL_Verify( 
                        rsaSignature, rsaSize,
                        decoded, ALENGTH(decoded),
                        &rsaKey);
                
                /* The decoded buffer has the FF padding stripped off,
                * so we need to make a small accommodation for comparison. */
                if (param->results.wolfSSLresult < 0)
                { param->results.errorMessage = "signature recovery failed"; }
                else if (0 != memcmp(&hashed[ans1_exptmod_header_size - test->asn1_size], 
                                        decoded, param->results.wolfSSLresult))
                { param->results.errorMessage = "recovered hash mismatch"; }
                else param->results.wolfSSLresult = 0;
                
                if (0 != param->results.errorMessage)
                    cryptoST_PRINT_hexBlock(CRLF ".recovered:", decoded, ALENGTH(decoded));
            }
        }
        
        if (0 != param->results.errorMessage)
        {
            const cryptoST_testData_t * const signature = td->io.rsas.out.signature;
            printf(CRLF "%s", param->results.errorMessage);
            printAll_verify(td);
            cryptoST_PRINT_hexBlock(CRLF "....vector:", 
                    vector->vector.data, vector->vector.length);
            cryptoST_PRINT_hexBlock(CRLF "......hash:", 
                    hashed, ans1_exptmod_header_size + test->hashSize);
            cryptoST_PRINT_hexBlock(CRLF "..computed:", rsaSignature, rsaSize);
            cryptoST_PRINT_hexBlock(CRLF "..expected:", signature->data, signature->length);
            printf(CRLF);
        }
        wc_FreeRsaKey(&rsaKey);
    }
    return param->results.errorMessage;
} // cryptoSTE_rsa_exptmod_timed

// *****************************************************************************
// Driver using DER format keys and WolfCrypt signing function
// *****************************************************************************
__attribute__((used))
static const char * cryptoSTE_rsa_sign_der_timed
                ( const cryptoST_testDetail_t * const td,
                    cryptoSTE_testExecution_t * const param,
                              const rsaTest_t * const test )
{
    // Do this prior to possible errors so that it reports in all cases.
    const cryptoST_testVector_t * const message = td->rawData;
    param->results.encryption.size = message->vector.length;
    param->results.encryption.iterations = param->parameters.iterationOverride? 
                                    param->parameters.iterationOverride
                                  : td->recommendedRepetitions;

    /* Statically defined to avoid overloading the stack. */
    static uint8_t rsaSignature[RSA_SIGNATURE_SIZE/8];
    memset(rsaSignature, 0, ALENGTH(rsaSignature));
    size_t signatureLength = 0;

    /* Initialize the buffers including the ANS1 header. 
     * See the comment below about ASN1 header magic. */
    assert_dbug(SHA_BUFFER_SIZE >= test->hashSize);
    assert_dbug(SHA_HEADER_SIZE >= test->asn1_size);
    uint8_t hashed[SHA_HEADER_SIZE + SHA_BUFFER_SIZE];
    memset(hashed, 0, ALENGTH(hashed));
    memcpy(hashed, test->asn1_header, test->asn1_size);

    param->results.encryption.start = SYS_TIME_CounterGet();
    for (int i = param->results.encryption.iterations; i > 0; i--)
    {
        /* Calculate hash digest of the plaintext message */
        assert_dbug(test->hash);
        param->results.errorMessage = 
            (test->hash)(&message->vector, &hashed[test->asn1_size]);
        if (0 == param->results.errorMessage)
        {
            /* Recover the keys from DER format. */
            if (0 != (param->results.wolfSSLresult = wc_InitRsaKey(&rsaKey, NULL)))
            { param->results.errorMessage = "key initialization failed"; }
            else
            {
                word32 index = 0;
                if (0 != (param->results.wolfSSLresult = wc_RsaPrivateKeyDecode
                            (td->io.rsas.in.der->data, 
                             &index, &rsaKey,
                             td->io.rsas.in.der->length)))
                { param->results.errorMessage = "failed to decode key (DER format?)"; }
                else
                {
                    assert(td->io.rsas.in.der->length == index);

                    /* This call will fail if the buffer is too small. */
                    signatureLength = wc_RsaSSL_Sign
                            (hashed, // include ASN.1 header
                             test->asn1_size + test->hashSize,
                             rsaSignature, ALENGTH(rsaSignature),
                             &rsaKey, 0); // no RNG
                    if (signatureLength <= 0)
                    { 
                        param->results.errorMessage = "RsaSSL_Sign() failed";
                        param->results.wolfSSLresult = signatureLength; 
                    }
                }
                wc_FreeRsaKey(&rsaKey);
            }
        }

        if (param->results.errorMessage) break; // out of the test routine
    } // END TIMED LOOP
    param->results.encryption.stop = SYS_TIME_CounterGet();
    param->results.encryption.startStopIsValid =
            (0 == param->results.errorMessage);
    
    /* Success is when the recovered result matches the hash result
     * in both length and content.   */
    if (0 == param->results.errorMessage)
    {
        const cryptoST_testData_t * const compare = td->io.rsas.out.signature;
        if (signatureLength != compare->length)
        { param->results.errorMessage = "incorrect computed length"; }
        if (0 != memcmp(compare->data, rsaSignature, signatureLength))
        { param->results.errorMessage = "computed signature mismatch"; }
    }
    // param->results.errorMessage = "no error";
    
    if (0 != param->results.errorMessage)
    {
        const cryptoST_testData_t * const compare = td->io.rsas.out.signature;
        printf(CRLF "%s", param->results.errorMessage);
        printAll_sign(td);
        cryptoST_PRINT_hexBlock(CRLF "..computed:", rsaSignature, signatureLength);
        cryptoST_PRINT_hexBlock(CRLF "..expected:", compare->data, compare->length);
        printf(CRLF);
    }
    return param->results.errorMessage;
}

// *****************************************************************************
// Driver using explicit N,E public key and WolfCrypt verification function
// *****************************************************************************
__attribute__((used))
static const char * cryptoSTE_rsa_verify_ne_timed
                ( const cryptoST_testDetail_t * const td,
                    cryptoSTE_testExecution_t * const param,
                              const rsaTest_t * const test )
{
    // Do this prior to possible errors so that it reports in all cases.
    const cryptoST_testVector_t * const vector = td->rawData;
    param->results.encryption.size = vector->vector.length;
    param->results.encryption.iterations = param->parameters.iterationOverride? 
                                    param->parameters.iterationOverride
                                  : td->recommendedRepetitions;

    /* Initialize the buffers including the ANS1 header. 
     * See the comment below about ASN1 header magic. */
    assert_dbug(SHA_BUFFER_SIZE >= test->hashSize);
    assert_dbug(SHA_HEADER_SIZE >= test->asn1_size);
    static uint8_t hashSignature[SHA_HEADER_SIZE + SHA_BUFFER_SIZE];
    static uint8_t rsaSignature[ALENGTH(hashSignature)];
    memset(rsaSignature, 0, ALENGTH(rsaSignature));
    memset(hashSignature, 0, ALENGTH(hashSignature));
    memcpy(hashSignature, test->asn1_header, test->asn1_size);
    int computedSigLength = 0;

    param->results.encryption.start = SYS_TIME_CounterGet();
    for (int i = param->results.encryption.iterations; i > 0; i--)
    {
        /* Calculate hash digest of the plaintext message */
        assert_dbug(test->hash);
        param->results.errorMessage = 
            (test->hash)(&vector->vector, &hashSignature[test->asn1_size]);
        if (0 == param->results.errorMessage)
        {
            /* Recover the hash digest sent with the keys. */
            if (0 != wc_InitRsaKey(&rsaKey, NULL))
            { param->results.errorMessage = "key initialization failed"; }
            else
            {
#if defined(WOLF_CRYPTO_CB)
                /* Magic when using a callback flavor of RSA (e.g., PUKCC).
                 * There is no WC InitRsaKey() that will load devId, and WC
                 * silently falls back to the SW version. Set devId
                 * explicitly to invoke the HW method. */
                rsaKey.devId = 0;
                /* The formal value is not recorded by CRYPT_WCCB_Initialize() 
                 * so we are forced to repeat that faux pas. */
#endif
                if ((0 != mp_read_unsigned_bin(&rsaKey.n,
                    td->io.rsav.in.n->data, td->io.rsav.in.n->length))
                 || (0 != mp_read_unsigned_bin(&rsaKey.e,
                    td->io.rsav.in.e->data, td->io.rsav.in.e->length)))
                { param->results.errorMessage = "key construction failed"; }
                else 
                {
                    /* Use n,e to obtain the (hopefully) same hash from em. */
                    computedSigLength = wc_RsaSSL_Verify( 
                            td->io.rsav.in.em->data, td->io.rsav.in.em->length,
                            rsaSignature, ALENGTH(rsaSignature),
                            &rsaKey);
                    if (computedSigLength < 0)
                    {
                        param->results.errorMessage = "signature recovery failed";
                        computedSigLength = ALENGTH(rsaSignature); // self protection
                    }
                }
                wc_FreeRsaKey(&rsaKey);
            }
        }

        if (param->results.errorMessage) break; // out of the test routine
    } // END TIMED LOOP
    param->results.encryption.stop = SYS_TIME_CounterGet();
    param->results.encryption.startStopIsValid =
            (0 == param->results.errorMessage);
    
    /* Success is when the recovered result matches the hash result
     * in both length and content.   */
    if (0 == param->results.errorMessage)
    {
        if (computedSigLength != test->asn1_size + test->hashSize)
        { param->results.errorMessage = "incorrect computed length"; }
        else if (0 != memcmp(hashSignature, rsaSignature, computedSigLength))
        { param->results.errorMessage = "computed signature mismatch"; }
    }
    // else param->results.errorMessage = "no error";
    
    if (0 != param->results.errorMessage)
    {
        printf(CRLF "%s", param->results.errorMessage);
        printf(CRLF "sizeof decSigLen:%d         hash:%lu", 
                                   computedSigLength, 
                (unsigned long int)(test->asn1_size + test->hashSize));
        printAll_verify(td);
        cryptoST_PRINT_hexBlock(CRLF "..computed:", rsaSignature, computedSigLength);
        cryptoST_PRINT_hexBlock(CRLF "......hash:", hashSignature, ALENGTH(hashSignature));
        printf(CRLF);
    }
    return param->results.errorMessage;
}
#endif // RSA and SHA

// *****************************************************************************
// *****************************************************************************
// Section: Load vectors
// *****************************************************************************
// *****************************************************************************
/* ASN1 header magic: the WC sign and verify assume a full ASN.1 encoding
 * of the recovered hash. So we fake the header and put our hash in line
 * with it, but rig it so that the header comes from non-volatile memory
 * (as defined below). Some values (field lengths) vary with hash size.
 * Headers are detailed in pkcs-1v2.12.pdf, in the notes for EMSA-PKCS1-V1_5. */

#define WOLF_NAME    "WOLF RSA"
#define MCHP_NAME    "MCHP RSA"

#if defined(NO_SHA224)
#define test_verify_sha224 (*((rsaTest_t*)0))
#define test_sign_sha224 (*((rsaTest_t*)0))
#else
/* this header is not in pkcs-1v2. */
static const uint8_t asn1_header_224[] = {
        0x30, 0x2D, 0x30, 0x0D, 0x06, 0x09, 0x60, 0x86,
        0x48, 0x01, 0x65, 0x03, 0x04, 0x02, 0x04, 0x05,
        0x00, 0x04, 0x1C }; // 19 bytes
static const rsaTest_t test_verify_sha224 = {
    .name = WOLF_NAME " VERIFY224",
    .hashSize = 224/8,
    .hash = rsa_sha224,
    .timer = cryptoSTE_rsa_verify_ne_timed,
    .asn1_header = asn1_header_224,
    .asn1_size = ALENGTH(asn1_header_224),
};
static const rsaTest_t test_sign_sha224 = {
    .name = WOLF_NAME " SIGN224",
    .hashSize = 224/8,
    .hash = rsa_sha224,
    .timer = cryptoSTE_rsa_sign_der_timed,
    .asn1_header = asn1_header_224,
    .asn1_size = ALENGTH(asn1_header_224),
};
static const rsaTest_t test_exptmod_sha224 = {
    .name = MCHP_NAME " EXPTMOD224",
    .timer = cryptoSTE_rsa_exptmod_timed,
    .hashSize = 224/8,
    .hash = rsa_sha224,
    .asn1_header = asn1_header_224,
    .asn1_size = ALENGTH(asn1_header_224),
};
#endif // no SHA224

#if defined(NO_SHA256)
#define test_verify_sha256 (*((void*)0))
#define test_sign_sha256 (*((void*)0))
#else
static const uint8_t asn1_header_256[] = {
        0x30, 0x31, 0x30, 0x0D, 0x06, 0x09, 0x60, 0x86,
        0x48, 0x01, 0x65, 0x03, 0x04, 0x02, 0x01, 0x05,
        0x00, 0x04, 0x20 }; // 19 bytes
static const rsaTest_t test_verify_sha256 = {
    .name = WOLF_NAME " VERIFY256",
    .hashSize = 256/8,
    .hash = rsa_sha256,
    .timer = cryptoSTE_rsa_verify_ne_timed,
    .asn1_header = asn1_header_256,
    .asn1_size = ALENGTH(asn1_header_256),
};
static const rsaTest_t test_sign_sha256 = {
    .name = WOLF_NAME " SIGN256",
    .hashSize = 256/8,
    .hash = rsa_sha256,
    .timer = cryptoSTE_rsa_sign_der_timed,
    .asn1_header = asn1_header_256,
    .asn1_size = ALENGTH(asn1_header_256),
};
static const rsaTest_t test_exptmod_sha256 = {
    .name = MCHP_NAME " EXPTMOD256",
    .timer = cryptoSTE_rsa_exptmod_timed,
    .hashSize = 256/8,
    .hash = rsa_sha256,
    .asn1_header = asn1_header_256,
    .asn1_size = ALENGTH(asn1_header_256),
};
#endif // no SHA256

/* This flavor encrypts the given data rather than the hash of the data.
 */
static const rsaTest_t test_exptmod_none = {
    .name = MCHP_NAME " EXPTMOD",
    .timer = cryptoSTE_rsa_exptmod_timed,
    .hashSize = 0,
};

// *****************************************************************************
// *****************************************************************************
// Section: External API
// *****************************************************************************
// *****************************************************************************
const char * cryptoSTE_rsa_timed(const cryptoST_testDetail_t * td,
                                   cryptoSTE_testExecution_t * param)
{
    const rsaTest_t * test = 0;
    
#if !defined(NO_RSA)
    /* The test structures are #def'd to null pointers if not enabled,
     * so we don't have to use if-def here. */
    switch(td->technique)
    {
    case ET_PK_RSA_SIGN:
        switch(td->io.rsas.in.hashmode)
        {
        case ET_SHA_224:
            test = &test_sign_sha224;
            break;
        case ET_SHA_256:
            test = &test_sign_sha256;
            break;
        default:
            break;
        };
        assert_dbug((0 == test)||(test->timer && test->hash && test->name));
        break;

    case ET_PK_RSA_VERIFY:
        switch(td->io.rsav.in.hashmode)
        {
        case ET_SHA_224:
            test = &test_verify_sha224;
            break;
        case ET_SHA_256:
            test = &test_verify_sha256;
            break;
        default:
            break;
        };
        assert_dbug((0 == test)||(test->timer && test->hash && test->name));
        break;

    case ET_PK_RSA_EXPTMOD:
        switch(td->io.rsav.in.hashmode)
        {
        case ET_NONE:
            test = &test_exptmod_none;
            break;
        case ET_SHA_224:
            test = &test_exptmod_sha224;
            break;
        case ET_SHA_256:
            test = &test_exptmod_sha256;
            break;
        default:
            break;
        };
        assert_dbug((0 == test)||(test->timer && test->name));
        break;

    default:
        break;
    };
#endif
    
    if (test)
    {
        param->results.testHandler = test->name;
        return (test->timer)(td, param, test);
    }
    else
    {
        param->results.testHandler = "RSA";
        return param->results.errorMessage = 
                "RSA not available for this mode";
    }
}
#endif // NO DES
