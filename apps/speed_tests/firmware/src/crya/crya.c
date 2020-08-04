/*******************************************************************************
  Crypto Speed Test Source File

  Company:
    Microchip Technology Inc.

  File Name:
    crya.c

  Description:
 * Entry points for the CRYA functions.
 *   see also datasheet SAML11 Omega DS60001513
 *******************************************************************************
 */

//DOM-IGNORE-BEGIN
/*****************************************************************************
 Copyright (C) 2013-2020 Microchip Technology Inc. and its subsidiaries.

Microchip Technology Inc. and its subsidiaries.

Subject to your compliance with these terms, you may use Microchip software 
and any derivatives exclusively with Microchip products. It is your 
responsibility to comply with third party license terms applicable to your 
use of third party software (including open source software) that may 
accompany Microchip software.

THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED 
WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A PARTICULAR 
PURPOSE.

IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS 
BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE 
FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN 
ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY, 
THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
*****************************************************************************/

//DOM-IGNORE-END


/* It is necessary to include configuration.h first because
 * the WC settings.h file depends on these values but does not
 * include it for itself. :(
 * */
#include "configuration.h"
#include "crya/crya.h"
#include <assert.h>
#include <string.h> // for memcpy()

/* CRYA entry points are located in ROM as defined by the device file.
 */
#if defined __SAML11E16A__
#include "crya\crya_saml11.h"

#define assert_dbug(X) __conditional_software_breakpoint((X))
#define ARRAY_SIZE(a)  (sizeof(a)/sizeof(a[0]))

/* *********************************************************************
   *********************************************************************
   * ROM-call wrappers for validation of pointer alignments
   *********************************************************************
   *********************************************************************
 */
__attribute__((used)) void crya_aes128_encrypt
    (const uint8_t *keys, uint32_t key_len, const uint8_t *src, uint8_t *dst)
{
    assert_dbug(16 == key_len);
    assert_dbug(keys && (0 == ((uint32_t)keys%4)));
    assert_dbug(src && (0 == ((uint32_t)src%4)));
    assert_dbug(dst && (0 == ((uint32_t)dst%4)));

    secure_crya_aes128_encrypt(keys,key_len,src,dst);
}

__attribute__((used)) void crya_aes128_decrypt
    (const uint8_t *keys, uint32_t key_len, const uint8_t *src, uint8_t *dst)
{
    assert_dbug(16 == key_len);
    assert_dbug(keys && (0 == ((uint32_t)keys%4)));
    assert_dbug(src && (0 == ((uint32_t)src%4)));
    assert_dbug(dst && (0 == ((uint32_t)dst%4)));
    
    secure_crya_aes128_decrypt(keys,key_len,src,dst);
}

void crya_gf_mult128
    (const uint32_t *block1, const uint32_t *block2, uint32_t *dst)
{
    assert_dbug(block1 && (0 == ((uint32_t)block1%4)));
    assert_dbug(block2 && (0 == ((uint32_t)block2%4)));
    assert_dbug(dst && (0 == ((uint32_t)dst%4)));
    
    secure_crya_gf_mult128(block1,block2,dst);
}

#if !defined(NO_SHA256)
#include "wolfcrypt/sha256.h"

void crya_sha256_process
    (uint32_t hash_in_out[8], const uint8_t data[64])
{
    // 8*uint32 is 256 bits hash buffer
    assert_dbug(hash_in_out && (0 == ((uint32_t)hash_in_out%4)));
    assert_dbug(data && (0 == ((uint32_t)data%4)));
    
    /* 256 bytes required for message schedule table working room.
     * This buffer is allocated on the stack to allow threaded execution.
     */
    uint32_t ram_buf[64]; // alignment guaranteed
    secure_crya_sha256_process(hash_in_out,data,ram_buf);
}
#endif // !NO_SHA256

/* *********************************************************************
   *********************************************************************
   * Helper functions
   *********************************************************************
   *********************************************************************
 */
uint32_t endian32(const uint32_t input)
{
    uint32_t answer;
    uint32_t value = input; // make sure the source is in RAM
    
    uint8_t * A = (uint8_t*)&answer;
    uint8_t * V = ((uint8_t*)(&value))+sizeof(value)-1;
    for (int i = 0; i < sizeof(answer); i++)
        *A++ = *V--;
    
    return answer;
}

/* *********************************************************************
   *********************************************************************
   * CRYA-accelerated driver
   *********************************************************************
   *********************************************************************
 */
#if !defined(NO_SHA256)

#if !defined(SHA256_BLOCK_SIZE)
#define SHA256_BLOCK_SIZE   WC_SHA256_BLOCK_SIZE
#endif

// Generic operation after the hash has been initialized.
static void crya_sha256_block
    (uint32_t hash[8], const uint8_t * data, const size_t length)
{
    size_t bytes = length;
    uint8_t remnant[SHA256_BLOCK_SIZE];
    
    while (SHA256_BLOCK_SIZE <= bytes) // process all full-size blocks
    {
        crya_sha256_process(hash,(const uint8_t*)data);
        data += SHA256_BLOCK_SIZE;
        bytes -= SHA256_BLOCK_SIZE;
    }
    
    assert_dbug(SHA256_BLOCK_SIZE > bytes);
    if (0 != bytes)
        memcpy(remnant, data, bytes); // bring up the remaining data
    
    // Zap the buffer tail and set the single bit after the message
    memset(&remnant[bytes],0x00,SHA256_BLOCK_SIZE-bytes);
    remnant[bytes++] = 0x80; // count this byte as it goes into the buffer
    
    // If there are not 8 bytes remaining, post what we have
    // and reset the buffer to prepare for posting the length field.
    if ((SHA256_BLOCK_SIZE-8) < bytes) // i.e. (SHA256_BLOCK_SIZE-bytes < 8)
    {
        crya_sha256_process(hash,remnant);
        memset(remnant,0,SHA256_BLOCK_SIZE);
    }
    
    // We know for certain that the final 8 bytes are now all zero
    // (whether we have data in the low-part of the buffer or not)
    // so the length field is simply the last few bytes (endian corrected).
    {
        // The buffered value is bit-length instead of byte-length
        register size_t bitLength = length * 8; // bits-per-byte
        assert_dbug(8 >= sizeof(bitLength)); // verify an assumption
        
        // FIPS-180-4 requires big-endian format for the length field.
        uint8_t * R = &remnant[SHA256_BLOCK_SIZE-1]; // last buffer byte
        for (int i = 0; i < sizeof(bitLength); i++) // foreach byte
        {
            *R-- = (uint8_t)(bitLength & 0xFF);
            bitLength >>= 8; // endian independent, but destroys bitLength
        }
    }
    crya_sha256_process(hash,remnant);

    // Endian swap here because CRYA is big-endian and we are not.
    for (int i = 0; i < 8; i++)
        hash[i] = endian32(hash[i]);
}

// End-to-end hash operator using 256b initialization
int crya_sha256(uint32_t hash[8], const uint8_t * data, const size_t length)
{
    hash[0] = (0x6a09e667);
    hash[1] = (0xbb67ae85);
    hash[2] = (0x3c6ef372);
    hash[3] = (0xa54ff53a);
    hash[4] = (0x510e527f);
    hash[5] = (0x9b05688c);
    hash[6] = (0x1f83d9ab);
    hash[7] = (0x5be0cd19);
    
    crya_sha256_block(hash, data, length);
    return 0;
}

#if defined(WOLFSSL_SHA224)
// End-to-end hash operator using 224b initialization
void crya_sha224(uint32_t hash[8], const uint8_t * data, const size_t length)
{
    hash[0] = 0xc1059ed8;
    hash[1] = 0x367cd507;
    hash[2] = 0x3070dd17;
    hash[3] = 0xf70e5939;
    hash[4] = 0xffc00b31;
    hash[5] = 0x68581511;
    hash[6] = 0x64f98fa7;
    hash[7] = 0xbefa4fa4;
    
    crya_sha256_block(hash, data, length);
    // only 7 of the 8 words are valid
}
#endif // WOLFSSL_SHA224
#endif // !NO_SHA256

/* *********************************************************************
   *********************************************************************
   * Entry points for test
   *********************************************************************
   *********************************************************************
 */
#define CRYA_TEST_AES128    0
#if CRYA_TEST_AES128
void crya_test_aes()
{
    static CRYA_ALIGN uint8_t plaintext[160];
    static CRYA_ALIGN uint8_t cyphertext_crya[160];
    static CRYA_ALIGN uint8_t cyphertext_wc[160];
    static CRYA_ALIGN uint8_t recovery_crya[160];
    static CRYA_ALIGN uint8_t recovery_wc[160];

    static CRYA_ALIGN uint8_t const key[16] = "123456789ABCDEF0";
#define key_len     ARRAY_SIZE(key)

    memset(cyphertext_crya,0,ARRAY_SIZE(cyphertext_crya));
    memset(recovery_crya,0,ARRAY_SIZE(recovery_crya));
    memset(plaintext,0x72,ARRAY_SIZE(plaintext));
    
    crya_aes_encrypt(key,key_len,plaintext,cyphertext_crya);
    crya_aes_decrypt(key,key_len,cyphertext_crya,recovery_crya);

    Aes enc;
    wc_AesSetKeyDirect(&enc, key, key_len, (void*)0, AES_ENCRYPTION);
    wc_AesEncryptDirect(&enc, cyphertext_wc, plaintext);
    wc_AesSetKeyDirect(&enc, key, key_len, (void*)0, AES_DECRYPTION);
    wc_AesDecryptDirect(&enc, recovery_wc, cyphertext_wc);
    
    cryptoST_PRINT_hexLine(     "     key ", key, 16);
    cryptoST_PRINT_hexLine(CRLF "   plain ", plaintext, 16);
    cryptoST_PRINT_hexLine(CRLF "crya_enc ", cyphertext_crya, 16);
    cryptoST_PRINT_hexLine(CRLF "crya_rec ", recovery_crya, 16);
    cryptoST_PRINT_hexLine(CRLF "wolf_enc ", cyphertext_wc, 16);
    cryptoST_PRINT_hexLine(CRLF "wolf_rec ", recovery_wc, 16);
    PRINT(CRLF);
            
    // __builtin_software_breakpoint();
}
#else
#define crya_test_aes()     ((void*)0)
#endif // CRYA_TEST_AES128

#define CRYA_TEST_SHA256    0
/* This test has been ported to a standard 
 * test data structure at cryptoSTD_sha256.c
 */
#if CRYA_TEST_SHA256
#include "wolfssl/wolfcrypt/hash.h"
static void WC_sha256
    (uint32_t hash[8], const uint8_t * data, const size_t length)
{
    wc_Sha256Hash(data, length, (uint8_t*)hash);
}

void crya_test_compare(char * tag, 
        const uint8_t data[], size_t length)
{
    char label[20];
    uint32_t wc_hash[8]; // 8*32=256 bits
    uint32_t crya_hash[8]; // 8*32=256 bits
    
    // Build the name string
    strncpy(label, CRLF "wolf_", ALENGTH(label));
    strncat(label, tag, ALENGTH(label));
    WC_sha256(wc_hash, data, length);
    cryptoST_PRINT_hexLine(label, (uint8_t*)wc_hash, 16);

    strncpy(label, CRLF "crya_", ALENGTH(label));
    strncat(label, tag, ALENGTH(label));
    crya_sha256(crya_hash, data, length);
    cryptoST_PRINT_hexLine(label, (uint8_t*)crya_hash, 16);
    PRINT(CRLF);
    
    if (0 == memcmp(wc_hash, crya_hash, ALENGTH(crya_hash)))
    { PRINT("compare OK" CRLF); }
    else
    { PRINT("oops :( " CRLF); }
}

void crya_test_sha1()
{
    static CRYA_ALIGN uint8_t data_abc[3] = {0x61, 0x62, 0x63};
    static CRYA_ALIGN uint8_t data_z1[] = {0x00};
    static CRYA_ALIGN uint8_t data_z2[] = {0x00, 0x00};
    static CRYA_ALIGN uint8_t data_z3[] = {0x00, 0x00, 0x00};
    static CRYA_ALIGN uint8_t data_z4[] = {0x00, 0x00, 0x00, 0x00};
    static CRYA_ALIGN uint8_t data_448[] = 
        "abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq";
    static CRYA_ALIGN uint8_t data_64[64] = {0x00};
    static CRYA_ALIGN uint8_t data_896[] =
        "abcdefghbcdefghicdefghijdefghijkefghijklfghijklmghijklmnhi"
        "jklmnoijklmnopjklmnopqklmnopqrlmnopqrsmnopqrstnopqrstu";
    static CRYA_ALIGN uint8_t data_128[128] = {0x00};
    static CRYA_ALIGN uint8_t data_1k[1024] = {0x00};
    
    // data from https://www.di-mgt.com.au/sha_testvectors.html
    crya_test_compare("abc ", data_abc, ALENGTH(data_abc));
    // answer: ba7816bf 8f01cfea 414140de 5dae2223 b00361a3 96177a9c b410ff61 f20015ad
    crya_test_compare("z0  ", data_z1, 0); // re-use z1
    // answer: e3b0c442 98fc1c14 9afbf4c8 996fb924 27ae41e4 649b934c a495991b 7852b855
    crya_test_compare("z1  ", data_z1, ALENGTH(data_z1));
    crya_test_compare("z2  ", data_z2, ALENGTH(data_z2));
    crya_test_compare("z3  ", data_z3, ALENGTH(data_z3));
    crya_test_compare("z4  ", data_z4, ALENGTH(data_z4));
    crya_test_compare("64  ", data_64, ALENGTH(data_64));
    crya_test_compare("448 ", data_448, ALENGTH(data_448)-1); // discount the null
    // answer: 248d6a61 d20638b8 e5c02693 0c3e6039 a33ce459 64ff2167 f6ecedd4 19db06c1
    crya_test_compare("896 ", data_896, ALENGTH(data_896)-1); // discount the null
    // answer: cf5b16a7 78af8380 036ce59e 7b049237 0b249b11 e8f07a51 afac4503 7afee9d1
    crya_test_compare("128 ", data_128, ALENGTH(data_128)); // 1k bits
    crya_test_compare("1k  ", data_1k, ALENGTH(data_1k)); // 8k bits
}
#else
#define crya_test_sha1()    ((void*)0)
#endif // CRYA_TEST_SHA256

void crya_test_all(void)
{
    (void)crya_test_aes();
    (void)crya_test_sha1();
    
    __builtin_software_breakpoint();
}
#endif // __SAML11E16A__
