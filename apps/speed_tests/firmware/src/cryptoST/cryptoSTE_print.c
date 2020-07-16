/*******************************************************************************
  Crypto Speed Test Source File

  Company:
    Microchip Technology Inc.

  File Name:
    cryptoST_print.c

  Summary:
    Routines to print test results.

  Description:
    This file contains functions to print test results in standard
    formats.
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

#include "cryptoSTE_print.h"
#include <stdlib.h> // for itoa()
#include <ctype.h>  // for isprint()
#include <stdbool.h>
#include <stdio.h>
#include <assert.h>
#include "cryptoSTE_buildInfo.h"

#if !defined(SEP)
#define SEP ","
#endif

// Quote marks on strings but not numeric fields
static const char * const formatTextField = SEP "\"%s\"";
// static const char * const formatLintField = SEP "%ld";
static const char * const formatSintField = SEP "%d";
static const char * const formatUintField = SEP "%lu";
#define PRINT_FIELD(msg)    printf(formatTextField,msg);
#define PRINT_LINT(val)     printf(formatLintField,val);
#define PRINT_INT(val)      printf(formatSintField,val);
#define PRINT_LUINT(val)    printf(formatUintField,val);

#define assert_dbug(X) __conditional_software_breakpoint((X))

// *****************************************************************************
// *****************************************************************************
// Section: Patch for stdlib and itoa()
// *****************************************************************************
// *****************************************************************************
#if defined(__mips__)
/* PIC is MIPS, but SAM is ARM; been broken a _long_ time. */
char * ansi_itoa(int value, char *string, int radix)
{ return itoa(string, value, radix); }
#else
/* The SAM version agrees with the ANSI standard. */
#define ansi_itoa(v,s,r)     itoa((v),(s),(r))
#endif

// *****************************************************************************
// *****************************************************************************
// Section: Support routines
// *****************************************************************************
// *****************************************************************************
/* The magic here is that size_t is different in ARM and MIPS,
 * so we up-cast it to UL for the printf's. */
void cryptoST_PRINT_announceElapsedTime_TEXT(cryptoSTE_results_t * testData)
{
    PRINT(">> ");
    PRINT(testData->testHandler);
    P0_UINT( " enc=", testData->encryption.size);

    const long unsigned int delta = 
        testData->encryption.stop - testData->encryption.start;
    if (CSTE_VERBOSE > 1)
    {
        printf("..delta clock: %lu counts" CRLF, delta);
        PRINT("Elapsed time: "); // _no_ CRLF -- continue line below
    }
    
    const uint32_t time = SYS_TIME_CountToUS(delta);
    uint32_t const iterate = testData->encryption.iterations;
    
    // Want to show the average to 3 decimal places (using integer arithmetic)
    const uint32_t intAverage = time/iterate;
    const uint32_t remainder = time - (intAverage * iterate);
    const uint32_t fraction = ((1000 * remainder) + (iterate/2))/iterate;
    
    if(testData->encryption.startStopIsValid)
        printf(" %10lu us on %lu iterations (%lu.%03lu us average)", 
                    (long unsigned int)time, 
                    (long unsigned int)iterate, 
                    (long unsigned int)intAverage, 
                    (long unsigned int)fraction);
    else
        printf(" no time recorded on %lu iterations", 
                    (long unsigned int)iterate);

    if (testData->errorMessage)
        printf("; test completed with error");
    
    PRINT_WAIT(CRLF);
}

#define SHOW_START_STOP     1
/* CSV = Comma Separated Values -- for import to Excel */
static bool CSV_sentHeader = false;
void cryptoST_PRINT_announceElapsedTime_CSV
      ( const CPU_CHAR * testName,
        cryptoSTE_labels_t * labels, 
        cryptoSTE_results_t * results)
{
    if (! CSV_sentHeader)
    {
        printf( "sep=" SEP CRLF    // excel-only it seems
                ">>" SEP           // line tag
                "Processor" SEP    // per cryptoST_xx
                "Platform" SEP     // per cryptoST_xx
                "Accelerator" SEP  // per cryptoST_xx
                "Optimized" SEP    // on, but not the level
                "Build" SEP        // hopefully the git version
                "Fcpu" SEP         // CPU frequency
                "Ftimer" SEP       // timer frequency (unit of measure)
                "Domain" SEP       // test category
                "Handler" SEP      // functional test driver
                "DataSize" SEP
                "IterateEnc" SEP   // ...encryption
#if SHOW_START_STOP
                "StartTEnc" SEP    // ...encryption
                "StopTEnc" SEP     // ...encryption
#else
                "DeltaTEnc" SEP    // ...encryption
#endif
                "IterateDec" SEP   // ...decryption
#if SHOW_START_STOP
                "StartTDec" SEP    // ...decryption
                "StopTDec" SEP     // ...decryption
#else
                "DeltaTDec" SEP    // ...decryption
#endif
                "Wolf Err" SEP     // numeric error code
                "Warning" SEP      // text
                "Error"            // text
                CRLF );
        CSV_sentHeader = true;
    }

    PRINT(">>"); // marker to grep the data output
    PRINT_FIELD(labels->processor);
    PRINT_FIELD(labels->platform);
    PRINT_FIELD(labels->accelerator);
    PRINT_FIELD(cryptoSTE_buildInfo.optimized);
    PRINT_FIELD(labels->build);
    PRINT_LUINT(((const long unsigned int)(SYS_TIME_CPU_CLOCK_FREQUENCY)));
    PRINT_LUINT(SYS_TIME_FrequencyGet());
    PRINT_FIELD(testName);
    PRINT_FIELD(results->testHandler);
    PRINT_INT(results->encryption.size);
    PRINT_INT(results->encryption.iterations);
#if SHOW_START_STOP
    if (results->encryption.startStopIsValid)
    { 
        PRINT_LUINT(results->encryption.start);
        PRINT_LUINT(results->encryption.stop);
    }
    else { PRINT(SEP SEP); }
#else
    if (results->encryption.startStopIsValid)
    { PRINT_LUINT(results->encryption.stop - results->encryption.start); }
    else { PRINT(SEP); }
#endif
#if INCLUDE_DECRYPTION
    PRINT_INT(results->decryption.iterations);
#if SHOW_START_STOP
    if (results->decryption.startStopIsValid)
    { 
        PRINT_LUINT(results->decryption.start);
        PRINT_LUINT(results->decryption.stop);
    }
    else { PRINT(SEP SEP); }
#else
    if (results->decryption.startStopIsValid)
    { PRINT_LUINT(results->decryption.stop - results->decryption.start); }
    else { PRINT(SEP); }
#endif
#else
#if SHOW_START_STOP
    PRINT(SEP SEP SEP); // decryption placeholders
#else
    PRINT(SEP SEP); // decryption placeholders
#endif
#endif
    if (results->wolfSSLresult)
    { PRINT_INT(results->wolfSSLresult); }
    else { PRINT(SEP); }
    PRINT_FIELD(results->warningMessage?results->warningMessage:"");
    PRINT_FIELD(results->errorMessage?results->errorMessage:"");
    PRINT_WAIT(CRLF); // something w/o a separator
}


// *****************************************************************************
// *****************************************************************************
// Section: External API
// *****************************************************************************
// *****************************************************************************

/* This is the "official" output printer.
 * Everything else is VERBOSE and pretty-printing.
 * 
 * The actual routines are above, according to the required format.
 *  */
void cryptoST_PRINT_announceElapsedTime
       (const CPU_CHAR * testName, 
        cryptoSTE_testExecution_t * config)
{
    switch(config->parameters.displayType)
    {
    case CST_TEXT:
        cryptoST_PRINT_announceElapsedTime_TEXT(&config->results);
        break;
    case CST_CSV:
        cryptoST_PRINT_announceElapsedTime_CSV
                (testName, &config->labels, &config->results);
        break;
    case CST_XML:
    case CST_JSON:
    default:
        printf(CRLF ">> %s |||| FORMAT ERROR ||||", config->results.testHandler);
        break;
    }
}


/* Print a line having both the hexadecimal and ASCII values
 * (that is, only printable characters, no controls).
 *  */
void cryptoST_PRINT_hexLine(const char * const tag, 
                            const uint8_t * const data, 
                            size_t const length)
{
    PRINT(tag);
    printf(" ");
    if (NULL == data)
    { PRINT("** null pointer"); return; }
    if (0 == length)
    { PRINT("** zero-length data"); return; }
    
    char line[70];  // 16*(2+1) + 1 + 8*1 + 1 + 8*1 characters + null
    size_t count = (length > 16)? 16 : length;
    
    // First loop to print the hexadecimals, little-endian
    char * pos = &line[0];
    for (int i = 0; i < 16; i++)
    {
        if (i >= count)
        {
            *pos++ = ' ';
            *pos++ = ' ';
        }
        else
        {
            const uint8_t datum = data[i]; // by definition, 00..FF

            if (datum < 0x10) // insert leading zero
                *pos++ = '0',ansi_itoa(datum, pos, 16), pos++;
            else
                ansi_itoa(datum, pos, 16), pos += 2;
        }
        
        *pos++ = ' '; // and now the trailing blank
        if (7 == i) *pos++ = ' '; // inner column separation
    }
    
    // One blank to set the 2nd column apart from the first
    *pos++ = ' ';
    
    // Second loop does the printable character version
    for (int i = 0; i < 16; i++)
    {
        if (i >= count)
            *pos++ = ' ';
        else
        {
            uint8_t datum = data[i]; // by definition, 00..FF
            *pos++ = isprint(datum)? datum : '.';
        }
        if (7 == i) *pos++ = ' '; // inner column separation
    }
    
    *pos++ = 0; // EOL -- verify we did not overrun the buffer
    __conditional_software_breakpoint(ALENGTH(line) > (pos - line));
    PRINT_WAIT(line); // wait before line goes out of scope
#if 1
    int align4 = ((uint32_t)data)%4;
    char * align = (0==align4)?"":" misaligned";
    printf(" (%lu)%s", (long unsigned int)length, align);
#endif
}

#if 1
/* Print a text block having both the hexadecimal and ASCII values
 * (that is, only printable characters, no controls).
 *  */
void cryptoST_PRINT_hexBlock
    (const char * const tag, const uint8_t * data, size_t length)
{
    size_t count = length;
    size_t offset = 0;
    while (count)
    {
        char buffer[16];
        int pad = strlen(tag);
        if (pad > 8) pad = 8;
        
        if (0 == offset)
        {
            memset(buffer,0,sizeof(buffer));
            strncpy(buffer,tag,sizeof(buffer)-1); // save room for null
        }
        else snprintf(buffer, sizeof(buffer), "  %*u:", 
                            pad, (unsigned int)offset);
        cryptoST_PRINT_hexLine(buffer, data, count);
        PRINT_WAIT(CRLF); // wait before CRLF goes out of scope
        
        data += 16;
        offset += 16;
        count = (count > 16)? count-16 : 0;
    }
}
#endif
