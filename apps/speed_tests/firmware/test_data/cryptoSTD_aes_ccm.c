/* cryptoSTV_wolfSSL_AES_CCM

   This package presents data from RFC-3610 (September 2003) to
   check operation of the AES-CCM (CBC-CTR) mode.
*/

#include <stdint.h>
#include "./cryptoSpeedTestData.h"
#include "cryptoST/cryptoSTE_generate.h"
#include "cryptoST/cryptoSTE_malloc.h"
#include "cryptoST/cryptoST_print.h" // for BASE_LINE

#define CONST /* as nothing */
#define DATA_PACKAGE_NAME "CCM"

#define AES_CCM_source "RFC3610 section 8"
const CPU_CHAR AES_CCM_default_description[] = {
        "Vectors from " AES_CCM_source
        " using 13 byte nonce (IV) and 8 or 10 byte AAD " };

/*************************************************************
 * Raw (input) data definitions.
 *************************************************************/
static CPU_CHAR PVdata[] = 
    "\x00\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0A\x0B\x0C\x0D\x0E\x0F"
    "\x10\x11\x12\x13\x14\x15\x16\x17\x18\x19\x1A\x1B\x1C\x1D\x1E";
static CPU_CHAR PVcipher[] =
    "\x00\x01\x02\x03\x04\x05\x06\x07\x58\x8C\x97\x9A\x61\xC6\x63\xD2"
    "\xF0\x66\xD0\xC2\xC0\xF9\x89\x80\x6D\x5F\x6B\x61\xDA\xC3\x84\x17"
    "\xE8\xD1\x2C\xFD\xF9\x26\xE0";

static CONST cryptoST_testVector_t rfc3610A[] = {
{
    .name = DATA_PACKAGE_NAME "_PV1.4.7.10",
    .source = AES_CCM_source,
    .description = AES_CCM_default_description,
    .vector.length = 31 - 8,
    .vector.data = (uint8_t*)(&PVdata[8]),
#if 0
            (uint8_t[]){ 
        "\x00\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0A\x0B\x0C\x0D\x0E\x0F"
        "\x10\x11\x12\x13\x14\x15\x16\x17\x18\x19\x1A\x1B\x1C\x1D\x1E"
    },
#endif
},
{
    .name = DATA_PACKAGE_NAME "_PV2.5.8.11",
    .source = AES_CCM_source,
    .description = AES_CCM_default_description,
    .vector.data = (uint8_t[]){ 
        "\x00\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0A\x0B\x0C\x0D\x0E\x0F"
        "\x10\x11\x12\x13\x14\x15\x16\x17\x18\x19\x1A\x1B\x1C\x1D\x1E\x1F"
    },
    .vector.length = 32,
},
{
    .name = DATA_PACKAGE_NAME "_PV3.6.9.12",
    .source = AES_CCM_source,
    .description = AES_CCM_default_description,
    .vector.data = (uint8_t[]){ 
        "\x00\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0A\x0B\x0C\x0D\x0E\x0F"
        "\x10\x11\x12\x13\x14\x15\x16\x17\x18\x19\x1A\x1B\x1C\x1D\x1E\x1F"
        "\x20"
    },
    .vector.length = 33,
},
};

__attribute__((used))
static CONST cryptoST_testVector_t rfc3610B[] = {
{
    .name = DATA_PACKAGE_NAME "_PV13",
    .source = AES_CCM_source,
    .description = AES_CCM_default_description,
    .vector.data = (uint8_t[]){ 
        "\x0B\xE1\xA8\x8B\xAC\xE0\x18\xB1\x08\xE8\xCF\x97\xD8\x20\xEA\x25"
        "\x84\x60\xE9\x6A\xD9\xCF\x52\x89\x05\x4D\x89\x5C\xEA\xC4\x7C"
    },
    .vector.length = 31,
},
{
    .name = DATA_PACKAGE_NAME "_PV14",
    .source = AES_CCM_source,
    .description = AES_CCM_default_description,
    .vector.data = (uint8_t[]){ 
        "\x63\x01\x8F\x76\xDC\x8A\x1B\xCB\x90\x20\xEA\x6F\x91\xBD\xD8\x5A"
        "\xFA\x00\x39\xBA\x4B\xAF\xF9\xBF\xB7\x9C\x70\x28\x94\x9C\xD0\xEC"
    },
    .vector.length = 32,
},
#if 0 
// data packets 14..24 all all different, same key but different nonce
Total packet length = 33. [Input with 8 cleartext header octets]
AA 6C FA 36 CA E8 6B 40 B9 16 E0 EA CC 1C 00 D7
DC EC 68 EC 0B 3B BB 1A 02 DE 8A 2D 1A A3 46 13
2E
Total packet length = 31. [Input with 12 cleartext header octets]
D0 D0 73 5C 53 1E 1B EC F0 49 C2 44 12 DA AC 56
30 EF A5 39 6F 77 0C E1 A6 6B 21 F7 B2 10 1C
Total packet length = 32. [Input with 12 cleartext header octets]
77 B6 0F 01 1C 03 E1 52 58 99 BC AE E8 8B 6A 46
C7 8D 63 E5 2E B8 C5 46 EF B5 DE 6F 75 E9 CC 0D
Total packet length = 33. [Input with 12 cleartext header octets]
CD 90 44 D2 B7 1F DB 81 20 EA 60 C0 64 35 AC BA
FB 11 A8 2E 2F 07 1D 7C A4 A5 EB D9 3A 80 3B A8
7F
Total packet length = 31. [Input with 8 cleartext header octets]
D8 5B C7 E6 9F 94 4F B8 8A 19 B9 50 BC F7 1A 01
8E 5E 67 01 C9 17 87 65 98 09 D6 7D BE DD 18
Total packet length = 32. [Input with 8 cleartext header octets]
74 A0 EB C9 06 9F 5B 37 17 61 43 3C 37 C5 A3 5F
C1 F3 9F 40 63 02 EB 90 7C 61 63 BE 38 C9 84 37
Total packet length = 33. [Input with 8 cleartext header octets]
44 A3 AA 3A AE 64 75 CA A4 34 A8 E5 85 00 C6 E4
15 30 53 88 62 D6 86 EA 9E 81 30 1B 5A E4 22 6B
FA
Total packet length = 31. [Input with 12 cleartext header octets]
EC 46 BB 63 B0 25 20 C3 3C 49 FD 70 B9 6B 49 E2
1D 62 17 41 63 28 75 DB 7F 6C 92 43 D2 D7 C2
Total packet length = 32. [Input with 12 cleartext header octets]
47 A6 5A C7 8B 3D 59 42 27 E8 5E 71 E2 FC FB B8
80 44 2C 73 1B F9 51 67 C8 FF D7 89 5E 33 70 76
Total packet length = 33. [Input with 12 cleartext header octets]
6E 37 A6 EF 54 6D 95 5D 34 AB 60 59 AB F2 1C 0B
02 FE B8 8F 85 6D F4 A3 73 81 BC E3 CC 12 85 17
D4
#endif
};

/*************************************************************
 * Key, nonce and AAD inputs and golden data and tag result definitions.
 *************************************************************/
static uint8_t key_pv1to12[] = (uint8_t[]){ // PV1-12 have the same data
    "\xC0\xC1\xC2\xC3\xC4\xC5\xC6\xC7\xC8\xC9\xCA\xCB\xCC\xCD\xCE\xCF" };

static CONST cryptoST_testDetail_t test_item[] =
{
    {
#undef CLEARTEXT
#define CLEARTEXT   8
        #if 0
from: https://github.com/ircmaxell/quality-checker/blob/master/tmp/gh_18/PHP-PasswordLib-master/test/Data/Vectors/ccm-RFC3610.test-vectors
=============== Packet Vector #1 ==================
   AES Key =  C0C1C2C3C4C5C6C7C8C9CACBCCCDCECF
   Nonce =    00000003020100A0A1A2A3A4A5
   Adata =    0001020304050607
   Asize =    8
   Data =     000102030405060708090A0B0C0D0E0F101112131415161718191A1B1C1D1E
   Cipher =   0001020304050607588C979A61C663D2F066D0C2C0F989806D5F6B61DAC38417E8D12CFDF926E0

from: https://lists.gnupg.org/pipermail/gcrypt-devel/2013-October/002520.html
+      /* RFC 3610 */
+      { GCRY_CIPHER_AES, /* Packet Vector #1 */
+          16, "\xC0\xC1\xC2\xC3\xC4\xC5\xC6\xC7\xC8\xC9\xCA\xCB\xCC\xCD\xCE\xCF",
+          13, "\x00\x00\x00\x03\x02\x01\x00\xA0\xA1\xA2\xA3\xA4\xA5",
+          8, "\x00\x01\x02\x03\x04\x05\x06\x07",
+          23,
+ "\x08\x09\x0A\x0B\x0C\x0D\x0E\x0F\x10\x11\x12\x13\x14\x15\x16\x17\x18\x19\x1A\x1B\x1C\x1D\x1E",
+          31,
+          "\x58\x8C\x97\x9A\x61\xC6\x63\xD2\xF0\x66\xD0\xC2\xC0\xF9\x89\x80\x6D\x5F\x6B\x61\xDA\xC3\x84\x17\xE8\xD1\x2C\xFD\xF9\x26\xE0"},
+      { GCRY_CIPHER_AES, /* Packet Vector #2 */
+          16, "\xC0\xC1\xC2\xC3\xC4\xC5\xC6\xC7\xC8\xC9\xCA\xCB\xCC\xCD\xCE\xCF",
+          13, "\x00\x00\x00\x04\x03\x02\x01\xA0\xA1\xA2\xA3\xA4\xA5",
+          8, "\x00\x01\x02\x03\x04\x05\x06\x07",
+          24,
+          "\x08\x09\x0A\x0B\x0C\x0D\x0E\x0F\x10\x11\x12\x13\x14\x15\x16\x17\x18\x19\x1A\x1B\x1C\x1D\x1E\x1F",
+          32,
+          "\x72\xC9\x1A\x36\xE1\x35\xF8\xCF\x29\x1C\xA8\x94\x08\x5C\x87\xE3\xCC\x15\xC4\x39\xC9\xE4\x3A\x3B\xA0\x91\xD5\x6E\x10\x40\x09\x16"},
+      { GCRY_CIPHER_AES, /* Packet Vector #3 */
+          16, "\xC0\xC1\xC2\xC3\xC4\xC5\xC6\xC7\xC8\xC9\xCA\xCB\xCC\xCD\xCE\xCF",
+          13, "\x00\x00\x00\x05\x04\x03\x02\xA0\xA1\xA2\xA3\xA4\xA5",
+          8, "\x00\x01\x02\x03\x04\x05\x06\x07",
+          25,
+          "\x08\x09\x0A\x0B\x0C\x0D\x0E\x0F\x10\x11\x12\x13\x14\x15\x16\x17\x18\x19\x1A\x1B\x1C\x1D\x1E\x1F\x20",
+          33,
+          "\x51\xB1\xE5\xF4\x4A\x19\x7D\x1D\xA4\x6B\x0F\x8E\x2D\x28\x2A\xE8\x71\xE8\x38\xBB\x64\xDA\x85\x96\x57\x4A\xDA\xA7\x6F\xBD\x9F\xB0\xC5"},
#endif
        .technique = ET_AES_CCM,
        .mode = EM_NONE,
        .recommendedRepetitions = 1000,

        // similar data also appears in the WolfSSL test suite
        // ./wolfssl/wolfcrypt/test/test.c line 6335",
        .source = __BASE_FILE__ "(" BASE_LINE ")",
        .pedigree = AES_CCM_source "_PV1",
        .rawData = &rfc3610A[0],
        .key = { .length = 16, .data = key_pv1to12 },
        .initVector = { // nonce
            .length = 13,
            .data = (uint8_t[]){
                "\x00\x00\x00\x03\x02\x01\x00"
                "\xA0\xA1\xA2\xA3\xA4\xA5" },
        },
        .additionalAuthData = { 
            .length = 8, 
            .data = (uint8_t*)PVdata, // rfc3610A[0].vector.data,
        },
        .goldenCipher = { 
            .length = 31,
            .data = (uint8_t*)&PVcipher[8],
#if 0
            .data = (uint8_t[]){
            "\x00\x01\x02\x03\x04\x05\x06\x07\x58\x8C\x97\x9A\x61\xC6\x63\xD2"
            "\xF0\x66\xD0\xC2\xC0\xF9\x89\x80\x6D\x5F\x6B\x61\xDA\xC3\x84\x17"
            "\xE8\xD1\x2C\xFD\xF9\x26\xE0"
        }
#endif
//   Cipher =     0001020304050607 588C979A61C663D2
//                F066D0C2C0F98980 6D5F6B61DAC38417
//                E8D12CFDF926E0
        },
        .goldenTag = { .length = 0, .data = 0 },
    },
    {}
};
#define test_item_count (sizeof(test_item)/sizeof(cryptoST_testDetail_t))

/*************************************************************
 * Helper functions
 *************************************************************/

/*************************************************************
 * API handlers
 *************************************************************/
static cryptoST_testDetail_t * firstTest(void)
{
    cryptoST_testDetail_t * td = &test_item[0];

    if (0 == td->additionalAuthData.data)
        td->additionalAuthData.data = td->rawData->vector.data;
    return td;
}
static cryptoST_testDetail_t * nextTest(cryptoST_testDetail_t * old)
{
    // Assume that if the pointer is in range, that it is legitimate.
    if (old < test_item) 
        return NULL;
    old++; // repurpose: this is now "new"
    
    // We know that the final (illegitimate) entry has a null technique,
    // but we still need to check if "old" is _way_ out of bounds.
    if ((old >= &test_item[test_item_count])
            || (ET_NONE == old->technique))
        return NULL;
    else
    {
        if (0 == old->additionalAuthData.data)
            old->additionalAuthData.data = old->rawData->vector.data;
        return old;
    }
}

#if 0 // not used here
static char * openData(void)
{
    /* Allocate the largest required buffer now, because there
     * is no provision for return errors in first() or next().
     * If we can't get it now, we won't get it later, either.
     *  */
    dynamicBuffer = cryptoSTE_malloc(SIZE_PREALLOCATE); // bytes
    return dynamicBuffer? NULL :
        DATA_PACKAGE_NAME " malloc error " __BASE_FILE__ "(" BASE_LINE ")";
}

static char * closeData(void)
{
    if (dynamicBuffer) cryptoSTE_free(dynamicBuffer);
    dynamicBuffer = NULL;
    return NULL;
}
#endif

/*************************************************************
 * Declaration of the test manager API
 * Obligatory entry points for executing a test
 *************************************************************/
#include "cryptoSTD_aes_ccm.h"
cryptoST_testAPI_t const microchip_aes_ccm =
{
    .name = "AES_" DATA_PACKAGE_NAME,
    .openData = ((void*)0),
    .firstTest = firstTest,
    .nextTest = nextTest,
    .closeData = ((void*)0),
};

