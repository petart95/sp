#include "Directive.h"
#include "Simbol.h"
#include "Section.h"
#include "CreateMap.hpp"
#include "ProcessString.h"
#include "Expresion.h"
#include "Error.h"

#define ERROR_PREFIX "Invalid directiv: "

void externDirectivFunctionForFirstPass(std::vector<std::string> directiv) {
    for(int i = 1; i < directiv.size(); i++) {
        Simbol::createExternal(directiv[i]);
    }
}

void charDirectivFunctionForFirstPass(std::vector<std::string> directiv) {
    Section::move(1 * (directiv.size() - 1));
}

void wordDirectivFunctionForFirstPass(std::vector<std::string> directiv) {
    Section::move(2 * (directiv.size() - 1));
}

void longDirectivFunctionForFirstPass(std::vector<std::string> directiv) {
    Section::move(4 * (directiv.size() - 1));
}

void alignDirectivFunctionForFirstPass(std::vector<std::string> directiv) {
    int alignAmount = directiv.size() > 1 ? expresion(directiv[1]).value : ALIGN_AMOUNT;
    int max = directiv.size() > 3 ? expresion(directiv[3]).value : MAX_ALIGN_AMOUNT;

    if(directiv.size() > 1 && expresion(directiv[1]).isRelativ()) {
        ERROR("first argument '", BOLD(directiv[1]), "' must be absolut");
    } else if(directiv.size() > 2 && expresion(directiv[2]).isRelativ()) {
        ERROR("second argument '", BOLD(directiv[2]), "' must be absolut");
    } else if(directiv.size() > 3 && expresion(directiv[3]).isRelativ()) {
        ERROR("third argument '", BOLD(directiv[3]), "' must be absolut");
    }

    int move = alignAmount - Section::offset() % alignAmount;
    if(move < max) {
        Section::move(move);
    }
}

void skipDirectivFunctionForFirstPass(std::vector<std::string> directiv) {
    if(directiv.size() > 1 && expresion(directiv[1]).isRelativ()) {
        ERROR("first argument '", BOLD(directiv[1]), "' must be absolut");
    } else if(directiv.size() > 2 && expresion(directiv[2]).isRelativ()) {
        ERROR("second argument '", BOLD(directiv[2]), "' must be absolut");
    }

    int move = directiv.size() > 1 ? expresion(directiv[1]).value : 0;
    Section::move(move);
}

void endDirectivFunctionForFirstPass(std::vector<std::string> directiv) {
    Directive::endFound = true;
}

void asciiDirectivFunctionForFirstPass(std::vector<std::string> directiv) {
    for(int i = 1; i < directiv.size(); i++) {
        Section::move(directiv[i].length() - 2);
    }
}

void ascizDirectivFunctionForFirstPass(std::vector<std::string> directiv) {
    for(int i = 1; i < directiv.size(); i++) {
        Section::move(directiv[i].length() - 1);
    }
}

void setDirectivFunctionForFirstPass(std::vector<std::string> directiv) {
    if(directiv.size() != 3) {
        ERROR("'", BOLD(directiv[0]), "' must have two arguments");
    }
    
    Simbol::update(directiv[1], expresion(directiv[2]));
}

std::map<std::string, DirectiveFunctionPointer> Directive::functionForFirstPass =
    createMap<std::string, DirectiveFunctionPointer>
    (".extern", &externDirectivFunctionForFirstPass)
    (".public", &Directive::emptyFunction)
    (".globl", &Directive::emptyFunction)
    (".global", &Directive::emptyFunction)
    (".char", &charDirectivFunctionForFirstPass)
    (".byte", &charDirectivFunctionForFirstPass)
    (".word", &wordDirectivFunctionForFirstPass)
    (".2byte", &wordDirectivFunctionForFirstPass)
    (".long", &longDirectivFunctionForFirstPass)
    (".4byte", &longDirectivFunctionForFirstPass)
    (".align", &alignDirectivFunctionForFirstPass)
    (".skip", &skipDirectivFunctionForFirstPass)
    (".space", &skipDirectivFunctionForFirstPass)
    (".zero", &skipDirectivFunctionForFirstPass)
    (".end", &endDirectivFunctionForFirstPass)
    (".ascii", &asciiDirectivFunctionForFirstPass)
    (".asciz", &ascizDirectivFunctionForFirstPass)
    (".set", &setDirectivFunctionForFirstPass)
    (".equ", &setDirectivFunctionForFirstPass)
    (".print", &Directive::emptyFunction)
    (".err", &Directive::emptyFunction)
    (".error", &Directive::emptyFunction)
    (".warning", &Directive::emptyFunction);

