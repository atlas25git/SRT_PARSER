#pragma once
#include "SubtitleParser.h"

class CSrtParser : public CSubtitleParser
{
	void Parse(string fileName);
public:
	CSrtParser(void);
	CSrtParser(string fileName);
	~CSrtParser(void);
};

