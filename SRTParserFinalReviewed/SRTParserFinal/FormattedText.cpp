#include "FormattedText.h"
//#include "Utility.h"
CFormattedText::CFormattedText()
{	
	this->m_nIdx = (int)1e9 + 7;
	this->m_sText = "";
	this->m_sFontColor = "";
	this->m_bIsBold = 0;
	this->m_bIsItalic = 0;
	this->m_bIsUnderlined = 0;

}

CFormattedText::CFormattedText(string text,int id)
{	
	this->m_nIdx = id;
	int i = 0;
	while (text[i] == ' ')i++;
	text = text.substr(i, text.size() - i);
	if (text.size() == 0)return;
	this->m_sText = text;

	if (this->m_sText[1] == '/' || this->m_sText.substr(0, NEWLINESZ) == NEWLINE)
	{
		this->m_sText = ParseHTML(this->m_sText);
		this->m_sFontColor = "default";
		this->m_sBackgroundColor = "default";
		this->m_bIsBold = 0;
		this->m_bIsItalic = 0;
		this->m_bIsUnderlined = 0;

	}

	else {
		if (this->m_sText.find("<b") != string::npos)
			this->m_bIsBold = 1;
		else this->m_bIsBold = 0;

		if (this->m_sText.find("<i") != string::npos)
			this->m_bIsItalic = 1;
		else this->m_bIsItalic = 0;

		if (this->m_sText.find("<u") != string::npos)
			this->m_bIsUnderlined = 1;
		else this->m_bIsUnderlined = 0;

		if (this->m_sText.find("<font color") != string::npos)
		{
			int idx = (int)this->m_sText.find("<font color");
			// cout<<"FC "<<idx<<" "<<this->text[idx]<<"\n";
			while (this->m_sText[idx] != '"')idx++;
			// cout<<"coC "<<idx<<" "<<this->text[idx+1]<<"\n";
			string ans;
			idx++;
			while (this->m_sText[idx] != '"')
				ans += this->m_sText[idx++];
			this->m_sFontColor = ans;
		}
		else this->m_sFontColor = "default";

		if (this->m_sText.find("<background color") != string::npos)
		{
			int idx = (int)this->m_sText.find("<background color");
			while (this->m_sText[idx] != '"')idx++;
			string ans;
			idx++;
			while (this->m_sText[idx] != '"')
				ans += this->m_sText[idx++];
			this->m_sBackgroundColor = ans;
		}
		else this->m_sBackgroundColor = "default";

		this->m_sText = ParseHTML(text);
	}



};

string CFormattedText::GetData()
{
	string ans = this->m_sText;

	int i = 0;
	if (ans.find(NEWLINE) != string::npos)
		ans.erase(ans.find(NEWLINE),NEWLINESZ);
	string chk = NEWLINE;chk = chk +" ";
	if (ans == NEWLINE || ans == chk || ans == " " )
		return "inValid";
	
	ans += " ";
	ans += "Properties: ";
	ans += "FontColor: " + this->m_sFontColor + " ";
	ans += "BackGroundColor: " + this->m_sBackgroundColor + " ";
	ans += "isBold: ";
	ans += (this->m_bIsBold) ? "Yes" : "No";
	ans += " isItalic: ";
	ans += (this->m_bIsItalic) ? "Yes" : "No";
	ans += " isUnderlined: ";
	ans += (this->m_bIsUnderlined) ? "Yes" : "No";

	return ans;

};

CFormattedText::~CFormattedText()
{

};