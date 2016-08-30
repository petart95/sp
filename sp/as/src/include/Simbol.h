#ifndef SIMBOL_H_
#define SIMBOL_H_

#include <iostream>
#include <string>
#include <vector>

struct Simbol {
	static int newID;
	
    static std::vector<Simbol> tabel;
    
	int id;
	std::string name;
	int offset;
	int sectionIndex;
	bool isGlobal;
	bool isDefined;

	Simbol(std::string _name, int _offset, int _sectionIndex, bool _isDefined = true, bool _isGlobal = false);
    
    friend std::istream & operator >> (std::istream &in, Simbol &simbol);
    friend std::ostream & operator << (std::ostream &out, const Simbol &simbol);
    
    static std::string tabelRows();
};

#endif /* SIMBOL_H_ */


