/**************************************************************************
  Crypto Framework Library Source

  Company:
    Microchip Technology Inc.

  File Name:
    CryptoLib_Services_pb.h

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

#ifndef _CRYPTOLIB_SERVICES_PB_INCLUDED
#define _CRYPTOLIB_SERVICES_PB_INCLUDED

// Services definition
#define CPKCL_SERVICE_SelfTest                    		0xA0
#define CPKCL_SERVICE_Rng                         		0xA1
#define CPKCL_SERVICE_Smult                       		0xA2
#define CPKCL_SERVICE_Comp                        		0xA3
#define CPKCL_SERVICE_Fmult                       		0xA4
#define CPKCL_SERVICE_Square                      		0xA5
#define CPKCL_SERVICE_Swap                        		0xA6
#define CPKCL_SERVICE_FastCopy                    		0xA7
#define CPKCL_SERVICE_CondCopy                    		0xA8
#define CPKCL_SERVICE_ClearFlags                  		0xA9
#define CPKCL_SERVICE_Fill                        		0xAA
#define CPKCL_SERVICE_NOP                         		0xAB
//=======================================================
#define CPKCL_SERVICE_Hash                        		0xB0
//=======================================================

#define CPKCL_SERVICE_Div                         		0xC0
#define CPKCL_SERVICE_CRT                         		0xC1
#define CPKCL_SERVICE_PrimeGen                    		0xC2
#define CPKCL_SERVICE_ExpMod                      		0xC3
#define CPKCL_SERVICE_GCD                         		0xC4
#define CPKCL_SERVICE_RedMod                      		0xC5
//=======================================================
#define CPKCL_SERVICE_ZpEcRandomiseCoordinate     		0xE0
#define CPKCL_SERVICE_ZpEcDsaVerifyFast           		0xE2
#define CPKCL_SERVICE_ZpEccDblFast                		0xE3
#define CPKCL_SERVICE_ZpEccMulFast                		0xE8
#define CPKCL_SERVICE_ZpEcConvAffineToProjective  		0xE9
#define CPKCL_SERVICE_ZpEcDsaGenerateFast         		0xEA
#define CPKCL_SERVICE_ZpEccAddFast                		0xEB
#define CPKCL_SERVICE_ZpEcPointIsOnCurve          		0xEC
#define CPKCL_SERVICE_ZpEcConvProjToAffine        		0xED
//=======================================================
#define CPKCL_SERVICE_GF2NEcRandomiseCoordinate     	0x90
#define CPKCL_SERVICE_GF2NEcDsaVerifyFast           	0x92
#define CPKCL_SERVICE_GF2NEccDblFast                	0x93
#define CPKCL_SERVICE_GF2NEccMulFast                	0x98
#define CPKCL_SERVICE_GF2NEcConvAffineToProjective  	0x99
#define CPKCL_SERVICE_GF2NEcDsaGenerateFast         	0x9A
#define CPKCL_SERVICE_GF2NEccAddFast                	0x9B
#define CPKCL_SERVICE_GF2NEcPointIsOnCurve          	0x9C
#define CPKCL_SERVICE_GF2NEcConvProjToAffine        	0x9D


#endif //_CRYPTOLIB_SERVICES_PB_INCLUDED

