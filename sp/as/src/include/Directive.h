#ifndef DIRECTIVE_H_
#define DIRECTIVE_H_

#include <string>
#include <vector>

typedef void (*DirectiveFunctionPointer)(std::vector<std::string> directiv);

struct Directive {
    std::string name;
    std::vector<std::string> arguments;

    std::string fill;
    bool shouldFill;
    
    bool shouldEnd;
    static bool didEnd;

    DirectiveFunctionPointer functionForFirstPass;
    DirectiveFunctionPointer functionForSecondPass;

    Directive(std::vector<std::string> directive);
    
    void firstPass();
    void secondPass();
};

#endif /* DIRECTIVE_H_ */

