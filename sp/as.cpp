#include "as.h"

#include "OperationFunctions.h"
#include "DirectiveFunctions.h"

#include "Operation.hpp"

std::ifstream in;
std::ofstream out;

std::vector<Simbol> simbolTabel;
std::vector<Section> sectionTabel;
int currentSectionIndex = 0;

void openFiles(std::string inFile) {
	in.open(inFile.c_str(), std::ifstream::in);

	std::string outFile = inFile + ".o";
	if(inFile.find(".") != std::string::npos) {
		outFile = inFile.substr(0, inFile.find(".")) + ".o";
	}

	out.open(outFile.c_str(), std::ifstream::out);

	log("Opening input file " + inFile + " and output files " + outFile);
}

void closeFiles() {
	in.close();
	out.close();
}

void init(int argc, char** argv) {
	initLog();

	if(argc != 2) {
		printf("Usage: as [file]\n");
		exit(0);
	}

	openFiles(std::string(argv[1]));

	setOperationFunctionsForFirstPass();
	setDirectivFunctionsForFirstPass();
}

void initForSeconPass() {
	in.clear();
	in.seekg (0, std::ios::beg);

	setOperationFunctionsForSecondPass();
	setDirectivFunctionsForSecondPass();

	isExitFlagSet = false;

	currentSectionIndex = 0;

	for(int i = 0; i < sectionTabel.size(); i++) {
		sectionTabel[i].locationCounter = 0;
	}
}

void close() {
	closeLog();

	closeFiles();
}

std::string removeCommentsFromLine(std::string line) {
	// Check for @ coments
	if(line.find("@") != std::string::npos) {
		line = line.substr(0, line.find("@"));
	}

	// Check for // coments
	if(line.find("//") != std::string::npos) {
		line = line.substr(0, line.find("//"));
	}

	return line;
}

void processLineFirstPass(std::string line) {
	// Check for label
	if(line.find(":") != std::string::npos) {
		std::string label = line.substr(0, line.find(":"));

		line = line.substr(line.find(":") + 1);

		simbolTabel.push_back(Simbol(label, sectionTabel[currentSectionIndex].locationCounter, currentSectionIndex));

		log("Found Label: " + label);
	}

	// Split string
	std::vector<std::string> split = splitStringWhitCharacterSet(line, " ,");

	if(split.size() == 0) {
		return;
	}

	// Cretae simbol tabel
	if(split[0].find(".") != std::string::npos) {
		if(isDirectivSupported(split[0])) {
			log("Found Directiv: " + split[0]);
			(*handelDirectiv[split[0]])(split);
		} else {
			log("Directiv: " + split[0] + " not supported");
		}

	} else {
		if(isOperationSupported(split[0])) {
			log("Found Operation: " + split[0]);
			(*handelOperation[split[0]])(split);
			sectionTabel[currentSectionIndex].locationCounter += 4;
		} else {
			log("Operation: " + split[0] + " not supported");
		}
	}
}

void processLineSecondPass(std::string line) {
	// Check for label
	if(line.find(":") != std::string::npos) {
		line = line.substr(line.find(":") + 1);
	}

	// Split string
	std::vector<std::string> split = splitStringWhitCharacterSet(line, " ,");

	if(split.size() == 0) {
		return;
	}

	// Cretae simbol tabel
	if(split[0].find(".") != std::string::npos) {
		if(isDirectivSupported(split[0])) {
			(*handelDirectiv[split[0]])(split);
		}
	} else {
        Operation operation(split);
		if(operation.isOperationValid()) {
			(*handelOperation[split[0]])(split);
        } else {
            if(!operation.opcode.isValid) {
                log("Opcode " + split[0] + " is invalid");
            } else {
                log("Operands for operation " + split[0] + " are invalid");
            }
        }
	}
}

int main(int argc, char** argv) {
	init(argc, argv);
	
	std::string line;
	
	// First pass	
	log("Starting first pass!\n");
	while (getline(in, line) && !isExitFlagSet) {
		processLineFirstPass(removeCommentsFromLine(line));
	}

	initForSeconPass();

	// Second pass
	log("Starting second pass!\n");
	while (getline(in, line) && !isExitFlagSet) {
		processLineSecondPass(removeCommentsFromLine(line));
	}

	log("Section tabel: name locationCounter\n");
	for(int i = 0; i < sectionTabel.size(); i++) {
		log(toString(i) + ": " + sectionTabel[i].name + " " + toString(sectionTabel[i].locationCounter));
	}	

	log("Simbol tabel: id name offset sectionIndex global\n");
	for(int i = 0; i < simbolTabel.size(); i++) {
		log(toString(simbolTabel[i].id) + ": " + simbolTabel[i].name + " " + toString(simbolTabel[i].offset) + 
		" " + toString(simbolTabel[i].sectionIndex) + (simbolTabel[i].isGlobal ? " global" : " local"));
	}

	close();

	return 0;
}
