#ifndef EXPRESION_H_
#define EXPRESION_H_

#include <string>
#include <string.h>
#include <cctype>

#include "Argument.h"

struct Expresion {
	std::string expresion;

	Expresion(std::string _expresion) : expresion(_expresion) {}

	Argument evaluate();  
};

Argument expresion(std::string s);

#endif /* PROCESS_STRING_H_ */
