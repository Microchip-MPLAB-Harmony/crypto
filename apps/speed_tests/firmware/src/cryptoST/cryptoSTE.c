/*******************************************************************************
  Crypto Speed Test Application Source File

  Company:
    Microchip Technology Inc.

  File Name:
    cyrptoSTE.c

  Summary:
    This file provides the generic execution framework for the 
    crypto speed test suite (cryptoST).

  Description:
    The test database is scanned for vectors that match the selected
    test options (see below). Each vector is then exercised beneath
    a timer, and the average iteration duration is calculated.
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

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include "cryptoSTE_definitions.h"
#include "cryptoSTE_print.h"
#include "cryptoSTE_announce.h"
#include "../test_data/cryptoSpeedTestData.h"
#include "wolfssl/wolfcrypt/error-crypt.h"

/* Declare the total test suite.
 *  */
#include "configuration.h"
#include "cryptoSTE_aes_ecb.h"
#include "cryptoSTE_aes_cbc.h"
#include "cryptoSTE_aes_cfb.h"
#include "cryptoSTE_aes_ctr.h"
#if defined(HAVE_AESGCM)
#include "cryptoSTE_aes_gcm.h"
#endif
#if defined(HAVE_AESCCM)
#include "cryptoSTE_aes_ccm.h"
#endif
#include "cryptoSTE_sha.h"
#include "cryptoSTE_des3.h"
#include "cryptoSTE_rsa.h"

// *****************************************************************************
// *****************************************************************************
// Section: Local data structures
// *****************************************************************************
// *****************************************************************************
static volatile const int level = 0;

// This is a local convenience, but should be applied more generally.
typedef const char * (*cryptoSTE_exec_t)(const cryptoST_testDetail_t *,
                                         cryptoSTE_testExecution_t *);

// *****************************************************************************
// *****************************************************************************
// Section: Support routines
// *****************************************************************************
// *****************************************************************************

#define assert_dbug(X) __conditional_software_breakpoint((X))

#if defined(WOLFSSL_AES_128)
cryptoSTE_exec_t sortOutAES128(const cryptoST_testDetail_t * rv)
{
    cryptoSTE_exec_t exec = NULL;
    
    switch(rv->mode)
    {
#if defined(HAVE_AES_CBC)
        case EM_CBC: // for AES, DES
            exec = cryptoSTE_aes_cbc_128_timed;
            break;
#endif
#if defined(WOLFSSL_AES_CFB)
        case EM_CFB: // for AES, DES
            exec = cryptoSTE_aes_cfb_128_timed;
            break;
#endif
#if defined(WOLFSSL_AES_COUNTER)
        case EM_CTR: // for AES only
            exec = cryptoSTE_aes_ctr_128_timed;
            break;
#endif
#if defined(HAVE_AES_ECB)
        case EM_ECB: // for AES, DES
            exec = cryptoSTE_aes_ecb_timed;
            break;
#endif
        case EM_OFB: // for AES, DES
            // assert_dbug(0);
            break;
        default:
            break;
    }
    return exec;
}
#else
#define sortOutAES128(x) ((void*)0)
#endif

#if defined(WOLFSSL_AES_192)
cryptoSTE_exec_t sortOutAES192(const cryptoST_testDetail_t * rv)
{
    cryptoSTE_exec_t exec = NULL;
    
    switch(rv->mode)
    {
#if defined(HAVE_AES_CBC)
        case EM_CBC: // for AES, DES
            exec = cryptoSTE_aes_cbc_192_timed;
            break;
#endif
#if defined(WOLFSSL_AES_CFB)
        case EM_CFB: // for AES, DES
            exec = cryptoSTE_aes_cfb_192_timed;
            break;
#endif
#if defined(WOLFSSL_AES_COUNTER)
        case EM_CTR: // for AES only
            exec = cryptoSTE_aes_ctr_192_timed;
            break;
#endif
#if defined(HAVE_AES_ECB)
        case EM_ECB: // for AES, DES
            exec = cryptoSTE_aes_ecb_timed;
            break;
#endif
        case EM_OFB: // for AES, DES
            break;
        default:
            break;
    }
    return exec;
}
#else
#define sortOutAES192(x) ((void*)0)
#endif

#if defined(WOLFSSL_AES_256)
cryptoSTE_exec_t sortOutAES256(const cryptoST_testDetail_t * rv)
{
    cryptoSTE_exec_t exec = NULL;
    switch(rv->mode)
    {
#if defined(HAVE_AES_CBC)
        case EM_CBC: // for AES, DES
            exec = cryptoSTE_aes_cbc_256_timed;
            break;
#endif
#if defined(WOLFSSL_AES_CFB)
        case EM_CFB: // for AES, DES
            exec = cryptoSTE_aes_cfb_256_timed;
            break;
#endif
#if defined(WOLFSSL_AES_COUNTER)
        case EM_CTR: // for AES only
            exec = cryptoSTE_aes_ctr_256_timed;
            break;
#endif
#if defined(HAVE_AES_ECB)
        case EM_ECB: // for AES, DES
            exec = cryptoSTE_aes_ecb_timed;
            break;
#endif
        case EM_OFB: // for AES, DES
            break;
        default:
            break;
    }
    return exec;
}
#else
#define sortOutAES256(x) ((void*)0)
#endif

/* Identify which test to run.
 * Every combination of technique/mode is covered here.
 *  */
cryptoSTE_exec_t cryptoSTE_identifyTest(const cryptoST_testDetail_t * rv)
{
    // Pointer to the selected test routine
    cryptoSTE_exec_t exec = NULL;

    // Begin by identifying the appropriate test routine
    if (rv) switch(rv->technique)
    {
        case ET_AES_128:
            exec = sortOutAES128(rv);
            break;
        case ET_AES_192:
            exec = sortOutAES192(rv);
            break;
        case ET_AES_256:
            exec = sortOutAES256(rv);
            break;

#if !defined(NO_DES)
        case ET_DES:  /* block=64, deprecated   */
            // exec = cryptoSTE_des_timed;
            break;
#endif
#if !defined(NO_DES3)
        case ET_DES3: /* block=64, key=24 bytes */
            exec = cryptoSTE_des3des_timed;
            break;
#endif
            
#if defined(HAVE_AESGCM)
        case ET_AES_GCM:
            if (EM_NONE == rv->mode)
                exec = cryptoSTE_aes_gcm_timed;
            break;
#endif
#if defined(HAVE_AESCCM)
        case ET_AES_CCM:
            if (EM_NONE == rv->mode)
                exec = cryptoSTE_aes_ccm_timed;
            break;
#endif
#if !defined(NO_SHA256)
        case ET_SHA_128:
        case ET_SHA_224:
        case ET_SHA_256:
        case ET_SHA_384:
        case ET_SHA_512: exec = cryptoSTE_crya_sha_timed;
            break;
#endif
#if !defined(NO_RSA)
        case ET_PK_RSA_SIGN:
        case ET_PK_RSA_VERIFY:
        case ET_PK_RSA_EXPTMOD:
            exec = cryptoSTE_rsa_timed;
            break;
#endif
        case ET_MD2:
        case ET_MD3:
        case ET_MD4:
        case ET_MD5:
        case ET_MD6:
        default:
            exec = NULL;
            break;
    }
    return exec;
}

/* Identify which test to run, run it, and announce any errors.
 * Return 'false' for good result
 *  */
bool cryptoSTE_executeOneVector(const cryptoST_testDetail_t * rv,
                                cryptoSTE_testExecution_t * param)
{
    bool answer = true; // means test has failed
    
    // Identify the appropriate test routine for this datum.
    cryptoSTE_exec_t exec = cryptoSTE_identifyTest(rv);
    
    if (NULL == exec)
    {
        /* This error is caused when test data is included, but 
         * the encryption library (e.g. WolfSSL) does not support 
         * that mode on the current device. The recourse is to remove
         * the test data file from the build or extend the library.
         *
         * Note that param->results.testHandler is not yet defined
         * (because we did not find the test handler)
         * but the data source file is listed in the details.
         * */
        if (CSTE_VERBOSE < 2) // sic -- only if not already announced
            cryptoSTE_announceDetails(5, rv);
        PRINT("**** Required test is not available at "
                    __BASE_FILE__ "(" BASE_LINE ")" CRLF);
        PRINT_WAIT("==================================" CRLF);
    }
    else do
    {
        // Capturing the return value is a temporary hack 
        // until we fix the return values in all tests
        param->results.errorMessage = (*exec)(rv,param);
        answer = (0 != param->results.errorMessage);
        
        // If we are returning CSV, skip the pretty-printing.
        if (CST_CSV == param->parameters.displayType)
            break;

        if (CSTE_VERBOSE && param->results.warningMessage)
        {
            printf("-v %s **** warning (%d): %s" CRLF,
                    param->results.testHandler, 
                    param->results.warningCount,
                    param->results.warningMessage);
        }

        if (param->results.errorMessage)
        {
            printf("-v %s **** error: %s" CRLF,
                    param->results.testHandler, param->results.errorMessage);
            cryptoSTE_announceDetails(5, rv);
            printf("     Forcing use of crypto HW: %s" CRLF,
                    param->parameters.useLocalDriverEntryPoints? "true" : "false");
            if (param->results.wolfSSLresult)
            {
#ifdef NO_ERROR_STRINGS
                // look at wolfssl\wolfcrypt\error-crypt.h
                printf("     WolfSSL error#: %d" CRLF, 
                        param->results.wolfSSLresult);
#else
                printf("     WolfSSL: %s" CRLF, 
                        wc_GetErrorString(param->results.wolfSSLresult));
#endif
            }
            printf("==================================" CRLF);
        }
        else if (CSTE_VERBOSE > 1) 
                PRINT_WAIT("-- test completed without errors" CRLF);
    } while(0);
    return answer;
}

// *****************************************************************************
// *****************************************************************************
// Section: External API
// *****************************************************************************
// *****************************************************************************

/* The general idea is to iterate through all supplied data
 * and assign the vectors to the appropriate test. The tricky
 * part is that the database has 3 layers.
 * 
 * The configuration parameters can be used to filter down
 * for specific test cases.
 *  */
#define P_BUMP 2
void cryptoSTE(cryptoSTE_localData_t * thisTest)
{
    cryptoSTE_testExecution_t * config = &thisTest->configuration;
    
    if (CSTE_VERBOSE > 1) printf("=== Begin test sequence ===" CRLF);
    
    const cryptoST_testAPI_t * cv; // crypto vector file declaration
    for (int i = 0; i < thisTest->numberOfVectorAPI; i++)
    {
        cv = &thisTest->vectorAPI[i];
        if (CSTE_VERBOSE > 1) cryptoSTE_announceSuite(cv);
        
        if (cv->openData)
        {
            if (CSTE_VERBOSE > 2) 
            { printf("-- opening data set %s" CRLF, cv->name); }
            const char * res = cv->openData();
            if (res)
            { 
                printf("-> ** %s (open) %s" CRLF, cv->name, res);
                continue;
            }
        }

        if (CSTE_VERBOSE > 2) 
        { printf("             -- executing data set %s" CRLF, cv->name); }

        config->parameters.useLocalDriverEntryPoints = false;
        while(1) // loop if we are doing HW-SW comparison
        {
            const cryptoST_testDetail_t * tr;
            tr = cv->firstTest();
            if (NULL == tr)
                printf("-> ** %s no data provided ********" CRLF, cv->name);
            else for (; NULL != tr; tr = cv->nextTest(tr))
            {
                if (ET_NONE == tr->technique) // safety check
                {
                    // get here if a data file has no test vectors
                    printf("-- incomplete vector list in %s" CRLF, cv->name);
                    // __builtin_software_breakpoint();
                    break; // this is the un-named tail of the list
                }
                else
                {
                    if (CSTE_VERBOSE > 2) 
                    { printf("             -- data item %s" CRLF, tr->rawData->name); }

                    thisTest->testsAttempted++;
                    if (CSTE_VERBOSE > 1) 
                    {
                        PRINT("-- executing vector " CRLF);
                        cryptoSTE_announceDetails(P_BUMP, tr);
                        cryptoSTE_announceVector(2*P_BUMP, tr->rawData);
                    }

                    // Even with error, continue to next test
                    config->results = (cryptoSTE_results_t){0};
                    bool testFailed = cryptoSTE_executeOneVector(tr,config);
                    if (!testFailed)
                        thisTest->testsSucceeded++;

                    // If we failed and pretty-printing, then skip the
                    // result announcement (its already been done),
                    // but if we are showing CSV then include this result.
                    if (config->results.encryption.startStopIsValid
                      || (CST_CSV == config->parameters.displayType))
                    {
                        cryptoST_PRINT_announceElapsedTime( cv->name, config);
                    }
                    else if (testFailed)
                    {
                        printf("-^ %s (%s) failed; see message above" CRLF, 
                                cv->name, 
                                config->results.testHandler?
                                    config->results.testHandler : "--");
                    }
                }
            }

            // Ping-pong w/wo HW acceleration
            if (config->parameters.compareHWvSW
                    && (false == config->parameters.useLocalDriverEntryPoints))
                config->parameters.useLocalDriverEntryPoints = true;
            else
            {
                config->parameters.useLocalDriverEntryPoints = false;
                break;
            }
        }
        if (cv->closeData)
        {
            if (CSTE_VERBOSE > 2) 
            { printf("-- closing data set %s" CRLF, cv->name); }
            const char * res = cv->closeData();
            if (res)
            { 
                printf("** %s (close) %s" CRLF, cv->name, res);
                continue;
            }
        }
    }
}
