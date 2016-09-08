//
//  Operation.cpp
//  sp
//
//  Created by maxeler on 8/25/16.
//  Copyright © 2016 ptrifunovic. All rights reserved.
//

#include "Operation.hpp"
#include "CreateMap.hpp"
#include "CreateVector.h"
#include "ProcessString.h"
#include "Log.h"

Operation::Operation(std::vector<std::string> operation)
    : opcode(operation[0]), 
      operands(std::vector<std::string>(operation.begin() + 1, operation.end()),
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

std::map<std::string, std::vector<std::string>> Operation::operandTypeForOpcode =
    createMap<std::string, std::vector<std::string>>
    ("int",  createVector<std::string>
             ("ABSEXP_4,NUSED_20"))
    ("add",  createVector<std::string>
             ("REG+PC+LR+SP,CONST_0,REG+PC+LR+SP,NUSED_13")
             ("REG+PC+LR+SP,CONST_1,ABSEXP_18_SIGNEXT"))
    ("sub",  createVector<std::string>
             ("REG+PC+LR+SP,CONST_0,REG+PC+LR+SP,NUSED_13")
             ("REG+PC+LR+SP,CONST_1,ABSEXP_18_SIGNEXT"))
    ("mul",  createVector<std::string>
             ("CONST_0,REG,CONST_0,CONST_0,REG,NUSED_13")
             ("CONST_0,REG,CONST_1,ABSEXP_18_SIGNEXT"))
    ("div",  createVector<std::string>
             ("CONST_0,REG,CONST_0,CONST_0,REG,NUSED_13")
             ("CONST_0,REG,CONST_1,ABSEXP_18_SIGNEXT"))
    ("cmp",  createVector<std::string>
             ("CONST_0,REG,CONST_0,CONST_0,REG,NUSED_13")
             ("CONST_0,REG,CONST_1,ABSEXP_18_SIGNEXT"))
    ("and",  createVector<std::string>
             ("REG+SP,REG+SP,NUSED_14"))
    ("or",   createVector<std::string>
             ("RGE+SP,REG+SP,NUSED_14"))
    ("not",  createVector<std::string>
             ("REG+SP,REG+SP,NUSED_14"))
    ("test", createVector<std::string>
             ("REG+SP,REG+SP,NUSED_14"))
    ("ldr",  createVector<std::string>
             ("REG+PC+LR+SP+PSW,REG+PC+LR+SP+PSW,ABSEXP_3,CONST_1,ABSEXP_10_SIGNEXT"))
    ("str",  createVector<std::string>
             ("REG+PC+LR+SP+PSW,REG+PC+LR+SP+PSW,ABSEXP_3,CONST_0,ABSEXP_10_SIGNEXT"))
    ("call", createVector<std::string>
             ("REG+PC+LR+SP+PSW,ABSEXP_19_SIGNEXT")
             ("ABSEXP_24"))
    ("in",   createVector<std::string>
             ("REG,REG,CONST_1,NUSED_15"))
    ("out",  createVector<std::string>
             ("REG,REG,CONST_0,NUSED_15"))
    ("mov",  createVector<std::string>
             ("REG+PC+LR+SP+PSW,REG+PC+LR+SP+PSW,NUSED_14"))
    ("shr",  createVector<std::string>
             ("REG+PC+LR+SP+PSW,REG+PC+LR+SP+PSW,ABSEXP_5,CONST_0,NUSED_8"))
    ("shl",  createVector<std::string>
             ("REG+PC+LR+SP+PSW,REG+PC+LR+SP+PSW,ABSEXP_5,CONST_1,NUSED_8"))
    ("ldch", createVector<std::string>
             ("REG,CONST_1,NUSED_3,R_386_16"))
    ("ldcl", createVector<std::string>
             ("REG,CONST_0,NUSED_3,R_386_16"));

