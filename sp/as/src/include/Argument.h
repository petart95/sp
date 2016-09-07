#ifndef ARGUMENT_H_
#define ARGUMENT_H_

#include "Simbol.h"

struct Argument {
	long long value;
	long long sectionID;
	long long simbolID;
	bool isRelativ;

	Argument(long long _value) : value(_value), sectionID(-1), isRelativ(false), simbolID(-1) {}
	Argument(Simbol simbol) : value(simbol.offset), sectionID(simbol.sectionIndex), isRelativ(true), simbolID(simbol.id) {}
	Argument(long long _value, long long _sectionID, bool _isRelativ, long long _simbolID)
	 : value(_value), sectionID(_sectionID), isRelativ(_isRelativ), simbolID(_simbolID) {}

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

	void addRealocatioDataForType(std::string type);
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

