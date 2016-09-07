#include "Argument.h"
#include "Error.h"
#include "Section.h"

#define ERROR_PREFIX "Invalid operation: "

Argument Argument::updateForNegation() {
    simbolID = -1;
    if(isRelativ) {
        ERROR("'", BOLD("-"), "' can't be done on relativ argument");
    }

    value = -value;

    return *this;
}
Argument Argument::updateForComplementation() {
    simbolID = -1;
    if(isRelativ) {
        ERROR("'", BOLD("~"), "' can't be done on relativ argument");
    }

    value = ~value;

    return *this;
}

Argument& Argument::operator*=(const Argument& rhs){
    simbolID = -1;
    if(rhs.isRelativ || isRelativ) {
        ERROR("'", BOLD("*"), "' can't be used between relativ arguments");
    }

    value *= rhs.value;

    return *this;
}
Argument& Argument::operator/=(const Argument& rhs){
    simbolID = -1;
    if(rhs.isRelativ || isRelativ) {
        ERROR("'", BOLD("/"), "' can't be used between relativ arguments");
    }

    value /= rhs.value;

    return *this;
}
Argument& Argument::operator%=(const Argument& rhs){
    simbolID = -1;
    if(rhs.isRelativ || isRelativ) {
        ERROR("'", BOLD("%"), "' can't be used between relativ arguments");
    }

    value %= rhs.value;

    return *this;
}
Argument& Argument::operator>>=(const Argument& rhs){
    simbolID = -1;
    if(rhs.isRelativ || isRelativ) {
        ERROR("'", BOLD(">>"), "' can't be used between relativ arguments");
    }

    value >>= rhs.value;

    return *this;
}
Argument& Argument::operator<<=(const Argument& rhs){
    simbolID = -1;
    if(rhs.isRelativ || isRelativ) {
        ERROR("'", BOLD("<<"), "' can't be used between relativ arguments");
    }

    value <<= rhs.value;

    return *this;
}

Argument& Argument::operator|=(const Argument& rhs){
    simbolID = -1;
    if(rhs.isRelativ || isRelativ) {
        ERROR("'", BOLD("|"), "' can't be used between relativ arguments");
    }

    value |= rhs.value;

    return *this;
}
Argument& Argument::operator&=(const Argument& rhs){
    simbolID = -1;
    if(rhs.isRelativ || isRelativ) {
        ERROR("'", BOLD("&"), "' can't be used between relativ arguments");
    }

    value &= rhs.value;

    return *this;
}
Argument& Argument::operator^=(const Argument& rhs){
    simbolID = -1;
    if(rhs.isRelativ || isRelativ) {
        ERROR("'", BOLD("^"), "' can't be used between relativ arguments");
    }

    value ^= rhs.value;

    return *this;
}

Argument& Argument::operator+=(const Argument& rhs){
    simbolID = -1;
    if(rhs.isRelativ && isRelativ) {
        ERROR("'", BOLD("+"), "' can't be used between relativ arguments");
    } else if(rhs.isRelativ && !isRelativ) {
        isRelativ = true;
        sectionID = rhs.sectionID;
    }

    value += rhs.value;

    return *this;
}
Argument& Argument::operator-=(const Argument& rhs){
    simbolID = -1;
    if((rhs.isRelativ && isRelativ) && sectionID != rhs.sectionID) {
        ERROR("'", BOLD("-"), "' can't be used between relativ arguments,",
              "if not from same section");
    } else if((rhs.isRelativ && isRelativ) && sectionID == rhs.sectionID) {
        isRelativ = false;
        sectionID = -1;
    } else if(rhs.isRelativ && !isRelativ) {
        isRelativ = true;
        sectionID = rhs.sectionID;
    }

    value -= rhs.value;

    return *this;
}

inline Argument operator*(Argument lhs, const Argument& rhs) {
    lhs *= rhs;
    return lhs;
}
inline Argument operator/(Argument lhs, const Argument& rhs) {
    lhs /= rhs;
    return lhs;
}
inline Argument operator%(Argument lhs, const Argument& rhs) {
    lhs %= rhs;
    return lhs;
}
inline Argument operator>>(Argument lhs, const Argument& rhs) {
    lhs >>= rhs;
    return lhs;
}
inline Argument operator<<(Argument lhs, const Argument& rhs) {
    lhs <<= rhs;
    return lhs;
}

inline Argument operator|(Argument lhs, const Argument& rhs) {
    lhs |= rhs;
    return lhs;
}
inline Argument operator&(Argument lhs, const Argument& rhs) {
    lhs &= rhs;
    return lhs;
}
inline Argument operator^(Argument lhs, const Argument& rhs) {
    lhs ^= rhs;
    return lhs;
}
inline Argument operator+(Argument lhs, const Argument& rhs) {
    lhs += rhs;
    return lhs;
}
inline Argument operator-(Argument lhs, const Argument& rhs) {
    lhs -= rhs;
    return lhs;
}

Argument operator==(Argument lhs, const Argument& rhs) {
    lhs.simbolID = -1;
    if(rhs.isRelativ || lhs.isRelativ) {
        ERROR("'", BOLD("=="), "' can't be used between relativ arguments");
    }

    lhs.value = lhs.value == rhs.value;

    return lhs;
}
Argument operator!=(Argument lhs, const Argument& rhs) {
    lhs.simbolID = -1;
    if(rhs.isRelativ || lhs.isRelativ) {
        ERROR("'", BOLD("!="), "' can't be used between relativ arguments");
    }

    lhs.value = lhs.value != rhs.value;

    return lhs;
}
Argument operator>(Argument lhs, const Argument& rhs) {
    lhs.simbolID = -1;
    if(rhs.isRelativ || lhs.isRelativ) {
        ERROR("'", BOLD(">"), "' can't be used between relativ arguments");
    }

    lhs.value = lhs.value > rhs.value;

    return lhs;
}
Argument operator<(Argument lhs, const Argument& rhs) {
    lhs.simbolID = -1;
    if(rhs.isRelativ || lhs.isRelativ) {
        ERROR("'", BOLD("<"), "' can't be used between relativ arguments");
    }

    lhs.value = lhs.value < rhs.value;

    return lhs;
}
Argument operator>=(Argument lhs, const Argument& rhs) {
    lhs.simbolID = -1;
    if(rhs.isRelativ || lhs.isRelativ) {
        ERROR("'", BOLD(">="), "' can't be used between relativ arguments");
    }

    lhs.value = lhs.value >= rhs.value;

    return lhs;
}
Argument operator<=(Argument lhs, const Argument& rhs) {
    lhs.simbolID = -1;
    if(rhs.isRelativ || lhs.isRelativ) {
        ERROR("'", BOLD("<="), "' can't be used between relativ arguments");
    }

    lhs.value = lhs.value <= rhs.value;

    return lhs;
}

Argument operator||(Argument lhs, const Argument& rhs) {
    lhs.simbolID = -1;
    if(rhs.isRelativ || lhs.isRelativ) {
        ERROR("'", BOLD("||"), "' can't be used between relativ arguments");
    }

    lhs.value = lhs.value || rhs.value;

    return lhs;
}
Argument operator&&(Argument lhs, const Argument& rhs) {
    lhs.simbolID = -1;
    if(rhs.isRelativ || lhs.isRelativ) {
        ERROR("'", BOLD("&&"), "' can't be used between relativ arguments");
    }

    lhs.value = lhs.value && rhs.value;

    return lhs;
}

void Argument::addRealocatioDataForType(std::string type) {
    if(simbolID != -1 && !Simbol::tabel[simbolID].isDefined) {
        std::stringstream realocationStream;

        realocationStream << "  ";
        realocationStream << std::left << std::setw(9) << std::setfill(' ')
                          << toHexadecimal(Section::tabel[Section::current].locationCounter, 8);
        realocationStream << std::left << std::setw(20) << std::setfill(' ') << type;
        realocationStream << std::left << std::setw(4) << std::setfill(' ') << simbolID;
        realocationStream << "\n";

        if(Section::tabel[Section::current].realocation.find(realocationStream.str()) == std::string::npos) {
            Section::tabel[Section::current].realocation += realocationStream.str();
        }
    } else if(isRelativ) {
        for(int i = 0; i < Simbol::tabel.size(); i++) {
            if(Section::tabel[Section::current].name.compare(Simbol::tabel[i].name) == 0) {
                simbolID = i;
            }
        }

        std::stringstream realocationStream;

        realocationStream << "  ";
        realocationStream << std::left << std::setw(9) << std::setfill(' ')
                          << toHexadecimal(Section::tabel[Section::current].locationCounter, 8);
        realocationStream << std::left << std::setw(20) << std::setfill(' ') << type;
        realocationStream << std::left << std::setw(4) << std::setfill(' ') << simbolID;
        realocationStream << "\n";

        if(Section::tabel[Section::current].realocation.find(realocationStream.str()) == std::string::npos) {
            Section::tabel[Section::current].realocation += realocationStream.str();
        }
    }
}
