#include <algorithm>
#include <cstring>

#include "Simbol.h"
#include "Section.h"

#include "Operation.hpp"
#include "ProcessString.h"

#include "Memory.h"
#include "Expresion.h"
#include "Error.h"
#include "Log.h"

#define dotSimbol Simbol::tabel[0]

std::ifstream in;
std::ofstream out;

std::string inFile;
int currentLineNumber = 0;
int currentColumNumber = -1;

void openFile(std::string inputFile) {
    inFile = inputFile;
	in.open(inputFile.c_str(), std::ifstream::in);
}

void closeFile() {
	in.close();
}

void init(int argc, char** argv) {
    // Initalize log
	initLog();

    // Check usage
	if(argc < 3) {
		ERROR("Usage: as [format] [file1] [file2] [...]");
	}
    
    // Create "." simbol
    Simbol(0, ".", ABSOLUT, true);
}

void parseFormatFile(char* formatFile) {
    // Open format file
    openFile(formatFile);
    
    std::string line;
    
    while (getline(in, line) && !line.empty()) {
        if(contains(line , "=")) {
            // Calculate expresion
            std::string simbolName = line.substr(0, line.find("="));
            Argument exp = expresion(line.substr(line.find("=") + 1));
            
            LOG("'", simbolName, "' = ", exp.value, " + absolut(", exp.simbolName, ")");
            
            if(simbolName == "." && exp.isRelativ()) {
                ERROR("Current memory position can't have relativ value (can't depend on '", BOLD(exp.simbolName),"')");
            } else if(simbolName == "." && exp.value < dotSimbol.offset) {
                ERROR("Current memory position can't be moved backword");
            }
            
            // Update simbol
            Simbol::update(simbolName, exp);
        } else {
            if(Section::withName(line) == -1) {
                ERROR("Section '", BOLD(line), "' dosn't exist");
            }
            
            // Set section absolut position
            Section::tabel[Section::withName(line)].absolutPosition = dotSimbol.offset;
            
            // Move current memory position
            dotSimbol.offset += Section::tabel[Section::withName(line)].data.length()/2;
        }
    }
    
    // Close file
    closeFile();
}

void calculateSectionAbsolutePositions(char* formatFile) {
    // Pars format file
    parseFormatFile(formatFile);
    
    // Sort sections lexicographic
    std::sort(Section::tabel.begin(), Section::tabel.end());
    
    // Calculete section absolut positions
    int sectionTabelSize = Section::tabel.size();
    
    for(int i = 0; i < sectionTabelSize; i++) {
        if(Section::tabel[i].absolutPosition == -1) {
            // Set section absolut position
            Section::tabel[i].absolutPosition = dotSimbol.offset;
            
            // Move current memory position
            dotSimbol.offset += Section::tabel[i].data.length()/2;
        }
    }
}

void loadDataFromInputFile(char* inputFile) {
    // Open file
    openFile(inputFile);
    
    std::string line;
    
    getline(in, line);
    getline(in, line);
    
    // Load simbols
    while (getline(in, line) && !line.empty()) {
        Simbol::read(line);
    }
    
    // Load sections
    while(!in.eof()) {
        Section::read(in);
    }
    
    // Close file
    closeFile();
}

void link(int argc, char** argv) {
    // Load all simbols
    for(int i = 2; i < argc; i++){
        loadDataFromInputFile(argv[i]);
    }
    
    // Calculete section absolut position
    calculateSectionAbsolutePositions(argv[1]);
    
    // Check that all Simbols are defined
    int simbolTabelSize = Simbol::tabel.size();
    
    for(int i = 0; i < simbolTabelSize; i++) {
        if(!Simbol::tabel[i].isDefined()) {
            ERROR("Undefined simbol '", BOLD(Simbol::tabel[i].name), "'");
        }
    }
}

void realoc(Section section, Realocation realoc) {
    long long pos = section.absolutPosition*8 + realoc.bitOffset;
    
    Simbol *simbol = &Simbol::tabel[Simbol::withName(realoc.simbolName)];
    Section *simbolSection = &Section::tabel[Section::withName(simbol->section)];
    
    unsigned long long *data = (unsigned long long *)(((long long)MEM) + pos);
    
    int value = simbol->offset + simbolSection->absolutPosition +
                readFromMem(pos, realoc.size);
    
    writeToMem(pos, realoc.size, value);
}

void load() {
    // Create Memory
    MEM = (ubyte*) calloc(MEMORY_SIZE, sizeof(ubyte));
    memset (MEM, 0, MEMORY_SIZE * sizeof(ubyte));
    
    // Load data into Memory
    int sectionTabelSize = Section::tabel.size();
    
    for(int i = 0; i < sectionTabelSize; i++) {
        for(int j = 0; j < Section::tabel[i].data.length(); j+=2) {
            MEM[Section::tabel[i].absolutPosition + j/2] =
                toIntager("0x" + Section::tabel[i].data.substr(j, 2));
        }
    }
    
    /*std::cout << "# Memomry layout\n";
    
    for(int i = 0; i < dotSimbol.offset; i++) {
        std::cout << toHexadecimal((int)MEM[i], 2) << " ";
    }
    std::cout << "\n";*/
    
    // Realoc
    for(int i = 0; i < sectionTabelSize; i++) {
        int ralocationTabelSize = Section::tabel[i].realocationTabel.size();
        
        for(int j = 0; j < ralocationTabelSize; j++) {
            realoc(Section::tabel[i], Section::tabel[i].realocationTabel[j]);
        }
    }
}

void interpret() {
    struct timespec start, finish;
    double elapsed;

    // staarting postion
    PC = readFromMem(32*0, 32);

    clock_gettime(CLOCK_MONOTONIC, &start);

    while(true) {
        bool correctOperation = Operation::execute();

	// Clock interupt
        clock_gettime(CLOCK_MONOTONIC, &finish);

        elapsed = (finish.tv_sec - start.tv_sec);
        elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;

        if(elapsed > 1 && READFROM(PSW, 31, 1) && READFROM(PSW, 30, 1)) {
            clock_gettime(CLOCK_MONOTONIC, &start);

            push(PSW);
            LR = PC;
            PC = readFromMem(32*1, 32);
            WRITETO(PSW, 31, 1, 0);
        }

        // Bad operation interupt
        if(!correctOperation && READFROM(PSW, 31, 1)) {
            push(PSW);
            LR = PC;
            PC = readFromMem(32*3, 32);
            WRITETO(PSW, 31, 1, 0);
        }

        // Keybord interupt
        char ch = kbhit();
	if(ch != EOF) {
            inputBuffer.push_back(ch);

            if(READFROM(PSW, 31, 1)) {
                push(PSW);
                LR = PC;
                PC = readFromMem(32*3, 32);
                WRITETO(PSW, 31, 1, 0);
            }
        }
    }
}

int main(int argc, char** argv) {
    init(argc, argv);
    
    // Link input files
    link(argc, argv);

    // Load data into Memory and realocate
    load();

    /*std::cout << Simbol::tabelRows();
    for(int i = 0; i < Simbol::tabel.size(); i++) {
        std::cout << Simbol::tabel[i];
    }
    
    for(int i = 0; i < Section::tabel.size(); i++) {
        std::cout << "\n" << Section::tabel[i];
    }
    
    std::cout << "# Memomry layout\n";
    
    for(int i = 0; i < dotSimbol.offset; i++) {
        std::cout << toHexadecimal((int)MEM[i], 2) << " ";
    }
    std::cout << "\n";*/

    // interpret
    interpret();

    // Close
    closeLog();
    closeFile();

    return 0;
}
