#include <algorithm>
#include <cstring>

#include "Simbol.h"
#include "Section.h"

#include "Operation.hpp"
#include "ProcessString.h"

#include "Expresion.h"
#include "Error.h"
#include "Log.h"

#define dotSimbol Simbol::tabel[0]

char* MEM;

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

#define GETMASK(index, size) (((1L << (size)) - 1L) << (index))
#define READFROM(data, index, size) (((data) & GETMASK((index), (size))) >> (index))
#define WRITETO(data, index, size, value) ((data) = ((data) & (~GETMASK((index), (size)))) | ((value) << (index)))

unsigned long long readFromMem(unsigned long long memIndex, unsigned long long size) {
    unsigned long long data = *((long long *)(((long long)MEM) + memIndex));
    unsigned long long index = sizeof(long long)*8 - size;
    
    return READFROM(data, index, size);
}

void writeToMem(unsigned long long memIndex, unsigned long long size, unsigned long long value) {
    unsigned long long data = *((long long *)(((long long)MEM) + memIndex));
    unsigned long long index = sizeof(long long)*8 - size;
    
    value =  WRITETO(data, index, size, value);
    
    *((long long *)(((long long)MEM) + memIndex)) = value;
}

void realoc(Section section, Realocation realoc) {
    long long pos = section.absolutPosition*8 + realoc.bitOffset;
    
    Simbol *simbol = &Simbol::tabel[Simbol::withName(realoc.simbolName)];
    Section *simbolSection = &Section::tabel[Section::withName(simbol->section)];
    
    LOG(toHexadecimal(*((long long *)(((long long) MEM) + pos)), sizeof(long long)*2));
    
    int value = simbol->offset + simbolSection->absolutPosition + readFromMem(pos, realoc.size);
    
    writeToMem(pos, realoc.size, value);
    
    LOG("index ", (sizeof(long long)*8 - (realoc.size)), " size ", realoc.size);
    LOG(toHexadecimal(value, realoc.size/4+1));
    LOG(toHexadecimal(*((long long *)((long long) MEM + pos)), sizeof(long long)*2));
    LOG("------------");
}

void load() {
    // Create Memory
    MEM = (char*) calloc(dotSimbol.offset, sizeof(char));
    
    // Load data into Memory
    int sectionTabelSize = Section::tabel.size();
    
    for(int i = 0; i < sectionTabelSize; i++) {
        for(int j = 0; j < Section::tabel[i].data.length(); j+=2) {
            MEM[Section::tabel[i].absolutPosition + j/2] =
                toIntager("0x" + Section::tabel[i].data.substr(j, 2));
        }
    }
    
    // Realoc
    for(int i = 0; i < sectionTabelSize; i++) {
        int ralocationTabelSize = Section::tabel[i].realocationTabel.size();
        
        for(int j = 0; j < ralocationTabelSize; j++) {
            realoc(Section::tabel[i], Section::tabel[i].realocationTabel[j]);
        }
    }
}

int main(int argc, char** argv) {
	init(argc, argv);
    
	// Link input files
	link(argc, argv);

    // Load data into Memory and realocate
    load();
    
    std::cout << Simbol::tabelRows();
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
    std::cout << "\n";

    // Close
    closeLog();
    closeFile();

	return 0;
}
