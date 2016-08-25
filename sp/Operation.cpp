//
//  Operation.cpp
//  sp
//
//  Created by maxeler on 8/25/16.
//  Copyright © 2016 ptrifunovic. All rights reserved.
//

#include "Operation.hpp"
#include "CreateMap.hpp"
#include "ProcessString.h"

std::map<std::string, std::string> Operation::operandTypeForOpcode = createMap<std::string, std::string>
    ("int",  "R_386_4")
    ("add",  "R_386_4+PC+LR+SP,R_386_4+PC+LR+SP|R_386_18S")
    ("sub",  "R_386_4+PC+LR+SP,R_386_4+PC+LR+SP|R_386_18S")
    ("mul",  "R_386_4,R_386_4|R_386_18S")
    ("div",  "R_386_4,R_386_4|R_386_18S")
    ("cmp",  "R_386_4,R_386_4|R_386_18S")
    ("and",  "R_386_4+SP,R_386_4+SP")
    ("or",   "R_386_4+SP,R_386_4+SP")
    ("not",  "R_386_4+SP,R_386_4+SP")
    ("test", "R_386_4+SP,R_386_4+SP")
    ("ldr",  "R_386_4+PC+LR+SP+PSW,R_386_4+PC+LR+SP+PSW,R_386_3,R_386_PC10S")
    ("str",  "R_386_4+PC+LR+SP+PSW,R_386_4+PC+LR+SP+PSW,R_386_3,R_386_PC10S")
    ("call", "R_386_4+PC+LR+SP+PSW,R_386_PC19S")
    ("in",   "R_386_4,R_386_4")
    ("out",  "R_386_4,R_386_4")
    ("mov",  "R_386_4+PC+LR+SP+PSW,R_386_4+PC+LR+SP+PSW")
    ("shr",  "R_386_4+PC+LR+SP+PSW,R_386_4+PC+LR+SP+PSW,R_386_5")
    ("shl",  "R_386_4+PC+LR+SP+PSW,R_386_4+PC+LR+SP+PSW,R_386_5")
    ("ldch", "R_386_4,R_386_16")
    ("ldcl", "R_386_4,R_386_16");

Operation::Operation(std::vector<std::string> operation)
    : opcode(operation[0]), operands(std::vector<std::string>(operation.begin() + 1, operation.end()),
                                     operandTypeForOpcode[opcode.name]) {
}

std::string Operation::createHexRepresentation(){
    return opcode.createHexRepresentation() + operands.createHexRepresentation();
};

bool Operation::isOperationValid() {
    return opcode.isValid && operands.areValid;
}