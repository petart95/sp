#ifndef SIMBOL_H_
#define SIMBOL_H_

#include <string>
#include <vector>

struct Section {
	struct Data {
		std::string value;
		int offset;

		Data(std::string _value, int _offset) : value(_value), offset(_offset) {}
	};

	std::string name;
	int locationCounter;
	std::vector<Data> data;

	Section(std::string _name) : name(_name), locationCounter(0) {}
};

struct Simbol {
	static int newID;
	
	int id;
	std::string name;
	int offset;
	int sectionIndex;
	bool isGlobal;

	Simbol(std::string _name, int _offset, int _sectionIndex) 
	: name(_name), offset(_offset), sectionIndex(_sectionIndex), isGlobal(false), id(newID++) {}  
};

#endif /* SIMBOL_H_ */


