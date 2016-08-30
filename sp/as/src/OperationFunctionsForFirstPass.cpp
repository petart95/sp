#include "OperationFunctions.h"
#include "Log.h"

using namespace std;

map<string, OperationFunctionPointer> handelOperation;

bool isOperationSupported(string operation) {
	return handelOperation.find(operation) != handelOperation.end();
}

void setOperationFunctionsForFirstPass() {
	handelOperation["int"] = &intOperationFunctionForFirstPass;
	handelOperation["add"] = &addOperationFunctionForFirstPass;
	handelOperation["sub"] = &subOperationFunctionForFirstPass;
	handelOperation["mul"] = &mulOperationFunctionForFirstPass;
	handelOperation["div"] = &divOperationFunctionForFirstPass;
	handelOperation["cmp"] = &cmpOperationFunctionForFirstPass;
	handelOperation["and"] = &andOperationFunctionForFirstPass;
	handelOperation["or"] = &orOperationFunctionForFirstPass;
	handelOperation["not"] = &notOperationFunctionForFirstPass;
	handelOperation["test"] = &testOperationFunctionForFirstPass;
	handelOperation["ldr"] = &ldrOperationFunctionForFirstPass;
	handelOperation["str"] = &strOperationFunctionForFirstPass;
	handelOperation["call"] = &callOperationFunctionForFirstPass;
	handelOperation["in"] = &inOperationFunctionForFirstPass;
	handelOperation["out"] = &outOperationFunctionForFirstPass;
	handelOperation["mov"] = &movOperationFunctionForFirstPass;
	handelOperation["shr"] = &shrOperationFunctionForFirstPass;
	handelOperation["shl"] = &shlOperationFunctionForFirstPass;
	handelOperation["ldch"] = &ldchOperationFunctionForFirstPass;
	handelOperation["ldcl"] = &ldclOperationFunctionForFirstPass;
}

//int, add, sub, mul, div, cmp, and, or, not, test, ldr/str, call, in/out, mov/shr/shl, ldch/l

void intOperationFunctionForFirstPass(std::vector<std::string> operation) {
}

void addOperationFunctionForFirstPass(std::vector<std::string> operation) {
}

void subOperationFunctionForFirstPass(std::vector<std::string> operation) {
}

void mulOperationFunctionForFirstPass(std::vector<std::string> operation) {
}

void divOperationFunctionForFirstPass(std::vector<std::string> operation) {
}

void cmpOperationFunctionForFirstPass(std::vector<std::string> operation) {
}

void andOperationFunctionForFirstPass(std::vector<std::string> operation) {
}

void orOperationFunctionForFirstPass(std::vector<std::string> operation) {
}

void notOperationFunctionForFirstPass(std::vector<std::string> operation) {
}

void testOperationFunctionForFirstPass(std::vector<std::string> operation) {
}

void ldrOperationFunctionForFirstPass(std::vector<std::string> operation) {
}

void strOperationFunctionForFirstPass(std::vector<std::string> operation) {
}

void callOperationFunctionForFirstPass(std::vector<std::string> operation) {
}

void inOperationFunctionForFirstPass(std::vector<std::string> operation) {
}

void outOperationFunctionForFirstPass(std::vector<std::string> operation) {
}

void movOperationFunctionForFirstPass(std::vector<std::string> operation) {
}

void shrOperationFunctionForFirstPass(std::vector<std::string> operation) {
}

void shlOperationFunctionForFirstPass(std::vector<std::string> operation) {
}

void ldchOperationFunctionForFirstPass(std::vector<std::string> operation) {
}

void ldclOperationFunctionForFirstPass(std::vector<std::string> operation) {
}

