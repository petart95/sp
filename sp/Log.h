/*
 * log.h
 *
 *  Created on: May 18, 2016
 *      Author: OS1
 */

#ifndef LOG_H_
#define LOG_H_

#define LOG

#include <stdio.h>
#include <stdarg.h>
#include <string>

#ifdef LOGFILE
#define LOG
#endif

#ifdef LOG

extern FILE* logFile;
extern volatile bool logging;

void vlog(const char* format, va_list &arglist);

#endif

inline void initLog() {
	#ifdef LOGFILE
	logFile = fopen(LOGFILE, "w");
	#ifdef TIMER_LOGFILE
	timerLogFile = fopen(TIMER_LOGFILE, "w");
	#endif
	#endif
}

inline void closeLog() {
	#ifdef LOGFILE
	fclose(logFile);
	#ifdef TIMER_LOGFILE
	fclose(timerLogFile);
	#endif
	#endif
}

inline void log(const char* format, ...) {
	#ifdef LOG
	va_list args;
	va_start(args, format);
	vlog(format, args);
	va_end(args);
	#endif
}

inline void log(std::string s) {
	log((s + "\n").c_str());
}

#endif /* LOG_H_ */
