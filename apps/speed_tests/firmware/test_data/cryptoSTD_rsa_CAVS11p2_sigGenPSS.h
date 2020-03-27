/*******************************************************************************
  Crypto Speed Test Data File

  Company:
    Microchip Technology Inc.

  File Name:
    cryptoSTD_rsa_CAVS11p2.c

  Summary:
   From the 186-4 RSA Validation System (RSA2VS) as described in
   rsa2vs.pdf (9 July 2014 10:59:36am) with data from files found in
   the companion 186-3rsatestvectors.zip.   

  Description:
   Known-good data for RSA encryption with public key, requiring padding. See also the pdf file.
   https://csrc.nist.gov/presentations/2004/the-rsa-validation-system-(rsavs)
   https://csrc.nist.gov/Projects/Cryptographic-Algorithm-Validation-Program/Component-Testing
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

#ifndef CRYPTOSTV_RSA_CAVS11p2_sigGenPSS
#define CRYPTOSTV_RSA_CAVS11p2_sigGenPSS

#include "./cryptoSpeedTestData.h"

/*************************************************************
 * Obligatory entry points for executing a test
 *************************************************************/
extern cryptoST_testAPI_t const CAVS11p2_sigGenPSS;

#endif // CRYPTOSTV_RSA_CAVS11p2_sigGenPSS