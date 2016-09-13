#ifndef REALOCATION_H_
#define REALOCATION_H_

#include <iostream>
#include <string>
#include <vector>

struct Realocation {
    int bitOffset;
    int simbolID;
    int size;
    
    Realocation(int _simbolID, int _size, int _bitOffset)
        : simbolID(_simbolID), size(_size), bitOffset(_bitOffset) {}
    
    static std::string tabelRows();
    
    friend std::istream & operator >> (std::istream &in, Realocation &realocation);
    friend std::ostream & operator << (std::ostream &out, const Realocation &realocation);
};

#endif
