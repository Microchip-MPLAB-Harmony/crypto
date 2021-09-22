# CRYPT_RNG_DeInitialize Function

## C
    int CRYPT_RNG_Deinitialize(
    CRYPT_RNG_CTX* rng
    );

## Description

This function frees the context that stores information relative to random number generation.

## Preconditions

RNG context was initialized using the CRYPT_RNG_Initialize function.

## Parameters

|Parameters  |Description  |
|----|----|
|rng  |Pointer to random number generator context.  |


## Returns

- 0 - Success.

## Remarks 

None.


## Example

    #define RANDOM_BYTE_SZ 32

    int           ret;
    CRYPT_RNG_CTX mcRng;
    byte          out[RANDOM_BYTE_SZ];

    ret = CRYPT_RNG_Initialize(&mcRng);
    ret = CRYPT_RNG_Get(&mcRng, &out[0]);
    ret = CRYPT_RNG_BlockGenerate(&mcRng, out, RANDOM_BYTE_SZ);
     ret = CRYPT_RNG_Deinitialize(&mcRng);