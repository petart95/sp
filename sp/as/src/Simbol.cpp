#include <sstream>

#include "Simbol.h"
#include "Section.h"
#include "Argument.h"
#include "Operation.hpp"
#include "Error.h"

std::vector<Simbol> Simbol::tabel;

Simbol::Simbol(int _offset, std::string _name, std::string _section, bool _isGlobal)
    : name(_name), offset(_offset), section(_section), isGlobal(_isGlobal) {
    int index = withName(name);

    if(index != -1) {
        if(tabel[index].isDefined()) {
            ERROR("Multiple definision of '", BOLD(name), "'");
        } else {
            tabel[index].offset = offset;
            tabel[index].section = section;
        }
    } else if(Operation::Operands::registerIndex(name) != -1) {
        ERROR("'", BOLD(name), "' can't be used as a simbol name (represent a register)");
    } else {
        tabel.push_back(*this);
    }
}

bool Simbol::isDefined() {
    return section != UNDEFINED;
}

bool Simbol::isRelativ() {
    return section != ABSOLUT;
}

void Simbol::createLocal(std::string name) {
    Simbol(Section::offset(), name, Section::tabel[Section::current].name);
}

void Simbol::createExternal(std::string name) {
    if(withName(name) == -1) {
        Simbol(0, name, UNDEFINED, true);
    }
}

void Simbol::update(std::string name, Argument arg) {
    int index = withName(name);
    
    if(index != -1) {
        tabel[index].offset = arg.value;
        tabel[index].section = Simbol::tabel[Simbol::withName(arg.simbolName)].section;
        
        if(tabel[index].section == UNDEFINED) {
            ERROR("Can't use undefined simbol '", BOLD(arg.simbolName),"' when updating simbol value");
        }
    } else {
        Simbol(arg.value, name, Simbol::tabel[Simbol::withName(arg.simbolName)].section);
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

void Simbol::read(std::istream &in) {
    std::string isGlobalString, section, name;
    int id, offset;
    
    in >> id;
    in >> name;
    in >> std::hex >> offset;
    in >> section;
    in >> isGlobalString;
    
    bool isGlobal = isGlobalString == "Local" == 0 ? false : true;

    std::string line;
    getline(in, line);
    
    Simbol(offset, name, section, isGlobal);
}

std::ostream & operator << (std::ostream &out, const Simbol &simbol) {
    out << "  ";
    out << std::left << std::setw(4) << std::setfill(' ') << Simbol::withName(simbol.name);
    out << std::left << std::setw(15) << std::setfill(' ') << simbol.name;
    out << std::left << std::setw(11) << std::setfill(' ') << toHexadecimal(simbol.offset, 8);
    out << std::left << std::setw(15) << std::setfill(' ') << simbol.section;
    out << std::left << std::setw(13) << std::setfill(' ') << (simbol.isGlobal ? "Global" : "Local");
    out << "\n";
    
    return out;
}

std::string Simbol::tabelRows() {
    std::stringstream stream;
    
    stream << "# Tabela simbola" << "\n" << "# ";
    stream << std::left << std::setw(4) << std::setfill(' ') << "ID";
    stream << std::left << std::setw(15) << std::setfill(' ') << "Name";
    stream << std::left << std::setw(11) << std::setfill(' ') << "Offset";
    stream << std::left << std::setw(15) << std::setfill(' ') << "Section";
    stream << std::left << std::setw(13) << std::setfill(' ') << "Global/Local";
    stream << "\n";
    
    return stream.str();
}
