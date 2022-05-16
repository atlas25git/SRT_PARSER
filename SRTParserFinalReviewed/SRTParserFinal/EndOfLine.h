#pragma once
#define WIN
//#define MACINTOSH

#ifdef WIN
	#define NEWLINE "\\r\\n"
constexpr auto NEWLINESZ = 4;
#elif defined MACINTOSH
	#define NEWLINE "\\r"
constexpr auto NEWLINESZ = 2;
#else
	#define NEWLINE "\\n"
constexpr auto NEWLINESZ = 2;
#endif

