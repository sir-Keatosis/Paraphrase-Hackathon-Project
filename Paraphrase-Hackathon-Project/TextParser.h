#pragma once

#include <string>
#include "TextParser.h"
#include "CounterManager.h"

class TextParser
{
	public:
		CounterManager counters;
		std::string ParseText(std::string unParse);
		void readValue(std::string* unParse, int stringPos);
	private:
};

