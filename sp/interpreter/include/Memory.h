#ifndef MEMORY_H_
#define MEMORY_H_

#define GETMASK(index, size) (((1L << (size)) - 1L) << (index))
#define READFROM(data, index, size) (((data) & GETMASK((index), (size))) >> (index))
#define WRITETO(data, index, size, value) ((data) = ((data) & (~GETMASK((index), (size)))) | ((value) << (index)))

unsigned long long readFromMem(unsigned long long memIndex, int bitOffset, unsigned long long size);
void writeToMem(unsigned long long memIndex, int bitOffset, unsigned long long size, unsigned long long value);

unsigned long long readFromMem(unsigned long long memIndex, unsigned long long size);
void writeToMem(unsigned long long memIndex, unsigned long long size, unsigned long long value);

extern char* MEM;

#endif
