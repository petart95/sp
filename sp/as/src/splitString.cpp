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
    if(s[0] == '0' && (s[1] == 'x' || s[1] == 'X' || s[1] == 'b' || s[1] == 'B')) {
        s = s.substr(2);
    } 

    return s.find_first_not_of("0123456789") == std::string::npos;
}

int toIntager(std::string s) {
    std::stringstream stringStream(s);

    int result;

    stringStream >> std::setbase(0) >> result;

    return result;
}

std::string toUpper(std::string s) {
    std::transform(s.begin(), s.end(), s.begin(), toupper);
    
    return s;
}

bool contains(std::string s, std::string sub) {
    return s.find(sub) != std::string::npos;
}

bool contains(std::string s, char sub) {
    return s.find(sub) != std::string::npos;
}

std::string trim(const std::string& str,
                 const std::string& whitespace) {
    const int strBegin = str.find_first_not_of(whitespace);
    if (strBegin == std::string::npos)
        return ""; // no content

    const int strEnd = str.find_last_not_of(whitespace);
    const int strRange = strEnd - strBegin + 1;

    return str.substr(strBegin, strRange);
}

std::string reduce(const std::string& str,
                   const std::string& fill,
                   const std::string& whitespace) {
    // trim first
    std::string result = trim(str, whitespace);

    // replace sub ranges
    int beginSpace = result.find_first_of(whitespace);
    while (beginSpace != std::string::npos) {
        const int endSpace = result.find_first_not_of(whitespace, beginSpace);
        const int range = endSpace - beginSpace;

        result.replace(beginSpace, range, fill);

        const int newStart = beginSpace + fill.length();
        beginSpace = result.find_first_of(whitespace, newStart);
    }

    return result;
}

std::string readNthLine(const std::string& filename, int n) {
    std::ifstream in(filename.c_str());

    std::string s;  

    //skip N lines
    for(int i = 0; i < n; ++i) {
        std::getline(in, s);
    }

    std::getline(in,s);

    in.close();

    return s; 
}

std::string repeatNTimes(const std::string& s, int n) {
    std::string res("");  

    for(int i = 0; i < n; ++i) {
        res += s;
    }

    return res;
}

std::string removeCharacterSetFromString(std::string str, std::string charsToRemove) {
   for (int i = 0; i < charsToRemove.length(); i++) {
      str.erase(remove(str.begin(), str.end(), charsToRemove[i]), str.end());
   }

   return str;
}

std::string insertCharEveryNthCharacterOfString(char c, int n, const std::string& s) {
    if (!s.size()) {
        return "";
    }
    
    std::stringstream ss;
    ss << s[0];
    for (int i = 1; i < s.size(); i++) {
        if (i%n == 0) {
            ss << c;
        }
        ss << s[i];
    }
    
    return ss.str();
}
