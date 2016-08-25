#include "DirectiveFunctions.h"
#include "as.h"
#include "Log.h"

using namespace std;

map<string, DirectiveFunctionPointer> handelDirectiv;
bool isExitFlagSet = false;

bool isDirectivSupported(string directiv) {
	return handelDirectiv.find(directiv) != handelDirectiv.end();
}

void setDirectivFunctionsForFirstPass() {
	handelDirectiv[".extern"] = &externDirectivFunctionForFirstPass;
	handelDirectiv[".public"] = &publicDirectivFunctionForFirstPass;
	handelDirectiv[".text"] = &textDirectivFunctionForFirstPass;
	handelDirectiv[".data"] = &dataDirectivFunctionForFirstPass;
	handelDirectiv[".bss"] = &bssDirectivFunctionForFirstPass;
	handelDirectiv[".char"] = &charDirectivFunctionForFirstPass;
	handelDirectiv[".word"] = &wordDirectivFunctionForFirstPass;
	handelDirectiv[".long"] = &longDirectivFunctionForFirstPass;
	handelDirectiv[".align"] = &alignDirectivFunctionForFirstPass;
	handelDirectiv[".skip"] = &skipDirectivFunctionForFirstPass;
	handelDirectiv[".end"] = &endDirectivFunctionForFirstPass;
}

// .public, .extern, .text, .data, .bss, .char, .word, .long, .align, .skip, .end

void publicDirectivFunctionForFirstPass(std::vector<std::string> directiv) {
}

void externDirectivFunctionForFirstPass(std::vector<std::string> directiv) {
}

void textDirectivFunctionForFirstPass(std::vector<std::string> directiv) {
	sectionTabel.push_back(Section(directiv[0]));
	currentSectionIndex = sectionTabel.size() - 1;
	simbolTabel.push_back(Simbol(directiv[0], sectionTabel[currentSectionIndex].locationCounter, currentSectionIndex));
}

void dataDirectivFunctionForFirstPass(std::vector<std::string> directiv) {
	sectionTabel.push_back(Section(directiv[0]));
	currentSectionIndex = sectionTabel.size() - 1;
	simbolTabel.push_back(Simbol(directiv[0], sectionTabel[currentSectionIndex].locationCounter, currentSectionIndex));
}

void bssDirectivFunctionForFirstPass(std::vector<std::string> directiv) {
	sectionTabel.push_back(Section(directiv[0]));
	currentSectionIndex = sectionTabel.size() - 1;
	simbolTabel.push_back(Simbol(directiv[0], sectionTabel[currentSectionIndex].locationCounter, currentSectionIndex));
}

void charDirectivFunctionForFirstPass(std::vector<std::string> directiv) {
	sectionTabel[currentSectionIndex].locationCounter += 1 * (directiv.size() - 1);
}

void wordDirectivFunctionForFirstPass(std::vector<std::string> directiv) {
	sectionTabel[currentSectionIndex].locationCounter += 2 * (directiv.size() - 1);
}

void longDirectivFunctionForFirstPass(std::vector<std::string> directiv) {
	sectionTabel[currentSectionIndex].locationCounter += 4 * (directiv.size() - 1);
}

void alignDirectivFunctionForFirstPass(std::vector<std::string> directiv) {
	int alignAmount = 4;

	if(directiv.size() > 1) {
		alignAmount = atoi(directiv[1].c_str());
	}

	if(sectionTabel[currentSectionIndex].locationCounter % alignAmount != 0) {
		sectionTabel[currentSectionIndex].locationCounter += alignAmount - sectionTabel[currentSectionIndex].locationCounter % alignAmount;
	}
}

void skipDirectivFunctionForFirstPass(std::vector<std::string> directiv) {
	sectionTabel[currentSectionIndex].locationCounter += atoi(directiv[1].c_str());
}

void endDirectivFunctionForFirstPass(std::vector<std::string> directiv) {
	isExitFlagSet = true;
}

