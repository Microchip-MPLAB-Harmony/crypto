/**************************************************************************
  Crypto Framework Library Source

  Company:
    Microchip Technology Inc.

  File Name:
    CryptoLib_Headers_pb.h

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

#ifndef _CryptoLib_HEADERS_PB_INCLUDED
#define _CryptoLib_HEADERS_PB_INCLUDED

// Include the services headers ...
#include "CryptoLib_Rc_pb.h"
#include "CryptoLib_ClearFlags_pb.h"
#include "CryptoLib_Comp_pb.h"
#include "CryptoLib_CondCopy_pb.h"
#include "CryptoLib_CRT_pb.h"
#include "CryptoLib_Div_pb.h"
#include "CryptoLib_ExpMod_pb.h"
#include "CryptoLib_FastCopy_pb.h"
#include "CryptoLib_Fill_pb.h"
#include "CryptoLib_Fmult_pb.h"
#include "CryptoLib_GCD_pb.h"
#include "CryptoLib_NOP_pb.h"
#include "CryptoLib_PrimeGen_pb.h"
#include "CryptoLib_RedMod_pb.h"
#include "CryptoLib_Rng_pb.h"
#include "CryptoLib_SelfTest_pb.h"
#include "CryptoLib_Hash_pb.h"
#include "CryptoLib_Smult_pb.h"
#include "CryptoLib_Square_pb.h"
#include "CryptoLib_Swap_pb.h"

// ECC
#include "CryptoLib_ZpEccAdd_pb.h"
#include "CryptoLib_ZpEccDbl_pb.h"
#include "CryptoLib_ZpEccMul_pb.h"
#include "CryptoLib_ZpEccConv_pb.h"
#include "CryptoLib_ZpEcDsa_pb.h"

#include "CryptoLib_GF2NEccAdd_pb.h"
#include "CryptoLib_GF2NEccDbl_pb.h"
#include "CryptoLib_GF2NEccMul_pb.h"
#include "CryptoLib_GF2NEccConv_pb.h"
#include "CryptoLib_GF2NEcDsa_pb.h"
#include "CryptoLib_JumpTable_pb.h"
#include "CryptoLib_Services_pb.h"

typedef struct _CPKCL_status {
               u4             CarryIn        : 1;
               u4             CarryOut       : 1;
               u4             Zero           : 1;
               u4             Gf2n           : 1;
               u4             Violation      : 1;
               u4            RFU            : (32-5);
               } CPKCL_STATUS,  * PCPKCL_STATUS, * PFCPKCL_STATUS;

typedef struct _CPKCL_header {
               u1             u1Service;
               u1             u1SubService;
               u2             u2Option;
               CPKCL_STATUS    Specific;
               u2             u2Status;
               u2             __Padding0;
               u4             __Padding1;
               } CPKCL_HEADER,  * PCPKCL_HEADER,  *  PFCPKCL_HEADER;

typedef struct _CPKCL_param {
               CPKCL_HEADER    CPKCL_Header;
               union
                    {
                    _CPKCL_CLEARFLAGS            CPKCL_ClearFlags;
                    _CPKCL_COMP                  CPKCL_Comp;
                    _CPKCL_CONDCOPY              CPKCL_CondCopy;
                    _CPKCL_CRT                   CPKCL_CRT;
                    _CPKCL_DIV                   CPKCL_Div;
                    _CPKCL_EXPMOD                CPKCL_ExpMod;
                    _CPKCL_FASTCOPY              CPKCL_FastCopy;
                    _CPKCL_FILL                  CPKCL_Fill;
                    _CPKCL_FMULT                 CPKCL_Fmult;
                    _CPKCL_GCD                   CPKCL_GCD;
                    _CPKCL_NOP                   CPKCL_Nop;
                    _CPKCL_PRIMEGEN              CPKCL_PrimeGen;
                    _CPKCL_REDMOD                CPKCL_RedMod;
                    _CPKCL_RNG                   CPKCL_Rng;
                    _CPKCL_SELFTEST              CPKCL_SelfTest;
                    _CPKCL_HASH                  CPKCL_Hash;
                    _CPKCL_SMULT                 CPKCL_Smult;
                    _CPKCL_SQUARE                CPKCL_Square;
                    _CPKCL_SWAP                  CPKCL_Swap;

// ECC
                    _CPKCL_ZPECCADD                     CPKCL_ZpEccAdd;
                    _CPKCL_ZPECCDBL                     CPKCL_ZpEccDbl;
                    _CPKCL_ZPECCMUL                     CPKCL_ZpEccMul;
                    _CPKCL_ZPECDSAGENERATE              CPKCL_ZpEcDsaGenerate;
                    _CPKCL_ZPECDSAVERIFY                CPKCL_ZpEcDsaVerify;
                    _CPKCL_ZPECCONVPROJTOAFFINE         CPKCL_ZpEcConvProjToAffine;
                    _CPKCL_ZPECCONVAFFINETOPROJECTIVE   CPKCL_ZpEcConvAffineToProjective;
                    _CPKCL_ZPECRANDOMIZECOORDINATE      CPKCL_ZpEcRandomiseCoordinate;
                    _CPKCL_ZPECPOINTISONCURVE           CPKCL_ZpEcPointIsOnCurve;

                    // ECC
					_CPKCL_GF2NECCADD                     CPKCL_GF2NEccAdd;
					_CPKCL_GF2NECCDBL                     CPKCL_GF2NEccDbl;
					_CPKCL_GF2NECCMUL                     CPKCL_GF2NEccMul;
					_CPKCL_GF2NECDSAGENERATE              CPKCL_GF2NEcDsaGenerate;
					_CPKCL_GF2NECDSAVERIFY                CPKCL_GF2NEcDsaVerify;
					_CPKCL_GF2NECCONVPROJTOAFFINE         CPKCL_GF2NEcConvProjToAffine;
					_CPKCL_GF2NECCONVAFFINETOPROJECTIVE   CPKCL_GF2NEcConvAffineToProjective;
					_CPKCL_GF2NECRANDOMIZECOORDINATE	    CPKCL_GF2NEcRandomiseCoordinate;
					_CPKCL_GF2NECPOINTISONCURVE           CPKCL_GF2NEcPointIsOnCurve;

                    } P;
               //u4   __Padding0;
               } CPKCL_PARAM, * PCPKCL_PARAM, * PFCPKCL_PARAM;

// CPKCL helpers
#define DEF_PARAM                          pvoid pvCPKCLParam
#define GET_PARAM()
#define USE_PARAM                          (PCPKCL_PARAM)pvCPKCLParam

#define CPKCL(a)                           (USE_PARAM)->CPKCL_Header.a

#define CPKCL_ClearFlags(a)                (USE_PARAM)->P.CPKCL_ClearFlags.a
#define CPKCL_Comp(a)                      (USE_PARAM)->P.CPKCL_Comp.a
#define CPKCL_CondCopy(a)                  (USE_PARAM)->P.CPKCL_CondCopy.a
#define CPKCL_CRT(a)                       (USE_PARAM)->P.CPKCL_CRT.a
#define CPKCL_Div(a)                       (USE_PARAM)->P.CPKCL_Div.a
#define CPKCL_ExpMod(a)                    (USE_PARAM)->P.CPKCL_ExpMod.a
#define CPKCL_FastCopy(a)                  (USE_PARAM)->P.CPKCL_FastCopy.a
#define CPKCL_Fill(a)                      (USE_PARAM)->P.CPKCL_Fill.a
#define CPKCL_Fmult(a)                     (USE_PARAM)->P.CPKCL_Fmult.a
#define CPKCL_GCD(a)                       (USE_PARAM)->P.CPKCL_GCD.a
#define CPKCL_NOP(a)                       (USE_PARAM)->P.CPKCL_NOP.a
#define CPKCL_PrimeGen(a)                  (USE_PARAM)->P.CPKCL_PrimeGen.a
#define CPKCL_RedMod(a)                    (USE_PARAM)->P.CPKCL_RedMod.a
#define CPKCL_Rng(a)                       (USE_PARAM)->P.CPKCL_Rng.a
#define CPKCL_SelfTest(a)                  (USE_PARAM)->P.CPKCL_SelfTest.a
#define CPKCL_Hash(a)                      (USE_PARAM)->P.CPKCL_Hash.a
#define CPKCL_Smult(a)                     (USE_PARAM)->P.CPKCL_Smult.a
#define CPKCL_Square(a)                    (USE_PARAM)->P.CPKCL_Square.a
#define CPKCL_Swap(a)                      (USE_PARAM)->P.CPKCL_Swap.a


#define CPKCL_ZpEccAdd(a)                  (USE_PARAM)->P.CPKCL_ZpEccAdd.a
#define CPKCL_ZpEccDbl(a)                  (USE_PARAM)->P.CPKCL_ZpEccDbl.a
#define CPKCL_ZpEccMul(a)                  (USE_PARAM)->P.CPKCL_ZpEccMul.a
#define CPKCL_ZpEcDsaGenerate(a)           (USE_PARAM)->P.CPKCL_ZpEcDsaGenerate.a
#define CPKCL_ZpEcDsaVerify(a)             (USE_PARAM)->P.CPKCL_ZpEcDsaVerify.a
#define CPKCL_ZpEcConvProjToAffine(a)      (USE_PARAM)->P.CPKCL_ZpEcConvProjToAffine.a
#define CPKCL_ZpEcConvAffineToProjective(a)(USE_PARAM)->P.CPKCL_ZpEcConvAffineToProjective.a
#define CPKCL_ZpEcRandomiseCoordinate(a)   (USE_PARAM)->P.CPKCL_ZpEcRandomiseCoordinate.a
#define CPKCL_ZpEcPointIsOnCurve(a)        (USE_PARAM)->P.CPKCL_ZpEcPointIsOnCurve.a

#define CPKCL_GF2NEccAdd(a)                  (USE_PARAM)->P.CPKCL_GF2NEccAdd.a
#define CPKCL_GF2NEccDbl(a)                  (USE_PARAM)->P.CPKCL_GF2NEccDbl.a
#define CPKCL_GF2NEccMul(a)                  (USE_PARAM)->P.CPKCL_GF2NEccMul.a
#define CPKCL_GF2NEcDsaGenerate(a)           (USE_PARAM)->P.CPKCL_GF2NEcDsaGenerate.a
#define CPKCL_GF2NEcDsaVerify(a)             (USE_PARAM)->P.CPKCL_GF2NEcDsaVerify.a
#define CPKCL_GF2NEcConvProjToAffine(a)      (USE_PARAM)->P.CPKCL_GF2NEcConvProjToAffine.a
#define CPKCL_GF2NEcConvAffineToProjective(a)(USE_PARAM)->P.CPKCL_GF2NEcConvAffineToProjective.a
#define CPKCL_GF2NEcRandomiseCoordinate(a)   (USE_PARAM)->P.CPKCL_GF2NEcRandomiseCoordinate.a
#define CPKCL_GF2NEcPointIsOnCurve(a)        (USE_PARAM)->P.CPKCL_GF2NEcPointIsOnCurve.a

// Services options helpers
#define MULTIPLIEROPTION_MASK      0x0003
#define CARRYOPTION_MASK           0x00fc
#define REDUCTIONOPTION_MASK       0xff00

// Common carry options to all services supporting arithmetic operations
// These two definitions are internal only
#define FORCE_CARRYIN              0x10
#define FORCE_NOCARRYIN            0x08

// These definitions are available for final user use
#define MISC_COMMAND               0x00
#define ADD_CARRY                  0x01
#define SUB_CARRY                  0x02
#define ADD_1_PLUS_CARRY           0x03
#define ADD_1_MINUS_CARRY          0x04
#define CARRY_NONE                 ADD_CARRY           | FORCE_NOCARRYIN
#define ADD_1                      ADD_CARRY           | FORCE_CARRYIN
#define SUB_1                      SUB_CARRY           | FORCE_CARRYIN
#define ADD_2                      ADD_1_PLUS_CARRY    | FORCE_CARRYIN

// Common multiplier options to all services supporting arithmetic operations
#define MULT_ONLY                  0x01
#define MULT_ADD                   0x02
#define MULT_SUB                   0x03

// Macro enabling to have access to the Carry Options
#define CARRYOPTION()              ((CPKCL(u2Option) & CARRYOPTION_MASK) >> 2)
#define SET_CARRYOPTION(a)         (u2)((a) << 2)

// Macro enabling to have access to the Multiplier Options
#define MULTIPLIEROPTION()         (CPKCL(u2Option) & MULTIPLIEROPTION_MASK)
#define SET_MULTIPLIEROPTION(a)    (u2)(a)

// Macro enabling to have access to the Multiplier Options
#define REDUCTIONOPTION()          ((CPKCL(u2Option) & REDUCTIONOPTION_MASK) >> 8)
#define SET_REDUCTIONOPTION(a)     (u2)((a) << 8)

// Calling a cryptographic service
#define vCPKCL_Process(a,b)     \
          {\
          b->CPKCL_Header.u1Service = CPKCL_SERVICE_##a;\
          b->CPKCL_Header.u2Status  = CPKCL_COMPUTATION_NOT_STARTED;\
          __vCPKCLCs##a(b);\
          }

#endif // _CryptoLib_HEADERS_PB_INCLUDED


