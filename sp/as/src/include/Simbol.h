#ifndef SIMBOL_H_
#define SIMBOL_H_

#include <string>
#include <vector>

struct Section {
	static int newID;
	
	int id;
	std::string name;
	int locationCounter;
	std::string data;
	std::string realocation;

	Section(std::string _name) : name(_name), locationCounter(0), id(newID++), data(""), realocation("") {}
};

struct Simbol {
	static int newID;
	
	int id;
	std::string name;
	int offset;
	int sectionIndex;
	bool isGlobal;
	bool isDefined;

	Simbol(std::string _name, int _offset, int _sectionIndex, bool _isDefined = true, bool _isGlobal = false); 
};

#endif /* SIMBOL_H_ */


