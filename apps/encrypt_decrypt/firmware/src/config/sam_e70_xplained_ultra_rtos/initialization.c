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


// ****************************************************************************
// ****************************************************************************
// Section: Configuration Bits
// ****************************************************************************
// ****************************************************************************
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
#pragma config TCM_CONFIGURATION = 0
#pragma config SECURITY_BIT = CLEAR
#pragma config BOOT_MODE = SET



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
// <editor-fold defaultstate="collapsed" desc="SYS_CONSOLE Instance 0 Initialization Data">

static QElement sysConsole0UARTRdQueueElements[SYS_CONSOLE_UART_RD_QUEUE_DEPTH_IDX0];
static QElement sysConsole0UARTWrQueueElements[SYS_CONSOLE_UART_WR_QUEUE_DEPTH_IDX0];

/* Declared in console device implementation (sys_console_uart.c) */
extern const SYS_CONSOLE_DEV_DESC sysConsoleUARTDevDesc;

const SYS_CONSOLE_UART_PLIB_INTERFACE sysConsole0UARTPlibAPI =
{
    .read = (SYS_CONSOLE_UART_PLIB_READ)USART1_Read,
    .write = (SYS_CONSOLE_UART_PLIB_WRITE)USART1_Write,
    .readCallbackRegister = (SYS_CONSOLE_UART_PLIB_REGISTER_CALLBACK_READ)USART1_ReadCallbackRegister,
    .writeCallbackRegister = (SYS_CONSOLE_UART_PLIB_REGISTER_CALLBACK_WRITE)USART1_WriteCallbackRegister,
    .errorGet = (SYS_CONSOLE_UART_PLIB_ERROR_GET)USART1_ErrorGet,
};

const SYS_CONSOLE_UART_INIT_DATA sysConsole0UARTInitData =
{
    .uartPLIB = &sysConsole0UARTPlibAPI,
    .readQueueElementsArr = sysConsole0UARTRdQueueElements,
    .writeQueueElementsArr = sysConsole0UARTWrQueueElements,
    .readQueueDepth = SYS_CONSOLE_UART_RD_QUEUE_DEPTH_IDX0,
    .writeQueueDepth = SYS_CONSOLE_UART_WR_QUEUE_DEPTH_IDX0,
    .interruptSource = USART1_IRQn,
};

const SYS_CONSOLE_INIT sysConsole0Init =
{
    .deviceInitData = (const void*)&sysConsole0UARTInitData,
    .consDevDesc = &sysConsoleUARTDevDesc,
    .deviceIndex = 0,
};


// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="SYS_TIME Initialization Data">

const SYS_TIME_PLIB_INTERFACE sysTimePlibAPI = {
    .timerCallbackSet = (SYS_TIME_PLIB_CALLBACK_REGISTER)TC0_CH0_TimerCallbackRegister,
    .timerCounterGet = (SYS_TIME_PLIB_COUNTER_GET)TC0_CH0_TimerCounterGet,
    .timerPeriodSet = (SYS_TIME_PLIB_PERIOD_SET)TC0_CH0_TimerPeriodSet,
    .timerFrequencyGet = (SYS_TIME_PLIB_FREQUENCY_GET)TC0_CH0_TimerFrequencyGet,
    .timerCompareSet = (SYS_TIME_PLIB_COMPARE_SET)TC0_CH0_TimerCompareSet,
    .timerStart = (SYS_TIME_PLIB_START)TC0_CH0_TimerStart,
    .timerStop = (SYS_TIME_PLIB_STOP)TC0_CH0_TimerStop 
};

const SYS_TIME_INIT sysTimeInitData =
{
    .timePlib = &sysTimePlibAPI,
    .hwTimerIntNum = TC0_CH0_IRQn,
};

// </editor-fold>


/*******************************************************************************
  Function:
    void SYS_Initialize ( void *data )

  Summary:
    Initializes the board, services, drivers, application and other modules.

  Remarks:
 */

void SYS_Initialize ( void* data )
{
    CLK_Initialize();
	PIO_Initialize();


	BSP_Initialize();
    NVIC_Initialize();
	RSWDT_REGS->RSWDT_MR = RSWDT_MR_WDDIS_Msk;	// Disable RSWDT 

	WDT_REGS->WDT_MR = WDT_MR_WDDIS_Msk; 		// Disable WDT 

 
    TC0_CH0_TimerInitialize(); 
     
    
	USART1_Initialize();



    sysObj.sysConsole0 = SYS_CONSOLE_Initialize(SYS_CONSOLE_INDEX_0, (SYS_MODULE_INIT *)&sysConsole0Init);

    sysObj.sysTime = SYS_TIME_Initialize(SYS_TIME_INDEX_0, (SYS_MODULE_INIT *)&sysTimeInitData);


    APP_Initialize();


}


/*******************************************************************************
 End of File
*/
