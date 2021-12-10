#ifndef _WOLFCRYPT_REQUIRED_CONFIG_H_
#define _WOLFCRYPT_REQUIRED_CONFIG_H_

#include "configuration.h"

#include <stddef.h>

#ifndef min
#define min(a,b) (((a) < (b)) ? (a) : (b))
#define WOLFSSL_HAVE_MIN
#endif


#endif