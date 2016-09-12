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
#include "Error.h"

#define ERROR_PREFIX "Invalid operation: "

Operation::Operation(std::vector<std::string> operation) : opcode(operation[0]) {
    std::vector<std::string> _operands(operation.begin() + 1, operation.end());
          
    std::map<std::string, std::vector<std::string>>::iterator it_type iterator;
          
    for(iterator = supportedOperations.begin(); iterator != supportedOperations.end(); iterator++) {
        if(iterator->first == opcode.name) {
            operands = Operands(_operands, iterator->second);
            
            if(operands.areValid) {
                break;
            }
        }
    }
    
    if(!operands) {
        ERROR(BOLD("operation for opcode '" , BOLD(operation[0]), "' was not found"));
    } else if(!operands.areValid) {
        ERROR(" operands layout for operation '", BOLD(operation[0]), "' is unsupported");
    }
}

std::string Operation::createHexRepresentation(){
    return opcode.createHexRepresentation() + operands.createHexRepresentation();
};

bool Operation::isOperationValid() {
    return opcode.isValid && operands.areValid;
}

std::map<std::string, std::vector<std::string>> Operation::supportedOperations =
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
             ("REG,CONST_1,NUSED_3,ABSEXP_16"))
    ("ldcl", createVector<std::string>
             ("REG,CONST_0,NUSED_3,ABSEXP_16"));

