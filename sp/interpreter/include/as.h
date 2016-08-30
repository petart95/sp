#ifndef AS_H_
#define AS_H_

#include "Log.h"

#include "ProcessString.h"
#include "Simbol.h"

extern std::ifstream in;
extern std::ofstream out;

extern std::vector<Simbol> simbolTabel;
extern std::vector<Section> sectionTabel;
extern int currentSectionIndex;

#endif /* AS_H_ */
