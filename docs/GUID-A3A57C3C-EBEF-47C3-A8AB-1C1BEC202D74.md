# CRYPT\_AES\_GCM\_Decrypt Function

**Parent topic:**[MPLAB® Harmony Crypto Library](GUID-20F7C343-23D4-42D9-B8C2-A97D4D0EE5CD.md)

## C

```
int CRYPT_AES_GCM_Decrypt(
    CRYPT_AES_CTX* aes, 
    unsigned char* out, 
    const unsigned char* in, 
    unsigned int sz, 
    const unsigned char* iv, 
    unsigned int ivSz, 
    const unsigned char* authTag, 
    unsigned int authTagSz, 
    const unsigned char* authIn, 
    unsigned int authInSz
);
```

## Description

This function decrypts a block of data using the AES algorithm in Galois/Counter Mode \(GCM\).

## Preconditions

Key must be set earlier with a call to CRYPT\_AES\_GCM\_SetKey.

## Parameters

|Parameters|Description|
|----------|-----------|
|aes|Pointer to context which saves state between calls.|
|out|Pointer to buffer to store the results of the decryption pass.|
|in|Pointer to buffer holding the data to be decrypted.|
|sz|Size of the input data, in bytes.|
|iv|Pointer to the initialization vector.|
|ivSz|Size of the initialization vector.|
|authTag|Pointer to the buffer to store the authentication tag.|
|authTagSz|Size of the authentication tag.|
|authIn|Pointer to the additional authentication data.|
|authInSz|Size of the additional authentication data.|

## Returns

-   BAD\_FUNC\_ARG - An invalid pointer was passed to the function. -AES\_GCM\_AUTH\_E - The authTag is incorrect.

-   0 - An invalid pointer was not passed to the function.


## Remarks

The output buffer must be equal in size to the input buffer.

