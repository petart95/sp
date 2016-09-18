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
#include "Section.h"
#include "Memory.h"

#define OPERANDS_LENGTH 6

#define TYPE_CONSTANT(type) (contains((type), "CONST"))
#define TYPE_REGISTER(type) (contains((type), "REG"))
#define TYPE_ABSOLUT_EXPRESION(type) (contains((type), "ABSEXP"))
#define TYPE_NOT_USED(type) (contains((type), "NUSED"))

Operation::Operands::Operands(std::vector<std::string> _operands, std::string _type)
    : operands(_operands), type(splitStringWhitCharacterSet(_type, ",")) {
    int typeIndex = 0, operandsIndex = 0;
    for(; typeIndex < type.size() && operandsIndex < operands.size(); typeIndex++, operandsIndex++) {
        while(typeIndex < type.size() && (TYPE_CONSTANT(type[typeIndex]) || TYPE_NOT_USED(type[typeIndex]))) {
            typeIndex++;
        }
        
        if (typeIndex < type.size() && TYPE_REGISTER(type[typeIndex]) &&
            registerIndex(operands[operandsIndex], type[typeIndex]) == -1) {
            break;
        }
    }
    
    while(typeIndex < type.size() && (TYPE_CONSTANT(type[typeIndex]) || TYPE_NOT_USED(type[typeIndex]))) {
        typeIndex++;
    }
        
    areValid = operandsIndex == operands.size() && typeIndex == type.size();     
}

Operation::Operands::Operands(int memPos, std::string _type)
 : type(splitStringWhitCharacterSet(_type, ",")) {
    int typeIndex = 0, offset = 0;
    for(; typeIndex < type.size(); typeIndex++) {
        if(TYPE_CONSTANT(type[typeIndex])) {
            int value = readFromMem(8*memPos + offset, 1);
            int con = toIntager(type[typeIndex].substr(type[typeIndex].find("_") + 1));
            if(value != con) {
                //break;
            }

            offset += 1;

            val.push_back(value);
        } else if(TYPE_NOT_USED(type[typeIndex])) {
            int shift = toIntager(type[typeIndex].substr(type[typeIndex].find("_") + 1));
            int value = readFromMem(8*memPos + offset, shift);

            if(value != 0) {
                break;
            }

            offset += shift;
        } else if(TYPE_REGISTER(type[typeIndex])) {
            int shift = contains(type[typeIndex], "+") ? 5 : 4;
            unsigned int value = readFromMem(8*memPos + offset, shift);

            if(value > 19) {
                break;
            }

            val.push_back(value);

            offset += shift;
        } else if(TYPE_ABSOLUT_EXPRESION(type[typeIndex])) {
            std::string size = type[typeIndex].substr(type[typeIndex].find("_") + 1);
            size = size.substr(0, size.find("_"));
            
            int shift = toIntager(size);

            unsigned int value = readFromMem(8*memPos + offset, shift);

            val.push_back(value);

            offset += shift;
        }
    }
        
    areValid = typeIndex == type.size(); 
}

std::string Operation::Operands::createHexRepresentation() {
    if(!areValid) {
        ERROR(BOLD("Internal error: "),
              "Can't create hex representation for invalid operands");
    }

    long long operandsCode = 0, offset = 8;
    
    for(int typeIndex = 0, operandsIndex = 0; typeIndex < type.size(); typeIndex++) {
        int shift = 1, value = 0;
        
        if(TYPE_CONSTANT(type[typeIndex])) {
            value = toIntager(type[typeIndex].substr(type[typeIndex].find("_")));
        } else if(TYPE_NOT_USED(type[typeIndex])) {
            shift = toIntager(type[typeIndex].substr(type[typeIndex].find("_")));
        } else if(TYPE_REGISTER(type[typeIndex])) {
            shift = contains(type[typeIndex], "+") ? 5 : 4;
            value = registerIndex(operands[operandsIndex++]);
        } else if(TYPE_ABSOLUT_EXPRESION(type[typeIndex])) {
            std::string size = type[typeIndex].substr(type[typeIndex].find("_") + 1);
            size = size.substr(0, size.find("_"));
            
            shift = toIntager(size);
            Argument exp = expresion(operands[operandsIndex++]);

            // TODO SIGNEXT

            value = exp.value;
            
            LOG("creating hex rep ", type[typeIndex], " ", size, " ", shift, " ", offset);
            
            Section::addRealocationOfSizeAtOffset(exp, shift, offset);
        }
        
        operandsCode <<= shift;
        operandsCode += value;
        offset += shift;
    }

    return toHexadecimal(operandsCode, OPERANDS_LENGTH);
}

int Operation::Operands::registerIndex(std::string reg, std::string supportedRegisters) {
    if((reg[0] == 'R' || reg[0] == 'r') && isIntager(reg.substr(1))) {
        int regIndex = toIntager(reg.substr(1));
        
        if(0 > regIndex || regIndex >= 16) {
            return -1;
        }
        
        return regIndex;
    }
    
    std::map<std::string, int> registers =
        createMap<std::string, int>
        ("PC", 16)("LR", 17)("SP", 18)("PSW", 19);
    
    if(!contains(supportedRegisters, toUpper(reg)) ) {
        return -1;
    }
    
    return registers[toUpper(reg)];
}

