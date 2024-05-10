/*******************************************************************************
  MPLAB Harmony Application Source File

  Company:
    Microchip Technology Inc.

  File Name:
    MCHP_Crypto_DigSign_WolfcryptWrapper.c

  Summary:
    This file contains the source code for the MPLAB Harmony application.

  Description:
    This file contains the source code for the MPLAB Harmony application.  It
    implements the logic of the application's state machine and it may call
    API routines of other MPLAB Harmony modules in the system, such as drivers,
    system services, and middleware.  However, it does not call any of the
    system interfaces (such as the "Initialize" and "Tasks" functions) of any of
    the modules in the system or make any assumptions about when those functions
    are called.  That is the responsibility of the configuration-specific system
    files.
*******************************************************************************/

 
// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************
#include "crypto/common_crypto/MCHP_Crypto_DigSign.h"
#include "crypto/common_crypto/MCHP_Crypto_Common.h"
#include "crypto/common_crypto/MCHP_Crypto_DigSign_WolfcryptWrapper.h"
#include "crypto/common_crypto/MCHP_Crypto_Common_WolfcryptWrapper.h"
#include "wolfssl/wolfcrypt/error-crypt.h"

#ifdef CRYPTO_DIGISIGN_WC_ECDSA_EN
#include "wolfssl/wolfcrypt/random.h"
#include "wolfssl/wolfcrypt/ecc.h"
#endif /* CRYPTO_DIGISIGN_WC_ECDSA_EN */

#ifdef CRYPTO_DIGISIGN_WC_ECDSA_EN
crypto_DigiSign_Status_E Crypto_DigiSign_Wc_Ecdsa_Sign(uint8_t *ptr_wcInputHash, uint32_t wcHashLen, uint8_t *ptr_wcSig, uint32_t wcSigLen, uint8_t *ptr_wcPrivKey, 
                                                       uint32_t wcPrivKeyLen, crypto_EccCurveType_E wcEccCurveType_en)
{
    crypto_DigiSign_Status_E ret_wcEcdsaStat_en;
    ecc_key wcEccPrivKey_st;
    WC_RNG wcRng_st;
    int wcEccCurveId = (int)ECC_CURVE_INVALID;
    int wcEcdsaStat = BAD_FUNC_ARG;
    mp_int r, s;
   
    wcEccCurveId = Crypto_Common_Wc_Ecc_GetWcCurveId(wcEccCurveType_en);
    
    if(wcEccCurveId == (int)ECC_CURVE_INVALID)
    {
        ret_wcEcdsaStat_en = CRYPTO_DIGISIGN_ERROR_CURVE;
    }
    else
    {
        // Setup the RNG
        wcEcdsaStat = wc_InitRng(&wcRng_st);

        if(wcEcdsaStat == 0)
        {
            /* Setup the ECC key */
            wcEcdsaStat = wc_ecc_init(&wcEccPrivKey_st);
            
            if(wcEcdsaStat == 0)
            {
                // Import private key, public part Pass as NULL
                wcEcdsaStat = wc_ecc_import_private_key_ex(ptr_wcPrivKey, wcPrivKeyLen,/* private key "d" */
                                                            NULL, 0,                    /* public (optional) */
                                                            &wcEccPrivKey_st,
                                                            wcEccCurveId                /* ECC Curve Id */
                                                            );
                if(wcEcdsaStat == 0)
                {
                    wcEcdsaStat = mp_init(&r);
                    
                    if(wcEcdsaStat == 0)
                    {        
                        wcEcdsaStat = mp_init(&s);           

                        if(wcEcdsaStat == 0)
                        {
                            wcEcdsaStat = wc_ecc_sign_hash_ex(ptr_wcInputHash, wcHashLen, &wcRng_st, &wcEccPrivKey_st, &r, &s);

                            //Import signature R and S
                            if(wcEcdsaStat == 0)
                            {
                                wcEcdsaStat = mp_to_unsigned_bin_len(&r, (byte*)ptr_wcSig, (int)wcPrivKeyLen);
                            }
                            if(wcEcdsaStat == 0)
                            {
                                wcEcdsaStat = mp_to_unsigned_bin_len(&s, (byte*)(ptr_wcSig + (uint32_t)wcPrivKeyLen), (int)wcPrivKeyLen);
                            }
                        }
                    }
                }
            }
            if(wcEcdsaStat == 0)
            {
                ret_wcEcdsaStat_en = CRYPTO_DIGISIGN_SUCCESS;
            }
            else if(wcEcdsaStat == ECC_CURVE_OID_E)
            {
                ret_wcEcdsaStat_en = CRYPTO_DIGISIGN_ERROR_CURVE;
            }
            else if( (wcEcdsaStat == BAD_FUNC_ARG) || (wcEcdsaStat == ECC_BAD_ARG_E) )
            {
                ret_wcEcdsaStat_en = CRYPTO_DIGISIGN_ERROR_ARG;
            }
            else
            {
                ret_wcEcdsaStat_en = CRYPTO_DIGISIGN_ERROR_FAIL;
            }
        }
        else
        {
            ret_wcEcdsaStat_en = CRYPTO_DIGISIGN_ERROR_RNG;
        }
    }
    
    return ret_wcEcdsaStat_en;
}

crypto_DigiSign_Status_E Crypto_DigiSign_Wc_Ecdsa_Verify(uint8_t *ptr_wcInputHash, uint32_t wcHashLen, uint8_t *ptr_wcInputSig, uint32_t wcSigLen, uint8_t *ptr_wcPubKey, uint32_t wcPubKeyLen, 
                                                         int8_t *ptr_wcHashVerifyStat, crypto_EccCurveType_E wcEccCurveType_en)
{
    crypto_DigiSign_Status_E ret_wcEcdsaStat_en;
    ecc_key wcEccPubKey_st;
    int wcEccCurveId = (int)ECC_CURVE_INVALID;
    int wcEcdsaStat = BAD_FUNC_ARG;
    int ptr_verifyStat = 0;
    mp_int r, s;
    int curveLen = 0;
    
    wcEccCurveId = Crypto_Common_Wc_Ecc_GetWcCurveId(wcEccCurveType_en);
    
    if(wcEccCurveId == (int)ECC_CURVE_INVALID)
    {
        ret_wcEcdsaStat_en = CRYPTO_DIGISIGN_ERROR_CURVE;
    }
    else
    {
        /* Setup the ECC key */
        wcEcdsaStat = wc_ecc_init(&wcEccPubKey_st);
        if(wcEcdsaStat == 0)
        {
            wcEcdsaStat = mp_init(&r);
            if(wcEcdsaStat == 0)
            {        
                wcEcdsaStat = mp_init(&s);
            }
            if(wcEcdsaStat == 0)
            {   
                wcEcdsaStat = wc_ecc_import_x963_ex(ptr_wcPubKey, wcPubKeyLen, &wcEccPubKey_st, wcEccCurveId);

                if(wcEcdsaStat == 0)
                {
                    //Get Curve Length using Curve ID
                    curveLen = wc_ecc_get_curve_size_from_id(wcEccCurveId);

                    // Import signature r and s
                    wcEcdsaStat = mp_read_unsigned_bin(&r, ptr_wcInputSig, (word32)curveLen);
                    if (wcEcdsaStat == 0) 
                    {
                        wcEcdsaStat = mp_read_unsigned_bin(&s, (const byte*)(ptr_wcInputSig+(uint32_t)curveLen), (word32)curveLen);

                        //If Verify status value is 1 then verification is successfully
                        if (wcEcdsaStat == 0) 
                        {
                            wcEcdsaStat = wc_ecc_verify_hash_ex(&r, &s, (const byte*)ptr_wcInputHash, (word32)wcHashLen, &ptr_verifyStat, &wcEccPubKey_st);
                            *ptr_wcHashVerifyStat = (int8_t)ptr_verifyStat;
                        }
                    }
                }
            }
        }
        else
        {
           //do nothing 
        }
        if(wcEcdsaStat == 0)
        {
            ret_wcEcdsaStat_en = CRYPTO_DIGISIGN_SUCCESS;
        }
        else if(wcEcdsaStat == ECC_CURVE_OID_E)
        {
            ret_wcEcdsaStat_en = CRYPTO_DIGISIGN_ERROR_CURVE;
        }
        else if( (wcEcdsaStat == BAD_FUNC_ARG) || (wcEcdsaStat == ECC_BAD_ARG_E) )
        {
            ret_wcEcdsaStat_en = CRYPTO_DIGISIGN_ERROR_ARG;
        }
        else
        {
            ret_wcEcdsaStat_en = CRYPTO_DIGISIGN_ERROR_FAIL;
        }
    }
    
    return ret_wcEcdsaStat_en;
}
#endif /* CRYPTO_DIGISIGN_WC_ECDSA_EN */