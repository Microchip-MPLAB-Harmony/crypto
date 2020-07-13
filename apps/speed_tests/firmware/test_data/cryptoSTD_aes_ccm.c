/*******************************************************************************
  Crypto Speed Test Data File

  Company:
    Microchip Technology Inc.

  File Name:
    cryptoSTD_aes_ccm.h

  Summary:
   Data from RFC-3610 (September 2003) to
   check operation of the AES-CCM (CBC-CTR) mode.

  Description:
  This package provides standard test cases for AES CCM encryption.
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

/* Data sources
   There are 3 reference sources for this data:
   1. RFC-3610 as published by
      https://github.com/ircmaxell/quality-checker/blob/master/tmp/gh_18/PHP-PasswordLib-master/test/Data/Vectors/ccm-RFC3610.test-vectors
   2. https://lists.gnupg.org/pipermail/gcrypt-devel/2013-October/002520.html
   3. WolfCrypt /wolfssl/wolfcrypt/test/test.c
The three sources provide the same data in radically different formats, where
(1) is the governing document albeit cryptic, and (2) and (3) are easier to apply
here but (3) provides only the first element of the 24-vector suite.

The key principles are these:
    a. RFC-3610 talks about "cleartext" which is taken as the AAD value,
       where the length of cleartext is specified.
    b. Input "data" is the remnant after the AAD has been skipped.
    c. RFC-3610 "output" concatenates AAD|cipher|io.sym.out.tag as the official
       output, which when combined fill the specified output packet length.
    d. The length of the generated tag is the remnant of the output data
       after cleartext (AAD) and ciphertext have been skipped. Although
       the tag length is, in principle, arbitrary, it must be defined
       so that the generated tag matches the provided golden-tag length.
*/

#include <stdint.h>
#include "./cryptoSpeedTestData.h"
#include "cryptoST/cryptoSTE_generate.h"
#include "cryptoST/cryptoSTE_malloc.h"
#include "cryptoST/cryptoSTE_print.h" // for BASE_LINE
#include "cryptoSTD_aes_ccm.h"

#define CONST /* as nothing */
#define DATA_PACKAGE_NAME "CCM"
#define ALIGN4 __attribute__((aligned(4)))
#define DATA_CHAR ALIGN4 const uint8_t

#define AES_CCM_source "RFC3610 section 8"
const CPU_CHAR AES_CCM_default_description[] = {
        "Vectors from " AES_CCM_source
        " using 13 byte nonce (IV) and 8 or 10 byte AAD " };

/*************************************************************
 * Raw (input) data definitions.
 *************************************************************/
#define CLEAR8      8
#define CLEAR12     12
static DATA_CHAR PVdata_pv1to12[] = 
    "\x00\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0A\x0B\x0C\x0D\x0E\x0F"
    "\x10\x11\x12\x13\x14\x15\x16\x17\x18\x19\x1A\x1B\x1C\x1D\x1E\x1F"
    "\x20";

static const cryptoST_testVector_t rfc3610A_pv1pv7 =
{
    .name = DATA_PACKAGE_NAME " PV1.PV7",
    .source = AES_CCM_source,
    .description = AES_CCM_default_description,
    .vector.length = 31 - CLEAR8,
    .vector.data = &PVdata_pv1to12[CLEAR8],
};
static const cryptoST_testVector_t rfc3610A_pv2pv8 =
{
    .name = DATA_PACKAGE_NAME " PV2.PV8",
    .source = AES_CCM_source,
    .description = AES_CCM_default_description,
    .vector.length = 32 - CLEAR8,
    .vector.data = &PVdata_pv1to12[CLEAR8],
};
static const cryptoST_testVector_t rfc3610A_pv3pv9 =
{
    .name = DATA_PACKAGE_NAME " PV3.PV9",
    .source = AES_CCM_source,
    .description = AES_CCM_default_description,
    .vector.length = 33 - CLEAR8,
    .vector.data = &PVdata_pv1to12[CLEAR8],
};
static const cryptoST_testVector_t rfc3610A_pv4pv10 =
{
    .name = DATA_PACKAGE_NAME " PV4.PV10",
    .source = AES_CCM_source,
    .description = AES_CCM_default_description,
    .vector.length = 31 - CLEAR12,
    .vector.data = &PVdata_pv1to12[CLEAR12],
};
static const cryptoST_testVector_t rfc3610A_pv5pv11 =
{
    .name = DATA_PACKAGE_NAME " PV5.PV11",
    .source = AES_CCM_source,
    .description = AES_CCM_default_description,
    .vector.length = 32 - CLEAR12,
    .vector.data = &PVdata_pv1to12[CLEAR12],
};
static const cryptoST_testVector_t rfc3610A_pv6pv12 =
{
    .name = DATA_PACKAGE_NAME " PV6.PV12",
    .source = AES_CCM_source,
    .description = AES_CCM_default_description,
    .vector.length = 33 - CLEAR12,
    .vector.data = &PVdata_pv1to12[CLEAR12],
};

static const cryptoST_testVector_t rfc3610B_pv13 =
{
    .name = DATA_PACKAGE_NAME " PV13",
    .source = AES_CCM_source,
    .description = AES_CCM_default_description,
    .vector.data = (DATA_CHAR*)
        "\x08\xE8\xCF\x97\xD8\x20\xEA\x25\x84\x60\xE9\x6A\xD9\xCF\x52\x89"
        "\x05\x4D\x89\x5C\xEA\xC4\x7C",
    .vector.length = 31-CLEAR8,
};
static const cryptoST_testVector_t rfc3610B_pv14 =
{
    .name = DATA_PACKAGE_NAME " PV14",
    .source = AES_CCM_source,
    .description = AES_CCM_default_description,
    .vector.data = (DATA_CHAR*)
        "\x90\x20\xEA\x6F\x91\xBD\xD8\x5A\xFA\x00\x39\xBA\x4B\xAF\xF9\xBF"
        "\xB7\x9C\x70\x28\x94\x9C\xD0\xEC",
    .vector.length = 32-CLEAR8,
};

/*************************************************************
 * Key, nonce and AAD inputs and golden data and tag result definitions.
 *************************************************************/
// Note: defined as strings, the length must be stated explicitly
//       lest the null gets counted by sizeof().
static DATA_CHAR key_pv1to12[] = // PV1-PV12 have the same data
    "\xC0\xC1\xC2\xC3\xC4\xC5\xC6\xC7\xC8\xC9\xCA\xCB\xCC\xCD\xCE\xCF";
static DATA_CHAR key_pv13to24[] = // PV13-PV24 have the same data
    "\xD7\x82\x8D\x13\xB2\xB0\xBD\xC3\x25\xA7\x62\x36\xDF\x93\xCC\x6B";
    
static DATA_CHAR PV1_cipher[] = // as stated in RFC-3610
    "\x00\x01\x02\x03\x04\x05\x06\x07\x58\x8C\x97\x9A\x61\xC6\x63\xD2"
    "\xF0\x66\xD0\xC2\xC0\xF9\x89\x80\x6D\x5F\x6B\x61\xDA\xC3\x84\x17"
    "\xE8\xD1\x2C\xFD\xF9\x26\xE0";
static DATA_CHAR PV2_cipher[] = // as stated in RFC-3610
    "\x00\x01\x02\x03\x04\x05\x06\x07\x72\xC9\x1A\x36\xE1\x35\xF8\xCF"
    "\x29\x1C\xA8\x94\x08\x5C\x87\xE3\xCC\x15\xC4\x39\xC9\xE4\x3A\x3B"
    "\xA0\x91\xD5\x6E\x10\x40\x09\x16";
static DATA_CHAR PV3_cipher[] = // as stated in RFC-3610
    "\x00\x01\x02\x03\x04\x05\x06\x07\x51\xB1\xE5\xF4\x4A\x19\x7D\x1D"
    "\xA4\x6B\x0F\x8E\x2D\x28\x2A\xE8\x71\xE8\x38\xBB\x64\xDA\x85\x96"
    "\x57\x4A\xDA\xA7\x6F\xBD\x9F\xB0\xC5";
static DATA_CHAR PV4_cipher[] = // as stated in RFC-3610
    "\x00\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0A\x0B"
    "\xA2\x8C\x68\x65\x93\x9A\x9A\x79\xFA\xAA\x5C\x4C\x2A\x9D\x4A\x91"
    "\xCD\xAC\x8C\x96\xC8\x61\xB9\xC9\xE6\x1E\xF1";
static DATA_CHAR PV5_cipher[] = // as stated in RFC-3610
    "\x00\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0A\x0B"
    "\xDC\xF1\xFB\x7B\x5D\x9E\x23\xFB\x9D\x4E\x13\x12\x53\x65\x8A\xD8"
    "\x6E\xBD\xCA\x3E\x51\xE8\x3F\x07\x7D\x9C\x2D\x93";
static DATA_CHAR PV6_cipher[] = // as stated in RFC-3610
    "\x00\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0A\x0B"
    "\x6F\xC1\xB0\x11\xF0\x06\x56\x8B\x51\x71\xA4\x2D\x95\x3D\x46\x9B"
    "\x25\x70\xA4\xBD\x87\x40\x5A\x04\x43\xAC\x91\xCB\x94";
static DATA_CHAR PV7_cipher[] = // as stated in RFC-3610
    "\x00\x01\x02\x03\x04\x05\x06\x07\x01\x35\xD1\xB2\xC9\x5F\x41\xD5"
    "\xD1\xD4\xFE\xC1\x85\xD1\x66\xB8\x09\x4E\x99\x9D\xFE\xD9\x6C\x04"
    "\x8C\x56\x60\x2C\x97\xAC\xBB\x74\x90";

static DATA_CHAR PV13_cipher[] = // as stated in RFC-3610
    "\x0B\xE1\xA8\x8B\xAC\xE0\x18\xB1" // 8 cleartext
    "\x4C\xB9\x7F\x86\xA2\xA4\x68\x9A\x87\x79\x47\xAB\x80\x91\xEF\x53"
    "\x86""\xA6\xFF\xBD\xD0\x80\xF8"
    "\xE7\x8C\xF7\xCB\x0C\xDD\xD7\xB3"; // computed tag
static DATA_CHAR PV14_cipher[] = // as stated in RFC-3610
    "\x63\x01\x8F\x76\xDC\x8A\x1B\xCB" // 8 cleartext
    "\x4C\xCB\x1E\x7C\xA9\x81\xBE\xFA\xA0\x72\x6C\x55\xD3\x78\x06\x12"
    "\x98\xC8\x5C\x92\x81\x4A\xBC\x33"
    "\xC5\x2E\xE8\x1D\x7D\x77\xC0\x8A"; // computed tag

static const cryptoST_testDetail_t test_item[] =
{
    #undef CLEAR
    #define CLEAR CLEAR8
    {
        #undef TL
        #define TL 31 // test length
        #undef PL
        #define PL 39 // packet length
        .technique = ET_AES_CCM,
        .mode = EM_NONE,
        .recommendedRepetitions = 1000,

        .source = __BASE_FILE__ "(" BASE_LINE ")",
        .pedigree = AES_CCM_source " PV1",
        .rawData = &rfc3610A_pv1pv7,
        .io.sym.in.key = { .data = key_pv1to12, .length = 16 },
        .io.sym.in.additionalAuthData = { .length = CLEAR, .data = PVdata_pv1to12 },
        .io.sym.in.ivNonce = { .length = 13, // nonce
            .data = (DATA_CHAR*)
                "\x00\x00\x00\x03\x02\x01\x00\xA0\xA1\xA2\xA3\xA4\xA5" },
        .io.sym.out.cipher = { .length = TL-CLEAR, .data = &PV1_cipher[CLEAR] },
        .io.sym.out.tag    = { .length = PL-TL, .data = &PV1_cipher[TL] },
    },
    {
        #undef TL
        #define TL 32 // test length
        #undef PL
        #define PL 40 // packet length
        .technique = ET_AES_CCM,
        .mode = EM_NONE,
        .recommendedRepetitions = 1000,

        .source = __BASE_FILE__ "(" BASE_LINE ")",
        .pedigree = AES_CCM_source " PV2",
        .rawData = &rfc3610A_pv2pv8,
        .io.sym.in.key = { .data = key_pv1to12, .length = 16 },
        .io.sym.in.additionalAuthData = { .length = CLEAR, .data = PVdata_pv1to12 },
        .io.sym.in.ivNonce = { .length = 13, // nonce
            .data = (DATA_CHAR*)
                "\x00\x00\x00\x04\x03\x02\x01\xA0\xA1\xA2\xA3\xA4\xA5" },
        .io.sym.out.cipher = { .length = TL-CLEAR, .data = &PV2_cipher[CLEAR] },
        .io.sym.out.tag    = { .length = PL-TL, .data = &PV2_cipher[TL] },
    },
    {
        #undef TL
        #define TL 33 // test length
        #undef PL
        #define PL 41 // packet length
        .technique = ET_AES_CCM,
        .mode = EM_NONE,
        .recommendedRepetitions = 1000,

        .source = __BASE_FILE__ "(" BASE_LINE ")",
        .pedigree = AES_CCM_source " PV3",
        .rawData = &rfc3610A_pv3pv9,
        .io.sym.in.key = { .data = key_pv1to12, .length = 16 },
        .io.sym.in.additionalAuthData = { .length = CLEAR, .data = PVdata_pv1to12 },
        .io.sym.in.ivNonce = { .length = 13, // nonce
            .data = (DATA_CHAR*)
                "\x00\x00\x00\x05\x04\x03\x02\xA0\xA1\xA2\xA3\xA4\xA5" },
        .io.sym.out.cipher = { .length = TL-CLEAR, .data = &PV3_cipher[CLEAR] },
        .io.sym.out.tag    = { .length = PL-TL, .data = &PV3_cipher[TL] },
    },
    #undef CLEAR
    #define CLEAR CLEAR12
    {
        #undef TL
        #define TL 31 // test length
        #undef PL
        #define PL 39 // packet length
        .technique = ET_AES_CCM,
        .mode = EM_NONE,
        .recommendedRepetitions = 1000,

        .source = __BASE_FILE__ "(" BASE_LINE ")",
        .pedigree = AES_CCM_source " PV4",
        .rawData = &rfc3610A_pv4pv10,
        .io.sym.in.key = { .data = key_pv1to12, .length = 16 },
        .io.sym.in.additionalAuthData = { .length = CLEAR, .data = PVdata_pv1to12 },
        .io.sym.in.ivNonce = { .length = 13, // nonce
            .data = (DATA_CHAR*)
                "\x00\x00\x00\x06\x05\x04\x03\xA0\xA1\xA2\xA3\xA4\xA5" },
        .io.sym.out.cipher = { .length = TL-CLEAR, .data = &PV4_cipher[CLEAR] },
        .io.sym.out.tag    = { .length = PL-TL, .data = &PV4_cipher[TL] },
    },
    {
        #undef TL
        #define TL 32 // test length
        #undef PL
        #define PL 40 // packet length
        .technique = ET_AES_CCM,
        .mode = EM_NONE,
        .recommendedRepetitions = 1000,

        .source = __BASE_FILE__ "(" BASE_LINE ")",
        .pedigree = AES_CCM_source " PV5",
        .rawData = &rfc3610A_pv5pv11,
        .io.sym.in.key = { .data = key_pv1to12, .length = 16 },
        .io.sym.in.additionalAuthData = { .length = CLEAR, .data = PVdata_pv1to12 },
        .io.sym.in.ivNonce = { .length = 13, // nonce
            .data = (DATA_CHAR*)
                "\x00\x00\x00\x07\x06\x05\x04\xA0\xA1\xA2\xA3\xA4\xA5" },
        .io.sym.out.cipher = { .length = TL-CLEAR, .data = &PV5_cipher[CLEAR] },
        .io.sym.out.tag    = { .length = PL-TL, .data = &PV5_cipher[TL] },
    },
    {
        #undef TL
        #define TL 33 // test length
        #undef PL
        #define PL 41 // packet length
        .technique = ET_AES_CCM,
        .mode = EM_NONE,
        .recommendedRepetitions = 1000,

        .source = __BASE_FILE__ "(" BASE_LINE ")",
        .pedigree = AES_CCM_source " PV6",
        .rawData = &rfc3610A_pv6pv12,
        .io.sym.in.key = { .data = key_pv1to12, .length = 16 },
        .io.sym.in.additionalAuthData = { .length = CLEAR, .data = PVdata_pv1to12 },
        .io.sym.in.ivNonce = { .length = 13, // nonce
            .data = (DATA_CHAR*)
                "\x00\x00\x00\x08\x07\x06\x05\xA0\xA1\xA2\xA3\xA4\xA5" },
        .io.sym.out.cipher = { .length = TL-CLEAR, .data = &PV6_cipher[CLEAR] },
        .io.sym.out.tag    = { .length = PL-TL, .data = &PV6_cipher[TL] },
    },
    #undef CLEAR
    #define CLEAR CLEAR8
    {
        #undef TL
        #define TL 31 // test length
        #undef PL
        #define PL 41 // packet length
        .technique = ET_AES_CCM,
        .mode = EM_NONE,
        .recommendedRepetitions = 1000,

        .source = __BASE_FILE__ "(" BASE_LINE ")",
        .pedigree = AES_CCM_source " PV7",
        .rawData = &rfc3610A_pv1pv7,
        .io.sym.in.key = { .data = key_pv1to12, .length = 16 },
        .io.sym.in.additionalAuthData = { .length = CLEAR, .data = PVdata_pv1to12 },
        .io.sym.in.ivNonce = { .length = 13, // nonce
            .data = (DATA_CHAR*)
                "\x00\x00\x00\x09\x08\x07\x06\xA0\xA1\xA2\xA3\xA4\xA5" },
        .io.sym.out.cipher = { .length = TL-CLEAR, .data = &PV7_cipher[CLEAR] },
        .io.sym.out.tag    = { .length = PL-TL, .data = &PV7_cipher[TL] },
    },
    // skipping PV8..PV12
    #undef CLEAR
    #define CLEAR CLEAR8
    {
        #undef TL
        #define TL 31 // test length
        #undef PL
        #define PL 39 // packet length
        .technique = ET_AES_CCM,
        .mode = EM_NONE,
        .recommendedRepetitions = 1000,

        .source = __BASE_FILE__ "(" BASE_LINE ")",
        .pedigree = AES_CCM_source " PV13",
        .rawData = &rfc3610B_pv13,
        .io.sym.in.key = { .length = 16, .data = key_pv13to24 },
        .io.sym.in.additionalAuthData = { .length = CLEAR, .data = PV13_cipher },
        .io.sym.in.ivNonce = { .length = 13, // nonce
            .data = (DATA_CHAR*)
                "\x00\x41\x2B\x4E\xA9\xCD\xBE\x3C\x96\x96\x76\x6C\xFA" },
        .io.sym.out.cipher = { .length = TL-CLEAR, .data = &PV13_cipher[CLEAR] },
        .io.sym.out.tag    = { .length = PL-TL, .data = &PV13_cipher[TL] },
    },
    {
        #undef TL
        #define TL 32 // test length
        #undef PL
        #define PL 40 // packet length
        .technique = ET_AES_CCM,
        .mode = EM_NONE,
        .recommendedRepetitions = 1000,

        .source = __BASE_FILE__ "(" BASE_LINE ")",
        .pedigree = AES_CCM_source " PV14",
        .rawData = &rfc3610B_pv14,
        .io.sym.in.key = { .length = 16, .data = key_pv13to24 },
        .io.sym.in.additionalAuthData = { .length = CLEAR, .data = PV14_cipher },
        .io.sym.in.ivNonce = { .length = 13, // nonce
            .data = (DATA_CHAR*)
                "\x00\x33\x56\x8E\xF7\xB2\x63\x3C\x96\x96\x76\x6C\xFA" },
        .io.sym.out.cipher = { .length = TL-CLEAR, .data = &PV14_cipher[CLEAR] },
        .io.sym.out.tag    = { .length = PL-TL, .data = &PV14_cipher[TL] },
    },
    // skipping PV15..PV24
    {}
};
#define test_item_count (sizeof(test_item)/sizeof(cryptoST_testDetail_t))

/*************************************************************
 * Helper functions
 *************************************************************/

/*************************************************************
 * API handlers
 *************************************************************/
static const cryptoST_testDetail_t * firstTest(void)
{
    const cryptoST_testDetail_t * td = &test_item[0];
    return td;
}
static const cryptoST_testDetail_t * nextTest(const cryptoST_testDetail_t * old)
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
        return old;
}

/*************************************************************
 * Declaration of the test manager API
 * Obligatory entry points for executing a test
 *************************************************************/
cryptoST_testAPI_t const microchip_aes_ccm =
{
    .name = "AES_" DATA_PACKAGE_NAME,
    .openData = ((void*)0),
    .firstTest = firstTest,
    .nextTest = nextTest,
    .closeData = ((void*)0),
};

