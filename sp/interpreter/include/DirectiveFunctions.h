#ifndef DIRECTIVE_FUNCTIONS_H_
#define DIRECTIVE_FUNCTIONS_H_

#include <vector>
#include <string>
#include <map>

typedef void (*DirectiveFunctionPointer)(std::vector<std::string> directiv);

extern std::map<std::string, DirectiveFunctionPointer> handelDirectiv;

extern bool isExitFlagSet;

void setDirectivFunctionsForFirstPass();
void setDirectivFunctionsForSecondPass();

bool isDirectivSupported(std::string directiv);

// .public, .extern, .text, .data, .bss, .char, .word, .long, .align, .skip, .end

void publicDirectivFunctionForFirstPass(std::vector<std::string> directiv);
void externDirectivFunctionForFirstPass(std::vector<std::string> directiv);
void textDirectivFunctionForFirstPass(std::vector<std::string> directiv);
void dataDirectivFunctionForFirstPass(std::vector<std::string> directiv);
void bssDirectivFunctionForFirstPass(std::vector<std::string> directiv);
void charDirectivFunctionForFirstPass(std::vector<std::string> directiv);
void wordDirectivFunctionForFirstPass(std::vector<std::string> directiv);
void longDirectivFunctionForFirstPass(std::vector<std::string> directiv);
void alignDirectivFunctionForFirstPass(std::vector<std::string> directiv);
void skipDirectivFunctionForFirstPass(std::vector<std::string> directiv);
void endDirectivFunctionForFirstPass(std::vector<std::string> directiv);

void publicDirectivFunctionForSecondPass(std::vector<std::string> directiv);
void externDirectivFunctionForSecondPass(std::vector<std::string> directiv);
void textDirectivFunctionForSecondPass(std::vector<std::string> directiv);
void dataDirectivFunctionForSecondPass(std::vector<std::string> directiv);
void bssDirectivFunctionForSecondPass(std::vector<std::string> directiv);
void charDirectivFunctionForSecondPass(std::vector<std::string> directiv);
void wordDirectivFunctionForSecondPass(std::vector<std::string> directiv);
void longDirectivFunctionForSecondPass(std::vector<std::string> directiv);
void alignDirectivFunctionForSecondPass(std::vector<std::string> directiv);
void skipDirectivFunctionForSecondPass(std::vector<std::string> directiv);
void endDirectivFunctionForSecondPass(std::vector<std::string> directiv);

#endif /* DIRECTIVE_FUNCTIONS_H_ */
