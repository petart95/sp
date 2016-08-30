#include "Section.h"

#include "as.h"

int Section::newID = 0;

int Section::current = 0;
std::vector<Section> Section::tabel;

Section::Section(std::string _name) : name(_name), locationCounter(0), id(newID++), data(""), realocation("") {
    tabel.push_back(*this);
    
    current = tabel.size() - 1;
    
    Simbol(_name, 0, current);
}

bool Section::isNameValid(std::string name) {
    int numberOfDots = std::count(name.begin(), name.end(), '.');
    
    if(numberOfDots > 2 || numberOfDots == 0) {
        return false;
    } else if(numberOfDots == 2) {
        name = name.substr(0, name.find_last_of('.'));
    }
    
    if(name.compare(".text") ||
       name.compare(".data") ||
       name.compare(".bss")) {
        return true;
    }
    
    return false;
}

std::istream & operator >> (std::istream &in, Section &section) {
    
}

std::ostream & operator << (std::ostream &out, const Section &section) {
    // Output section
    out << "# " << section.name << "\n";
    out << section.data << "\n";
    out << "\n";
    
    // Output section realocation tabel
    out << "# .ret" << section.name << "\n";
    out << "# ";
    out << std::left << std::setw(9) << std::setfill(' ') << "Offset";
    out << std::left << std::setw(20) << std::setfill(' ') << "Type";
    out << std::left << std::setw(4) << std::setfill(' ') << "Simbol ID";
    out << "\n";
    out << section.realocation;
}