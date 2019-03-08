/**************************************************************************
  Crypto Framework Library Source

  Company:
    Microchip Technology Inc.

  File Name:
    crypt_sha_sam6156.c

  Summary:
    Crypto Framework Library source for cryptographic functions.

  Description:
    This source file contains functions that make up the Cryptographic
	Framework Library for SAMA5D2 families of Microchip microcontrollers.
**************************************************************************/

//DOM-IGNORE-BEGIN
/*****************************************************************************
 Copyright (C) 2019 Microchip Technology Inc. and its subsidiaries.

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

/** \addtogroup sha_module Working with SHA
 * \ingroup peripherals_module
 * The SHA driver provides the interface to configure and use the SHA
 * peripheral.
 * \n
 *
 * The Secure Hash Algorithm (SHA) module requires a padded message
 * according to FIPS180-2 specification. The first block of the
 * message must be indicated to the module by a specific command. The
 * SHA module produces a N-bit message digest each time a block is
 * written and processing period ends. N is 160 for SHA1, 224 for
 * SHA224, 256 for SHA256, 384 for SHA384, 512 for SHA512.
 *
 * To Enable a SHA encryption and decrypt,the user has to follow these
 * few steps:
 * <ul>
 * <li> Configure SHA algorithm mode, key mode, start mode and
 * operation mode by sha_configure(). </li>
 * <li> Set sha_first_block() to indicates that the next block to
 * process is the first one of a message.</li>
 * <li> Input data for encryption by sha_set_input(). </li>
 * <li> To start the encryption process with sha_start()</li>
 * <li> To get the encryption result by sha_get_output() </li>
 * </ul>
 *
 * For more accurate information, please look at the SHA section of the
 * Datasheet.
 *
 * Related files :\n
 * \ref sha.c\n
 * \ref sha.h\n
 */
/*@{*/
/*@}*/

/**
 * \file
 *
 * Implementation of Secure Hash Algorithm (SHA)
 *
 */

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include <string.h>
#include <stdio.h>

#include "packs/ATSAMA5D27_DFP/atsama5d27.h"
#include "packs/ATSAMA5D27_DFP/component/sha.h"
#include "crypto/src/crypt_sha_hw.h"

#ifdef NO_INLINE
    #include "crypto/src/misc.h"
#else
    #define WOLFSSL_MISC_INCLUDED
    #include "crypto/src/misc.c"
#endif


typedef struct {
    enum sha_algo algo;
    uint32_t      blockBytes;
    uint32_t      digestBytes;
}algoBytes;

/* must be in same order as enum sha_algo */
algoBytes shaAlgoBytes[10] =
{
    {SHA_1_ALGO,        CRYPT_SHA1_BLOCK_BYTES,   CRYPT_SHA1_DIGEST_BYTES},
    {SHA_256_ALGO,      CRYPT_SHA256_BLOCK_BYTES, CRYPT_SHA256_DIGEST_BYTES},
    {SHA_384_ALGO,      CRYPT_SHA384_BLOCK_BYTES, CRYPT_SHA384_DIGEST_BYTES},
    {SHA_512_ALGO,      CRYPT_SHA512_BLOCK_BYTES, CRYPT_SHA512_DIGEST_BYTES},
    {SHA_224_ALGO,      CRYPT_SHA224_BLOCK_BYTES, CRYPT_SHA224_DIGEST_BYTES},
    {HMAC_SHA_1_ALGO,   CRYPT_SHA1_BLOCK_BYTES,   CRYPT_SHA1_DIGEST_BYTES},
    {HMAC_SHA_256_ALGO, CRYPT_SHA256_BLOCK_BYTES, CRYPT_SHA256_DIGEST_BYTES},
    {HMAC_SHA_384_ALGO, CRYPT_SHA384_BLOCK_BYTES, CRYPT_SHA384_DIGEST_BYTES},
    {HMAC_SHA_512_ALGO, CRYPT_SHA512_BLOCK_BYTES, CRYPT_SHA512_DIGEST_BYTES},
    {HMAC_SHA_224_ALGO, CRYPT_SHA224_BLOCK_BYTES, CRYPT_SHA224_DIGEST_BYTES}
};

/*----------------------------------------------------------------------------
 *        Exported functions
 *----------------------------------------------------------------------------*/

void sha_set_input(const uint8_t* data, int len)
{
	int i;
	int32_t value;

	for (i = 0; i < (len / 4) && i < 32; i++) {
		memcpy(&value, &data[i * 4], 4);
		if (i < 16)
			SHA_REGS->SHA_IDATAR[i] = value;
		else
			SHA_REGS->SHA_IODATAR[i - 16] = value;
	}
}

void sha_get_output(uint8_t* data, int len)
{
	int i;
	int32_t value;

	for (i = 0; i < (len / 4) && i < 16; i++) {
		value = SHA_REGS->SHA_IODATAR[i];
		memcpy(&data[i * 4], &value, 4);
	}
}

int CRYPT_SHA1_InitSha(crypt_sha_hw_descriptor* sha, void* heap, int devId)
{
    sha->sha_descriptor.algo = SHA_1_ALGO;
    crypt_InitSha(sha);
    return 0;
}

int CRYPT_SHA256_InitSha(crypt_sha_hw_descriptor* sha, void* heap, int devId)
{
    sha->sha_descriptor.algo = SHA_256_ALGO;
    crypt_InitSha(sha);
    return 0;
}

int CRYPT_SHA224_InitSha(crypt_sha_hw_descriptor* sha, void* heap, int devId)
{
    sha->sha_descriptor.algo = SHA_224_ALGO;
    crypt_InitSha(sha);
    return 0;
}

int CRYPT_SHA384_InitSha(crypt_sha_hw_descriptor* sha, void* heap, int devId)
{
    sha->sha_descriptor.algo = SHA_384_ALGO;
    crypt_InitSha(sha);
    return 0;
}

int CRYPT_SHA512_InitSha(crypt_sha_hw_descriptor* sha, void* heap, int devId)
{
    sha->sha_descriptor.algo = SHA_512_ALGO;
    crypt_InitSha(sha);
    return 0;
}

int CRYPT_HMAC_SHA1_InitSha(crypt_sha_hw_descriptor* sha, void* heap, int devId)
{
    sha->sha_descriptor.algo = HMAC_SHA_1_ALGO;
    crypt_InitSha(sha);
    return 0;
}

int CRYPT_HMAC_SHA256_InitSha(crypt_sha_hw_descriptor* sha, void* heap, int devId)
{
    sha->sha_descriptor.algo = HMAC_SHA_256_ALGO;
    crypt_InitSha(sha);
    return 0;
}

int CRYPT_HMAC_SHA224_InitSha(crypt_sha_hw_descriptor* sha, void* heap, int devId)
{
    sha->sha_descriptor.algo = HMAC_SHA_224_ALGO;
    crypt_InitSha(sha);
    return 0;
}

int CRYPT_HMAC_SHA384_InitSha(crypt_sha_hw_descriptor* sha, void* heap, int devId)
{
    sha->sha_descriptor.algo = HMAC_SHA_384_ALGO;
    crypt_InitSha(sha);
    return 0;
}

int CRYPT_HMAC_SHA512_InitSha(crypt_sha_hw_descriptor* sha, void* heap, int devId)
{
    sha->sha_descriptor.algo = HMAC_SHA_512_ALGO;
    crypt_InitSha(sha);
    return 0;
}

void crypt_InitSha(crypt_sha_hw_descriptor* sha)
{
    uint32_t sha_mr_mode = 0;
    
    /* Enable clock for SHA */
    uint32_t id;
    if (ID_SHA >= 32)
      id = ID_SHA - 32;
    else
      id = ID_SHA;
    uint32_t ShaPmcBit = 1u << id;
    if ((PMC_REGS->PMC_PCSR0 & (ShaPmcBit)) != (ShaPmcBit))
    {
        PMC_REGS->PMC_PCER0 = ShaPmcBit;
    }

    /* software reset */
    SHA_REGS->SHA_CR = SHA_CR_SWRST(1);

    sha->sha_descriptor.start_mode = SHA_AUTO_START;
    sha->sha_descriptor.proc_delay = SHA_SHORTEST_RUNTIME;
    sha->sha_descriptor.UIHV = SHA_STD_UIHV;
    sha->sha_descriptor.UIEHV = SHA_STD_UIEHV;
    sha->sha_descriptor.dualbuff = SHA_DUALBUFF_INACTIVE;
    sha->sha_descriptor.hashcheck = SHA_HASHCHECK_NONE;
    sha->sha_descriptor.checkcount = 0; //based on algo 

    sha_mr_mode |= SHA_MR_SMOD(sha->sha_descriptor.start_mode);
    sha_mr_mode |= SHA_MR_PROCDLY(sha->sha_descriptor.proc_delay);
    sha_mr_mode |= SHA_MR_UIHV(sha->sha_descriptor.UIHV);
    sha_mr_mode |= SHA_MR_UIEHV(sha->sha_descriptor.UIEHV);
    sha_mr_mode |= SHA_MR_ALGO(sha->sha_descriptor.algo);
    sha_mr_mode |= SHA_MR_DUALBUFF(sha->sha_descriptor.dualbuff);
    sha_mr_mode |= SHA_MR_CHECK(sha->sha_descriptor.hashcheck);
    sha_mr_mode |= SHA_MR_CHKCNT(sha->sha_descriptor.checkcount);
    
    SHA_REGS->SHA_MR = sha_mr_mode;
}

int CRYPT_SHA_Update(crypt_sha_hw_descriptor* sha, const byte* inptr, word32 byteLen)
{
    uint32_t block = 0;   
    
    /* number of bytes of the message */
    SHA_REGS->SHA_MSR = SHA_MSR_MSGSIZE(byteLen);

    /* remaining number of bytes to write */
    SHA_REGS->SHA_BCR = SHA_BCR_BYTCNT(byteLen);

    /* indicate first block of the message */
    SHA_REGS->SHA_CR = SHA_CR_FIRST(1);
  
    for (block = 0; block < byteLen; block += shaAlgoBytes[sha->sha_descriptor.algo].blockBytes)
    {
        /* Write the block to be processed in the SHA_IDATARx */
        sha_set_input((const uint8_t*)inptr, (int)shaAlgoBytes[sha->sha_descriptor.algo].blockBytes);
        
        /* no need to set SHA_CR.START if in auto mode */
        /* wait for DATRDY in the Interrupt Status register (SHA_ISR) */
        while (!(SHA_REGS->SHA_ISR & SHA_ISR_DATRDY_Msk));
    }
    
    return 0;
}

int CRYPT_SHA_Final(crypt_sha_hw_descriptor* sha, byte* digest)
{
    /* read the message digest in the Output Data registers */
    sha_get_output((uint8_t*)digest, (int)shaAlgoBytes[sha->sha_descriptor.algo].digestBytes);
 
    crypt_InitSha(sha);

    return 0;
}

void CRYPT_SHA_Free(crypt_sha_hw_descriptor* sha)
{
    return;
}
