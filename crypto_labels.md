|
The following Boolean symbols are used to enable generation of Crypto V4 API selection:    

CONFIG\_USE\_HASH            
CONFIG\_USE\_SYM             
CONFIG\_USE\_ASYM              
CONFIG\_USE\_AEAD              
CONFIG\_USE\_KAS              
CONFIG\_USE\_DS                
CONFIG\_USE\_HMAC         
CONFIG\_USE\_RNG              

NOTE:  Currently, the api files are still generated even if they are false (the function has no specific selections)

These defines are generated to the Hardware configuration section of the crypto\_config.h if the device supports the given hardware driver.:

HAVE\_MCHP\_CRYPTO\_TRNG\_HW\_HSM     
HAVE\_MCHP\_CRYPTO\_TRNG\_HW\_6334    
HAVE\_MCHP\_CRYPTO\_TRNG\_HW\_U2242    
HAVE\_MCHP\_CRYPTO\_TRNG\_HW\_03597    
HAVE\_MCHP\_CRYPTO\_SHA\_HW\_11105    
HAVE\_MCHP\_CRYPTO\_SHA\_HW\_U2010    
HAVE\_MCHP\_CRYPTO\_SHA\_HW\_6156    
HAVE\_MCHP\_CRYPTO\_SHA\_HW\_U2803"    
HAVE\_MCHP\_CRYPTO\_SHA\_HW\_03710    
HAVE\_MCHP\_CRYPTO\_AES\_HW\_6149    
HAVE\_MCHP\_CRYPTO\_AES\_HW\_U2238    
HAVE\_MCHP\_CRYPTO\_TDES\_HW\_6150    
HAVE\_MCHP\_CRYPTO\_RSA\_HW\_PUKCC    
HAVE\_MCHP\_CRYPTO\_RSA\_HW\_CPKCC    
HAVE\_MCHP\_CRYPTO\_ECC\_HW\_BA414E    
HAVE\_MCHP\_CRYPTO\_HW\_BA414E    
HAVE\_MCHP\_CRYPTO\_HW\_U2805    
HAVE\_MCHP\_CRYPTO\_HW\_03710"        
    
NOTE: These would require symbols to be used by FreeMarker files.    
    
    
The following symbols are used to enable generation of Crypto V4 Hardware function selection:

CONFIG\_USE\_TRNG\_HW    
CONFIG\_USE\_SHA\_HW    
CONFIG\_USE\_AES\_HW    
CONFIG\_USE\_TDES\_HW    
CONFIG\_USE\_RSA\_HW    
CONFIG\_USE\_ECC\_HW    

These are only True when the crypto function is selected and the hardware implementation is available and selected.
NOTE:  Currently, I am not generating any driver files based on these boolean values.   
    

The following Boolean symbols indicate if the specific api function is selected(Enabled), ant the HW is supported and selected(Enabled):

crypto<Function>EnabledSymbol     -- As currently used in the configuration headers for each crypto function 
cryptoHw<Function>Supported        -- Added for each specific function with possible hardware support
cryptoHw<Function>EnabledSymbol  -- True for function selected with HW implementation and that is selected.

| HASH         | AES       | DES    | AEAD-AES       | MAC-AES      | KAS   | DS      | ECC    | RNG |
|--------------|-----------|--------|----------------|--------------|-------|---------|--------|------|
| Md5          | Aes       | Des    | AeadAes        | MacAes       |KasEcdh| DsEcdsa | Ecc    | RngTrng|
| RipeMd160    | Aes       | DesEcb | AeadAesGcm     | MacAesCmac   |
| Sha224       | AesEcb    | DesCbc | AeadAesCcm     | MacAesCbcMac |
| Sha256       | Aes128    | DesCfb | AeadAesEax     | MacAesGmac   |
| Sha384       | Aes192    | DesOfb | AeadAesSivCmac |              |
| Sha512       | Aes256    |        | AeadAesSivGcm  |              |
| Sha3224      | AesEcb    |        | AeadAesCcm     |              |
| Sha3256      | AesCbc    |        | AeadAesEax     |              |
| Sha3384      | AesOfb    |        | AeadAesSivCmac |              |
| Sha3512      | AesCfb    |        | AeadAesSivGcm  |              |
| Sha3Shake256 | AesCfb1   |        |                |              |
| Blake224     | AesCfb8   |        |                |              |
| Blake256     | AesCfb64  |        |                |              |
| Blake384     | AesCfb128 |        |                |              |
| Blake512     | AesCtr    |        |                |              |
| Blake2s224   | AesXts    |        |                |              |
| Blake2s256   | AesEax    |        |                |              |
| Blake2b384   | AesGcm    |        |                |              |
| Blake2b512   | AesCcm    |  iii   |                |              |

