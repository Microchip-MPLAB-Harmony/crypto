/* cryptoSTD_sha1

  Crypto Speed Test Data File

  Company:
    Microchip Technology Inc.

  Description:
  This package provides standard test cases for Triple-DES encryption. Data
  provided by Bill's SecuritySite https://asecuritysite.com/encryption/threedes.
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

#include <stdint.h>
#include "./cryptoSpeedTestData.h"
#include "cryptoST/cryptoSTE_print.h" // for BASE_LINE
#include "configuration.h"

#define CONST /* as nothing */
#define ALIGN4 __attribute__((aligned(4)))

/*************************************************************
 * Raw (input) data definitions.
 *************************************************************/
#if !defined(NO_DES3)
#define DATA_PACKAGE_NAME "THREEDES"
static const CPU_CHAR threedes_description[] =
    "Public data from Bill's SecuritySite.";
static const CPU_CHAR threedes_source[] =
    "https://asecuritysite.com/encryption/threedes";

/* PKCS7 padding works by appending N bytes with the value
 * of chr(N), where N is the number of bytes required to make
 * the final block of data the same size as the block size.
 * From: https://cryptography.io/en/latest/hazmat/primitives/padding/
 * See also: https://crypto.stackexchange.com/questions/9043
 *      and: https://en.wikipedia.org/wiki/PKCS
 * */

static const cryptoST_testVector_t qbf =
{
    .name = DATA_PACKAGE_NAME "qbf",
    .source = threedes_source,
    .description = threedes_description,
    .vector.data = (ALIGN4 const uint8_t*)
        "The quick brown fox jumped over the lazy dog"
        "\x04\x04\x04\x04\x04\x04\x04\x04", // PKCS note
    .vector.length = 48, // 44 text as 6 whole blocks 
};

#if defined(WOLFSSL_DES_ECB)
static const cryptoST_testVector_t eee =
{
    .name = DATA_PACKAGE_NAME "eee",
    .source = threedes_source,
    .description = threedes_description,
    .vector.data = (ALIGN4 const uint8_t*)
        "eeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee"
        "eeeeeeeeeeeeeeeeeeeeeee" // 55 e's
        "\x01\x01\x01\x01\x01\x01\x01\x01", // PKCS note
    .vector.length = ((55/8)+1)*8,
};
#endif

static const cryptoST_testVector_t lorem =
{
    .name = DATA_PACKAGE_NAME "lorem",
    .source = threedes_source,
    .description = threedes_description,
    .vector.data = (ALIGN4 const uint8_t*)
        "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do "
        "eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut e"
        "nim ad minim veniam, quis nostrud exercitation ullamco laboris n"
        "isi ut aliquip ex ea commodo consequat. Duis aute irure dolor in"
        " reprehenderit in voluptate velit esse cillum dolore eu fugiat n"
        "ulla pariatur. Excepteur sint occaecat cupidatat non proident, s"
        "unt in culpa qui officia deserunt mollit anim id est laborum."
        "\x03\x03\x03\x03\x03\x03\x03\x03", // PKCS note
    .vector.length = (7*64), // 3 pad bytes all with 0x03
};

static ALIGN4 const uint8_t lorem_cipher_cbc[] = 
    "\x7C\xC4\xE2\xFC\x58\x08\x36\x5D\xED\xD8\xC3\xB6\x94\x83\xC2\xD4"
    "\xD3\x7E\x63\x67\xB7\x84\xA5\x0E\x15\xA2\x2A\xC2\x47\xAA\x04\x96"
    "\x99\x94\x51\xE7\x83\xF0\xF4\xD2\x09\x0C\x9C\x03\x24\xE3\x7F\xE7"
    "\x35\xD6\xFD\xF5\x18\x7D\x64\xE5\xE1\x6D\x4E\xE4\x43\x73\x55\x83"
    "\xF6\x40\xA7\xF4\x34\x82\x98\xEB\x3F\xE5\x7B\x9D\x53\x1B\x7F\x02"
    "\xB8\x69\x5B\xAE\x17\x87\xBD\xA6\x6C\x53\x24\xAE\xB2\x51\xEB\x59"
    "\x66\xEF\xC3\x1F\xA7\xAE\x9A\xF6\x8F\xF9\xFC\x34\x40\x66\x28\x11"
    "\xC1\x6D\xB6\x65\x32\x5E\x65\x0F\x7A\x9D\xC7\xC1\x7E\x8C\xDA\xBC"
    "\x56\x97\xA6\xC8\x59\xBF\xF8\xA8\xA1\x1F\xB4\x4E\x27\x71\x3B\x60"
    "\x2B\xFC\x89\xD4\x2A\x6A\x7B\x87\x16\xD5\xF1\x02\xC8\x50\xA1\x93"
    "\x0F\x7C\x03\xC0\x4C\xE6\xE1\x36\x72\x4F\xBF\x92\x2B\xDA\x20\xE0"
    "\x69\xE5\xF9\xBF\xB1\x5F\xB2\xBD\xAD\x19\x22\xAE\x92\x78\xFC\xDB"
    "\x6B\x42\x0C\x65\x9C\x18\xD4\x81\xF1\x55\xE2\xE8\xE3\x95\x33\x93"
    "\xEB\x7E\xB1\x00\x4C\x6F\x10\x4E\xD0\xEB\x09\x0B\x57\xD6\xFE\xDE"
    "\xD5\x82\x31\x91\x3F\xFA\x83\xFC\x32\x57\xC3\x05\xCA\x20\x0D\x4C"
    "\x6C\x4A\xDC\xBF\x49\x18\x27\x69\x0A\x33\xFB\x8A\x04\xCF\xCD\x81"
    "\xF0\x3A\x9F\x9F\x88\x2D\xB4\x51\x32\x9D\xFC\xE0\x2F\x72\x52\xB9"
    "\x29\xF1\x1A\x47\x13\x89\xBE\x36\x15\x51\x35\x17\x8E\x80\xFD\xC6"
    "\x4E\x2C\xF4\x78\xA2\xE4\x28\xB6\xBA\xA2\xDA\xA4\x96\xBC\x6C\xFD"
    "\xC0\x2E\xBB\x5E\xBE\x3A\x7C\xD0\x28\xA5\x8B\xB4\xD9\xD7\x4C\xB1"
    "\x5C\xF2\x2C\xA2\xFD\xCC\x34\x19\xA6\x6D\x1B\xF4\xED\x79\x3D\xFB"
    "\x03\xF6\xD9\xD2\xEF\x9B\xDA\xFF\x15\xA2\x10\x95\x59\xF0\x24\xED"
    "\x9F\xFB\x1B\xC4\x31\x16\xD7\xB6\xC1\xA0\xF7\xC0\x93\x18\x50\x58"
    "\x5C\x1F\x47\xC0\xBE\xBE\xF3\xAB\x8F\x07\xFC\x50\x52\x91\x3D\x06"
    "\x9F\x54\x83\xB6\x46\xDC\xB8\xF4\x96\x4A\x38\x8C\xEA\xC1\x04\x0F"
    "\x5A\x7E\x3B\x86\x50\xB0\x42\x73\xEF\x75\x5C\xDD\x47\x26\xC2\x56"
    "\x3F\x76\x82\xA1\xEE\x25\xD1\xFB\x17\x8A\x24\xD8\x58\xB8\xBE\x43"
    "\xEE\x1D\x7C\xA3\xA6\x62\xFF\x67\x60\xFE\xCB\x77\x7C\xDB\xCA\x4B";

#if defined(WOLFSSL_DES_ECB)
static ALIGN4 const uint8_t lorem_cipher_ecb[] = 
    "\x80\xF7\x6C\x2C\xFA\x99\xB2\xDC\xBE\x31\x31\xCB\xD7\x38\x04\x96"
    "\x56\x3A\x71\x3C\xCE\x0E\x96\x71\xE1\xB9\x03\x46\x9F\xB9\xF5\x67"
    "\xCB\x7A\x03\xA8\x28\x68\xA6\x28\x66\xE3\xEA\x74\xB1\xE8\x6B\xE9"
    "\x96\xC2\x54\x69\x85\x21\xB0\x07\xAA\x39\xCF\xEA\xC9\x73\x9E\x5C"
    "\xEE\x30\xEE\x48\x2C\x3B\xD3\x08\xF0\x72\x56\x2E\xA1\xD1\xE8\xC1"
    "\xF2\x2E\x0D\x52\x61\xC1\x7A\x79\x19\x4D\x35\xB5\x2F\x6D\x51\xA1"
    "\x7A\x28\x71\x09\xA8\x44\xF3\xBB\x5B\xC7\x77\x84\xEC\xE1\xE4\xDB"
    "\xDD\x50\x5B\x1C\xA2\x3C\x12\x43\x8B\x6A\x10\x60\x75\xF4\xE8\xF6"
    "\xB3\x0C\xC5\x51\x7D\xAC\x6E\x8C\x9A\xC1\xC9\x2C\x83\x18\x09\xF4"
    "\x10\x35\x5E\x7D\xCB\x55\x32\x88\x4E\x69\xE7\x60\x78\x90\x59\xCC"
    "\x40\xFD\x23\x29\x46\xB2\xCE\x4C\x6C\xEB\x75\xBD\x5D\x3D\xEA\xC8"
    "\x50\x03\x76\xD2\x11\x63\xEA\x8B\xB5\x09\xF8\xCD\x9B\x48\x07\xBA"
    "\xBF\x80\xB7\xDA\x1A\x8A\xC5\x94\x76\x9D\x59\xDA\x47\xDA\xC4\x31"
    "\x79\x50\x42\xCE\x92\x6B\xF2\x69\xDE\x3C\x51\x61\x31\xF6\xE5\xF6"
    "\x07\x63\xD6\xC4\x7F\xE5\x90\x03\xE8\x8D\x6E\xC2\x07\x2F\xD4\x73"
    "\xCF\x7A\x61\xB9\x10\x5F\xF8\x6B\x8E\xAF\x83\x37\x10\x38\xCA\x5A"
    "\x0D\x25\x82\xE8\x01\x0D\xDF\xE9\xD8\xE0\xBD\x29\xC5\x79\x10\xF7"
    "\x9A\x0F\x0E\x68\x17\xE1\xEC\x63\x75\x74\x85\xBA\x23\xAE\x2F\x7A"
    "\x6A\xEF\x8E\x5B\x2D\xE3\xAD\x66\x57\xDA\xEC\x7C\x19\x70\x21\x2D"
    "\x13\xBF\x00\x39\xC3\xB4\x9C\x1E\x9B\x6B\xD7\x0B\xC1\xFD\x5D\x22"
    "\x06\x94\x17\xFC\x6B\xD2\xDF\x62\xB9\xC1\xD4\xA0\x4B\x52\x80\x49"
    "\x86\x3C\x8C\x1F\x0B\x73\x9B\xE4\xC2\xB9\xCE\x89\x7B\xB2\x72\xA2"
    "\x9C\x00\x2D\xF5\x6A\x18\x36\x48\x54\x2A\x61\x46\x2F\x13\x63\xF4"
    "\x0D\x3D\x00\x6C\x8D\x74\xD4\xC0\xE5\xE1\x54\xF6\x98\x91\x26\xE6"
    "\x9E\xCB\xB7\x8A\x50\x12\xB4\x40\x07\x02\xEE\x1F\x46\xF3\xDE\xF5"
    "\x57\xE1\x8B\x5C\x88\x92\xB6\x1A\xDA\x04\xA7\xF6\x57\xDD\x4D\xAB"
    "\x61\x1E\xEB\xCB\x94\x9D\x9A\x6A\x14\x8A\x5C\xF9\x20\x12\xED\x49"
    "\xA2\x90\xE8\x62\x34\xFD\x6E\xC8\x39\x0F\x9F\x9C\xA1\xCE\xB0\xB3";
#endif // DES_ECB
#endif // !NO_DES3

/*************************************************************
 * Golden data definitions.
 *************************************************************/
static const uint8_t threedes_key[] = "1234567890123456ABCDEFGH";
static __attribute__((unused)) const cryptoST_testDetail_t test_item[] =
{
    // ////// CBC MODE /////////////////////////////////
    {
        .technique = ET_DES3,
        .mode = EM_CBC,
        .recommendedRepetitions = 1000,

        .source = __BASE_FILE__ "(" BASE_LINE ")",
        .pedigree = threedes_description,
        .rawData = &qbf,
        .io.sym.in.key = { .length = 24, .data = threedes_key },
        .io.sym.in.ivNonce.length = 8,
        .io.sym.in.ivNonce.data = (ALIGN4 const uint8_t*)"12345678",
        .io.sym.out.cipher = {
            .length = (6*8),
            .data = (ALIGN4 const uint8_t[]){
                "\xE6\xB6\x34\x5F\x10\x15\x38\x02"
                "\x84\x48\x1B\xBC\xFF\xB9\x05\x2A"
                "\x22\x7F\xC1\x4F\x73\x07\x2E\x8D"
                "\x50\x07\xAC\x01\xDF\xED\xCC\x2B"
                "\xCB\xCE\x1E\xB1\x4A\x95\xED\x60"
                "\xBA\x1A\x44\x70\x0F\x4E\x18\xAE" },
        },
    },
    {
        .technique = ET_DES3,
        .mode = EM_CBC,
        .recommendedRepetitions = 1000,

        .source = __BASE_FILE__ "(" BASE_LINE ")",
        .pedigree = threedes_description,
        .rawData = &qbf,
        .io.sym.in.key = { .length = 24, .data = threedes_key },
        .io.sym.in.ivNonce.length = 8,
        .io.sym.in.ivNonce.data = (ALIGN4 const uint8_t*)"23456789",
        .io.sym.out.cipher = {
            .length = 48,
            .data = (ALIGN4 const uint8_t[]){
                "\x5B\xF2\x96\x57\xE6\x06\x4E\xB9"
                "\x9E\x52\xAC\xC8\xE3\xA6\x80\x8A"
                "\x76\x1A\x86\xA7\xEE\x85\xC2\x5C"
                "\x32\x70\x22\xC3\x0D\x93\x9D\x3A"
                "\x8A\x41\xA9\xCD\x42\x68\x9A\xA4"
                "\x48\x1F\xF2\x01\x55\x81\x6A\x8C" },
        },
    },
    {
        .technique = ET_DES3,
        .mode = EM_CBC,
        .recommendedRepetitions = 1000,

        .source = __BASE_FILE__ "(" BASE_LINE ")",
        .pedigree = threedes_description,
        .rawData = &lorem,
        .io.sym.in.key = { .length = 24, .data = threedes_key },
        .io.sym.in.ivNonce.length = 8,
        .io.sym.in.ivNonce.data = (ALIGN4 const uint8_t*)"12345678",
        .io.sym.out.cipher = {
            .length = (28*16),
            .data = lorem_cipher_cbc,
        },
    },
    // ////// ECB MODE /////////////////////////////////
#if defined(WOLFSSL_DES_ECB)
/* Note: at CRYPTO=3.5.0 this may not be set in configuration.h
 * by Harmony3 and must be added after generating code.
 * */
    {
        .technique = ET_DES3,
        .mode = EM_ECB,
        .recommendedRepetitions = 1000,

        .source = __BASE_FILE__ "(" BASE_LINE ")",
        .pedigree = threedes_description,
        .rawData = &qbf,
        .io.sym.in.key = { .length = 24, .data = threedes_key },
        // .io.sym.in.ivNonce.length = 8,
        // .io.sym.in.ivNonce.data = (const uint8_t*)"12345678",
        .io.sym.out.cipher = {
            .length = (6*8),
            .data = (ALIGN4 const uint8_t[]){
    "\x13\xD4\xD3\x54\x94\x93\xD2\x87\x0F\x93\xC3\xE0\x81\x2A\x06\xDE"
    "\x46\x7E\x1F\x9C\x0B\xFB\x16\xC0\x70\xED\xE5\xCA\xBB\xD3\xCA\x62"
    "\xF2\x17\xA7\xAE\x8D\x47\xF2\xC7\x19\x8F\xF3\x91\x62\xEC\xEC\x94" },
        },
    },
    {
        .technique = ET_DES3,
        .mode = EM_ECB,
        .recommendedRepetitions = 1000,

        .source = __BASE_FILE__ "(" BASE_LINE ")",
        .pedigree = threedes_description,
        .rawData = &eee,
        .io.sym.in.key = { .length = 24, .data = threedes_key },
        // .io.sym.in.ivNonce.length = 8,
        // .io.sym.in.ivNonce.data = (const uint8_t*)"12345678",
        .io.sym.out.cipher = {
            .length = (7*8),
            .data = (ALIGN4 const uint8_t[]){
    "\xDB\x5E\x0A\x57\x6B\x31\x6D\x78\xDB\x5E\x0A\x57\x6B\x31\x6D\x78"
    "\xDB\x5E\x0A\x57\x6B\x31\x6D\x78\xDB\x5E\x0A\x57\x6B\x31\x6D\x78"
    "\xDB\x5E\x0A\x57\x6B\x31\x6D\x78\xDB\x5E\x0A\x57\x6B\x31\x6D\x78"
    "\x9F\xA9\xB6\x06\x88\xE2\x01\xC2" },
        },
    },
    {
        .technique = ET_DES3,
        .mode = EM_ECB,
        .recommendedRepetitions = 1000,

        .source = __BASE_FILE__ "(" BASE_LINE ")",
        .pedigree = threedes_description,
        .rawData = &lorem,
        .io.sym.in.key = { .length = 24, .data = threedes_key },
        // .io.sym.in.ivNonce.length = 8,
        // .io.sym.in.ivNonce.data = (const uint8_t*)"12345678",
        .io.sym.out.cipher = {
            .length = (28*16),
            .data = lorem_cipher_ecb,
        },
    },
#endif // DES_ECB
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
    return &test_item[0];
}

static const cryptoST_testDetail_t * nextTest(const cryptoST_testDetail_t * old)
{
    // Assume that if the pointer is in range, that it is legitimate.
    if (old < test_item) 
        ;
    
    // We know that the final (illegitimate) entry has a null technique,
    // but we still need to check if "old" is _way_ out of bounds.
    else if ((++old >= &test_item[test_item_count])
            || (ET_NONE == old->technique))
        ;
    else return old;

    return NULL;
}

#define openData_func      NULL
#define closeData_func     NULL

/*************************************************************
 * Declaration of the test manager API
 * Obligatory entry points for executing a test
 *************************************************************/
cryptoST_testAPI_t const microchip_des3 =
{
    .name = "DES3_" DATA_PACKAGE_NAME,
    .openData = openData_func,
    .firstTest = firstTest,
    .nextTest = nextTest,
    .closeData = closeData_func,
};

