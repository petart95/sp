#include "ProcessString.h"

#include <sstream>
#include <iterator>
#include <cstring>
#include <algorithm>

struct tokens : std::ctype<char> {
    tokens(std::string characterSet) : std::ctype<char>(get_table(characterSet)) {}

    static std::ctype_base::mask const* get_table(std::string characterSet) {
	typedef std::ctype<char> cctype;
	static const cctype::mask *const_rc= cctype::classic_table();

	static cctype::mask rc[cctype::table_size];
	std::memcpy(rc, const_rc, cctype::table_size * sizeof(cctype::mask));

	for(int i = 0; i < characterSet.length(); i++) {
		rc[characterSet[i]] = std::ctype_base::space;
	}

	return &rc[0];
    }
};

std::vector<std::string> splitStringWhitCharacterSet(std::string stringToSplit, std::string characterSet) {
	std::stringstream stringStream(stringToSplit);

	stringStream.imbue(std::locale(std::locale(), new tokens(characterSet)));

	std::istream_iterator<std::string> begin(stringStream), end;

	return 	std::vector<std::string>(begin, end);
}

bool isIntager(std::string s) {
    return s.find_first_not_of("0123456789") == std::string::npos;
}

int toIntager(std::string s) {
    return atoi(s.c_str());
}

std::string toUpper(std::string s) {
    std::transform(s.begin(), s.end(), s.begin(), toupper);
    
    return s;
}
