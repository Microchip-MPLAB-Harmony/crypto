/*******************************************************************************
  Crypto Speed Test Source File

  Company:
    Microchip Technology Inc.

  File Name:
    cryptoSTE_malloc.c

  Summary:
    Virtualization of malloc() for the crypto test suite.

  Description:
    This file contains a wrapper for malloc() and free() that allow
    for easier debugging when necessary.
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

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#define CRLF "\r\n"

#define PRINT_MALLOC  0
#if PRINT_MALLOC
__attribute__((used)) static size_t allocated = 0;
__attribute__((used)) static size_t allocations = 0;
#endif

void * cryptoSTE_malloc(size_t s)
{
    void * p = malloc(s);
#if PRINT_MALLOC
    if (p)
    {
        allocations++;
        allocated += s;
        printf("<(%3d) malloc %p size=%u>" CRLF, allocations, p, s);
    }
    else printf("<(%3d) malloc %p failed size=%u>" CRLF, allocations, p, s);
#endif
    return p;
}

void cryptoSTE_free(void * p)
{
    free(p);
#if PRINT_MALLOC
    allocations--;
    printf("<(%3d) free   %p>" CRLF, allocations, p);
#endif
}