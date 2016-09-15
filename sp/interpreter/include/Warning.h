#ifndef WARNING_H_
#define WARNING_H_

#include <cstdio>
#include <cstdlib>
#include <cstdarg>
#include <string>

#include "ProcessString.h"
#include "Colors.h"

#define WARNING_PREFIX ""

#define CONCATENATE_STRINGS(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, ...) \
(toString(_0) + toString(_1) + toString(_2) + toString(_3) + toString(_4) + \
 toString(_5) + toString(_6) + toString(_7) + toString(_8) + toString(_9))

#define WARNING(...) warning(CONCATENATE_STRINGS(WARNING_PREFIX, __VA_ARGS__, "", "", "", "", "", "", "", "", ""))

void warning(const char* format, ...);

void warning(std::string s);

#endif
