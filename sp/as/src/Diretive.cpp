#include "Directive.h"

bool Directive::endFound = false;

bool Directive::isNameValid(std::string name) {
    return functionForFirstPass.find(name) != functionForFirstPass.end();
}

