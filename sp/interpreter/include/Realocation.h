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
    
    Realocation(std::string line);
    
    static std::string tabelRows();
    
    friend std::ostream & operator << (std::ostream &out, const Realocation &realocation);
};

#endif
