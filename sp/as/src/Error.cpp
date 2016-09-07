#include "Error.h"

#include "as.h"

void error(const char* format, ...) {
    va_list args;
    va_start(args, format);
    vfprintf(stderr, format, args);
    va_end(args);
    
    exit(EXIT_FAILURE);
}

void error(std::string s) {
    std::string prefix(inFile + ":" + toString(currentLineNumber) + ":");
    std::string postfix("");

    if(currentColumNumber != -1) {
        prefix += toString(currentColumNumber) + ":";
        postfix += " " + trim(readNthLine(inFile, currentLineNumber)) + "\n" +
                   std::string(currentColumNumber, ' ') + GRN("^") + "\n";
    }   

    error((BOLD(prefix + RED(" error: ")) + s + "\n" + postfix).c_str());

    currentColumNumber = -1;
}

void setErrorColumToEndOfLine() {
    currentColumNumber = (" " + trim(readNthLine(inFile, currentLineNumber))).length();
}

void setErrorColumToBeginingOfString(std::string s) {
    std::string line = " " + trim(readNthLine(inFile, currentLineNumber));

    currentColumNumber = line.find(s);
}

