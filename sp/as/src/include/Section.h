#ifndef SECTION_H_
#define SECTION_H_

#include <iostream>
#include <string>
#include <vector>

#include "Log.h"
#include "Argument.h"
#include "Realocation.h"

struct Section {
    static int current;
    static std::vector<Section> tabel;
    
    int locationCounter;
    std::string name;
    std::string data;
    std::vector<Realocation> realocationTabel;
    
    Section(std::string name);
    Section(std::string _name, std::string _data, std::vector<Realocation> _realocationTabel)
    : name(_name), data(_data), realocationTabel(_realocationTabel) {}
    
    static bool isNameValid(std::string name);
    static int withName(std::string name);
    static void prepareForSecondPass();
    
    static void move(int count);
    static void fill(std::string data);
    static int offset();
    static void addRealocationOfSizeAtOffset(Argument arg, int size, int offset = 0);
    
    static void read(std::istream &in);
    friend std::ostream & operator << (std::ostream &out, const Section &section);
};

#endif

