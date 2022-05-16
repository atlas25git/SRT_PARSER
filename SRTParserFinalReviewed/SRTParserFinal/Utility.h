#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <unordered_map>
#include "EndOfLine.h"
using namespace std;

inline vector<string> &Split(const string &s, char delim, vector<string> &elems) {
	stringstream ss(s);
	string element;

	while (getline(ss, element, delim)) {
		elems.push_back(element);
	}
	return elems;
}

inline string ParseHTML(string output)
{
	int pairCount = 0;
	for (char& c : output) 
	{
		if (c == '<')
		{
			pairCount++;
			c = '#';
		}

		else
		{
			if (pairCount != 0)
			{
				if (c != '>')
					c = '#';

				else if (c == '>')
				{
					c = '#';
					pairCount--;
				}
			}
		}
	}
	output.erase(remove(output.begin(), output.end(), '#'), output.end());

	size_t x = output.find((NEWLINE));
	while (x != string::npos)
	{
		output.erase(x, NEWLINESZ);
		x = output.find(NEWLINE);

	}
	return output;
}