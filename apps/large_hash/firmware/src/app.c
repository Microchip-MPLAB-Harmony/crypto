/*******************************************************************************
  MPLAB Harmony Application Source File

  Company:
    Microchip Technology Inc.

  File Name:
    app.c

  Summary:
    This file contains the source code for the MPLAB Harmony application.

  Description:
    This file contains the source code for the MPLAB Harmony application.  It
    implements the logic of the application's state machine and it may call
    API routines of other MPLAB Harmony modules in the system, such as drivers,
    system services, and middleware.  However, it does not call any of the
    system interfaces (such as the "Initialize" and "Tasks" functions) of any of
    the modules in the system or make any assumptions about when those functions
    are called.  That is the responsibility of the configuration-specific system
    files.
 *******************************************************************************/

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include "app.h"
//#include "crypto\src\sha256.h"


// *****************************************************************************
// *****************************************************************************
// Section: Global Data Definitions
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
/* Application Data

  Summary:
    Holds application data

  Description:
    This structure holds the application's data.

  Remarks:
    This structure should be initialized by the APP_Initialize function.

    Application strings and buffers are be defined outside this structure.
 */

APP_DATA appData;

// *****************************************************************************
// *****************************************************************************
// Section: Application Callback Functions
// *****************************************************************************
// *****************************************************************************


// *****************************************************************************
// *****************************************************************************
// Section: Application Local Functions
// *****************************************************************************
// *****************************************************************************


#if defined(RUN_FLASH_TEST)
static const uint8_t inputData[512 * 1024] = {[0 ... 524287] = 'a'};
#endif

/*****************************************************
 * Initialize the application data structure. All
 * application related variables are stored in this
 * data structure.
 *****************************************************/

APP_DATA appData ={
    .state = APP_STATE_INIT,
    .wrComplete = true,
    .rdComplete = true
};

static const uint8_t MD5Expected[] = "\x30\xc2\x55\x7e\x83\x02\xa5\xbe"
        "\xb2\x90\xc7\x15\x20\xd8\x7f\x42";
static const uint8_t SHAExpected[] = "\xf7\xfe\xc1\x28\xd7\xfc\xd5\x92"
        "\x22\xba\x37\x36\x8d\x3b\x72\x10"
        "\xd4\xc7\xb6\xef";
static const uint8_t SHA256Expected[] = "\x85\xa8\x4a\x75\x88\x6e\x8a\x52"
        "\x6d\xbe\xc4\xe1\x6e\x33\x75\xfa"
        "\xa3\x07\xb4\xae\xad\x79\xc9\xed"
        "\x32\x64\xc0\x47\x7a\x6f\x6e\xba";
static const uint8_t SHA384Expected[] = "\xa5\x50\x56\x1a\x63\x30\x04\x8e"
        "\xfe\x82\x6a\x97\xe5\xfe\xd8\x43"
        "\xfa\x1c\xe6\x46\xa9\xbf\x54\x6c"
        "\xcb\x43\x3c\x2f\xcb\x0e\x54\x82"
        "\x1c\x4c\x94\x5e\xed\x9a\x59\x2b"
        "\x5b\xf4\x31\x57\xe2\x12\xf2\x77";
static const uint8_t SHA512Expected[] = "\x7f\x49\x15\x7f\xb3\x59\xb3\x9e"
        "\xa6\xda\x93\x4d\xc9\xa1\x07\x09"
        "\xfe\xdf\x88\x46\xd1\x39\xd0\xe6"
        "\x37\xa3\xc0\xfc\x83\x3b\x6f\x42"
        "\x70\x38\x58\xdb\xac\xee\x28\xf4"
        "\x48\x9b\x5e\x95\xfa\xb5\xe5\x65"
        "\x5a\x25\xf8\x38\xb0\xdc\x7b\xf3"
        "\xc8\x4c\x7c\xc0\x26\x4f\x6a\x4f";

// *****************************************************************************
// *****************************************************************************
// Section: Application Local Routines
// *****************************************************************************
// *****************************************************************************
uint32_t APP_getTicks(void) {
    return SYS_TIME_CounterGet();
}

char printBuffer[50 * 1024] = {0};

void APP_DisplayHash(uint8_t *hash, uint32_t hashSz) {
    while (hashSz--) {
        sprintf(printBuffer, "%s%02X", printBuffer, *hash++);

        //sprintf(printBuffer, "%s%02X", *hash++);
    }
}

#if defined(RUN_FLASH_TEST)

void APP_Md5Run_Bulk(void) {
    CRYPT_MD5_CTX md5;
    uint32_t hashStart;
    uint32_t hashStop;
#if defined(MZ_DA)
    uint32_t currentFlashWS = PLIB_PCACHE_WaitStateGet(PCACHE_ID_0);
#endif


    CRYPT_MD5_Initialize(&md5);
    CRYPT_MD5_DataSizeSet(&md5, 512 * 1024);
    hashStart = APP_getTicks();
#if defined(MZ_DA)
    PLIB_PCACHE_WaitStateSet(PCACHE_ID_0, 4); // Necessary for crypto engine to work on MZ_DA parts.
#endif
    CRYPT_MD5_DataAdd(&md5, inputData, 512 * 1024);
    CRYPT_MD5_Finalize(&md5, appData.md5_result);
#if defined(MZ_DA)
    PLIB_PCACHE_WaitStateSet(PCACHE_ID_0, currentFlashWS);
#endif
    hashStop = APP_getTicks();
    appData.md5_timing = hashStop - hashStart;
}

void APP_ShaRun_Bulk(void) {
    CRYPT_SHA_CTX sha;
    uint32_t hashStart;
    uint32_t hashStop;
#if defined(MZ_DA)
    uint32_t currentFlashWS = PLIB_PCACHE_WaitStateGet(PCACHE_ID_0);
#endif

    // First, run by giving the entire block in flash.
    CRYPT_SHA_Initialize(&sha);
    CRYPT_SHA_DataSizeSet(&sha, 512 * 1024);
    hashStart = APP_getTicks();
#if defined(MZ_DA)
    PLIB_PCACHE_WaitStateSet(PCACHE_ID_0, 4); // Necessary for crypto engine to work on MZ_DA parts.
#endif
    CRYPT_SHA_DataAdd(&sha, inputData, 512 * 1024);
    CRYPT_SHA_Finalize(&sha, appData.sha1_result);
#if defined(MZ_DA)
    PLIB_PCACHE_WaitStateSet(PCACHE_ID_0, currentFlashWS);
#endif
    hashStop = APP_getTicks();
    appData.sha1_timing = hashStop - hashStart;
}

void APP_Sha256Run_Bulk(void) {
    CRYPT_SHA256_CTX sha256;
    uint32_t hashStart;
    uint32_t hashStop;
#if defined(MZ_DA)
    uint32_t currentFlashWS = PLIB_PCACHE_WaitStateGet(PCACHE_ID_0);
#endif

    CRYPT_SHA256_Initialize(&sha256);
    CRYPT_SHA256_DataSizeSet(&sha256, 512 * 1024);
    hashStart = APP_getTicks();
#if defined(MZ_DA)
    PLIB_PCACHE_WaitStateSet(PCACHE_ID_0, 4); // Necessary for crypto engine to work on MZ_DA parts.
#endif
    CRYPT_SHA256_DataAdd(&sha256, inputData, 512 * 1024);
    CRYPT_SHA256_Finalize(&sha256, appData.sha256_result);
#if defined(MZ_DA)
    PLIB_PCACHE_WaitStateSet(PCACHE_ID_0, currentFlashWS);
#endif
    hashStop = APP_getTicks();
    appData.sha256_timing = hashStop - hashStart;
}

void APP_Sha384Run_Bulk(void) {
    CRYPT_SHA384_CTX sha384;
    uint32_t hashStart;
    uint32_t hashStop;

    CRYPT_SHA384_Initialize(&sha384);
    hashStart = APP_getTicks();
    CRYPT_SHA384_DataAdd(&sha384, inputData, 512 * 1024);
    CRYPT_SHA384_Finalize(&sha384, appData.sha384_result);
    hashStop = APP_getTicks();
    appData.sha384_timing = hashStop - hashStart;
}

void APP_Sha512Run_Bulk(void) {
    CRYPT_SHA512_CTX sha512;
    uint32_t hashStart;
    uint32_t hashStop;

    CRYPT_SHA512_Initialize(&sha512);
    hashStart = APP_getTicks();
    CRYPT_SHA512_DataAdd(&sha512, inputData, 512 * 1024);
    CRYPT_SHA512_Finalize(&sha512, appData.sha512_result);
    hashStop = APP_getTicks();
    appData.sha512_timing = hashStop - hashStart;
}
#endif

void APP_Md5Run_Feed(void) {
    CRYPT_MD5_CTX md5;
    uint32_t hashStart;
    uint32_t hashStop;
    uint8_t myBuf[1024];
    int i;

    CRYPT_MD5_Initialize(&md5);
    memset(myBuf, 'a', 1024);
#if defined(WOLFSSL_MICROCHIP_PIC32MZ)
    // Write out the cache if we're running the hardware engine.
    SYS_DEVCON_DataCacheClean((uint32_t) myBuf, 1024);
#endif
    CRYPT_MD5_DataSizeSet(&md5, 512 * 1024);
    hashStart = APP_getTicks();
    for (i = 0; i < 512; i++)
        CRYPT_MD5_DataAdd(&md5, myBuf, sizeof (myBuf));
    CRYPT_MD5_Finalize(&md5, appData.md5_feed_result);
    hashStop = APP_getTicks();
    appData.md5_feed_timing = hashStop - hashStart;
}
uint8_t __attribute__((aligned(64))) myBuf[1024];

void APP_ShaRun_Feed(void) {
    CRYPT_SHA_CTX sha;
    uint32_t hashStart;
    uint32_t hashStop;
    int i;

    CRYPT_SHA_Initialize(&sha);
    memset(myBuf, 'a', sizeof (myBuf));
#if defined(WOLFSSL_MICROCHIP_PIC32MZ)
    // Write out the cache if we're running the hardware engine.
    SYS_DEVCON_DataCacheClean((uint32_t) myBuf, 1024);
#endif
    CRYPT_SHA_DataSizeSet(&sha, 512 * 1024);
    hashStart = APP_getTicks();
    for (i = 0; i < 512; i++)
        CRYPT_SHA_DataAdd(&sha, myBuf, sizeof (myBuf));
    CRYPT_SHA_Finalize(&sha, appData.sha1_feed_result);
    hashStop = APP_getTicks();
    appData.sha1_feed_timing = hashStop - hashStart;
}
#if 0
char outputBuffer[160 * 512] = {0};

void printHash(uint32_t * digest) {
    for (int x = 0; x < 8; x++) {
        snprintf(outputBuffer, sizeof (outputBuffer), "%s%08x", outputBuffer, (unsigned int) digest[x]);
    }
}
#endif

void APP_Sha256Run_Feed(void) {
    CRYPT_SHA256_CTX sha256;
    uint32_t hashStart;
    uint32_t hashStop;
    int i;

    CRYPT_SHA256_Initialize(&sha256);
    memset(myBuf, 'a', sizeof (myBuf));
#if defined(WOLFSSL_MICROCHIP_PIC32MZ)
    // Write out the cache if we're running the hardware engine.
    SYS_DEVCON_DataCacheClean((uint32_t) myBuf, 1024);
#endif
    CRYPT_SHA256_DataSizeSet(&sha256, 512 * 1024);
    hashStart = APP_getTicks();
    //Sha256 * shaPtr = (Sha256 *) & sha256;
    for (i = 0; i < 512; i++) {
        CRYPT_SHA256_DataAdd(&sha256, myBuf, sizeof (myBuf));
#if 0
#if defined(WOLFSSL_PIC32C_HASH)
        snprintf(outputBuffer, sizeof (outputBuffer), "%sSize %lld: ", outputBuffer, shaPtr->total_len);
#else
        snprintf(outputBuffer, sizeof (outputBuffer), "%sSize %d: ", outputBuffer, shaPtr->loLen);
#endif
        printHash((uint32_t*) shaPtr->digest);
        snprintf(outputBuffer, sizeof (outputBuffer), "%s\r\n", outputBuffer);
#endif
    }
    CRYPT_SHA256_Finalize(&sha256, appData.sha256_feed_result);
#if 0
    snprintf(outputBuffer, sizeof (outputBuffer), "%sFinal: ", outputBuffer);
    printHash((uint32_t*) appData.sha256_feed_result);
    snprintf(outputBuffer, sizeof (outputBuffer), "%s\r\n", outputBuffer);
    SYS_CONSOLE_Write(SYS_CONSOLE_INDEX_0, STDOUT_FILENO, outputBuffer, strlen(outputBuffer));
#endif
    hashStop = APP_getTicks();
    appData.sha256_feed_timing = hashStop - hashStart;
}

void APP_Sha384Run_Feed(void) {
    CRYPT_SHA384_CTX sha384;
    uint32_t hashStart;
    uint32_t hashStop;
    uint8_t myBuf[1024];
    int i;

    CRYPT_SHA384_Initialize(&sha384);
    memset(myBuf, 'a', 1024);
    hashStart = APP_getTicks();
    for (i = 0; i < 512; i++)
        CRYPT_SHA384_DataAdd(&sha384, myBuf, sizeof (myBuf));
    CRYPT_SHA384_Finalize(&sha384, appData.sha384_feed_result);
    hashStop = APP_getTicks();
    appData.sha384_feed_timing = hashStop - hashStart;
}

void APP_Sha512Run_Feed(void) {
    CRYPT_SHA512_CTX sha512;
    uint32_t hashStart;
    uint32_t hashStop;
    uint8_t myBuf[1024];
    int i;

    CRYPT_SHA512_Initialize(&sha512);
    memset(myBuf, 'a', 1024);
    hashStart = APP_getTicks();
    for (i = 0; i < 512; i++)
        CRYPT_SHA512_DataAdd(&sha512, myBuf, sizeof (myBuf));
    CRYPT_SHA512_Finalize(&sha512, appData.sha512_feed_result);
    hashStop = APP_getTicks();
    appData.sha512_feed_timing = hashStop - hashStart;
}

// *****************************************************************************
// *****************************************************************************
// Section: Application Callback Functions
// *****************************************************************************
// *****************************************************************************

void APP_ReadComplete(void *handle) {
    appData.rdComplete = true;
}

void APP_WriteComplete(void *handle) {
    appData.wrComplete = true;
}

void APP_Reset() {
    appData.rdComplete = true;
    appData.wrComplete = true;
}


// *****************************************************************************
// *****************************************************************************
// Section: Application Initialization and State Machine Functions
// *****************************************************************************
// *****************************************************************************

/*******************************************************************************
  Function:
    void APP_Initialize ( void )

  Remarks:
    See prototype in app.h.
 */
char *msgBuffer = "\r\n Application created " __DATE__ " " __TIME__ " initialized!\r\n";

void APP_Initialize(void) {
    /* Place the App state machine in its initial state. */
    appData.state = APP_STATE_INIT;

}

/******************************************************************************
  Function:
    void APP_Tasks ( void )

  Remarks:
    See prototype in app.h.
 */

void APP_Tasks(void) {

    static int i;

    /* Check the application's current state. */
    switch (appData.state) {
            /* Application's initial state. */
        case APP_STATE_INIT:
        {
            /* Show Hyperterminal is working using available output functions */
            //            SYS_MESSAGE("SYS_MESSAGE:" "\r\n Application created " __DATE__ " " __TIME__ " initialized!\r\n");            
            //            SYS_DEBUG(SYS_ERROR_INFO,"SYS_DEBUG:" "\r\n Application created " __DATE__ " " __TIME__ " initialized!\r\n");
            // SYS_CONSOLE_Write(SYS_CONSOLE_INDEX_0, STDOUT_FILENO, msgBuffer, strlen(msgBuffer));            


            appData.state = APP_STATE_RUN_MD5_FEED;
            break;
        }


#if defined(RUN_FLASH_TEST)
        case APP_STATE_RUN_MD5_BULK:
            APP_Md5Run_Bulk();
            appData.state = APP_STATE_RUN_SHA1_BULK;
            break;

        case APP_STATE_RUN_SHA1_BULK:
            APP_ShaRun_Bulk();
            appData.state = APP_STATE_RUN_SHA256_BULK;
            break;

        case APP_STATE_RUN_SHA256_BULK:
            APP_Sha256Run_Bulk();
            appData.state = APP_STATE_RUN_SHA384_BULK;
            break;

        case APP_STATE_RUN_SHA384_BULK:
            APP_Sha384Run_Bulk();
            appData.state = APP_STATE_RUN_SHA512_BULK;
            break;

        case APP_STATE_RUN_SHA512_BULK:
            APP_Sha512Run_Bulk();
            i = 0;
            appData.state = APP_STATE_RUN_MD5_FEED;
            break;
#endif

        case APP_STATE_RUN_MD5_FEED:
            APP_Md5Run_Feed();
            appData.state = APP_STATE_RUN_SHA1_FEED;
            break;

        case APP_STATE_RUN_SHA1_FEED:
            APP_ShaRun_Feed();
            appData.state = APP_STATE_RUN_SHA256_FEED;
            break;

        case APP_STATE_RUN_SHA256_FEED:
            APP_Sha256Run_Feed();
            appData.state = APP_STATE_RUN_SHA384_FEED;
            break;

        case APP_STATE_RUN_SHA384_FEED:
            APP_Sha384Run_Feed();
            appData.state = APP_STATE_RUN_SHA512_FEED;
            break;

        case APP_STATE_RUN_SHA512_FEED:
            APP_Sha512Run_Feed();
            i = 0;
            appData.state = APP_STATE_DISPLAY_RESULTS;
            break;

        case APP_STATE_DISPLAY_RESULTS:
            switch (i) {
                case 0:

#if (RUN_FLASH_TEST)
                    sprintf(printBuffer, "%s\n\rMD5 from Flash:    ", printBuffer);
                    APP_DisplayHash(appData.md5_result, CRYPT_MD5_DIGEST_SIZE);
                    sprintf(printBuffer, "%s\t took %d clock cycles", printBuffer, (int) appData.md5_timing);
#endif
                    break;

                case 1:
                    sprintf(printBuffer, "%s\n\rMD5 from feed:     ", printBuffer);
                    APP_DisplayHash(appData.md5_feed_result, CRYPT_MD5_DIGEST_SIZE);
                    sprintf(printBuffer, "%s\t took %d clock cycles", printBuffer, (int) appData.md5_feed_timing);
                    break;

                case 2:
#if (RUN_FLASH_TEST)
                    sprintf(printBuffer, "%s\n\rSHA from Flash:    ", printBuffer);
                    APP_DisplayHash(appData.sha1_result, CRYPT_SHA_DIGEST_SIZE);
                    sprintf(printBuffer, "%s\t took %d clock cycles", printBuffer, (int) appData.sha1_timing);
#endif
                    break;

                case 3:
                    sprintf(printBuffer, "%s\n\rSHA from feed:     ", printBuffer);
                    APP_DisplayHash(appData.sha1_feed_result, CRYPT_SHA_DIGEST_SIZE);
                    sprintf(printBuffer, "%s\t took %d clock cycles", printBuffer, (int) appData.sha1_feed_timing);
                    break;

                case 4:
#if (RUN_FLASH_TEST)
                    sprintf(printBuffer, "%s\n\rSHA256 from Flash: ", printBuffer);
                    APP_DisplayHash(appData.sha256_result, CRYPT_SHA256_DIGEST_SIZE);
                    sprintf(printBuffer, "%s\t took %d clock cycles", printBuffer, (int) appData.sha256_timing);
#endif
                    break;

                case 5:
                    sprintf(printBuffer, "%s\n\rSHA256 from feed:  ", printBuffer);
                    APP_DisplayHash(appData.sha256_feed_result, CRYPT_SHA256_DIGEST_SIZE);
                    sprintf(printBuffer, "%s\t took %d clock cycles", printBuffer, (int) appData.sha256_feed_timing);
                    break;

                case 6:
#if (RUN_FLASH_TEST)
                    sprintf(printBuffer, "%s\n\rSHA384 from Flash: ", printBuffer);
                    APP_DisplayHash(appData.sha384_result, CRYPT_SHA384_DIGEST_SIZE);
                    sprintf(printBuffer, "%s\t took %d clock cycles", printBuffer, (int) appData.sha384_timing);
#endif
                    break;

                case 7:
                    sprintf(printBuffer, "%s\n\rSHA384 from feed:  ", printBuffer);
                    APP_DisplayHash(appData.sha384_feed_result, CRYPT_SHA384_DIGEST_SIZE);
                    sprintf(printBuffer, "%s\t took %d clock cycles", printBuffer, (int) appData.sha384_feed_timing);
                    break;

                case 8:
#if (RUN_FLASH_TEST)
                    sprintf(printBuffer, "%s\n\rSHA512 from Flash: ", printBuffer);
                    APP_DisplayHash(appData.sha512_result, CRYPT_SHA512_DIGEST_SIZE);
                    sprintf(printBuffer, "%s\t took %d clock cycles", printBuffer, (int) appData.sha512_timing);
#endif
                    break;

                case 9:
                    sprintf(printBuffer, "%s\n\rSHA512 from feed:  ", printBuffer);
                    APP_DisplayHash(appData.sha512_feed_result, CRYPT_SHA512_DIGEST_SIZE);
                    sprintf(printBuffer, "%s\t took %d clock cycles", printBuffer, (int) appData.sha512_feed_timing);
                    break;
            }
            i++;
            if (i > 9)
                appData.state = APP_STATE_CHECK_RESULTS;
            else {
                appData.state = APP_STATE_WAIT_FOR_CONSOLE;
            }
            break;

        case APP_STATE_CHECK_RESULTS:
            if (
#if (RUN_FLASH_TEST)
                    memcmp(MD5Expected, appData.md5_result, CRYPT_MD5_DIGEST_SIZE) ||
                    memcmp(SHAExpected, appData.sha1_result, CRYPT_SHA_DIGEST_SIZE) ||
                    memcmp(SHA256Expected, appData.sha256_result, CRYPT_SHA256_DIGEST_SIZE) ||
                    memcmp(SHA384Expected, appData.sha384_result, CRYPT_SHA384_DIGEST_SIZE) ||
                    memcmp(SHA512Expected, appData.sha512_result, CRYPT_SHA512_DIGEST_SIZE) ||
#endif
                    memcmp(MD5Expected, appData.md5_feed_result, CRYPT_MD5_DIGEST_SIZE) ||
                    memcmp(SHAExpected, appData.sha1_feed_result, CRYPT_SHA_DIGEST_SIZE) ||
                    memcmp(SHA256Expected, appData.sha256_feed_result, CRYPT_SHA256_DIGEST_SIZE) ||
                    memcmp(SHA384Expected, appData.sha384_feed_result, CRYPT_SHA384_DIGEST_SIZE) ||
                    memcmp(SHA512Expected, appData.sha512_feed_result, CRYPT_SHA512_DIGEST_SIZE)) {
                // We had an error during comparions
                sprintf(printBuffer, "%s\n\rA test failed.", printBuffer);
                //BSP_LEDOn(BSP_LED_1);
            } else {
                sprintf(printBuffer, "%s\n\rAll tests passed.", printBuffer);
                //BSP_LEDOn(BSP_LED_3);
            }
            SYS_CONSOLE_Write(SYS_CONSOLE_INDEX_0, STDOUT_FILENO, printBuffer, strlen(printBuffer));
            appData.state = APP_SPIN;
            break;

        case APP_STATE_WAIT_FOR_CONSOLE:
            //            if (appData.wrComplete)
            if (appData.wallTime <= APP_getTicks())
                appData.state = APP_STATE_DISPLAY_RESULTS;
            break;

        case APP_SPIN:

            /* The default state should never be executed. */
        default:
        {
            /* TODO: Handle error in application's state machine. */
            break;
        }
    }
}


/*******************************************************************************
 End of File
 */
