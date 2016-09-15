#include "Realocation.h"
#include "ProcessString.h"

Realocation::Realocation(std::string line) {
    std::string type, bitOffsetString;
    std::istringstream stm(line);
    
    stm >> bitOffsetString;
    stm >> type;
    stm >> simbolName;
    
    size = toIntager(type.substr(type.find_last_of("_") + 1));
    bitOffset = toIntager("0x" + bitOffsetString);
}

std::ostream & operator << (std::ostream &out, const Realocation &realocation) {
    std::string type = "R_386_" + toString(realocation.size);
    
    out << "  ";
    out << std::left << std::setw(12) << std::setfill(' ') << toHexadecimal(realocation.bitOffset, 8);
    out << std::left << std::setw(10) << std::setfill(' ') << type;
    out << std::left << std::setw(4) << std::setfill(' ') << realocation.simbolName;
    out << "\n";
    
    return out;
}

std::string Realocation::tabelRows() {
    std::stringstream stream;
    
    stream << "# ";
    stream << std::left << std::setw(12) << std::setfill(' ') << "Bit Offset";
    stream << std::left << std::setw(10) << std::setfill(' ') << "Type";
    stream << std::left << std::setw(4) << std::setfill(' ') << "Simbol";
    stream << "\n";
    
    return stream.str();
}
