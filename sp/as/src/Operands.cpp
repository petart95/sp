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
#include "Log.h"
#include "Error.h"

#include "Expresion.h"
#include "Argument.h"

#define OPERANDS_LENGTH 24

#define TYPE_CONSTANT(type) (contains((type), "CONST"))
#define TYPE_REGISTER(type) (contains((type), "REG"))
#define TYPE_ABSOLUT_EXPRESION(type) (contains((type), "ABSEXP"))
#define TYPE_NOT_USED(type) (contains((type), "NUSED"))

Operation::Operands::Operands(std::vector<std::string> _operands, std::string _type)
    : operands(_operands), type(splitStringWhitCharacterSet(_type, ",")), areValid(true) {
    int typeIndex, operandsIndex;
        
    for(typeIndex = 0, operandsIndex = 0;
        typeIndex < type.size() && operandsIndex < operands.size;
        typeIndex++, operandsIndex++) {
        while(TYPE_CONSTANT(type[typeIndex]) || TYPE_NOT_USED(type[typeIndex])) {
            typeIndex++;
        }
        
        if (TYPE_REGISTER(type[typeIndex]) &&
            (registerHexRepresentation(operands[operandsIndex]) != -1 ||
            !contains(splitStringWhitCharacterSet(type[typeIndex], "+"),
                      toUpper(operands[operandsIndex])))) {
            break;
        }
    }
        
    if(operandsIndex != operands.size() || typeIndex != type.size()) {
        areValid = false;
    }
}

std::string Operation::Operands::createHexRepresentation() {
    if(!areValid) {
        ERROR(BOLD("Internal error: "), "Can not create hex representation for invalid operands");
    }

    long long operandsCode = 0, valueIndex = 0, typeIndex;
    for(typeIndex = 0; typeIndex < type.size(); typeIndex++) {
        int shift = 1, value = 0;
        
        if(TYPE_CONSTANT(type[typeIndex])) {
            value = toIntager(type[typeIndex].substr(type[typeIndex].find("_")));
        } else if(TYPE_NOT_USED(type[typeIndex])) {
            shift = toIntager(type[typeIndex].substr(type[typeIndex].find("_")));
        } else if(TYPE_REGISTER(type[typeIndex])) {
            shift = contains(type[typeIndex], "+") ? 5 : 4;
            value = registerHexRepresentation(value[valueIndex++]);
        } else if(TYPE_ABSOLUT_EXPRESION(type[typeIndex])) {
            shift = toIntager(type[typeIndex].substr(type[typeIndex].find("_"), type[typeIndex].find_last_of("_")));
            Argument exp = expresion(value[valueIndex++]);

            value = exp.value;
            
            // TODO add realocation data
            exp.addRealocatioDataForType(type[typeIndex]);
        }
        
        operandsCode <<= shift;
        operandsCode += value;
    }

    return toHexadecimal(operandsCode, OPERANDS_LENGTH);
}

int Operation::Operands::registerHexRepresentation(std::string operand) {
    if((operand[0] == "R" || operand[0] = "r") && isIntager(operand.substr(1))) {
        int regIndex = toIntager(operand.substr(1));
        
        if(0 > regIndex || regIndex >= 16) {
            return -1;
        }
        
        return regIndex;
    }
    
    std::map<std::string, int> registers =
        createMap<std::string, int>
        ("PC", 16)("LR", 17)("SP", 18)("PSW", 19);
    
    if(!contains(registers, toUpper(operand))) {
        return -1;
    }
    
    return registers[toUpper(operand)];
}
