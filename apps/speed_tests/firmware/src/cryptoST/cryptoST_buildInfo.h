/* 
 * File:   cryptoST_buildInfo.h
 * Author: C14102
 *
 * Created on June 10, 2020, 11:34 AM
 */

#ifndef CRYPTOST_BUILD_INFO_H
#define	CRYPTOST_BUILD_INFO_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <stdbool.h>
typedef struct cryptoST_buildInfo_s
{
    const char buildDate[16];
    const char buildTime[16];
    const char optimized[4];  // yes or no, not the optimization level
    const char processor[16];
} cryptoST_buildInfo_t;

extern cryptoST_buildInfo_t cryptoST_buildInfo;

#ifdef	__cplusplus
}
#endif

#endif	/* CRYPTOST_BUILD_INFO_H */

