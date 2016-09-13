//
//  Operation.hpp
//  sp
//
//  Created by maxeler on 8/25/16.
//  Copyright © 2016 ptrifunovic. All rights reserved.
//

#ifndef Operation_hpp
#define Operation_hpp

#include <string>
#include <vector>
#include <map>
#include <utility>

struct Operand {
    long long value;
    long long size;
    std::string type;
    
    Operand(int _size, int _value, std::string _type)
        : size(_size), value(_value), type(_type) {}
};

typedef Operand (*parseOperandWithTypeFunctionPointer)(std::string operandValue);

struct Operation {
    
    struct Opcode {
        std::string name;
        std::string condition;
        std::string flag;
        
        int isValid;
        
        static std::map<std::string, int> codeForValidName;
        static std::map<std::string, int> codeForValidCondition;
        static std::map<std::string, int> codeForValidFlag;
        
        Opcode(std::string opcode);
        
        std::string createHexRepresentation();
    };
    
    struct Operands {
        std::vector<std::string> operands;
        std::vector<std::string> type;
        
        int areValid;
        
        Operand parseOperandWithType(std::string value, std::string type);
        
        Operands(std::vector<std::string> _operands, std::string _type);
        
        std::string createHexRepresentation();
        
        int registerHexRepresentation(std::string operand);
    };
    
    Opcode opcode;
    Operands operands;
    
    static std::map<std::string, std::vector<std::string> > validLayouts;
    
    Operation(std::vector<std::string> operation);
    
    std::string createHexRepresentation();
    
    bool isOperationValid();
};

#endif /* Operation_hpp */
