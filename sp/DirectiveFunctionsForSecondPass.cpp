#include "DirectiveFunctions.h"
#include "as.h"
#include "Log.h"

using namespace std;

void setDirectivFunctionsForSecondPass() {
	handelDirectiv[".extern"] = &externDirectivFunctionForSecondPass;
	handelDirectiv[".public"] = &publicDirectivFunctionForSecondPass;
	handelDirectiv[".text"] = &textDirectivFunctionForSecondPass;
	handelDirectiv[".data"] = &dataDirectivFunctionForSecondPass;
	handelDirectiv[".bss"] = &bssDirectivFunctionForSecondPass;
	handelDirectiv[".char"] = &charDirectivFunctionForSecondPass;
	handelDirectiv[".word"] = &wordDirectivFunctionForSecondPass;
	handelDirectiv[".long"] = &longDirectivFunctionForSecondPass;
	handelDirectiv[".align"] = &alignDirectivFunctionForSecondPass;
	handelDirectiv[".skip"] = &skipDirectivFunctionForSecondPass;
	handelDirectiv[".end"] = &endDirectivFunctionForSecondPass;
}

// .public, .extern, .text, .data, .bss, .char, .word, .long, .align, .skip, .end

void publicDirectivFunctionForSecondPass(std::vector<std::string> directiv) {
	for(int i = 1; i < directiv.size(); i++) {
		for(int j = 0; j < simbolTabel.size(); j++) {
			if(simbolTabel[j].name.compare(directiv[i]) == 0) {
				simbolTabel[j].isGlobal = false;
			}
		}
	}
}

void externDirectivFunctionForSecondPass(std::vector<std::string> directiv) {
	for(int i = 1; i < directiv.size(); i++) {
		for(int j = 0; j < simbolTabel.size(); j++) {
			if(simbolTabel[j].name.compare(directiv[i]) == 0) {
				simbolTabel[j].isGlobal = true;
			}
		}
	}
}

void textDirectivFunctionForSecondPass(std::vector<std::string> directiv) {
}

void dataDirectivFunctionForSecondPass(std::vector<std::string> directiv) {
}

void bssDirectivFunctionForSecondPass(std::vector<std::string> directiv) {
}

void charDirectivFunctionForSecondPass(std::vector<std::string> directiv) {
}

void wordDirectivFunctionForSecondPass(std::vector<std::string> directiv) {
}

void longDirectivFunctionForSecondPass(std::vector<std::string> directiv) {
}

void alignDirectivFunctionForSecondPass(std::vector<std::string> directiv) {
}

void skipDirectivFunctionForSecondPass(std::vector<std::string> directiv) {
}

void endDirectivFunctionForSecondPass(std::vector<std::string> directiv) {
	isExitFlagSet = true;
}

