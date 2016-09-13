#ifndef ARGUMENT_H_
#define ARGUMENT_H_

#include "Simbol.h"

struct Argument {
	long long value;
	long long simbolID;

    bool isRelativ() const;
    
    Argument(Simbol simbol);
	Argument(long long _value) : value(_value), simbolID(-1) {}
	Argument(long long _value, long long _simbolID)
	 : value(_value), simbolID(_simbolID) {}

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

