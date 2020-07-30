/*******************************************************************************
  System Initialization File

  File Name:
    initialization.c

  Summary:
    This file contains source code necessary to initialize the system.

  Description:
    This file contains source code necessary to initialize the system.  It
    implements the "SYS_Initialize" function, defines the configuration bits,
    and allocates any necessary global system resources,
 *******************************************************************************/

// DOM-IGNORE-BEGIN
/*******************************************************************************
* Copyright (C) 2018 Microchip Technology Inc. and its subsidiaries.
*
* Subject to your compliance with these terms, you may use Microchip software
* and any derivatives exclusively with Microchip products. It is your
* responsibility to comply with third party license terms applicable to your
* use of third party software (including open source software) that may
* accompany Microchip software.
*
* THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
* EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
* WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
* PARTICULAR PURPOSE.
*
* IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
* INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
* WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
* BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
* FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
* ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
* THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *******************************************************************************/
// DOM-IGNORE-END

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************
#include "configuration.h"
#include "definitions.h"
#include "device.h"



// ****************************************************************************
// ****************************************************************************
// Section: Configuration Bits
// ****************************************************************************
// ****************************************************************************
// #pragma config NVMCTRL_SULCK = 0x7
#pragma config NVMCTRL_NSULCK = 0x7
#pragma config BOD33_LEVEL = 0x6
#pragma config BOD33_DIS = CLEAR
#pragma config BOD33_ACTION = 0x1
#pragma config WDT_RUNSTDBY = CLEAR
#pragma config WDT_ENABLE = CLEAR
#pragma config WDT_ALWAYSON = CLEAR
#pragma config WDT_PER = 0xB
#pragma config WDT_WINDOW = 0xB
#pragma config WDT_EWOFFSET = 0xB
#pragma config WDT_WEN = CLEAR
#pragma config BOD33_HYST = CLEAR
#pragma config IDAU_AS = 0xff
#pragma config IDAU_ANSC = 0x0
#pragma config IDAU_DS = 0x8
#pragma config IDAU_RS = 0x7f
#pragma config NVMCTRL_URWEN = SET
#pragma config NONSECA_PAC = CLEAR
#pragma config NONSECA_PM = CLEAR
#pragma config NONSECA_MCLK = CLEAR
#pragma config NONSECA_RSTC = CLEAR
#pragma config NONSECA_OSCCTRL = CLEAR
#pragma config NONSECA_OSC32KCTRL = CLEAR
#pragma config NONSECA_SUPC = CLEAR
#pragma config NONSECA_GCLK = CLEAR
#pragma config NONSECA_WDT = CLEAR
#pragma config NONSECA_RTC = CLEAR
#pragma config NONSECA_EIC = CLEAR
#pragma config NONSECA_FREQM = CLEAR
#pragma config NONSECA_PORT = CLEAR
#pragma config NONSECA_AC = CLEAR
#pragma config NONSECB_IDAU = CLEAR
#pragma config NONSECB_DSU = CLEAR
#pragma config NONSECB_NVMCTRL = CLEAR
#pragma config NONSECB_DMAC = CLEAR
#pragma config NONSECC_EVSYS = CLEAR
#pragma config NONSECC_SERCOM0 = CLEAR
#pragma config NONSECC_SERCOM1 = CLEAR
#pragma config NONSECC_SERCOM2 = CLEAR
#pragma config NONSECC_TC0 = CLEAR
#pragma config NONSECC_TC1 = CLEAR
#pragma config NONSECC_TC2 = CLEAR
#pragma config NONSECC_ADC = CLEAR
#pragma config NONSECC_DAC = CLEAR
#pragma config NONSECC_PTC = CLEAR
#pragma config NONSECC_TRNG = CLEAR
#pragma config NONSECC_CCL = CLEAR
#pragma config NONSECC_OPAMP = CLEAR
#pragma config NONSECC_TRAM = CLEAR
#pragma config BOOTROM_USERCRC = 0x8433651e

/* Do not remove the following line when performing Harmony3 code build. 
 * Refer to the crypt library release notes for V3.5. 
 */
void TC0_TimerCallbackRegister
    (SYS_TIME_PLIB_CALLBACK callback, uintptr_t context){}



// *****************************************************************************
// *****************************************************************************
// Section: Driver Initialization Data
// *****************************************************************************
// *****************************************************************************


// *****************************************************************************
// *****************************************************************************
// Section: System Data
// *****************************************************************************
// *****************************************************************************
/* Structure to hold the object handles for the modules in the system. */
SYSTEM_OBJECTS sysObj;

// *****************************************************************************
// *****************************************************************************
// Section: Library/Stack Initialization Data
// *****************************************************************************
// *****************************************************************************


// *****************************************************************************
// *****************************************************************************
// Section: System Initialization
// *****************************************************************************
// *****************************************************************************
// <editor-fold defaultstate="collapsed" desc="SYS_TIME Initialization Data">

const SYS_TIME_PLIB_INTERFACE sysTimePlibAPI = {
    .timerCallbackSet = (SYS_TIME_PLIB_CALLBACK_REGISTER)TC0_TimerCallbackRegister,
    .timerStart = (SYS_TIME_PLIB_START)TC0_TimerStart,
    .timerStop = (SYS_TIME_PLIB_STOP)TC0_TimerStop,
    .timerFrequencyGet = (SYS_TIME_PLIB_FREQUENCY_GET)TC0_TimerFrequencyGet,
    .timerPeriodSet = (SYS_TIME_PLIB_PERIOD_SET)TC0_Timer32bitPeriodSet,
    .timerCompareSet = (SYS_TIME_PLIB_COMPARE_SET)TC0_Timer32bitCompareSet,
    .timerCounterGet = (SYS_TIME_PLIB_COUNTER_GET)TC0_Timer32bitCounterGet,
};

const SYS_TIME_INIT sysTimeInitData =
{
    .timePlib = &sysTimePlibAPI,
    .hwTimerIntNum = TC0_IRQn,
};

// </editor-fold>



// *****************************************************************************
// *****************************************************************************
// Section: Local initialization functions
// *****************************************************************************
// *****************************************************************************



/*******************************************************************************
  Function:
    void SYS_Initialize ( void *data )

  Summary:
    Initializes the board, services, drivers, application and other modules.

  Remarks:
 */

void SYS_Initialize ( void* data )
{
    NVMCTRL_REGS->NVMCTRL_CTRLB = NVMCTRL_CTRLB_RWS(2);

    PM_Initialize();

  
    PORT_Initialize();

    CLOCK_Initialize();



    NVMCTRL_Initialize();

	BSP_Initialize();
    EVSYS_Initialize();

    SERCOM0_USART_Initialize();

    TC0_TimerInitialize();



    sysObj.sysTime = SYS_TIME_Initialize(SYS_TIME_INDEX_0, (SYS_MODULE_INIT *)&sysTimeInitData);

    CRYPT_WCCB_Initialize();

    APP_Initialize();


    NVIC_Initialize();

}


/*******************************************************************************
 End of File
*/
