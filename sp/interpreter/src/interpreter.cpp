#include "as.h"

#include "Simbol.h"

#include "Operation.hpp"
#include "ProcessString.h"

#include "Expresion.h"

#include <algorithm>
#include <cstring>

std::ifstream in;
std::ofstream out;

std::vector<Simbol> simbolTabel;
std::vector<Section> sectionTabel;
int currentSectionIndex = 0;
int currentMemoryPosition = 0;

void openFile(std::string inFile) {
	in.open(inFile.c_str(), std::ifstream::in);
}

void closeFile() {
	in.close();
}

void init(int argc, char** argv) {
	initLog();

	if(argc < 3) {
		printf("Usage: as [format] [file1] [file2] [...]\n");
		exit(0);
	}
}

void close() {
	closeLog();

	closeFile();
}

void parseFile() {
	std::string line;
	
	int sectionOffset = sectionTabel.size();
	int simbolOffset = simbolTabel.size();

	// Ucitavanje tabele simbola
	getline(in, line); // # Tabela simbola
	getline(in, line); // # ID  Name           Offset   Section ID Global/Local Defined/Undefnd
	while (getline(in, line) && line.length() > 5) {
		Simbol(line, sectionOffset);
	}

	while(!in.eof()) {
		Section(in, simbolOffset);
	}
}

void checkSimbolTabel() {
	int simbolTabelSize = simbolTabel.size();

	for(int i = 0; i < simbolTabelSize; i++) {
		int numberOfDefinisions = 0;
		for(int j = 0; j < simbolTabelSize; j++) {
			if(simbolTabel[i].name.compare(simbolTabel[j].name) == 0) {
				if(simbolTabel[j].isDefined) {
					numberOfDefinisions++;
				}

				if(!simbolTabel[i].isDefined && simbolTabel[j].isDefined) {
					simbolTabel[i].offset = simbolTabel[j].offset; 
					simbolTabel[i].sectionIndex = simbolTabel[j].sectionIndex; 
				}
			}
		}

		if(numberOfDefinisions > 1) {
			log("***ERROR*** Multiple definisions of a simbol: " + simbolTabel[i].name);
		} else if(numberOfDefinisions == 0) {
			log("***ERROR*** Undefined simbol: " + simbolTabel[i].name);
		}
	}
}

void parsFormatFile() {
	std::string line;	

	Simbol(".", 0, -1, true, true);
	currentMemoryPosition = simbolTabel.size() - 1;
	int oldPosition = 0;

	while (getline(in, line)) {
		if(line.find("=") != std::string::npos) {
			int simbolIndex = Simbol::findeSimbolWithName(line.substr(0, line.find("=")));
			Expresion expresion(line.substr(line.find("=") + 1));
			if(simbolIndex == -1) {
				Simbol(line.substr(0, line.find("=")), expresion.evaluate().value, -1, true, true);
			} else {
				simbolTabel[simbolIndex].offset = expresion.evaluate().value; 
			}
		} else {
			int sectionIndex = Section::findeSectionWithName(line);
			if(sectionIndex != -1) {
				sectionTabel[sectionIndex].absolutPosition = simbolTabel[currentMemoryPosition].offset;
				simbolTabel[currentMemoryPosition].offset += sectionTabel[sectionIndex].data.length()/2;
			} else {
				log("***ERROR*** Section " + line + " dos not exsist");
			}
		}

		if(oldPosition > simbolTabel[currentMemoryPosition].offset) {
			log("***ERROR*** Current memory position moved backword\n");
		} else {
			oldPosition = simbolTabel[currentMemoryPosition].offset;
		}
	}
}

void calculateSectionAbsolutePositions() {
	int sectionTabelSize = sectionTabel.size();
	for(int i = 0; i < sectionTabelSize; i++) {
		if(sectionTabel[i].absolutPosition == -1) {
			sectionTabel[i].absolutPosition = simbolTabel[currentMemoryPosition].offset; 
			simbolTabel[currentMemoryPosition].offset += sectionTabel[i].data.length()/2;
		}
		log(sectionTabel[i].name + " absolut position " + toString(sectionTabel[i].absolutPosition));
	}
}

int main(int argc, char** argv) {
	init(argc, argv);
	
	// Parse input files
	for(int i = 2; i < argc; i++){
		openFile(argv[i]);
		parseFile();
		closeFile();
	}

	// Pars format file
	openFile(argv[1]);
	parsFormatFile();
	closeFile();

	// Sort sections alphabeticaly
	std::sort(sectionTabel.begin(), sectionTabel.end());

	// Check simbol tabel for multiple definisions and undefined simboles
	checkSimbolTabel();

	// Calculate section absoulte positions
	calculateSectionAbsolutePositions();

	// Load data into memory

	// Realocate data wher necessary

	close();

	return 0;
}
