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
#include "Log.h"

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
    std::string hexString;

    if(opcode.name.compare("int") == 0) {
        hexString = opcode.createHexRepresentation() + toHexadecimal(operands.createHexRepresentation()<<20, 6);
    } else if(opcode.name.compare("add") == 0 ||
              opcode.name.compare("sub") == 0 ||
              opcode.name.compare("mul") == 0 ||
              opcode.name.compare("div") == 0 ||
              opcode.name.compare("cmp") == 0) {
	long long constant = 0; 
        if(operands.getOperandAtIndex(1).type.compare("R_386_18S") == 0) {
            constant = 1;
        }
        long long operandsCode = (operands.getOperandAtIndex(0).value<<19) + (constant<<18) + operands.getOperandAtIndex(1).value;
        hexString = opcode.createHexRepresentation() + toHexadecimal(operandsCode, 6);
    } else if(opcode.name.compare("and") == 0 ||
              opcode.name.compare("or") == 0 ||
              opcode.name.compare("not") == 0 ||
              opcode.name.compare("test") == 0) {
        hexString = opcode.createHexRepresentation() + toHexadecimal(operands.createHexRepresentation()<<14, 6);
    } else if(opcode.name.compare("ldr") == 0) {
        long long operandsCode = (operands.getOperandAtIndex(0).value<<19) + (operands.getOperandAtIndex(1).value<<14) +
                                 (operands.getOperandAtIndex(2).value<<11) + (1<<10) +  operands.getOperandAtIndex(3).value;
        hexString = opcode.createHexRepresentation() + toHexadecimal(operandsCode, 6);
    } else if(opcode.name.compare("str") == 0) {
        long long operandsCode = (operands.getOperandAtIndex(0).value<<19) + (operands.getOperandAtIndex(1).value<<14) +
                                 (operands.getOperandAtIndex(2).value<<11) + (0<<10) +  operands.getOperandAtIndex(3).value;
        hexString = opcode.createHexRepresentation() + toHexadecimal(operandsCode, 6);
    } else if(opcode.name.compare("call") == 0) {
        hexString = opcode.createHexRepresentation() + toHexadecimal(operands.createHexRepresentation(), 6);
    } else if(opcode.name.compare("in") == 0) {
        hexString = opcode.createHexRepresentation() + toHexadecimal((operands.createHexRepresentation()<<16) + (1<<15), 6);
    } else if(opcode.name.compare("out") == 0) {
        hexString = opcode.createHexRepresentation() + toHexadecimal((operands.createHexRepresentation()<<16) + (0<<15), 6);
    } else if(opcode.name.compare("mov") == 0) {
        hexString = opcode.createHexRepresentation() + toHexadecimal((operands.createHexRepresentation()<<14), 6);
    } else if(opcode.name.compare("shr") == 0) {
        hexString = opcode.createHexRepresentation() + toHexadecimal((operands.createHexRepresentation()<<9) + (0<<8), 6);
    } else if(opcode.name.compare("shl") == 0) {
        hexString = opcode.createHexRepresentation() + toHexadecimal((operands.createHexRepresentation()<<9) + (1<<8), 6);
    } else if(opcode.name.compare("ldch") == 0) {
        long long operandsCode = (operands.getOperandAtIndex(0).value<<20) + (1<<19) + (0<<16) + operands.getOperandAtIndex(1).value;
        hexString = opcode.createHexRepresentation() + toHexadecimal(operandsCode, 6);
    } else if(opcode.name.compare("ldcl") == 0) {
        long long operandsCode = (operands.getOperandAtIndex(0).value<<20) + (0<<19) + (0<<16) + operands.getOperandAtIndex(1).value;
        hexString = opcode.createHexRepresentation() + toHexadecimal(operandsCode, 6);
    }

    return hexString;
};

bool Operation::isOperationValid() {
    return opcode.isValid && operands.areValid;
}
