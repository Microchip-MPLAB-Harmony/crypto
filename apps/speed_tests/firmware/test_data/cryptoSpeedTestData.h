/* cryptoSpeedTestData
  Crypto Speed Test Data File

  Company:
    Microchip Technology Inc.

  File Name:
    cryptoSpeedTestData.h

  Description:
 * cryptoSpeedTestData.h frames the test cases that are used for 
 * speed testing the crypto libraries. Each test case should build
 * a cryptoST_testAPI_t structure to enumerate local cryptoST_testVector_t.
 * The cryptoST_testDetail_t is an optional component that is used to
 * validate the operation of the tested logic.
 * 
 * Capabilities include repetitive (averaged) execution of specific test data,
 * as suggested by recommendedRepetitions, with optional results checking.
 * 
 * This file provides standard definitions for all test suites;
 * application programs (test drivers) should include cryptoSpeedTest.h.
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

#ifndef CRYPTO_SPEED_TEST_DATA_H
#define CRYPTO_SPEED_TEST_DATA_H 1

#include <stdint.h>
#include <stddef.h> // for size_t
#include <stdbool.h>
#include "configuration.h"
#include <wolfssl/wolfcrypt/settings.h>

/* Standard definitions
   FIXME: get these from the Harmony framework
   */
typedef char CPU_CHAR;

#define AES128_KEY_SIZE 128
#define AES192_KEY_SIZE 192
#define AES256_KEY_SIZE 256

/* Simple utility of general application.
 *  */
#define ALENGTH(array) (sizeof(array)/sizeof(array[0]))    
    
/* Encryption techniques and modes
   FIXME: get these from the Harmony framework
   */
typedef enum EncryptTechnique_e
{
    ET_NONE = 0,
    ET_AES_128,
    ET_AES_192,
    ET_AES_256,
    ET_AES_GCM,     /* hash -- use EM_NONE */
    ET_AES_CCM,     /* hash -- use EM_NONE */
    ET_AES_GMAC,    /* hash -- use EM_NONE */
    ET_DES,         /* block=64, deprecated   */
    ET_DES3,        /* block=64, key=3*8 bytes */
    ET_MD2,
    ET_MD3,
    ET_MD4,
    ET_MD5,
    ET_MD6,
    ET_SHA_128,     /* a.k.a. SHA or SHA1 */
    ET_SHA_224,
    ET_SHA_256,
    ET_SHA_384,
    ET_SHA_512,

    ET_PK_RSA_SIGN,
    ET_PK_RSA_VERIFY,
    ET_PK_RSA_EXPTMOD,
    ET_PK_DH,
    ET_PK_ECDH,
    ET_PK_ECDSA_SIGN,
    ET_PK_ECDSA_VERIFY,
    ET_PK_ED25519,
    ET_PK_CURVE25519,
    ET_PK_RSA_KEYGEN,
    ET_PK_EC_KEYGEN,

    ET_ECC_CDH, // Cofactor Diffie-Hellman primitive

    /* These options allow the TA100 commands to be speed-tested.
     * All are listed here, but not all have test drivers. */
    TA100_AES,
    TA100_Authorize,
    TA100_Counter,
    TA100_Create,
    TA100_Delete,
    TA100_Dev_Update,
    TA100_ECDH,
    TA100_Export,
    TA100_FC_Config,
    TA100_Import,
    TA100_Info,
    TA100_KDF,
    TA100_Key_Gen,
    TA100_Lock,
    TA100_MAC,
    TA100_Manage_Cert,
    TA100_Power,
    TA100_Random,
    TA100_Read,
    TA100_RSA_Enc,
    TA100_Secure_Boot,
    TA100_Self_Test,
    TA100_Sequence,
    TA100_SHA,
    TA100_Sign,
    TA100_Verify,
    TA100_Write,
    TA100_Sequences,
            
    ET_UNKNOWN, // error case to cover RSA translation
} EncryptTechnique_t;

typedef enum EncryptMode_e
{
    EM_NONE = 0,
    EM_ECB,  // AES, DES
    EM_CBC,  // AES, DES
    EM_CFB,  // AES, deprecated for DES
    EM_OFB,  // AES, deprecated for DES
    EM_CTR,  // AES

    EM_ECC_P192,
    EM_ECC_P224,
    EM_ECC_P256,
    EM_ECC_P384,
    EM_ECC_P521,
    EM_ECC_K163,
    EM_ECC_K233,
    EM_ECC_K283,
    EM_ECC_K409,
    EM_ECC_K571,
    EM_ECC_B163,
    EM_ECC_B233,
    EM_ECC_B283,
    EM_ECC_B409,
    EM_ECC_B571,
} EncryptMode_t;

/*************************************************************
 * Look-ahead declarations for circular references,tions for circular references, etc.
 *************************************************************/
typedef struct cryptoST_testAPI_s cryptoST_testAPI_t;
typedef struct cryptoST_testDetail_s cryptoST_testDetail_t; 
typedef struct cryptoST_testVector_s cryptoST_testVector_t;

typedef const char * cryptoST_OpenData_t(void);  // Allocate memory, precompute golden results
typedef const cryptoST_testDetail_t * cryptoST_FirstDetail_t(void);
typedef const cryptoST_testDetail_t * cryptoST_NextDetail_t(const cryptoST_testDetail_t *);
typedef const char * cryptoST_CloseData_t(void); // release any allocated memory

/*************************************************************
 * Declaration of the test manager API
 * Obligatory entry points for executing a test
 * 
 * Each test vector module should assemble one of these and provide
 * handlers. As required, .openData does mallloc() so that we can 
 * share some memory resources at run-time, and then builds whatever
 * verification dataset that may be required. Later, .closeData does free().
 * 
 * FIXME: The bigger problem is how to assemble a list of these that can be
 * scanned at run time. Can we do a linker region?
 *************************************************************/
typedef struct cryptoST_testAPI_s
{
    const CPU_CHAR * name;
    cryptoST_OpenData_t * openData;     // execute prior to executing any tests
    cryptoST_FirstDetail_t * firstTest; // execute the test, possible multiple times
    cryptoST_NextDetail_t * nextTest;   // execute the test, possible multiple times
    cryptoST_CloseData_t * closeData;   // execute after executing the test
} cryptoST_testAPI_t;

/*************************************************************
 * Provision for standard data sets (a la ArrayList<>)
 *************************************************************/
/* Data-store definitions and requirements:
   1. cryptoST_testVector_t (test vector) data is the reason for this data base.
   2. cryptoST_testData_t (output) data is optional:
   2a. Each datum is for a specific technique/mode setting
   2b. The key/IV pair for the given output is defined if required.
   2c. .rawData is a circular reference to the raw data, if available
   2d. If .ivNonce is required but null, use a random IV
   2e. An input nonce uses .ivNonce
   3. ASCII strings provide info for auto-gen of summary labels.
   3a. .name identifies this raw data set (should be unique)
   3b. .source is a self-reference to the enclosing file
   3c. .description provides traceability (e.g., WolfSSL)
   3d. .pedigree describes where the gold-data came from
   4. TDES uses a 3-key array of key data

   Generation of the output list in C is something of a burden.
   */

typedef struct cryptoST_testData_s
{
    size_t length;        // size of the data block
    const uint8_t * data; // location of the data
} cryptoST_testData_t;

/* Similar, but for output buffers that are not const. */
typedef struct cryptoST_softData_s
{
    size_t length;  // size of the data block
    uint8_t * data; // location of the data
} cryptoST_softData_t;

/*************************************************************
 * Declaration of input parameters
 * 
 * Any given test set requires specific (known good) input
 * data values. The actual form these values take must be 
 * discriminated by the type of encryption algorithm,
 * so these will be union'd in the final data set.
 * */
typedef struct cryptoST_hash_input_s
{
    cryptoST_testData_t key;
    cryptoST_testData_t ivNonce;
} cryptoST_hash_input_t;

typedef struct cryptoST_symmetric_input_s
{
    cryptoST_testData_t key;
    cryptoST_testData_t ivNonce;
    cryptoST_testData_t additionalAuthData;
} cryptoST_symmetric_input_t;

/*************************************************************
 * Declaration of output parameters
 * 
 * Any given test set produces output(s) specific for that
 * method. The actual form these values take must be 
 * discriminated by the type of encryption algorithm,
 * so these will be union'd in the final data set.
 * */
typedef struct cryptoST_hash_output_s
{
    cryptoST_testData_t hash;
} cryptoST_hash_output_t;

typedef struct cryptoST_symmetric_output_s
{
    cryptoST_testData_t cipher;
    cryptoST_testData_t tag;
} cryptoST_symmetric_output_t;

#if !defined(NO_RSA)
typedef struct cryptoST_asymmetric_rsas_input_s
{
    /* ASN.1 formatted private key file */
    const cryptoST_testData_t * der;
    EncryptTechnique_t hashmode;
} cryptoST_asymmetric_rsas_input_t; // RSA signing

typedef struct cryptoST_asymmetric_rsas_output_s
{
    cryptoST_testData_t * signature;
    cryptoST_testData_t * salt; // why this?
} cryptoST_asymmetric_rsas_output_t;

typedef struct cryptoST_asymmetric_rsav_input_s
{
    /* By concatenation: PU = {e,n}, PR = {d,n} */
    const cryptoST_testData_t * n;  // =pq; product of primes
    const cryptoST_testData_t * e;  // selected
    const cryptoST_testData_t * d;  // =e^(-1) mod ..etc.
    const cryptoST_testData_t * em;  // encrypted message
    EncryptTechnique_t hashmode;
} cryptoST_asymmetric_rsav_input_t; // RSA verification

typedef struct cryptoST_asymmetric_rsav_output_s
{
    // output is the raw data
} cryptoST_asymmetric_rsav_output_t;
#endif // NO_RSA

#if !defined(NO_ECC)
typedef struct cryptoST_ecc_key_s
{
    const uint8_t * x; // length is convey separately
    const uint8_t * y;
} cryptoST_ecc_key_t;

typedef struct cryptoST_asym_ecc_input_s
{
    const cryptoST_ecc_key_t remotePU;
    const uint8_t            * d; // random number
} cryptoST_asymmetric_ecc_input_t;

typedef struct cryptoST_asym_ecc_output_s
{
    const cryptoST_ecc_key_t localPR;
    const uint8_t            * z; // random number
} cryptoST_asymmetric_ecc_output_t;
#endif

/*************************************************************
 * Declaration of golden results
 * 
 * Given input data .rawData, the results of a specific
 * encryption are provided by this structure. As a matter of
 * good practice, .goldenResult may be null when compiled, then
 * established by cryptoST_testAPI_t.openData, and ultimately
 * destroyed by cryptoST_testAPI_t.closeData. Likewise for
 * .key, .ivNonce (or nonce) and .authenticateTag as necessary.
 *************************************************************/
typedef struct cryptoST_testDetail_s
{
    EncryptTechnique_t technique;   // filter parameters for this result
    EncryptMode_t mode;
    int recommendedRepetitions;     // to get reasonable statistics
    bool doNotUseHWAcceleration;    // to compare HW vs. SW

    const CPU_CHAR * source;         // name of enclosing file
    const CPU_CHAR * pedigree;       // history of gold-standard data
    const cryptoST_testVector_t * rawData; // reference to original data
    // depending on how the data file is built, .rawData maybe must be null

    // Inputs
    union
    {
        /* The SYM and HASH entries are always enabled
         * because there is no "single" WC #define that
         * operates for all of them. The others are
         * bigger and less frequently used.
         * */
        struct // AES is in because its too hard to inhibit
        {
            cryptoST_symmetric_input_t in;
            cryptoST_symmetric_output_t out;
        } sym;
        struct
        {
            cryptoST_hash_input_t in;
            cryptoST_hash_output_t out;
        } hash;
#if !defined(NO_RSA)
        struct rsas_s
        {
            cryptoST_asymmetric_rsas_input_t in; // sign
            cryptoST_asymmetric_rsas_output_t out;
        } rsas;
        struct rsav_s
        {
            cryptoST_asymmetric_rsav_input_t in; // verify
            cryptoST_asymmetric_rsav_output_t out;
        } rsav;
#endif // NO_RSA
#if !defined(NO_ECC)
        struct
        {
            cryptoST_asymmetric_ecc_input_t in;
            cryptoST_asymmetric_ecc_output_t out;
        } ecc;
    } io; // unnamed unions are not allowed by MISRA
#endif // NO_ECC
    /* The definition of an error depends on the specific test
     * invoked by technique/mode (e.g., GMAC validation failure).
     *  */
    bool expectError;
} cryptoST_testDetail_t;

/*************************************************************
 * Declaration of raw test vector(s)
 * 
 * The data module must make at least one of these, but could
 * make many to support multiple test cases.
 *************************************************************/
typedef struct cryptoST_testVector_s
{
    const CPU_CHAR * name;      // short name of this vector
    const CPU_CHAR * source;    // name of enclosing file
    const CPU_CHAR * pedigree;  // source of this vector
    const CPU_CHAR * description; // long description of this vector

    cryptoST_testData_t vector;     // raw input data
} cryptoST_testVector_t;

#endif // CRYPTO_SPEED_TEST_DATA_H
