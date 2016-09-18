#include "Memory.h"
#include "ProcessString.h"
#include "Log.h"

ubyte* MEM;

std::vector<char> inputBuffer;

CPU cpu;

unsigned long long readFromMem(unsigned long long memIndex, int bitOffset, unsigned long long size) {
    unsigned long long *data = (unsigned long long *)(((unsigned long long)MEM) + memIndex);
    unsigned long long index = sizeof(unsigned long long)*8 - size - bitOffset;
    
    return READFROM(__builtin_bswap64(*data), index, size);
}

void writeToMem(unsigned long long memIndex, int bitOffset, unsigned long long size, unsigned long long value) {
    unsigned long long *data = (unsigned long long *)(((unsigned long long)MEM) + memIndex);
    unsigned long long index = sizeof(unsigned long long)*8 - size - bitOffset;
    
    unsigned long long a = __builtin_bswap64(*data);
    
    WRITETO(a, index, size, value);
    
    *data = __builtin_bswap64(a);
}

unsigned long long readFromMem(unsigned long long memIndex, unsigned long long size) {
    return readFromMem(memIndex/8, memIndex%8, size);
}

void writeToMem(unsigned long long memIndex, unsigned long long size, unsigned long long value) {
    writeToMem(memIndex/8, memIndex%8, size, value);
}

