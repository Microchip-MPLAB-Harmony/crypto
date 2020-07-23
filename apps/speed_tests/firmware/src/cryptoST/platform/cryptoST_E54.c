/*******************************************************************************
  Crypto Speed Test Application Source File

  Company:
    Microchip Technology Inc.

  File Name:
    cyrptoST_E54.c

  Summary:
    This file provides the generic execution framework for the 
    crypto speed test suite (cryptoST) on SAM E54.

  Description:
 *  The test database is scanned for vectors that match the selected
 *  test options (see below). Each vector is then exercised beneath
 *  a timer, and the average iteration duration is calculated.
 * 
 * Currently there are three items that must be customized in this file.
 * 1. Platform and processor name, immediately below.
 * 2. The test parameter callout in cryptoST(), and the output format.
 * 3. Add/remove #include's for the data sources;
 *      If a new source is added, then also the loader in cryptoST_init().
 *******************************************************************************/

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

#include "cryptoST/cryptoST_execute.h"
#include "cryptoST/cryptoSTE_announce.h"
#include "cryptoST/cryptoSTE_print.h"
#include "../test_data/cryptoSpeedTestData.h"
#include "cryptoST/cryptoSTE_init.h"
#include "cryptoST/cryptoSTE_buildInfo.h"

#define PLATFORM "SAME54 XPlained Ultra"
#if defined(WOLFSSL_HAVE_MCHP_HW_CRYPTO)
#define ENCRYPTION_ENGINE "PUKCC|AES256|ICM"
#else
#define ENCRYPTION_ENGINE "Software" /* no acceleration */
#endif
#define HAVE_HW_DRIVERS     false
#define VERIFY_DATA_QUALITY
#define EXECUTE_SPEED_TEST

// *****************************************************************************
// *****************************************************************************
// Section: Local data structures
// *****************************************************************************
// *****************************************************************************
#if defined(EXECUTE_SPEED_TEST)
static cryptoSTE_parameters_t exec_repetitiveTimed =
{
    /* A value of zero here invokes the recommended iteration count
     * supplied in the data-result vectors for each test set.
     * A value of '1' though allows verification to be performed.
     * */
    .iterationOverride = 0,

    .verifyByDecryption = false,
    .verifyByGoldenCiphertext = false,
    
    // This is the default; actual may be spec'd later
    .displayType = CST_CSV,
    // .displayType does not affect the VERBOSE messages
};
#endif // EXECUTE_SPEED_TEST

#if defined(VERIFY_DATA_QUALITY)
static cryptoSTE_parameters_t exec_onceThroughAndCheck =
{
    /* A value of zero here invokes the recommended iteration count
     * supplied in the data-result vectors for each test set.
     * A value of '1' though allows verification to be performed.
     * */
    .iterationOverride = 1,

    .verifyByDecryption = true,
    .verifyByGoldenCiphertext = true,
    
    // This is the default; actual may be spec'd later
    .displayType = CST_TEXT,
    // .displayType does not affect the VERBOSE messages
};
#endif // VERIFY_DATA_QUALITY

// *****************************************************************************
// *****************************************************************************
// Section: Support routines
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
// *****************************************************************************
// Section: External API
// *****************************************************************************
// *****************************************************************************

void cryptoST(void)
{
    printf( "\r\n"
            " Microchip benchMark test suite\r\n"
            " Application created %s %s initialized!\r\n",
        cryptoSTE_buildInfo.buildDate, cryptoSTE_buildInfo.buildTime);

    if (CSTE_VERBOSE > 1) P0_UINT("Verbose level ", CSTE_VERBOSE);

    cryptoSTE_localData_t execData;
    cryptoSTE_init(&execData);
    
    execData.configuration.labels = (cryptoSTE_labels_t){
        .platform = PLATFORM,
        .processor = cryptoSTE_buildInfo.processor,
        .accelerator = ENCRYPTION_ENGINE,
        .build = "$ld:$",
    };
    
#if defined(VERIFY_DATA_QUALITY) // execute and verify all data sets
    execData.testsAttempted = execData.testsSucceeded = 0;

    execData.configuration.parameters = exec_onceThroughAndCheck;
    execData.configuration.parameters.displayType = CST_TEXT;
    execData.configuration.parameters.compareHWvSW = HAVE_HW_DRIVERS;
    cryptoSTE_announceParameters(&execData.configuration);

    printf("Encrypt/decrypt all data to demonstrate correct operation." CRLF);
    cryptoSTE(&execData);
    
    printf(CRLF "Tests attempted :%u" CRLF, execData.testsAttempted);
    printf(     "Tests successful:%u" CRLF, execData.testsSucceeded);
#endif
#if defined(EXECUTE_SPEED_TEST) // measure run-time of all data sets possibly w/o verification
    execData.testsAttempted = execData.testsSucceeded = 0;

    execData.configuration.parameters = exec_repetitiveTimed;
    execData.configuration.parameters.displayType = CST_CSV;
    execData.configuration.parameters.compareHWvSW = HAVE_HW_DRIVERS;
    cryptoSTE_announceParameters(&execData.configuration);
    
    printf("-----BEGIN TIMED TESTING-----" CRLF);
    cryptoSTE(&execData);
    printf("-----END TIMED TESTING-----" CRLF);
#endif
    
    printf(CRLF "Tests attempted :%u" CRLF, execData.testsAttempted);
    printf(     "Tests successful:%u" CRLF, execData.testsSucceeded);
}
