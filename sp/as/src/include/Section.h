#ifndef SECTION_H_
#define SECTION_H_

#include <iostream>
#include <string>
#include <vector>

#include "Log.h"
#include "Argument.h"
#include "Realocation.h"

struct Section {
    static int newID;
    
    static int current;
    static std::vector<Section> tabel;
    
    int id;
    int locationCounter;
    std::string name;
    std::string data;
    std::vector<Realocation> realocationTabel;
    
    Section(std::string name);
    
    static bool isNameValid(std::string name);
    static int withName(std::string name);
    static void prepareForSecondPass();

    static void move(int count);
    static void fill(std::string data);
    static int offset();
    static void addRealocationOfSizeAtOffset(Argument arg, int size, int offset = 0);

    friend std::istream & operator >> (std::istream &in, Section &section);
    friend std::ostream & operator << (std::ostream &out, const Section &section);
};

#endif

