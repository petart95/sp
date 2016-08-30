#ifndef SECTION_H_
#define SECTION_H_

#include <iostream>
#include <string>
#include <vector>

struct Section {
    static int newID;
    
    static int current;
    static std::vector<Section> tabel;
    
    int id;
    std::string name;
    int locationCounter;
    std::string data;
    std::string realocation;
    
    Section(std::string _name);
    
    friend std::istream & operator >> (std::istream &in, Section &section);
    friend std::ostream & operator << (std::ostream &out, const Section &section);
    
    static bool isNameValid(std::string name);
};

#endif