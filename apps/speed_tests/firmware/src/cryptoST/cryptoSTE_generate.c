/*******************************************************************************
  Crypto Speed Test Source File

  Company:
    Microchip Technology Inc.

  File Name:
    cryptoSTE_generate.c

  Summary:
    Pseudo-random sequence generators

  Description:
    This file contains functions to produce repeatable sequences of
    integers beginning with a defined seed value. Options include
    sequential and pseudo-random patterns.
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

#include <stddef.h>
#include "cryptoSTE_print.h" // for BASE_LINE
#include "cryptoSTE_generate.h"

/*************************************************************
 * Helper functions
 *************************************************************/
static size_t maxBitNumber_UINT32(uint32_t const n)
{
    size_t answer = 0;
    
    for (uint32_t i = 0x80000000; i > 0; i >>= 1)
        if (0 == (n & i)) answer++;
        else break;
    
    return ((8*sizeof(uint32_t)) - answer)-1;
}


/*************************************************************
 * API handlers
 *************************************************************/
/* Generate a sequential sequence to fill a buffer.
 *  */
const char * cryptoSTE_generateSequentialUINT32
    (uint32_t * dst, uint32_t seed, size_t size)
{
    uint32_t counter = seed;
    while (size--)
        *dst++ = counter++;
    
    return 0;
}

/* Generate a maximal-length (pseudoRandom) sequence to fill a buffer
 * of a given (power-of-2) size. Note that the first and last
 * entries will be the same when the buffer is power-of-2 length.
 * 
 * See also: https://en.wikipedia.org/wiki/Linear-feedback_shift_register
 *           http://in.ncu.edu.tw/ncume_ee/digilogi/prbs.htm
 * 
 * To be standard, define the feedback masks used for all input sizes.
 *  */
static uint32_t fb_tap[]={
    0x0000000C, // 4 checked
    0x00000014, // 5 checked
    0x00000021, // 6 checked
    0x00000060, // 7 checked
    0x000000E1, // 8 checked
    0x00000110, // 9 checked
    0x00000204, // 10 checked
    0x00000415, // 11 checked
    0x00000E08, // 12 checked
    0x00001C80, // 13 <<-- not checked
    0, // 14
    0, // 15
    0x0000B400, // 16 checked
};
#define FB_TAPS (sizeof(fb_tap)/sizeof(fb_tap[0]))

/* Maximal length shift register for any buffer.
 * If there are size = N = power-of-2 elements in the array, this
 * algorithm will generate N-1 distinct values, and then
 * put zero in the final element.
 * TODO: update this for non power-of-2 sizes. */
const char * cryptoSTE_generatePseudorandomUINT32
    (uint32_t * dst, uint32_t const seed, size_t const size)
{
    // Force a power-of-2 length
    uint32_t bitsOfSignificance = maxBitNumber_UINT32(size);
    if (0 == bitsOfSignificance)
        return "cannot get LFSR of this size (" BASE_LINE ")";
    else
    {
        /* Find the appropriate tap specification.
         * Required: this is a power-of-2 value */
        uint32_t const expectedLength = 1 << bitsOfSignificance;
        uint32_t fb = 0;
        for (int tap = 0; tap < FB_TAPS; tap++)
        {
            // This only works because we start from the smallest tap option.
            if (0 != (fb_tap[tap] & expectedLength)) break;
            fb = fb_tap[tap]; // capture the next-to-last entry
        }
        
        if (0 == fb)
            return "no generator for LFSR (" BASE_LINE ")";
        else
        {
            /* Produce the maximal sequence.
             * Truncate the seed and guarantee non-zero. */
            uint32_t const start_state = seed & (expectedLength-1);
            uint32_t lfsr = start_state? start_state 
                                       : ~start_state; // non-zero required

            /* This formulation of the end condition is intended to 
             * prove that the maximal sequence has been generated,
             * rather than counting length and assuming we got them all.
             * On the downside, it only does power-of-2.
             * */
            uint32_t period = 0;
            do // generate all the values
            {
                uint32_t lsb = lfsr & 1u;  /* Get LSB (i.e., the output bit). */
                lfsr >>= 1;                /* Shift the accumulator */
                if (lsb)                   /* If the output bit is 1, */
                    lfsr ^= fb;            /*  apply toggle mask. */
                
                /* Verify that we don't overrun the buffer, which also
                 * proves that we are not stuck in an infinite loop.
                 * */
                __conditional_software_breakpoint(period < size);
                *dst++ = lfsr;  // store the data
                ++period;
            }
            while (lfsr != start_state);
            
            *dst = 0; // everything exactly fits if all works right
            __conditional_software_breakpoint(++period == expectedLength);
        }
    }
    return 0;
}
