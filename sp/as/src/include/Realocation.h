#ifndef REALOCATION_H_
#define REALOCATION_H_

#include <iostream>
#include <string>
#include <vector>

struct Realocation {
    std::string simbolName;
    int bitOffset;
    int size;
    
    Realocation(std::string _simbolName, int _size, int _bitOffset)
        : simbolName(_simbolName), size(_size), bitOffset(_bitOffset) {}
    
    static std::string tabelRows();
    
    friend std::istream & operator >> (std::istream &in, Realocation &realocation);
    friend std::ostream & operator << (std::ostream &out, const Realocation &realocation);
};

#endif
