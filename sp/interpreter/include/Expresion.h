#ifndef EXPRESION_H_
#define EXPRESION_H_

#include <string>
#include <string.h>
#include <cctype>

#include "as.h"
#include "Simbol.h"

struct Value {
	long long value;
	long long sectionID;
	long long simbolID;
	bool isRelativ;

	Value(long long _value) : value(_value), sectionID(-1), isRelativ(false), simbolID(-1) {}
	Value(Simbol simbol) : value(simbol.offset), sectionID(simbol.sectionIndex), isRelativ(true), simbolID(simbol.id) {}
	Value(long long _value, long long _sectionID, bool _isRelativ, long long _simbolID)
	 : value(_value), sectionID(_sectionID), isRelativ(_isRelativ), simbolID(_simbolID) {}

	void updateForNegation();
	void updateForComplementation();

	void updateForMultiplication(Value value);
	void updateForDivision(Value value);
	void updateForRemainder(Value value);
	void updateForShiftLeft(Value value);
	void updateForShiftRight(Value value);

	void updateForBitwiseInclusiveOr(Value value);
	void updateForBitwiseAnd(Value value);
	void updateForBitwiseExclusiveOr(Value value);
	//void updateForBitwiseOrNot(Value value);

	void updateForAdditionWith(Value value);
	void updateForSubstactionWith(Value value);
	void updateForIsEqualTo(Value value);
	void updateForIsNotEqualTo(Value value);
	void updateForIsLessThan(Value value);
	void updateForIsGreaterThan(Value value);
	void updateForIsGreaterThanOrEqualTo(Value value);
	void updateForIsLessThanOrEqualTo(Value value);

	void updateForLogicalAnd(Value value);
	void updateForLogicalOr(Value value);

	void error();

	void addRealocatioDataForType(std::string type);
};

struct Expresion {
	std::string expresion;

	Expresion(std::string _expresion) : expresion(_expresion) {}

	Value evaluate();  
};

#endif /* PROCESS_STRING_H_ */
