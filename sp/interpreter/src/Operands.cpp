//
//  Operands.cpp
//  sp
//
//  Created by maxeler on 8/25/16.
//  Copyright © 2016 ptrifunovic. All rights reserved.
//

#include "Operation.hpp"
#include "CreateMap.hpp"
#include "ProcessString.h"
#include "as.h"
#include "Log.h"

#include "Expresion.h"

Operation::Operands::Operands(std::vector<std::string> _value, std::string _type)
    : value(_value), type(splitStringWhitCharacterSet(_type, ",")), areValid(true) {
    if(value.size() != type.size()) {
        areValid = false;
        return;
    }
        
    for(int i = 0; i < value.size(); i++) {
        if(getOperandAtIndex(i).value == -1) {
            areValid = false;
            return;
        }
    }
}

Operand Operation::Operands::getOperandAtIndex(int index) {
    std::vector<std::string> types = splitStringWhitCharacterSet(type[index], "|");
    
    for(int i = 0; i < types.size(); i++) {
        Operand operand = parseOperandWithType(value[index], types[i]);
        if(operand.value !=-1) {
            return operand;
        }
    }
    
    return Operand(-1,-1, type[index]);
}

long long Operation::Operands::createHexRepresentation() {
    if(!areValid) {
        return -1;
    }

    long long operandsCode = 0, shift = 0;
    for(int i = 0; i < value.size(); i++) {
        Operand operand = getOperandAtIndex(i);

        operandsCode <<= operand.size;
        operandsCode += operand.value;
    }

    return operandsCode;
}

int parsOperandAsRegister(std::string value){
    int _value;
    
    if(value[0] == 'r' || value[0] == 'R') {
        value = value.substr(1);
        
        if(!isIntager(value)) {
            _value = -1;
        } else {
            _value = toIntager(value);
            
            if(_value < 0 || _value > 15) {
                _value = -1;
            }
        }
    } else {
        _value = -1;
    }
    
    return _value;
}

Operand Operation::Operands::parseOperandWithType(std::string value, std::string type) {
    std::string tmp = type.substr(std::string("R_386_").length());
    
    int _size = toIntager(tmp.substr(tmp.find_first_of("0123456789"),
                                     tmp.find_last_of("0123456789") - tmp.find_first_of("0123456789") + 1));
    
    int _value;
    
    if(_size == 4) {
        _value = parsOperandAsRegister(value);
        if(_value == -1) {
            tmp = tmp.substr(tmp.find("+"));
            std::vector<std::string> supportedRegisters = splitStringWhitCharacterSet(tmp, "+");
            std::map<std::string, long long> registers =
                createMap<std::string, long long>("PC", 16)("LR", 17)("SP", 18)("PSW", 19);
            for(int i = 0; i < supportedRegisters.size(); i++) {
                if(supportedRegisters[i].compare(toUpper(value)) == 0) {
                    _value = registers[toUpper(value)];
                }
            }
        }
        if(tmp.find("+") != std::string::npos) {
            _size++;
        }
    } else {
	Expresion expresion(value);

	Value expresionEvaluated = expresion.evaluate();
	
	expresionEvaluated.addRealocatioDataForType(type);

	_value  = expresionEvaluated.value;
    }
    
    return Operand(_size, _value, type);
}

