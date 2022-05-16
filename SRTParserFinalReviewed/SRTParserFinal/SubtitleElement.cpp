#include "SubtitleElement.h"


CSubtitleElement::CSubtitleElement(void)
{
}


CSubtitleElement::CSubtitleElement(int subNo, string startTime, string endTime, string plainText,
	string pos)
{
	this->m_nStartTime = m_nTimeMSec(startTime);
	this->m_nEndTime = m_nTimeMSec(endTime);
	this->m_sPlainText = plainText;

	m_nSequence = subNo;
	m_sStartTimeString = startTime;
	m_sEndTimeString = endTime;
	m_sPosition = pos;
	ExtractInfo();
}

long int CSubtitleElement::m_nTimeMSec(string value)
{
	vector<string> t, secs;
	int hours = 0, mins = 0, seconds = 0, milliseconds = 0;

	t = Split(value, ':', t);
	hours = atoi(t[0].c_str());
	mins = atoi(t[1].c_str());

	secs = Split(t[2], ',', secs);
	seconds = atoi(secs[0].c_str());
	milliseconds = atoi(secs[1].c_str());

	return hours * 3600000 + mins * 60000 + seconds * 1000 + milliseconds;
}

std::vector<CFormattedText *> CSubtitleElement::GetFormattedText() const
{
	return m_FormattedTextCollection;
}

long int CSubtitleElement::GetStartTime() const
{
	return m_nStartTime;
}
long int CSubtitleElement::GetEndTime() const
{
	return m_nEndTime;
}

string CSubtitleElement::GetText() const
{
	return m_sPlainText;
}

int CSubtitleElement::GetSubNo() const
{
	return m_nSequence;
}
string CSubtitleElement::GetPos() const
{
	return m_sPosition;
}

void CSubtitleElement::SetPosition(string& output)
{
	size_t idx = output.find("{\\an");

	if (idx != string::npos)
	{
		// cout<<idx<<"\n";
		int posNO = m_sPlainText[idx + 4] - '0';
		output.erase(idx, 6);
		switch (posNO)
		{
		case 1:
		{
			this->m_sPosition = "Bottom-left";
			break;
		}
		case 2:
		{
			this->m_sPosition = "Bottom-center";
			break;
		}
		case 3:
		{
			this->m_sPosition = "Bottom-right";
			break;
		}
		case 4:
		{
			this->m_sPosition = "Middle-left";
			break;
		}
		case 5:
		{
			this->m_sPosition = "Middle-center";
			break;
		}
		case 6:
		{
			this->m_sPosition = "Middle-right";
			break;
		}
		case 7:
		{
			this->m_sPosition = "Top-left";
			break;
		}
		case 8:
		{
			this->m_sPosition = "Top-center";
			break;
		}
		case 9:
		{
			this->m_sPosition = "Top-right";
			break;
		}
		}

	}
}
void CSubtitleElement :: FillFormattedTextCollection(string& output)
{
	int start = (int)1e9 + 7, end = 0, prevStart, prevEnd;
	int cnt = 0, tokCount = 0;
	for (int i = 0; i < (int)output.size() - 1; i++)
	{
		if (output[i] == '<' && output[i + 1] != '/')
		{
			prevStart = start;
			start = min(start, i);
			cnt++;
		}
		else if (output[i] == '<' && output[i + 1] == '/')
		{
			prevEnd = end;
			end = i;
			cnt--;
		}

		if (!cnt && start != 1e9 + 7)
		{
			if (!tokCount && start)
			{
				if (start != 0)
					m_FormattedTextCollection.push_back(new CFormattedText(output.substr(0, start), start));

			}
			else
			{
				if (start - prevEnd != 0)
					m_FormattedTextCollection.push_back(new CFormattedText(output.substr(prevEnd, start - prevEnd), prevEnd));
			}

			if (end - start != 0)
				m_FormattedTextCollection.push_back(new CFormattedText(output.substr(start, end - start), start));
			cnt = 0, start = (int)1e9 + 7;
			tokCount++;
		}
	}

	sort(m_FormattedTextCollection.begin(), m_FormattedTextCollection.end(), [](CFormattedText* a, CFormattedText* b)
	{
		return a->m_nIdx < b->m_nIdx;
	});
}
void CSubtitleElement::ExtractInfo()   
{
	string output = m_sPlainText;

	SetPosition(output);
	FillFormattedTextCollection(output);
	
	output = ParseHTML(output);
	this->m_sPlainText = output;
}


CSubtitleElement::~CSubtitleElement(void)
{
	for (auto x : m_FormattedTextCollection)
		delete x;
}
