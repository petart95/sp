#ifndef SIMBOL_H_
#define SIMBOL_H_

#include <iostream>
#include <string>
#include <vector>

#define UNDEFINED "UNDEFINED"
#define ABSOLUT "ABSOLUT"

struct Argument;

struct Simbol {
    static std::vector<Simbol> tabel;
    
    int offset;
    bool isGlobal;
    std::string name;
    std::string section;

    Simbol(int _offset, std::string _name, std::string _section, bool _isGlobal = false);
    
    bool isDefined();
    bool isRelativ();
    
    static int withName(std::string name);
    
    static void createLocal(std::string name);
    static void createExternal(std::string name);
    static void update(std::string name, Argument arg);
    
    static void read(std::istream &in);
    static void read(std::string line);
    static std::string tabelRows();
    friend std::ostream & operator << (std::ostream &out, const Simbol &simbol);
};

#endif /* SIMBOL_H_ */

