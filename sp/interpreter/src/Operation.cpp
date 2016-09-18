//
//  Operation.cpp
//  sp
//
//  Created by maxeler on 8/25/16.
//  Copyright © 2016 ptrifunovic. All rights reserved.
//

#include <numeric>

#include "Operation.hpp"
#include "CreateMap.hpp"
#include "CreateVector.h"
#include "ProcessString.h"
#include "Log.h"
#include "Error.h"
#include "Memory.h"

#define ERROR_PREFIX "Invalid operation: "

Operation::Operation(std::vector<std::string> operation) : opcode(operation[0]) {
    std::vector<std::string> _operands(operation.begin() + 1, operation.end());
          
    for(int i = 0; i < validLayouts[opcode.name].size() && !operands.areValid; i++) {
        operands = Operands(_operands, validLayouts[opcode.name][i]);
    }
    
    if(!operands.areValid) {
        ERROR("operands layout for operation '", BOLD(operation[0]), "' is unsupported");
    }
}

Operation::Operation(int memPos) : opcode(memPos) {
    LOG(opcode.name, " ", opcode.condition, " ", opcode.flag);

    for(int i = 0; i < validLayouts[opcode.name].size() && !operands.areValid; i++) {
        operands = Operands(memPos + 1, validLayouts[opcode.name][i]);
    }
    
    if(!operands.areValid) {
        ERROR("operands layout for operation '", BOLD(opcode.name), "' is unsupported");
    }
}


std::string Operation::createHexRepresentation(){
    return opcode.createHexRepresentation() + operands.createHexRepresentation();
};

bool Operation::execute() {
    if(readFromMem(PC*8, 32) == 0) {
        exit(0);
    }

    Operation opr(PC);

    PC += 4;

    if(!opr.opcode.isConditionValid()) {
        return true;
    }

    (*executeFunction[opr.opcode.name])(opr);

    for(int i=0;i<16;i++) {
        LOG("REG[", i, "] = ", REG[i], "(", toHexadecimal(REG[i], 8), ")");
    }

    LOG("-------------------");

    return true;
}

std::map<std::string, std::vector<std::string> > Operation::validLayouts =
    createMap<std::string, std::vector<std::string> >
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
    ("shr",  createVector<std::string>
             ("REG+PC+LR+SP+PSW,REG+PC+LR+SP+PSW,ABSEXP_5,CONST_0,NUSED_8"))
    ("shl",  createVector<std::string>
             ("REG+PC+LR+SP+PSW,REG+PC+LR+SP+PSW,ABSEXP_5,CONST_1,NUSED_8"))
    /*("mov",  createVector<std::string>
             ("REG+PC+LR+SP+PSW,REG+PC+LR+SP+PSW,NUSED_14"))*/
    ("ldch", createVector<std::string>
             ("REG,CONST_1,NUSED_3,ABSEXP_16"))
    ("ldcl", createVector<std::string>
             ("REG,CONST_0,NUSED_3,ABSEXP_16"));

void executeInt(Operation opr) {
    push(PSW);
    LR = PC;
    PC = readFromMem(32*opr.operands.val[0], 32);
}

void executeAdd(Operation opr) {
    if(opr.operands.val[1] == 0) {
        REG[opr.operands.val[0]] += REG[opr.operands.val[2]];
    } else if(opr.operands.val[1] == 1) {
        REG[opr.operands.val[0]] += opr.operands.val[2];
    }

    SET_OR_CLEAR_FLAG_N(REG[opr.operands.val[0]] < 0);
    SET_OR_CLEAR_FLAG_Z(REG[opr.operands.val[0]] == 0);
}

void executeSub(Operation opr) {
    if(opr.operands.val[1] == 0) {
        REG[opr.operands.val[0]] -= REG[opr.operands.val[2]];
    } else if(opr.operands.val[1] == 1) {
        REG[opr.operands.val[0]] -= opr.operands.val[2];
    }

    SET_OR_CLEAR_FLAG_N(REG[opr.operands.val[0]] < 0);
    SET_OR_CLEAR_FLAG_Z(REG[opr.operands.val[0]] == 0);
}

void executeMul(Operation opr) {
    if(opr.operands.val[2] == 0) {
        REG[opr.operands.val[1]] *= REG[opr.operands.val[4]];
    } else if(opr.operands.val[2] == 1) {
        REG[opr.operands.val[1]] *= opr.operands.val[3];
    }

    SET_OR_CLEAR_FLAG_N(REG[opr.operands.val[1]] < 0);
    SET_OR_CLEAR_FLAG_Z(REG[opr.operands.val[1]] == 0);
}

void executeDiv(Operation opr) {
     if(opr.operands.val[2] == 0) {
        REG[opr.operands.val[1]] /= REG[opr.operands.val[4]];
    } else if(opr.operands.val[2] == 1) {
        REG[opr.operands.val[1]] /= opr.operands.val[3];
    }

    SET_OR_CLEAR_FLAG_N(REG[opr.operands.val[1]] < 0);
    SET_OR_CLEAR_FLAG_Z(REG[opr.operands.val[1]] == 0);
}

void executeCmp(Operation opr) {
    int a;

    if(opr.operands.val[1] == 0) {
        a = REG[opr.operands.val[0]] - REG[opr.operands.val[2]];
    } else if(opr.operands.val[1] == 1) {
        a = REG[opr.operands.val[0]] - opr.operands.val[2];
    }

    SET_OR_CLEAR_FLAG_N(a < 0);
    SET_OR_CLEAR_FLAG_Z(a == 0);
}

void executeAnd(Operation opr) {
    REG[opr.operands.val[0]] &= REG[opr.operands.val[1]];
    SET_OR_CLEAR_FLAG_N(REG[opr.operands.val[0]] < 0);
    SET_OR_CLEAR_FLAG_Z(REG[opr.operands.val[0]] == 0);
}

void executeOr(Operation opr) {
    REG[opr.operands.val[0]] |= REG[opr.operands.val[1]];
    SET_OR_CLEAR_FLAG_N(REG[opr.operands.val[0]] < 0);
    SET_OR_CLEAR_FLAG_Z(REG[opr.operands.val[0]] == 0);
}

void executeNot(Operation opr) {
    REG[opr.operands.val[0]] = ~REG[opr.operands.val[1]];
    SET_OR_CLEAR_FLAG_N(REG[opr.operands.val[0]] < 0);
    SET_OR_CLEAR_FLAG_Z(REG[opr.operands.val[0]] == 0);
}

void executeTest(Operation opr) {
    // samo za flegove bitan
    int a = REG[opr.operands.val[0]] & REG[opr.operands.val[1]];
    SET_OR_CLEAR_FLAG_N(a);
    SET_OR_CLEAR_FLAG_Z(a);
}

void executeLdrStr(Operation opr) {
    int a = opr.operands.val[0];
    int f = opr.operands.val[2];

    if(f == 4 || f == 2) {
        a += 4;
    } else if(f == 5 || f==3) {
        a-=4;
    }

    if(opr.operands.val[3] == 1) {
        REG[opr.operands.val[1]] = readFromMem((REG[a]+opr.operands.val[4])*8, 32);
    } else {
        writeToMem((REG[a]+opr.operands.val[4])*8, 32, REG[opr.operands.val[1]]);
    }
}

void executeCall(Operation opr) {
    LR = PC;
    PC = REG[opr.operands.val[0]] + opr.operands.val[1];
    // TODO call label
}

void executeInOut(Operation opr) {
    // TODO
    // 0x1000 je tastatura upis
    // 0x1010 je status
    // 0x2000 je tastatura ispis
    if(opr.operands.val[2] == 1) {//in
	if(REG[opr.operands.val[1]] = 0X1000){
            if(inputBuffer.empty()) {
                PC -= 4;
            } else {
                REG[opr.operands.val[0]] = inputBuffer[0];
                inputBuffer.erase (inputBuffer.begin());
            }
        } else if(REG[opr.operands.val[1]] = 0X1010) {
            REG[opr.operands.val[0]] = !inputBuffer.empty();
        }
    } else {
        if(REG[opr.operands.val[1]] = 0X2000){
            putchar(REG[opr.operands.val[0]]);
        }
    }
}

void executeShrShlMov(Operation opr) {
    if(opr.operands.val[3] == 1) {
        REG[opr.operands.val[0]] = REG[opr.operands.val[1]] << opr.operands.val[2];
    } else {
        REG[opr.operands.val[0]] = REG[opr.operands.val[1]] >> opr.operands.val[2];
    }

    if(opr.operands.val[0] == PC_POS && opr.opcode.shouldSetFlags()) {
        PSW = pop();
    }

    SET_OR_CLEAR_FLAG_N(REG[opr.operands.val[0]] < 0);
    SET_OR_CLEAR_FLAG_Z(REG[opr.operands.val[0]] == 0);
}

void executeLdchLdcl(Operation opr) {
    if(opr.operands.val[1] == 1) {
        WRITETO(REG[opr.operands.val[0]], 16, 16, REG[opr.operands.val[1]]);
    } else {
        WRITETO(REG[opr.operands.val[0]], 0, 16, REG[opr.operands.val[1]]);
    }
}

std::map<std::string, executeOperation > Operation::executeFunction =
    createMap<std::string, executeOperation >
    ("int",  &executeInt)
    ("add",  &executeAdd)
    ("sub",  &executeAdd)
    ("mul",  &executeMul)
    ("div",  &executeDiv)
    ("cmp",  &executeCmp)
    ("and",  &executeAnd)
    ("or",   &executeOr)
    ("not",  &executeNot)
    ("test", &executeTest)
    ("ldr",  &executeLdrStr)
    ("str",  &executeLdrStr)
    ("call", &executeCall)
    ("in",   &executeInOut)
    ("out",  &executeInOut)
    ("mov",  &executeShrShlMov)
    ("shr",  &executeShrShlMov)
    ("shl",  &executeShrShlMov)
    ("ldch", &executeLdchLdcl)
    ("ldcl", &executeLdchLdcl);

std::map<std::string, std::string> Operation::changesFlags = 
    createMap<std::string, std::string >
    ("int",  "")
    ("add",  "zocn")
    ("sub",  "zocn")
    ("mul",  "zocn")
    ("div",  "zocn")
    ("cmp",  "zocn")
    ("and",  "zn")
    ("or",   "zn")
    ("not",  "zn")
    ("test", "zn")
    ("ldr",  "")
    ("str",  "")
    ("call", "")
    ("in",   "")
    ("out",  "")
    ("mov",  "zcn")
    ("shr",  "zcn")
    ("shl",  "zcn")
    ("ldch", "")
    ("ldcl", "");

