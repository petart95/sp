#include "DirectiveFunctions.h"
#include "as.h"
#include "Log.h"
#include "Expresion.h"

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
		for(int j = 0; j < Simbol::tabel.size(); j++) {
			if(Simbol::tabel[j].name.compare(directiv[i]) == 0) {
				Simbol::tabel[j].isGlobal = false;
			}
		}
	}
}

void externDirectivFunctionForSecondPass(std::vector<std::string> directiv) {
	for(int i = 1; i < directiv.size(); i++) {
		for(int j = 0; j < Simbol::tabel.size(); j++) {
			if(Simbol::tabel[j].name.compare(directiv[i]) == 0) {
				Simbol::tabel[j].isGlobal = true;
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
	for(int i = 1; i < directiv.size(); i++) {
		Expresion expresion(directiv[i]);

		Value expresionEvaluated = expresion.evaluate();

		int result = expresionEvaluated.value;

		expresionEvaluated.addRealocatioDataForType("R_386_8");

		Section::fill(toHexadecimal(result, 2));
	}
}

void wordDirectivFunctionForSecondPass(std::vector<std::string> directiv) {
	for(int i = 1; i < directiv.size(); i++) {
		Expresion expresion(directiv[i]);

		Value expresionEvaluated = expresion.evaluate();

		int result = expresionEvaluated.value;

		expresionEvaluated.addRealocatioDataForType("R_386_16");

		Section::fill(toHexadecimal(result, 4));
	}
}

void longDirectivFunctionForSecondPass(std::vector<std::string> directiv) {
	for(int i = 1; i < directiv.size(); i++) {
		Expresion expresion(directiv[i]);

		Value expresionEvaluated = expresion.evaluate();

		int result = expresionEvaluated.value;

		expresionEvaluated.addRealocatioDataForType("R_386_32");

		Section::fill(toHexadecimal(result, 8));
	}
}

void alignDirectivFunctionForSecondPass(std::vector<std::string> directiv) {
	int alignAmount = 4;

	if(directiv.size() > 1) {
		alignAmount = atoi(directiv[1].c_str());
	}

	if(Section::tabel[Section::current].locationCounter % alignAmount != 0) {
		int offset = alignAmount - Section::tabel[Section::current].locationCounter % alignAmount;
		Section::fill(std::string(2*offset, '0'));
	}
}

void skipDirectivFunctionForSecondPass(std::vector<std::string> directiv) {
	Section::fill(std::string(2*atoi(directiv[1].c_str()), '0'));
}

void endDirectivFunctionForSecondPass(std::vector<std::string> directiv) {
	isExitFlagSet = true;
}

