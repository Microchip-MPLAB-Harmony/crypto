# CRYPT_SHA256_Initialize Function

## C
    int CRYPT_SHA256_Initialize(
        CRYPT_SHA256_CTX* sha256
    );

## Description

This function initializes the internal structures necessary for SHA256 hash calculations.

## Preconditions

None.

## Parameters
|Parameters |Description |
|---|---|
|sha256 |Pointer to context which saves state between calls. |

## Returns 
- BAD_FUNC_ARG - An invalid pointer was passed to the function.
- 0 - An invalid pointer was not passed to the function. 

## Remarks 

All SHA hashes have to start at a particular value before adding new data to it. This function sets the necessary values for the structure.

## Example 

    CRYPT_SHA256_CTX sha;
    uint8_t shaSum[SHA256_DIGEST_SIZE];

    CRYPT_SHA256_Initialize(&sha);
    CRYPT_SHA256_DataAdd(&sha, buffer, sizeof(buffer));
    CRYPT_SHA256_Finalize(&sha, shaSum);