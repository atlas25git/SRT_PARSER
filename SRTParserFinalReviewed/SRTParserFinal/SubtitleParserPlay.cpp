#include "SubtitleParserPlay.h"
#include "SrtParser.h"

CSubtitleParserPlay::CSubtitleParserPlay(string fileName)
{
	this->m_sFileName = fileName;
}

CSubtitleParser* CSubtitleParserPlay::GetParser()
{
	return new CSrtParser(m_sFileName);              
}

CSubtitleParserPlay::~CSubtitleParserPlay(void)
{
}