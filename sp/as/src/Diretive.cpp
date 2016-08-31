#include "Directive.h"
#include "Section.h"
#include "Expresion.h"
#include "ProcessString.h"

bool Directive::didEnd = false;

std::string createFillDataForCharWordLong(std::vector<std::string> arguments, int size) {
    int argumentsSize = arguments.size();
    
    std::string fill = "";
    
    for(int i = 0; i < argumentsSize; i++) {
        Expresion expresion(arguments[i]);
        
        Value expresionEvaluated = expresion.evaluate();
        
        int result = expresionEvaluated.value;
        
        expresionEvaluated.addRealocatioDataForType("R_386_" + toString(2*size));
        
        fill += Section::fill(toHexadecimal(result, size));
    }
    
    return fill;
}

Directive::Directive(std::vector<std::string> directive) : shouldEnd(false), shouldFill(true){
    name = directive[0];
    arguments = std::vector<std::string>(directive.begin() + 1, directive.end()

    if(name.comapre(".char") == 0) {
        fill = createFillDataForCharWordLong(arguments, 2);
    } else if(name.comapre(".word") == 0) {
        fill = createFillDataForCharWordLong(arguments, 4);
    } else if(name.comapre(".long") == 0) {
        fill = createFillDataForCharWordLong(arguments, 8);
    } else if(name.comapre(".align") == 0) {
        int alignAmount = 4;
        
        if(directiv.size() > 1) {
            alignAmount = atoi(directiv[1].c_str());
        }
        
        int offset = alignAmount - Section::tabel[Section::current].locationCounter % alignAmount;
        
        fill = std::string(2*offset, '0');
    } else if(name.comapre(".skip") == 0) {
        fill = std::string(2*atoi(directiv[1].c_str()), '0');
    } else if(name.comapre(".public") == 0) {
        shouldFill = false;
    } else if(name.comapre(".extern") == 0) {
        shouldFill = false;
    } else if(name.comapre(".end") == 0) {
        shouldFill = false;
        shouldEnd = true;
    }
}

void Directive::firstPass() {
    if(shouldFill) {
        Section::move(fill.length() / 2);
    } else if(shouldEnd) {
        didEnd = true;
    } else {
        (*functionForFirstPass)(argumets);
    }
}

void Directive::secondPass() {
    if(shouldFill) {
        Section::fill(fill);
    } else if(shouldEnd) {
        didEnd = true;
    } else {
        (*functionForSecondPass)(argumets);
    }
}

