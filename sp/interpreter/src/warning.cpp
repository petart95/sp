#include "Warning.h"

#include "as.h"

void warning(const char* format, ...) {
    va_list args;
    va_start(args, format);
    vfprintf(stderr, format, args);
    va_end(args);
}

void warning(std::string s) {
    std::string prefix(inFile + ":" + toString(currentLineNumber) + ":");  

    warning((BOLD(prefix + MAG(" warning: ")) + s + "\n").c_str());
}

