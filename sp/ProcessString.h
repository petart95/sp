#ifndef PROCESS_STRING_H_
#define PROCESS_STRING_H_

#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <stdlib.h>

std::vector<std::string> splitStringWhitCharacterSet (std::string stringToSplit, std::string characterSet);

template < typename T > std::string toString(const T& n ) {
    std::ostringstream stm ;
    stm << n ;
    return stm.str() ;
}


template< typename T > std::string toHexadecimal( T i ) {
    std::stringstream stream;
    //stream << "0x"<< std::setfill ('0') << std::setw(sizeof(T)*2)<< std::hex << i;
    stream << std::hex << i;
    return stream.str();
}

bool isIntager(std::string s);

int toIntager(std::string s);

std::string toUpper(std::string s);

#endif /* PROCESS_STRING_H_ */
