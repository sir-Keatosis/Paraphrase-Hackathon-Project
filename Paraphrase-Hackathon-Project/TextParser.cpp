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
		case '[': readValue(&unParse, stringPos);
			break;
		case '|': 
			break;
		case '{': conditional(&unParse, stringPos);
			break;
		case '~':
			break;
		default:
			break;
		}
		stringPos++;
	}
	return unParse;
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
		unParse->replace(stringPos, offset + 1, std::to_string(counters.get_number_counter(variable))); //checks to see if the variable exists in the number map
																									//Number variables will always take precidence over string variables
	}
	else if (counters.check_string_counter(variable))
	{
		unParse->replace(stringPos, offset + 1, counters.get_string_counter(variable)); //If a number variable is not found in the map, then the string map is checked
	}
	else
	{
		unParse->replace(stringPos, offset + 1, "variable : " + variable + " not found "); //Finally, if this variable is not found in the string counter map then you get this error message
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
		case'[':
			readValue(unParse, stringPos + offset);
			break;
		case'{':
			conditional(unParse, stringPos + offset);
		default:
			variable += unParse->at(stringPos + offset);
			break;
		}
		if (!ignore)
		{
			conditional_text += (unParse->at(stringPos + offset));
		}
		offset++;
	}
	if (ignore)
	{
		unParse->replace(stringPos, offset + 1, "");
	}
	else 
	{
		unParse->replace(stringPos, offset + 1, conditional_text);
	}
}

void TextParser::modify_counter(std::string* unParse, int stringPos)
{
	int value_mod = 0;
	bool done = false; //flag is set to true when the calculation is complete
	std::string variable;
	std::string variable2; //for when you're doing variable + variable which is coming later after the base stuff is working
						   //so for now it goes unused
	int offset = 1;
	while (unParse->at(stringPos + offset) != '|')
	{
		switch (unParse->at(stringPos + offset))
		{
		case'=':
			value_mod = 0; //new temporary variable that holds the value that the number counter is being set to
			int iterations = 0; //new temporary variable that can handle multiple digits
			while (unParse->at(stringPos + offset) != ' ' and unParse->at(stringPos + offset) != '|')
			{
				value_mod = (value_mod * iterations) + ((unParse->at(stringPos + offset) - '0')); //gonna need to do some check within stuff here for multi variable maths
				iterations++;
				offset++;
			}
			counters.number_counter_equals(variable, value_mod);
			break;
		case'+':
			value_mod = 0; //new temporary variable that holds the value that the number that is added to the counter
			int iterations = 0; //new temporary variable that can handle multiple digits
			while (unParse->at(stringPos + offset) != ' ' and unParse->at(stringPos + offset) != '|')
			{
				value_mod = (value_mod * iterations) + ((unParse->at(stringPos + offset) - '0')); //gonna need to do some check within stuff here for multi variable maths
				iterations++;
				offset++;
			}
			counters.number_counter_add(variable, value_mod);
			break;
		case'-':
			value_mod = 0; //new temporary variable that holds the value that the number counter is being set to
			int iterations = 0; //new temporary variable that can handle multiple digits
			while (unParse->at(stringPos + offset) != ' ' and unParse->at(stringPos + offset) != '|')
			{
				value_mod = (value_mod * iterations) + ((unParse->at(stringPos + offset) - '0')); //gonna need to do some check within stuff here for multi variable maths
				iterations++;
				offset++;
			}
			counters.number_counter_subtract(variable, value_mod);
			break;
		case'*':
			value_mod = 0; //new temporary variable that holds the value that the number counter is being multiplied by
			int iterations = 0; //new temporary variable that can handle multiple digits
			while (unParse->at(stringPos + offset) != ' ' and unParse->at(stringPos + offset) != '|')
			{
				value_mod = (value_mod * iterations) + ((unParse->at(stringPos + offset) - '0')); //gonna need to do some check within stuff here for multi variable maths
				iterations++;
				offset++;
			}
			counters.number_counter_multiply(variable, value_mod);
			break;
		case'/':
			value_mod = 0; //new temporary variable that holds the value that the number counter is being divided by
			int iterations = 0; //new temporary variable that can handle multiple digits
			while (unParse->at(stringPos + offset) != ' ' and unParse->at(stringPos + offset) != '|')
			{
				value_mod = (value_mod * iterations) + ((unParse->at(stringPos + offset) - '0')); //gonna need to do some check within stuff here for multi variable maths
				iterations++;
				offset++;
			}
			counters.number_counter_divide(variable, value_mod);
			break;
		default:
			variable += unParse->at(stringPos + offset);
			break;
		}
		offset++;
	}
	unParse->replace(stringPos, offset + 1, "");
}

	





