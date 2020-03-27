/* 
 * File:   cryptoSTE_sha.h
 * Author: C14102
 *
 * Created on November 6, 2019, 7:49 AM
 */

#ifndef CRYPTOST_SHA_H
#define	CRYPTOST_SHA_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "../test_data/cryptoSpeedTestData.h"

#if 1
const char * cryptoSTE_crya_sha_timed(const cryptoST_testDetail_t * td,
                                      cryptoSTE_testExecution_t * param);
#else
#define cryptoSTE_sha_timed(t_,r_,i_) \
    PRINT("**** SHA is not available!" CRLF);
#endif

#endif // ndef CRYPTOST_SHA_H
