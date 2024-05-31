/**************************************************************************
  Crypto Framework Library Source

  Company:
    Microchip Technology Inc.

  File Name:
    CryptoLib_Rng_pb.h

  Summary:
    Crypto Framework Libarary interface file for hardware Cryptography.

  Description:
    This file provides an example for interfacing with the CPKCC module
    on the PIC32CXMxxx device family.
**************************************************************************/

//DOM-IGNORE-BEGIN
/*
Copyright (C) 2024, Microchip Technology Inc., and its subsidiaries. All rights reserved.

The software and documentation is provided by microchip and its contributors
"as is" and any express, implied or statutory warranties, including, but not
limited to, the implied warranties of merchantability, fitness for a particular
purpose and non-infringement of third party intellectual property rights are
disclaimed to the fullest extent permitted by law. In no event shall microchip
or its contributors be liable for any direct, indirect, incidental, special,
exemplary, or consequential damages (including, but not limited to, procurement
of substitute goods or services; loss of use, data, or profits; or business
interruption) however caused and on any theory of liability, whether in contract,
strict liability, or tort (including negligence or otherwise) arising in any way
out of the use of the software and documentation, even if advised of the
possibility of such damage.

Except as expressly permitted hereunder and subject to the applicable license terms
for any third-party software incorporated in the software and any applicable open
source software license terms, no license or other rights, whether express or
implied, are granted under any patent or other intellectual property rights of
Microchip or any third party.
*/
//DOM-IGNORE-END

#ifndef _CRYPTOLIB_RNG_PB_INCLUDED
#define _CRYPTOLIB_RNG_PB_INCLUDED

// Structure definition
typedef struct _PKCL_rng {
               nu1       nu1XKeyBase;        // Pointer to the Input and Output XKEY value of length u2XKeyLength bytes
               nu1       nu1WorkSpace;       // Pointer to the workspace of length 64 bytes
               u2        u2XKeyLength;       // Length in bytes multiple of 4 of XKEY, XSEED[0], XSEED[1]

               nu1       nu1XSeedBase;       // Pointer to the Input value of XSEED[0] and XSEED[1] of length (2*u1XKeyLength + 4)
               nu1       nu1WorkSpace2;		 // Pointer to the WorkSpace2 Of SHA (HICM)
               nu1       nu1QBase;           // Pointer to the Input prime number Q of length 160 bits = 20 bytes
               nu1       nu1RBase;           // (Significant length of 'N' without the padding word)
               u2        u2RLength;          // length of the resulting RNG
               u2        u2X9_31Rounds;
               u2        __Padding1;
               } _CPKCL_RNG, *_PCPKCL_RNG;

// Options definition
#define CPKCL_RNG_SEED              0x01
#define CPKCL_RNG_GET               0x02
#define CPKCL_RNG_GETSEED           0x03
#define CPKCL_RNG_X931_GET          0x04


#endif //_CRYPTOLIB_RNG_PB_INCLUDED

