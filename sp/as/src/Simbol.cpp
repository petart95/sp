#include "Simbol.h"

#include "as.h"

int Simbol::newID = 0;
int Section::newID = 0;

Simbol::Simbol(std::string _name, int _offset, int _sectionIndex, bool _isDefined, bool _isGlobal) 
: name(_name), offset(_offset), sectionIndex(_sectionIndex), isGlobal(_isGlobal), isDefined(_isDefined), id(newID++) {
	simbolTabel.push_back(*this);
} 
