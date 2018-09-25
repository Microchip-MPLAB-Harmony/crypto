/*******************************************************************************
  MPLAB Harmony Application Source File

  Company:
    Microchip Technology Inc.

  File Name:
    app.c

  Summary:
    This file contains the source code for the MPLAB Harmony application.

  Description:
    This file contains the source code for the MPLAB Harmony application.  It
    implements the logic of the application's state machine and it may call
    API routines of other MPLAB Harmony modules in the system, such as drivers,
    system services, and middleware.  However, it does not call any of the
    system interfaces (such as the "Initialize" and "Tasks" functions) of any of
    the modules in the system or make any assumptions about when those functions
    are called.  That is the responsibility of the configuration-specific system
    files.
 *******************************************************************************/

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include "app.h"
#include <stdio.h>
#include "crypto/src/md5.h"
#include "crypto/src/sha.h"
#include "crypto/src/sha256.h"
#include "crypto/src/sha512.h"
#include "crypto/src/random.h"
#include "crypto/src/rsa.h"
#include "crypto/src/certs_test.h"
#include "crypto/src/des3.h"
#include "crypto/src/aes.h"
#include "crypto/src/hmac.h"
#ifdef HAVE_ECC
#include "crypto/src/ecc.h"
#endif
#ifdef HAVE_LIBZ
#include "crypto/src/compress.h"
#endif

// *****************************************************************************
// *****************************************************************************
// Section: Global Data Definitions
// *****************************************************************************
// *****************************************************************************

typedef struct testVector {
    const char*  input;
    const char*  output;
    size_t inLen;
    size_t outLen;
} testVector;

// *****************************************************************************
/* Application Data

  Summary:
    Holds application data

  Description:
    This structure holds the application's data.

  Remarks:
    This structure should be initialized by the APP_Initialize function.

    Application strings and buffers are be defined outside this structure.
 */

APP_DATA appData;

// *****************************************************************************
// *****************************************************************************
// Section: Application Callback Functions
// *****************************************************************************
// *****************************************************************************


// *****************************************************************************
// *****************************************************************************
// Section: Application Local Functions
// *****************************************************************************
// *****************************************************************************
void  md5_test(void);
void  sha_test(void);
void  sha256_test(void);
void  sha384_test(void);
void  sha512_test(void);
void  hmac_md5_test(void);
void  hmac_sha_test(void);
void  hmac_sha256_test(void);
void  hmac_sha384_test(void);
void  hmac_sha512_test(void);
void  des_test(void);
void  des3_test(void);
void  aes_test(void);
void  aesgcm_test(void);
void  gmac_test(void);
void  aesccm_test(void);
void  rsa_test(void);
void  random_test(void);
#ifdef HAVE_ECC
    void  ecc_test(void);
    #ifdef HAVE_ECC_ENCRYPT
        //void  ecc_encrypt_test(void);
    #endif
#endif
#ifdef HAVE_BLAKE2
    //void  blake2b_test(void);
#endif
#ifdef HAVE_LIBZ
    //void compress_test(void);
#endif
    
/*****************************************************
 * Initialize the application data structure. All
 * application related variables are stored in this
 * data structure.
 *****************************************************/

APP_DATA appData ={
    .state = APP_STATE_INIT,
    .wrComplete = true,
    .rdComplete = true
};

static const int MD5_Expected = 0;
static const int SHA_Expected = 0;
static const int SHA256_Expected = 0;
static const int SHA384_Expected = 0;
static const int SHA512_Expected = 0;
static const int HMAC_MD5_Expected = 0;
static const int HMAC_SHA_Expected = 0;
static const int HMAC_SHA256_Expected = 0;
static const int HMAC_SHA384_Expected = 0;
static const int HMAC_SHA512_Expected = 0;
static const int DES_Expected = 0;
static const int DES3_Expected = 0;
static const int AES_CBC_Expected = 0;
static const int AES_CTR_Expected = 0;
static const int Random_Expected = 0;

// *****************************************************************************
// *****************************************************************************
// Section: Application Local Routines
// *****************************************************************************
// *****************************************************************************
uint32_t APP_getTicks(void) {
    return SYS_TIME_CounterGet();
}

char printBuffer[50 * 1024] = {0};

void APP_DisplayHash(uint8_t *hash, uint32_t hashSz) {
    while (hashSz--) {
        sprintf(printBuffer, "%s%02X", printBuffer, *hash++);

        //sprintf(printBuffer, "%s%02X", *hash++);
    }
}


uint8_t __attribute__((aligned(64))) myBuf[1024];


#ifndef NO_MD5
void md5_test(void)
{
    CRYPT_MD5_CTX  md5;
    byte hash[MD5_DIGEST_SIZE];

    testVector a, b, c, d, e;
    testVector test_md5[5];
    int times = sizeof(test_md5) / sizeof(testVector), i;

    a.input  = "abc";
    a.output = "\x90\x01\x50\x98\x3c\xd2\x4f\xb0\xd6\x96\x3f\x7d\x28\xe1\x7f"
               "\x72";
    a.inLen  = strlen(a.input);
    a.outLen = MD5_DIGEST_SIZE;

    b.input  = "message digest";
    b.output = "\xf9\x6b\x69\x7d\x7c\xb7\x93\x8d\x52\x5a\x2f\x31\xaa\xf1\x61"
               "\xd0";
    b.inLen  = strlen(b.input);
    b.outLen = MD5_DIGEST_SIZE;

    c.input  = "abcdefghijklmnopqrstuvwxyz";
    c.output = "\xc3\xfc\xd3\xd7\x61\x92\xe4\x00\x7d\xfb\x49\x6c\xca\x67\xe1"
               "\x3b";
    c.inLen  = strlen(c.input);
    c.outLen = MD5_DIGEST_SIZE;

    d.input  = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz012345"
               "6789";
    d.output = "\xd1\x74\xab\x98\xd2\x77\xd9\xf5\xa5\x61\x1c\x2c\x9f\x41\x9d"
               "\x9f";
    d.inLen  = strlen(d.input);
    d.outLen = MD5_DIGEST_SIZE;

    e.input  = "1234567890123456789012345678901234567890123456789012345678"
               "9012345678901234567890";
    e.output = "\x57\xed\xf4\xa2\x2b\xe3\xc9\x55\xac\x49\xda\x2e\x21\x07\xb6"
               "\x7a";
    e.inLen  = strlen(e.input);
    e.outLen = MD5_DIGEST_SIZE;

    test_md5[0] = a;
    test_md5[1] = b;
    test_md5[2] = c;
    test_md5[3] = d;
    test_md5[4] = e;

    CRYPT_MD5_Initialize(&md5);

    appData.md5_test_result = 0;
        
    for (i = 0; i < times; ++i) {
        CRYPT_MD5_DataAdd(&md5, (byte*)test_md5[i].input, (word32)test_md5[i].inLen);
        CRYPT_MD5_Finalize(&md5, hash);

        if (memcmp(hash, test_md5[i].output, MD5_DIGEST_SIZE) != 0)
        {
            appData.md5_test_result++;
        }
    }
}
#endif /* NO_MD5 */

#ifndef NO_SHA
void sha_test(void)
{
    CRYPT_SHA_CTX  sha;
    byte hash[SHA_DIGEST_SIZE];

    testVector a, b, c, d;
    testVector test_sha[4];
    int times = sizeof(test_sha) / sizeof(struct testVector), i;

    a.input  = "abc";
    a.output = "\xA9\x99\x3E\x36\x47\x06\x81\x6A\xBA\x3E\x25\x71\x78\x50\xC2"
               "\x6C\x9C\xD0\xD8\x9D";
    a.inLen  = strlen(a.input);
    a.outLen = SHA_DIGEST_SIZE;

    b.input  = "abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq";
    b.output = "\x84\x98\x3E\x44\x1C\x3B\xD2\x6E\xBA\xAE\x4A\xA1\xF9\x51\x29"
               "\xE5\xE5\x46\x70\xF1";
    b.inLen  = strlen(b.input);
    b.outLen = SHA_DIGEST_SIZE;

    c.input  = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
               "aaaaaa";
    c.output = "\x00\x98\xBA\x82\x4B\x5C\x16\x42\x7B\xD7\xA1\x12\x2A\x5A\x44"
               "\x2A\x25\xEC\x64\x4D";
    c.inLen  = strlen(c.input);
    c.outLen = SHA_DIGEST_SIZE;

    d.input  = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
               "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
               "aaaaaaaaaa";
    d.output = "\xAD\x5B\x3F\xDB\xCB\x52\x67\x78\xC2\x83\x9D\x2F\x15\x1E\xA7"
               "\x53\x99\x5E\x26\xA0";
    d.inLen  = strlen(d.input);
    d.outLen = SHA_DIGEST_SIZE;

    test_sha[0] = d;
    test_sha[1] = b;
    test_sha[2] = c;
    test_sha[3] = a;

    CRYPT_SHA_Initialize(&sha);

    appData.sha_test_result = 0;
    
    for (i = 0; i < times; ++i) {
        CRYPT_SHA_DataAdd(&sha, (byte*)test_sha[i].input, (word32)test_sha[i].inLen);
        CRYPT_SHA_Finalize(&sha, hash);

        if (memcmp(hash, test_sha[i].output, SHA_DIGEST_SIZE) != 0)
            appData.sha_test_result++;
    }
}
#endif /* NO_SHA */

#ifndef NO_SHA256
void sha256_test(void)
{
    CRYPT_SHA256_CTX sha;
    byte   hash[SHA256_DIGEST_SIZE];

    testVector a, b;
    testVector test_sha[2];
    int times = sizeof(test_sha) / sizeof(struct testVector), i;

    a.input  = "abc";
    a.output = "\xBA\x78\x16\xBF\x8F\x01\xCF\xEA\x41\x41\x40\xDE\x5D\xAE\x22"
               "\x23\xB0\x03\x61\xA3\x96\x17\x7A\x9C\xB4\x10\xFF\x61\xF2\x00"
               "\x15\xAD";
    a.inLen  = strlen(a.input);
    a.outLen = SHA256_DIGEST_SIZE;

    b.input  = "abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq";
    b.output = "\x24\x8D\x6A\x61\xD2\x06\x38\xB8\xE5\xC0\x26\x93\x0C\x3E\x60"
               "\x39\xA3\x3C\xE4\x59\x64\xFF\x21\x67\xF6\xEC\xED\xD4\x19\xDB"
               "\x06\xC1";
    b.inLen  = strlen(b.input);
    b.outLen = SHA256_DIGEST_SIZE;

    test_sha[0] = a;
    test_sha[1] = b;

    CRYPT_SHA256_Initialize(&sha);

    appData.sha256_test_result = 0;
    
    for (i = 0; i < times; ++i) {
        CRYPT_SHA256_DataAdd(&sha, (byte*)test_sha[i].input,(word32)test_sha[i].inLen);
        CRYPT_SHA256_Finalize(&sha, hash);

        if (memcmp(hash, test_sha[i].output, SHA256_DIGEST_SIZE) != 0)
            appData.sha256_test_result++;
    }
}
#endif /* NO_SHA256 */

#ifdef WOLFSSL_SHA384
void sha384_test(void)
{
    CRYPT_SHA384_CTX sha;
    byte   hash[SHA384_DIGEST_SIZE];

    testVector a, b;
    testVector test_sha[2];
    int times = sizeof(test_sha) / sizeof(struct testVector), i;

    a.input  = "abc";
    a.output = "\xcb\x00\x75\x3f\x45\xa3\x5e\x8b\xb5\xa0\x3d\x69\x9a\xc6\x50"
               "\x07\x27\x2c\x32\xab\x0e\xde\xd1\x63\x1a\x8b\x60\x5a\x43\xff"
               "\x5b\xed\x80\x86\x07\x2b\xa1\xe7\xcc\x23\x58\xba\xec\xa1\x34"
               "\xc8\x25\xa7";
    a.inLen  = strlen(a.input);
    a.outLen = SHA384_DIGEST_SIZE;

    b.input  = "abcdefghbcdefghicdefghijdefghijkefghijklfghijklmghijklmnhi"
               "jklmnoijklmnopjklmnopqklmnopqrlmnopqrsmnopqrstnopqrstu";
    b.output = "\x09\x33\x0c\x33\xf7\x11\x47\xe8\x3d\x19\x2f\xc7\x82\xcd\x1b"
               "\x47\x53\x11\x1b\x17\x3b\x3b\x05\xd2\x2f\xa0\x80\x86\xe3\xb0"
               "\xf7\x12\xfc\xc7\xc7\x1a\x55\x7e\x2d\xb9\x66\xc3\xe9\xfa\x91"
               "\x74\x60\x39";
    b.inLen  = strlen(b.input);
    b.outLen = SHA384_DIGEST_SIZE;

    test_sha[0] = a;
    test_sha[1] = b;

    CRYPT_SHA384_Initialize(&sha);

    appData.sha384_test_result = 0;
    
    for (i = 0; i < times; ++i) {
        CRYPT_SHA384_DataAdd(&sha, (byte*)test_sha[i].input,(word32)test_sha[i].inLen);
        CRYPT_SHA384_Finalize(&sha, hash);

        if (memcmp(hash, test_sha[i].output, SHA384_DIGEST_SIZE) != 0)
            appData.sha384_test_result++;
    }
}
#endif /* WOLFSSL_SHA384 */

#ifdef WOLFSSL_SHA512
void sha512_test(void)
{
    CRYPT_SHA512_CTX sha;
    byte   hash[SHA512_DIGEST_SIZE];

    testVector a, b;
    testVector test_sha[2];
    int times = sizeof(test_sha) / sizeof(struct testVector), i;

    a.input  = "abc";
    a.output = "\xdd\xaf\x35\xa1\x93\x61\x7a\xba\xcc\x41\x73\x49\xae\x20\x41"
               "\x31\x12\xe6\xfa\x4e\x89\xa9\x7e\xa2\x0a\x9e\xee\xe6\x4b\x55"
               "\xd3\x9a\x21\x92\x99\x2a\x27\x4f\xc1\xa8\x36\xba\x3c\x23\xa3"
               "\xfe\xeb\xbd\x45\x4d\x44\x23\x64\x3c\xe8\x0e\x2a\x9a\xc9\x4f"
               "\xa5\x4c\xa4\x9f";
    a.inLen  = strlen(a.input);
    a.outLen = SHA512_DIGEST_SIZE;

    b.input  = "abcdefghbcdefghicdefghijdefghijkefghijklfghijklmghijklmnhi"
               "jklmnoijklmnopjklmnopqklmnopqrlmnopqrsmnopqrstnopqrstu";
    b.output = "\x8e\x95\x9b\x75\xda\xe3\x13\xda\x8c\xf4\xf7\x28\x14\xfc\x14"
               "\x3f\x8f\x77\x79\xc6\xeb\x9f\x7f\xa1\x72\x99\xae\xad\xb6\x88"
               "\x90\x18\x50\x1d\x28\x9e\x49\x00\xf7\xe4\x33\x1b\x99\xde\xc4"
               "\xb5\x43\x3a\xc7\xd3\x29\xee\xb6\xdd\x26\x54\x5e\x96\xe5\x5b"
               "\x87\x4b\xe9\x09";
    b.inLen  = strlen(b.input);
    b.outLen = SHA512_DIGEST_SIZE;

    test_sha[0] = a;
    test_sha[1] = b;

    CRYPT_SHA512_Initialize(&sha);

    appData.sha512_test_result = 0;
    
    for (i = 0; i < times; ++i) {
        CRYPT_SHA512_DataAdd(&sha, (byte*)test_sha[i].input,(word32)test_sha[i].inLen);
        CRYPT_SHA512_Finalize(&sha, hash);

        if (memcmp(hash, test_sha[i].output, SHA512_DIGEST_SIZE) != 0)
            appData.sha512_test_result++;
    }
}
#endif /* WOLFSSL_SHA512 */

#if !defined(NO_HMAC) && !defined(NO_MD5)
void hmac_md5_test(void)
{
    Hmac hmac;
    byte hash[MD5_DIGEST_SIZE];

    const char* keys[]=
    {
        "\x0b\x0b\x0b\x0b\x0b\x0b\x0b\x0b\x0b\x0b\x0b\x0b\x0b\x0b\x0b\x0b",
        "Jefe",
        "\xAA\xAA\xAA\xAA\xAA\xAA\xAA\xAA\xAA\xAA\xAA\xAA\xAA\xAA\xAA\xAA"
    };

    testVector a, b, c;
    testVector test_hmac[3];

    int times = sizeof(test_hmac) / sizeof(testVector), i;

    a.input  = "Hi There";
    a.output = "\x92\x94\x72\x7a\x36\x38\xbb\x1c\x13\xf4\x8e\xf8\x15\x8b\xfc"
               "\x9d";
    a.inLen  = strlen(a.input);
    a.outLen = MD5_DIGEST_SIZE;

    b.input  = "what do ya want for nothing?";
    b.output = "\x75\x0c\x78\x3e\x6a\xb0\xb5\x03\xea\xa8\x6e\x31\x0a\x5d\xb7"
               "\x38";
    b.inLen  = strlen(b.input);
    b.outLen = MD5_DIGEST_SIZE;

    c.input  = "\xDD\xDD\xDD\xDD\xDD\xDD\xDD\xDD\xDD\xDD\xDD\xDD\xDD\xDD"
               "\xDD\xDD\xDD\xDD\xDD\xDD\xDD\xDD\xDD\xDD\xDD\xDD\xDD\xDD\xDD"
               "\xDD\xDD\xDD\xDD\xDD\xDD\xDD\xDD\xDD\xDD\xDD\xDD\xDD\xDD\xDD"
               "\xDD\xDD\xDD\xDD\xDD\xDD";
    c.output = "\x56\xbe\x34\x52\x1d\x14\x4c\x88\xdb\xb8\xc7\x33\xf0\xe8\xb3"
               "\xf6";
    c.inLen  = strlen(c.input);
    c.outLen = MD5_DIGEST_SIZE;

    test_hmac[0] = a;
    test_hmac[1] = b;
    test_hmac[2] = c;

    appData.hmac_md5_test_result = 0;
    
    for (i = 0; i < times; ++i) {
        wc_HmacSetKey(&hmac, MD5, (byte*)keys[i], (word32)strlen(keys[i]));
        wc_HmacUpdate(&hmac, (byte*)test_hmac[i].input,
                   (word32)test_hmac[i].inLen);
        wc_HmacFinal(&hmac, hash);

        if (memcmp(hash, test_hmac[i].output, MD5_DIGEST_SIZE) != 0)
            appData.hmac_md5_test_result++;
    }
}
#endif /* NO_HMAC && NO_MD5 */

#if !defined(NO_HMAC) && !defined(NO_SHA)
void hmac_sha_test(void)
{
    Hmac hmac;
    byte hash[SHA_DIGEST_SIZE];

    const char* keys[]=
    {
        "\x0b\x0b\x0b\x0b\x0b\x0b\x0b\x0b\x0b\x0b\x0b\x0b\x0b\x0b\x0b\x0b\x0b"
                                                                "\x0b\x0b\x0b",
        "Jefe",
        "\xAA\xAA\xAA\xAA\xAA\xAA\xAA\xAA\xAA\xAA\xAA\xAA\xAA\xAA\xAA\xAA\xAA"
                                                                "\xAA\xAA\xAA"
    };

    testVector a, b, c;
    testVector test_hmac[3];

    int times = sizeof(test_hmac) / sizeof(testVector), i;

    a.input  = "Hi There";
    a.output = "\xb6\x17\x31\x86\x55\x05\x72\x64\xe2\x8b\xc0\xb6\xfb\x37\x8c"
               "\x8e\xf1\x46\xbe\x00";
    a.inLen  = strlen(a.input);
    a.outLen = SHA_DIGEST_SIZE;

    b.input  = "what do ya want for nothing?";
    b.output = "\xef\xfc\xdf\x6a\xe5\xeb\x2f\xa2\xd2\x74\x16\xd5\xf1\x84\xdf"
               "\x9c\x25\x9a\x7c\x79";
    b.inLen  = strlen(b.input);
    b.outLen = SHA_DIGEST_SIZE;

    c.input  = "\xDD\xDD\xDD\xDD\xDD\xDD\xDD\xDD\xDD\xDD\xDD\xDD\xDD\xDD"
               "\xDD\xDD\xDD\xDD\xDD\xDD\xDD\xDD\xDD\xDD\xDD\xDD\xDD\xDD\xDD"
               "\xDD\xDD\xDD\xDD\xDD\xDD\xDD\xDD\xDD\xDD\xDD\xDD\xDD\xDD\xDD"
               "\xDD\xDD\xDD\xDD\xDD\xDD";
    c.output = "\x12\x5d\x73\x42\xb9\xac\x11\xcd\x91\xa3\x9a\xf4\x8a\xa1\x7b"
               "\x4f\x63\xf1\x75\xd3";
    c.inLen  = strlen(c.input);
    c.outLen = SHA_DIGEST_SIZE;

    test_hmac[0] = a;
    test_hmac[1] = b;
    test_hmac[2] = c;

    appData.hmac_sha_test_result = 0;
    
    for (i = 0; i < times; ++i) {
        wc_HmacSetKey(&hmac, SHA, (byte*)keys[i], (word32)strlen(keys[i]));
        wc_HmacUpdate(&hmac, (byte*)test_hmac[i].input,
                   (word32)test_hmac[i].inLen);
        wc_HmacFinal(&hmac, hash);

        if (memcmp(hash, test_hmac[i].output, SHA_DIGEST_SIZE) != 0)
            appData.hmac_sha_test_result++;
    }
}
#endif /* NO_HMAC && NO_SHA */

#if !defined(NO_HMAC) && !defined(NO_SHA256)
void hmac_sha256_test(void)
{
    Hmac hmac;
    byte hash[SHA256_DIGEST_SIZE];

    const char* keys[]=
    {
        "\x0b\x0b\x0b\x0b\x0b\x0b\x0b\x0b\x0b\x0b\x0b\x0b\x0b\x0b\x0b\x0b\x0b"
                                                                "\x0b\x0b\x0b",
        "Jefe",
        "\xAA\xAA\xAA\xAA\xAA\xAA\xAA\xAA\xAA\xAA\xAA\xAA\xAA\xAA\xAA\xAA\xAA"
                                                                "\xAA\xAA\xAA"
    };

    testVector a, b, c;
    testVector test_hmac[3];

    int times = sizeof(test_hmac) / sizeof(testVector), i;

    a.input  = "Hi There";
    a.output = "\xb0\x34\x4c\x61\xd8\xdb\x38\x53\x5c\xa8\xaf\xce\xaf\x0b\xf1"
               "\x2b\x88\x1d\xc2\x00\xc9\x83\x3d\xa7\x26\xe9\x37\x6c\x2e\x32"
               "\xcf\xf7";
    a.inLen  = strlen(a.input);
    a.outLen = SHA256_DIGEST_SIZE;

    b.input  = "what do ya want for nothing?";
    b.output = "\x5b\xdc\xc1\x46\xbf\x60\x75\x4e\x6a\x04\x24\x26\x08\x95\x75"
               "\xc7\x5a\x00\x3f\x08\x9d\x27\x39\x83\x9d\xec\x58\xb9\x64\xec"
               "\x38\x43";
    b.inLen  = strlen(b.input);
    b.outLen = SHA256_DIGEST_SIZE;

    c.input  = "\xDD\xDD\xDD\xDD\xDD\xDD\xDD\xDD\xDD\xDD\xDD\xDD\xDD\xDD"
               "\xDD\xDD\xDD\xDD\xDD\xDD\xDD\xDD\xDD\xDD\xDD\xDD\xDD\xDD\xDD"
               "\xDD\xDD\xDD\xDD\xDD\xDD\xDD\xDD\xDD\xDD\xDD\xDD\xDD\xDD\xDD"
               "\xDD\xDD\xDD\xDD\xDD\xDD";
    c.output = "\x77\x3e\xa9\x1e\x36\x80\x0e\x46\x85\x4d\xb8\xeb\xd0\x91\x81"
               "\xa7\x29\x59\x09\x8b\x3e\xf8\xc1\x22\xd9\x63\x55\x14\xce\xd5"
               "\x65\xfe";
    c.inLen  = strlen(c.input);
    c.outLen = SHA256_DIGEST_SIZE;

    test_hmac[0] = a;
    test_hmac[1] = b;
    test_hmac[2] = c;

    appData.hmac_sha256_test_result = 0;
    
    for (i = 0; i < times; ++i) {
        wc_HmacSetKey(&hmac, SHA256, (byte*)keys[i], (word32)strlen(keys[i]));
        wc_HmacUpdate(&hmac, (byte*)test_hmac[i].input,
                   (word32)test_hmac[i].inLen);
        wc_HmacFinal(&hmac, hash);

        if (memcmp(hash, test_hmac[i].output, SHA256_DIGEST_SIZE) != 0)
            appData.hmac_sha256_test_result++;
    }
}
#endif /* NO_HMAC && NO_SHA256 */

#if !defined(NO_HMAC) && defined(WOLFSSL_SHA384)
void hmac_sha384_test(void)
{
    Hmac hmac;
    byte hash[SHA384_DIGEST_SIZE];

    const char* keys[]=
    {
        "\x0b\x0b\x0b\x0b\x0b\x0b\x0b\x0b\x0b\x0b\x0b\x0b\x0b\x0b\x0b\x0b\x0b"
                                                                "\x0b\x0b\x0b",
        "Jefe",
        "\xAA\xAA\xAA\xAA\xAA\xAA\xAA\xAA\xAA\xAA\xAA\xAA\xAA\xAA\xAA\xAA\xAA"
                                                                "\xAA\xAA\xAA"
    };

    testVector a, b, c;
    testVector test_hmac[3];

    int times = sizeof(test_hmac) / sizeof(testVector), i;

    a.input  = "Hi There";
    a.output = "\xaf\xd0\x39\x44\xd8\x48\x95\x62\x6b\x08\x25\xf4\xab\x46\x90"
               "\x7f\x15\xf9\xda\xdb\xe4\x10\x1e\xc6\x82\xaa\x03\x4c\x7c\xeb"
               "\xc5\x9c\xfa\xea\x9e\xa9\x07\x6e\xde\x7f\x4a\xf1\x52\xe8\xb2"
               "\xfa\x9c\xb6";
    a.inLen  = strlen(a.input);
    a.outLen = SHA384_DIGEST_SIZE;

    b.input  = "what do ya want for nothing?";
    b.output = "\xaf\x45\xd2\xe3\x76\x48\x40\x31\x61\x7f\x78\xd2\xb5\x8a\x6b"
               "\x1b\x9c\x7e\xf4\x64\xf5\xa0\x1b\x47\xe4\x2e\xc3\x73\x63\x22"
               "\x44\x5e\x8e\x22\x40\xca\x5e\x69\xe2\xc7\x8b\x32\x39\xec\xfa"
               "\xb2\x16\x49";
    b.inLen  = strlen(b.input);
    b.outLen = SHA384_DIGEST_SIZE;

    c.input  = "\xDD\xDD\xDD\xDD\xDD\xDD\xDD\xDD\xDD\xDD\xDD\xDD\xDD\xDD"
               "\xDD\xDD\xDD\xDD\xDD\xDD\xDD\xDD\xDD\xDD\xDD\xDD\xDD\xDD\xDD"
               "\xDD\xDD\xDD\xDD\xDD\xDD\xDD\xDD\xDD\xDD\xDD\xDD\xDD\xDD\xDD"
               "\xDD\xDD\xDD\xDD\xDD\xDD";
    c.output = "\x88\x06\x26\x08\xd3\xe6\xad\x8a\x0a\xa2\xac\xe0\x14\xc8\xa8"
               "\x6f\x0a\xa6\x35\xd9\x47\xac\x9f\xeb\xe8\x3e\xf4\xe5\x59\x66"
               "\x14\x4b\x2a\x5a\xb3\x9d\xc1\x38\x14\xb9\x4e\x3a\xb6\xe1\x01"
               "\xa3\x4f\x27";
    c.inLen  = strlen(c.input);
    c.outLen = SHA384_DIGEST_SIZE;

    test_hmac[0] = a;
    test_hmac[1] = b;
    test_hmac[2] = c;

    appData.hmac_sha384_test_result = 0;
    
    for (i = 0; i < times; ++i) {
        wc_HmacSetKey(&hmac, SHA384, (byte*)keys[i], (word32)strlen(keys[i]));
        wc_HmacUpdate(&hmac, (byte*)test_hmac[i].input,
                   (word32)test_hmac[i].inLen);
        wc_HmacFinal(&hmac, hash);

        if (memcmp(hash, test_hmac[i].output, SHA384_DIGEST_SIZE) != 0)
            appData.hmac_sha384_test_result++;
    }
}
#endif /* NO_HMAC && WOLFSSL_SHA384 */

#if !defined(NO_HMAC) && defined(WOLFSSL_SHA512)
void hmac_sha512_test(void)
{
    Hmac hmac;
    byte hash[SHA512_DIGEST_SIZE];

    const char* keys[]=
    {
        "\x0b\x0b\x0b\x0b\x0b\x0b\x0b\x0b\x0b\x0b\x0b\x0b\x0b\x0b\x0b\x0b\x0b"
                                                                "\x0b\x0b\x0b",
        "Jefe",
        "\xAA\xAA\xAA\xAA\xAA\xAA\xAA\xAA\xAA\xAA\xAA\xAA\xAA\xAA\xAA\xAA\xAA"
                                                                "\xAA\xAA\xAA"
    };

    testVector a, b, c;
    testVector test_hmac[3];

    int times = sizeof(test_hmac) / sizeof(testVector), i;

    a.input  = "Hi There";
    a.output = "\x87\xaa\x7c\xde\xa5\xef\x61\x9d\x4f\xf0\xb4\x24\x1a\x1d\x6c"
               "\xb0\x23\x79\xf4\xe2\xce\x4e\xc2\x78\x7a\xd0\xb3\x05\x45\xe1"
               "\x7c\xde\xda\xa8\x33\xb7\xd6\xb8\xa7\x02\x03\x8b\x27\x4e\xae"
               "\xa3\xf4\xe4\xbe\x9d\x91\x4e\xeb\x61\xf1\x70\x2e\x69\x6c\x20"
               "\x3a\x12\x68\x54";
    a.inLen  = strlen(a.input);
    a.outLen = SHA512_DIGEST_SIZE;

    b.input  = "what do ya want for nothing?";
    b.output = "\x16\x4b\x7a\x7b\xfc\xf8\x19\xe2\xe3\x95\xfb\xe7\x3b\x56\xe0"
               "\xa3\x87\xbd\x64\x22\x2e\x83\x1f\xd6\x10\x27\x0c\xd7\xea\x25"
               "\x05\x54\x97\x58\xbf\x75\xc0\x5a\x99\x4a\x6d\x03\x4f\x65\xf8"
               "\xf0\xe6\xfd\xca\xea\xb1\xa3\x4d\x4a\x6b\x4b\x63\x6e\x07\x0a"
               "\x38\xbc\xe7\x37";
    b.inLen  = strlen(b.input);
    b.outLen = SHA512_DIGEST_SIZE;

    c.input  = "\xDD\xDD\xDD\xDD\xDD\xDD\xDD\xDD\xDD\xDD\xDD\xDD\xDD\xDD"
               "\xDD\xDD\xDD\xDD\xDD\xDD\xDD\xDD\xDD\xDD\xDD\xDD\xDD\xDD\xDD"
               "\xDD\xDD\xDD\xDD\xDD\xDD\xDD\xDD\xDD\xDD\xDD\xDD\xDD\xDD\xDD"
               "\xDD\xDD\xDD\xDD\xDD\xDD";
    c.output = "\xfa\x73\xb0\x08\x9d\x56\xa2\x84\xef\xb0\xf0\x75\x6c\x89\x0b"
               "\xe9\xb1\xb5\xdb\xdd\x8e\xe8\x1a\x36\x55\xf8\x3e\x33\xb2\x27"
               "\x9d\x39\xbf\x3e\x84\x82\x79\xa7\x22\xc8\x06\xb4\x85\xa4\x7e"
               "\x67\xc8\x07\xb9\x46\xa3\x37\xbe\xe8\x94\x26\x74\x27\x88\x59"
               "\xe1\x32\x92\xfb";
    c.inLen  = strlen(c.input);
    c.outLen = SHA512_DIGEST_SIZE;

    test_hmac[0] = a;
    test_hmac[1] = b;
    test_hmac[2] = c;

    appData.hmac_sha512_test_result = 0;
    
    for (i = 0; i < times; ++i) {
        wc_HmacSetKey(&hmac, SHA512, (byte*)keys[i], (word32)strlen(keys[i]));
        wc_HmacUpdate(&hmac, (byte*)test_hmac[i].input,
                   (word32)test_hmac[i].inLen);
        wc_HmacFinal(&hmac, hash);

        if (memcmp(hash, test_hmac[i].output, SHA512_DIGEST_SIZE) != 0)
            appData.hmac_sha512_test_result++;
    }
}
#endif /* NO_HMAC && WOLFSSL_SHA512 */

#ifndef NO_DES3
void des_test(void)
{
    const byte exp_pt[] = { /* "now is the time for all " w/o trailing 0 */
        0x6e,0x6f,0x77,0x20,0x69,0x73,0x20,0x74,
        0x68,0x65,0x20,0x74,0x69,0x6d,0x65,0x20,
        0x66,0x6f,0x72,0x20,0x61,0x6c,0x6c,0x20
    };

    byte gen_pt[24];
    byte gen_ct[24];

    Des enc;
    Des dec;

    const byte key[] =
    {
        0x01,0x23,0x45,0x67,0x89,0xab,0xcd,0xef
    };

    const byte iv[] =
    {
        0x12,0x34,0x56,0x78,0x90,0xab,0xcd,0xef
    };

    const byte exp_ct[] =
    {
        0x8b,0x7c,0x52,0xb0,0x01,0x2b,0x6c,0xb8,
        0x4f,0x0f,0xeb,0xf3,0xfb,0x5f,0x86,0x73,
        0x15,0x85,0xb3,0x22,0x4b,0x86,0x2b,0x4b
    };

    
    /* The above const allocates in RAM, but does not flush out of cache. Copy
       it back out so it is in physical memory. */
#if defined(WOLFSSL_MICROCHIP_PIC32MZ)
 //   SYS_DEVCON_DataCacheFlush();
#endif


    appData.des_test_result = 0;

    wc_Des_SetKey(&enc, key, iv, DES_ENCRYPTION);
    wc_Des_CbcEncrypt(&enc, gen_ct, exp_pt, sizeof(exp_pt));
    wc_Des_SetKey(&dec, key, iv, DES_DECRYPTION);
    wc_Des_CbcDecrypt(&dec, gen_pt, exp_ct, sizeof(exp_ct));

    if (memcmp(gen_pt, exp_pt, sizeof(gen_pt)))
        appData.des_test_result = 2;
    
    if (memcmp(gen_ct, exp_ct, sizeof(gen_ct)))
        appData.des_test_result++;
}
#endif /* NO_DES3 */


#ifndef NO_DES3
void des3_test(void)
{
    const byte vector[] = { /* "Now is the time for all " w/o trailing 0 */
        0x4e,0x6f,0x77,0x20,0x69,0x73,0x20,0x74,
        0x68,0x65,0x20,0x74,0x69,0x6d,0x65,0x20,
        0x66,0x6f,0x72,0x20,0x61,0x6c,0x6c,0x20
    };

    byte plain[24];
    byte cipher[24];

    CRYPT_TDES_CTX enc;
    CRYPT_TDES_CTX dec;

    const byte key3[] =
    {
        0x01,0x23,0x45,0x67,0x89,0xab,0xcd,0xef,
        0xfe,0xde,0xba,0x98,0x76,0x54,0x32,0x10,
        0x89,0xab,0xcd,0xef,0x01,0x23,0x45,0x67
    };
    const byte iv3[] =
    {
        0x12,0x34,0x56,0x78,0x90,0xab,0xcd,0xef,
        0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,
        0x11,0x21,0x31,0x41,0x51,0x61,0x71,0x81

    };

    const byte verify3[] =
    {
        0x43,0xa0,0x29,0x7e,0xd1,0x84,0xf8,0x0e,
        0x89,0x64,0x84,0x32,0x12,0xd5,0x08,0x98,
        0x18,0x94,0x15,0x74,0x87,0x12,0x7d,0xb0
    };

    appData.des3_test_result = 0;
    
    /* The above const allocates in RAM, but does not flush out of cache. Copy
       it back out so it is in physical memory. */
#if defined(HW_CRYPTO)
    SYS_DEVCON_DataCacheFlush();
#endif
    CRYPT_TDES_KeySet(&enc, key3, iv3, DES_ENCRYPTION);
    CRYPT_TDES_KeySet(&dec, key3, iv3, DES_DECRYPTION);
    CRYPT_TDES_CBC_Encrypt(&enc, cipher, vector, sizeof(vector));
    CRYPT_TDES_CBC_Decrypt(&dec, plain, verify3, sizeof(verify3));

    if (memcmp(plain, vector, sizeof(plain)))
        appData.des3_test_result = 2;

    if (memcmp(cipher, verify3, sizeof(cipher)))
        appData.des3_test_result++;
}
#endif /* NO_DES3 */

#ifndef NO_AES
void aes_test(void)
{
    CRYPT_AES_CTX enc;
    CRYPT_AES_CTX dec;

    const byte msg[] = { /* "now is the time for all " w/o trailing 0 */
        0x6e,0x6f,0x77,0x20,0x69,0x73,0x20,0x74,
        0x68,0x65,0x20,0x74,0x69,0x6d,0x65,0x20
    };

    const byte verify[] =
    {
        0x95,0x94,0x92,0x57,0x5f,0x42,0x81,0x53,
        0x2c,0xcc,0x9d,0x46,0x77,0xa2,0x33,0xcb
    };

    byte key[] = "0123456789abcdef   ";  /* align */
    byte iv[]  = "1234567890abcdef   ";  /* align */

    byte cipher[AES_BLOCK_SIZE * 4];
    byte plain [AES_BLOCK_SIZE * 4];

    /* The above const allocates in RAM, but does not flush out of cache. Copy
       it back out so it is in physical memory. */
#if defined(HW_CRYPTO)
    SYS_DEVCON_DataCacheFlush();
#endif
    CRYPT_AES_KeySet(&enc, key, AES_BLOCK_SIZE, iv, AES_ENCRYPTION);
    CRYPT_AES_KeySet(&dec, key, AES_BLOCK_SIZE, iv, AES_DECRYPTION);

    CRYPT_AES_CBC_Encrypt(&enc, cipher, msg,   AES_BLOCK_SIZE);
    CRYPT_AES_CBC_Decrypt(&dec, plain, verify, AES_BLOCK_SIZE);

    appData.aes_cbc_test_result = 0;

    if (memcmp(plain, msg, AES_BLOCK_SIZE))
        appData.aes_cbc_test_result = 2;

    if (memcmp(cipher, verify, AES_BLOCK_SIZE))
        appData.aes_cbc_test_result++;

#ifdef WOLFSSL_AES_COUNTER
    {
        const byte ctrKey[] =
        {
            0x2b,0x7e,0x15,0x16,0x28,0xae,0xd2,0xa6,
            0xab,0xf7,0x15,0x88,0x09,0xcf,0x4f,0x3c
        };

        const byte ctrIv[] =
        {
            0xf0,0xf1,0xf2,0xf3,0xf4,0xf5,0xf6,0xf7,
            0xf8,0xf9,0xfa,0xfb,0xfc,0xfd,0xfe,0xff
        };

        const byte ctrPlain[] =
        {
            0x6b,0xc1,0xbe,0xe2,0x2e,0x40,0x9f,0x96,
            0xe9,0x3d,0x7e,0x11,0x73,0x93,0x17,0x2a,
            0xae,0x2d,0x8a,0x57,0x1e,0x03,0xac,0x9c,
            0x9e,0xb7,0x6f,0xac,0x45,0xaf,0x8e,0x51,
            0x30,0xc8,0x1c,0x46,0xa3,0x5c,0xe4,0x11,
            0xe5,0xfb,0xc1,0x19,0x1a,0x0a,0x52,0xef,
            0xf6,0x9f,0x24,0x45,0xdf,0x4f,0x9b,0x17,
            0xad,0x2b,0x41,0x7b,0xe6,0x6c,0x37,0x10
        };

        const byte ctrCipher[] =
        {
            0x87,0x4d,0x61,0x91,0xb6,0x20,0xe3,0x26,
            0x1b,0xef,0x68,0x64,0x99,0x0d,0xb6,0xce,
            0x98,0x06,0xf6,0x6b,0x79,0x70,0xfd,0xff,
            0x86,0x17,0x18,0x7b,0xb9,0xff,0xfd,0xff,
            0x5a,0xe4,0xdf,0x3e,0xdb,0xd5,0xd3,0x5e,
            0x5b,0x4f,0x09,0x02,0x0d,0xb0,0x3e,0xab,
            0x1e,0x03,0x1d,0xda,0x2f,0xbe,0x03,0xd1,
            0x79,0x21,0x70,0xa0,0xf3,0x00,0x9c,0xee
        };

        CRYPT_AES_KeySet(&enc, ctrKey, AES_BLOCK_SIZE, ctrIv, AES_ENCRYPTION);
        /* Ctr only uses encrypt, even on key setup */
        CRYPT_AES_KeySet(&dec, ctrKey, AES_BLOCK_SIZE, ctrIv, AES_ENCRYPTION);

        /* The above const allocates in RAM, but does not flush out of cache. 
           Copy it back out so it is in physical memory. */
#if defined(HW_CRYPTO)
        SYS_DEVCON_DataCacheFlush();
#endif
        CRYPT_AES_CTR_Encrypt(&enc, cipher, ctrPlain, AES_BLOCK_SIZE*4);
        CRYPT_AES_CTR_Encrypt(&dec, plain, ctrCipher, AES_BLOCK_SIZE*4);

        appData.aes_ctr_test_result = 0;
        
        if (memcmp(plain, ctrPlain, AES_BLOCK_SIZE*4))
            appData.aes_ctr_test_result = 2;

        if (memcmp(cipher, ctrCipher, AES_BLOCK_SIZE*4))
            appData.aes_ctr_test_result++;
    }
#endif /* WOLFSSL_AES_COUNTER */
}

#endif // NO_AES

void random_test(void)
{
    CRYPT_RNG_CTX  rng;
    byte block[32];
    int ret;

    appData.random_test_result = 0;

    ret = CRYPT_RNG_Initialize(&rng);
    if (ret != 0) 
    {
        appData.random_test_result++;
    }
    else
    {
        ret = CRYPT_RNG_BlockGenerate(&rng, block, sizeof(block));   
        if (ret != 0) 
        {
            appData.random_test_result++;
        }
    }
  
}


// *****************************************************************************
// *****************************************************************************
// Section: Application Callback Functions
// *****************************************************************************
// *****************************************************************************

void APP_ReadComplete(void *handle) {
    appData.rdComplete = true;
}

void APP_WriteComplete(void *handle) {
    appData.wrComplete = true;
}

void APP_Reset() {
    appData.rdComplete = true;
    appData.wrComplete = true;
}


// *****************************************************************************
// *****************************************************************************
// Section: Application Initialization and State Machine Functions
// *****************************************************************************
// *****************************************************************************

/*******************************************************************************
  Function:
    void APP_Initialize ( void )

  Remarks:
    See prototype in app.h.
 */
char *msgBuffer = "\r\n Application created " __DATE__ " " __TIME__ " initialized!\r\n";

void APP_Initialize(void) {
    /* Place the App state machine in its initial state. */
    appData.state = APP_STATE_INIT;

}

/******************************************************************************
  Function:
    void APP_Tasks ( void )

  Remarks:
    See prototype in app.h.
 */

void APP_Tasks(void) {

    static int j;

    /* Check the application's current state. */
    switch (appData.state) {
            /* Application's initial state. */
        case APP_STATE_INIT:
        {
            /* Show Hyperterminal is working using available output functions */
            //            SYS_MESSAGE("SYS_MESSAGE:" "\r\n Application created " __DATE__ " " __TIME__ " initialized!\r\n");            
            //            SYS_DEBUG(SYS_ERROR_INFO,"SYS_DEBUG:" "\r\n Application created " __DATE__ " " __TIME__ " initialized!\r\n");
            // SYS_CONSOLE_Write(SYS_CONSOLE_INDEX_0, STDOUT_FILENO, msgBuffer, strlen(msgBuffer));            

            appData.state = APP_STATE_TEST_MD5;
            break;
        }

        case APP_STATE_TEST_MD5:
            md5_test();
            appData.state = APP_STATE_TEST_SHA;
            break;

         case APP_STATE_TEST_SHA:
            sha_test();
            appData.state = APP_STATE_TEST_SHA256;
            break;

         case APP_STATE_TEST_SHA256:
            sha256_test();
            appData.state = APP_STATE_TEST_SHA384;
            break;
 
        case APP_STATE_TEST_SHA384:
            sha384_test();
            appData.state = APP_STATE_TEST_SHA512;
            break;

        case APP_STATE_TEST_SHA512:
            sha512_test();
            appData.state = APP_STATE_TEST_HMAC_MD5;
            break;
 
        case APP_STATE_TEST_HMAC_MD5:
            hmac_md5_test();
            appData.state = APP_STATE_TEST_HMAC_SHA;
            break;
            
        case APP_STATE_TEST_HMAC_SHA:
            hmac_sha_test();
            appData.state = APP_STATE_TEST_HMAC_SHA256;
            break;
             
        case APP_STATE_TEST_HMAC_SHA256:
            hmac_sha256_test();
            appData.state = APP_STATE_TEST_HMAC_SHA384;
            break;
              
        case APP_STATE_TEST_HMAC_SHA384:
            hmac_sha384_test();
            appData.state = APP_STATE_TEST_HMAC_SHA512;
            break;
              
        case APP_STATE_TEST_HMAC_SHA512:
            hmac_sha512_test();
            appData.state = APP_STATE_TEST_DES;
            break;
              
        case APP_STATE_TEST_DES:
           des_test();
            appData.state = APP_STATE_TEST_DES3;
            break;
                   
        case APP_STATE_TEST_DES3:
            des3_test();
            appData.state = APP_STATE_TEST_AES;
            break;
                          
        case APP_STATE_TEST_AES:
            aes_test();
            appData.state = APP_STATE_TEST_RANDOM;
            break;
   
        case APP_STATE_TEST_RANDOM:
            random_test();
            appData.state = APP_STATE_DISPLAY_RESULTS;
            break;
          
        case APP_STATE_DISPLAY_RESULTS:
            switch (j) {
                case 0:
#ifndef NO_MD5
                    sprintf(printBuffer, "%s\n\rMD5 test:          %d", 
                            printBuffer, appData.md5_test_result);
#endif
                    break;
                
                case 1:
#ifndef NO_SHA
                    sprintf(printBuffer, "%s\n\rSHA test:          %d", 
                            printBuffer, appData.sha_test_result);
#endif
                    break;
                    
                case 2:
#ifndef NO_SHA256
                    sprintf(printBuffer, "%s\n\rSHA256 test:       %d", 
                            printBuffer, appData.sha256_test_result);
#endif
                    break;

                case 3:
#ifdef WOLFSSL_SHA384
                    sprintf(printBuffer, "%s\n\rSHA384 test:       %d", 
                            printBuffer, appData.sha384_test_result);
#endif
                    break; 

                case 4:
#ifdef WOLFSSL_SHA512
                    sprintf(printBuffer, "%s\n\rSHA512 test:       %d", 
                            printBuffer, appData.sha512_test_result);
#endif
                    break;
 
                case 5:
#if !defined(NO_HMAC) && !defined(NO_MD5)
                    sprintf(printBuffer, "%s\n\rHMAC_MD5 test:     %d", 
                            printBuffer, appData.hmac_md5_test_result);
#endif
                    break;
 
                case 6:
#if !defined(NO_HMAC) && !defined(NO_SHA)
                    sprintf(printBuffer, "%s\n\rHMAC_SHA test:     %d", 
                            printBuffer, appData.hmac_sha_test_result);
#endif
                    break;            
  
                case 7:
#if !defined(NO_HMAC) && !defined(NO_SHA256)
                    sprintf(printBuffer, "%s\n\rHMAC_SHA256 test:  %d", 
                            printBuffer, appData.hmac_sha256_test_result);
#endif
                    break; 
  
                case 8:
#if !defined(NO_HMAC) && defined(WOLFSSL_SHA384)
                    sprintf(printBuffer, "%s\n\rHMAC_SHA384 test:  %d", 
                            printBuffer, appData.hmac_sha384_test_result);
#endif
                    break; 
   
                case 9:
#if !defined(NO_HMAC) && defined(WOLFSSL_SHA512)
                    sprintf(printBuffer, "%s\n\rHMAC_SHA512 test:  %d", 
                            printBuffer, appData.hmac_sha512_test_result);
#endif
                    break;
                    
                case 10:
#ifndef NO_DES3
                    sprintf(printBuffer, "%s\n\rDES test:          %d", 
                            printBuffer, appData.des_test_result);
#endif
                    break;
                    
                case 11:
#ifndef NO_DES3
                    sprintf(printBuffer, "%s\n\rDES3 test:         %d", 
                            printBuffer, appData.des3_test_result);
#endif
                    break;
                    
                case 12:
#ifndef NO_AES
                    sprintf(printBuffer, "%s\n\rAES CBC test:      %d", 
                            printBuffer, appData.aes_cbc_test_result);
#ifdef WOLFSSL_AES_COUNTER
                    sprintf(printBuffer, "%s\n\rAES CTR test:      %d", 
                            printBuffer, appData.aes_ctr_test_result);
#endif                    
#endif
                    break;                    
                     
                case 13:
                    sprintf(printBuffer, "%s\n\rRANDOM test:       %d", 
                            printBuffer, appData.random_test_result);
                    break;
            }
            
            j++;
            if (j > 13)
                appData.state = APP_STATE_CHECK_RESULTS;
            else {
                appData.state = APP_STATE_WAIT_FOR_CONSOLE;
            }
            break;

        case APP_STATE_CHECK_RESULTS:
            if (
#ifndef NO_MD5
                MD5_Expected != appData.md5_test_result 
#endif
#ifndef NO_SHA                    
                || SHA_Expected != appData.sha_test_result
#endif
#ifndef NO_SHA256                    
                || SHA256_Expected != appData.sha256_test_result
#endif
#ifdef WOLFSSL_SHA384                    
                || SHA384_Expected != appData.sha384_test_result
#endif
#ifdef WOLFSSL_SHA512                    
                || SHA512_Expected != appData.sha512_test_result
#endif
#if !defined(NO_HMAC) && !defined(NO_MD5)                    
                || HMAC_MD5_Expected != appData.hmac_md5_test_result
#endif
#if !defined(NO_HMAC) && !defined(NO_SHA)                    
                || HMAC_SHA_Expected != appData.hmac_sha_test_result
#endif
#if !defined(NO_HMAC) && !defined(NO_SHA256)                    
                || HMAC_SHA256_Expected != appData.hmac_sha256_test_result
#endif
#if !defined(NO_HMAC) && defined(WOLFSSL_SHA384)                    
                || HMAC_SHA384_Expected != appData.hmac_sha384_test_result
#endif
#if !defined(NO_HMAC) && defined(WOLFSSL_SHA512)                    
                || HMAC_SHA512_Expected != appData.hmac_sha512_test_result
#endif
#ifndef NO_DES3                   
                || DES_Expected != appData.des_test_result
#endif
#ifndef NO_DES3                   
                || DES3_Expected != appData.des3_test_result
#endif
#ifndef NO_AES                   
                || AES_CBC_Expected != appData.aes_cbc_test_result
#ifdef WOLFSSL_AES_COUNTER                    
                || AES_CTR_Expected != appData.aes_ctr_test_result
#endif
#endif
                || Random_Expected != appData.random_test_result
                ) 
            {    
                // We had an error during comparisons
                sprintf(printBuffer, "%s\n\rA test failed.\n", printBuffer);
            } else {
                sprintf(printBuffer, "%s\n\rAll tests passed.\n", printBuffer);
            }
            SYS_CONSOLE_Write(SYS_CONSOLE_INDEX_0, STDOUT_FILENO, printBuffer, 
                              strlen(printBuffer));
            appData.state = APP_STATE_SPIN;
            break;

        case APP_STATE_WAIT_FOR_CONSOLE:
            //            if (appData.wrComplete)
            if (appData.wallTime <= APP_getTicks())
                appData.state = APP_STATE_DISPLAY_RESULTS;
            break;

        case APP_STATE_SPIN:
            
            /* The default state should never be executed. */
        default:
        {
            /* TODO: Handle error in application's state machine. */
            break;
        }
    }
}


/*******************************************************************************
 End of File
 */
