#include "Directive.h"
#include "Simbol.h"
#include "Section.h"
#include "CreateMap.hpp"
#include "ProcessString.h"

void externDirectivFunctionForFirstPass(std::vector<std::string> directiv) {
    for(int i = 1; i < directiv.size(); i++) {
        // TODO
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
    int alignAmount = directiv.size() > 1 ? toIntager(directiv[1]) : ALIGN_AMOUNT;
    
    Section::move(alignAmount - Section::offset() % alignAmount);
}

void skipDirectivFunctionForFirstPass(std::vector<std::string> directiv) {
	Section::move(toIntager(directiv[1]));
}

void endDirectivFunctionForFirstPass(std::vector<std::string> directiv) {
    Directive::endFound = true;
}

std::map<std::string, DirectiveFunctionPointer> Directive::functionForFirstPass =
createMap<std::string, DirectiveFunctionPointer>
(".extern", &externDirectivFunctionForFirstPass)
(".public", &Directive::emptyFunction)
(".char", &charDirectivFunctionForFirstPass)
(".word", &wordDirectivFunctionForFirstPass)
(".long", &longDirectivFunctionForFirstPass)
(".align", &alignDirectivFunctionForFirstPass)
(".skip", &skipDirectivFunctionForFirstPass)
(".end", &endDirectivFunctionForFirstPass);
