#ifndef DIRECTIVE_H_
#define DIRECTIVE_H_

#include <string>
#include <vector>
#include <map>

#define ALIGN_AMOUNT 4

typedef void (*DirectiveFunctionPointer)(std::vector<std::string> directiv);

struct Directive {
    static bool endFound;

    static std::map<std::string, DirectiveFunctionPointer> functionForFirstPass;
    static std::map<std::string, DirectiveFunctionPointer> functionForSecondPass;
    
    static bool isNameValid(std::string name);
    
    static void emptyFunction(std::vector<std::string> directiv) {}
};

#endif /* DIRECTIVE_H_ */

