#include "ProcessString.h"
#include "Operation.hpp"
#include "Directive.h"
#include "Section.h"
#include "Simbol.h"
#include "Error.h"
#include "Log.h"


std::ifstream in;
std::ofstream out;

std::string inFile;
int currentLineNumber = 0;
int currentColumNumber = -1;

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
        ERROR("Usage: as [file]");
    }

    // Open files
    inFile = std::string(argv[1]);
    openFiles(inFile);
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
    in.seekg(0, std::ios::beg);
    
    // Initalize data for second pass
    Directive::endFound = false;

    Section::prepareForSecondPass();

    currentLineNumber = 0;
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

        Simbol::createLocal(label);
        
        line = line.substr(line.find(":") + 1);
    }

    // Split string
    std::vector<std::string> split = splitStringWhitCharacterSet(line, " ,");

    if(split.size() == 0) {
        return;
    }

    if(Section::isNameValid(split[0])) {
        // Found  section
        Section(std::string(split[0]));
    } else if(Directive::isNameValid(split[0])) {
        // Found directiv
        (*Directive::functionForFirstPass[split[0]])(split);
    } else {
        // Increas location counter by operation size 
        // All operation have size 4.
        Section::move(4);

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

    if(Section::isNameValid(split[0])) {
        // Found  section
        Section::current = Section::withName(split[0]);
    } else if(Directive::isNameValid(split[0])) {
        // Found directiv
        (*Directive::functionForSecondPass[split[0]])(split);
    } else {
        Operation operation(split);

        // Fill in section data.
        Section::fill(operation.createHexRepresentation());
    }
}

int main(int argc, char** argv) {
    LOG("Open files");
    init(argc, argv);
    
    std::string line;
    
    LOG("First pass");   
    while (getline(in, line) && !Directive::endFound) {
        processLineFirstPass(removeCommentsFromLine(line));
        currentLineNumber++;
    }

    LOG("Initalize assembler for second pass");
    initForSeconPass();

    LOG("Second pass");
    while (getline(in, line) && !Directive::endFound) {
        processLineSecondPass(removeCommentsFromLine(line));
        currentLineNumber++;
    }

    LOG("Output simbol tabel");
    out << Simbol::tabelRows();
    for(int i = 0; i < Simbol::tabel.size(); i++) {
        out << Simbol::tabel[i];
    }

    LOG("Output section tabel");
    for(int i = 0; i < Section::tabel.size(); i++) {
        out << "\n" << Section::tabel[i];
    }    

    LOG("Close files");
    closeLog();

    in.close();
    out.close();

    return 0;
}
