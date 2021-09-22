# CRYPT\_RNG\_DeInitialize Function

**Parent topic:**[MPLAB® Harmony Crypto Library](GUID-20F7C343-23D4-42D9-B8C2-A97D4D0EE5CD.md)

## C

```
int CRYPT_RNG_Deinitialize(
CRYPT_RNG_CTX* rng
);
```

## Description

This function frees the context that stores information relative to random number generation.

## Preconditions

RNG context was initialized using the CRYPT\_RNG\_Initialize function.

## Parameters

|Parameters|Description|
|----------|-----------|
|rng|Pointer to random number generator context.|

## Returns

-   0 - Success.


## Remarks

None.

## Example

```
#define RANDOM_BYTE_SZ 32

int           ret;
CRYPT_RNG_CTX mcRng;
byte          out[RANDOM_BYTE_SZ];

ret = CRYPT_RNG_Initialize(&mcRng);
ret = CRYPT_RNG_Get(&mcRng, &out[0]);
ret = CRYPT_RNG_BlockGenerate(&mcRng, out, RANDOM_BYTE_SZ);
 ret = CRYPT_RNG_Deinitialize(&mcRng);
```

