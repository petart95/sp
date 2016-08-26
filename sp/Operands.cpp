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
        log("parsing " + value[index] + " of type " + types[i]);
        Operand operand = parseOperandWithType(value[index], types[i]);
        if(operand.value !=-1) {
            return operand;
        }
    }
    
    return Operand(-1,-1, type[index]);
}

std::string Operation::Operands::createHexRepresentation() {
    if(!areValid) {
        return "ERROR";
    }
    
    int shift = 24;
    for(int i = value.size() - 1; i >= 0 ;i--) {
        shift -= getOperandAtIndex(i).size;
    }
    
    int operandsCode = 0;
    for(int i = value.size() - 1; i >= 0 ;i--) {
        operandsCode += getOperandAtIndex(i).value << shift;
        shift += getOperandAtIndex(i).size;
    }
    
    return toHexadecimal(operandsCode);
}

// TODO
//std::map<std::string, parseOperandWithTypeFunctionPointer> Operation::Operands::parseOperanWithType;

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

int parsOperandAsLabel(std::string value) {
    int _value = -2;
    for(int i = 0; i < simbolTabel.size(); i++) {
        if(simbolTabel[i].name.compare(value) == 0) {
            _value = simbolTabel[i].offset;
        }
    }
    
    if(_value == -2) {
        //TODO
        // Should add r to .realoc
        log("Label " + value + " dosn't exsist\n");
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
            std::map<std::string, int> registers =
                createMap<std::string, int>("PC", 16)("LR", 17)("SP", 18)("PSW", 19);
            for(int i = 0; i < supportedRegisters.size(); i++) {
                if(supportedRegisters[i].compare(toUpper(value)) == 0) {
                    _value = registers[value];
                }
            }
        }
    } else {
        if(isIntager(value)) {
            _value = toIntager(value);
            
            if((_value > ((2 << (_size - 1)) - 1)) ||
               (_value < -(2 << (_size - 1)))) {
                _value = -1;
            }
        } else {
            _value = parsOperandAsLabel(value);
        }
        
    }
    
    return Operand(_size, _value, type);
}

