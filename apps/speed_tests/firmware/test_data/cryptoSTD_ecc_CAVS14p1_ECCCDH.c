/*******************************************************************************
  Crypto Speed Test Data File

  Company:
    Microchip Technology Inc.

  File Name:
    cryptoSTD_ecc_CAVS14p1_ECCCDH

  Summary:
   Given data from the SP 800-56A Elliptic Curve Cryptography Cofactor 
   Diffie-Hellman (ECC CDH) Primitive Testing suite as described in
   ecccdhvs.pdf (ECC_CDH_PrimitiveVS_04122011, 12 April 2011 10:35:35am)
   with data from files found in the companion ecccdhtestvectors.zip.

  Description:
   Known-good data for generation of public/private key pairs for ECC encryption. 
   See also the pdf file NIST.SP.800-56Ar2.pdf (16 April 2018). The applied 
   algorithm is the Elliptic Curve Cryptography Cofactor 
   Diffie-Hellman (ECC CDH) Primitive (ibid. section 5.7.1.2).
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

#include <stdint.h>
#include "configuration.h"
#include <wolfssl/wolfcrypt/settings.h>
#include "./cryptoSpeedTestData.h"
#include "cryptoST/cryptoSTE_print.h" // for BASE_LINE

#define DATA_PACKAGE_NAME "CAVS14p1"
#define ALIGN4 __attribute__((aligned(4)))
#define DATA_CHAR ALIGN4 const uint8_t

static const CPU_CHAR source[] = "KAS_ECC_CDH_PrimitiveTest.txt";
static const CPU_CHAR pedigree[] = "NIST suite SP 800-56A (ECC_CDHVS)";
static const CPU_CHAR description[] = DATA_PACKAGE_NAME;

/*************************************************************
 * Raw (given) data definitions.
 *************************************************************/
/* Transliterate the data from the test suite without regard
 * to input or output designations.
 *    CAVS = values associated with the remote host
 *    IUT = values associated with the implementation under test
 *    QCAVS: public key (x,y)
 *        d: random integer, private key (explicitly defined here)
 *     QIUT: generated public key
 *        Z: conversion of xp per Appendix C.2 (ibid.)
 *           in our case, big-endian
 * */
typedef struct ECCCDH_P256_s
{
    const ALIGN4 uint8_t QCAVSx[32];
    const ALIGN4 uint8_t QCAVSy[32];
    const ALIGN4 uint8_t   dIUT[32];
    const ALIGN4 uint8_t  QIUTx[32];
    const ALIGN4 uint8_t  QIUTy[32];
    const ALIGN4 uint8_t   ZIUT[32];
} ECCCDH_P256_t;

const ECCCDH_P256_t CAVS14p1_P256[] =
{
    { // COUNT = 0
        .QCAVSx = {
0x70, 0x0c, 0x48, 0xf7, 0x7f, 0x56, 0x58, 0x4c, 0x5c, 0xc6, 0x32, 0xca, 0x65, 0x64, 0x0d, 0xb9, 
0x1b, 0x6b, 0xac, 0xce, 0x3a, 0x4d, 0xf6, 0xb4, 0x2c, 0xe7, 0xcc, 0x83, 0x88, 0x33, 0xd2, 0x87},
        .QCAVSy = {
0xdb, 0x71, 0xe5, 0x09, 0xe3, 0xfd, 0x9b, 0x06, 0x0d, 0xdb, 0x20, 0xba, 0x5c, 0x51, 0xdc, 0xc5, 
0x94, 0x8d, 0x46, 0xfb, 0xf6, 0x40, 0xdf, 0xe0, 0x44, 0x17, 0x82, 0xca, 0xb8, 0x5f, 0xa4, 0xac},
          .dIUT = {
0x7d, 0x7d, 0xc5, 0xf7, 0x1e, 0xb2, 0x9d, 0xda, 0xf8, 0x0d, 0x62, 0x14, 0x63, 0x2e, 0xea, 0xe0, 
0x3d, 0x90, 0x58, 0xaf, 0x1f, 0xb6, 0xd2, 0x2e, 0xd8, 0x0b, 0xad, 0xb6, 0x2b, 0xc1, 0xa5, 0x34},
         .QIUTx = {
0xea, 0xd2, 0x18, 0x59, 0x01, 0x19, 0xe8, 0x87, 0x6b, 0x29, 0x14, 0x6f, 0xf8, 0x9c, 0xa6, 0x17, 
0x70, 0xc4, 0xed, 0xbb, 0xf9, 0x7d, 0x38, 0xce, 0x38, 0x5e, 0xd2, 0x81, 0xd8, 0xa6, 0xb2, 0x30},
         .QIUTy = {
0x28, 0xaf, 0x61, 0x28, 0x1f, 0xd3, 0x5e, 0x2f, 0xa7, 0x00, 0x25, 0x23, 0xac, 0xc8, 0x5a, 0x42, 
0x9c, 0xb0, 0x6e, 0xe6, 0x64, 0x83, 0x25, 0x38, 0x9f, 0x59, 0xed, 0xfc, 0xe1, 0x40, 0x51, 0x41},
          .ZIUT = {
0x46, 0xfc, 0x62, 0x10, 0x64, 0x20, 0xff, 0x01, 0x2e, 0x54, 0xa4, 0x34, 0xfb, 0xdd, 0x2d, 0x25, 
0xcc, 0xc5, 0x85, 0x20, 0x60, 0x56, 0x1e, 0x68, 0x04, 0x0d, 0xd7, 0x77, 0x89, 0x97, 0xbd, 0x7b},
    },
};


/*************************************************************
 * Formal test-data definitions.
 *************************************************************/
#define vector_template(mode,size)  {  \
        .name = vector_set_##mode,  \
        .source = source,           \
        .pedigree = pedigree,       \
        .description = description, \
        .vector.length = (size)/8,  \
        .vector.data = ((void*)0) }

const CPU_CHAR vector_set_P256[] = "ECCCDH_vectors_P";
const cryptoST_testVector_t vectors_P256[] =
{
    vector_template(P256, 256),
};

/*************************************************************
 * Inputs and golden data result definitions.
 * * EM_ECC_ # # mode, *  
 *************************************************************/
#define item_template(et_mode,index) {  \
    .technique = ET_ECC_CDH,            \
    .mode = EM_CTR,                     \
    .recommendedRepetitions = 100,      \
    .source = __BASE_FILE__ "(" BASE_LINE ")",  \
    .pedigree = pedigree,                       \
    .rawData = &vectors_##et_mode[0],           \
    .io.ecc.in.remotePU.x = CAVS14p1_##et_mode[(index)].QCAVSx,   \
    .io.ecc.in.remotePU.x = CAVS14p1_##et_mode[(index)].QCAVSy,   \
    .io.ecc.in.d          = CAVS14p1_##et_mode[(index)].dIUT,     \
    .io.ecc.out.localPR.x = CAVS14p1_##et_mode[(index)].QIUTx,    \
    .io.ecc.out.localPR.y = CAVS14p1_##et_mode[(index)].QIUTy,    \
    .io.ecc.out.z         = CAVS14p1_##et_mode[(index)].ZIUT }

static const cryptoST_testDetail_t test_item[] =
{
    item_template(P256,0),
    {}
};

#define test_item_count (ALENGTH(test_item))

/*************************************************************
 * Helper functions
 *************************************************************/

/*************************************************************
 * API handlers
 *************************************************************/
/* This handles the case with the empty test_item. */ 
static const cryptoST_testDetail_t * nextTest
                (const cryptoST_testDetail_t * old)
{
    if (old >= test_item) 
    {
        old++; // repurpose: this is now "new"
        if (old < &test_item[test_item_count-1])
            return old;
    }
    return NULL;
}

static const cryptoST_testDetail_t * firstTest(void)
{
    return ((test_item_count > 0)
         && (ET_NONE != test_item[0].technique))?
        test_item : 0;
}

__attribute__((used))
static const char * openError(void)
{ return "FIXME: this data set is not in DER format and will produce errors if used"; }

/*************************************************************
 * Declaration of the test manager API
 * Obligatory entry points for executing a test
 *************************************************************/
cryptoST_testAPI_t const CAVS14p1_ECCCDH =
{
#ifndef ALT_ECC_SIZE
    .name = "RSA_ALT" DATA_PACKAGE_NAME,
#else    
    .name = "RSA_" DATA_PACKAGE_NAME,
#endif
    .openData = ((void*)0), // openError, // 
    .firstTest = firstTest,
    .nextTest = nextTest,
    .closeData = ((void*)0),
};
