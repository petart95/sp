#include <algorithm>

#include "Section.h"
#include "Simbol.h"

int Section::newID = 0;

int Section::current = 0;
std::vector<Section> Section::tabel;

Section::Section(std::string _name) : name(_name), locationCounter(0), id(newID++), data("") {
    tabel.push_back(*this);

    current = tabel.size() - 1;

    Simbol(std::string(name), 0, current);
}

bool Section::isNameValid(std::string name) {
    int numberOfDots = std::count(name.begin(), name.end(), '.');
    
    if(numberOfDots > 2 || numberOfDots == 0) {
        return false;
    } else if(numberOfDots == 2) {
        name = name.substr(0, name.find_last_of('.'));
    }

    if(name.compare(".text") == 0 ||
       name.compare(".data") == 0 ||
       name.compare(".bss") == 0) {
        return true;
    }
    
    return false;
}

int Section::withName(std::string name) {
    int tabelSize = tabel.size();

    for(int i = 0; i < tabelSize; i++) {
        if(name.compare(tabel[i].name) == 0) {
            return i;
        }
    }

    return -1;
}

void Section::prepareForSecondPass() {
    int tabelSize = tabel.size();

    for(int i = 0; i < tabelSize; i++) {
        tabel[i].locationCounter = 0;
    }

    current = 0;
}

void Section::move(int count) {
    tabel[current].locationCounter += count;
}

void Section::fill(std::string data) {
    tabel[current].data += data;

    Section::move(data.length() / 2);
}

int Section::offset() {
    return tabel[current].locationCounter;
}

void Section::addRealocationOfSizeAtOffset(Argument arg, int size, int _offset) {
    if(arg.isRelativ()) {
        tabel[current].realocationTabel.push_back(Realocation(arg.simbolID, size, 8*offset() + _offset));
    }
}

std::istream & operator >> (std::istream &in, Section &section) {
    // TODO
    return in;
}

std::ostream & operator << (std::ostream &out, const Section &section) {
    // Output section
    out << "# " << section.name << "\n";
    out << insertCharEveryNthCharacterOfString(' ', 2, section.data) << "\n" << "\n";
    
    // Output section realocation tabel
    out << "# .ret" << section.name << "\n";
    out << Realocation::tabelRows();
    for(int i = 0; i < section.realocationTabel.size(); i++) {
        out << section.realocationTabel[i];
    }
    
    return out;
}
