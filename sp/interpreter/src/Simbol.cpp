#include "Simbol.h"

#include "as.h"

int Simbol::newID = 0;
int Section::newID = 0;

Simbol::Simbol(std::string _name, int _offset, int _sectionIndex, bool _isDefined, bool _isGlobal) 
: name(_name), offset(_offset), sectionIndex(_sectionIndex), isGlobal(_isGlobal), isDefined(_isDefined), id(newID++) {
	simbolTabel.push_back(*this);
} 

Simbol::Simbol(std::string line, int sectionOffset) : id(newID++) {
	std::istringstream stm(line);

	std::string lg, ud;

	int _id;

	stm >> _id;
	stm >> name;
	stm >> std::hex >> offset;
	stm >> sectionIndex;
	stm >> lg;
	stm >> ud;

	isGlobal = lg.compare("Local") == 0 ? false : true;
	isDefined = ud.compare("Defined") == 0 ? true : false;

	sectionIndex += sectionOffset;

	simbolTabel.push_back(*this);
}

int Simbol::findeSimbolWithName(std::string name) {
	int simbolTabelSize = simbolTabel.size();

	for(int i = 0; i < simbolTabelSize; i++) {
		if(name.compare(simbolTabel[i].name) == 0) {
			return i;
		}
	}

	return -1;
}

Section::Section(std::ifstream & in, int _simbolOffset)
 : locationCounter(0), id(newID++), simbolOffset(_simbolOffset), absolutPosition(-1) {
	std::string line;

	getline(in, name); // "# .section"
	name = name.substr(2);
	getline(in, data);

	getline(in, line); // "\n"
	getline(in, line); // ".ret.section"
	getline(in, line); // "# Offset   Type                Simbol ID"

	while (getline(in, line) && line.length() > 5) {
		realocation += line + "\n";
	}

	sectionTabel.push_back(*this);
}

int Section::findeSectionWithName(std::string name) {
	int sectionTabelSize = sectionTabel.size();
	for(int i = 0; i < sectionTabelSize; i++) {
		if(name.compare(sectionTabel[i].name) == 0) {
			return i;
		}
	}

	return -1;
}


