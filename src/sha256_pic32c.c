/**************************************************************************
  Crypto Framework Library Source

  Company:
    Microchip Technology Inc.

  File Name:
    sha256_pic32c.c

  Summary:
    Crypto Framework Libarary source for cryptographic functions.

  Description:
    This source file contains functions that make up the Cryptographic
	Framework Library for PIC32 families of Microchip microcontrollers.
**************************************************************************/

//DOM-IGNORE-BEGIN
/******************************************************************************
File Name:  sha256_pic32c.c
Copyright © 2016 released Microchip Technology Inc.  All rights reserved.

Microchip licenses to you the right to use, modify, copy and distribute
Software only when embedded on a Microchip microcontroller or digital signal
controller that is integrated into your product or third party product
(pursuant to the sublicense terms in the accompanying license agreement).

You should refer to the license agreement accompanying this Software for
additional information regarding your rights and obligations.

SOFTWARE AND DOCUMENTATION ARE PROVIDED “AS IS” WITHOUT WARRANTY OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF
MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE.
IN NO EVENT SHALL MICROCHIP OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER
CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR
OTHER LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES
INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE OR
CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT OF
SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES
(INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.
*******************************************************************************/
//DOM-IGNORE-END




/* code submitted by raphael.huck@efixo.com */

#ifdef HAVE_CONFIG_H
    #include "config.h"
#endif
#include "system_config.h"
#include "crypto/src/settings.h"

#include "crypto/src/sha256.h"
#include "system_definitions.h"


#if !defined(NO_SHA256)


#include "crypto/src/logging.h"
#include "crypto/src/error-crypt.h"


#ifdef NO_INLINE
    #include "crypto/src/misc.h"
#else
    #include "crypto/src/misc.c"
#endif




int wc_InitSha256(Sha256* sha256)
{
    /* Enable ICM */
    uint32_t PmcBit = 1u << (ID_ICM - 32);
    if ((_PMC_REGS->PMC_PCSR1.w & PmcBit) != PmcBit)
    {
        _PMC_REGS->PMC_PCER1.w = PmcBit;
    }

    sha256->icm_descriptor.cfg.reg = 0x0;
    sha256->icm_descriptor.cfg.bit.is_end_mon = 1;

    /* need initial hash for 256 - byte reversed from internet examples */
    sha256->digest[0] = 0x67E6096A;
    sha256->digest[1] = 0x85AE67BB;
    sha256->digest[2] = 0x72F36E3C;
    sha256->digest[3] = 0x3AF54FA5;
    sha256->digest[4] = 0x7F520E51;
    sha256->digest[5] = 0x8C68059B;
    sha256->digest[6] = 0xABD9831F;
    sha256->digest[7] = 0x19CDE05B;

    sha256->total_len = 0;

    /* memory barrier */
    __DMB();

    return 0;
}



/* length is in bytes */
static int32_t Sha256Process(Sha256* sha256, const uint8_t *input, word32 length)
{
    sha256->icm_descriptor.start_addr = (uint32_t)input;

    /* Transfer size = (tran_size + 1) * 512bits */
    sha256->icm_descriptor.tran_size =  (length >> 6) - 1;

    /* ICM can set up FIPS default starting digest */
    _ICM_REGS->ICM_DSCR.w = (uint32_t)&sha256->icm_descriptor;
    _ICM_REGS->ICM_CFG.w = ICM_CFG_SLBDIS_Msk
                 | ICM_CFG_BBC(0)
                 | ICM_CFG_UALGO_SHA256
                 | ICM_CFG_UIHASH_Msk;

    /* MUST BE ALIGNED at 128! */
    _ICM_REGS->ICM_HASH.w = (uint32_t)sha256->digest;

    _ICM_REGS->ICM_UIHVAL[0].VAL = sha256->digest[0];
    _ICM_REGS->ICM_UIHVAL[1].VAL = sha256->digest[1];
    _ICM_REGS->ICM_UIHVAL[2].VAL = sha256->digest[2];
    _ICM_REGS->ICM_UIHVAL[3].VAL = sha256->digest[3];
    _ICM_REGS->ICM_UIHVAL[4].VAL = sha256->digest[4];
    _ICM_REGS->ICM_UIHVAL[5].VAL = sha256->digest[5];
    _ICM_REGS->ICM_UIHVAL[6].VAL = sha256->digest[6];
    _ICM_REGS->ICM_UIHVAL[7].VAL = sha256->digest[7];

    /* memory barrier - sync all before enable ICM */
    __DMB();

    /* enable the ICM and wait */
    _ICM_REGS->ICM_CTRL.ENABLE = 1;
    while (!(_ICM_REGS->ICM_ISR.RHC))
    {
        /* wait for region to finish hash */
    }

    return 0;
}




/* len is number of bytes - multiple of 64 only */
int wc_Sha256Update(Sha256* sha256, const byte* data, word32 len)
{
    uint32_t fill;
    uint32_t left;
    int result = 0;

    left = sha256->total_len & 0x3F;
    fill = SHA256_BLOCK_SIZE - left;

    sha256->total_len += len;

    /* buffer is not aligned to 512 bits do the first part */
    if (left && len >= fill)
    {
        memcpy((void *)(sha256->buffer + left), data, fill);
        result = Sha256Process(sha256, sha256->buffer, SHA256_BLOCK_SIZE);
        data += fill;
        len -= fill;
        left = 0;
    }

    /* process a full 64 bytes = 512 bits */
    if (len >= SHA256_BLOCK_SIZE)
    {
        result = Sha256Process(sha256, data, len & 0xFFFFFFC0);
        data += (len & 0xFFFFFFC0);
        len &= 0x3F;
    }

    /* fill in a partial buffer */
    if (len > 0)
    {
        memcpy((void *)(sha256->buffer + left), data, len);
    }

    return result;
}




static const uint8_t sha_padding[SHA256_BLOCK_SIZE] = {
    0x80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
       0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
       0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
       0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };


int wc_Sha256Final(Sha256* sha256, byte* hash)
{
    uint32_t last;
    uint8_t  padn;
    uint8_t  msg_len[8];

    /* Get the number of bits */
    /* create the message bit length block */
    uint64_t total_bits = sha256->total_len << 3;
    msg_len[0] = (uint8_t)(total_bits >> 56);
    msg_len[1] = (uint8_t)(total_bits >> 48);
    msg_len[2] = (uint8_t)(total_bits >> 40);
    msg_len[3] = (uint8_t)(total_bits >> 32);
    msg_len[4] = (uint8_t)(total_bits >> 24);
    msg_len[5] = (uint8_t)(total_bits >> 16);
    msg_len[6] = (uint8_t)(total_bits >>  8);
    msg_len[7] = (uint8_t)(total_bits);

    /* pad the last bits with bytes */
    last = sha256->total_len & 0x3F;
    padn = (last < SHA256_PAD_SIZE) ? (SHA256_PAD_SIZE - last) : (120 - last);

    /* future note: Capella will have auto padding with MSGSIZE != 0 */
    wc_Sha256Update(sha256, sha_padding, padn);
    wc_Sha256Update(sha256, msg_len, 8);

    memcpy(hash, (void *)sha256->digest, SHA256_DIGEST_SIZE);

    return wc_InitSha256(sha256);
}



void wc_Sha256Free(Sha256* sha256)
{
    (void)sha256;
}



#endif /* NO_SHA256 */

