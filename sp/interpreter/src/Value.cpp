#include "Expresion.h"

#include "Log.h"

void Value::updateForNegation() {
	simbolID = -1;
	if(isRelativ) {
		error();
		return;
	}

	value = -value;
}
void Value::updateForComplementation() {
	simbolID = -1;
	if(isRelativ) {
		error();
		return;
	}

	value = ~value;
}

void Value::updateForMultiplication(Value _value) {
	simbolID = -1;
	if(_value.isRelativ || isRelativ) {
		error();
		return;
	}

	value = value * _value.value;
}
void Value::updateForDivision(Value _value) {
	simbolID = -1;
	if(_value.isRelativ || isRelativ) {
		error();
		return;
	}

	value = value / _value.value;
}
void Value::updateForRemainder(Value _value) {
	simbolID = -1;
	if(_value.isRelativ || isRelativ) {
		error();
		return;
	}

	value = value % _value.value;
}
void Value::updateForShiftLeft(Value _value) {
	simbolID = -1;
	if(_value.isRelativ || isRelativ) {
		error();
		return;
	}

	value = value << _value.value;
}
void Value::updateForShiftRight(Value _value) {
	simbolID = -1;
	if(_value.isRelativ || isRelativ) {
		error();
		return;
	}

	value = value >> _value.value;
}

void Value::updateForBitwiseInclusiveOr(Value _value) {
	simbolID = -1;
	if(_value.isRelativ || isRelativ) {
		error();
		return;
	}

	value = value | _value.value;
}
void Value::updateForBitwiseAnd(Value _value) {
	simbolID = -1;
	if(_value.isRelativ || isRelativ) {
		error();
		return;
	}

	value = value & _value.value;
}
void Value::updateForBitwiseExclusiveOr(Value _value) {
	simbolID = -1;
	if(_value.isRelativ || isRelativ) {
		error();
		return;
	}

	value = value ^ _value.value;
}
/*void Value::updateForBitwiseOrNot(Value _value) {
	simbolID = -1;

}*/

void Value::updateForAdditionWith(Value _value) {
	simbolID = -1;
	if(_value.isRelativ && isRelativ) {
		error();
		return;
	} else if(_value.isRelativ && !isRelativ) {
		isRelativ = true;
		sectionID = _value.sectionID;
	}

	value = value + _value.value;
}
void Value::updateForSubstactionWith(Value _value) {
	simbolID = -1;
	if((_value.isRelativ && isRelativ) && sectionID != _value.sectionID) {
		error();
		return;
	} else if((_value.isRelativ && isRelativ) && sectionID == _value.sectionID) {
		isRelativ = false;
		sectionID = -1;
	} else if(_value.isRelativ && !isRelativ) {
		isRelativ = true;
		sectionID = _value.sectionID;
	}

	value = value - _value.value;
}
void Value::updateForIsEqualTo(Value _value) {
	simbolID = -1;
	if(_value.isRelativ || isRelativ) {
		error();
		return;
	}

	value = value == _value.value;
}
void Value::updateForIsNotEqualTo(Value _value) {
	simbolID = -1;
	if(_value.isRelativ || isRelativ) {
		error();
		return;
	}

	value = value != _value.value;
}
void Value::updateForIsLessThan(Value _value) {
	simbolID = -1;
	if(_value.isRelativ || isRelativ) {
		error();
		return;
	}

	value = value < _value.value;
}
void Value::updateForIsGreaterThan(Value _value) {
	simbolID = -1;
	if(_value.isRelativ || isRelativ) {
		error();
		return;
	}

	value = value > _value.value;
}
void Value::updateForIsGreaterThanOrEqualTo(Value _value) {
	simbolID = -1;
	if(_value.isRelativ || isRelativ) {
		error();
		return;
	}

	value = value >= _value.value;
}
void Value::updateForIsLessThanOrEqualTo(Value _value) {
	simbolID = -1;
	if(_value.isRelativ || isRelativ) {
		error();
		return;
	}

	value = value <= _value.value;
}

void Value::updateForLogicalAnd(Value _value) {
	simbolID = -1;
	if(_value.isRelativ || isRelativ) {
		error();
		return;
	}

	value = value && _value.value;
}
void Value::updateForLogicalOr(Value _value) {
	simbolID = -1;
	if(_value.isRelativ || isRelativ) {
		error();
		return;
	}

	value = value || _value.value;
}

void Value::error() {
	log("***ERROR*** Equasion is incorect!\n");
}

void Value::addRealocatioDataForType(std::string type) {
	if(simbolID != -1 && !simbolTabel[simbolID].isDefined) {
		std::stringstream realocationStream;

		realocationStream << "  ";
		realocationStream << std::left << std::setw(9) << std::setfill(' ')
				  << toHexadecimal(sectionTabel[currentSectionIndex].locationCounter, 8);
		realocationStream << std::left << std::setw(20) << std::setfill(' ') << type;
		realocationStream << std::left << std::setw(4) << std::setfill(' ') << simbolID;
		realocationStream << "\n";

		if(sectionTabel[currentSectionIndex].realocation.find(realocationStream.str()) == std::string::npos) {
			sectionTabel[currentSectionIndex].realocation += realocationStream.str();
		}
	} else if(isRelativ) {
		for(int i = 0; i < simbolTabel.size(); i++) {
			if(sectionTabel[sectionID].name.compare(simbolTabel[i].name) == 0) {
				simbolID = i;
			}
		}

		std::stringstream realocationStream;

		realocationStream << "  ";
		realocationStream << std::left << std::setw(9) << std::setfill(' ')
				  << toHexadecimal(sectionTabel[currentSectionIndex].locationCounter, 8);
		realocationStream << std::left << std::setw(20) << std::setfill(' ') << type;
		realocationStream << std::left << std::setw(4) << std::setfill(' ') << simbolID;
		realocationStream << "\n";

		if(sectionTabel[currentSectionIndex].realocation.find(realocationStream.str()) == std::string::npos) {
			sectionTabel[currentSectionIndex].realocation += realocationStream.str();
		}
	}
}
