/*******************************************************************************
  System Exceptions File

  File Name:
    exceptions.c

  Summary:
    This file contains a function which overrides the default _weak_ exception
    handlers provided by the interrupt.c file.

  Description:
    This file redefines the default _weak_  exception handler with a more debug
    friendly one. If an unexpected exception occurs the code will stop in a
    while(1) loop.
 *******************************************************************************/

// DOM-IGNORE-BEGIN
/*******************************************************************************
Copyright (c) 2017-2018 released Microchip Technology Inc.  All rights reserved.

Microchip licenses to you the right to use, modify, copy and distribute
Software only when embedded on a Microchip microcontroller or digital signal
controller that is integrated into your product or third party product
(pursuant to the sublicense terms in the accompanying license agreement).

You should refer to the license agreement accompanying this Software for
additional information regarding your rights and obligations.

SOFTWARE AND DOCUMENTATION ARE PROVIDED AS IS WITHOUT WARRANTY OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF
MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE.
IN NO EVENT SHALL MICROCHIP OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER
CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR
OTHER LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES
INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE OR
CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT OF
SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES
(INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.
 *******************************************************************************/
// DOM-IGNORE-END

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************
#include "configuration.h"
#include "definitions.h"
#include <stdio.h>

// *****************************************************************************
// *****************************************************************************
// Section: Exception Handling Routine
// *****************************************************************************
// *****************************************************************************

/* Brief default interrupt handlers for core IRQs.*/

void NonMaskableInt_Handler(void)
{
#if defined(__DEBUG) || defined(__DEBUG_D) && defined(__XC32)
    __builtin_software_breakpoint();
#endif
    while (1)
    {
    }
}
void HardFault_Handler(void)
{
    asm("TST    LR, #4");
    asm("ITE    EQ");
    asm("MRSEQ  R0, MSP");
    asm("MRSNE  R0, PSP");
    asm("MOV    R1, LR");
    asm("B      HardFault_Handler_C");
}

void HardFault_Handler_C(uint32_t * hardfault_args, unsigned int lr_value)
{
    uint32_t stacked_r0;
    uint32_t stacked_r1;
    uint32_t stacked_r2;
    uint32_t stacked_r3;
    uint32_t stacked_r12;
    uint32_t stacked_lr;
    uint32_t stacked_pc;
    uint32_t stacked_psr;
    uint32_t cfsr;
    uint32_t bus_fault_address;
    uint32_t memmanage_fault_address;

    bus_fault_address       = SCB->BFAR;  // BusFault Address Register
    memmanage_fault_address = SCB->MMFAR; // MemManage Fault Address Register
    cfsr                    = SCB->CFSR;  // Configurable Fault Status Register

    stacked_r0  = hardfault_args[0];
    stacked_r1  = hardfault_args[1];
    stacked_r2  = hardfault_args[2];
    stacked_r3  = hardfault_args[3];
    stacked_r12 = hardfault_args[4];
    stacked_lr  = hardfault_args[5];  // Link Register
    stacked_pc  = hardfault_args[6];  // Program Counter
    stacked_psr = hardfault_args[7];  // Program Status Register

    printf("\r\n");
    printf("[HardFault]\r\n");
    printf("- Stack frame:\r\n");
    printf(" R0  = 0x%08lX\r\n", stacked_r0);
    printf(" R1  = 0x%08lX\r\n", stacked_r1);
    printf(" R2  = 0x%08lX\r\n", stacked_r2);
    printf(" R3  = 0x%08lX\r\n", stacked_r3);
    printf(" R12 = 0x%08lX\r\n", stacked_r12);
    printf(" LR  = 0x%08lX\r\n", stacked_lr);
    printf(" PC  = 0x%08lX\r\n", stacked_pc);
    printf(" PSR = 0x%08lX\r\n", stacked_psr);
    printf("- FSR/FAR:\r\n");
    printf(" CFSR = 0x%08lX\r\n", cfsr);
    printf(" HFSR = 0x%08lX\r\n", SCB->HFSR); // HardFault Status
    printf(" DFSR = 0x%08lX\r\n", SCB->DFSR); // Debug Fault Status
    printf(" AFSR = 0x%08lX\r\n", SCB->AFSR); // Auxiliary Fault Status
    if (cfsr & 0x0080) printf(" MMFAR = 0x%08lX\r\n", memmanage_fault_address);
    if (cfsr & 0x8000) printf(" BFAR = 0x%08lX\r\n", bus_fault_address);
    printf("- Misc\r\n");
    printf(" LR/EXC_RETURN = 0x%X, Bit 2: %d\r\n", lr_value, (lr_value & 0x4)>>2 );

  #if defined(__DEBUG) || defined(__DEBUG_D) && defined(__XC32)
    __builtin_software_breakpoint();
  #endif
    while (1)
    {
        // Do Nothing
    }
}

void DebugMonitor_Handler(void)
{
    asm("TST    LR, #4");
    asm("ITE    EQ");
    asm("MRSEQ  R0, MSP");
    asm("MRSNE  R0, PSP");
    asm("MOV    R1, LR");
    asm("B      DebugMonitor_Handler_C");
}

void DebugMonitor_Handler_C(uint32_t * hardfault_args, unsigned int lr_value)
{
    uint32_t stacked_r0;
    uint32_t stacked_r1;
    uint32_t stacked_r2;
    uint32_t stacked_r3;
    uint32_t stacked_r12;
    uint32_t stacked_lr;
    uint32_t stacked_pc;
    uint32_t stacked_psr;
    uint32_t cfsr;

    cfsr = SCB->CFSR;  // Configurable Fault Status Register

    stacked_r0  = hardfault_args[0];
    stacked_r1  = hardfault_args[1];
    stacked_r2  = hardfault_args[2];
    stacked_r3  = hardfault_args[3];
    stacked_r12 = hardfault_args[4];
    stacked_lr  = hardfault_args[5];  // Link Register
    stacked_pc  = hardfault_args[6];  // Program Counter
    stacked_psr = hardfault_args[7];  // Program Status Register

    printf("\r\n");
    printf("[DebugFault]\r\n");
    printf("- Stack frame:\r\n");
    printf(" R0  = 0x%08lX\r\n", stacked_r0);
    printf(" R1  = 0x%08lX\r\n", stacked_r1);
    printf(" R2  = 0x%08lX\r\n", stacked_r2);
    printf(" R3  = 0x%08lX\r\n", stacked_r3);
    printf(" R12 = 0x%08lX\r\n", stacked_r12);
    printf(" LR  = 0x%08lX\r\n", stacked_lr);
    printf(" PC  = 0x%08lX\r\n", stacked_pc);
    printf(" PSR = 0x%08lX\r\n", stacked_psr);
    printf("- FSR/FAR:\r\n");
    printf(" CFSR = 0x%08lX\r\n", cfsr);
    printf(" HFSR = 0x%08lX\r\n", SCB->HFSR); // HardFault Status
    printf(" DFSR = 0x%08lX\r\n", SCB->DFSR); // Debug Fault Status
    printf(" AFSR = 0x%08lX\r\n", SCB->AFSR); // Auxiliary Fault Status
    printf("- Misc\r\n");
    printf(" LR/EXC_RETURN = 0x%X, Bit 2: %d\r\n", lr_value, (lr_value & 0x4)>>2 );

  #if defined(__DEBUG) || defined(__DEBUG_D) && defined(__XC32)
    __builtin_software_breakpoint();
  #endif
    while (1)
    {
        // Do Nothing
    }
}


#if (defined __CM7_REV) || (defined __CM4_REV)

void MemoryManagement_Handler(void)
{
    asm("TST    LR, #4");
    asm("ITE    EQ");
    asm("MRSEQ  R0, MSP");
    asm("MRSNE  R0, PSP");
    asm("MOV    R1, LR");
    asm("B      MemoryManagement_Handler_C");
}

void MemoryManagement_Handler_C(uint32_t * hardfault_args, unsigned int lr_value)
{
    uint32_t stacked_r0;
    uint32_t stacked_r1;
    uint32_t stacked_r2;
    uint32_t stacked_r3;
    uint32_t stacked_r12;
    uint32_t stacked_lr;
    uint32_t stacked_pc;
    uint32_t stacked_psr;
    uint32_t cfsr;
    uint8_t  mmfsr;
    uint32_t memmanage_fault_address;

    memmanage_fault_address = SCB->MMFAR; // MemManage Fault Address Register
    cfsr                    = SCB->CFSR;  // Configurable Fault Status Register

    mmfsr = cfsr & 0xFF;  // MemManage Fault Status

    stacked_r0  = hardfault_args[0];
    stacked_r1  = hardfault_args[1];
    stacked_r2  = hardfault_args[2];
    stacked_r3  = hardfault_args[3];
    stacked_r12 = hardfault_args[4];
    stacked_lr  = hardfault_args[5];  // Link Register
    stacked_pc  = hardfault_args[6];  // Program Counter
    stacked_psr = hardfault_args[7];  // Program Status Register

    printf("\r\n");
    printf("[MemoryManagement]\r\n");
    printf("- Stack frame:\r\n");
    printf(" R0  = 0x%08lX\r\n", stacked_r0);
    printf(" R1  = 0x%08lX\r\n", stacked_r1);
    printf(" R2  = 0x%08lX\r\n", stacked_r2);
    printf(" R3  = 0x%08lX\r\n", stacked_r3);
    printf(" R12 = 0x%08lX\r\n", stacked_r12);
    printf(" LR  = 0x%08lX\r\n", stacked_lr);
    printf(" PC  = 0x%08lX\r\n", stacked_pc);
    printf(" PSR = 0x%08lX\r\n", stacked_psr);
    printf("- FSR/FAR:\r\n");
    printf(" CFSR  = 0x%08lX\r\n", cfsr);
    printf(" MMFSR = 0x%02X\r\n", mmfsr);
    printf(" HFSR  = 0x%08lX\r\n", SCB->HFSR); // HardFault Status
    printf(" DFSR  = 0x%08lX\r\n", SCB->DFSR); // Debug Fault Status
    printf(" AFSR  = 0x%08lX\r\n", SCB->AFSR); // Auxiliary Fault Status
    if (cfsr & 0x0080) printf(" MMFAR = 0x%08lX\r\n", memmanage_fault_address);
    printf("- Misc\r\n");
    printf(" LR/EXC_RETURN = 0x%X, Bit 2: %d\r\n", lr_value, (lr_value & 0x4)>>2 );

  #if defined(__DEBUG) || defined(__DEBUG_D) && defined(__XC32)
    __builtin_software_breakpoint();
  #endif
    while (1)
    {
        // Do Nothing
    }
}

void BusFault_Handler(void)
{
    asm("TST    LR, #4");
    asm("ITE    EQ");
    asm("MRSEQ  R0, MSP");
    asm("MRSNE  R0, PSP");
    asm("MOV    R1, LR");
    asm("B      BusFault_Handler_C");
}

void BusFault_Handler_C(uint32_t * hardfault_args, unsigned int lr_value)
{
    uint32_t stacked_r0;
    uint32_t stacked_r1;
    uint32_t stacked_r2;
    uint32_t stacked_r3;
    uint32_t stacked_r12;
    uint32_t stacked_lr;
    uint32_t stacked_pc;
    uint32_t stacked_psr;
    uint32_t cfsr;
    uint8_t  bfsr;
    uint32_t bus_fault_address;

    bus_fault_address = SCB->BFAR;  // BusFault Address Register
    cfsr              = SCB->CFSR;  // Configurable Fault Status Register

    bfsr = ( cfsr & 0x0000FF00 ) >>8;  // Bus Fault Status

    stacked_r0  = hardfault_args[0];
    stacked_r1  = hardfault_args[1];
    stacked_r2  = hardfault_args[2];
    stacked_r3  = hardfault_args[3];
    stacked_r12 = hardfault_args[4];
    stacked_lr  = hardfault_args[5];  // Link Register
    stacked_pc  = hardfault_args[6];  // Program Counter
    stacked_psr = hardfault_args[7];  // Program Status Register

    printf("\r\n");
    printf("[BusFault]\r\n");
    printf("- Stack frame:\r\n");
    printf(" R0  = 0x%08lX\r\n", stacked_r0);
    printf(" R1  = 0x%08lX\r\n", stacked_r1);
    printf(" R2  = 0x%08lX\r\n", stacked_r2);
    printf(" R3  = 0x%08lX\r\n", stacked_r3);
    printf(" R12 = 0x%08lX\r\n", stacked_r12);
    printf(" LR  = 0x%08lX\r\n", stacked_lr);
    printf(" PC  = 0x%08lX\r\n", stacked_pc);
    printf(" PSR = 0x%08lX\r\n", stacked_psr);
    printf("- FSR/FAR:\r\n");
    printf(" CFSR  = 0x%08lX\r\n", cfsr);
    printf(" BFSR  = 0x%02X\r\n",  bfsr);
    printf(" HFSR  = 0x%08lX\r\n", SCB->HFSR); // HardFault Status
    printf(" DFSR  = 0x%08lX\r\n", SCB->DFSR); // Debug Fault Status
    printf(" AFSR  = 0x%08lX\r\n", SCB->AFSR); // Auxiliary Fault Status
    if (bfsr & 0x04) printf(" ABFSR = 0x%08lX\r\n", SCB->ABFSR);
    if (bfsr & 0x80) printf(" BFAR = 0x%08lX\r\n", bus_fault_address);
    printf("- Misc\r\n");
    printf(" LR/EXC_RETURN = 0x%X, Bit 2: %d\r\n", lr_value, (lr_value & 0x4)>>2 );

  #if defined(__DEBUG) || defined(__DEBUG_D) && defined(__XC32)
    __builtin_software_breakpoint();
  #endif
    while (1)
    {
        // Do Nothing
    }
}

void UsageFault_Handler(void)
{
    asm("TST    LR, #4");
    asm("ITE    EQ");
    asm("MRSEQ  R0, MSP");
    asm("MRSNE  R0, PSP");
    asm("MOV    R1, LR");
    asm("B      UsageFault_Handler_C");
}

void UsageFault_Handler_C(uint32_t * hardfault_args, unsigned int lr_value)
{
    uint32_t stacked_r0;
    uint32_t stacked_r1;
    uint32_t stacked_r2;
    uint32_t stacked_r3;
    uint32_t stacked_r12;
    uint32_t stacked_lr;
    uint32_t stacked_pc;
    uint32_t stacked_psr;
    uint32_t cfsr;
    uint16_t ufsr;

    cfsr = SCB->CFSR;  // Configurable Fault Status Register
    ufsr = cfsr >> 16; // Usage Fault Status

    stacked_r0  = hardfault_args[0];
    stacked_r1  = hardfault_args[1];
    stacked_r2  = hardfault_args[2];
    stacked_r3  = hardfault_args[3];
    stacked_r12 = hardfault_args[4];
    stacked_lr  = hardfault_args[5];  // Link Register
    stacked_pc  = hardfault_args[6];  // Program Counter
    stacked_psr = hardfault_args[7];  // Program Status Register

    printf("\r\n");
    printf("[UsageFault]\r\n");
    printf("- Stack frame:\r\n");
    printf(" R0  = 0x%08lX\r\n", stacked_r0);
    printf(" R1  = 0x%08lX\r\n", stacked_r1);
    printf(" R2  = 0x%08lX\r\n", stacked_r2);
    printf(" R3  = 0x%08lX\r\n", stacked_r3);
    printf(" R12 = 0x%08lX\r\n", stacked_r12);
    printf(" LR  = 0x%08lX\r\n", stacked_lr);
    printf(" PC  = 0x%08lX\r\n", stacked_pc);
    printf(" PSR = 0x%08lX\r\n", stacked_psr);
    printf("- FSR/FAR:\r\n");
    printf(" CFSR = 0x%08lX\r\n", cfsr);
    printf(" UFSR = 0x%04X\r\n",  ufsr);
    printf(" HFSR = 0x%08lX\r\n", SCB->HFSR); // HardFault Status
    printf(" DFSR = 0x%08lX\r\n", SCB->DFSR); // Debug Fault Status
    printf(" AFSR = 0x%08lX\r\n", SCB->AFSR); // Auxiliary Fault Status
    printf("- Misc\r\n");
    printf(" LR/EXC_RETURN = 0x%X, Bit 2: %d\r\n", lr_value, (lr_value & 0x4)>>2 );

  #if defined(__DEBUG) || defined(__DEBUG_D) && defined(__XC32)
    __builtin_software_breakpoint();
  #endif
    while (1)
    {
        // Do Nothing
    }
}
#endif // (defined __CM7_REV) || (defined __CM4_REV)

/*******************************************************************************
 End of File
 */

