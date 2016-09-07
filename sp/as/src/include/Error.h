#ifndef ERROR_H_
#define ERROR_H_

#include <cstdio>
#include <cstdlib>
#include <cstdarg>
#include <string>

#include "ProcessString.h"
#include "Colors.h"

#define ERROR_PREFIX ""

#define CONCATENATE_STRINGS(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, ...) \
(toString(_0) + toString(_1) + toString(_2) + toString(_3) + toString(_4) + \
 toString(_5) + toString(_6) + toString(_7) + toString(_8) + toString(_9))

#define ERROR(...) error(CONCATENATE_STRINGS(ERROR_PREFIX, __VA_ARGS__, "", "", "", "", "", "", "", "", ""))

void error(const char* format, ...);

void error(std::string s);

void setErrorColumToEndOfLine();
void setErrorColumToBeginingOfString(std::string s);

#endif
