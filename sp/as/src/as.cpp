#include <algorithm>
#include <numeric>

#include "as.h"
#include "ProcessString.h"
#include "Operation.hpp"
#include "OperationFunctions.h"
#include "DirectiveFunctions.h"
#include "Error.h"

std::ifstream in;
std::ofstream out;

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

        Simbol(label, sectionTabel[currentSectionIndex].locationCounter, currentSectionIndex);
        
		line = line.substr(line.find(":") + 1);
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
			ERROR("Directiv: '", split[0], "' not supported");
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
    // Remove label from line
    if(line.find(":") != std::string::npos) {
        line = line.substr(line.find(":") + 1);
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
		} 
	} else {
		Operation operation(split);
		
		// Check if operation valid
		if(operation.isOperationValid()) {
			// Fill in section data.
			sectionTabel[currentSectionIndex].data += operation.createHexRepresentation();
        	} else {
                if(!operation.opcode.isValid) {
                    ERROR("Opcode for operation: '", line, "' is invalid");
                } else {
                    ERROR("Operands for operationl: ' " , line, "' are invalid");
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
    out << Simbol::tabelRows();
    for(int i = 0; i < Simbol::tabel.size(); i++) {
        out << Simbol::tabel[i];
	}

	// Output section tabel
    for(int i = 0; i < Section::tabel.size(); i++) {
        out << "\n" << Section::tabel[i];
	}	

	// Close
	closeLog();

	in.close();
	out.close();

	return 0;
}
