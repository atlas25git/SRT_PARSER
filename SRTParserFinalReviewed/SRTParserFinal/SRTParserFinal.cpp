#include "EndOfLine.h"
#include "Utility.h"
#include "pugixml.hpp"
#include "FormattedText.h"
#include "SrtParser.h"
#include "SubtitleElement.h"
#include "SubtitleParser.h"
#include "SubtitleParserPlay.h"
string XML_FILE_PATH = "C:\\Users\\sarthaks\\source\\repos\\SRTParserFinal\\SRTParserFinal";
using namespace pugi;

void createXML(std::vector<CSubtitleElement*> collection,string xmlFileName);

int main(int argc, char *argv[]) {


	if (argc < 1) {
		cout << "Please pass the filename as an argument: ./a.out filename.srt\n";
		return 0;
	}

	cout << "Please input test case no, \n Following is the mapping: " << "\n";
	cout << "test1 -> utf8 -> linux" << "\n";
	cout << "test2 -> ansi -> " << "\n";
	cout << "test1 -> utf8 -> BOM" << "\n";
	cout << "test1 -> utf8 -> MAC \n*Please make sure appropriate header has been defined." << "\n";

	string fname,textFileName,xmlFileName;// = "input.srt";
	//cin >> fname;
	fname = argv[1];
	if (fname == "test1")
	{
		fname = "test1utf8linux.srt";
		textFileName = "outputTest1.txt";
		xmlFileName = "xmlTest1.xml";
	}
	if (fname == "test2")
	{
		fname = "test2ansi.srt";
		textFileName = "outputTest2.txt";
		xmlFileName = "xmlTest2.xml";
	}
	if (fname == "test3")
	{
		fname = "test3utf8bom.srt";
		textFileName = "outputTest3.txt";
		xmlFileName = "xmlTest3.xml";
	}
	if (fname == "test4")
	{
		fname = "test4utf8MAC.srt";
		textFileName = "outputTest4.txt";
		xmlFileName = "xmlTest4.xml";
	}

	std::cout << fname << endl;

	CSubtitleParserPlay *subtitleParserPlay1 = new CSubtitleParserPlay(fname);
	CSubtitleParser *srtParser1 = subtitleParserPlay1->GetParser();

	std::vector<CSubtitleElement*> collection = srtParser1->GetSubtitles();

	ofstream outputFile;
	outputFile.open(textFileName);

	for (CSubtitleElement * obj : collection)
	{
		outputFile << "\n *********Description Starts*****************************" << endl;
		outputFile << "Time in ms: \n";
		outputFile << "Start : " << obj->GetStartTime() << endl;

		outputFile << "End : " << obj->GetEndTime() << endl;

		outputFile << "Text in srt: \n";
		outputFile << "PlainText : " << obj->GetText() << endl;


		outputFile << "FormattedText :" << "\n";
		for (auto x : obj->GetFormattedText())
			if(x->GetData()!="inValid")
			outputFile << "\n" << x->GetData() << "\n";
		if (obj->GetFormattedText().size() == 0)
			outputFile << "\n" << "Text isn't formatted" << "\n";

		outputFile << endl;

		outputFile << "Position of srt Block: ";
		outputFile << obj->GetPos() << endl;

		outputFile << "Sequence no. in srt: ";
		outputFile << obj->GetSubNo() << endl;
		outputFile << "*********Description Ends*******************************" << endl;
	}
	createXML(collection,xmlFileName);
	std::cout << "CheckOut Out.txt file for parsed srt, Thanks.\n";

	return 0;
}

void createXML(std::vector<CSubtitleElement*> collection,string xmlFileName)
{
	//// Generate new XML document within memory
	pugi::xml_document doc;
	//// Alternatively store as shared pointer if tree shall be used for longer
	//// time or multiple client calls:
	std::shared_ptr<pugi::xml_document> spDoc = std::make_shared<pugi::xml_document>();
	//// Generate XML declaration
	auto declarationNode = doc.append_child(pugi::node_declaration);
	declarationNode.append_attribute("version") = "1.0";
	declarationNode.append_attribute("encoding") = "ISO-8859-1";
	declarationNode.append_attribute("standalone") = "yes";
	//// A valid XML doc must contain a single root node of any name
	auto root1s = doc.append_child("SubTitles");
	//// Save XML tree to file.
	//// Remark: second optional param is indent string to be used;
	//// default indentation is tab character.
	string path = XML_FILE_PATH + "\\" + xmlFileName;
	bool saveSucceeded = doc.save_file(path.c_str(), PUGIXML_TEXT("  "));

	pugi::xml_parse_result result = doc.load_file(path.c_str(),
		pugi::parse_default | pugi::parse_declaration);
	if (!result)
	{
		std::cout << "Parse error: " << result.description()
			<< ", character pos= " << result.offset;
	}
	pugi::xml_node root = doc.document_element();

	for (CSubtitleElement * obj : collection)
	{
		string Title = "SubtitleElement";//No: " + to_string(obj->GetSubNo());
		pugi::xml_node nodeChild = root.append_child(Title.c_str());
		nodeChild.append_attribute("SequenceNo") = obj->GetSubNo();
		nodeChild.append_attribute("StartTime") = obj->GetStartTime();
		nodeChild.append_attribute("EndTime") = obj->GetEndTime();
		nodeChild.append_child("PlainText").append_attribute("PlainText") = obj->GetText().c_str();
		pugi::xml_node nodeChildFtexts = nodeChild.append_child("FormattedTexts");
		for (auto x : obj->GetFormattedText())
		{
			string fd;
			string data = x->GetData();

			if (data != "inValid")
				fd += "{" + data + "}";

			if (obj->GetFormattedText().size() == 0)
				fd = "{ Text isn't formatted }";

			if(fd.size())nodeChildFtexts.append_child("FormattedText").append_attribute("Content") = fd.c_str();
		}
		nodeChild.append_child("Position").append_attribute("Position") = obj->GetPos().c_str();

	}
	doc.save_file(path.c_str(), PUGIXML_TEXT("  "));
}