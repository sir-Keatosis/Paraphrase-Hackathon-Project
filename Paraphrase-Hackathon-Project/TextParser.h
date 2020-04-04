#pragma once

#include <string>
#include "TextParser.h"
#include "CounterManager.h"

class TextParser
{
	public:
		CounterManager counters;
		std::string ParseText(std::string unParse);
		void readValue(std::string* unParse, int stringPos); //unParse is a pointer to the origional string, stringPos says where it was in parsing before it hit this character
		void conditional(std::string* unParse, int stringPos);
		void modify_counter(std::string* unParse, int stringPos);
	private:
};

