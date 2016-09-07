#include <sstream>

#include "Simbol.h"

#include "Error.h"

int Simbol::newID = 0;

std::vector<Simbol> Simbol::tabel;

Simbol::Simbol(std::string _name,
               int _offset,
               int _sectionIndex,
               bool _isDefined,
               bool _isGlobal,
               bool update) 
    : name(_name),
      offset(_offset),
      sectionIndex(_sectionIndex),
      isGlobal(_isGlobal),
      isDefined(_isDefined),
      id(newID++) {
    int index = withName(name);

    if(index != -1) {
        if(tabel[index].isDefined && !update) {
            ERROR("Multiple definision of '", BOLD(name), "'");
        } else {
            tabel[index].offset = offset;
            tabel[index].sectionIndex = sectionIndex;
            tabel[index].isDefined = isDefined;
        }
    } else {
        tabel.push_back(*this);
    }
}

int Simbol::withName(std::string name) {
    int tabelSize = tabel.size();

    for(int i = 0; i < tabelSize; i++) {
        if(name.compare(tabel[i].name) == 0) {
            return i;
        }
    }

    return -1;
}

std::istream & operator >> (std::istream &in, Simbol &simbol) {
    // TODO
    return in;
}

std::ostream & operator << (std::ostream &out, const Simbol &simbol) {
    out << "  ";
    out << std::left << std::setw(4) << std::setfill(' ') << simbol.id;
    out << std::left << std::setw(15) << std::setfill(' ') << simbol.name;
    out << std::left << std::setw(9) << std::setfill(' ') << toHexadecimal(simbol.offset, 8);
    out << std::left << std::setw(11) << std::setfill(' ') << simbol.sectionIndex;
    out << std::left << std::setw(13) << std::setfill(' ') << (simbol.isGlobal ? "Global" : "Local");
    out << std::left << std::setw(18) << std::setfill(' ') << (simbol.isDefined ? "Defined" : "Undefnded");
    out << "\n";
    
    return out;
}

std::string Simbol::tabelRows() {
    std::stringstream stream;
    
    stream << "# Tabela simbola" << "\n" << "# ";
    stream << std::left << std::setw(4) << std::setfill(' ') << "ID";
    stream << std::left << std::setw(15) << std::setfill(' ') << "Name";
    stream << std::left << std::setw(9) << std::setfill(' ') << "Offset";
    stream << std::left << std::setw(11) << std::setfill(' ') << "Section ID";
    stream << std::left << std::setw(13) << std::setfill(' ') << "Global/Local";
    stream << std::left << std::setw(18) << std::setfill(' ') << "Defined/Undefnded";
    stream << "\n";
    
    return stream.str();
}
