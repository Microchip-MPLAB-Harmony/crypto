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

#include <stdio.h>
#include <string.h>
#include <inttypes.h>

#include "app.h"
#include "wolfssl/wolfcrypt/md5.h"
#include "wolfssl/wolfcrypt/sha.h"
#include "wolfssl/wolfcrypt/sha256.h"
#include "wolfssl/wolfcrypt/sha512.h"
#include "wolfssl/wolfcrypt/random.h"
#include "wolfssl/wolfcrypt/hmac.h"
#ifndef NO_AES
#include "wolfssl/wolfcrypt/aes.h"
#endif
#ifdef HAVE_ECC
#include "wolfssl/wolfcrypt/ecc.h"
#endif
#ifdef HAVE_LIBZ
#include "wolfssl/wolfcrypt/compress.h"
#endif
#ifndef NO_DES3
#include "wolfssl/wolfcrypt/des3.h"
#endif
#ifndef NO_RSA
#include "wolfssl/wolfcrypt/rsa.h"
#include "wolfssl/certs_test.h"
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

static const int expectedResult = 0;
static const int dummy_test_result = 0;
static int testCount = 0;
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
void md5_test(void);
void sha_test(void);
void sha256_test(void);
void sha384_test(void);
void sha512_test(void);
void hmac_md5_test(void);
void hmac_sha_test(void);
void hmac_sha256_test(void);
void hmac_sha384_test(void);
void hmac_sha512_test(void);
void random_test(void);
#ifndef NO_AES
    void aes_test(void);
    #ifdef HAVE_AESGCM
        int  aesgcm_default_test(void);
    #endif
#endif
#ifdef HAVE_ECC
    void  ecc_test(void);
#endif
#ifdef HAVE_LIBZ
    void compress_test(void);
#endif
#ifndef NO_DES3
void des_test(void);
void des3_test(void);
#endif
#ifndef NO_RSA
void rsa_test(void);
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



// *****************************************************************************
// *****************************************************************************
// Section: Application Local Routines
// *****************************************************************************
// *****************************************************************************
uint32_t APP_getTicks(void) {
    return SYS_TIME_CounterGet();
}

char printBuffer[10 * 1024] = {0};

#ifndef NO_MD5
void md5_test(void)
{
    CRYPT_MD5_CTX  md5;
    uint8_t hash[MD5_DIGEST_SIZE];

    testVector a, b, c, d, e;
    testVector test_md5[5];
    int times = sizeof(test_md5) / sizeof(testVector), i;
    uint32_t hashStart;
    uint32_t hashStop;

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

    appData.md5_test_result = times;

    hashStart = APP_getTicks();	
    for (i = 0; i < times; ++i) {
        CRYPT_MD5_DataAdd(&md5, (uint8_t*)test_md5[i].input, (word32)test_md5[i].inLen);
        CRYPT_MD5_Finalize(&md5, hash);

        if (memcmp(hash, test_md5[i].output, MD5_DIGEST_SIZE) == 0)
        {
            appData.md5_test_result--;
        }
    }
    hashStop = APP_getTicks();
    appData.md5_timing = hashStop - hashStart;
}
#endif /* NO_MD5 */

#ifndef NO_SHA
void sha_test(void)
{
    CRYPT_SHA_CTX  sha;
    uint8_t hash[SHA_DIGEST_SIZE];

    testVector a, b, c, d;
    testVector test_sha[4];
    int times = sizeof(test_sha) / sizeof(struct testVector), i;
    uint32_t hashStart;
    uint32_t hashStop;

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

    appData.sha_test_result = times;
    
    hashStart = APP_getTicks();
    for (i = 0; i < times; ++i) {
        CRYPT_SHA_DataAdd(&sha, (uint8_t*)test_sha[i].input, (word32)test_sha[i].inLen);
        CRYPT_SHA_Finalize(&sha, hash);

        if (memcmp(hash, test_sha[i].output, SHA_DIGEST_SIZE) == 0) {
            printf("\ntest_sha[%d] passed", i);
            appData.sha_test_result--;
        }

    }
    hashStop = APP_getTicks();
    appData.sha_timing = hashStop - hashStart;
}
#endif /* NO_SHA */

#ifndef NO_SHA256
void sha256_test(void)
{
    CRYPT_SHA256_CTX sha;
    uint8_t   hash[SHA256_DIGEST_SIZE];

    testVector a, b;
    testVector test_sha[2];
    int times = sizeof(test_sha) / sizeof(struct testVector), i;
    uint32_t hashStart;
    uint32_t hashStop;

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

    appData.sha256_test_result = times;
    
    hashStart = APP_getTicks();
    for (i = 0; i < times; ++i) {
        CRYPT_SHA256_DataAdd(&sha, (uint8_t*)test_sha[i].input,(word32)test_sha[i].inLen);
        CRYPT_SHA256_Finalize(&sha, hash);

        if (memcmp(hash, test_sha[i].output, SHA256_DIGEST_SIZE) == 0)
            appData.sha256_test_result--;
    }
    hashStop = APP_getTicks();
    appData.sha256_timing = hashStop - hashStart;
}
#endif /* NO_SHA256 */

#ifdef WOLFSSL_SHA224
void sha224_test(void)
{
    CRYPT_SHA256_CTX sha;
    byte   hash[SHA224_DIGEST_SIZE];

    testVector a, b;
    testVector test_sha[2];
    int times = sizeof(test_sha) / sizeof(struct testVector), i;
    uint32_t hashStart;
    uint32_t hashStop;

    a.input  = "abc";
    a.output = "\x23\x09\x7D\x22"
               "\x34\x05\xD8\x22"
               "\x86\x42\xA4\x77"
               "\xBD\xA2\x55\xB3"
               "\x2A\xAD\xBC\xE4"
               "\xBD\xA0\xB3\xF7"
               "\xE3\x6C\x9D\xA7";
    a.inLen  = strlen(a.input);
    a.outLen = SHA224_DIGEST_SIZE;

    b.input  = "abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq";
    b.output = "\x75\x38\x8B\x16"
               "\x51\x27\x76\xCC"
               "\x5D\xBA\x5D\xA1"
               "\xFD\x89\x01\x50"
               "\xB0\xC6\x45\x5C"
               "\xB4\xF5\x8B\x19"
               "\x52\x52\x25\x25";
    b.inLen  = strlen(b.input);
    b.outLen = SHA224_DIGEST_SIZE;

    test_sha[0] = a;
    test_sha[1] = b;

    CRYPT_SHA224_Initialize(&sha);

    appData.sha224_test_result = times;
    
    hashStart = APP_getTicks();
    for (i = 0; i < times; ++i) {
        CRYPT_SHA224_DataAdd(&sha, (byte*)test_sha[i].input,(word32)test_sha[i].inLen);
        CRYPT_SHA224_Finalize(&sha, hash);

        if (memcmp(hash, test_sha[i].output, SHA224_DIGEST_SIZE) == 0)
            appData.sha224_test_result--;
    }
    hashStop = APP_getTicks();
    appData.sha224_timing = hashStop - hashStart;
}
#endif /* WOLFSSL_SHA224 */

#ifdef WOLFSSL_SHA384
void sha384_test(void)
{
    CRYPT_SHA384_CTX sha;
    uint8_t   hash[SHA384_DIGEST_SIZE];

    testVector a, b;
    testVector test_sha[2];
    int times = sizeof(test_sha) / sizeof(struct testVector), i;
    uint32_t hashStart;
    uint32_t hashStop;

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

    appData.sha384_test_result = times;
    
    hashStart = APP_getTicks();
    for (i = 0; i < times; ++i) {
        CRYPT_SHA384_DataAdd(&sha, (uint8_t*)test_sha[i].input,(word32)test_sha[i].inLen);
        CRYPT_SHA384_Finalize(&sha, hash);

        if (memcmp(hash, test_sha[i].output, SHA384_DIGEST_SIZE) == 0)
            appData.sha384_test_result--;
    }
    hashStop = APP_getTicks();
    appData.sha384_timing = hashStop - hashStart;
}
#endif /* WOLFSSL_SHA384 */

#ifdef WOLFSSL_SHA512
void sha512_test(void)
{
    CRYPT_SHA512_CTX sha;
    uint8_t   hash[SHA512_DIGEST_SIZE];

    testVector a, b;
    testVector test_sha[2];
    int times = sizeof(test_sha) / sizeof(struct testVector), i;
    uint32_t hashStart;
    uint32_t hashStop;

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

    appData.sha512_test_result = times;
    
    hashStart = APP_getTicks();
    for (i = 0; i < times; ++i) {
        CRYPT_SHA512_DataAdd(&sha, (uint8_t*)test_sha[i].input,(word32)test_sha[i].inLen);
        CRYPT_SHA512_Finalize(&sha, hash);

        if (memcmp(hash, test_sha[i].output, SHA512_DIGEST_SIZE) == 0)
            appData.sha512_test_result--;
    }
    hashStop = APP_getTicks();
    appData.sha512_timing = hashStop - hashStart;
}
#endif /* WOLFSSL_SHA512 */

#if !defined(NO_HMAC) && !defined(NO_MD5)
void hmac_md5_test(void)
{
    Hmac hmac;
    uint8_t hash[MD5_DIGEST_SIZE];

    const char* keys[]=
    {
        "\x0b\x0b\x0b\x0b\x0b\x0b\x0b\x0b\x0b\x0b\x0b\x0b\x0b\x0b\x0b\x0b",
        "Jefe",
        "\xAA\xAA\xAA\xAA\xAA\xAA\xAA\xAA\xAA\xAA\xAA\xAA\xAA\xAA\xAA\xAA"
    };

    testVector a, b, c;
    testVector test_hmac[3];

    int times = sizeof(test_hmac) / sizeof(testVector), i;
    uint32_t hashStart;
    uint32_t hashStop;

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

    appData.hmac_md5_test_result = times;
    
    hashStart = APP_getTicks();
    for (i = 0; i < times; ++i) {
        wc_HmacSetKey(&hmac, MD5, (uint8_t*)keys[i], (word32)strlen(keys[i]));
        wc_HmacUpdate(&hmac, (uint8_t*)test_hmac[i].input,
                   (word32)test_hmac[i].inLen);
        wc_HmacFinal(&hmac, hash);

        if (memcmp(hash, test_hmac[i].output, MD5_DIGEST_SIZE) == 0)
            appData.hmac_md5_test_result--;
    }
    hashStop = APP_getTicks();
    appData.hmac_md5_timing = hashStop - hashStart;
}
#endif /* NO_HMAC && NO_MD5 */

#if !defined(NO_HMAC) && !defined(NO_SHA)
void hmac_sha_test(void)
{
    Hmac hmac;
    uint8_t hash[SHA_DIGEST_SIZE];

    const char* keys[]=
    {
        "\x0b\x0b\x0b\x0b\x0b\x0b\x0b\x0b\x0b\x0b\x0b\x0b\x0b\x0b\x0b\x0b\x0b"
                                                                "\x0b\x0b\x0b",
//        "\x00\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0A\x0B\x0C\x0D\x0E\x0F"
//        "\x10\x11\x12\x13\x14\x15\x16\x17\x18\x19\x1A\x1B\x1C\x1D\x1E\x1F"
//        "\x20\x21\x22\x23\x24\x25\x26\x27\x28\x29\x2A\x2B\x2C\x2D\x2E\x2F"
//        "\x30\x31\x32\x33\x34\x35\x36\x37\x38\x39\x3A\x3B\x3C\x3D\x3E\x3F",
        "Jefe",
        "\xAA\xAA\xAA\xAA\xAA\xAA\xAA\xAA\xAA\xAA\xAA\xAA\xAA\xAA\xAA\xAA\xAA"
                                                                "\xAA\xAA\xAA"
    };

    testVector a, b, c;
    testVector test_hmac[3];

    int times = sizeof(test_hmac) / sizeof(testVector), i;
    uint32_t hashStart;
    uint32_t hashStop;

    a.input  = "Hi There";
    a.output = "\xb6\x17\x31\x86\x55\x05\x72\x64\xe2\x8b\xc0\xb6\xfb\x37\x8c"
               "\x8e\xf1\x46\xbe\x00";
//    a.input  = "Sample message for keylen=blocklen";
//    a.output = "\x5F\xD5\x96\xEE\x78\xD5\x55\x3C\x8F\xF4\xE7\x2D"
//               "\x26\x6D\xFD\x19\x23\x66\xDA\x29";
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

    appData.hmac_sha_test_result = times;
    
    hashStart = APP_getTicks();
    for (i = 0; i < times; ++i) {
        wc_HmacSetKey(&hmac, SHA, (uint8_t*)keys[i], (word32)strlen(keys[i]));
        wc_HmacUpdate(&hmac, (uint8_t*)test_hmac[i].input,
                   (word32)test_hmac[i].inLen);
        wc_HmacFinal(&hmac, hash);

        if (memcmp(hash, test_hmac[i].output, SHA_DIGEST_SIZE) == 0)
            appData.hmac_sha_test_result--;
    }
    hashStop = APP_getTicks();
    appData.hmac_sha_timing = hashStop - hashStart;
}
#endif /* NO_HMAC && NO_SHA */

#if !defined(NO_HMAC) && !defined(NO_SHA256)
void hmac_sha256_test(void)
{
    Hmac hmac;
    uint8_t hash[SHA256_DIGEST_SIZE];

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
    uint32_t hashStart;
    uint32_t hashStop;

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

    appData.hmac_sha256_test_result = times;
    
    hashStart = APP_getTicks();
    for (i = 0; i < times; ++i) {
        wc_HmacSetKey(&hmac, SHA256, (uint8_t*)keys[i], (word32)strlen(keys[i]));
        wc_HmacUpdate(&hmac, (uint8_t*)test_hmac[i].input,
                   (word32)test_hmac[i].inLen);
        wc_HmacFinal(&hmac, hash);

        if (memcmp(hash, test_hmac[i].output, SHA256_DIGEST_SIZE) == 0)
            appData.hmac_sha256_test_result--;
    }
    hashStop = APP_getTicks();
    appData.hmac_sha256_timing = hashStop - hashStart;
}
#endif /* NO_HMAC && NO_SHA256 */

#if !defined(NO_HMAC) && defined(WOLFSSL_SHA384)
void hmac_sha384_test(void)
{
    Hmac hmac;
    uint8_t hash[SHA384_DIGEST_SIZE];

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
    uint32_t hashStart;
    uint32_t hashStop;

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

    appData.hmac_sha384_test_result = times;
    
    hashStart = APP_getTicks();
    for (i = 0; i < times; ++i) {
        wc_HmacSetKey(&hmac, SHA384, (uint8_t*)keys[i], (word32)strlen(keys[i]));
        wc_HmacUpdate(&hmac, (uint8_t*)test_hmac[i].input,
                   (word32)test_hmac[i].inLen);
        wc_HmacFinal(&hmac, hash);

        if (memcmp(hash, test_hmac[i].output, SHA384_DIGEST_SIZE) == 0)
            appData.hmac_sha384_test_result--;
    }
    hashStop = APP_getTicks();
    appData.hmac_sha384_timing = hashStop - hashStart;
}
#endif /* NO_HMAC && WOLFSSL_SHA384 */

#if !defined(NO_HMAC) && defined(WOLFSSL_SHA512)
void hmac_sha512_test(void)
{
    Hmac hmac;
    uint8_t hash[SHA512_DIGEST_SIZE];

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
    uint32_t hashStart;
    uint32_t hashStop;

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

    appData.hmac_sha512_test_result = times;
    
    hashStart = APP_getTicks();
    for (i = 0; i < times; ++i) {
        wc_HmacSetKey(&hmac, SHA512, (uint8_t*)keys[i], (word32)strlen(keys[i]));
        wc_HmacUpdate(&hmac, (uint8_t*)test_hmac[i].input,
                   (word32)test_hmac[i].inLen);
        wc_HmacFinal(&hmac, hash);

        if (memcmp(hash, test_hmac[i].output, SHA512_DIGEST_SIZE) == 0)
            appData.hmac_sha512_test_result--;
    }
    hashStop = APP_getTicks();
    appData.hmac_sha512_timing = hashStop - hashStart;
}
#endif /* NO_HMAC && WOLFSSL_SHA512 */

#ifdef HAVE_ECC

void ecc_test(void)
{
    CRYPT_RNG_CTX     rng;
    uint8_t    sharedA[1024];
    uint8_t    sharedB[1024];
    uint8_t    sig[1024];
    uint8_t    digest[32];
    uint8_t    exportBuf[1024];

    word32  x, y;
    int     i, verify, ret;
    static ecc_key userA, userB, pubKey;

    appData.ecc_test_result = 12;
    uint32_t hashStart;
    uint32_t hashStop;
    
    ret = CRYPT_RNG_Initialize(&rng);
    hashStart = APP_getTicks();
    if (ret == 0)
        appData.ecc_test_result--;

    wc_ecc_init_ex(&userA, 0, 0);
    wc_ecc_init_ex(&userB, 0, 0);
    wc_ecc_init_ex(&pubKey, 0, 0);

    ret = wc_ecc_make_key((struct RNG *)&rng, 32, &userA);
    ret = wc_ecc_make_key((struct RNG *)&rng, 32, &userB);

    if (ret == 0)
        appData.ecc_test_result--;

    x = sizeof(sharedA);
    ret = wc_ecc_shared_secret(&userA, &userB, sharedA, &x);

    y = sizeof(sharedB);
    ret = wc_ecc_shared_secret(&userB, &userA, sharedB, &y);

    if (ret == 0)
        appData.ecc_test_result--;

    if (y == x)
        appData.ecc_test_result--;

    if (!(memcmp(sharedA, sharedB, x)))
        appData.ecc_test_result--;

    x = sizeof(exportBuf);
    ret = wc_ecc_export_x963(&userA, exportBuf, &x);
    if (ret == 0)
        appData.ecc_test_result--;

    ret = wc_ecc_import_x963(exportBuf, x, &pubKey);

    if (ret == 0)
        appData.ecc_test_result--;

    y = sizeof(sharedB);
    ret = wc_ecc_shared_secret(&userB, &pubKey, sharedB, &y);

    if (ret == 0)
        appData.ecc_test_result--;

    if (!(memcmp(sharedA, sharedB, y)))
        appData.ecc_test_result--;

    /* test DSA sign hash */
    for (i = 0; i < (int)sizeof(digest); i++)
        digest[i] = i;

    x = sizeof(sig);
    ret = wc_ecc_sign_hash(digest, sizeof(digest), sig, &x, (struct RNG *)&rng, &userA);

    verify = 0;
    ret = wc_ecc_verify_hash(sig, x, digest, sizeof(digest), &verify, &userA);

    if (ret == 0)
        appData.ecc_test_result--;

    if (verify == 1)
        appData.ecc_test_result--;

    x = sizeof(exportBuf);
    ret = wc_ecc_export_private_only(&userA, exportBuf, &x);
    if (ret == 0)
        appData.ecc_test_result--;

    wc_ecc_free(&pubKey);
    wc_ecc_free(&userB);
    wc_ecc_free(&userA);
    hashStop = APP_getTicks();
    appData.ecc_timing = hashStop - hashStart;
}
#endif  /* HAVE_ECC */

void random_test(void)
{
    CRYPT_RNG_CTX  rng;
    uint8_t block[32];
    int ret;
    uint32_t hashStart;
    uint32_t hashStop;

    appData.random_test_result = 1;

    hashStart = APP_getTicks();
    ret = CRYPT_RNG_Initialize(&rng);
    if (ret == 0) 
    {
        ret = CRYPT_RNG_BlockGenerate(&rng, block, sizeof(block));   
        if (ret == 0) 
            appData.random_test_result--;
    }
    hashStop = APP_getTicks();
    appData.random_timing = hashStop - hashStart;
}

#ifndef NO_AES
void aes_test(void)
{
    CRYPT_AES_CTX enc;
    CRYPT_AES_CTX dec;

#ifdef HAVE_AES_CBC
    const uint8_t msg[] = { /* "now is the time for all " w/o trailing 0 */
        0x6e,0x6f,0x77,0x20,0x69,0x73,0x20,0x74,
        0x68,0x65,0x20,0x74,0x69,0x6d,0x65,0x20
    };

    const uint8_t verify[] =
    {
        0x95,0x94,0x92,0x57,0x5f,0x42,0x81,0x53,
        0x2c,0xcc,0x9d,0x46,0x77,0xa2,0x33,0xcb
    };

    uint8_t key[] = "0123456789abcdef   ";  /* align */
    uint8_t iv[]  = "1234567890abcdef   ";  /* align */

    uint8_t cipher[AES_BLOCK_SIZE * 4] = {0};
    uint8_t plain [AES_BLOCK_SIZE * 4] = {0};
    int numCbcSubTests = 2;
#endif /* HAVE_AES_CBC */

    uint32_t hashStart;
    uint32_t hashStop;

#ifdef HAVE_AES_CBC
    hashStart = APP_getTicks();

    /* The above const allocates in RAM, but does not flush out of cache. Copy
       it back out so it is in physical memory. */
   #if defined(HW_CRYPTO)
    SYS_DEVCON_DataCacheFlush();
#endif
    CRYPT_AES_KeySet(&enc, key, AES_BLOCK_SIZE, iv, AES_ENCRYPTION);
    CRYPT_AES_KeySet(&dec, key, AES_BLOCK_SIZE, iv, AES_DECRYPTION);

    CRYPT_AES_CBC_Encrypt(&enc, cipher, msg,   AES_BLOCK_SIZE);
    CRYPT_AES_CBC_Decrypt(&dec, plain, verify, AES_BLOCK_SIZE);

    appData.aes_cbc_test_result = numCbcSubTests;

    if (!(memcmp(plain, msg, AES_BLOCK_SIZE)))
        appData.aes_cbc_test_result--;

    if (!(memcmp(cipher, verify, AES_BLOCK_SIZE)))
        appData.aes_cbc_test_result--;
    hashStop = APP_getTicks();
    appData.aes_cbc_timing = hashStop - hashStart;
#endif /* HAVE_AES_CBC */
    
#ifdef WOLFSSL_AES_COUNTER
    {
        const uint8_t ctrKey[] =
        {
            0x2b,0x7e,0x15,0x16,0x28,0xae,0xd2,0xa6,
            0xab,0xf7,0x15,0x88,0x09,0xcf,0x4f,0x3c
        };

        const uint8_t ctrIv[] =
        {
            0xf0,0xf1,0xf2,0xf3,0xf4,0xf5,0xf6,0xf7,
            0xf8,0xf9,0xfa,0xfb,0xfc,0xfd,0xfe,0xff
        };

        const uint8_t ctrPlain[] =
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

        const uint8_t ctrCipher[] =
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

        hashStart = APP_getTicks();
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

        int numCtrSubTests = 2;
        appData.aes_ctr_test_result = numCtrSubTests;
        
        if (!(memcmp(plain, ctrPlain, AES_BLOCK_SIZE*4)))
            appData.aes_ctr_test_result--;

        if (!(memcmp(cipher, ctrCipher, AES_BLOCK_SIZE*4)))
            appData.aes_ctr_test_result--;
    
        hashStop = APP_getTicks();
        appData.aes_ctr_timing = hashStop - hashStart;
    }
#endif /* WOLFSSL_AES_COUNTER */
}

#endif /* NO_AES */

#ifdef HAVE_AESGCM

static int aesgcm_default_test_helper(const uint8_t* key, int keySz, const uint8_t* iv, int ivSz,
		const uint8_t* plain, int plainSz, const uint8_t* cipher, int cipherSz,
		const uint8_t* aad, int aadSz, const uint8_t* tag, int tagSz)
{
    CRYPT_AES_CTX enc;
    CRYPT_AES_CTX dec;

    uint8_t resultT[AES_BLOCK_SIZE];
    uint8_t resultP[AES_BLOCK_SIZE * 3];
    uint8_t resultC[AES_BLOCK_SIZE * 3];
    int  result;

    memset(resultT, 0, sizeof(resultT));
    memset(resultC, 0, sizeof(resultC));
    memset(resultP, 0, sizeof(resultP));

    result = CRYPT_AES_GCM_SetKey(&enc, key, keySz);

    if (result != 0)
        return -4701;

    /* AES-GCM encrypt and decrypt both use AES encrypt internally */
    result = CRYPT_AES_GCM_Encrypt(&enc, resultC, plain, plainSz, iv, ivSz,
                                        resultT, tagSz, aad, aadSz);
    
    if (result != 0)
        return -4702;
    if (cipher != NULL) {
        if (memcmp(cipher, resultC, cipherSz))
            return -4703;
    }
    if (memcmp(tag, resultT, tagSz))
        return -4704;

#ifdef HAVE_AES_DECRYPT
    result = CRYPT_AES_GCM_SetKey(&dec, key, keySz);
    if (result != 0)
        return -4705;

    result = CRYPT_AES_GCM_Decrypt(&dec, resultP, resultC, cipherSz,
                      iv, ivSz, resultT, tagSz, aad, aadSz);
    if (result != 0)
        return -4706;
    if (plain != NULL) {
        if (memcmp(plain, resultP, plainSz))
        {
            int x = 0;
            uint8_t errorFound = 0;
            for (x = 0; x < plainSz; x++)
            {
                if (plain[x] != resultP[x])
                {
                    sprintf(printBuffer, "GCM Failed at uint8_t %x first uint8_t %x second uint8_t %x\r\n", x, plain[x], resultP[x]);
                    DRV_USART_WriteBuffer( appData.usartHandle, printBuffer, strlen(printBuffer));
                    errorFound = 1;
                    break;
                }
            }
            if (errorFound != 0)
            {
                return -4707;
            }
        }
    }

#endif /* HAVE_AES_DECRYPT */

    return 0;
}


/* tests that only use 12 uint8_t IV and 16 or less uint8_t AAD
 * test vectors are from NIST SP 800-38D
 * https://csrc.nist.gov/Projects/Cryptographic-Algorithm-Validation-Program/CAVP-TESTING-BLOCK-CIPHER-MODES*/
int aesgcm_default_test(void)
{
     uint8_t key1[] = {
        0x29, 0x8e, 0xfa, 0x1c, 0xcf, 0x29, 0xcf, 0x62,
        0xae, 0x68, 0x24, 0xbf, 0xc1, 0x95, 0x57, 0xfc
    };

     uint8_t iv1[] = {
        0x6f, 0x58, 0xa9, 0x3f, 0xe1, 0xd2, 0x07, 0xfa,
        0xe4, 0xed, 0x2f, 0x6d
    };

     uint8_t plain1[] = {
        0xcc, 0x38, 0xbc, 0xcd, 0x6b, 0xc5, 0x36, 0xad,
        0x91, 0x9b, 0x13, 0x95, 0xf5, 0xd6, 0x38, 0x01,
        0xf9, 0x9f, 0x80, 0x68, 0xd6, 0x5c, 0xa5, 0xac,
        0x63, 0x87, 0x2d, 0xaf, 0x16, 0xb9, 0x39, 0x01
    };

     uint8_t aad1[] = {
        0x02, 0x1f, 0xaf, 0xd2, 0x38, 0x46, 0x39, 0x73,
        0xff, 0xe8, 0x02, 0x56, 0xe5, 0xb1, 0xc6, 0xb1
    };

     uint8_t cipher1[] = {
        0xdf, 0xce, 0x4e, 0x9c, 0xd2, 0x91, 0x10, 0x3d,
        0x7f, 0xe4, 0xe6, 0x33, 0x51, 0xd9, 0xe7, 0x9d,
        0x3d, 0xfd, 0x39, 0x1e, 0x32, 0x67, 0x10, 0x46,
        0x58, 0x21, 0x2d, 0xa9, 0x65, 0x21, 0xb7, 0xdb
    };

     uint8_t tag1[] = {
        0x54, 0x24, 0x65, 0xef, 0x59, 0x93, 0x16, 0xf7,
        0x3a, 0x7a, 0x56, 0x05, 0x09, 0xa2, 0xd9, 0xf2
    };


     uint8_t key2[] = {
        0x01, 0x6d, 0xbb, 0x38, 0xda, 0xa7, 0x6d, 0xfe,
        0x7d, 0xa3, 0x84, 0xeb, 0xf1, 0x24, 0x03, 0x64
    };

     uint8_t iv2[] = {
        0x07, 0x93, 0xef, 0x3a, 0xda, 0x78, 0x2f, 0x78,
        0xc9, 0x8a, 0xff, 0xe3
    };

     uint8_t plain2[] = {
        0x4b, 0x34, 0xa9, 0xec, 0x57, 0x63, 0x52, 0x4b,
        0x19, 0x1d, 0x56, 0x16, 0xc5, 0x47, 0xf6, 0xb7
    };

     uint8_t cipher2[] = {
        0x60, 0x9a, 0xa3, 0xf4, 0x54, 0x1b, 0xc0, 0xfe,
        0x99, 0x31, 0xda, 0xad, 0x2e, 0xe1, 0x5d, 0x0c
    };

     uint8_t tag2[] = {
        0x33, 0xaf, 0xec, 0x59, 0xc4, 0x5b, 0xaf, 0x68,
        0x9a, 0x5e, 0x1b, 0x13, 0xae, 0x42, 0x36, 0x19
    };
     uint8_t key3[] = {
        0xb0, 0x1e, 0x45, 0xcc, 0x30, 0x88, 0xaa, 0xba,
        0x9f, 0xa4, 0x3d, 0x81, 0xd4, 0x81, 0x82, 0x3f
    };

     uint8_t iv3[] = {
        0x5a, 0x2c, 0x4a, 0x66, 0x46, 0x87, 0x13, 0x45,
        0x6a, 0x4b, 0xd5, 0xe1
    };

     uint8_t tag3[] = {
        0x01, 0x42, 0x80, 0xf9, 0x44, 0xf5, 0x3c, 0x68,
        0x11, 0x64, 0xb2, 0xff
    };
    uint32_t hashStart;
    uint32_t hashStop;

    hashStart = APP_getTicks();
        int numGcmSubTests = 3;

    int ret;
	ret = aesgcm_default_test_helper(key1, sizeof(key1), iv1, sizeof(iv1),
		plain1, sizeof(plain1), cipher1, sizeof(cipher1),
		aad1, sizeof(aad1), tag1, sizeof(tag1));
	if (ret == 0) {
		numGcmSubTests--;
	}

	ret = aesgcm_default_test_helper(key2, sizeof(key2), iv2, sizeof(iv2),
		plain2, sizeof(plain2), cipher2, sizeof(cipher2),
		NULL, 0, tag2, sizeof(tag2));
	if (ret == 0) {
		numGcmSubTests--;
	}
	ret = aesgcm_default_test_helper(key3, sizeof(key3), iv3, sizeof(iv3),
		NULL, 0, NULL, 0,
		NULL, 0, tag3, sizeof(tag3));
	if (ret == 0) {
		numGcmSubTests--;
	}
    hashStop = APP_getTicks();

    appData.aes_gcm_test_result = numGcmSubTests;
    appData.aes_gcm_timing = hashStop - hashStart;
    
	return 0;
}

int aesgcm_test(void)
{
    CRYPT_AES_CTX enc;

    /*
     * This is Test Case 16 from the document Galois/
     * Counter Mode of Operation (GCM) by McGrew and
     * Viega.
     */
    const uint8_t p[] =
    {
        0xd9, 0x31, 0x32, 0x25, 0xf8, 0x84, 0x06, 0xe5,
        0xa5, 0x59, 0x09, 0xc5, 0xaf, 0xf5, 0x26, 0x9a,
        0x86, 0xa7, 0xa9, 0x53, 0x15, 0x34, 0xf7, 0xda,
        0x2e, 0x4c, 0x30, 0x3d, 0x8a, 0x31, 0x8a, 0x72,
        0x1c, 0x3c, 0x0c, 0x95, 0x95, 0x68, 0x09, 0x53,
        0x2f, 0xcf, 0x0e, 0x24, 0x49, 0xa6, 0xb5, 0x25,
        0xb1, 0x6a, 0xed, 0xf5, 0xaa, 0x0d, 0xe6, 0x57,
        0xba, 0x63, 0x7b, 0x39
    };

    const uint8_t a[] =
    {
        0xfe, 0xed, 0xfa, 0xce, 0xde, 0xad, 0xbe, 0xef,
        0xfe, 0xed, 0xfa, 0xce, 0xde, 0xad, 0xbe, 0xef,
        0xab, 0xad, 0xda, 0xd2
    };

#ifdef WOLFSSL_AES_256
    const uint8_t k1[] =
    {
        0xfe, 0xff, 0xe9, 0x92, 0x86, 0x65, 0x73, 0x1c,
        0x6d, 0x6a, 0x8f, 0x94, 0x67, 0x30, 0x83, 0x08,
        0xfe, 0xff, 0xe9, 0x92, 0x86, 0x65, 0x73, 0x1c,
        0x6d, 0x6a, 0x8f, 0x94, 0x67, 0x30, 0x83, 0x08
    };

    const uint8_t iv1[] =
    {
        0xca, 0xfe, 0xba, 0xbe, 0xfa, 0xce, 0xdb, 0xad,
        0xde, 0xca, 0xf8, 0x88
    };

    const uint8_t c1[] =
    {
        0x52, 0x2d, 0xc1, 0xf0, 0x99, 0x56, 0x7d, 0x07,
        0xf4, 0x7f, 0x37, 0xa3, 0x2a, 0x84, 0x42, 0x7d,
        0x64, 0x3a, 0x8c, 0xdc, 0xbf, 0xe5, 0xc0, 0xc9,
        0x75, 0x98, 0xa2, 0xbd, 0x25, 0x55, 0xd1, 0xaa,
        0x8c, 0xb0, 0x8e, 0x48, 0x59, 0x0d, 0xbb, 0x3d,
        0xa7, 0xb0, 0x8b, 0x10, 0x56, 0x82, 0x88, 0x38,
        0xc5, 0xf6, 0x1e, 0x63, 0x93, 0xba, 0x7a, 0x0a,
        0xbc, 0xc9, 0xf6, 0x62
    };
#endif /* WOLFSSL_AES_256 */

    const uint8_t t1[] =
    {
        0x76, 0xfc, 0x6e, 0xce, 0x0f, 0x4e, 0x17, 0x68,
        0xcd, 0xdf, 0x88, 0x53, 0xbb, 0x2d, 0x55, 0x1b
    };

    /* FIPS, QAT and STM32F2/4 HW Crypto only support 12-uint8_t IV */
#if !defined(HAVE_FIPS) && \
        !defined(STM32_CRYPTO) && !defined(WOLFSSL_PIC32MZ_CRYPT) && \
        !defined(FREESCALE_LTC) && !defined(FREESCALE_MMCAU) && \
        !defined(WOLFSSL_XILINX_CRYPT)

    #define ENABLE_NON_12BYTE_IV_TEST
#ifdef WOLFSSL_AES_192
    /* Test Case 12, uses same plaintext and AAD data. */
    const uint8_t k2[] =
    {
        0xfe, 0xff, 0xe9, 0x92, 0x86, 0x65, 0x73, 0x1c,
        0x6d, 0x6a, 0x8f, 0x94, 0x67, 0x30, 0x83, 0x08,
        0xfe, 0xff, 0xe9, 0x92, 0x86, 0x65, 0x73, 0x1c
    };

    const uint8_t iv2[] =
    {
        0x93, 0x13, 0x22, 0x5d, 0xf8, 0x84, 0x06, 0xe5,
        0x55, 0x90, 0x9c, 0x5a, 0xff, 0x52, 0x69, 0xaa,
        0x6a, 0x7a, 0x95, 0x38, 0x53, 0x4f, 0x7d, 0xa1,
        0xe4, 0xc3, 0x03, 0xd2, 0xa3, 0x18, 0xa7, 0x28,
        0xc3, 0xc0, 0xc9, 0x51, 0x56, 0x80, 0x95, 0x39,
        0xfc, 0xf0, 0xe2, 0x42, 0x9a, 0x6b, 0x52, 0x54,
        0x16, 0xae, 0xdb, 0xf5, 0xa0, 0xde, 0x6a, 0x57,
        0xa6, 0x37, 0xb3, 0x9b
    };

    const uint8_t c2[] =
    {
        0xd2, 0x7e, 0x88, 0x68, 0x1c, 0xe3, 0x24, 0x3c,
        0x48, 0x30, 0x16, 0x5a, 0x8f, 0xdc, 0xf9, 0xff,
        0x1d, 0xe9, 0xa1, 0xd8, 0xe6, 0xb4, 0x47, 0xef,
        0x6e, 0xf7, 0xb7, 0x98, 0x28, 0x66, 0x6e, 0x45,
        0x81, 0xe7, 0x90, 0x12, 0xaf, 0x34, 0xdd, 0xd9,
        0xe2, 0xf0, 0x37, 0x58, 0x9b, 0x29, 0x2d, 0xb3,
        0xe6, 0x7c, 0x03, 0x67, 0x45, 0xfa, 0x22, 0xe7,
        0xe9, 0xb7, 0x37, 0x3b
    };

    const uint8_t t2[] =
    {
        0xdc, 0xf5, 0x66, 0xff, 0x29, 0x1c, 0x25, 0xbb,
        0xb8, 0x56, 0x8f, 0xc3, 0xd3, 0x76, 0xa6, 0xd9
    };
#endif /* WOLFSSL_AES_192 */
#ifdef WOLFSSL_AES_128
    /* The following is an interesting test case from the example
     * FIPS test vectors for AES-GCM. IVlen = 1 uint8_t */
    const uint8_t p3[] =
    {
        0x57, 0xce, 0x45, 0x1f, 0xa5, 0xe2, 0x35, 0xa5,
        0x8e, 0x1a, 0xa2, 0x3b, 0x77, 0xcb, 0xaf, 0xe2
    };

    const uint8_t k3[] =
    {
        0xbb, 0x01, 0xd7, 0x03, 0x81, 0x1c, 0x10, 0x1a,
        0x35, 0xe0, 0xff, 0xd2, 0x91, 0xba, 0xf2, 0x4b
    };

    const uint8_t iv3[] =
    {
        0xca
    };

    const uint8_t c3[] =
    {
        0x6b, 0x5f, 0xb3, 0x9d, 0xc1, 0xc5, 0x7a, 0x4f,
        0xf3, 0x51, 0x4d, 0xc2, 0xd5, 0xf0, 0xd0, 0x07
    };

    const uint8_t a3[] =
    {
        0x40, 0xfc, 0xdc, 0xd7, 0x4a, 0xd7, 0x8b, 0xf1,
        0x3e, 0x7c, 0x60, 0x55, 0x50, 0x51, 0xdd, 0x54
    };

    const uint8_t t3[] =
    {
        0x06, 0x90, 0xed, 0x01, 0x34, 0xdd, 0xc6, 0x95,
        0x31, 0x2e, 0x2a, 0xf9, 0x57, 0x7a, 0x1e, 0xa6
    };
#endif /* WOLFSSL_AES_128 */
#ifdef WOLFSSL_AES_256
    int ivlen;
#endif
#endif

    uint8_t resultT[sizeof(t1)];
    uint8_t resultP[sizeof(p)];
    uint8_t resultC[sizeof(p)];
    int  result;
#ifdef WOLFSSL_AES_256
    int  alen, plen;
#endif

#if !defined(BENCH_EMBEDDED)
    #ifndef BENCH_AESGCM_LARGE
        #define BENCH_AESGCM_LARGE 1024
    #endif
    uint8_t large_input[BENCH_AESGCM_LARGE];
    uint8_t large_output[BENCH_AESGCM_LARGE];
    uint8_t large_outdec[BENCH_AESGCM_LARGE];

    memset(large_input, 0, sizeof(large_input));
    memset(large_output, 0, sizeof(large_output));
    memset(large_outdec, 0, sizeof(large_outdec));
#endif

    memset(resultT, 0, sizeof(resultT));
    memset(resultC, 0, sizeof(resultC));
    memset(resultP, 0, sizeof(resultP));

#ifdef WOLFSSL_AES_256
    result = CRYPT_AES_GCM_SetKey(&enc, k1, sizeof(k1));
    if (result != 0)
        return -5701;

    /* AES-GCM encrypt and decrypt both use AES encrypt internally */
    result = CRYPT_AES_GCM_Encrypt(&enc, resultC, p, sizeof(p), iv1, sizeof(iv1),
                                        resultT, sizeof(resultT), a, sizeof(a));
    if (result != 0)
        return -5702;
    if (memcmp(c1, resultC, sizeof(resultC)))
        return -5703;
    if (memcmp(t1, resultT, sizeof(resultT)))
        return -5704;

#ifdef HAVE_AES_DECRYPT
    result = CRYPT_AES_GCM_Decrypt(&enc, resultP, resultC, sizeof(resultC),
                      iv1, sizeof(iv1), resultT, sizeof(resultT), a, sizeof(a));
    if (result != 0)
        return -5705;
    if (memcmp(p, resultP, sizeof(resultP)))
        return -5706;
#endif /* HAVE_AES_DECRYPT */

    /* Large buffer test */
#ifdef BENCH_AESGCM_LARGE
    /* setup test buffer */
    for (alen=0; alen<BENCH_AESGCM_LARGE; alen++)
        large_input[alen] = (uint8_t)alen;

    /* AES-GCM encrypt and decrypt both use AES encrypt internally */
    result = CRYPT_AES_GCM_Encrypt(&enc, large_output, large_input,
                              BENCH_AESGCM_LARGE, iv1, sizeof(iv1),
                              resultT, sizeof(resultT), a, sizeof(a));
    if (result != 0)
        return -5707;

#ifdef HAVE_AES_DECRYPT
    result = CRYPT_AES_GCM_Decrypt(&enc, large_outdec, large_output,
                              BENCH_AESGCM_LARGE, iv1, sizeof(iv1), resultT,
                              sizeof(resultT), a, sizeof(a));
    if (result != 0)
        return -5708;
    if (memcmp(large_input, large_outdec, BENCH_AESGCM_LARGE))
        return -5709;
#endif /* HAVE_AES_DECRYPT */
#endif /* BENCH_AESGCM_LARGE */
#if defined(ENABLE_NON_12BYTE_IV_TEST) && defined(WOLFSSL_AES_256)
    /* Variable IV length test */
    for (ivlen=0; ivlen<(int)sizeof(k1); ivlen++) {
         /* AES-GCM encrypt and decrypt both use AES encrypt internally */
         result = CRYPT_AES_GCM_Encrypt(&enc, resultC, p, sizeof(p), k1,
                         (word32)ivlen, resultT, sizeof(resultT), a, sizeof(a));
        if (result != 0)
            return -5710;
#ifdef HAVE_AES_DECRYPT
        result = CRYPT_AES_GCM_Decrypt(&enc, resultP, resultC, sizeof(resultC), k1,
                         (word32)ivlen, resultT, sizeof(resultT), a, sizeof(a));
        if (result != 0)
            return -5711;
#endif /* HAVE_AES_DECRYPT */
    }
#endif

    /* Variable authenticated data length test */
    for (alen=0; alen<(int)sizeof(p); alen++) {
         /* AES-GCM encrypt and decrypt both use AES encrypt internally */
         result = CRYPT_AES_GCM_Encrypt(&enc, resultC, p, sizeof(p), iv1,
                        sizeof(iv1), resultT, sizeof(resultT), p, (word32)alen);
        if (result != 0)
            return -5712;
#ifdef HAVE_AES_DECRYPT
        result = CRYPT_AES_GCM_Decrypt(&enc, resultP, resultC, sizeof(resultC), iv1,
                        sizeof(iv1), resultT, sizeof(resultT), p, (word32)alen);
        if (result != 0)
            return -5713;
#endif /* HAVE_AES_DECRYPT */
    }

#ifdef BENCH_AESGCM_LARGE
    /* Variable plain text length test */
    for (plen=1; plen<BENCH_AESGCM_LARGE; plen++) {
        /* AES-GCM encrypt and decrypt both use AES encrypt internally */
        result = CRYPT_AES_GCM_Encrypt(&enc, large_output, large_input,
                                  plen, iv1, sizeof(iv1), resultT,
                                  sizeof(resultT), a, sizeof(a));
        if (result != 0)
            return -5714;

#ifdef HAVE_AES_DECRYPT
        result = CRYPT_AES_GCM_Decrypt(&enc, large_outdec, large_output,
                                  plen, iv1, sizeof(iv1), resultT,
                                  sizeof(resultT), a, sizeof(a));
        if (result != 0)
            return -5715;
#endif /* HAVE_AES_DECRYPT */
    }
#else
    /* Variable plain text length test */
    for (plen=1; plen<(int)sizeof(p); plen++) {
         /* AES-GCM encrypt and decrypt both use AES encrypt internally */
         result = CRYPT_AES_GCM_Encrypt(&enc, resultC, p, (word32)plen, iv1,
                           sizeof(iv1), resultT, sizeof(resultT), a, sizeof(a));
        if (result != 0)
            return -5716;
#ifdef HAVE_AES_DECRYPT
        result = CRYPT_AES_GCM_Decrypt(&enc, resultP, resultC, (word32)plen, iv1,
                           sizeof(iv1), resultT, sizeof(resultT), a, sizeof(a));
        if (result != 0)
            return -5717;
#endif /* HAVE_AES_DECRYPT */
    }
#endif /* BENCH_AESGCM_LARGE */
#endif /* WOLFSSL_AES_256 */

    /* test with IV != 12 uint8_ts */
#ifdef ENABLE_NON_12BYTE_IV_TEST
    memset(resultT, 0, sizeof(resultT));
    memset(resultC, 0, sizeof(resultC));
    memset(resultP, 0, sizeof(resultP));

#ifdef WOLFSSL_AES_192
    CRYPT_AES_GCM_SetKey(&enc, k2, sizeof(k2));
    /* AES-GCM encrypt and decrypt both use AES encrypt internally */
    result = CRYPT_AES_GCM_Encrypt(&enc, resultC, p, sizeof(p), iv2, sizeof(iv2),
                                        resultT, sizeof(resultT), a, sizeof(a));
    if (result != 0)
        return -5718;
    if (memcmp(c2, resultC, sizeof(resultC)))
        return -5719;
    if (memcmp(t2, resultT, sizeof(resultT)))
        return -5720;

#ifdef HAVE_AES_DECRYPT
    result = CRYPT_AES_GCM_Decrypt(&enc, resultP, resultC, sizeof(resultC),
                      iv2, sizeof(iv2), resultT, sizeof(resultT), a, sizeof(a));
    if (result != 0)
        return -5721;
    if (memcmp(p, resultP, sizeof(resultP)))
        return -5722;
#endif /* HAVE_AES_DECRYPT */

    memset(resultT, 0, sizeof(resultT));
    memset(resultC, 0, sizeof(resultC));
    memset(resultP, 0, sizeof(resultP));
#endif /* WOLFSSL_AES_192 */
#ifdef WOLFSSL_AES_128
    CRYPT_AES_GCM_SetKey(&enc, k3, sizeof(k3));
    /* AES-GCM encrypt and decrypt both use AES encrypt internally */
    result = CRYPT_AES_GCM_Encrypt(&enc, resultC, p3, sizeof(p3), iv3, sizeof(iv3),
                                        resultT, sizeof(t3), a3, sizeof(a3));
    if (result != 0)
        return -5723;
    if (memcmp(c3, resultC, sizeof(c3)))
        return -5724;
    if (memcmp(t3, resultT, sizeof(t3)))
        return -5725;

#ifdef HAVE_AES_DECRYPT
    result = CRYPT_AES_GCM_Decrypt(&enc, resultP, resultC, sizeof(c3),
                      iv3, sizeof(iv3), resultT, sizeof(t3), a3, sizeof(a3));
    if (result != 0)
        return -5726;
    if (memcmp(p3, resultP, sizeof(p3)))
        return -5727;
#endif /* HAVE_AES_DECRYPT */
#endif /* WOLFSSL_AES_128 */
#endif /* ENABLE_NON_12BYTE_IV_TEST */

#ifdef WOLFSSL_AES_256
    memset(resultT, 0, sizeof(resultT));
    memset(resultC, 0, sizeof(resultC));
    memset(resultP, 0, sizeof(resultP));

    CRYPT_AES_GCM_SetKey(&enc, k1, sizeof(k1));
    /* AES-GCM encrypt and decrypt both use AES encrypt internally */
    result = CRYPT_AES_GCM_Encrypt(&enc, resultC, p, sizeof(p), iv1, sizeof(iv1),
                                resultT + 1, sizeof(resultT) - 1, a, sizeof(a));
    if (result != 0)
        return -5728;
    if (memcmp(c1, resultC, sizeof(resultC)))
        return -5729;
    if (memcmp(t1, resultT + 1, sizeof(resultT) - 1))
        return -5730;

#ifdef HAVE_AES_DECRYPT
    result = CRYPT_AES_GCM_Decrypt(&enc, resultP, resultC, sizeof(resultC),
              iv1, sizeof(iv1), resultT + 1, sizeof(resultT) - 1, a, sizeof(a));
    if (result != 0)
        return -5731;
    if (memcmp(p, resultP, sizeof(resultP)))
        return -5732;
#endif /* HAVE_AES_DECRYPT */
#endif /* WOLFSSL_AES_256 */


    return 0;
}



#endif

#ifdef HAVE_LIBZ

const uint8_t sample_text[] =
    "Biodiesel cupidatat marfa, cliche aute put a bird on it incididunt elit\n"
    "polaroid. Sunt tattooed bespoke reprehenderit. Sint twee organic id\n"
    "marfa. Commodo veniam ad esse gastropub. 3 wolf moon sartorial vero,\n"
    "plaid delectus biodiesel squid +1 vice. Post-ironic keffiyeh leggings\n"
    "selfies cray fap hoodie, forage anim. Carles cupidatat shoreditch, VHS\n"
    "small batch meggings kogi dolore food truck bespoke gastropub.\n"
    "\n"
    "Terry richardson adipisicing actually typewriter tumblr, twee whatever\n"
    "four loko you probably haven't heard of them high life. Messenger bag\n"
    "whatever tattooed deep v mlkshk. Brooklyn pinterest assumenda chillwave\n"
    "et, banksy ullamco messenger bag umami pariatur direct trade forage.\n"
    "Typewriter culpa try-hard, pariatur sint brooklyn meggings. Gentrify\n"
    "food truck next level, tousled irony non semiotics PBR ethical anim cred\n"
    "readymade. Mumblecore brunch lomo odd future, portland organic terry\n"
    "richardson elit leggings adipisicing ennui raw denim banjo hella. Godard\n"
    "mixtape polaroid, pork belly readymade organic cray typewriter helvetica\n"
    "four loko whatever street art yr farm-to-table.\n"
    "\n"
    "Vinyl keytar vice tofu. Locavore you probably haven't heard of them pug\n"
    "pickled, hella tonx labore truffaut DIY mlkshk elit cosby sweater sint\n"
    "et mumblecore. Elit swag semiotics, reprehenderit DIY sartorial nisi ugh\n"
    "nesciunt pug pork belly wayfarers selfies delectus. Ethical hoodie\n"
    "seitan fingerstache kale chips. Terry richardson artisan williamsburg,\n"
    "eiusmod fanny pack irony tonx ennui lo-fi incididunt tofu YOLO\n"
    "readymade. 8-bit sed ethnic beard officia. Pour-over iphone DIY butcher,\n"
    "ethnic art party qui letterpress nisi proident jean shorts mlkshk\n"
    "locavore.\n"
    "\n"
    "Narwhal flexitarian letterpress, do gluten-free voluptate next level\n"
    "banh mi tonx incididunt carles DIY. Odd future nulla 8-bit beard ut\n"
    "cillum pickled velit, YOLO officia you probably haven't heard of them\n"
    "trust fund gastropub. Nisi adipisicing tattooed, Austin mlkshk 90's\n"
    "small batch american apparel. Put a bird on it cosby sweater before they\n"
    "sold out pork belly kogi hella. Street art mollit sustainable polaroid,\n"
    "DIY ethnic ea pug beard dreamcatcher cosby sweater magna scenester nisi.\n"
    "Sed pork belly skateboard mollit, labore proident eiusmod. Sriracha\n"
    "excepteur cosby sweater, anim deserunt laborum eu aliquip ethical et\n"
    "neutra PBR selvage.\n"
    "\n"
    "Raw denim pork belly truffaut, irony plaid sustainable put a bird on it\n"
    "next level jean shorts exercitation. Hashtag keytar whatever, nihil\n"
    "authentic aliquip disrupt laborum. Tattooed selfies deserunt trust fund\n"
    "wayfarers. 3 wolf moon synth church-key sartorial, gastropub leggings\n"
    "tattooed. Labore high life commodo, meggings raw denim fingerstache pug\n"
    "trust fund leggings seitan forage. Nostrud ullamco duis, reprehenderit\n"
    "incididunt flannel sustainable helvetica pork belly pug banksy you\n"
    "probably haven't heard of them nesciunt farm-to-table. Disrupt nostrud\n"
    "mollit magna, sriracha sartorial helvetica.\n"
    "\n"
    "Nulla kogi reprehenderit, skateboard sustainable duis adipisicing viral\n"
    "ad fanny pack salvia. Fanny pack trust fund you probably haven't heard\n"
    "of them YOLO vice nihil. Keffiyeh cray lo-fi pinterest cardigan aliqua,\n"
    "reprehenderit aute. Culpa tousled williamsburg, marfa lomo actually anim\n"
    "skateboard. Iphone aliqua ugh, semiotics pariatur vero readymade\n"
    "organic. Marfa squid nulla, in laborum disrupt laboris irure gastropub.\n"
    "Veniam sunt food truck leggings, sint vinyl fap.\n"
    "\n"
    "Hella dolore pork belly, truffaut carles you probably haven't heard of\n"
    "them PBR helvetica in sapiente. Fashion axe ugh bushwick american\n"
    "apparel. Fingerstache sed iphone, jean shorts blue bottle nisi bushwick\n"
    "flexitarian officia veniam plaid bespoke fap YOLO lo-fi. Blog\n"
    "letterpress mumblecore, food truck id cray brooklyn cillum ad sed.\n"
    "Assumenda chambray wayfarers vinyl mixtape sustainable. VHS vinyl\n"
    "delectus, culpa williamsburg polaroid cliche swag church-key synth kogi\n"
    "magna pop-up literally. Swag thundercats ennui shoreditch vegan\n"
    "pitchfork neutra truffaut etsy, sed single-origin coffee craft beer.\n"
    "\n"
    "Odio letterpress brooklyn elit. Nulla single-origin coffee in occaecat\n"
    "meggings. Irony meggings 8-bit, chillwave lo-fi adipisicing cred\n"
    "dreamcatcher veniam. Put a bird on it irony umami, trust fund bushwick\n"
    "locavore kale chips. Sriracha swag thundercats, chillwave disrupt\n"
    "tousled beard mollit mustache leggings portland next level. Nihil esse\n"
    "est, skateboard art party etsy thundercats sed dreamcatcher ut iphone\n"
    "swag consectetur et. Irure skateboard banjo, nulla deserunt messenger\n"
    "bag dolor terry richardson sapiente.\n";


void compress_test(void)
{
    int ret = 0;
    word32 dSz = sizeof(sample_text);
    word32 cSz = (dSz + (word32)(dSz * 0.001) + 12);
    uint8_t *c = NULL;
    uint8_t *d = NULL;
    int numSubTests = 4;
    
    c = calloc(cSz, sizeof(uint8_t));
    d = calloc(dSz, sizeof(uint8_t));
    uint32_t hashStart;
    uint32_t hashStop;

    hashStart = APP_getTicks();
    appData.compress_test_result = numSubTests;
    
    if (c != NULL && d != NULL)
    {
        appData.compress_test_result--;
    }    
    if ((appData.compress_test_result == numSubTests-1) && 
        (ret = wc_Compress(c, cSz, sample_text, dSz, 0)) >= 0)
    {
        appData.compress_test_result--;
    }    
    if (ret > 0) {
        cSz = (word32)ret;
        ret = 0;
    }

    if ((appData.compress_test_result == numSubTests-2) && 
         wc_DeCompress(d, dSz, c, cSz) == (int)dSz)
    {
        appData.compress_test_result--;
    }    
    if ((appData.compress_test_result == numSubTests-3) && 
         !(memcmp(d, sample_text, dSz)))
    {
        appData.compress_test_result--;
    }
    
    if (c) free(c);
    if (d) free(d);
    hashStop = APP_getTicks();
    appData.compress_timing = hashStop - hashStart;
}

#endif /* HAVE_LIBZ */

#ifndef NO_DES3
void des_test(void)
{
    const uint8_t exp_pt[] = { /* "now is the time for all " w/o trailing 0 */
        0x6e,0x6f,0x77,0x20,0x69,0x73,0x20,0x74,
        0x68,0x65,0x20,0x74,0x69,0x6d,0x65,0x20,
        0x66,0x6f,0x72,0x20,0x61,0x6c,0x6c,0x20
    };

    uint8_t gen_pt[24];
    uint8_t gen_ct[24];

    Des enc;
    Des dec;

    const uint8_t key[] =
    {
        0x01,0x23,0x45,0x67,0x89,0xab,0xcd,0xef
    };

    const uint8_t iv[] =
    {
        0x12,0x34,0x56,0x78,0x90,0xab,0xcd,0xef
    };

    const uint8_t exp_ct[] =
    {
        0x8b,0x7c,0x52,0xb0,0x01,0x2b,0x6c,0xb8,
        0x4f,0x0f,0xeb,0xf3,0xfb,0x5f,0x86,0x73,
        0x15,0x85,0xb3,0x22,0x4b,0x86,0x2b,0x4b
    };

    uint32_t hashStart;
    uint32_t hashStop;
    int numSubTests = 2;
    
    /* The above const allocates in RAM, but does not flush out of cache. Copy
       it back out so it is in physical memory. */
#if defined(WOLFSSL_MICROCHIP_PIC32MZ)
 //   SYS_DEVCON_DataCacheFlush();
#endif


    hashStart = APP_getTicks();
    appData.des_test_result = numSubTests;

    wc_Des_SetKey(&enc, key, iv, DES_ENCRYPTION);
    wc_Des_CbcEncrypt(&enc, gen_ct, exp_pt, sizeof(exp_pt));
    wc_Des_SetKey(&dec, key, iv, DES_DECRYPTION);
    wc_Des_CbcDecrypt(&dec, gen_pt, exp_ct, sizeof(exp_ct));

    if (!(memcmp(gen_pt, exp_pt, sizeof(gen_pt))))
        appData.des_test_result--;
    
    if (!(memcmp(gen_ct, exp_ct, sizeof(gen_ct))))
        appData.des_test_result--;
    
    hashStop = APP_getTicks();
    appData.des_timing = hashStop - hashStart;
}
#endif /* !NO_DES3 */


#ifndef NO_DES3
void des3_test(void)
{
    const uint8_t vector[] = { /* "Now is the time for all " w/o trailing 0 */
        0x4e,0x6f,0x77,0x20,0x69,0x73,0x20,0x74,
        0x68,0x65,0x20,0x74,0x69,0x6d,0x65,0x20,
        0x66,0x6f,0x72,0x20,0x61,0x6c,0x6c,0x20
    };

    uint8_t plain[24];
    uint8_t cipher[24];

    CRYPT_TDES_CTX enc;
    CRYPT_TDES_CTX dec;

    const uint8_t key3[] =
    {
        0x01,0x23,0x45,0x67,0x89,0xab,0xcd,0xef,
        0xfe,0xde,0xba,0x98,0x76,0x54,0x32,0x10,
        0x89,0xab,0xcd,0xef,0x01,0x23,0x45,0x67
    };
    const uint8_t iv3[] =
    {
        0x12,0x34,0x56,0x78,0x90,0xab,0xcd,0xef,
        0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,
        0x11,0x21,0x31,0x41,0x51,0x61,0x71,0x81

    };

    const uint8_t verify3[] =
    {
        0x43,0xa0,0x29,0x7e,0xd1,0x84,0xf8,0x0e,
        0x89,0x64,0x84,0x32,0x12,0xd5,0x08,0x98,
        0x18,0x94,0x15,0x74,0x87,0x12,0x7d,0xb0
    };
    
    int numSubTests = 2;
    uint32_t hashStart;
    uint32_t hashStop;
    
    appData.des3_test_result = numSubTests;
    
    hashStart = APP_getTicks();
    /* The above const allocates in RAM, but does not flush out of cache. Copy
       it back out so it is in physical memory. */
#if defined(HW_CRYPTO)
    SYS_DEVCON_DataCacheFlush();
#endif
    CRYPT_TDES_KeySet(&enc, key3, iv3, DES_ENCRYPTION);
    CRYPT_TDES_KeySet(&dec, key3, iv3, DES_DECRYPTION);
    CRYPT_TDES_CBC_Encrypt(&enc, cipher, vector, sizeof(vector));
    CRYPT_TDES_CBC_Decrypt(&dec, plain, verify3, sizeof(verify3));

    if (!(memcmp(plain, vector, sizeof(plain))))
        appData.des3_test_result--;

    if (!(memcmp(cipher, verify3, sizeof(cipher))))
        appData.des3_test_result--;

    hashStop = APP_getTicks();
    appData.des3_timing = hashStop - hashStart;
}
#endif /* !NO_DES3 */

#ifndef NO_RSA

#if !defined(USE_CERT_BUFFERS_1024) && !defined(USE_CERT_BUFFERS_2048)
    #ifdef FREESCALE_MQX
        static const char* clientKey  = "a:\\certs\\client-key.der";
        static const char* clientCert = "a:\\certs\\client-cert.der";
        #ifdef WOLFSSL_CERT_GEN
            static const char* caKeyFile  = "a:\\certs\\ca-key.der";
            static const char* caCertFile = "a:\\certs\\ca-cert.pem";
            #ifdef HAVE_ECC
                static const char* eccCaKeyFile  = "a:\\certs\\ecc-key.der";
                static const char* eccCaCertFile = "a:\\certs\\server-ecc.pem";
            #endif
        #endif
    #elif defined(WOLFSSL_MKD_SHELL)
        static char* clientKey = "certs/client-key.der";
        static char* clientCert = "certs/client-cert.der";
        void set_clientKey(char *key) {  clientKey = key ; }
        void set_clientCert(char *cert) {  clientCert = cert ; }
        #ifdef WOLFSSL_CERT_GEN
            static char* caKeyFile  = "certs/ca-key.der";
            static char* caCertFile = "certs/ca-cert.pem";
            void set_caKeyFile (char * key)  { caKeyFile   = key ; }
            void set_caCertFile(char * cert) { caCertFile = cert ; }
            #ifdef HAVE_ECC
                static const char* eccCaKeyFile  = "certs/ecc-key.der";
                static const char* eccCaCertFile = "certs/server-ecc.pem";
                void set_eccCaKeyFile (char * key)  { eccCaKeyFile  = key ; }
                void set_eccCaCertFile(char * cert) { eccCaCertFile = cert ; }
            #endif
        #endif
    #else
        static const char* clientKey  = "./certs/client-key.der";
        static const char* clientCert = "./certs/client-cert.der";
        #ifdef WOLFSSL_CERT_GEN
            static const char* caKeyFile  = "./certs/ca-key.der";
            static const char* caCertFile = "./certs/ca-cert.pem";
            #ifdef HAVE_ECC
                static const char* eccCaKeyFile  = "./certs/ecc-key.der";
                static const char* eccCaCertFile = "./certs/server-ecc.pem";
            #endif
        #endif
    #endif
#endif

void rsa_test(void)
{

    uint8_t*   tmp;
    size_t  uint8_ts;
    RsaKey  key;
    RNG     rng;

    word32 idx = 0;
    int    ret;
    uint8_t   in[] = "Everyone gets Friday off.";
    word32 inLen = (word32)strlen((char*)in);
    uint8_t   out[256];
    uint8_t   plain[256];
#if !defined(USE_CERT_BUFFERS_1024) && !defined(USE_CERT_BUFFERS_2048)
    FILE*  file, * file2;
#endif
#ifdef WOLFSSL_TEST_CERT
    DecodedCert cert;
#endif
    
    appData.rsa_test_result = 9;
    uint32_t hashStart;
    uint32_t hashStop;
        
    hashStart = APP_getTicks();
    tmp = (uint8_t*)malloc(FOURK_BUF);
    if (tmp != NULL)
        appData.rsa_test_result--;

#ifdef USE_CERT_BUFFERS_1024
    XMEMCPY(tmp, client_key_der_1024, sizeof_client_key_der_1024);
    uint8_ts = sizeof_client_key_der_1024;
#elif defined(USE_CERT_BUFFERS_2048)
    XMEMCPY(tmp, client_key_der_2048, sizeof_client_key_der_2048);
    uint8_ts = sizeof_client_key_der_2048;
#else
    appData.rsa_test_result++;
    file = fopen(clientKey, "rb");
    if (file)
        appData.rsa_test_result--;
    
    uint8_ts = fread(tmp, 1, FOURK_BUF, file);
    fclose(file);
#endif /* USE_CERT_BUFFERS */

#ifdef HAVE_CAVIUM
    RsaInitCavium(&key, CAVIUM_DEV_ID);
#endif
    wc_InitRsaKey_ex(&key, 0, 0);
    ret = wc_RsaPrivateKeyDecode(tmp, &idx, &key, (word32)uint8_ts);
    if (ret == 0) appData.rsa_test_result--;

    ret = CRYPT_RNG_Initialize((CRYPT_RNG_CTX*)&rng);
    if (ret == 0) appData.rsa_test_result--;

    ret = wc_RsaPublicEncrypt(in, inLen, out, sizeof(out), &key, &rng);
    if (ret >= 0) appData.rsa_test_result--;

    ret = wc_RsaPrivateDecrypt(out, ret, plain, sizeof(plain), &key);
    if (ret >= 0) appData.rsa_test_result--;

    if (!(memcmp(plain, in, inLen))) appData.rsa_test_result--;

    ret = wc_RsaSSL_Sign(in, inLen, out, sizeof(out), &key, &rng);
    if (ret >= 0) appData.rsa_test_result--;

    memset(plain, 0, sizeof(plain));
    ret = wc_RsaSSL_Verify(out, ret, plain, sizeof(plain), &key);
    if (ret >= 0) appData.rsa_test_result--;

    if (!(memcmp(plain, in, ret))) appData.rsa_test_result--;

#if defined(WOLFSSL_MDK_ARM)
    #define sizeof(s) strlen((char *)(s))
#endif

#ifdef USE_CERT_BUFFERS_1024
    XMEMCPY(tmp, client_cert_der_1024, sizeof_client_cert_der_1024);
    uint8_ts = sizeof_client_cert_der_1024;
#elif defined(USE_CERT_BUFFERS_2048)
    XMEMCPY(tmp, client_cert_der_2048, sizeof_client_cert_der_2048);
    uint8_ts = sizeof_client_cert_der_2048;
#else
    appData.rsa_test_result++;
    file2 = fopen(clientCert, "rb");
    if (file2)
        appData.rsa_test_result--;

    uint8_ts = fread(tmp, 1, FOURK_BUF, file2);
    fclose(file2);
#endif

#ifdef sizeof
		#undef sizeof
#endif

#ifdef WOLFSSL_TEST_CERT
    appData.rsa_test_result++;
    InitDecodedCert(&cert, tmp, (word32)uint8_ts, 0);

    ret = ParseCert(&cert, CERT_TYPE, NO_VERIFY, 0);
    if (ret == 0) appData.rsa_test_result--;

    FreeDecodedCert(&cert);
#else
    (void)uint8_ts;
#endif


#ifdef WOLFSSL_KEY_GEN
    {
        uint8_t*  der;
        uint8_t*  pem;
        int    derSz = 0;
        int    pemSz = 0;
        RsaKey derIn;
        RsaKey genKey;
        FILE* keyFile;
        FILE* pemFile;

        appData.rsa_test_result += 8;
        InitRsaKey(&genKey, 0);
        ret = MakeRsaKey(&genKey, 1024, 65537, &rng);
        if (ret == 0)
            appData.rsa_test_result--;

        der = (uint8_t*)malloc(FOURK_BUF);
        if (der != NULL)
            appData.rsa_test_result--;
        pem = (uint8_t*)malloc(FOURK_BUF);
        if (pem != NULL)
            appData.rsa_test_result--;

        derSz = RsaKeyToDer(&genKey, der, FOURK_BUF);
        if (derSz >=0)
            appData.rsa_test_result--;

        keyFile = fopen("./key.der", "wb");
        if (keyFile)
            appData.rsa_test_result--;
        ret = (int)fwrite(der, derSz, 1, keyFile);
        fclose(keyFile);

        pemSz = DerToPem(der, derSz, pem, FOURK_BUF, PRIVATEKEY_TYPE);
        if (pemSz >= 0)
            appData.rsa_test_result--;

        pemFile = fopen("./key.pem", "wb");
        if (pemFile)
            appData.rsa_test_result--;
        ret = (int)fwrite(pem, pemSz, 1, pemFile);
        fclose(pemFile);

        InitRsaKey(&derIn, 0);
        idx = 0;
        ret = RsaPrivateKeyDecode(der, &idx, &derIn, derSz);
        if (ret == 0)
            appData.rsa_test_result--;

        FreeRsaKey(&derIn);
        FreeRsaKey(&genKey);
        free(pem);
        free(der);
    }
#endif /* WOLFSSL_KEY_GEN */


#ifdef WOLFSSL_CERT_GEN    /* self signed */
    {
        Cert        myCert;
        uint8_t*       derCert;
        uint8_t*       pem;
        FILE*       derFile;
        FILE*       pemFile;
        int         certSz;
        int         pemSz;
#ifdef WOLFSSL_TEST_CERT
        DecodedCert decode;
#endif
        appData.rsa_test_result += 16;
        
        derCert = (uint8_t*)malloc(FOURK_BUF);
        if (derCert != NULL)
            appData.rsa_test_result--;
        pem = (uint8_t*)malloc(FOURK_BUF);
        if (pem != NULL)
            appData.rsa_test_result--;

        InitCert(&myCert);

        strncpy(myCert.subject.country, "US", CTC_NAME_SIZE);
        strncpy(myCert.subject.state, "OR", CTC_NAME_SIZE);
        strncpy(myCert.subject.locality, "Portland", CTC_NAME_SIZE);
        strncpy(myCert.subject.org, "yaSSL", CTC_NAME_SIZE);
        strncpy(myCert.subject.unit, "Development", CTC_NAME_SIZE);
        strncpy(myCert.subject.commonName, "www.yassl.com", CTC_NAME_SIZE);
        strncpy(myCert.subject.email, "info@yassl.com", CTC_NAME_SIZE);
        myCert.isCA    = 1;
        myCert.sigType = CTC_SHA256wRSA;

        certSz = MakeSelfCert(&myCert, derCert, FOURK_BUF, &key, &rng);
        if (certSz >= 0)
            appData.rsa_test_result--;

#ifdef WOLFSSL_TEST_CERT
        appData.rsa_test_result++;
        InitDecodedCert(&decode, derCert, certSz, 0);
        ret = ParseCert(&decode, CERT_TYPE, NO_VERIFY, 0);
        if (ret == 0)
            appData.rsa_test_result--;
        FreeDecodedCert(&decode);
#endif
        derFile = fopen("./cert.der", "wb");
        if (derFile)
            appData.rsa_test_result--;
        ret = (int)fwrite(derCert, certSz, 1, derFile);
        fclose(derFile);

        pemSz = DerToPem(derCert, certSz, pem, FOURK_BUF, CERT_TYPE);
        if (pemSz >= 0)
            appData.rsa_test_result--;

        pemFile = fopen("./cert.pem", "wb");
        if (pemFile)
            appData.rsa_test_result--;
        ret = (int)fwrite(pem, pemSz, 1, pemFile);
        fclose(pemFile);
        free(pem);
        free(derCert);
    }
    /* CA style */
    {
        RsaKey      caKey;
        Cert        myCert;
        uint8_t*       derCert;
        uint8_t*       pem;
        FILE*       derFile;
        FILE*       pemFile;
        int         certSz;
        int         pemSz;
        size_t      uint8_ts3;
        word32      idx3 = 0;
        FILE*       file3 ;
#ifdef WOLFSSL_TEST_CERT
        DecodedCert decode;
#endif

        derCert = (uint8_t*)malloc(FOURK_BUF);
        if (derCert != NULL)
            appData.rsa_test_result--;
        pem = (uint8_t*)malloc(FOURK_BUF);
        if (pem != NULL)
            appData.rsa_test_result--;

        file3 = fopen(caKeyFile, "rb");

        if (file3)
            appData.rsa_test_result--;

        uint8_ts3 = fread(tmp, 1, FOURK_BUF, file3);
        fclose(file3);

        InitRsaKey(&caKey, 0);
        ret = RsaPrivateKeyDecode(tmp, &idx3, &caKey, (word32)uint8_ts3);
        if (ret == 0) appData.rsa_test_result--;

        InitCert(&myCert);

        strncpy(myCert.subject.country, "US", CTC_NAME_SIZE);
        strncpy(myCert.subject.state, "OR", CTC_NAME_SIZE);
        strncpy(myCert.subject.locality, "Portland", CTC_NAME_SIZE);
        strncpy(myCert.subject.org, "yaSSL", CTC_NAME_SIZE);
        strncpy(myCert.subject.unit, "Development", CTC_NAME_SIZE);
        strncpy(myCert.subject.commonName, "www.yassl.com", CTC_NAME_SIZE);
        strncpy(myCert.subject.email, "info@yassl.com", CTC_NAME_SIZE);

        ret = SetIssuer(&myCert, caCertFile);
        if (ret >= 0)
            appData.rsa_test_result--;

        certSz = MakeCert(&myCert, derCert, FOURK_BUF, &key, NULL, &rng);
        if (certSz >= 0)
            appData.rsa_test_result--;

        certSz = SignCert(myCert.bodySz, myCert.sigType, derCert, FOURK_BUF,
                          &caKey, NULL, &rng);
        if (certSz >= 0)
            appData.rsa_test_result--;


#ifdef WOLFSSL_TEST_CERT
        appData.rsa_test_result++;
        InitDecodedCert(&decode, derCert, certSz, 0);
        ret = ParseCert(&decode, CERT_TYPE, NO_VERIFY, 0);
        if (ret == 0)
            appData.rsa_test_result--;
        FreeDecodedCert(&decode);
#endif

        derFile = fopen("./othercert.der", "wb");
        if (derFile)
            appData.rsa_test_result--;
        ret = (int)fwrite(derCert, certSz, 1, derFile);
        fclose(derFile);

        pemSz = DerToPem(derCert, certSz, pem, FOURK_BUF, CERT_TYPE);
        if (pemSz >= 0)
            appData.rsa_test_result--;

        pemFile = fopen("./othercert.pem", "wb");
        if (pemFile)
            appData.rsa_test_result--;
        ret = (int)fwrite(pem, pemSz, 1, pemFile);
        fclose(pemFile);
        free(pem);
        free(derCert);
        FreeRsaKey(&caKey);
    }
#ifdef HAVE_ECC
    /* ECC CA style */
    {
        ecc_key     caKey;
        Cert        myCert;
        uint8_t*       derCert;
        uint8_t*       pem;
        FILE*       derFile;
        FILE*       pemFile;
        int         certSz;
        int         pemSz;
        size_t      uint8_ts3;
        word32      idx3 = 0;
        FILE*       file3 ;
#ifdef WOLFSSL_TEST_CERT
        DecodedCert decode;
#endif
        appData.rsa_test_result += 10;
        derCert = (uint8_t*)malloc(FOURK_BUF);
        if (derCert != NULL)
            appData.rsa_test_result--;
        pem = (uint8_t*)malloc(FOURK_BUF);
        if (pem != NULL)
            appData.rsa_test_result--;

        file3 = fopen(eccCaKeyFile, "rb");

        if (file3)
            appData.rsa_test_result--;

        uint8_ts3 = fread(tmp, 1, FOURK_BUF, file3);
        fclose(file3);

        ecc_init(&caKey);
        ret = EccPrivateKeyDecode(tmp, &idx3, &caKey, (word32)uint8_ts3);
        if (ret == 0) appData.rsa_test_result--;

        InitCert(&myCert);
        myCert.sigType = CTC_SHA256wECDSA;

        strncpy(myCert.subject.country, "US", CTC_NAME_SIZE);
        strncpy(myCert.subject.state, "OR", CTC_NAME_SIZE);
        strncpy(myCert.subject.locality, "Portland", CTC_NAME_SIZE);
        strncpy(myCert.subject.org, "wolfSSL", CTC_NAME_SIZE);
        strncpy(myCert.subject.unit, "Development", CTC_NAME_SIZE);
        strncpy(myCert.subject.commonName, "www.wolfssl.com", CTC_NAME_SIZE);
        strncpy(myCert.subject.email, "info@wolfssl.com", CTC_NAME_SIZE);

        ret = SetIssuer(&myCert, eccCaCertFile);
        if (ret >= 0)
            appData.rsa_test_result--;

        certSz = MakeCert(&myCert, derCert, FOURK_BUF, NULL, &caKey, &rng);
        if (certSz >= 0)
            appData.rsa_test_result--;

        certSz = SignCert(myCert.bodySz, myCert.sigType, derCert, FOURK_BUF,
                          NULL, &caKey, &rng);
        if (certSz >= 0)
            appData.rsa_test_result--;

#ifdef WOLFSSL_TEST_CERT
        appData.rsa_test_result++;
        InitDecodedCert(&decode, derCert, certSz, 0);
        ret = ParseCert(&decode, CERT_TYPE, NO_VERIFY, 0);
        if (ret == 0)
            appData.rsa_test_result--;
        FreeDecodedCert(&decode);
#endif

        derFile = fopen("./certecc.der", "wb");
        if (derFile)
            appData.rsa_test_result--;
        ret = (int)fwrite(derCert, certSz, 1, derFile);
        fclose(derFile);

        pemSz = DerToPem(derCert, certSz, pem, FOURK_BUF, CERT_TYPE);
        if (pemSz >= 0)
            appData.rsa_test_result--;

        pemFile = fopen("./certecc.pem", "wb");
        if (pemFile)
            appData.rsa_test_result--;
        ret = (int)fwrite(pem, pemSz, 1, pemFile);
        fclose(pemFile);
        free(pem);
        free(derCert);
        ecc_free(&caKey);
    }
#endif /* HAVE_ECC */
#ifdef HAVE_NTRU
    {
        RsaKey      caKey;
        Cert        myCert;
        uint8_t*       derCert;
        uint8_t*       pem;
        FILE*       derFile;
        FILE*       pemFile;
        FILE*       caFile;
        FILE*       ntruPrivFile;
        int         certSz;
        int         pemSz;
        size_t      uint8_ts;
        word32      idx = 0;
#ifdef WOLFSSL_TEST_CERT
        DecodedCert decode;
#endif
        appData.rsa_test_result += 14;
        derCert = (uint8_t*)malloc(FOURK_BUF);
        if (derCert != NULL)
            appData.rsa_test_result--;
        pem = (uint8_t*)malloc(FOURK_BUF);
        if (pem != NULL)
            appData.rsa_test_result--;

        uint8_t   public_key[557];          /* sized for EES401EP2 */
        word16 public_key_len;           /* no. of octets in public key */
        uint8_t   private_key[607];         /* sized for EES401EP2 */
        word16 private_key_len;          /* no. of octets in private key */
        DRBG_HANDLE drbg;
        static uint8_t const pers_str[] = {
                'C', 'y', 'a', 'S', 'S', 'L', ' ', 't', 'e', 's', 't'
        };
        word32 rc = crypto_drbg_instantiate(112, pers_str, sizeof(pers_str),
                                            GetEntropy, &drbg);
        if (rc == DRBG_OK)
            appData.rsa_test_result--;

        rc = crypto_ntru_encrypt_keygen(drbg, NTRU_EES401EP2, &public_key_len,
                                        NULL, &private_key_len, NULL);
        if (rc == NTRU_OK)
            appData.rsa_test_result--;

        rc = crypto_ntru_encrypt_keygen(drbg, NTRU_EES401EP2, &public_key_len,
                                     public_key, &private_key_len, private_key);
        crypto_drbg_uninstantiate(drbg);

        if (rc == NTRU_OK)
            appData.rsa_test_result--;

        caFile = fopen(caKeyFile, "rb");

        if (caFile)
            appData.rsa_test_result--;

        uint8_ts = fread(tmp, 1, FOURK_BUF, caFile);
        fclose(caFile);

        InitRsaKey(&caKey, 0);
        ret = RsaPrivateKeyDecode(tmp, &idx, &caKey, (word32)uint8_ts);
        if (ret == 0) appData.rsa_test_result--;

        InitCert(&myCert);

        strncpy(myCert.subject.country, "US", CTC_NAME_SIZE);
        strncpy(myCert.subject.state, "OR", CTC_NAME_SIZE);
        strncpy(myCert.subject.locality, "Portland", CTC_NAME_SIZE);
        strncpy(myCert.subject.org, "yaSSL", CTC_NAME_SIZE);
        strncpy(myCert.subject.unit, "Development", CTC_NAME_SIZE);
        strncpy(myCert.subject.commonName, "www.yassl.com", CTC_NAME_SIZE);
        strncpy(myCert.subject.email, "info@yassl.com", CTC_NAME_SIZE);

        ret = SetIssuer(&myCert, caCertFile);
        if (ret >= 0)
            appData.rsa_test_result--;

        certSz = MakeNtruCert(&myCert, derCert, FOURK_BUF, public_key,
                              public_key_len, &rng);
        if (certSz >= 0)
            appData.rsa_test_result--;

        certSz = SignCert(myCert.bodySz, myCert.sigType, derCert, FOURK_BUF,
                          &caKey, NULL, &rng);
        if (certSz >= 0)
            appData.rsa_test_result--;


#ifdef WOLFSSL_TEST_CERT
        appData.rsa_test_result++;
        InitDecodedCert(&decode, derCert, certSz, 0);
        ret = ParseCert(&decode, CERT_TYPE, NO_VERIFY, 0);
        if (ret == 0)
            appData.rsa_test_result--;
        FreeDecodedCert(&decode);
#endif
        derFile = fopen("./ntru-cert.der", "wb");
        if (derFile)
            appData.rsa_test_result--;
        ret = fwrite(derCert, certSz, 1, derFile);
        fclose(derFile);

        pemSz = DerToPem(derCert, certSz, pem, FOURK_BUF, CERT_TYPE);
        if (pemSz >= 0)
            appData.rsa_test_result--;

        pemFile = fopen("./ntru-cert.pem", "wb");
        if (pemFile)
            appData.rsa_test_result--;
        ret = fwrite(pem, pemSz, 1, pemFile);
        fclose(pemFile);

        ntruPrivFile = fopen("./ntru-key.raw", "wb");
        if (ntruPrivFile)
            appData.rsa_test_result--;
        ret = fwrite(private_key, private_key_len, 1, ntruPrivFile);
        fclose(ntruPrivFile);
        free(pem);
        free(derCert);
        FreeRsaKey(&caKey);
    }
#endif /* HAVE_NTRU */
#endif /* WOLFSSL_CERT_GEN */

    wc_FreeRsaKey(&key);
#ifdef HAVE_CAVIUM
    RsaFreeCavium(&key);
#endif
    free(tmp);

    hashStop = (uint32_t) APP_getTicks();
    appData.rsa_timing = hashStop - hashStart;
}
#endif /* !NO_RSA */

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

#ifdef WOLFSSL_HAVE_MCHP_BA414E_CRYPTO
#include "wolfssl/wolfcrypt/tfm.h"

const static char primTestPrime[] = "FFFFFFFF00000001000000000000000000000000FFFFFFFFFFFFFFFFFFFFFFFF";
const static char primTestA[] = "FFFFFFFF00000001000000000000000000000000FFFFFFFFFFFFFFFFFFFFFFFC";
const static char primTestB[] = "5AC635D8AA3A93E7B3EBBD55769886BC651D06B0CC53B0F63BCE3C3E27D2604B";
const static char primTestOrder[] = "FFFFFFFF00000000FFFFFFFFFFFFFFFFBCE6FAADA7179E84F3B9CAC2FC632551";
const static char primTestGx[] = "6B17D1F2E12C4247F8BCE6E563A440F277037D812DEB33A0F4A13945D898C296";
const static char primTestGy[] = "4FE342E2FE1A7F9B8EE7EB4A7C0F9E162BCE33576B315ECECBB6406837BF51F5";


const static char primTestModAdd[] = "5ac635d8aa3a93e7b3ebbd55769886bc651d06b0cc53b0f63bce3c3e27d26048"; //(A+B)%P
const static char primTestModSub[] = "a539ca2655c56c194c1442aa896779439ae2f95033ac4f09c431c3c1d82d9fb1"; //(A-B)%P
const static char primTestModMult[] = "efad5e740150444ae43cc7ff9c366bcad0a8ebef9b04ed1d4c954b458888df1d"; //(A*B)%P
const static char primTestModExp[] = "85582a98093647809f4dce8e4c9331a84ad2091f2f8cc98ecbaa1e2eb993f5a4"; //(A^B)%P

const static char primTestPx[] =  "282167aa6ba380c53a9c5230c0b53b1ebc456983cc05f0f2b869a75f7f232e91";
const static char primTestPy[] =  "cc8a545065e3a76c6731a0f4471a338442ef3cc3c978e787e0d5cdc907dd4e9c";
const static char primTestQx[] =  "05b8430eb7a99e24877ce69baf3dc580e309633d6b385f83ee1c3ec3591f1a53";
const static char primTestQy[] =  "93c06e805ddceb2fde50930dd7cfebb987c6ff9666af164eb5184d8e6662ed6a";
const static char primTestRx[] =  "4b5c21597658f4e3eddfb4b99f25b4d6540f32ff1fd5c530c60a794448610bc6";
const static char primTestNRy[] = "de3d92bdbbd47d935980ca6cf8988ab6630be6764c885ceb9793970f695217ee";
const static char primTestSx[] =  "ad68ea339d3db924f4ccee64bcc0609ed8258760dd85428bb3194f262dff4888";
const static char primTestMax[] = "ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff";

const static char primTestI[] =   "5564f045b2ea1e566cf1dd741f70d9be35d2df5b9a5502946ee03cf8dae27e1e";
const static char primTestJ[] =   "a906f61e4d3a5d4eb2965ff34cf917dd044445c878c17ca5d5b93786da9f83cf";
const static char primTestK[] =   "4234b4fb17aa435c52fbfdebe64039b43478200e54ff7b6e07b69cad74153c15";
const static char primTestOne[] = "0000000000000000000000000000000000000000000000000000000000000001";
const static char primTestTwo[] = "0000000000000000000000000000000000000000000000000000000000000002";

const static char primTestPDx[] = {0x57, 0xf6, 0x5d, 0x88, 0xbe, 0xe8, 0x1d, 0xc0, 0x0c, 0x7c, 0xc2, 0xe1, 0x48, 0xe7, 0x80, 0x5b, 
                                   0x2e, 0xb3, 0x22, 0x06, 0xac, 0x97, 0xe8, 0xe6, 0xfb, 0x12, 0x5c, 0x37, 0x91, 0x13, 0xae, 0x99};
const static char primTestPDy[] = {0xaa, 0x01, 0x10, 0xa3, 0xdf, 0x6d, 0x2e, 0x3f, 0x37, 0xfe, 0x84, 0xbe, 0x9f, 0xa3, 0x05, 0xec, 
                                   0xa4, 0xbe, 0x33, 0x9d, 0xcb, 0x5e, 0xcf, 0xc5, 0x8e, 0xf7, 0x50, 0xc5, 0xa6, 0xef, 0xc2, 0x84};


mp_int mpPrime, mpA, mpB, mpOrder, mpGx, mpGy, mpC, mpRes, mpResY;
mp_int mpPx, mpPy, mpQx, mpQy, mpRx, mpRy, mpNRy, mpSx, mpMax;
mp_int mpI, mpJ, mpK, mpOne, mp2;


void prim_test(void)
{
    DRV_HANDLE ba414Handle = DRV_BA414E_Open(DRV_BA414E_INDEX_0, DRV_IO_INTENT_READWRITE | DRV_IO_INTENT_BLOCKING);
    
    mp_clear(&mpPrime);
    mp_clear(&mpA);
    mp_clear(&mpB);
    mp_clear(&mpOrder);
    mp_clear(&mpGx);
    mp_clear(&mpGy);
    mp_clear(&mpC);
    mp_clear(&mpRes);
    mp_clear(&mpResY);
    mp_clear(&mpPx);
    mp_clear(&mpPy);
    mp_clear(&mpQx);
    mp_clear(&mpQy);
    mp_clear(&mpRx);
    mp_clear(&mpRy);
    mp_clear(&mpNRy);
    mp_clear(&mpSx);
    mp_clear(&mpMax);
    mp_clear(&mpI);
    mp_clear(&mpJ);
    mp_clear(&mpK);
    mp_clear(&mpOne);
    mp_clear(&mp2);
    
    mp_read_radix(&mpPrime, primTestPrime, 16);
    mp_read_radix(&mpA, primTestA, 16);
    mp_read_radix(&mpB, primTestB, 16);
    mp_read_radix(&mpOrder, primTestOrder, 16);
    mp_read_radix(&mpGx, primTestGx, 16);
    mp_read_radix(&mpGy, primTestGy, 16);
    mp_read_radix(&mpRes, primTestModAdd, 16);
    
    mp_read_radix(&mpPx, primTestPx, 16);
    mp_read_radix(&mpPy, primTestPy, 16);
    mp_read_radix(&mpQx, primTestQx, 16);
    mp_read_radix(&mpQy, primTestQy, 16);
    mp_read_radix(&mpRx, primTestRx, 16);
    mp_read_radix(&mpNRy, primTestNRy, 16);
    mp_read_radix(&mpSx, primTestSx, 16);
    mp_read_radix(&mpMax, primTestMax, 16);
    mp_read_radix(&mpI, primTestI, 16);
    mp_read_radix(&mpJ, primTestJ, 16);
    mp_read_radix(&mpK, primTestK, 16);
    mp_read_radix(&mpOne, primTestOne, 16);
    mp_read_radix(&mp2, primTestTwo, 16);
    
    appData.prim_test_result = 22;
    
    DRV_BA414E_OP_RESULT ret = DRV_BA414E_PRIM_ModAddition(ba414Handle, 
                                            DRV_BA414E_OPSZ_256, 
                                            (uint8_t*)&(mpC.dp), 
                                            (uint8_t*)&(mpPrime.dp), 
                                            (uint8_t*)&(mpA.dp), 
                                            (uint8_t*)&(mpB.dp), 
                                            0, 0);
    if (ret == DRV_BA414E_OP_SUCCESS)
    {
        appData.prim_test_result--;
    }
    if (memcmp(mpC.dp, mpRes.dp, 32) == 0)
    {
        appData.prim_test_result--;        
    }    
    mp_clear(&mpC);
    
    ret = DRV_BA414E_PRIM_ModSubtraction(ba414Handle, 
                                        DRV_BA414E_OPSZ_256, 
                                        (uint8_t*)&(mpC.dp), 
                                        (uint8_t*)&(mpMax.dp), 
                                        (uint8_t*)&(mpA.dp), 
                                        (uint8_t*)&(mpB.dp), 
                                        0, 0);
    mp_read_radix(&mpRes, primTestModSub, 16);
    if (ret == DRV_BA414E_OP_SUCCESS)
    {
        appData.prim_test_result--;
    }
    if (memcmp(mpC.dp, mpRes.dp, 32) == 0)
    {
        appData.prim_test_result--;        
    }    
    mp_clear(&mpC);

    
    ret = DRV_BA414E_PRIM_ModMultiplication(ba414Handle, 
                                            DRV_BA414E_OPSZ_256, 
                                            (uint8_t*)&(mpC.dp), 
                                            (uint8_t*)&(mpPrime.dp), 
                                            (uint8_t*)&(mpA.dp), 
                                            (uint8_t*)&(mpB.dp), 
                                            0, 0);
    mp_read_radix(&mpRes, primTestModMult, 16);
    if (ret == DRV_BA414E_OP_SUCCESS)
    {
        appData.prim_test_result--;
    }
    if (memcmp(mpC.dp, mpRes.dp, 32) == 0)
    {
        appData.prim_test_result--;        
    }    
    mp_clear(&mpC);

    DRV_BA414E_PRIM_ModExponentiation(ba414Handle, 
                                    DRV_BA414E_OPSZ_256, 
                                    (uint8_t*)&(mpC.dp), 
                                    (uint8_t*)&(mpPrime.dp), 
                                    (uint8_t*)&(mpA.dp), 
                                    (uint8_t*)&(mpB.dp), 
                                    0, 0);
    mp_read_radix(&mpRes, primTestModExp, 16);
    if (ret == DRV_BA414E_OP_SUCCESS)
    {
        appData.prim_test_result--;
    }
    if (memcmp(mpC.dp, mpRes.dp, 32) == 0)
    {
        appData.prim_test_result--;        
    }    
    mp_clear(&mpC);

    DRV_BA414E_ECC_DOMAIN eccDomain;
    eccDomain.keySize = 32;
    eccDomain.opSize = DRV_BA414E_OPSZ_256;
    eccDomain.primeField = (uint8_t*)&(mpPrime.dp);
    eccDomain.order = (uint8_t*)&(mpOrder.dp);
    eccDomain.generatorX = (uint8_t*)&(mpGx.dp);
    eccDomain.generatorY = (uint8_t*)&(mpGy.dp);
    eccDomain.a = (uint8_t*)&(mpA.dp);
    eccDomain.b = (uint8_t*)&(mpB.dp);
    
    ret = DRV_BA414E_PRIM_EccCheckPointOnCurve(ba414Handle, &eccDomain, 
                                            (uint8_t*)&(mpPx.dp), 
                                            (uint8_t*)&(mpPy.dp),
                                            0, 0);
    if (ret == DRV_BA414E_OP_SUCCESS)
    {
        appData.prim_test_result--;
    }
    
    ret = DRV_BA414E_PRIM_EccCheckPointOnCurve(ba414Handle, &eccDomain, 
                                            (uint8_t*)&(mpQx.dp), 
                                            (uint8_t*)&(mpQy.dp), 
                                            0, 0);
    if (ret == DRV_BA414E_OP_SUCCESS)
    {
        appData.prim_test_result--;
    }
    
    DRV_BA414E_PRIM_ModSubtraction(ba414Handle, DRV_BA414E_OPSZ_256, 
                                    (uint8_t*)&(mpRy.dp), 
                                    (uint8_t*)&(mpMax.dp), 
                                    (uint8_t*)&(mpPrime.dp), 
                                    (uint8_t*)&(mpNRy.dp),
                                    0, 0);
    ret = DRV_BA414E_PRIM_EccCheckPointOnCurve(ba414Handle, &eccDomain, 
                                    (uint8_t*)&(mpRx.dp), 
                                    (uint8_t*)&(mpRy.dp), 
                                    0, 0);
    if (ret == DRV_BA414E_OP_SUCCESS)
    {
        appData.prim_test_result--;
    }
    
    ret = DRV_BA414E_PRIM_EccCheckPointOnCurve(ba414Handle, &eccDomain, 
                                    (uint8_t*)&(mpRx.dp), 
                                    (uint8_t*)&(mpNRy.dp), 
                                    0, 0);
    if (ret == DRV_BA414E_OP_SUCCESS)
    {
        appData.prim_test_result--;
    }

    ret = DRV_BA414E_PRIM_EccCheckPointOnCurve(ba414Handle, &eccDomain, 
                                    (uint8_t*)&(mpOne.dp), 
                                    (uint8_t*)&(mpOne.dp), 
                                    0, 0);
    if (ret == DRV_BA414E_OP_POINT_NOT_ON_CURVE)
    {
        appData.prim_test_result--;
    }

    ret = DRV_BA414E_PRIM_EccPointAddition(ba414Handle, &eccDomain, 
                                    (uint8_t*)&(mpRes.dp), 
                                    (uint8_t*)&(mpResY.dp), 
                                    (uint8_t*)&(mpRx.dp), 
                                    (uint8_t*)&(mpRy.dp), 
                                    (uint8_t*)&(mpRx.dp), 
                                    (uint8_t*)&(mpNRy.dp), 
                                    0, 0);
    if (ret == DRV_BA414E_OP_ERROR_POINT_AT_INFINITY)
    {
        appData.prim_test_result--;
    }
    
    ret = DRV_BA414E_PRIM_EccPointMultiplication(ba414Handle, &eccDomain, 
                                    (uint8_t*)&(mpRes.dp), 
                                    (uint8_t*)&(mpResY.dp), 
                                    (uint8_t*)&(mpPx.dp), 
                                    (uint8_t*)&(mpPy.dp), 
                                    (uint8_t*)&(mpK.dp), 
                                    0, 0);
    if ((memcmp(mpRx.dp, mpRes.dp, 32) == 0) && (memcmp(mpRy.dp, mpResY.dp, 32) == 0))
    {
        appData.prim_test_result--;
    }
    
    
    mp_clear(&mpRes);
    mp_clear(&mpResY);
    
    ret = DRV_BA414E_PRIM_EccPointMultiplication(ba414Handle, &eccDomain, 
                                    (uint8_t*)&(mpRes.dp), 
                                    (uint8_t*)&(mpResY.dp), 
                                    (uint8_t*)&(mpPx.dp), 
                                    (uint8_t*)&(mpPy.dp), 
                                    (uint8_t*)&(mpI.dp), 
                                    0, 0);
    if (ret == DRV_BA414E_OP_SUCCESS)
    {
        appData.prim_test_result--;
    }
    ret = DRV_BA414E_PRIM_EccPointAddition(ba414Handle, &eccDomain, 
                                    (uint8_t*)&(mpRes.dp), 
                                    (uint8_t*)&(mpResY.dp), 
                                    (uint8_t*)&(mpRes.dp), 
                                    (uint8_t*)&(mpResY.dp), 
                                    (uint8_t*)&(mpQx.dp), 
                                    (uint8_t*)&(mpQy.dp), 
                                    0, 0);
    if (ret == DRV_BA414E_OP_SUCCESS)
    {
        appData.prim_test_result--;
    }
    ret = DRV_BA414E_PRIM_EccPointMultiplication(ba414Handle, &eccDomain, 
                                    (uint8_t*)&(mpRes.dp), 
                                    (uint8_t*)&(mpResY.dp), 
                                    (uint8_t*)&(mpRes.dp), 
                                    (uint8_t*)&(mpResY.dp), 
                                    (uint8_t*)&(mpJ.dp), 
                                    0, 0);
    if (ret == DRV_BA414E_OP_SUCCESS)
    {
        appData.prim_test_result--;
    }
    ret = DRV_BA414E_PRIM_EccCheckPointOnCurve(ba414Handle, &eccDomain, 
                                    (uint8_t*)&(mpRes.dp), 
                                    (uint8_t*)&(mpResY.dp), 
                                    0, 0);
    

    if (ret == DRV_BA414E_OP_SUCCESS)
    {
        appData.prim_test_result--;
    }
    if ((memcmp(mpSx.dp, mpRes.dp, 32) == 0))
    {
        appData.prim_test_result--;
    }
    mp_clear(&mpRes);
    mp_clear(&mpResY);

    mp_clear(&mpRes);
    mp_clear(&mpResY);
    ret = DRV_BA414E_PRIM_EccPointDouble(ba414Handle, &eccDomain, 
                                        (uint8_t*)&(mpRes.dp), 
                                        (uint8_t*)&(mpResY.dp), 
                                        (uint8_t*)&(mpPx.dp), 
                                        (uint8_t*)&(mpPy.dp), 
                                        0, 0);
    if (ret == DRV_BA414E_OP_SUCCESS)
    {
        appData.prim_test_result--;
    }
    if ((memcmp(primTestPDx, mpRes.dp, 32) == 0) && (memcmp(primTestPDy, mpResY.dp, 32) == 0))
    {
        appData.prim_test_result--;
    }
    
    
    DRV_BA414E_Close(ba414Handle);
    
    
}


#endif


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

    /* Check the application's current state. */
    switch (appData.state) {
        /* Application's initial state. */
        case APP_STATE_INIT:
        {
            /* Show Hyperterminal is working using available output functions */
            // SYS_MESSAGE("SYS_MESSAGE:" "\r\n Application created " __DATE__ " " __TIME__ " initialized!\r\n");            
            // SYS_DEBUG(SYS_ERROR_INFO,"SYS_DEBUG:" "\r\n Application created " __DATE__ " " __TIME__ " initialized!\r\n");
            appData.usartHandle = DRV_USART_Open(DRV_USART_INDEX_0, DRV_IO_INTENT_READWRITE);
            DRV_USART_WriteBuffer( appData.usartHandle, msgBuffer, strlen(msgBuffer));
            appData.state = APP_STATE_TEST_MD5;
            break;
        }

        case APP_STATE_TEST_MD5:
#ifndef NO_MD5
            testCount++;
            md5_test();
#endif
            appData.state = APP_STATE_TEST_SHA;
            break;


         case APP_STATE_TEST_SHA:
#ifndef NO_SHA
            testCount++;
            sha_test();
#endif
            appData.state = APP_STATE_TEST_SHA256;
            break;

         case APP_STATE_TEST_SHA256: 

#ifndef NO_SHA256
            testCount++;
            sha256_test();
#endif
            appData.state = APP_STATE_TEST_SHA224;
            break;

         case APP_STATE_TEST_SHA224: 
#ifdef WOLFSSL_SHA224
            testCount++;
            sha224_test();
#endif
            appData.state = APP_STATE_TEST_SHA384;
            break;
            
        case APP_STATE_TEST_SHA384:
#ifdef WOLFSSL_SHA384
            sha384_test();
#endif
            appData.state = APP_STATE_TEST_SHA512;
            break;

        case APP_STATE_TEST_SHA512:
#ifdef WOLFSSL_SHA512
            testCount++;
            sha512_test();
#endif
            appData.state = APP_STATE_TEST_HMAC_MD5;
            break;
  
        case APP_STATE_TEST_HMAC_MD5:
#if !defined(NO_HMAC) && !defined(NO_MD5)
            testCount++;
            hmac_md5_test();
#endif
            appData.state = APP_STATE_TEST_HMAC_SHA;
            break;
            
        case APP_STATE_TEST_HMAC_SHA:
#if !defined(NO_HMAC) && !defined(NO_SHA)
            testCount++;
            hmac_sha_test();
#endif
            appData.state = APP_STATE_TEST_HMAC_SHA256;
            break;
             
        case APP_STATE_TEST_HMAC_SHA256:
#if !defined(NO_HMAC) && !defined(NO_SHA256)
            testCount++;
            hmac_sha256_test();
#endif
            appData.state = APP_STATE_TEST_HMAC_SHA384;
            break;
              
        case APP_STATE_TEST_HMAC_SHA384:
#if !defined(NO_HMAC) && defined(WOLFSSL_SHA384)
            testCount++;
            hmac_sha384_test();
#endif
            appData.state = APP_STATE_TEST_HMAC_SHA512;
            break;
              
        case APP_STATE_TEST_HMAC_SHA512:
#if !defined(NO_HMAC) && defined(WOLFSSL_SHA512)
            testCount++;
            hmac_sha512_test();
#endif
            appData.state = APP_STATE_TEST_RANDOM;
            break;
            
        case APP_STATE_TEST_RANDOM:
#ifndef NO_RNG_TEST
            testCount++;
            random_test();
#endif
            appData.state = APP_STATE_TEST_ECC;
            break;
			
        case APP_STATE_TEST_ECC:
#ifdef HAVE_ECC
            testCount++;
            ecc_test();
#endif
            appData.state = APP_STATE_TEST_AES;
            break;
                          
        case APP_STATE_TEST_AES:
#ifndef NO_AES
            testCount++;
            aes_test();
#endif
            appData.state = APP_STATE_TEST_AES_GCM;
            break;

        case APP_STATE_TEST_AES_GCM:
#ifdef HAVE_AESGCM
            testCount++;
            aesgcm_default_test();
            int result = aesgcm_test();
            result = result;
#endif
            appData.state = APP_STATE_TEST_COMPRESS;
            break;
            
            
        case APP_STATE_TEST_COMPRESS:
#ifdef HAVE_LIBZ
            testCount++;
            compress_test();
#endif
            appData.state = APP_STATE_TEST_DES;
            break;
              
        case APP_STATE_TEST_DES:
#ifndef NO_DES3
            testCount++;
            des_test();
#endif
            appData.state = APP_STATE_TEST_DES3;
            break;
 
        case APP_STATE_TEST_DES3:
#ifndef NO_DES3
            testCount++;
            des3_test();
#endif
            appData.state = APP_STATE_TEST_RSA;
            break;
        
        case APP_STATE_TEST_RSA:
#ifndef NO_RSA
            testCount++;
            rsa_test();
#endif
            appData.state = APP_STATE_TEST_PRIMS;
            break;
            
        case APP_STATE_TEST_PRIMS:
#ifdef WOLFSSL_HAVE_MCHP_BA414E_CRYPTO
            testCount++;
            prim_test();
#endif
            appData.state = APP_STATE_DISPLAY_RESULTS;
            break;
        case APP_STATE_DISPLAY_RESULTS:
#ifndef NO_MD5
            sprintf(printBuffer, "%s\n\rMD5 test:          %s", 
                    printBuffer, (appData.md5_test_result==expectedResult?"Pass":"FAIL"));
            sprintf(printBuffer, "%s\t %10d clock cycles", printBuffer, (int) appData.md5_timing);
#endif

#ifndef NO_SHA
            sprintf(printBuffer, "%s\n\rSHA test:          %s", 
                    printBuffer, (appData.sha_test_result==expectedResult?"Pass":"FAIL"));
            sprintf(printBuffer, "%s\t %10d clock cycles", printBuffer, (int) appData.sha_timing);
#endif

#ifdef WOLFSSL_SHA224
            sprintf(printBuffer, "%s\n\rSHA224 test:       %s", 
                    printBuffer, (appData.sha224_test_result==expectedResult?"Pass":"FAIL"));
            sprintf(printBuffer, "%s\t %10d clock cycles", printBuffer, (int) appData.sha224_timing);
#endif
            
#ifndef NO_SHA256
            sprintf(printBuffer, "%s\n\rSHA256 test:       %s", 
                    printBuffer, (appData.sha256_test_result==expectedResult?"Pass":"FAIL"));
            sprintf(printBuffer, "%s\t %10d clock cycles", printBuffer, (int) appData.sha256_timing);
#endif

#ifdef WOLFSSL_SHA384
            sprintf(printBuffer, "%s\n\rSHA384 test:       %s", 
                    printBuffer, (appData.sha384_test_result==expectedResult?"Pass":"FAIL"));
            sprintf(printBuffer, "%s\t %10d clock cycles", printBuffer, (int) appData.sha384_timing);
#endif

#ifdef WOLFSSL_SHA512
            sprintf(printBuffer, "%s\n\rSHA512 test:       %s", 
                    printBuffer, (appData.sha512_test_result==expectedResult?"Pass":"FAIL"));
            sprintf(printBuffer, "%s\t %10d clock cycles", printBuffer, (int) appData.sha512_timing);
#endif

#if !defined(NO_HMAC) && !defined(NO_MD5)
            sprintf(printBuffer, "%s\n\rHMAC_MD5 test:     %s", 
                    printBuffer, (appData.hmac_md5_test_result==expectedResult?"Pass":"FAIL"));
            sprintf(printBuffer, "%s\t %10d clock cycles", printBuffer, (int) appData.hmac_md5_timing);
#endif

#if !defined(NO_HMAC) && !defined(NO_SHA)
            sprintf(printBuffer, "%s\n\rHMAC_SHA test:     %s", 
                    printBuffer, (appData.hmac_sha_test_result==expectedResult?"Pass":"FAIL"));
            sprintf(printBuffer, "%s\t %10d clock cycles", printBuffer, (int) appData.hmac_sha_timing);
#endif

#if !defined(NO_HMAC) && !defined(NO_SHA256)
            sprintf(printBuffer, "%s\n\rHMAC_SHA256 test:  %s", 
                    printBuffer, (appData.hmac_sha256_test_result==expectedResult?"Pass":"FAIL"));
            sprintf(printBuffer, "%s\t %10d clock cycles", printBuffer, (int) appData.hmac_sha256_timing);
#endif

#if !defined(NO_HMAC) && defined(WOLFSSL_SHA384)
            sprintf(printBuffer, "%s\n\rHMAC_SHA384 test:  %s", 
                    printBuffer, (appData.hmac_sha384_test_result==expectedResult?"Pass":"FAIL"));
            sprintf(printBuffer, "%s\t %10d clock cycles", printBuffer, (int) appData.hmac_sha384_timing);
#endif

#if !defined(NO_HMAC) && defined(WOLFSSL_SHA512)
            sprintf(printBuffer, "%s\n\rHMAC_SHA512 test:  %s", 
                    printBuffer, (appData.hmac_sha512_test_result==expectedResult?"Pass":"FAIL"));
            sprintf(printBuffer, "%s\t %10d clock cycles", printBuffer, (int) appData.hmac_sha512_timing);
#endif

#ifdef HAVE_ECC
            sprintf(printBuffer, "%s\n\rECC test:          %s", 
                    printBuffer, (appData.ecc_test_result==expectedResult?"Pass":"FAIL"));
            sprintf(printBuffer, "%s\t %10"PRIu64" clock cycles", printBuffer, appData.ecc_timing);
#endif
#ifndef NO_RNG_TEST
            sprintf(printBuffer, "%s\n\rRANDOM test:       %s", 
                    printBuffer, (appData.random_test_result==expectedResult?"Pass":"FAIL"));
            sprintf(printBuffer, "%s\t %10d clock cycles", printBuffer, (int) appData.random_timing);
#endif
#ifndef NO_AES
            sprintf(printBuffer, "%s\n\rAES CBC test:      %s", 
                    printBuffer, (appData.aes_cbc_test_result==expectedResult?"Pass":"FAIL"));
            sprintf(printBuffer, "%s\t %10d clock cycles", printBuffer, (int) appData.aes_cbc_timing);
#ifdef HAVE_AESGCM
            sprintf(printBuffer, "%s\n\rAES GCM test:      %s", 
                    printBuffer, (appData.aes_gcm_test_result==expectedResult?"Pass":"FAIL"));
            sprintf(printBuffer, "%s\t %10d clock cycles", printBuffer, (int) appData.aes_gcm_timing);            
#endif
#ifdef WOLFSSL_AES_COUNTER
            sprintf(printBuffer, "%s\n\rAES CTR test:      %s", 
                     printBuffer, (appData.aes_ctr_test_result==expectedResult?"Pass":"FAIL"));
            sprintf(printBuffer, "%s\t %10d clock cycles", printBuffer, (int) appData.aes_ctr_timing);
#endif                    
#endif

#ifdef HAVE_LIBZ
            sprintf(printBuffer, "%s\n\rCOMPRESS test:     %s", 
                    printBuffer, (appData.compress_test_result==expectedResult?"Pass":"FAIL"));
            sprintf(printBuffer, "%s\t %10d clock cycles", printBuffer, (int) appData.compress_timing);
#endif

#ifndef NO_DES3
            sprintf(printBuffer, "%s\n\rDES test:          %s", 
                    printBuffer, (appData.des_test_result==expectedResult?"Pass":"FAIL"));
            sprintf(printBuffer, "%s\t %10d clock cycles", printBuffer, (int) appData.des_timing);
#endif

#ifndef NO_DES3
            sprintf(printBuffer, "%s\n\rDES3 test:         %s", 
                    printBuffer, (appData.des3_test_result==expectedResult?"Pass":"FAIL"));
            sprintf(printBuffer, "%s\t %10d clock cycles", printBuffer, (int) appData.des3_timing);
#endif

#ifndef NO_RSA
            sprintf(printBuffer, "%s\n\rRSA test:          %s", 
                    printBuffer, (appData.rsa_test_result==expectedResult?"Pass":"FAIL"));
            sprintf(printBuffer, "%s\t %10"PRIu64" clock cycles", printBuffer, appData.rsa_timing);
#endif
#ifdef WOLFSSL_HAVE_MCHP_BA414E_CRYPTO
            sprintf(printBuffer, "%s\n\rPrimative test:    %s", 
                    printBuffer, (appData.prim_test_result==expectedResult?"Pass":"FAIL"));
#endif
            appData.state = APP_STATE_CHECK_RESULTS;

            break;

        case APP_STATE_CHECK_RESULTS:
            if ( testCount == 0 ) {
                sprintf(printBuffer, "%s\n\rNo tests executed\n\r", printBuffer);
            }
            else if (
#ifndef NO_RNG_TEST
                expectedResult != appData.random_test_result ||
#endif
#ifndef NO_MD5
                expectedResult != appData.md5_test_result || 
#endif
#ifndef NO_SHA                    
                expectedResult != appData.sha_test_result ||
#endif
#ifdef WOLFSSL_SHA224                    
                expectedResult != appData.sha224_test_result ||
#endif
#ifndef NO_SHA256                    
                expectedResult != appData.sha256_test_result ||
#endif
#ifdef WOLFSSL_SHA384                    
                expectedResult != appData.sha384_test_result ||
#endif
#ifdef WOLFSSL_SHA512                    
                expectedResult != appData.sha512_test_result ||
#endif
#if !defined(NO_HMAC) && !defined(NO_MD5)                    
                expectedResult != appData.hmac_md5_test_result ||
#endif
#if !defined(NO_HMAC) && !defined(NO_SHA)                    
                expectedResult != appData.hmac_sha_test_result ||
#endif
#if !defined(NO_HMAC) && !defined(NO_SHA256)                    
                expectedResult != appData.hmac_sha256_test_result ||
#endif
#if !defined(NO_HMAC) && defined(WOLFSSL_SHA384)                    
                expectedResult != appData.hmac_sha384_test_result ||
#endif
#if !defined(NO_HMAC) && defined(WOLFSSL_SHA512)                    
                expectedResult != appData.hmac_sha512_test_result ||
#endif
#ifdef HAVE_ECC
                expectedResult != appData.ecc_test_result ||
#endif
#ifndef NO_AES 
#ifndef NO_AES_CBC                  
                expectedResult != appData.aes_cbc_test_result ||
#endif
#ifdef WOLFSSL_AES_COUNTER                    
                expectedResult != appData.aes_ctr_test_result ||
#endif
#ifdef HAVE_AESGCM
                expectedResult != appData.aes_gcm_test_result ||
#endif                    
#endif
#ifdef HAVE_LIBZ
                expectedResult != appData.compress_test_result ||
#endif
#ifndef NO_DES3                   
                expectedResult != appData.des_test_result ||
                expectedResult != appData.des3_test_result ||
#endif
#ifndef NO_RSA
                expectedResult != appData.rsa_test_result ||
#endif
#ifdef WOLFSSL_HAVE_MCHP_BA414E_CRYPTO
                expectedResult != appData.prim_test_result ||
#endif                    
                expectedResult != dummy_test_result /* always false */
            ) 
            {
                /* We had an error during comparisons */
                sprintf(printBuffer, "%s\n\rOne or more tests FAILED\n\r", printBuffer);
            } else {
                sprintf(printBuffer, "%s\n\rAll tests passed\n\r", printBuffer);
            }
            DRV_USART_WriteBuffer( appData.usartHandle, printBuffer, strlen(printBuffer));
            appData.state = APP_SPIN;
            break;

        case APP_STATE_WAIT_FOR_CONSOLE:
            if (appData.wallTime <= APP_getTicks())
                appData.state = APP_STATE_DISPLAY_RESULTS;
            break;

        case APP_SPIN:

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
