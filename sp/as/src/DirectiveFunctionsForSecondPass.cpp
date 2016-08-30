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
	for(int i = 0; i < sectionTabel.size(); i++) {
		if(directiv[0].compare(sectionTabel[i].name) == 0) {
			currentSectionIndex = i;
			return;
		}
	}
}

void dataDirectivFunctionForSecondPass(std::vector<std::string> directiv) {
	for(int i = 0; i < sectionTabel.size(); i++) {
		if(directiv[0].compare(sectionTabel[i].name) == 0) {
			currentSectionIndex = i;
			return;
		}
	}
}

void bssDirectivFunctionForSecondPass(std::vector<std::string> directiv) {
	for(int i = 0; i < sectionTabel.size(); i++) {
		if(directiv[0].compare(sectionTabel[i].name) == 0) {
			currentSectionIndex = i;
			return;
		}
	}
}

void charDirectivFunctionForSecondPass(std::vector<std::string> directiv) {
	for(int i = 1; i < directiv.size(); i++) {
		Expresion expresion(directiv[i]);

		Value expresionEvaluated = expresion.evaluate();

		int result = expresionEvaluated.value;

		sectionTabel[currentSectionIndex].data += toHexadecimal(result, 2);

		expresionEvaluated.addRealocatioDataForType("R_386_8");

		sectionTabel[currentSectionIndex].locationCounter += 1;
	}
}

void wordDirectivFunctionForSecondPass(std::vector<std::string> directiv) {
	for(int i = 1; i < directiv.size(); i++) {
		Expresion expresion(directiv[i]);

		Value expresionEvaluated = expresion.evaluate();

		int result = expresionEvaluated.value;

		sectionTabel[currentSectionIndex].data += toHexadecimal(result, 4);

		expresionEvaluated.addRealocatioDataForType("R_386_16");

		sectionTabel[currentSectionIndex].locationCounter += 2;
	}
}

void longDirectivFunctionForSecondPass(std::vector<std::string> directiv) {
	for(int i = 1; i < directiv.size(); i++) {
		Expresion expresion(directiv[i]);

		Value expresionEvaluated = expresion.evaluate();

		int result = expresionEvaluated.value;

		sectionTabel[currentSectionIndex].data += toHexadecimal(result, 8);

		expresionEvaluated.addRealocatioDataForType("R_386_32");

		sectionTabel[currentSectionIndex].locationCounter += 4;
	}
}

void alignDirectivFunctionForSecondPass(std::vector<std::string> directiv) {
	int alignAmount = 4;

	if(directiv.size() > 1) {
		alignAmount = atoi(directiv[1].c_str());
	}

	if(sectionTabel[currentSectionIndex].locationCounter % alignAmount != 0) {
		int offset = alignAmount - sectionTabel[currentSectionIndex].locationCounter % alignAmount;
		sectionTabel[currentSectionIndex].data += std::string(2*offset, '0');
		sectionTabel[currentSectionIndex].locationCounter += offset;
	}
}

void skipDirectivFunctionForSecondPass(std::vector<std::string> directiv) {
	sectionTabel[currentSectionIndex].data += std::string(2*atoi(directiv[1].c_str()), '0');
	sectionTabel[currentSectionIndex].locationCounter += atoi(directiv[1].c_str());
}

void endDirectivFunctionForSecondPass(std::vector<std::string> directiv) {
	isExitFlagSet = true;
}

