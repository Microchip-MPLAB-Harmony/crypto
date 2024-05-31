/**************************************************************************
  Crypto Framework Library Source

  Company:
    Microchip Technology Inc.

  File Name:
    CryptoLib_RedMod_pb.h

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

#ifndef _CRYPTOLIB_REDMOD_PB_INCLUDED
#define _CRYPTOLIB_REDMOD_PB_INCLUDED

// Structure definition
typedef struct _CPKCL_redmod {
               nu1       nu1ModBase;
               nu1       nu1CnsBase;
               u2        u2ModLength;

               nu1       nu1RBase;
               u2        __Padding0;
               u2        __Padding1;
               nu1       nu1XBase;
               } _CPKCL_REDMOD, *_PPKCL_REDMOD;

#define CPKCL_REDMOD_SETUP           0x0100
#define CPKCL_REDMOD_REDUCTION       0x0200
#define CPKCL_REDMOD_NORMALIZE       0x0400
#define CPKCL_REDMOD_OPERATIONMASK   0x0F00

#define CPKCL_REDMOD_USING_DIVISION  0x1000
#define CPKCL_REDMOD_USING_FASTRED   0x2000
#define CPKCL_REDMOD_RANDOMIZE       0x4000
#define CPKCL_REDMOD_MODEMASK        0xF000


#endif // _CRYPTOLIB_REDMOD_PB_INCLUDED
