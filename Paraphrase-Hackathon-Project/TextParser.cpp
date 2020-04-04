#include "TextParser.h"

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
		case '[':   temp = readValue(&unParse, stringPos + 1);
					

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



std::string readValue(std::string* unParse, int stringPos)
{
	int offset = 1;
	std::string variable = "";
	while (unParse->at(stringPos + offset) != ']')
	{
		variable += unParse->at(stringPos + offset);
		offset++;
	}

	/*if (variable is a string)
	{
		return check_text_counter(variable)
	}
	else if (variable is a int)
	{
		return check_number_counter(variable)
	}
	else
	{

	*/
	unParse->replace(stringPos, offset, "Variable");
	// }
}





	





