/*
 * File:   my_assert.h
 * Author: C14575
 *
 * Created on August 7, 2018, 11:48 AM
 */
#ifdef  __cplusplus
extern "C" {
#endif

#if defined(__DEBUG) && defined(__XC32)
#  undef assert
#  define assert(__e) ((__e) ? (void)0 : __builtin_software_breakpoint() )
#endif

#ifdef  __cplusplus
}
#endif
