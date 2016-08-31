#ifndef PROCESS_STRING_H_
#define PROCESS_STRING_H_

#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <cstdlib>

std::vector<std::string> splitStringWhitCharacterSet (std::string stringToSplit, std::string characterSet);

template < typename T > std::string toString(const T& n ) {
    std::ostringstream stm ;
    stm << n ;
    return stm.str() ;
}


template< typename T > std::string toHexadecimal( T i, int size ) {
    std::stringstream stream;
    stream << std::setfill('0') << std::setw(size)<< std::hex << i;
    return stream.str();
}

bool isIntager(std::string s);

int toIntager(std::string s);

std::string toUpper(std::string s);

#endif /* PROCESS_STRING_H_ */
