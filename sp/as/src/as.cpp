#include <algorithm>

#include "as.h"
#include "ProcessString.h"
#include "Operation.hpp"
#include "OperationFunctions.h"
#include "DirectiveFunctions.h"

std::ifstream in;
std::ofstream out;

std::vector<Simbol> simbolTabel;
std::vector<Section> sectionTabel;
int currentSectionIndex = 0;

/**
 * @brief Opens all files.
 *
 * @discussion Open the input and the output file.
 *             The output file name is created by
 *             replacing the extension of the input file by .s. 
 *
 * @param inFile Name of the input file.
 */
void openFiles(std::string inFile) {
	// Open input file
	in.open(inFile.c_str(), std::ifstream::in);

	// Create output file name
	std::string outFile = inFile + ".o";
	if(inFile.find(".") != std::string::npos) {
		outFile = inFile.substr(0, inFile.find(".")) + ".o";
	}

	// Open output file
	out.open(outFile.c_str(), std::ifstream::out);
}

/**
 * @brief Initializes as with given arguments.
 *
 * @discussion Initalizes log and funstions for first pass,
 *             checks usage and opens the files. 
 */
void init(int argc, char** argv) {
	// Initalize log
	initLog();

	// Check usage
	if(argc != 2) {
		printf("Usage: as [file]\n");
		exit(0);
	}

	// Open files
	openFiles(std::string(argv[1]));

	// Initlize functions for first pass
	setOperationFunctionsForFirstPass();
	setDirectivFunctionsForFirstPass();
}

/**
 * @brief Initializes as for second pass.
 *
 * @discussion Initalizes funstions for second pass and
 *             resets location counters for all sections.
 */
void initForSeconPass() {
	// Return to the begining of the file
	in.clear();
	in.seekg (0, std::ios::beg);

	// Initlize functions for second pass
	setOperationFunctionsForSecondPass();
	setDirectivFunctionsForSecondPass();

	// Initalize data for second pass
	isExitFlagSet = false;

	currentSectionIndex = 0;
	
	for(int i = 0; i < sectionTabel.size(); i++) {
		sectionTabel[i].locationCounter = 0;
	}
}

/**
 * @brief Removes comments form a line.
 *
 * @discussion There are two types of supported comments:
 *                 1) @  single line comment
 *                 2) // single line comment
 *
 * @param line The line to be procssed.
 *
 * @return The line without comments.
 */
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

/**
 * @brief Process line for first pass.
 *
 * @discussion Main purpos of the first pass
 *             is to fill the simbol tabel.
 *
 *             Every line is first checked for a label.
 *             Label is a part of the string untile ':'.
 *             Afther this we check for directives
 *             and execute the apropriate function
 *             for the found directive.
 *
 * @param line The line to be procssed.
 */
void processLineFirstPass(std::string line) {
	// Check line for label
	if(line.find(":") != std::string::npos) {
		std::string label = line.substr(0, line.find(":"));

		line = line.substr(line.find(":") + 1);

		Simbol(label, sectionTabel[currentSectionIndex].locationCounter, currentSectionIndex);
	}

	// Split string
	std::vector<std::string> split = splitStringWhitCharacterSet(line, " ,");

	if(split.size() == 0) {
		return;
	}

	// Check line for directives
	if(split[0].find(".") != std::string::npos) {
		// Get directiv name
		int numberOfDots = std::count(split[0].begin(), split[0].end(), '.');
		std::string directiv(split[0]);
		if(numberOfDots > 1) {
			directiv = directiv.substr(0, directiv.find_last_of('.'));
		}

		// Check if directive is supported
		if(isDirectivSupported(directiv)) {
			(*handelDirectiv[directiv])(split);
		} else {
			log("***ERORR*** Directiv: " + split[0] + " not supported");
		}
	} else {
  		// Increas location counter by operation size 
		// All operation have size 4.
		sectionTabel[currentSectionIndex].locationCounter += 4;

		// TODO Pseudo operation ldc has operation size 8.
	}
}

/**
 * @brief Process line for second pass.
 *
 * @discussion Main purpos of the second pass
 *             is to fill the section data.
 *
 *             Check for directives and execute
 *             the apropriate function for the found directive.
 *             Create operation hexcode and
 *             fiil in the current section.
 *
 * @param line The line to be procssed.
 */
void processLineSecondPass(std::string line) {
	// Split string
	std::vector<std::string> split = splitStringWhitCharacterSet(line, " ,");

	if(split.size() == 0) {
		return;
	}

	// Check line for directives
	if(split[0].find(".") != std::string::npos) {
		// Get directiv name
		int numberOfDots = std::count(split[0].begin(), split[0].end(), '.');
		std::string directiv(split[0]);
		if(numberOfDots > 1) {
			directiv = directiv.substr(0, directiv.find_last_of('.'));
		}

		// Check if directive is supported
		if(isDirectivSupported(directiv)) {
			(*handelDirectiv[directiv])(split);
		} 
	} else {
		Operation operation(split);
		
		// Check if operation valid
		if(operation.isOperationValid()) {
			// Fill in section data.
			sectionTabel[currentSectionIndex].data += operation.createHexRepresentation();
        	} else {
            		if(!operation.opcode.isValid) {
                		log("***ERROR*** Opcode for operation:" + line + ", is invalid");
       		     	} else {
                		log("***ERROR*** Operands for operationl: " + line + ", are invalid");
            		}
        	}

  		// Increas location counter by operation size 
		// All operation have size 4.
		sectionTabel[currentSectionIndex].locationCounter += 4;

		// TODO Pseudo operation ldc has operation size 8.
	}
}

int main(int argc, char** argv) {
	// Initalize as for first pass
	init(argc, argv);
	
	std::string line;
	
	// First pass	
	while (getline(in, line) && !isExitFlagSet) {
		processLineFirstPass(removeCommentsFromLine(line));
	}

	// Initalize as for second pass
	initForSeconPass();

	// Second pass
	while (getline(in, line) && !isExitFlagSet) {
		processLineSecondPass(removeCommentsFromLine(line));
	}

	// Output simbol tabel
	out << "# Tabela simbola\n";
	out << "# ";
	out << std::left << std::setw(4) << std::setfill(' ') << "ID";
	out << std::left << std::setw(15) << std::setfill(' ') << "Name";
	out << std::left << std::setw(9) << std::setfill(' ') << "Offset";
	out << std::left << std::setw(11) << std::setfill(' ') << "Section ID";
	out << std::left << std::setw(13) << std::setfill(' ') << "Global/Local";
	out << std::left << std::setw(18) << std::setfill(' ') << "Defined/Undefnded";
	out << "\n";
	for(int i = 0; i < simbolTabel.size(); i++) {
		// Output simbol
		out << "  ";
		out << std::left << std::setw(4) << std::setfill(' ') << simbolTabel[i].id;
		out << std::left << std::setw(15) << std::setfill(' ') << simbolTabel[i].name;
		out << std::left << std::setw(9) << std::setfill(' ') << toHexadecimal(simbolTabel[i].offset, 8);
		out << std::left << std::setw(11) << std::setfill(' ') << simbolTabel[i].sectionIndex;
		out << std::left << std::setw(13) << std::setfill(' ') << (simbolTabel[i].isGlobal ? "Global" : "Local");
		out << std::left << std::setw(18) << std::setfill(' ') << (simbolTabel[i].isDefined ? "Defined" : "Undefnded");
		out << "\n";
	}

	// Output section tabel
	for(int i = 0; i < sectionTabel.size(); i++) {
		// Output section
		out << "\n";
		out << "# " << sectionTabel[i].name << "\n";
		out << sectionTabel[i].data << "\n";
		out << "\n";

		// Output section realocation tabel
		out << "# .ret" << sectionTabel[i].name << "\n";
		out << "# ";
		out << std::left << std::setw(9) << std::setfill(' ') << "Offset";
		out << std::left << std::setw(20) << std::setfill(' ') << "Type";
		out << std::left << std::setw(4) << std::setfill(' ') << "Simbol ID";
		out << "\n";
		out << sectionTabel[i].realocation;
	}	

	// Close
	closeLog();

	in.close();
	out.close();

	return 0;
}
