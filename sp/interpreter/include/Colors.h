#ifndef _COLORS_
#define _COLORS_

#include "ProcessString.h"

/* FOREGROUND */
#define RST  "\x1B[0m"
#define RED_PREFIX  "\x1B[31m"
#define GRN_PREFIX  "\x1B[32m"
#define YEL_PREFIX  "\x1B[33m"
#define BLU_PREFIX  "\x1B[34m"
#define MAG_PREFIX  "\x1B[35m"
#define CYN_PREFIX  "\x1B[36m"
#define WHT_PREFIX  "\x1B[37m"

#define RED(x) RED_PREFIX + toString(x) + RST
#define GRN(x) GRN_PREFIX + toString(x) + RST
#define YEL(x) YEL_PREFIX + toString(x) + RST
#define BLU(x) BLU_PREFIX + toString(x) + RST
#define MAG(x) MAG_PREFIX + toString(x) + RST
#define CYN(x) CYN_PREFIX + toString(x) + RST
#define WHT(x) WHT_PREFIX + toString(x) + RST

#define BOLD(x) "\x1B[1m" + toString(x) + RST
#define UNDL(x) "\x1B[4m" + toString(x) + RST

#endif  /* _COLORS_ */
