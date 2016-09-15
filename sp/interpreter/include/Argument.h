#ifndef ARGUMENT_H_
#define ARGUMENT_H_

#include "Simbol.h"

struct Argument {
	long long value;
    std::string simbolName;

    bool isRelativ() const;
    
    Argument(Simbol simbol);
    Argument(long long _value, std::string _simbolName = ABSOLUT)
	 : value(_value), simbolName(_simbolName) {}

	Argument updateForNegation();
	Argument updateForComplementation();

    Argument& operator*=(const Argument& rhs);
    Argument& operator/=(const Argument& rhs);
    Argument& operator%=(const Argument& rhs);
    Argument& operator>>=(const Argument& rhs);
    Argument& operator<<=(const Argument& rhs);

    Argument& operator|=(const Argument& rhs);
    Argument& operator&=(const Argument& rhs);
    Argument& operator^=(const Argument& rhs);

    Argument& operator+=(const Argument& rhs);
    Argument& operator-=(const Argument& rhs);
};

Argument operator*(Argument lhs, const Argument& rhs);
Argument operator/(Argument lhs, const Argument& rhs);
Argument operator%(Argument lhs, const Argument& rhs);
Argument operator>>(Argument lhs, const Argument& rhs);
Argument operator<<(Argument lhs, const Argument& rhs);

Argument operator|(Argument lhs, const Argument& rhs);
Argument operator&(Argument lhs, const Argument& rhs);
Argument operator^(Argument lhs, const Argument& rhs);
Argument operator+(Argument lhs, const Argument& rhs);
Argument operator-(Argument lhs, const Argument& rhs);

Argument operator==(Argument lhs, const Argument& rhs);
Argument operator!=(Argument lhs, const Argument& rhs);
Argument operator>(Argument lhs, const Argument& rhs);
Argument operator<(Argument lhs, const Argument& rhs);
Argument operator>=(Argument lhs, const Argument& rhs);
Argument operator<=(Argument lhs, const Argument& rhs);

Argument operator||(Argument lhs, const Argument& rhs);
Argument operator&&(Argument lhs, const Argument& rhs);

#endif

