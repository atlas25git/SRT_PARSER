#pragma once
#include "SubtitleParser.h"

class CSubtitleParserPlay
{
private:
	string m_sFileName;
public:
	CSubtitleParserPlay(string fileName);
	CSubtitleParser* GetParser();
	~CSubtitleParserPlay(void);
};