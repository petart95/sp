#include "Error.h"

void error(const char* format, ...) {
    va_list args;
    va_start(args, format);
    vfprintf(stderr, format, args);
    va_end(args);
    
    exit(EXIT_FAILURE);
}

void error(std::string s) {
    error(("***ERROR*** " + s + "\n").c_str());
}