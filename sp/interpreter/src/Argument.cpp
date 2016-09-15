#include "Argument.h"
#include "Error.h"
#include "Section.h"

#define ERROR_PREFIX "Invalid operation: "

Argument::Argument(Simbol simbol) : value(simbol.offset), simbolName(simbol.name) {
    if(simbol.isDefined()){
        simbolName = simbol.section;
    }
}

bool Argument::isRelativ() const {
    return simbolName != ABSOLUT;
}

Argument Argument::updateForNegation() {
    if(isRelativ()) {
        ERROR("'", BOLD("-"), "' can't be done on relativ argument");
    }

    value = -value;

    return *this;
}
Argument Argument::updateForComplementation() {
    if(isRelativ()) {
        ERROR("'", BOLD("~"), "' can't be done on relativ argument");
    }

    value = ~value;

    return *this;
}

Argument& Argument::operator*=(const Argument& rhs){
    if(rhs.isRelativ() || isRelativ()) {
        ERROR("'", BOLD("*"), "' can't be used between relativ arguments");
    }

    value *= rhs.value;

    return *this;
}
Argument& Argument::operator/=(const Argument& rhs){
    if(rhs.isRelativ() || isRelativ()) {
        ERROR("'", BOLD("/"), "' can't be used between relativ arguments");
    }

    value /= rhs.value;

    return *this;
}
Argument& Argument::operator%=(const Argument& rhs){
    if(rhs.isRelativ() || isRelativ()) {
        ERROR("'", BOLD("%"), "' can't be used between relativ arguments");
    }

    value %= rhs.value;

    return *this;
}
Argument& Argument::operator>>=(const Argument& rhs){
    if(rhs.isRelativ() || isRelativ()) {
        ERROR("'", BOLD(">>"), "' can't be used between relativ arguments");
    }

    value >>= rhs.value;

    return *this;
}
Argument& Argument::operator<<=(const Argument& rhs){
    if(rhs.isRelativ() || isRelativ()) {
        ERROR("'", BOLD("<<"), "' can't be used between relativ arguments");
    }

    value <<= rhs.value;

    return *this;
}

Argument& Argument::operator|=(const Argument& rhs){
    if(rhs.isRelativ() || isRelativ()) {
        ERROR("'", BOLD("|"), "' can't be used between relativ arguments");
    }

    value |= rhs.value;

    return *this;
}
Argument& Argument::operator&=(const Argument& rhs){
    if(rhs.isRelativ() || isRelativ()) {
        ERROR("'", BOLD("&"), "' can't be used between relativ arguments");
    }

    value &= rhs.value;

    return *this;
}
Argument& Argument::operator^=(const Argument& rhs){
    if(rhs.isRelativ() || isRelativ()) {
        ERROR("'", BOLD("^"), "' can't be used between relativ arguments");
    }

    value ^= rhs.value;

    return *this;
}

Argument& Argument::operator+=(const Argument& rhs){
    if(rhs.isRelativ() && isRelativ()) {
        ERROR("'", BOLD("+"), "' can't be used between relativ arguments");
    } else if(rhs.isRelativ()) {
        simbolName = rhs.simbolName;
    }
    
    value += rhs.value;

    return *this;
}
Argument& Argument::operator-=(const Argument& rhs){
    if(rhs.isRelativ() && isRelativ()) {
        if(simbolName != rhs.simbolName) {
            ERROR("'", BOLD("-"), "' can't be used between relativ arguments,",
                  "if not from same section");
        } else {
            simbolName = ABSOLUT;
        }
    } else if(rhs.isRelativ()) {
        simbolName = rhs.simbolName;
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
    if(rhs.isRelativ() || lhs.isRelativ()) {
        ERROR("'", BOLD("=="), "' can't be used between relativ arguments");
    }

    lhs.value = lhs.value == rhs.value;

    return lhs;
}
Argument operator!=(Argument lhs, const Argument& rhs) {
    if(rhs.isRelativ() || lhs.isRelativ()) {
        ERROR("'", BOLD("!="), "' can't be used between relativ arguments");
    }

    lhs.value = lhs.value != rhs.value;

    return lhs;
}
Argument operator>(Argument lhs, const Argument& rhs) {
    if(rhs.isRelativ() || lhs.isRelativ()) {
        ERROR("'", BOLD(">"), "' can't be used between relativ arguments");
    }

    lhs.value = lhs.value > rhs.value;

    return lhs;
}
Argument operator<(Argument lhs, const Argument& rhs) {
    if(rhs.isRelativ() || lhs.isRelativ()) {
        ERROR("'", BOLD("<"), "' can't be used between relativ arguments");
    }

    lhs.value = lhs.value < rhs.value;

    return lhs;
}
Argument operator>=(Argument lhs, const Argument& rhs) {
    if(rhs.isRelativ() || lhs.isRelativ()) {
        ERROR("'", BOLD(">="), "' can't be used between relativ arguments");
    }

    lhs.value = lhs.value >= rhs.value;

    return lhs;
}
Argument operator<=(Argument lhs, const Argument& rhs) {
    if(rhs.isRelativ() || lhs.isRelativ()) {
        ERROR("'", BOLD("<="), "' can't be used between relativ arguments");
    }

    lhs.value = lhs.value <= rhs.value;

    return lhs;
}

Argument operator||(Argument lhs, const Argument& rhs) {
    if(rhs.isRelativ() || lhs.isRelativ()) {
        ERROR("'", BOLD("||"), "' can't be used between relativ arguments");
    }

    lhs.value = lhs.value || rhs.value;

    return lhs;
}
Argument operator&&(Argument lhs, const Argument& rhs) {
    if(rhs.isRelativ() || lhs.isRelativ()) {
        ERROR("'", BOLD("&&"), "' can't be used between relativ arguments");
    }

    lhs.value = lhs.value && rhs.value;

    return lhs;
}
