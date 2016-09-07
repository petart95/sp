#ifndef SIMBOL_H_
#define SIMBOL_H_

#include <iostream>
#include <string>
#include <vector>

struct Simbol {
    static int newID;
    
    static std::vector<Simbol> tabel;
    
    int id;
    int offset;
    int sectionIndex;
    std::string name;
    bool isGlobal;
    bool isDefined;

    Simbol(std::string _name, int _offset, int _sectionIndex, bool _isDefined = true, bool _isGlobal = false, bool update = false);
    
    static std::string tabelRows();
    static int withName(std::string name);

    friend std::istream & operator >> (std::istream &in, Simbol &simbol);
    friend std::ostream & operator << (std::ostream &out, const Simbol &simbol);
};

#endif /* SIMBOL_H_ */

