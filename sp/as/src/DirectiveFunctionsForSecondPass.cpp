#include "Directive.h"
#include "Simbol.h"
#include "Section.h"
#include "Expresion.h"
#include "CreateMap.hpp"
#include "ProcessString.h"
#include "Error.h"

std::string createFillData(std::vector<std::string> arguments, int size) {
    int argumentsSize = arguments.size();
    
    std::string fill = "";
    
    for(int i = 1; i < argumentsSize; i++) {
        Expresion expresion(arguments[i]);
        
        Value expresionEvaluated = expresion.evaluate();
        
        int result = expresionEvaluated.value;
        
        expresionEvaluated.addRealocatioDataForType("R_386_" + toString(2*size));
        
        fill += toHexadecimal(result, size);
    }
    
    return fill;
}

void publicDirectivFunctionForSecondPass(std::vector<std::string> directiv) {
    for(int i = 1; i < directiv.size(); i++) {
        int index = Simbol::withName(directiv[i]);
        
        if(index == -1) {
            ERROR("Undefined simbol ", directiv[i]);
        }
        
        Simbol::tabel[index].isGlobal = true;
    }
}

void charDirectivFunctionForSecondPass(std::vector<std::string> directiv) {
    Section::fill(createFillData(directiv, 1));
}

void wordDirectivFunctionForSecondPass(std::vector<std::string> directiv) {
    Section::fill(createFillData(directiv, 2));
}

void longDirectivFunctionForSecondPass(std::vector<std::string> directiv) {
    Section::fill(createFillData(directiv, 4));
}

void alignDirectivFunctionForSecondPass(std::vector<std::string> directiv) {
    int alignAmount = directiv.size() > 1 ? toIntager(directiv[1]) : ALIGN_AMOUNT;
    
    Section::fill(std::string(2 * (alignAmount - Section::offset() % alignAmount), '0'));
}

void skipDirectivFunctionForSecondPass(std::vector<std::string> directiv) {
    Section::fill(std::string(2 * toIntager(directiv[1]), '0'));
}

void endDirectivFunctionForSecondPass(std::vector<std::string> directiv) {
    Directive::endFound = true;
}

std::map<std::string, DirectiveFunctionPointer> Directive::functionForSecondPass =
createMap<std::string, DirectiveFunctionPointer>
(".extern", &Directive::emptyFunction)
(".public", &publicDirectivFunctionForSecondPass)
(".char", &charDirectivFunctionForSecondPass)
(".word", &wordDirectivFunctionForSecondPass)
(".long", &longDirectivFunctionForSecondPass)
(".align", &alignDirectivFunctionForSecondPass)
(".skip", &skipDirectivFunctionForSecondPass)
(".end", &endDirectivFunctionForSecondPass);
