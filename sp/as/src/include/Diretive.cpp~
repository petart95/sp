#include "Directive.h"
#include "Section.h"

bool Directive::didEnd = false;

Directive::Directive(std::vector<std::string> directive) {
    name = directive[0];
    arguments = std::vector<std::string>(directive.begin() + 1, directive.end()

    if(name.comapre(".char") == 0) {
        fill = ;
    } else if(name.comapre(".word") == 0) {
        fill = ;
    } else if(name.comapre(".long") == 0) {
        fill = ;
    } else if(name.comapre(".align") == 0) {
        fill = ;
    } else if(name.comapre(".skip") == 0) {
        fill = ;
    } else if(name.comapre(".public") == 0) {
    } else if(name.comapre(".extern") == 0) {
    } else if(name.comapre(".end") == 0) {
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

