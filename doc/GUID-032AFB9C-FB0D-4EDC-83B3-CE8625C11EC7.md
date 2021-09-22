# CRYPT_AES_GCM_Encrypt Function

## C
    int CRYPT_AES_GCM_Encrypt(
        CRYPT_AES_CTX* aes, 
        unsigned char* out, 
        const unsigned char* in, 
        unsigned int sz, 
        const unsigned char* iv, 
        unsigned int ivSz, 
        unsigned char* authTag, 
        unsigned int authTagSz, 
        const unsigned char* authIn, 
        unsigned int authInSz
    );

## Description

This function encrypts a block of data using the AES algorithm in Galois/Counter Mode (GCM).

## Preconditions

Key must be set earlier with a call to CRYPT_AES_GCM_SetKey.

## Parameters

|Parameters  |Description  |
|----|----|
|aes  |Pointer to context which saves state between calls.  |
|out |Pointer to buffer to store the results of the encryption pass. |
|in |Pointer to buffer holding the data to be encrypted. |
|sz |Size of the input data, in bytes. |
|iv |Pointer to the initialization vector. |
|ivSz |Size of the initialization vector. |
|authTag |Pointer to the buffer to store the authentication tag. |
|authTagSz |Size of the authentication tag. |
|authIn |Pointer to the additional authentication data. |
|authInSz |Size of the additional authentication data. |


## Returns

- BAD_FUNC_ARG - An invalid pointer was passed to the function.
- 0 - An invalid pointer was not passed to the function.

## Remarks

The output buffer must be equal in size to the input buffer.


