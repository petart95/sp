#ifndef SIMBOL_H_
#define SIMBOL_H_

#include <string>
#include <cstring>
#include <vector>

struct Section {
	static int newID;
	
	std::string name;
	std::string data;
	std::string realocation;

	int id;
	int locationCounter;
	int simbolOffset;
	int absolutPosition;

	Section(std::string _name) : name(_name), locationCounter(0), id(newID++), data(""), realocation(""), absolutPosition(-1) {}
	Section(std::ifstream & in, int simbolOffset);

	static int findeSectionWithName(std::string name);

	bool operator < (const Section& section) const	{
		return (name < section.name);
	}

	bool operator > (const Section& section) const	{
		return (name > section.name);
	}
};

struct Simbol {
	static int newID;
	
	int id;
	std::string name;
	int offset;
	int sectionIndex;
	bool isGlobal;
	bool isDefined;

	Simbol(std::string line, int sectionOffset);
	Simbol(std::string _name, int _offset, int _sectionIndex, bool _isDefined = true, bool _isGlobal = false); 

	static int findeSimbolWithName(std::string name);
};

#endif /* SIMBOL_H_ */


