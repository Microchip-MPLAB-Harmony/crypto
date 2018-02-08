/**************************************************************************
  Crypto Framework Library Source

  Company:
    Microchip Technology Inc.

  File Name:
    sha_pic32c.c

  Summary:
    Crypto Framework Libarary source for cryptographic functions.

  Description:
    This source file contains functions that make up the Cryptographic
	Framework Library for PIC32 families of Microchip microcontrollers.
**************************************************************************/

//DOM-IGNORE-BEGIN
/******************************************************************************
File Name:  sha.c
Copyright � 2016 released Microchip Technology Inc.  All rights reserved.

Microchip licenses to you the right to use, modify, copy and distribute
Software only when embedded on a Microchip microcontroller or digital signal
controller that is integrated into your product or third party product
(pursuant to the sublicense terms in the accompanying license agreement).

You should refer to the license agreement accompanying this Software for
additional information regarding your rights and obligations.

SOFTWARE AND DOCUMENTATION ARE PROVIDED ?AS IS? WITHOUT WARRANTY OF ANY KIND,
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




#ifdef HAVE_CONFIG_H
    #include "config.h"
#endif
#include "system_config.h"

#include "crypto/src/settings.h"

#if !defined(NO_SHA)

#include "crypto/src/sha.h"
#include "system_definitions.h"



int wc_InitSha(Sha* sha)
{
    /* Enable ICM if not already */
    uint32_t PmcBit = 1u << (ID_ICM - 32);
    if ((_PMC_REGS->PMC_PCSR1.w & PmcBit) != PmcBit)
    {
        _PMC_REGS->PMC_PCER1.w = PmcBit;
    }

    /* ICM does the SHA work */
    sha->icm_descriptor.cfg.reg = 0x0;
    sha->icm_descriptor.cfg.bit.is_end_mon = 1;

    sha->digest[0] = 0x01234567;
    sha->digest[1] = 0x89ABCDEF;
    sha->digest[2] = 0xFEDCBA98;
    sha->digest[3] = 0x76543210;
    sha->digest[4] = 0xF0E1D2C3;

    sha->total_len = 0;

    return 0;
}



static int32_t Sha1Process(Sha *sha, const uint8_t *input, word32 length)
{
    sha->icm_descriptor.start_addr = (uint32_t)input;

    /* Transfer size = (tran_size + 1) * 512bits */
    sha->icm_descriptor.tran_size =  (length >> 6) - 1;

    _ICM_REGS->ICM_DSCR.w = (uint32_t)&sha->icm_descriptor;

    /* digest must be 128 aligned */
    _ICM_REGS->ICM_HASH.w = (uint32_t)sha->digest;

    /* configured so initial hash digest is auto-loaded */
    _ICM_REGS->ICM_CFG.w = ICM_CFG_SLBDIS_Msk
                 | ICM_CFG_BBC(0)
                 | ICM_CFG_UALGO_SHA1
                 | ICM_CFG_UIHASH_Msk;

    _ICM_REGS->ICM_UIHVAL[0].w = sha->digest[0];
    _ICM_REGS->ICM_UIHVAL[1].w = sha->digest[1];
    _ICM_REGS->ICM_UIHVAL[2].w = sha->digest[2];
    _ICM_REGS->ICM_UIHVAL[3].w = sha->digest[3];
    _ICM_REGS->ICM_UIHVAL[4].w = sha->digest[4];

    /* memory barrier */
    __DMB();

    /* enable the ICM and wait ICM CTRL is write only - don't OR it */
    _ICM_REGS->ICM_CTRL.w = ICM_CTRL_ENABLE_Msk;
    while (!(_ICM_REGS->ICM_ISR.w & ICM_ISR_RHC_Msk))
    {
        /* wait - when finished digest will be updated */
    }

    return 0;
}



/* From the crypto DataAdd */
int wc_ShaUpdate(Sha* sha, const byte* data, word32 len)
{
    uint32_t fill;
    uint32_t left;
    uint32_t result = 0;

    left = sha->total_len & 0x3F;
    fill = SHA_BLOCK_SIZE - left;
    sha->total_len += len;

    if (left && len >= fill)
    {
        memcpy((void *)(sha->buffer + left), data, fill);
        result = Sha1Process(sha, sha->buffer, SHA_BLOCK_SIZE);
        data += fill;
        len -= fill;
        left = 0;
    }

    if (len >= SHA_BLOCK_SIZE)
    {
        result = Sha1Process(sha, data, len & 0xFFFFFFC0);
        data += (len & 0xFFFFFFC0);
        len &= 0x3F;
    }

    if( len > 0 )
    {
        memcpy((void *)(sha->buffer + left), data, len);
    }

    return result;
}




static const uint8_t sha_padding[SHA_BLOCK_SIZE] = {
    0x80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
       0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
       0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
       0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };



int wc_ShaFinal(Sha* sha, byte* hash)
{
    uint32_t last;
    uint8_t  padn;
    uint8_t  msg_len[8];

    /* Get the number of bits */
    /* create the message bit length block */
    uint64_t total_bits = sha->total_len << 3;
    msg_len[0] = (uint8_t)(total_bits >> 56);
    msg_len[1] = (uint8_t)(total_bits >> 48);
    msg_len[2] = (uint8_t)(total_bits >> 40);
    msg_len[3] = (uint8_t)(total_bits >> 32);
    msg_len[4] = (uint8_t)(total_bits >> 24);
    msg_len[5] = (uint8_t)(total_bits >> 16);
    msg_len[6] = (uint8_t)(total_bits >>  8);
    msg_len[7] = (uint8_t)(total_bits);

    last = sha->total_len & 0x3F;
    padn = (last < SHA_PAD_SIZE) ? (SHA_PAD_SIZE - last) : (120 - last);

    wc_ShaUpdate(sha, sha_padding, padn);

    wc_ShaUpdate(sha, msg_len, 8);

    memcpy(hash, sha->digest, SHA_DIGEST_SIZE);

    return wc_InitSha(sha);
}



#endif /* NO_SHA */
