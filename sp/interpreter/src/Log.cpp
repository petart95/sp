/*
 * log.cpp
 *
 *  Created on: May 18, 2016
 *      Author: OS1
 */

#include "Log.h"

#ifdef LOGG

FILE* logFile = stdout;
volatile bool logging = false;

void vlog(const char* format, va_list &arglist) {
	if (logging) {
		return;
	}

	logging = true;

	vfprintf(logFile, format, arglist);

	logging = false;
}

#endif // LOG

// Get current date/time, format is YYYY-MM-DD.HH:mm:ss
const std::string currentDateTime() {
    time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&now);
    // Visit http://en.cppreference.com/w/cpp/chrono/c/strftime
    // for more information about date/time format
    strftime(buf, sizeof(buf), "%Y-%m-%d %X", &tstruct);
    
    return buf;
}
