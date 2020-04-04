#include "TextParser.h"
#include "CounterManager.h"

/*
	takes an unedited chapter and evaulates all offical sytex with correct values.

*/
std::string TextParser::ParseText(std::string unParse)
{
	int stringPos = 0;
	std::string temp = "a";

	while (stringPos < unParse.length())
	{
		switch (unParse.at(stringPos))
		{
		case '[': readValue(&unParse, stringPos + 1);
			break;
		case '|': 
			break;
		case '{': conditional(&unParse, stringPos + 1);
			break;
		case '~':
			break;
		default:
			break;
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

void TextParser::conditional(std::string* unParse, int stringPos)
{
	bool ignore = true;
	int offset = 1;
	std::string variable = "";
	std::string conditional_text = "";
	while (unParse->at(stringPos + offset) != '}')
	{
		switch (unParse->at(stringPos + offset))
		{
		case' ':
			if (counters.check_number_counter(variable))
			{
				if (counters.get_number_counter(variable) > 0)
				{
					ignore = false;
				}
			}
			break;
		case'>':
			if (counters.check_number_counter(variable))
			{
				offset++;
				int check_against=0; //new temporary variable that holds the value that the inequality is checking
				int iterations = 0; //new temporary variable that can handle multiple digits
				while (unParse->at(stringPos + offset) != ' ')
				{
					check_against = (check_against * iterations) + ((unParse->at(stringPos + offset) - '0'));
					iterations++;
					offset++;
				}
				if (counters.get_number_counter(variable) > check_against)
				{
					ignore = false;
				}
			}
			break;
		case'<':
			if (counters.check_number_counter(variable))
			{
				offset++;
				int check_against = 0; //new temporary variable that holds the value that the inequality is checking
				int iterations = 0; //new temporary variable that can handle multiple digits
				while (unParse->at(stringPos + offset) != ' ')
				{
					check_against = (check_against * iterations) + ((unParse->at(stringPos + offset) - '0'));
					iterations++;
					offset++;
				}
				if (counters.get_number_counter(variable) < check_against)
				{
					ignore = false;
				}
			}
			break;
		case'=':
			if (counters.check_number_counter(variable))
			{
				offset++;
				int check_against = 0; //new temporary variable that holds the value that the inequality is checking
				int iterations = 0; //new temporary variable that can handle multiple digits
				while (unParse->at(stringPos + offset) != ' ')
				{
					check_against = (check_against * iterations) + ((unParse->at(stringPos + offset) - '0'));
					iterations++;
					offset++;
				}
				if (counters.get_number_counter(variable) == check_against)
				{
					ignore = false;
				}
			}
			break;
		case'{':
			conditional(unParse, stringPos + offset);
		default:
			variable += unParse->at(stringPos + offset);
		}
		if (!ignore)
		{
			conditional_text += (unParse->at(stringPos + offset));
		}
		offset++;
	}
	if (ignore)
	{
		unParse->replace(stringPos, offset, "");
	}
	else 
	{
		unParse->replace(stringPos, offset, conditional_text);
	}
}





	





