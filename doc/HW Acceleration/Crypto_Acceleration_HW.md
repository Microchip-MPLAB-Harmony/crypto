#Microchip MCU32/MPU32 Crypto Acceleration Hardware

## SAME54P20A
U2009 - PUKCC("PUblic-Key Cryptography Controller")    
U2238 - AES(Advanced Encryption Standard)    
U2242 - TRNG(True Random Number Generator)

U2224 - I2SC

## SAME70Q21B (Canopus)
6149  - AES (Keysize: 128,192,256)    
6334  - TRNG(True Random Number Generator)

11241 - I2SC
6078  - SSC

## SAM L11 (Lifeguard)
Boot Protection
U2802 - FUSES(Non-Volatile Fuses)     
U2801 - TRAM(TrustRAM)    
U2242 - TRNG(True Random Number Generator)   
     
U2803 - IDAU(Implementation Defined Attribution Unit, CRYA)

## PIC32MZ2048EFM144 (Chicagoland)   
ICM(AES,DES,SHA,MD5)    
00158 - "CRYPTO"    
00159 - "RNG"   
    
## PIC32MZ-W (Rio2)
ICM(AES,DES,SHA,MD5)    
00343 - BA414E (Asymmetric Crypto  Module)
00158 - CRYPTO (Symmetric Crypto Module)    
00350 - RNG (Random Number Generator)   

NOTE: MHC Generated BA414E Driver not working.

## A5D27
6149  - AES (Advanced Encryption Standard, Keysize: 128,192,256)
11145 - AESB (
6150  - TDES (Triple Data Encryption Standard)

## 9x60
6149  - AES(Advanced Encryption Standard)    
11038 - PMECC("Programmable Multibit Error Correction Code Controller")    
11039 - PMERRLOC("Programmable Multibit ECC Error Location")   
6156  - SHA(Secure Hash Algorithm)   
6150  - TDES(Triple Data Encryption Standard)   
6334  - TRNG(True Random Number Generator)   

44157 - I2SMCC (Multi Channel Controller)  
6350  - ISI (Image Sensor Interface)

## RH71
44125 - TCMECC   (not in speed test) 
6334  - TRNG(True Random Number Generator)
6156  - SHA(Secure Hash Algorithm)   


# Encrypt/Decrypt Tests 

| HW Algo     | Configuration                 |  Rio2 |    
| ----------- | ----------------------------- | ----- |    
| MD5         | !NO\_MD5                      |   x   |    
| SHA         | !NO\_SHA                      |   x   |    
| SHA256      | !NO\_SHA256                   |   x   |   
| SHA224      | WOLFSSL\_SHA224               |       |    
| SHA384      | WOLFSSL\_SHA384               |   x   |    
| SHA512      | WOLFSSL\_SHA512               |   x   |
| HMAC/MD5    | !NO\_HMAC && !NO\_MD5         |   x   |
| HMAC/SHA    | !NO\_HMAC && !NO\_SHA         |   x   |
| HMAC/SHA256 | !NO\_HMAC && !NO\_SHA256      |   x   |
| HMAC/SHA384 | !NO\_HMAC && !WOLFSSL\_SH384  |   x   |
| HMAC/SHA512 | !NO\_HMAC && !WOLFSSL\_SH512  |   x   |
| RNG         | NO\_RNG\_TEST                 |   x   |
| ECC         | HAV\_ECC                      |   x   |
| AES         | !NO\_AES                      |   x   |
| AES/CBC     | !NO\_AES && !NO\_AEC\_CBC     |   x   |
| AES/GCM     | !NO\_AES && HAVE\_AESGCM      |   x   |
| AES/CTR     | !NO\_AES && WOLFSSL\_AES\_CTR |   x   |
| Compression | HAVE\_LIBZ                    |   x   |
| DES         | !NO\_DES3                     |   x   |
| DES3        | !NO\_DES3                     |   x   |
| RSA         | !NO\_RSA                      |   x   |
| Primatives  | WOLFSSL\_HAVE\_MCHP\_BA414E\_CRYPTO && ECC\_PRIM\_TEST |    |

