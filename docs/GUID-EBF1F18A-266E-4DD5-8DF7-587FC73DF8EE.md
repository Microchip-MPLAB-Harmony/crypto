# CRYPT\_AES\_CTR\_Encrypt Function

**Parent topic:**[MPLAB® Harmony Crypto Library](GUID-20F7C343-23D4-42D9-B8C2-A97D4D0EE5CD.md)

## C

```
int CRYPT_AES_CTR_Encrypt(
CRYPT_AES_CTX* aes, 
unsigned char* out, 
const unsigned char* in, 
unsigned int inSz
);
```

## Description

This function encrypts a block of data using the AES algorithm in Counter \(CTR\) mode.

## Preconditions

Key and Initialization Vector \(IV\) must be set earlier with a call to CRYPT\_AES\_KeySet and CRYPT\_AES\_IvSet.

## Parameters

|Parameters|Description|
|----------|-----------|
|aes|Pointer to context which saves state between calls.|
|out|Pointer to buffer to store the results of the encryption pass.|
|in|Pointer to buffer holding the data to be encrypted.|
|inSz|Size of the input data, in bytes.|

## Returns

-   BAD\_FUNC\_ARG - An invalid pointer was passed to the function.

-   0 - An invalid pointer was not passed to the function.


## Remarks

The output buffer must be equal in size to the input buffer.

## Example

```
CRYPT_AES_CTX mcAes;
int           ret;
byte          out1[AES_TEST_SIZE];

strncpy((char*)key, "1234567890abcdefghijklmnopqrstuv", 32);
strncpy((char*)iv,  "1234567890abcdef", 16);

ret = CRYPT_AES_KeySet(&mcAes, key, 16, iv, CRYPT_AES_ENCRYPTION);
ret = CRYPT_AES_CTR_Encrypt(&mcAes, out1, ourData, AES_TEST_SIZE);
```
