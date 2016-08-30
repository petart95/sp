//
//  Opcode.cpp
//  sp
//
//  Created by maxeler on 8/25/16.
//  Copyright © 2016 ptrifunovic. All rights reserved.
//

#include "Operation.hpp"
#include "CreateMap.hpp"
#include "ProcessString.h"

#define FLAG_OFFSET 4
#define CONDITION_OFFSET 5

std::map<std::string, int> Operation::Opcode::codeForValidName =
createMap<std::string, int> ("int", 0)("add", 1)("sub", 2)("mul", 3)("div", 4)("cmp", 5)
("and", 6)("or", 7)("not", 8)("test", 9)("ldr", 10)("str", 10)("call", 12)
("in", 13)("out", 13)("mov", 14)("shr", 14)("shl", 14)("ldch", 15)("ldcl", 15);

std::map<std::string, int> Operation::Opcode::codeForValidCondition =
createMap<std::string, int> ("eq", 0)("ne", 1)("gt", 2)("ge", 3)("lt", 4)("le", 5)("", 7)("al", 7);

std::map<std::string, int> Operation::Opcode::codeForValidFlag =
createMap<std::string, int> ("nf", 0)("", 0)("uf", 1);

Operation::Opcode::Opcode(std::string opcode) : isValid(true) {
    std::vector<std::string> opcodeParts = splitStringWhitCharacterSet(opcode, "-");
    
    if(opcodeParts.size() == 1) {
        opcodeParts.push_back("");
        opcodeParts.push_back("");
    } else if(opcodeParts.size() == 2) {
        opcodeParts.push_back("");
        
        if(codeForValidCondition.find(opcodeParts[1]) == codeForValidCondition.end()){
            swap(opcodeParts[1], opcodeParts[2]);
        }
    } else if(opcodeParts.size() > 3) {
        isValid = false;
        return;
    }
    
    if(codeForValidName.find(opcodeParts[0]) == codeForValidName.end() ||
       codeForValidCondition.find(opcodeParts[1]) == codeForValidCondition.end() ||
       codeForValidFlag.find(opcodeParts[2]) == codeForValidFlag.end()) {
        isValid = false;
        return;
    }
    
    name = opcodeParts[0];
    condition = opcodeParts[1];
    flag = opcodeParts[2];
}

std::string Operation::Opcode::createHexRepresentation() {
    if(!isValid) {
        return "ERROR";
    }
    
    int opcode = (codeForValidCondition[condition] << CONDITION_OFFSET) +
    (codeForValidFlag[flag] << FLAG_OFFSET) +
    codeForValidName[name];
    
    return toHexadecimal(opcode, 2);
}
