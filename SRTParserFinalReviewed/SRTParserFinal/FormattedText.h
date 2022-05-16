#pragma once
#include "Utility.h"
//#include "EndOfLine.h"

class CFormattedText {
	string m_sText, m_sFontColor, m_sBackgroundColor;
	bool m_bIsBold, m_bIsItalic,m_bIsUnderlined;

public:

	int m_nIdx ;
	CFormattedText();
	CFormattedText(string text,int id);
	string GetData();

	virtual ~CFormattedText();
};
