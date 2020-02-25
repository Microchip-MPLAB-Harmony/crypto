/* cryptoSpeedTestData
 * 
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
 * application programs should include cryptoSpeedTest.h.
*/

#ifndef CRYPTO_SPEED_TEST_DATA_H
#define CRYPTO_SPEED_TEST_DATA_H 1

#include <stdint.h>
#include <stddef.h> // for size_t
#include <stdbool.h>

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
    ET_DES3,        /* block=64, key=24 bytes */
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
} EncryptTechnique_t;

typedef enum EncryptMode_e
{
    EM_NONE = 0,
    EM_ECB,  // AES, DES
    EM_CBC,  // AES, DES
    EM_CFB,  // AES, DES
    EM_OFB,  // AES, DES
    EM_CTR,  // AES
} EncryptMode_t;

/*************************************************************
 * Look-ahead declarations for circular references, etc.
 *************************************************************/
typedef struct cryptoST_testAPI_s cryptoST_testAPI_t;
typedef struct cryptoST_testDetail_s cryptoST_testDetail_t; 
typedef struct cryptoST_testVector_s cryptoST_testVector_t;

typedef char * cryptoST_OpenData_t(void);  // Allocate memory, precompute golden results
typedef cryptoST_testDetail_t * cryptoST_FirstDetail_t(void);
typedef cryptoST_testDetail_t * cryptoST_NextDetail_t(cryptoST_testDetail_t *);
typedef char * cryptoST_CloseData_t(void); // release any allocated memory

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
    size_t length;  // size of the data block
    const uint8_t * data; // location of the data
} cryptoST_testData_t;

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
    cryptoST_testVector_t * rawData; // reference to original data
    // depending on how the data file is built, .rawData maybe must be null

    // Inputs
    const cryptoST_testData_t * key;
    cryptoST_testData_t ivNonce;
    cryptoST_testData_t additionalAuthData; // for GCM/CTR/CCM mode

    // Output compare data supplied for (optional) verification
    cryptoST_testData_t goldenCipher;
    cryptoST_testData_t goldenTag;

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
