#include "TextParser.h"
#include "CounterManager.h"

/*
	takes an unedited chapter and evaulates all offical sytex with correct values.

*/
std::string TextParser::ParseText(std::string unParse)
{
	int stringPos = 0;
	std::string temp = "a";

	while (stringPos < unParse.length)
	{
		switch (unParse.at(stringPos))
		{
		case '[': readValue(&unParse, stringPos + 1);
			break;
		case '|': 
			break;
		case '#':
			break;
		case '~':
			break;
		default:
		}

		stringPos++;
	}
	return "this should be a Parsed string";
}



void TextParser::readValue(std::string* unParse, int stringPos)
{
	int offset = 1;
	std::string variable = "";
	while (unParse->at(stringPos + offset) != ']')
	{
		variable += unParse->at(stringPos + offset); 
		offset++;
	}
	if (counters.check_number_counter(variable))
	{
		unParse->replace(stringPos, offset, std::to_string(counters.get_number_counter(variable))); //checks to see if the variable exists in the number map
																									//Number variables will always take precidence over string variables
	}
	else if (counters.check_string_counter(variable))
	{
		unParse->replace(stringPos, offset, counters.get_string_counter(variable)); //If a number variable is not found in the map, then the string map is checked
	}
	else
	{
		unParse->replace(stringPos, offset, "variable : " + variable + " not found "); //Finally, if this variable is not found in the string counter map then you get this error message
	}
}





	





