#pragma once
#include "SubtitleElement.h"

class CSubtitleParser
{
protected:
	vector<CSubtitleElement*> m_SubtitlesCollection;              
	string m_sFilename;                              
	virtual void Parse(string fileName) = 0;

public:
	vector<CSubtitleElement*> GetSubtitles(); 
	CSubtitleParser(void);
	virtual ~CSubtitleParser(void);
};
