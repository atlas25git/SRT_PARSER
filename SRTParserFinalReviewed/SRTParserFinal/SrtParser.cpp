#include "SrtParser.h"
//#include "SubtitleElement.h"
CSrtParser::CSrtParser(void)
{
}


void CSrtParser::Parse(string fileName)      //srt parser
{

	ifstream infile(fileName);
	string line, start, end, completeLine = "", timeLine = "";
	int subNo, lineNo = 0;

#ifdef MACINTOSH
	while (getline(infile, line, '\r'))
#else
	while (getline(infile, line))
#endif
	{
		if (line.size())
		{
			if (!lineNo)
			{   //storing sequence
				subNo = atoi(line.c_str());
				lineNo++;
				continue;
			}

			if (line.find("-->") != string::npos)
			{
				timeLine += line;

				vector<string> srtTime;
				srtTime = Split(timeLine, ' ', srtTime);
				start = srtTime[0];
				end = srtTime[2];
			}
			else
			{
				if (completeLine != "")
					completeLine = completeLine + NEWLINE + " ";

				completeLine += line;
			}

			lineNo++;
		}
		//parsing complete storing in a struct
		else
		{
			lineNo = 0;
			//dynamically allocating

			string chk = NEWLINE; chk = chk + " ";
			if(completeLine != chk)
				m_SubtitlesCollection.push_back(new CSubtitleElement(subNo, start, end, completeLine));
			completeLine = timeLine = "";
		}

		if (infile.eof())    //insert last remaining subtitle
		{
			m_SubtitlesCollection.push_back(new CSubtitleElement(subNo, start, end, completeLine));
		}
	}
}

CSrtParser::CSrtParser(string fileName)
{
	m_sFilename = fileName;
	Parse(fileName);
}

CSrtParser::~CSrtParser(void)
{
	for (int i = 0; i != m_SubtitlesCollection.size(); ++i)
	{
		if (m_SubtitlesCollection[i])
			delete m_SubtitlesCollection[i];
	}
}
