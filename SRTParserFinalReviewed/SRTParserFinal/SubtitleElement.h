#pragma once
#include "FormattedText.h"

class CSubtitleElement
{
private:
	long int m_nStartTime;                    
	long int m_nEndTime;
	string m_sPlainText;                      
	long int m_nTimeMSec(string value);   
	int m_nSequence;                            
	string m_sPosition;
	string m_sStartTimeString;          
	string m_sEndTimeString;
	vector<CFormattedText*> m_FormattedTextCollection;
	void SetPosition(string& output);
	void FillFormattedTextCollection(string& output);
	void ExtractInfo();

public:

	vector<CFormattedText*> GetFormattedText() const;
	long int GetStartTime() const;          
	long int GetEndTime() const;            
	string GetText() const;            
	int GetSubNo() const;              
	string GetPos() const;             



	CSubtitleElement(void);
	CSubtitleElement(int subNo, string startTime, string endTime, string plainText,
		string position = "Bottom-Center"
	);

	~CSubtitleElement(void);
};