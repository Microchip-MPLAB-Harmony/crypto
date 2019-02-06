/**************************************************************************
  Crypto Framework Library Source

  Company:
    Microchip Technology Inc.

  File Name:
    cpuid.c
  
  Summary:
    Crypto Framework Libarary source for cryptographic functions.

  Description:
    This source file contains functions that make up the Cryptographic 
	Framework Library for PIC32 families of Microchip microcontrollers.
**************************************************************************/

//DOM-IGNORE-BEGIN
/*****************************************************************************
 Copyright (C) 2013-2019 Microchip Technology Inc. and its subsidiaries.

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

#ifdef HAVE_CONFIG_H
    #include <config.h>
#endif

#include <wolfssl/wolfcrypt/settings.h>

#include <wolfssl/wolfcrypt/cpuid.h>

#if (defined(WOLFSSL_X86_64_BUILD) || defined(USE_INTEL_SPEEDUP) || \
     defined(WOLFSSL_AESNI)) && !defined(WOLFSSL_NO_ASM)
    /* Each platform needs to query info type 1 from cpuid to see if aesni is
     * supported. Also, let's setup a macro for proper linkage w/o ABI conflicts
     */

    #ifndef _MSC_VER
        #define cpuid(reg, leaf, sub)\
            __asm__ __volatile__ ("cpuid":\
                "=a" (reg[0]), "=b" (reg[1]), "=c" (reg[2]), "=d" (reg[3]) :\
                "a" (leaf), "c"(sub));

        #define XASM_LINK(f) asm(f)
    #else
        #include <intrin.h>

        #define cpuid(a,b,c) __cpuidex((int*)a,b,c)

        #define XASM_LINK(f)
    #endif /* _MSC_VER */

    #define EAX 0
    #define EBX 1
    #define ECX 2
    #define EDX 3

    static word32 cpuid_check = 0;
    static word32 cpuid_flags = 0;

    static word32 cpuid_flag(word32 leaf, word32 sub, word32 num, word32 bit)
    {
        int got_intel_cpu = 0;
        int got_amd_cpu = 0;
        unsigned int reg[5];
        reg[4] = '\0';
        cpuid(reg, 0, 0);

        /* check for Intel cpu */
        if (XMEMCMP((char *)&(reg[EBX]), "Genu", 4) == 0 &&
            XMEMCMP((char *)&(reg[EDX]), "ineI", 4) == 0 &&
            XMEMCMP((char *)&(reg[ECX]), "ntel", 4) == 0) {
            got_intel_cpu = 1;
        }

        /* check for AMD cpu */
        if (XMEMCMP((char *)&(reg[EBX]), "Auth", 4) == 0 &&
            XMEMCMP((char *)&(reg[EDX]), "enti", 4) == 0 &&
            XMEMCMP((char *)&(reg[ECX]), "cAMD", 4) == 0) {
            got_amd_cpu = 1;
        }

        if (got_intel_cpu || got_amd_cpu) {
            cpuid(reg, leaf, sub);
            return ((reg[num] >> bit) & 0x1);
        }
        return 0;
    }


    void cpuid_set_flags(void)
    {
        if (!cpuid_check) {
            if (cpuid_flag(1, 0, ECX, 28)) { cpuid_flags |= CPUID_AVX1  ; }
            if (cpuid_flag(7, 0, EBX,  5)) { cpuid_flags |= CPUID_AVX2  ; }
            if (cpuid_flag(7, 0, EBX,  8)) { cpuid_flags |= CPUID_BMI2  ; }
            if (cpuid_flag(1, 0, ECX, 30)) { cpuid_flags |= CPUID_RDRAND; }
            if (cpuid_flag(7, 0, EBX, 18)) { cpuid_flags |= CPUID_RDSEED; }
            if (cpuid_flag(1, 0, ECX, 26)) { cpuid_flags |= CPUID_AESNI ; }
            if (cpuid_flag(7, 0, EBX, 19)) { cpuid_flags |= CPUID_ADX   ; }
            cpuid_check = 1;
        }
    }

    word32 cpuid_get_flags(void)
    {
        if (!cpuid_check)
            cpuid_set_flags();
        return cpuid_flags;
    }
#endif
