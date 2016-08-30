/*
 * log.cpp
 *
 *  Created on: May 18, 2016
 *      Author: OS1
 */

#include "Log.h"

#ifdef LOG

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
