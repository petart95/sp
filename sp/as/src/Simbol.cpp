#include <sstream>

#include "Simbol.h"

#include "as.h"

int Simbol::newID = 0;

std::vector<Simbol> Simbol::tabel;

Simbol::Simbol(std::string _name, int _offset, int _sectionIndex, bool _isDefined, bool _isGlobal) 
: name(_name), offset(_offset), sectionIndex(_sectionIndex), isGlobal(_isGlobal), isDefined(_isDefined), id(newID++) {
	tabel.push_back(*this);
}

std::istream & operator >> (std::istream &in, Simbol &simbol) {}
std::ostream & operator << (std::ostream &out, const Simbol &simbol) {
    out << "  ";
    out << std::left << std::setw(4) << std::setfill(' ') << simbol.id;
    out << std::left << std::setw(15) << std::setfill(' ') << simbol.name;
    out << std::left << std::setw(9) << std::setfill(' ') << toHexadecimal(simbol.offset, 8);
    out << std::left << std::setw(11) << std::setfill(' ') << simbol.sectionIndex;
    out << std::left << std::setw(13) << std::setfill(' ') << (simbol.isGlobal ? "Global" : "Local");
    out << std::left << std::setw(18) << std::setfill(' ') << (simbol.isDefined ? "Defined" : "Undefnded");
    out << "\n";
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