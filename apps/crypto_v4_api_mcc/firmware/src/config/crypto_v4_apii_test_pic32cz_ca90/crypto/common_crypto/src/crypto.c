//crypto_v4.c


//I_Crypto_Hash_Sha_Digest
//1   st_Crypto_Sha_Hash_Ctx* ptr_shaCtx_st Input  Hash Algorithm and Crypto handler context
//2   uint8_t*                ptr_data      Input  Input data which digest needs to calculate
//3   uint32_t                dataLen       Input  Length of the input data in no. of bytes
//4   uint8_t*                ptr_digest    Output Pointer to store calculated digest
crypto_Hash_Status_E I_Crypto_Hash_Sha_Digest(
        st_Crypto_Sha_Hash_Ctx *ptr_shaCtx_st, 
        uint8_t *ptr_data, 
        uint32_t dataLen, uint8_t *ptr_digest)
{
    return CRYPTO_HASH_FAIL;
}

//I_Crypto_Hash_Sha_Init
//1   st_Crypto_Sha_Hash_Ctx* ptr_shaCtx_st     Output Hash Algorithm and Crypto handler selection
//2   crypto_Hash_Algo_E      shaAlgorithm_en   Input  Hash Algorithm selection 
//3   crypto_HandlerType_E    shaHandler_en     Input  Input to select Crypto engine SW library or HW crypto
//4   uint32_t                shaSessionId      Input  Element for the Session ID else 0
//    crypto_Hash_Status_E returns the status of the API.
crypto_Hash_Status_E I_Crypto_Hash_Sha_Init(
        st_Crypto_Sha_Hash_Ctx *ptr_shaCtx_st, 
        crypto_Hash_Algo_E shaAlgorithm_en, 
        crypto_HandlerType_E shaHandler_en, 
        uint32_t shaSessionId)
{
    return CRYPTO_HASH_FAIL;
}

//I_Crypto_Hash_Sha_Update
//1   st_Crypto_Sha_Hash_Ctx* ptr_shaCtx_st  Output Hash Algorithm and Crypto handler selection
//2   uint8_t*                ptr_data       Input  Input data which digest needs to calculate
//3   uint32_t                dataLen        Input  Length of the input data in no. of bytes
//    crypto_Hash_Status_E returns the status of the API.
crypto_HandlerType_E I_Crypto_Hash_Sha_Update(
        st_Crypto_Sha_Hash_Ctx *ptr_shaCtx_st, 
        uint8_t *ptr_data, 
        uint32_t dataLen) 
{
    return CRYPTO_HASH_FAIL;
}


//I_Crypto_Hash_Sha_Final
//1   st_Crypto_Sha_Hash_Ctx ptr_shaCtx_st Input/out //Hash Algorithm and Crypto handler selection
//2   uint8_t*               ptr_digest    Output    //Pointer to store calculated digest
//crypto_Hash_Status_E returns the status of the API.
crypto_HandlerType_E I_Crypto_Hash_Sha_Final(
        st_Crypto_Sha_Hash_Ctx *ptr_shaCtx_st, 
        uint8_t *ptr_digest)
{
    return CRYPTO_HASH_FAIL;
}

//SHA3-SHAKE
//Secure Hash Algorithm with KECCAK referred to as "SHAKE". SHA-3 has two
//extendable-output functions (XOFs) SHAKE-128 and SHAKE-256.

//I_Crypto_Hash_Shake_Digest 
//1   st_Crypto_Sha_Hash_Ctx* ptr_shakeCtx_st   Input   Hash Algorithm and Crypto handler selection
//2   uint8_t*                ptr_data          Input   Input data which digest needs to calculate
//3   uint32_t                dataLen           Input   Length of the input data in no. of bytes
//4   uint8_t*                ptr_digest       Output   Pointer to store calculated digest
//crypto_Hash_Status_E returns the status of the API.
crypto_Hash_Status_E I_Crypto_Hash_Shake_Digest(
        st_Crypto_Shake_Hash_Ctx* ptr_shakeCtx_st, 
        uint8_t *ptr_data, 
        uint32_t dataLen, 
        uint8_t *ptr_digest)
{
    return CRYPTO_HASH_FAIL;
}
 
//I_Crypto_Hash_Shake_Init
//1   st_Crypto_Sha_Hash_Ctx* ptr_shakeCtx_st   Output   Hash Algorithm and Crypto handler selection
//2   crypto_Hash_Algo_E shakeAlgorithm_en   Input   Hash Algorithm selection
//3   uint32_t   digestlen   Input   Hash length required by user in bytes in multiple of 8
//4   crypto_HandlerType_E shakeHandlerType_en   Input   Input to select the Crypto engine i.e., SW library or HW crypto
//    crypto_Hash_Status_E returns the status of the API.
crypto_Hash_Status_E I_Crypto_Hash_Shake_Init(
        st_Crypto_Shake_Hash_Ctx* ptr_shakeCtx_st, 
        crypto_Hash_Algo_E shakeAlgorithm_en, 
        crypto_HandlerType_E shakeHandlerType_en, 
        uint32_t digestlen)
{
    return CRYPTO_HASH_FAIL;
}

//I_Crypto_Hash_Shake_Update
//1   st_Crypto_Sha_Hash_Ctx* ptr_shakeCtx_st   Input   Hash Algorithm and Crypto handler selection
//2   uint8_t*   ptr_data   Input   Input data which digest needs to calculate
//3   uint32_t   dataLen   Input   Length of the input data in no. of bytes
//    crypto_Hash_Status_E returns the status of the API.
crypto_HandlerType_E I_Crypto_Hash_Shake_Update(
        st_Crypto_Hash_Shake_Ctx* ptr_shakeCtx_st, 
        uint8_t *ptr_data, 
        uint32_t dataLen)
{
    return CRYPTO_HASH_FAIL;
}

//I_Crypto_Hash_ShakeFinal
//1   st_Crypto_Hash_Shake_Ctx* ptr_shakeCtx_st   Input   Hash Algorithm and Crypto handler selection
//2   uint8_t*   ptr_digest   Output   Pointer to store calculated digest
//    crypto_Hash_Status_E returns the status of the API.
crypto_HandlerType_E I_Crypto_Hash_ShakeFinal(
        st_Crypto_Hash_Shake_Ctx* ptr_shakeCtx_st, 
        uint8_t *ptr_digest)
{
    return CRYPTO_HASH_FAIL;
}

//BLAKE Algorithm
//BLAKE Algorithm is based on stream cipher ChaCha. BLAKE2 algorithm hash
//calculated without key is called unkeyed Hash. BLAKE2 Algorithm uses key of
//size 0 to 64 bytes, and it is optional else key length will be 0. Here is the
//list of variants supported by BLAKE:
//Algorithms   BLAKE Algorithms Variants   Digest Size (bits)   Block Size (bits)   Reference Standard Docs
//  BLAKE   BLAKE-224   224   512   
//  BLAKE-256   256   512   
//  BLAKE-384   384   1024   
//  BLAKE-512   512   1024   
//  BLAKE2   BLAKE2b   <= 512 (user defined   1024   RFC 7693 blake2.pdf

//  BLAKE2s   <= 256 (user defined)   512   
//  BLAKE2s-224   224   512   
//  BLAKE2s-224   224   512   
//  BLAKE2s-256   256   512   
//  BLAKE2b-384   384   1024   
//  BLAKE2b-512   512   1024   

//I_Crypto_Hash_Blake_Digest
//1   st_Crypto_Hash_Blake_Ctx* ptr_blakeCtx_st  Input   Blake variant Algorithm and Crypto handler selection
//2   uint8_t*                  ptr_data         Input   Input data which digest needs to calculate
//3   uint32_t                  dataLen          Input   Length of the input data in no. of bytes
//4   uint8_t*                  ptr_digest      Output   Pointer to store calculated digest
//    crypto_Hash_Status_E returns the status of the API.
crypto_Hash_Status_E I_Crypto_Hash_Blake_Digest(
        st_Crypto_Hash_Blake_Ctx *ptr_blakeCtx_st, 
        uint8_t *ptr_data, 
        uint32_t dataLen, 
        uint8_t *ptr_digest)
{
    return CRYPTO_HASH_FAIL;
}

//I_Crypto_Hash_Blake_Init
//1   st_Crypto_Hash_Blake_Ctx* ptr_blakeCtx_st   Output   Blake variant Algorithm and Crypto handler selection
//2   crypto_Hash_Algo_E blakeAlgorithm_en   Input   Hash Algorithm selection
//3   uint8_t*   blakeKey   Input   (Optional) key needed for the BLAKE algo. Else NULL
//4   uint32_t   keySize   Input   (Optional) Key length needed for the BLAKE algo. Else 0
//5   uint32_t   digestSize   Input   Hash length required by user in bytes in multiple of 8
//6   crypto_HandlerType_E blakeHandlerType_en   Input   Input to select the Crypto engine i.e., SW library or HW crypto
//    crypto_Hash_Status_E returns the status of the API.
crypto_Hash_Status_E I_Crypto_Hash_Blake_Init(
        st_Crypto_Hash_Blake_Ctx *ptr_blakeCtx_st, 
        crypto_Hash_Algo_E blakeAlgorithm_en, 
        uint8_t *blakeKey, 
        uint32_t keySize, 
        uint32_t digestSize, 
        crypto_HandlerType_E blakeHandlerType_en)
{
    return CRYPTO_HASH_FAIL;
}

//I_Crypto_Hash_Blake_Update
//1   st_Crypto_Hash_Blake_Ctx* ptr_blakeCtx_st   Input   Blake variant Algorithm and Crypto handler selection
//2   uint8_t*   ptr_data   Input   Input data which digest needs to calculate
//3   uint32_t   dataLen   Input   Length of the input data in no. of bytes
//    crypto_Hash_Status_E
crypto_HandlerType_E I_Crypto_Hash_Blake_Update(
        st_Crypto_Hash_Blake_Ctx * ptr_blakeCtx_st, 
        uint8_t *ptr_data, 
        uint32_t dataLen) 
{
    return CRYPTO_HASH_FAIL;
}

//I_Crypto_Hash_Blake_Final
//1   st_Crypto_Hash_Blake_Ctx* ptr_blakeCtx_st   Input   Blake variant Algorithm and Crypto handler selection
//2   uint8_t*   ptr_digest   Output   Pointer to store calculated digest
//    crypto_Hash_Status_E returns the status of the API.
crypto_HandlerType_E I_Crypto_Hash_Blake_Final(
        st_Crypto_Hash_Blake_Ctx * ptr_blakeCtx_st, 
        uint8_t *ptr_digest)
{
    return CRYPTO_HASH_FAIL;
}

//MD5 Algorithm
//MD5 (Message Digest) algorithm designed by Ronald Rivest of MIT. It is an
//extension of the MD4 algorithm.

//Algorithms   Digest Size (bits)   Block Size (bits)   Reference Standard Docs
//MD5   128   512   RFC 1321

//I_Crypto_Hash_Md5_Digest
//1   st_Crypto_Hash_Md5_Ctx ptr_md5Ctx_st   Input   Md5 Algorithm and Crypto handler context
//2   uint8_t*   ptr_data   Input   Input data which digest needs to calculate
//3   uint32_t   dataLen   Input   Length of the input data in no. of bytes
//4   uint8_t*   ptr_digest   Output   Pointer to store calculated digest
//    crypto_Hash_Status_E returns the status of the API.
crypto_Hash_Status_E I_Crypto_Hash_Md5_Digest(
        st_Crypto_Hash_Md5_Ctx *ptr_md5Ctx_st, 
        uint8_t *ptr_data, 
        uint32_t dataLen, 
        uint8_t *ptr_digest)
{
    return CRYPTO_HASH_FAIL;
}

//Crypto_Hash_Md5_Init
//1   st_Crypto_Hash_Md5_Ctx* ptr_md5Ctx_st     Output  Md5 Algorithm and Crypto handler context
//2   crypto_HandlerType_E    md5HandlerType_en Input   Input to select the Crypto engine i.e., SW library or HW crypto
//    crypto_Hash_Status_E returns the status of the API.
crypto_Hash_Status_E I_Crypto_Hash_Md5_Init(
        st_Crypto_Hash_Md5_Ctx *ptr_md5Ctx_st, 
        crypto_HandlerType_E md5HandlerType_en)
{
    return CRYPTO_HASH_FAIL;
}

//Crypto_Hash_Md5_Update
//1   st_Crypto_Hash_Md5_Ctx* ptr_md5Ctx_st   Input   Md5 Algorithm and Crypto handler context
//2   uint8_t*   ptr_data   Input   Input data which digest needs to calculate
//3   uint32_t   dataLen   Input   Length of the input data in no. of bytes
//    crypto_Hash_Status_E returns the status of the API.
crypto_HandlerType_E I_Crypto_Hash_Md5_Update(
        st_Crypto_Hash_Md5_Ctx * ptr_md5Ctx_st, 
        uint8_t *ptr_data, 
        uint32_t dataLen)
{
    return CRYPTO_HASH_FAIL;
}

//I_Crypto_Hash_Md5_Final
//1   st_Crypto_Hash_Md5_Ctx* ptr_md5Ctx_st   Input   Md5 Algorithm and Crypto handler context
//2   uint8_t*   ptr_digest   Output   Pointer to store calculated digest
//    crypto_Hash_Status_E returns the status of the API.
crypto_HandlerType_E I_Crypto_Hash_Md5_Final(
        st_Crypto_Hash_Md5_Ctx * ptr_md5Ctx_st, 
        uint8_t *ptr_digest)
{
    return CRYPTO_HASH_FAIL;
}

//RIPEMD-160 Algorithm
//RIPEMD-160 (RIPE Message Digest) is a variant of RIPEMD hash function family.
//It has evolved from 256-bit extension of MD4. RIPEMD-160 is part of the ISO/IEC
//international standard ISO/IEC 10118-3:2004. 
//Algorithm   Digest Size (bits)   Block Size (bits)   Reference Standard Docs
//RIPEMD-160   160   512   RIPEMD-160

//I_Crypto_Hash_Ripemd_Digest
//1   st_Crypto_Hash_Ripemd160_Ctx* ptr_ripemdCtx_st   Output   Hash Algorithm and Crypto handler context
//2   uint8_t*   ptr_data   Input   Input data which digest needs to calculate
//3   uint32_t   dataLen   Input   Length of the input data in no. of bytes
//4   uint8_t*   ptr_digest   Output   Pointer to store calculated digest
//    crypto_Hash_Status_E returns the status of the API.
crypto_Hash_Status_E I_Crypto_Hash_Ripemd_Digest(
        st_Crypto_Hash_Ripemd160_Ctx* ptr_ripemdCtx_st, 
        uint8_t *ptr_data, 
        uint32_t dataLen, 
        uint8_t *ptr_digest)
{
    return CRYPTO_HASH_FAIL;
}
 
//I_Crypto_Hash_Ripemd160_Init
//1   st_Crypto_Hash_Ripemd160_Ctx* ptr_ripemdCtx_st   Output   Hash Algorithm and Crypto handler context
//2   crypto_HandlerType_E ripemdHandlerType_en   Input   Input to select the Crypto engine i.e., SW library or HW crypto
//3   uint32_t   ripemdSessionId   Input   Element for the Session ID else 0
//    crypto_Hash_Status_E returns the status of the API.
crypto_Hash_Status_E I_Crypto_Hash_Ripemd160_Init(
        st_Crypto_Hash_Ripemd160_Ctx *ptr_ripemdCtx_st, 
        crypto_HandlerType_E ripemdHandlerType_en, 
        uint32_t ripemdSessionId)
{
    return CRYPTO_HASH_FAIL;
}

//I_Crypto_Hash_Ripemd160_Update
//1   st_Crypto_Hash_Ripemd160_Ctx* ptr_ripemdCtx_st   Input   Hash Algorithm and Crypto handler context
//2   uint8_t*   ptr_data   Input   Input data which digest needs to calculate
//3   uint32_t   dataLen   Input   Length of the input data in no. of bytes
//    crypto_Hash_Status_E returns the status of the API.
crypto_HandlerType_E I_Crypto_Hash_Ripemd160_Update(
        st_Crypto_Hash_Ripemd160_Ctx *ptr_ripemdCtx_st, 
        uint8_t *ptr_data, 
        uint32_t dataLen) 
{
    return CRYPTO_HASH_FAIL;
}

//I_Crypto_Hash_Ripemd160_Final
//1   st_Crypto_Hash_Ripemd160_Ctx* ptr_ripemdCtx_st   Input   Hash Algorithm and Crypto handler context
//2   uint8_t*   ptr_digest   Output   Pointer to store calculated digest
//    crypto_Hash_Status_E returns the status of the API.
crypto_HandlerType_E I_Crypto_Hash_Ripemd160_Final(
        st_Crypto_Hash_Ripemd160_Ctx *ptr_ripemdCtx_st, 
        uint8_t *ptr_digest)
{
    return CRYPTO_HASH_FAIL;
}
