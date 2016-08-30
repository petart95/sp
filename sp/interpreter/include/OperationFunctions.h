#ifndef OPERATION_FUNCTIONS_H_
#define OPERATION_FUNCTIONS_H_

#include <vector>
#include <string>
#include <map>

typedef void (*OperationFunctionPointer)(std::vector<std::string> operaion);

extern std::map<std::string, OperationFunctionPointer> handelOperation;

void setOperationFunctionsForFirstPass();
void setOperationFunctionsForSecondPass();

bool isOperationSupported(std::string operation);

//int, add, sub, mul, div, cmp, and, or, not, test, ldr/str, call, in/out, mov/shr/shl, ldch/l

void intOperationFunctionForFirstPass(std::vector<std::string> operation);
void addOperationFunctionForFirstPass(std::vector<std::string> operation);
void subOperationFunctionForFirstPass(std::vector<std::string> operation);
void mulOperationFunctionForFirstPass(std::vector<std::string> operation);
void divOperationFunctionForFirstPass(std::vector<std::string> operation);
void cmpOperationFunctionForFirstPass(std::vector<std::string> operation);
void andOperationFunctionForFirstPass(std::vector<std::string> operation);
void orOperationFunctionForFirstPass(std::vector<std::string> operation);
void notOperationFunctionForFirstPass(std::vector<std::string> operation);
void testOperationFunctionForFirstPass(std::vector<std::string> operation);
void ldrOperationFunctionForFirstPass(std::vector<std::string> operation);
void strOperationFunctionForFirstPass(std::vector<std::string> operation);
void callOperationFunctionForFirstPass(std::vector<std::string> operation);
void inOperationFunctionForFirstPass(std::vector<std::string> operation);
void outOperationFunctionForFirstPass(std::vector<std::string> operation);
void movOperationFunctionForFirstPass(std::vector<std::string> operation);
void shrOperationFunctionForFirstPass(std::vector<std::string> operation);
void shlOperationFunctionForFirstPass(std::vector<std::string> operation);
void ldchOperationFunctionForFirstPass(std::vector<std::string> operation);
void ldclOperationFunctionForFirstPass(std::vector<std::string> operation);

void intOperationFunctionForSecondPass(std::vector<std::string> operation);
void addOperationFunctionForSecondPass(std::vector<std::string> operation);
void subOperationFunctionForSecondPass(std::vector<std::string> operation);
void mulOperationFunctionForSecondPass(std::vector<std::string> operation);
void divOperationFunctionForSecondPass(std::vector<std::string> operation);
void cmpOperationFunctionForSecondPass(std::vector<std::string> operation);
void andOperationFunctionForSecondPass(std::vector<std::string> operation);
void orOperationFunctionForSecondPass(std::vector<std::string> operation);
void notOperationFunctionForSecondPass(std::vector<std::string> operation);
void testOperationFunctionForSecondPass(std::vector<std::string> operation);
void ldrOperationFunctionForSecondPass(std::vector<std::string> operation);
void strOperationFunctionForSecondPass(std::vector<std::string> operation);
void callOperationFunctionForSecondPass(std::vector<std::string> operation);
void inOperationFunctionForSecondPass(std::vector<std::string> operation);
void outOperationFunctionForSecondPass(std::vector<std::string> operation);
void movOperationFunctionForSecondPass(std::vector<std::string> operation);
void shrOperationFunctionForSecondPass(std::vector<std::string> operation);
void shlOperationFunctionForSecondPass(std::vector<std::string> operation);
void ldchOperationFunctionForSecondPass(std::vector<std::string> operation);
void ldclOperationFunctionForSecondPass(std::vector<std::string> operation);

#endif /* OPERATION_FUNCTIONS_H_ */

