#include "Directive.h"
#include "Simbol.h"
#include "Section.h"
#include "Expresion.h"
#include "Argument.h"
#include "CreateMap.hpp"
#include "ProcessString.h"
#include "Error.h"
#include "Warning.h"
#include "as.h"

std::string createFillData(std::vector<std::string> arguments, int size) {
    int argumentsSize = arguments.size();
    
    std::string fill = "";
    
    for(int i = 1; i < argumentsSize; i++) {
        Argument expresionEvaluated = expresion(arguments[i]);
        
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
            ERROR("Undefined simbol: '", BOLD(directiv[i]), "'");
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
    int alignAmount = directiv.size() > 1 ? expresion(directiv[1]).value : ALIGN_AMOUNT;
    int max = directiv.size() > 3 ? expresion(directiv[3]).value : MAX_ALIGN_AMOUNT;
    int fill = directiv.size() > 2 ? expresion(directiv[2]).value : 0;

    int move = alignAmount - Section::offset() % alignAmount;
    if(move < max) {
         Section::fill(repeatNTimes(toHexadecimal(fill, 2), move));
    }
}

void skipDirectivFunctionForSecondPass(std::vector<std::string> directiv) {
    int fill = directiv.size() > 2 ? expresion(directiv[2]).value : 0;
    int move = directiv.size() > 1 ? expresion(directiv[1]).value : 0;

    Section::fill(repeatNTimes(toHexadecimal(fill, 2), move));
}

void endDirectivFunctionForSecondPass(std::vector<std::string> directiv) {
    Directive::endFound = true;
}

void asciiDirectivFunctionForSecondPass(std::vector<std::string> directiv) {
    for(int i = 1; i < directiv.size(); i++) {
        Argument exp = expresion(directiv[i]);
        Section::fill(toHexadecimal(exp.value, 2 * (directiv[i].length() - 2)));
    }
}

void ascizDirectivFunctionForSecondPass(std::vector<std::string> directiv) {
    for(int i = 1; i < directiv.size(); i++) {
        Argument exp = expresion(directiv[i]);
        Section::fill(toHexadecimal(exp.value, 2 * (directiv[i].length() - 2)) + "00");
    }
}

void setDirectivFunctionForSecondPass(std::vector<std::string> directiv) {
    if(directiv.size() != 3) {
        ERROR("'", BOLD(directiv[0]), "' must have two arguments");
    }

    Argument exp = expresion(directiv[2]);

    Simbol(directiv[1], exp.value, exp.sectionID, true, false, true);
}

void printDirectivFunctionForSecondPass(std::vector<std::string> directiv) {
    if(directiv.size() != 2) {
        ERROR("'", BOLD(directiv[0]), "' must have one arguments");
    }

    if(!contains(directiv[1], '"')) {
        WARNING("Strings must be placed between '", BOLD("\""), "'");
    }

    std::string prefix(inFile + ":" + toString(currentLineNumber) + ":");
    printf("%s%s\n",(BOLD(prefix + BLU(" message: "))).c_str(),
                    removeCharacterSetFromString(directiv[1], "\'\"").c_str());
}

void errDirectivFunctionForSecondPass(std::vector<std::string> directiv) {
    if(directiv.size() != 1) {
        ERROR("'", BOLD(directiv[0]), "' must have zero arguments");
    }

    ERROR(".error directive invoked in source file");
}

void errorDirectivFunctionForSecondPass(std::vector<std::string> directiv) {
    if(directiv.size() == 1) {
        ERROR(".error directive invoked in source file");
    } else if (directiv.size() == 2) {
        if(!contains(directiv[1], '"')) {
            WARNING("Strings must be placed between '", BOLD("\""), "'");
        }

        ERROR(removeCharacterSetFromString(directiv[1], "\'\""));
    } else {
        ERROR("'", BOLD(directiv[0]), "' must have zero or one arguments");
    }
}

void warningDirectivFunctionForSecondPass(std::vector<std::string> directiv) {
    if(directiv.size() != 2) {
        ERROR("'", BOLD(directiv[0]), "' must have one arguments");
    }

    if(!contains(directiv[1], '"')) {
        WARNING("Strings must be placed between '", BOLD("\""), "'");
    }

    WARNING(removeCharacterSetFromString(directiv[1], "\'\""));
}

std::map<std::string, DirectiveFunctionPointer> Directive::functionForSecondPass =
    createMap<std::string, DirectiveFunctionPointer>
    (".extern", &Directive::emptyFunction)
    (".public", &publicDirectivFunctionForSecondPass)
    (".globl", &publicDirectivFunctionForSecondPass)
    (".global", &publicDirectivFunctionForSecondPass)
    (".char", &charDirectivFunctionForSecondPass)
    (".byte", &charDirectivFunctionForSecondPass)
    (".word", &wordDirectivFunctionForSecondPass)
    (".2byte", &wordDirectivFunctionForSecondPass)
    (".long", &longDirectivFunctionForSecondPass)
    (".4byte", &longDirectivFunctionForSecondPass)
    (".align", &alignDirectivFunctionForSecondPass)
    (".skip", &skipDirectivFunctionForSecondPass)
    (".space", &skipDirectivFunctionForSecondPass)
    (".zero", &skipDirectivFunctionForSecondPass)
    (".end", &endDirectivFunctionForSecondPass)
    (".ascii", &asciiDirectivFunctionForSecondPass)
    (".asciz", &ascizDirectivFunctionForSecondPass)
    (".set", &setDirectivFunctionForSecondPass)
    (".equ", &setDirectivFunctionForSecondPass)
    (".print", &printDirectivFunctionForSecondPass)
    (".err", &errDirectivFunctionForSecondPass)
    (".error", &errorDirectivFunctionForSecondPass)
    (".warning", &warningDirectivFunctionForSecondPass);

