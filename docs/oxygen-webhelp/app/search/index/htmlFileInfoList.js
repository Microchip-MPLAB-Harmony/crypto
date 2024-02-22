define(function () {
return ["GUID-03122BFE-52BC-4937-A998-34DA8A7F383F.html@@@3.7.1.1 st_Crypto_Hash_Ripemd160_Ctx@@@This structure is used to define context for Ripemd160 algorithms variants. Structure Elements Data Type Element Name Description uint32_t ripemd160SessionId It defines the session ID, must be more...","GUID-03CBC189-3BC8-451A-AA95-D6FCEFA3D7D1.html@@@4.3.2.3 Crypto_Mac_AesCmac_Final@@@crypto_Mac_Status_E Crypto_Mac_AesCmac_Final( st_Crypto_Mac_Aes_ctx *ptr_aesCmacCtx_st, uint8_t *ptr_outMac, uint32_t macLen ); This API performs AES-CMAC to get the MAC. Initialize context by calling...","GUID-07E17AB4-15B5-4452-A6FA-739D95C1195B.html@@@2.5.1.3 Crypto_Sym_Camellia_EncryptDirect@@@crypto_Sym_Status_E Crypto_Sym_Camellia_EncryptDirect( crypto_HandlerType_E handlerType_en, crypto_Sym_OpModes_E opMode_en, uint8_t *ptr_inputData, uint32_t dataLen, uint8_t *ptr_outData, uint8_t...","GUID-098F7EFE-E879-4E28-B4A8-F31880F135DF.html@@@2.1.2 crypto_Sym_OpModes_E@@@This enum used as an argument in Block Symmetric algorithm APIs for operation modes. i.e., ECB, CBC, or others. Enumeration Data Types Numerical Value Description CRYPTO_SYM_OPMODE_INVALID 0...","GUID-0C440F72-FABA-41DA-84D3-C5177429223E.html@@@7.1 KAS Algorithms Enumerations@@@...","GUID-0CB49CCD-5C54-4C11-BEAA-7F021B4D75A7.html@@@5.4.2.3 Crypto_Aead_AesEax_Final@@@crypto_Aead_Status_E Crypto_Aead_AesEax_Final( st_crypto_Aead_AesEax_Ctx * ptr_aesEaxCtx_st, uint8_t *ptr_authTag, uint32_t authTagLen ); This API performs AES-EAX to get the authentication tag...","GUID-0D01CA7A-EE8E-487C-9FED-4DDE8C9E6C14.html@@@3.1 Hash Algorithms Enumerations@@@...","GUID-0EE98187-E103-4D9F-81A8-33DF696FDBE0.html@@@8.2 Imported External Enumerations and Structures@@@...","GUID-114F1E79-4860-4D1A-A87A-59C92665D9DC.html@@@2.7.1.2 Crypto_Sym_ChaCha20_Cipher@@@crypto_Sym_Status_E Crypto_Sym_ChaCha20_Cipher( st_Crypto_Sym_StreamCtx *ptr_chaChaCtx_st, uint8_t *ptr_inputData, uint32_t dataLen, uint8_t *ptr_outData ); This API performs ChaCha20 encryption or...","GUID-12BEC0D1-F4C2-433D-BEAA-5D09C4413009.html@@@3.3.1 SHA-1, SHA-2, and SHA-3 Structures@@@...","GUID-144C081B-CA0F-4340-856F-53842DAC0ECF.html@@@2.7 ChaCha20 Algorithm@@@ChaCha20 is stream Cipher. It is a refinement of the Salsa20 algorithm. ChaCha20 is ARX (Addition/Rotation/XOR) based hash function, keyed, running in counter mode. It embodies the idea that hash...","GUID-1629B769-42DB-45E4-AC46-EF299F2657AB.html@@@7 Key Agreement Scheme (KAS) Algorithms@@@Key Agreement algorithms are used to generate a shared secret. Two parties exchange data to generate a shared secret. The shared secret is used to derive a symmetric key, or directly used as a key...","GUID-1723711A-0BC9-4497-9E0A-4932ED6647C1.html@@@2.7.1.3 Crypto_Sym_ChaCha20Direct@@@crypto_Sym_Status_E Crypto_Sym_ChaCha20Direct( crypto_HandlerType_E handlerType_en, uint8_t *ptr_inputData, uint32_t dataLen, uint8_t *ptr_outData, uint8_t *ptr_key, uint8_t *ptr_initVect, uint32_t...","GUID-189EFBA1-C1A7-447C-90DE-C441CD6FB8DB.html@@@3.5.2.3 Crypto_Hash_Blake_Update@@@crypto_Hash_Status_E Crypto_Hash_Blake_Update ( st_Crypto_Hash_Blake_Ctx * ptr_blakeCtx_st, uint8_t *ptr_data, uint32_t dataLen ); This API performs hash calculation for different variants BLAKE...","GUID-195AD0A9-256B-42BA-9768-B6654594AF40.html@@@1 Summary@@@This document provides information about the Common Crypto API. It contains information about the functionality of each API call, as well as information about each parameter. Each function is...","GUID-1A33A361-430F-49EF-9350-A25050A88F10.html@@@8.3.1 crypto_Rng_Prng_Generate@@@crypto_Rng_Status_E Crypto_Rng_Prng_Generate( crypto_HandlerType_E rngHandlerType_en, uint8_t *ptr_rngData, uint32_t rngLen, uint8_t *ptr_nonce, uint32_t nonceLen, uint32_t sessionID); This API is...","GUID-1B19E672-DFF0-4B0F-A245-6D1A540D915D.html@@@6 Digital Signature Algorithms@@@Digital Signature algorithms include signature generation and a signature verification process. An entity that intends to generate digital signature referred to as Signatory and an entity that intends...","GUID-1C5C2A77-F569-41F0-A885-83F328420181.html@@@3.6.1 MD5 Structures@@@...","GUID-1CFCA9A4-09D9-4A6A-95BA-818885F338F7.html@@@3.4.2.2 Crypto_Hash_Shake_Init@@@crypto_Hash_Status_E Crypto_Hash_Shake_Init( st_Crypto_Hash_Shake_Ctx ptr_shakeCtx_st, crypto_Hash_Algo_E shakeAlgorithm_en, uint32_t digestlen, crypto_HandlerType_E shakeHandlerType_en, uint32_t...","GUID-1E9C1BC1-A0F2-45CC-9C35-243CCE7D5333.html@@@3.6.2.1 Crypto_Hash_Md5_Digest@@@crypto_Hash_Status_E Crypto_Hash_Md5_Digest( crypto_HandlerType_E md5Handler_en, uint8_t *ptr_data, uint32_t dataLen, uint8_t *ptr_digest, uint32_t md5SessionId ); This API performs hash generation...","GUID-20692A11-5B76-48A4-9EFA-9BC57E86A22C.html@@@5.4.2.5 Crypto_Aead_AesEax_EncryptAuthDirect@@@crypto_Aead_Status_E Crypto_Aead_AesEax_EncryptAuthDirect( crypto_HandlerType_E handlerType_en, uint8_t *ptr_inputData, uint32_t dataLen, uint8_t *ptr_outData, uint8_t *ptr_key, uint32_t keyLen...","GUID-24DF3641-ABE6-45E8-A9EA-7CBF61B9C0A2.html@@@3.4.2 SHA-1, SHA-2, and SHA-3 (excluding SHAKE) APIs@@@...","GUID-2616DD89-CA26-4C47-9341-D4714BF99E53.html@@@3.3.2 SHA-1, SHA-2, and SHA-3 (excluding SHAKE) APIs@@@...","GUID-26BE22A2-AA07-43D0-934F-F9ABF295DD8F.html@@@5.3.1 AES-CCM Structures@@@...","GUID-28F849E7-9B37-45CD-B16D-0616C72D801A.html@@@3.1.2 crypto_Hash_Status_E@@@This Enum is used to represent the return type of Hash algorithm APIs Enumeration Data Types Numerical Value Description CRYPTO_HASH_ERROR_NOTSUPPTED -127 Error when cipher algorithm not supported by...","GUID-29BD950B-2AFE-48FC-9EDC-CCE605DB3090.html@@@2.4 AES Algorithm@@@The Advanced Encryption Standard (AES) specifies a FIPS-approved cryptographic algorithm in 2001 by NIST. AES is also known as Rijndael. Rijndael block cipher developed by two cryptographers, Joan...","GUID-2BFBB333-EEC2-43E3-8376-AD40F53B0970.html@@@2.7.1 ChaCha20 Algorithm APIs@@@...","GUID-32EC4010-18ED-4708-8C28-5CF20F9C0520.html@@@2.2.1 crypto_HandlerType_E@@@This enum defines the handler type. Handler type defines which component will do the cipher operation. It can be internal or external hardware crypto engine or any crypto software library. Enumeration...","GUID-34BC13C4-9532-497E-8C49-2475D1223849.html@@@3.3.2.3 Crypto_Hash_Sha_Update@@@crypto_Hash_Status_E Crypto_Hash_Sha_Update( st_Crypto_Sha_Hash_Ctx *ptr_shaCtx_st, uint8_t *ptr_data, uint32_t dataLen ); This API performs hash calculation for different variants of SHA-1, SHA-2...","GUID-354263BC-FFDC-4D01-8E59-8E55F9B0D647.html@@@4.3.1.1 st_Crypto_Mac_Aes_ctx@@@This structure is used to define context for AES-CMAC algorithms. Structure Elements Data Type Element Name Description uint32_t cryptoSessionID It defines the session ID, must be more than zero...","GUID-3755A601-C8FC-4C78-B6C7-B8CCE5F758C0.html@@@2.4.1.4 Crypto_Sym_Aes_EncryptDirect@@@crypto_Sym_Status_E Crypto_Sym_Aes_EncryptDirect( crypto_HandlerType_E handlerType_en, crypto_Sym_OpModes_E opMode_en, uint8_t *ptr_inputData, uint32_t dataLen, uint8_t *ptr_outData, uint8_t *ptr_key...","GUID-3887162A-F034-4291-94A4-0E139B2E3B8A.html@@@5.4.1.1 st_Crypto_Aead_AesEax_ctx@@@This structure is used to define context for AES-EAX algorithms. Structure Elements Data Type Element Name Description uint32_t cryptoSessionID It defines the session ID, must be more than zero...","GUID-3898AFFC-D3C7-48D4-B0FB-3D1C2D9B77D2.html@@@3.2 Imported External Enumerations and Structures@@@...","GUID-3BD54F59-D3E7-4C6B-9CE9-9A2163FD22CC.html@@@7.2.1 crypto_HandlerType_E@@@This enum defines the handler type. Handler type defines which component will do the cipher operation. It can be internal or external hardware crypto engine or any crypto software Library. Enumeration...","GUID-3C2C40F9-7D68-4B9C-BE07-12F5275637FA.html@@@2.8.1.2 Crypto_Sym_AesKeyWrap_Cipher@@@crypto_Sym_Status_E Crypto_Sym_AesKeyWrap_Cipher( st_Crypto_Sym_BlockCtx *ptr_aesCtx_st, uint8_t *ptr_inputData, uint32_t dataLen, uint8_t *ptr_outData ); This API is used to wrap or unwrap the data...","GUID-3C68EE80-5E9D-4926-8099-902C28BB3301.html@@@6.1.1 crypto_DigiSign_Status_E@@@This enum is used to represent the return type of Digital Signature algorithm APIs. Enumeration Data Types Numerical Value Description CRYPTO_DIGISIGN_ERROR_ALGONOTSUPPTD -127 Error when a Digital...","GUID-3E43B56B-0965-48A5-9C73-7FA2A2B42843.html@@@5.2.2 crypto_AesKeySize_E@@@This enum defines the different key sizes for the AES algorithm Enumeration Data Types Numerical Value Description CRYPTO_AESKEYSIZE_128 16 Enum used for AES key size of 128 bits CRYPTO_AESKEYSIZE_192...","GUID-3ECCB5DE-8083-405E-B9A6-B54884825BD1.html@@@2.6 TDES Algorithm@@@Triple Data Encryption Algorithm (TDES) is a symmetric key block cipher proposed in 1981, which applies the DES cipher algorithm three times to each data block. DES key size is 56 bit and 8 bits of...","GUID-3F7F15B2-07CE-423E-878E-D07EB27F5524.html@@@6.3.1 Crypto_DigiSign_Ecdsa_Sign@@@crypto_DigiSign_Status_E Crypto_DigiSign_Ecdsa_Sign( crypto_HandlerType_E ecdsaHandlerType_en, uint8_t *ptr_inputHash, uint32_t hashLen, uint8_t *ptr_outSig, uint32_t sigLen, uint8_t *ptr_privKey...","GUID-3FABC3BD-634A-42E2-BA31-DCCDD3A5C2BB.html@@@2.5.1.1 Crypto_Sym_Camellia_Init@@@crypto_Sym_Status_E Crypto_Sym_Camellia_Init( st_Crypto_Sym_BlockCtx *ptr_camCtx_st, crypto_HandlerType_E handlerType_en, crypto_CipherOper_E cipherOpType_en, crypto_Sym_OpModes_E opMode_en, uint8_t...","GUID-40799C9B-9B08-45CB-A6E5-ADC234298109.html@@@2.2.3 crypto_CipherOper_E@@@This enum defines crypto operation. This enum defines that APIs will do encryption operation or decryption operation. Enumeration Data Types Numerical Value Description CRYPTO_CIOP_INVALID 0 Invalid...","GUID-410448E9-840F-4EB5-A918-CA4718D707E3.html@@@3.1.1 crypto_Hash_Algo_E@@@Enums are used as argument to use different hash algorithms APIs. Enumeration Data Types Numerical Value Description CRYPTO_HASH_INVALID 0 Min range for the Hash algorithm macro CRYPTO_HASH_SHA1 1...","GUID-41591FA2-8217-4765-8F94-71CEA74FE4D5.html@@@3.6.2.3 Crypto_Hash_Md5_Update@@@crypto_HandlerType_E Crypto_Hash_Md5_Update( st_Crypto_Hash_Md5_Ctx * ptr_md5Ctx_st, uint8_t *ptr_data, uint32_t dataLen ); This API performs Hash calculation for MD5 algorithm in multi-steps...","GUID-41B81207-6DB1-4740-B8B3-D1F9E5DD11BE.html@@@3.4 SHAKE Algorithm@@@Secure Hash Algorithm with KECCAK referred to as &quot;SHAKE&quot;. SHA-3 has two extendable-output functions (XOFs) SHAKE-128 and SHAKE-256. Here 128 and 256 suffix indicate the security strength supported by...","GUID-42061E3C-9189-4D8E-9AF1-08A4F6BFA2D0.html@@@3.6.2.2 Crypto_Hash_Md5_Init@@@crypto_Hash_Status_E Crypto_Hash_Md5_Init( st_Crypto_Hash_Md5_Ctx *ptr_md5Ctx_st, crypto_HandlerType_E md5HandlerType_en, uint32_t md5SessionId ); This API is used to initiate context for MD5...","GUID-43B8B5C3-279D-4265-877A-D49A807B82A2.html@@@4.2.2 crypto_AesKeySize_E@@@This enum defines the handler type. Handler type defines which component will do the cipher operation. It can be internal or external hardware crypto engine or any crypto software library. Enumeration...","GUID-49DC73E9-0FEB-495B-93D9-DBD9408B81A0.html@@@2.2.2 crypto_AesKeySize_E@@@This enum defines the different key sizes for the AES algorithm Enumeration Data Types Numerical Value Description CRYPTO_AESKEYSIZE_128 16 Enum used for AES key size of 128 bits CRYPTO_AESKEYSIZE_192...","GUID-4BE907F2-6EFF-4783-8345-B057325D9845.html@@@2.4.1.1 Crypto_Sym_Aes_Init@@@crypto_Sym_Status_E Crypto_Sym_Aes_Init( st_Crypto_Sym_BlockCtx *ptr_aesCtx_st, crypto_HandlerType_E handlerType_en, crypto_CipherOper_E cipherOpType_en, crypto_Sym_OpModes_E opMode_en, uint8_t...","GUID-4CD622E7-8D08-438F-AAFD-4E7F451CEFDE.html@@@2.6.1 TDES/3DES Algorithm APIs@@@...","GUID-4D5264B7-A707-43D5-8C90-CE0AC903F1DA.html@@@5 AEAD Algorithms@@@Authenticated encryption (AE) schemes are symmetric-key mechanisms by which a message M is transformed into a ciphertext C in such a way that C protects both privacy and authenticity. AE schemes and...","GUID-4E45892C-0A91-48DC-8179-A10FABE025DB.html@@@2.8.1.1 Crypto_Sym_AesKeyWrap_Init@@@crypto_Sym_Status_E Crypto_Sym_AesKeyWrap_Init( st_Crypto_Sym_BlockCtx *ptr_aesCtx_st, crypto_HandlerType_E handlerType_en, crypto_CipherOper_E cipherOpType_en, uint8_t *ptr_key, uint32_t keyLen...","GUID-4FA66A29-6E7C-4536-8AB0-EDF3B50811E9.html@@@5.3.2.2 Crypto_Aead_AesCcm_Cipher@@@crypto_Aead_Status_E Crypto_Aead_AesCcm_Cipher( st_Crypto_Aead_AesCcm_ctx *ptr_aesCcmCtx_st, crypto_CipherOper_E cipherOper_en, uint8_t *ptr_inputData, uint32_t dataLen, uint8_t *ptr_outData, uint8_t...","GUID-4FFF23D7-D26C-4648-A903-2485776F41A3.html@@@2.8 Key-Wrap Algorithm@@@Key wrap constructions are a class of symmetric encryption algorithms designed to encapsulate (encrypt) cryptographic key material. The AES key wrap algorithm is designed to wrap or encrypt key data...","GUID-5258A9CB-4DE3-44D3-BA18-0231217C3072.html@@@2.4.1.2 Crypto_Sym_Aes_Cipher@@@crypto_Sym_Status_E Crypto_Sym_Aes_Cipher( st_Crypto_Sym_BlockCtx *ptr_aesCtx_st, uint8_t *ptr_inputData, uint32_t dataLen, uint8_t *ptr_outDa ); This API performs AES encryption or decryption for...","GUID-5A15BF55-D661-49FC-97B3-BB2D8F8CA5AE.html@@@3.6.2.4 Crypto_Hash_Md5_Final@@@crypto_HandlerType_E Crypto_Hash_Md5_Final( st_Crypto_Hash_Md5_Ctx * ptr_md5Ctx_st, uint8_t *ptr_digest ); This API is used to get the calculated hash/digest for MD5 algorithm in multi-steps...","GUID-6269AFA7-D391-486A-83FF-B6256FDE461E.html@@@3.5.2 BLAKE Algorithm APIs@@@...","GUID-63148F7D-B7B6-4FFA-9A58-E2BB5770C989.html@@@7.2.2 crypto_EccCurveType_E@@@This Enum defines the different Curve Types for the ECC Curve based algorithm. Enumeration Data Types Numerical Value Description CRYPTO_ECC_CURVE_INVALID -1 Enum used invalid curve...","GUID-63AB7984-BF03-4648-8FD3-C32A12DA43BD.html@@@3.5.2.4 Crypto_Hash_Blake_Final@@@crypto_HandlerType_E Crypto_Hash_Blake_Final( st_Crypto_Hash_Blake_Ctx * ptr_blakeCtx_st, uint8_t *ptr_digest ); This API is used to get the calculated hash/digest for different variants BLAKE...","GUID-660CA4C7-7A46-4579-B5E5-DB376EF3B5DA.html@@@2.5.1.2 Crypto_Sym_Camellia_Cipher@@@crypto_Sym_Status_E Crypto_Sym_Camellia_Cipher( st_Crypto_Sym_BlockCtx *ptr_camCtx_st, uint8_t *ptr_inputData, uint32_t dataLen, uint8_t *ptr_outData ); This API performs Camellia encryption or...","GUID-675F0957-0E8B-480B-9B4C-DDF7380F55E0.html@@@2.5.1 Camellia Algorithm APIs@@@...","GUID-67D4D6ED-0ECD-4B15-99AD-2DC3714C7018.html@@@5.3.1.1 st_Crypto_Aead_AesCcm_ctx@@@This structure is used to define context for AES-CCM algorithms. Structure Elements Data Type Element Name Description uint32_t cryptoSessionID It defines the session ID, must be more than zero...","GUID-69858BF8-B03B-4FA5-B112-874933AF9BE9.html@@@4.1 MAC Algorithms Enumerations@@@...","GUID-6B1A5494-499D-4903-8CD2-54369694892E.html@@@5.3 AES-CCM Algorithm@@@CCM mode was designed by Russ Housley, Doug Whiting, and Niels Ferguson. CCM mode uses AES-CTR mode for confidentiality and CBC-MAC for authentication. MAC is first computed and then message, and MAC...","GUID-6BBF6DF0-98DA-4E0B-B1EE-D5264AC2BEC9.html@@@2.1 Symmetric Algorithms Enumerations@@@...","GUID-6FE14C5C-78D9-493B-BDCB-ED001A8DC34E.html@@@5.4.2.1 Crypto_Aead_AesEax_Init@@@crypto_Aead_Status_E Crypto_Aead_AesEax_Init( st_Crypto_Aead_AesEax_ctx *ptr_aesEaxCtx_st, crypto_HandlerType_E handlerType_en, crypto_CipherOper_E cipherOper_en, uint8_t *ptr_key, uint32_t keyLen...","GUID-724DFDA5-6394-46A4-B0B5-D2446D54C58C.html@@@4 MAC Algorithms@@@MAC algorithms are used to check the authenticating and integrity of a message. MAC, also known as Authentication Tag, is used to authenticate a message. MAC helps to identify any change to message...","GUID-75FE88D6-E954-41D3-9517-2BD0AF3D618A.html@@@2.7.1.1 Crypto_Sym_ChaCha20_Init@@@crypto_Sym_Status_E Crypto_Sym_ChaCha20_Init( st_Crypto_Sym_StreamCtx *ptr_chaChaCtx_st, crypto_HandlerType_E handlerType_en, uint8_t *ptr_key, uint8_t *ptr_initVect, uint32_t sessionID ); This API is...","GUID-7732487B-1C4D-4B03-8085-52079A0DEDA4.html@@@3.5.1.1 st_Crypto_Hash_Blake_Ctx@@@This structure is used to define context for BLAKE algorithms variants. Structure Elements Data Type Element Name Description uint32_t blakeSessionId It defines the session ID, must be more than zero...","GUID-774567E5-2FB6-4BA7-9560-E077EE688E45.html@@@2.4.1.3 Crypto_Sym_AesXts_Cipher@@@crypto_Sym_Status_E Crypto_Sym_AesXts_Cipher( st_Crypto_Sym_BlockCtx *ptr_aesCtx_st, uint8_t *ptr_inputData, uint32_t dataLen, uint8_t *ptr_outData, uint8_t *ptr_tweak ); This API performs AES...","GUID-79CFFDFD-CB9E-49B1-A937-6B0770EE6AD7.html@@@2.6.1.4 Crypto_Sym_Tdes_DecryptDirect@@@crypto_Sym_Status_E Crypto_Sym_Tdes_DecryptDirect( crypto_HandlerType_E handlerType_en, crypto_Sym_OpModes_E opMode_en, uint8_t *ptr_inputData, uint32_t dataLen, uint8_t *ptr_outData, uint8_t...","GUID-7A8CDF22-CEC0-4DF8-8BA0-97BF1F0676E2.html@@@2.6.1.2 Crypto_Sym_Tdes_Cipher@@@crypto_Sym_Status_E Crypto_Sym_Tdes_Cipher( st_Crypto_Sym_BlockCtx *ptr_tdesCtx_st, uint8_t *ptr_inputData, uint32_t dataLen, uint8_t *ptr_outData ); This API performs TDES/3DES encryption or...","GUID-7C48CA1C-F2C5-4D64-AF0C-22E728DB96CA.html@@@2.3.2 st_Crypto_Sym_StreamCtx@@@This structure is used to define Context for Stream Symmetric Algorithms. Structure Elements Data Type Element Name Description uint32_t cryptoSessionID It defines the session ID, must be more than...","GUID-810E3077-6D57-43BB-A0CC-6D70A5EF3BE6.html@@@3.6.2 MD5 Algorithm APIs@@@...","GUID-82435FF2-C856-4B00-A008-E2736952534C.html@@@5.1 AEAD Algorithms Enumerations@@@...","GUID-82FE83ED-1EE8-4B5C-909A-4E8A86EE18AF.html@@@2.5 Camellia Algorithm@@@Camellia was developed jointly by NTT and Mitsubishi Electric Corporation in the year 2000. Camellia is a symmetric cipher with a Feistel structure. The cipher was named for the flower Camellia...","GUID-8378E107-8264-40B6-84B2-261F5DF5EB80.html@@@3.7.1 RIPEMD-160 Structures@@@...","GUID-854883B3-AC40-49F3-983A-DB74A983106A.html@@@5.3.2 AES-CCM Algorithm APIs@@@...","GUID-8614BA41-DFDD-457D-9701-FF251CFE804F.html@@@5.1.1 crypto_AEAD_Status_E@@@This enum is used to represent the return type of AEAD algorithm APIs. Enumeration Data Types Numerical Value Description CRYPTO_AEAD_ERROR_CIPNOTSUPPTD -127 Error when AEAD algorithm not supported by...","GUID-864148C6-7F09-4ED5-87B1-82870E604C60.html@@@4.1.1 crypto_Hash_Status_E@@@Enumeration Data Types Numerical Value Description CRYPTO_HASH_ERROR_NOTSUPPTED -127 Error when cipher algorithm not supported by Crypto software component CRYPTO_HASH_ERROR_CTX -126 Error when...","GUID-87ABDAFB-D438-4790-8D44-B27D71ABD262.html@@@8.3 PRNG Algorithm@@@The Pseudorandom number generator is sometimes called Deterministic random bit generator (DRBG) or deterministic random number generator. It is used for generating a sequence of numbers whose...","GUID-891C407A-A1A7-4E9E-803A-1CC3EBC9EEAB.html@@@7.3.1 Crypto_Kas_Ecdh_SharedSecret@@@crypto_Kas_Status_E Crypto_Kas_Ecdh_SharedSecret( crypto_HandlerType_E ecdhHandlerType_en, uint8_t *ptr_privKey, uint32_t privKeyLen, uint8_t *ptr_pubKey, uint32_t pubKeyLen, uint8_t...","GUID-8CBCD06A-0108-48FD-8E60-42DDB2DFEE1B.html@@@8 Random Number Generator (RNG) Algorithms@@@Random bit generators (RBGs) (also called random number generators (RNGs)) are required for the generation of keying material (e.g., keys and IVs). RBGs generate sequences of random bits (e.g...","GUID-8E1477DC-185B-49E9-AD7F-D78F5694E322.html@@@5.4.2.4 Crypto_Aead_AesEax_AddAadData@@@crypto_Aead_Status_E Crypto_Aead_AesEax_AddAadData( st_Crypto_Aead_AesEax_ctx *ptr_aesEaxCtx_st, uint8_t *ptr_aad, uint32_t aadLen ); This API performs AES-EAX to add additional authentication data to...","GUID-8ECFDCC1-6472-4A85-8808-9B8F423801D0.html@@@3.7.2.1 Crypto_Hash_Ripemd160_Digest@@@crypto_Hash_Status_E Crypto_Hash_Ripemd160_Digest( crypto_HandlerType_E ripedmd160Handler_en, uint8_t *ptr_data, uint32_t dataLen, uint8_t *ptr_digest, uint32_t ripemdSessionId ); This API performs...","GUID-904C11F5-E035-47A6-AD71-82EF3213325B.html@@@2.8.1.4 Crypto_Sym_AesKeyUnWrapDirect@@@crypto_Sym_Status_E Crypto_Sym_AesKeyUnWrapDirect( crypto_HandlerType_E handlerType_en, uint8_t *ptr_inputData, uint32_t inputLen, uint8_t *ptr_outData, uint8_t *ptr_key, uint32_t keyLen, uint8_t...","GUID-928649F2-433B-4290-BAE7-EDF717394181.html@@@4.3.2.4 Crypto_Mac_AesCmac_Direct@@@crypto_Mac_Status_E Crypto_Mac_AesCmac_Direct( crypto_HandlerType_E macHandlerType_en, uint8_t *ptr_inputData, uint32_t dataLen, uint8_t * ptr_outMac, uint32_t macLen, uint8_t *ptr_key, uint8_t...","GUID-95508D60-924D-440B-BC70-AE521A27FCDD.html@@@5.3.2.1 Crypto_Aead_AesCcm_Init@@@crypto_Aead_Status_E Crypto_Aead_AesCcm_Init( st_Crypto_Aead_AesCcm_ctx *ptr_aesCcmCtx_st, crypto_HandlerType_E handlerType_en, uint8_t *ptr_key, uint32_t keyLen, uint32_t sessionID ); This API is...","GUID-95CB023A-C6FF-4BEB-B958-B875E290F9E5.html@@@4.3.2 AES-CMAC Algorithm APIs@@@...","GUID-963461D2-C4C9-45BD-A5EB-F92657220B2C.html@@@3.3.2.4 Crypto_Hash_Sha_Final@@@crypto_HandlerType_E Crypto_Hash_Sha_Final( st_Crypto_Sha_Hash_Ctx *ptr_shaCtx_st, uint8_t *ptr_digest ); This API is used to get the calculated hash/digest for different variants of SHA-1, SHA-2, and...","GUID-97FD7EA4-2677-4B31-8C74-A365DFAF05E6.html@@@6.2 Imported External Enumerations and Structures@@@...","GUID-982285DA-2B79-46CE-9578-0AB016C8E3DA.html@@@4.3.2.1 Crypto_Mac_AesCmac_Init@@@crypto_Mac_Status_E Crypto_Mac_AesCmac_Init( st_Crypto_Mac_Aes_ctx *ptr_aesCcmCtx_st, crypto_HandlerType_E handlerType_en, uint8_t *ptr_key, uint32_t keyLen, uint32_t sessionID ); This API is used to...","GUID-9AFE1DCD-C661-4067-B9E7-B02BA8CC334D.html@@@3 Hash Algorithms@@@Hash Function (Algorithm) used to map data of arbitrary size into the fixed-sized integer values. This fixed-sized value is called Hash or Digest. There are few hashes functions that support variable...","GUID-9C65399F-B9EF-4E2D-952A-10D99CBBBF0D.html@@@2.6.1.3 Crypto_Sym_Tdes_EncryptDirect@@@crypto_Sym_Status_E Crypto_Sym_Tdes_EncryptDirect( crypto_HandlerType_E handlerType_en, crypto_Sym_OpModes_E opMode_en, uint8_t *ptr_inputData, uint32_t dataLen, uint8_t *ptr_outData, uint8_t...","GUID-A1846A5F-0DF3-4C4E-A824-EA78E269E9B1.html@@@3.3.2.2 Crypto_Hash_ShaInit@@@crypto_Hash_Status_E Crypto_Hash_Sha_Init( st_Crypto_Sha_Hash_Ctx *ptr_shaCtx_st, crypto_Hash_Algo_E shaAlgorithm_en, crypto_HandlerType_E shaHandler_en, uint32_t shaSessionId ); This API is used to...","GUID-A1AAB65D-FE23-4012-8EAF-32FAA9A217F7.html@@@3.2.1 crypto_HandlerType_E@@@This enum defines the handler type. Handler type defines which component will do the cipher operation. It can be internal or external hardware crypto engine or any crypto software library. Enumeration...","GUID-A818456A-991A-470C-A5A7-65F48992FC16.html@@@3.3 SHA Algorithm@@@The Secure Hash Algorithm known as SHA, Designed by United States National Security Agency (NSA) and is a U.S. Federal Information Processing Standard (FIPS). SHA-3 family of standards released by...","GUID-AEB00F08-6321-4AD7-B55E-8CCD76FA0B64.html@@@3.5.2.2 Crypto_Hash_Blake_Init@@@crypto_Hash_Status_E Crypto_Hash_Blake_Init( st_Crypto_Hash_Blake_Ctx *ptr_blakeCtx_st, crypto_Hash_Algo_E blakeAlgorithm_en, uint8_t *ptr_blakeKey, uint32_t keySize, uint32_t digestSize...","GUID-AEF94FAF-E3D9-47DC-BDBA-37E7F1C4ADA4.html@@@2.3.1 st_Crypto_Sym_BlockCtx@@@This structure is used to define context for Block Symmetric algorithms. Structure Elements Data Type Element Name Description uint32_t cryptoSessionID It defines the session ID, must be more than...","GUID-B173F793-6608-4A65-A2FE-620196289ED6.html@@@6.1 Digital Signature Algorithms@@@Digital Signature algorithms include signature generation and a signature verification process. An entity that intends to generate digital signature referred to as Signatory and an entity that intends...","GUID-B4E4A2F7-6409-4D83-99D1-021618B5638D.html@@@5.2 Imported External Enumerations and Structures@@@...","GUID-B58BC987-B7A0-4504-84B9-4643D02056C1.html@@@5.4.2 AES-EAX Algorithm APIs@@@...","GUID-B8A43CD8-238A-404F-8729-28936CC712B7.html@@@3.7.2.3 Crypto_Hash_Ripemd160_Update@@@crypto_HandlerType_E Crypto_Hash_Ripemd160_Update( st_Crypto_Hash_Ripemd160_Ctx *ptr_ripemdCtx_st, uint8_t *ptr_data, uint32_t dataLen ); This API performs hash calculation for RIPEMD-160 algorithm in...","GUID-BBB29DC6-0BBC-4AC7-B55A-FA609CB60CC0.html@@@6.2.1 crypto_HandlerType_E@@@This enum defines the handler type. Handler type defines which component will do the cipher operation. It can be internal or external hardware crypto engine or any crypto software Library. Enumeration...","GUID-BCE56ED5-C15F-45F5-8054-816609BDFCF8.html@@@2.6.1.1 Crypto_Sym_Tdes_Init@@@crypto_Sym_Status_E Crypto_Sym_Tdes_Init( st_Crypto_Sym_BlockCtx *ptr_tdesCtx_st, crypto_HandlerType_E handlerType_en, crypto_CipherOper_E cipherOpType_en, crypto_Sym_OpModes_E opMode_en, uint8_t...","GUID-BEC2FAC9-6C65-457C-AD5F-502A98E6FBF0.html@@@3.3.1.1 st_Crypto_Hash_Sha_Ctx@@@This structure is used to define context for SHA Algorithms including SHA-1, SHA-2 and SHA-3 excluding SHAKE. Structure Elements Data Type Element Name Description uint32_t shaSessionId It defines the...","GUID-C546E426-3570-4236-8FCE-C44E186DAAB5.html@@@4.2.1 crypto_HandlerType_E@@@This enum defines the handler type. Handler type defines which component will do the cipher operation. It can be internal or external hardware crypto engine or any crypto software library. Enumeration...","GUID-C7EC3361-737C-468F-B818-2F02947B11D3.html@@@8.1 KAS Algorithms Enumerations@@@...","GUID-C86D2835-B6A9-48F1-B0BE-822B42F93A34.html@@@3.3.2.1 Crypto_Hash_Sha_Digest@@@crypto_Hash_Status_E Crypto_Hash_Sha_Digest ( crypto_HandlerType_E shaHandler_en, uint8_t *ptr_data, uint32_t dataLen, uint8_t *ptr_digest, crypto_Hash_Algo_E shaAlgorithm_en, uint32_t shaSessionId )...","GUID-C98CF869-C5CF-4BE7-BC2F-391CBCA5E988.html@@@3.4.2.4 Crypto_Hash_ShakeFinal@@@crypto_Hash_Status_E Crypto_Hash_ShakeFinal( st_Crypto_Hash_Shake_Ctx* ptr_shakeCtx_st, uint8_t *ptr_digest ); This API is used to get the calculated hash/digest for different variants SHAKE...","GUID-C99BD434-6B60-4BFF-ACA8-8497D7031B05.html@@@3.7 RIPEMD-160 Algorithm@@@RIPEMD-160 (RIPE Message Digest) is a variant of RIPEMD hash function family. It has evolved from 256-bit extension of MD4. RIPEMD-160 is part of the ISO/IEC international standard ISO/IEC...","GUID-CCDD139A-A9E8-40AE-AD11-09E3E43A44D1.html@@@5.4.2.6 Crypto_Aead_AesEax_DecryptAuthDirect@@@crypto_Aead_Status_E Crypto_Aead_AesEax_DecryptAuthDirect( crypto_HandlerType_E handlerType_en, uint8_t *ptr_inputData, uint32_t dataLen, uint8_t *ptr_outData, uint8_t *ptr_key, uint32_t keyLen...","GUID-CD2D0202-8AC0-46B6-8515-9BF963E3D878.html@@@4.3.2.2 Crypto_Mac_AesCmac_Cipher@@@crypto_Mac_Status_E Crypto_Mac_AesCmac_Cipher( st_Crypto_Mac_Aes_ctx *ptr_aesCmacCtx_st, uint8_t *ptr_inputData, uint32_t dataLen ); This API performs AES-CMAC operation, which calculates the MAC...","GUID-CD5A2F77-082C-4FC9-B719-28241E080240.html@@@3.4.1 SHAKE Structures@@@...","GUID-CD67D2F3-AE0B-429C-AE81-B9B6F4470AFD.html@@@5.2.3 crypto_CipherOper_E@@@This enum defines crypto operation. This enum defines that APIs will do encryption operation or decryption operation. Enumeration Data Types Numerical Value Description CRYPTO_CIOP_INVAILD 0 Invalid...","GUID-CF9C7832-DF4A-4F53-95E8-5108EDA4EF53.html@@@8.1.1 crypto_Rng_Status_E@@@This enum is used to represent the return type of Random Number algorithm APIs. Enumeration Data Types Numerical Value Description CRYPTO_RNG_ERROR_ALGONOTSUPPTD -127 Error when a Random number...","GUID-D4C52344-9F63-4FE8-B033-BF2C0A44F348.html@@@2 Symmetric Algorithms@@@Symmetric key algorithms use the same key for encryption of plain text and decryption of cipher text. Symmetric key algorithm can be either Stream cipher or Block Cipher. Stream cipher encrypts the...","GUID-D4E9F605-BF1F-4A1B-925B-0FAA3927AF7D.html@@@4.3 AES-CMAC Algorithm@@@AES-CMAC is the variation of CBC-MAC proposed by Black and Rogaway. This algorithm uses AES symmetric keys to generate a MAC for a message. It uses CBC mode of block cipher to generate MAC for a...","GUID-D6F097B1-3B61-4B41-9274-B5B3E7FA0EE4.html@@@3.5.1 BLAKE Structures@@@...","GUID-D7EB4D30-9AEF-43CF-BB53-B3295543FC2B.html@@@6.3.2 Crypto_DigiSign_Ecdsa_Verify@@@crypto_DigiSign_Status_E Crypto_DigiSign_Ecdsa_Verify( crypto_HandlerType_E ecdsaHandlerType_en, uint8_t *ptr_inputHash, uint32_t hashLen, uint8_t *ptr_inputSig, uint32_t sigLen, uint8_t *ptr_pubKey...","GUID-D82A919F-1701-46F4-B5D9-CC3273441F01.html@@@2.1.1 crypto_Sym_Status_E@@@This enum is used to represent the return type of Symmetric algorithm APIs. Enumeration Data Types Numerical Value Description CRYPTO_SYM_ERROR_CIPNOTSUPPTD -127 Error when cipher algorithm not...","GUID-DBBFA84E-1714-439B-9EAF-1D90B7B847DB.html@@@2.4.1 AES Algorithm APIs@@@...","GUID-DBEAA735-7359-474B-9336-C4DF2261D5D8.html@@@2.8.1.3 Crypto_Sym_AesKeyWrapDirect@@@crypto_Sym_Status_E Crypto_Sym_AesKeyWrapDirect( crypto_HandlerType_E handlerType_en, uint8_t *ptr_inputData, uint32_t inputLen, uint8_t *ptr_outData, uint8_t *ptr_key, uint32_t keyLen, uint8_t...","GUID-DD682253-1D77-40C1-9D3E-1839D2DCCC7A.html@@@3.4.2.1 Crypto_Hash_Shake_Digest@@@crypto_Hash_Status_E Crypto_Hash_Shake_Digest( crypto_HandlerType_E shakeHandlerType_en, crypto_Hash_Algo_E shakeAlgorithm_en, uint8_t *ptr_data, uint32_t dataLen, uint8_t *ptr_digest, uint32_t...","GUID-DDA609C9-2891-4532-90DE-18F96ACFB3AC.html@@@6.2.2 crypto_EccCurveType_E@@@This Enum defines the different Curve Types for the ECC Curve based algorithm. Enumeration Data Types Numerical Value Description CRYPTO_ECC_CURVE_INVALID -1 Enum used invalid curve...","GUID-DDC9DCD3-7E92-45D7-AB54-18488D33A475.html@@@3.5 BLAKE Algorithm@@@BLAKE algorithm is based on stream cipher ChaCha. BLAKE2 algorithm hash calculated without key is called unkeyed hash. BLAKE2 algorithm uses key of size 0 to 64 bytes, and it is optional; else key...","GUID-E0333AB5-E157-42B5-8346-E64AE0565210.html@@@7.2 Imported External Enumerations and Structures@@@...","GUID-E051BABA-24AE-4DEC-AEE0-263CFAD5D258.html@@@3.4.1.1 st_Crypto_Hash_Shake_Ctx@@@This structure is used to define context for SHAKE algorithms variants. Structure Elements Data Type Element Name Description uint32_t shakeSessionId It defines the session ID, must be more than zero...","GUID-E08FF1FE-055F-49A7-A5BD-783824FD64AE.html@@@5.4.2.2 Crypto_Aead_AesEax_Cipher@@@crypto_Aead_Status_E Crypto_Aead_AesEax_Cipher( st_crypto_Aead_AesEax_Ctx * ptr_aesEaxCtx_st, uint8_t *ptr_inputData, uint32_t inputDataLen, uint8_t *ptr_outData, uint8_t *ptr_key, uint8_t *ptr_nonce...","GUID-E140AA65-86BF-4A25-9C60-76B83A688591.html@@@3.5.2.1 Crypto_Hash_Blake_Digest@@@crypto_Hash_Status_E Crypto_Hash_Blake_Digest( crypto_HandlerType_E blakeHandlerType_en, crypto_Hash_Algo_E blakeAlgorithm_en, uint8_t *ptr_data, uint32_t dataLen, uint8_t *ptr_blakeKey, uint32_t...","GUID-E19AC4DB-6777-4F82-AFE6-24A282893CDF.html@@@7.3 ECDH Algorithm@@@The Elliptic-curve Diffie-Hellman (ECDH) algorithm allows two parties, each having an elliptic-curve private-public key pair, to generate a shared secret over the insecure channel. It is a variant of...","GUID-E1A128DA-7F0D-44DA-9D52-4AD4AB2581D8.html@@@3.7.2.2 Crypto_Hash_Ripemd160_Init@@@crypto_Hash_Status_E Crypto_Hash_Ripemd160_Init( st_Crypto_Hash_Ripemd160_Ctx *ptr_ripemdCtx_st, crypto_HandlerType_E ripedmd160Handler_en, uint32_t ripemdSessionId ); This API is used to initiate...","GUID-E32327C9-8680-4667-8B5F-4F611DAE866A.html@@@7.1.1 crypto_Kas_Status_E@@@This enum is used to represent the return type of KAS algorithm APIs. Enumeration Data Types Numerical Value Description CRYPTO_KAS_ERROR_CIPNOTSUPPTD -127 Error when a KAS algorithm not supported by...","GUID-E3B6EF4B-BEE0-4579-8B08-00248B913F0F.html@@@5.4 AES-EAX Algorithm@@@EAX mode was submitted on October 3, 2003, to the attention of NIST by Mihir Bellare, Phillip Rogaway, and David Wagne. EAX mode uses AES-CTR mode for encryption and AES-OMAC for authentication. EAX...","GUID-E70F4B7D-AFE2-47B8-8964-5CFE2B0304D7.html@@@4.3.1 AES-CMAC Structures@@@...","GUID-EAC7F72E-AFD6-4245-AC5C-F3F1536BF653.html@@@3.7.2 RIPEMD-160 Algorithm APIs@@@...","GUID-ED147ED5-D54B-449B-850C-137A3FB80902.html@@@3.6 MD5 Algorithm@@@MD5 (Message Digest) algorithm designed by Ronald Rivest of MIT. It is an extension of the MD4 algorithm...","GUID-EE123160-063E-4DA6-BB14-C383A94684FD.html@@@3.4.2.3 Crypto_Hash_Shake_Update@@@crypto_Hash_Status_E Crypto_Hash_Shake_Update( st_Crypto_Hash_Shake_Ctx* ptr_shakeCtx_st, uint8_t *ptr_data, uint32_t dataLen ); This API performs hash calculation for different variants SHAKE...","GUID-EFADA66D-43AD-4BA9-87BC-53D343C71258.html@@@2.3 Symmetric Algorithms Structures@@@...","GUID-EFBFDAE7-FA1D-4BD5-BB32-79C7E59CEEB0.html@@@5.2.1 crypto_HandlerType_E@@@This enum defines the handler type. Handler type defines which component will do the cipher operation. It can be internal or external hardware crypto engine or any crypto software library. Enumeration...","GUID-F01E35C5-E73C-4595-ACD6-37B285C60E52.html@@@8.2.1 crypto_HandlerType_E@@@This enum defines the handler type. Handler type defines which component will do the cipher operation. It can be internal or external hardware crypto engine or any crypto software library. Enumeration...","GUID-F2419079-08CD-4166-99E1-49833788C40F.html@@@5.4.1 AES-EAX Structures@@@...","GUID-F40E0E13-076D-42AC-AF0A-8BC075FC8459.html@@@2.5.1.4 Crypto_Sym_Camellia_DecryptDirect@@@crypto_Sym_Status_E Crypto_Sym_Camellia_EncryptDirect( crypto_HandlerType_E handlerType_en, crypto_Sym_OpModes_E opMode_en, uint8_t *ptr_inputData, uint32_t dataLen, uint8_t *ptr_outData, uint8_t...","GUID-F56D9AD6-DFB5-4121-9E0A-8210DDCD8E17.html@@@2.2 Imported External Enumerations and Structures@@@These below enums and structures are imported from other files...","GUID-F6C472FF-A886-4328-9DEE-555AC354CC5C.html@@@2.8.1 Key-Wrap Algorithm APIs@@@...","GUID-FA428BD6-4E3C-4F86-AB8C-F098C5B65D64.html@@@4.2 Imported External Enumerations and Structures@@@...","GUID-FBEDB0C4-1A44-44BA-9013-28650AEBEEFD.html@@@6.3 ECDSA Algorithm@@@The Elliptic-curve Digital Signature Algorithm (ECDSA) is a variant of DSA algorithm which uses Elliptic-Curve. Initially, two parties should agree on the curve parameter to which includes curve and...","GUID-FBF79FEF-8825-4DAB-A321-DDDBEE4BF16B.html@@@3.7.2.4 Crypto_Hash_Ripemd160_Final@@@crypto_Hash_Status_E Crypto_Hash_Ripemd160_Final( st_Crypto_Hash_Ripemd160_Ctx *ptr_ripemdCtx_st, uint8_t *ptr_digest ); This API is used to get the calculated hash/digest for RIPEMD-160 algorithm in...","GUID-FC21D47D-1B95-4548-83D1-4C1AEED3AC9F.html@@@2.4.1.5 Crypto_Sym_Aes_DecryptDirect@@@crypto_Sym_Status_E Crypto_Sym_Aes_DecryptDirect( crypto_HandlerType_E handlerType_en, crypto_Sym_OpModes_E opMode_en, uint8_t *ptr_inputData, uint32_t dataLen, uint8_t *ptr_outData, uint8_t *ptr_key...","GUID-FC2A40EA-C4FE-478C-B65B-47F1AE13F28E.html@@@3.6.1.1 st_Crypto_Hash_Md5_Ctx@@@This structure is used to define context for Md5 algorithms variants. Structure Elements Data Type Element Name Description uint32_t md5SessionId It defines the session ID, must be more than zero...","cshelp.html@@@Context Sensitive Help@@@..."];
});