/*******************************************************************************
  MPLAB Harmony Application Header File

  Company:
    Microchip Technology Inc.

  File Name:
    cryptoST_DERformat.h

  Summary:
    Utilities for conversion to/from DER key format.

  Description:
    Utilities for conversion to/from DER key format.
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

/* Example:
 * from: https://crypto.stackexchange.com/questions/21102/what-is-the-ssl-private-key-file-format
 * 
 * 3082025c02010002818100aa18aba....  for a total of (15*40+8)=608 bytes (1216 char's)
 * The 30 is because it's a SEQUENCE tag.
 * The 82025c represents the length.
 *      The first byte means the length is of the "long form" (82 & 80)
 *      and that the next two bytes represent the length (82 & 7F).
 * So the actual length of the SEQUENCE is 025c (=604).
 * So after that is the value.
 * 
 * Then you get to the version. 
 *      02 is of type int, 
 *      01 is the tag length and 
 *      00 is the value.
 * Therefore, it's a two-prime key as opposed to a multi-prime key.
 * */

/* See PKCS#1v2.2 Appendix A.1.2
30 ASN.1 tag for sequence, a BER-TLV tag (Application class, Constructed encoding, Tag number 0)
82 01 39 Length as prefix plus two bytes, of 0x139 = 313 (number of bytes following)
02 ASN.1 tag for int, also a BER-TLV tag (Universal class, Primitive encoding, Tag number 2)
01 Length encoded on one byte, of 0x01 = 1
00 Version 0, meaning RSA private key with 2 primes
    02 ASN.1 tag for int
    41 Length encoded on one byte, of 0x41 = 65
    00 83 8B 7A 98 1D A9 7A CC D3 B3 B8 75 5F E7 27 98 12 03 5D A3 72 30 5E 05 72 B9 99 93 BB 19 CE FB F0 7B AF 84 98 BE 46 FA A1 4A 2F 36 12 E3 7D B0 73 F1 D6 24 2A 68 2B 97 B9 2D 6F A6 EA AF 62 25 public modulus n (big-endian, leftmost bit is sign)
    02 ASN.1 tag for int
    03 Length encoded on one byte, of 0x03 = 3
    01 00 01 public exponent e (big-endian, leftmost bit is sign)
    02 ASN.1 tag for int
    40 Length encoded on one byte, of 0x40 = 64
    4D 10 DB 0A E1 5D D8 46 C5 C4 65 CD C6 18 CB 96 88 FF 15 CD DA E9 41 3C 19 E1 68 7B 27 43 50 82 63 5A 27 DB 08 04 2C A6 D4 8F 21 3E 6F 85 CB 9D 66 05 84 30 34 97 AC 89 FB F6 75 EF C8 FC B9 05 private exponent d (big-endian, leftmost bit is sign)
    02 ASN.1 tag for int
    21 Length encoded on one byte, of 0x21 = 33
    00 F5 3E 5F 0A CB 1B 2D 07 77 84 68 BA 0F BD 21 13 2B 96 ED 20 B5 2B D3 25 15 90 FD BE E6 D1 F6 DF secret prime p (big-endian, leftmost bit is sign)
    02 ASN.1 tag for int
    21 Length encoded on one byte, of 0x21 = 33
    00 89 50 7B 6D 43 32 9D 97 F8 4B 05 49 F0 D0 05 E0 08 A4 06 66 31 38 93 D4 C6 73 E3 12 9F 03 DB 7B secret prime q (big-endian, leftmost bit is sign)
    02 ASN.1 tag for int
    20 Length encoded on one byte, of 0x20 = 32
    0D D9 70 DA 96 2F B9 B2 43 40 99 FD 6F E8 19 57 10 CE 1C 24 0D B7 24 DC 62 44 66 E0 01 FE F7 77 dp=dmod(p−1) (big-endian, leftmost bit is sign)
    02 ASN.1 tag for int
    20 Length encoded on one byte, of 0x20 = 32
    12 9A 7B CE 66 CF 41 B8 A8 24 09 D8 65 AE D9 4C EB FE C4 FB 2D 69 FB E5 54 E9 B8 76 FA 62 3C 67 dq=dmod(q−1) (big-endian, leftmost bit is sign)
    02 ASN.1 tag for int
    20 Length encoded on one byte, of 0x20 = 32
    7F 84 21 BB EC D8 08 97 C8 8E D2 49 A4 7D 65 1D 95 BE 03 AD 22 4E 12 AD 7B 36 82 93 B1 62 00 2E qinv=q−1modp (big-endian, leftmost bit is sign)
Therefore, this private keys has:

n = 6889562268374622799957651484276189567066573692163081374402850932375514118031048420110853972747558241305562483958233191802399592639320405757333978594894373
e = 65537
d = 4036265671212347870735218712159303880670782869380678233214786480134242711167668040594757438422211656546040377235338723652323162649874081271989898105895173
p = 110926848377808511478526072563819593239744031998335766139683653481372583065311
q = 62109059881601353504240950986730444628975000449359215027377545384004575026043
dp = 6264251733315063261699879374379301990940883202249731761950794231267222026103
dq = 8414580201851449070969916288679366126930879182597013446268294634551118019687
qinv = 57677188406707620788831013172875873422122983590947547357547002213122938372142
As expected, these values verify:

n=p⋅q
e⋅d≡1(modlcm(p−1,q−1))
dp=e−1mod(p−1)=dmod(p−1)
dq=e−1mod(q−1)=dmod(q−1)
qinv=q−1modp
The public modulus n is 512-bit, which is too small to be safe.
*/
