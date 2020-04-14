/*******************************************************************************
  Crypto Speed Test Source File

  Company:
    Microchip Technology Inc.

  File Name:
    cryptoSTE_utility.c

  Summary:
    Library of useful tools.

  Description:
    Library of cryptoSTE tools.
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

/* Mapping function for hash types from WC to MCHP.
*/
#include "../../test_data/cryptoSpeedTestData.h"
#include <wolfssl/wolfcrypt/types.h>
enum wc_HashType cryptoSTE_get_wcHashType(EncryptTechnique_t mchp_type)
{
    register enum wc_HashType answer = ET_UNKNOWN;

    switch(mchp_type)
    {
    default:
    case ET_NONE:
        answer = WC_HASH_TYPE_NONE;
        break;
    case ET_MD2:
        answer = WC_HASH_TYPE_MD2;
        break;
    case ET_MD3:
        // answer = ;
        break;
    case ET_MD4:
        answer = WC_HASH_TYPE_MD4;
        break;
    case ET_MD5:
        answer = WC_HASH_TYPE_MD5;
        break;
    case ET_MD6:
        // answer = ;
        break;
    case ET_SHA_128: /* a.k.a. SHA or SHA1 */
        answer = WC_HASH_TYPE_SHA;
        break;
    case ET_SHA_224:
        answer = WC_HASH_TYPE_SHA224;
        break;
    case ET_SHA_256:
        answer = WC_HASH_TYPE_SHA256;
        break;
    case ET_SHA_384:
        answer = WC_HASH_TYPE_SHA384;
        break;
    case ET_SHA_512:
        answer = WC_HASH_TYPE_SHA512;
        break;
    }
    /* Not accounted for :(
    WC_HASH_TYPE_MD5_SHA = 9,
    WC_HASH_TYPE_SHA3_224 = 10,
    WC_HASH_TYPE_SHA3_256 = 11,
    WC_HASH_TYPE_SHA3_384 = 12,
    WC_HASH_TYPE_SHA3_512 = 13,
    WC_HASH_TYPE_BLAKE2B = 14,
    WC_HASH_TYPE_BLAKE2S = 15,
    */
    return answer;
}
