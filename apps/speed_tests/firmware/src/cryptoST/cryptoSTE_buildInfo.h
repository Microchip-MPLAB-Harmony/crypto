/* 
 * File:   cryptoSTE_buildInfo.h
 * Author: C14102
 *
 * Created on June 10, 2020, 11:34 AM
 */

#ifndef CRYPTOST_BUILD_INFO_H
#define	CRYPTOST_BUILD_INFO_H

#ifdef	__cplusplus
extern "C" {
#endif

typedef struct cryptoSTE_buildInfo_s
{
    const char * const buildDate;
    const char * const buildTime;
    const char * const optimized;  // yes or no, not the optimization level
    const char * const processor;
} cryptoSTE_buildInfo_t;

extern cryptoSTE_buildInfo_t cryptoSTE_buildInfo;

#ifdef	__cplusplus
}
#endif

#endif	/* CRYPTOST_BUILD_INFO_H */

