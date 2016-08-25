#include "OperationFunctions.h"
#include "Log.h"

using namespace std;

void setOperationFunctionsForSecondPass() {
	handelOperation["int"] = &intOperationFunctionForSecondPass;
	handelOperation["add"] = &addOperationFunctionForSecondPass;
	handelOperation["sub"] = &subOperationFunctionForSecondPass;
	handelOperation["mul"] = &mulOperationFunctionForSecondPass;
	handelOperation["div"] = &divOperationFunctionForSecondPass;
	handelOperation["cmp"] = &cmpOperationFunctionForSecondPass;
	handelOperation["and"] = &andOperationFunctionForSecondPass;
	handelOperation["or"] = &orOperationFunctionForSecondPass;
	handelOperation["not"] = &notOperationFunctionForSecondPass;
	handelOperation["test"] = &testOperationFunctionForSecondPass;
	handelOperation["ldr"] = &ldrOperationFunctionForSecondPass;
	handelOperation["str"] = &strOperationFunctionForSecondPass;
	handelOperation["call"] = &callOperationFunctionForSecondPass;
	handelOperation["in"] = &inOperationFunctionForSecondPass;
	handelOperation["out"] = &outOperationFunctionForSecondPass;
	handelOperation["mov"] = &movOperationFunctionForSecondPass;
	handelOperation["shr"] = &shrOperationFunctionForSecondPass;
	handelOperation["shl"] = &shlOperationFunctionForSecondPass;
	handelOperation["ldch"] = &ldchOperationFunctionForSecondPass;
	handelOperation["ldcl"] = &ldclOperationFunctionForSecondPass;
}

//int, add, sub, mul, div, cmp, and, or, not, test, ldr/str, call, in/out, mov/shr/shl, ldch/l

void intOperationFunctionForSecondPass(std::vector<std::string> operation) {
}

void addOperationFunctionForSecondPass(std::vector<std::string> operation) {
}

void subOperationFunctionForSecondPass(std::vector<std::string> operation) {
}

void mulOperationFunctionForSecondPass(std::vector<std::string> operation) {
}

void divOperationFunctionForSecondPass(std::vector<std::string> operation) {
}

void cmpOperationFunctionForSecondPass(std::vector<std::string> operation) {
}

void andOperationFunctionForSecondPass(std::vector<std::string> operation) {
}

void orOperationFunctionForSecondPass(std::vector<std::string> operation) {
}

void notOperationFunctionForSecondPass(std::vector<std::string> operation) {
}

void testOperationFunctionForSecondPass(std::vector<std::string> operation) {
}

void ldrOperationFunctionForSecondPass(std::vector<std::string> operation) {
}

void strOperationFunctionForSecondPass(std::vector<std::string> operation) {
}

void callOperationFunctionForSecondPass(std::vector<std::string> operation) {
}

void inOperationFunctionForSecondPass(std::vector<std::string> operation) {
}

void outOperationFunctionForSecondPass(std::vector<std::string> operation) {
}

void movOperationFunctionForSecondPass(std::vector<std::string> operation) {
}

void shrOperationFunctionForSecondPass(std::vector<std::string> operation) {
}

void shlOperationFunctionForSecondPass(std::vector<std::string> operation) {
}

void ldchOperationFunctionForSecondPass(std::vector<std::string> operation) {
}

void ldclOperationFunctionForSecondPass(std::vector<std::string> operation) {
}
