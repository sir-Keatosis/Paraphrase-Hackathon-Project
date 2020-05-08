#include "TextParser.h"
#include "CounterManager.h"
#include "Portal.h"
#include <string>

//check out Antler

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
			stringPos--;
			break;
		case '#': modify_counter(&unParse, stringPos);
			stringPos--;
			break;
		case '{': conditional(&unParse, stringPos);
			stringPos--;
			stringPos--;
			break;
		case '~':
			MakePortal(&unParse, stringPos);
			stringPos--;
			break;
		case '|':
			string_modify_counter(&unParse, stringPos);
			stringPos--;
		default:
			break;
		}
		stringPos++;
	}
	return unParse;
}

void TextParser::string_modify_counter(std::string* unParse, int stringPos)
{
	bool done = false; //flag is set to true when the calculation is complete
	std::string variable;
	std::string input; //for when you're doing variable + variable which is coming later after the base stuff is working
						   //so for now it goes unused
	int offset = 1;
	while (unParse->at(stringPos + offset) != '|')
	{
		switch (unParse->at(stringPos + offset))
		{
		case'=':
			offset++;
			while (unParse->at(stringPos + offset) != '|')
			{
				input += unParse->at(stringPos + offset);
				offset++;
			}
			if (!readOnly)
			{
				counters.set_string_counter(variable, input);
			}
			break;
		default:
			variable += unParse->at(stringPos + offset);
			offset++;
			break;
		}
	}
	unParse->replace(stringPos - 1, offset + 2, "");
}





void TextParser::MakePortal(std::string* unParse, int stringPos)
{
	int offset = 1;
	std::string fileName = "";
	std::string Text = "";

	while (unParse->at(stringPos + offset) != ' ')
	{
		fileName += unParse->at(stringPos + offset);
		offset++;
	}
	while (unParse->at(stringPos + offset) != '~')
	{
		Text += unParse->at(stringPos + offset);
		offset++;
	}
	
	portals.push_back(*(new Portal(fileName, Text)));
	unParse->replace(stringPos - 1, offset + 2, "");
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
			else //should allow less than conditionals to allways suceed if the counter is undefined 
			{
				offset++;
				int iterations = 0;
				while (unParse->at(stringPos + offset) != ' ')
				{
					iterations++;
					offset++;
				}
				ignore = false;
				
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
			else if (counters.check_string_counter(variable)) //Will only check string counters if a number counter does not already exist
			{
				offset++;
				std::string check_against_string = ""; //new temporary variable that holds the value that the inequality is checking
				while (unParse->at(stringPos + offset) != ' ')
				{
					check_against_string += unParse->at(stringPos+offset);
					offset++;
				}
				if (counters.get_string_counter(variable) == check_against_string)
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
	int iterations = 0;
	int value_mod = 0;
	bool done = false; //flag is set to true when the calculation is complete
	std::string variable;
	std::string variable2; //for when you're doing variable + variable which is coming later after the base stuff is working
						   //so for now it goes unused
	int offset = 1;
	while (unParse->at(stringPos + offset) != '#')
	{
		switch (unParse->at(stringPos + offset))
		{
		case'=':
			offset++;
			value_mod = 0; //new temporary variable that holds the value that the number counter is being set to
			iterations = 0; //new temporary variable that can handle multiple digits
			if (isdigit(unParse->at(stringPos + offset))) //if character after the equals sign is a numeral then do regular modification
			{//                                                                but if not then do multivariable operation
				while (unParse->at(stringPos + offset) != ' ' and unParse->at(stringPos + offset) != '#')
				{
					value_mod = (value_mod * (10 * iterations)) + ((unParse->at(stringPos + offset) - '0')); //gonna need to do some check within stuff here for multi variable maths
					iterations++;
					offset++;
				}
				if (!readOnly)
				{
					counters.number_counter_equals(variable, value_mod);
				}
			}
			else //multi variable operation
			{
				while (unParse->at(stringPos + offset) != '#')
				{
					variable2 += unParse->at(stringPos + offset);
					offset++;
				}
				if (!readOnly)
				{
					if (counters.check_number_counter(variable2))
					{
						counters.number_counter_equals(variable, counters.get_number_counter(variable2));
					}
					else //sets it to zero if the variable does not exist
					{
						counters.number_counter_equals(variable, 0);
					}
				}
			}
			break;
		case'+':
			offset++;
			value_mod = 0; //new temporary variable that holds the value that the number that is added to the counter
			iterations = 0; //new temporary variable that can handle multiple digits
			if (isdigit(unParse->at(stringPos + offset)))
			{
				while (unParse->at(stringPos + offset) != ' ' and unParse->at(stringPos + offset) != '#')
				{
					value_mod = (value_mod * (10 * iterations)) + ((unParse->at(stringPos + offset) - '0')); //gonna need to do some check within stuff here for multi variable maths
					offset++;
					iterations++;
				}
				if (!readOnly)
				{
					counters.number_counter_add(variable, value_mod);
				}
			}
			else //multi variable operation
			{
				while (unParse->at(stringPos + offset) != '#')
				{
					variable2 += unParse->at(stringPos + offset);
					offset++;
				}
				if (!readOnly)
				{
					if (counters.check_number_counter(variable2))
					{
						counters.number_counter_add(variable, counters.get_number_counter(variable2));
					}
					else //sets it to zero if the variable does not exist
					{
						counters.number_counter_add(variable, 0);
					}
				}
			}
			break;
		case'-':
			offset++;
			value_mod = 0; //new temporary variable that holds the value that the number counter is being set to
			iterations = 0; //new temporary variable that can handle multiple digits
			if (isdigit(unParse->at(stringPos + offset)))
			{
				while (unParse->at(stringPos + offset) != ' ' and unParse->at(stringPos + offset) != '#')
				{
					value_mod = (value_mod * (10 * iterations)) + ((unParse->at(stringPos + offset) - '0')); //gonna need to do some check within stuff here for multi variable maths
					iterations++;
					offset++;
				}
				if (!readOnly)
				{
					counters.number_counter_subtract(variable, value_mod);
				}
			}
			else //multi variable operation
			{
				while (unParse->at(stringPos + offset) != '#')
				{
					variable2 += unParse->at(stringPos + offset);
					offset++;
				}
				if (!readOnly)
				{
					if (counters.check_number_counter(variable2))
					{
						counters.number_counter_subtract(variable, counters.get_number_counter(variable2));
					}
					else //sets it to zero if the variable does not exist
					{
						counters.number_counter_subtract(variable, 0);
					}
				}
			}
			break;
		case'*':
			offset++;
			value_mod = 0; //new temporary variable that holds the value that the number counter is being multiplied by
			iterations = 0; //new temporary variable that can handle multiple digits
			if (isdigit(unParse->at(stringPos + offset)))
			{
				while (unParse->at(stringPos + offset) != ' ' and unParse->at(stringPos + offset) != '#')
				{
					value_mod = (value_mod * (10 * iterations)) + ((unParse->at(stringPos + offset) - '0')); //gonna need to do some check within stuff here for multi variable maths
					iterations++;
					offset++;
				}
				if (!readOnly)
				{
					counters.number_counter_multiply(variable, value_mod);
				}
			}
			else //multi variable operation
			{
				while (unParse->at(stringPos + offset) != '#')
				{
					variable2 += unParse->at(stringPos + offset);
					offset++;
				}
				if (!readOnly)
				{
					if (counters.check_number_counter(variable2))
					{
						counters.number_counter_multiply(variable, counters.get_number_counter(variable2));
					}
					else //sets it to zero if the variable does not exist
					{
						counters.number_counter_multiply(variable, 0);
					}
				}
			}
			break;
		case'/':
			offset++;
			value_mod = 0; //new temporary variable that holds the value that the number counter is being divided by
			iterations = 0; //new temporary variable that can handle multiple digits
			if (isdigit(unParse->at(stringPos + offset)))
			{
				while (unParse->at(stringPos + offset) != ' ' and unParse->at(stringPos + offset) != '#')
				{
					value_mod = (value_mod * (10 * iterations)) + ((unParse->at(stringPos + offset) - '0')); //gonna need to do some check within stuff here for multi variable maths
					iterations++;
					offset++;
				}
				if (!readOnly)
				{
					counters.number_counter_divide(variable, value_mod);
				}
			}
			else //multi variable operation
			{
				while (unParse->at(stringPos + offset) != '#')
				{
					variable2 += unParse->at(stringPos + offset);
					offset++;
				}
				if (!readOnly)
				{
					if (counters.check_number_counter(variable2))
					{
						counters.number_counter_divide(variable, counters.get_number_counter(variable2));
					}
					else //sets it to zero if the variable does not exist
					{
						counters.number_counter_divide(variable, 0);
					}
				}
			}
			break;
		case'?': //this is how random number generation works
			offset++;
			value_mod = 0; //new temporary variable that holds the value that the number counter is being divided by
			iterations = 0; //new temporary variable that can handle multiple digits
			if (isdigit(unParse->at(stringPos + offset)))
			{
				while (unParse->at(stringPos + offset) != ' ' and unParse->at(stringPos + offset) != '#')
				{
					value_mod = (value_mod * (10 * iterations)) + ((unParse->at(stringPos + offset) - '0')); //gonna need to do some check within stuff here for multi variable maths
					iterations++;
					offset++;
				}
				if (!readOnly)
				{
					counters.number_counter_equals(variable, rand()%value_mod);
					counters.number_counter_add("random_iterations", 1);
				}
			}
			else //multi variable operation
			{
				while (unParse->at(stringPos + offset) != '#')
				{
					variable2 += unParse->at(stringPos + offset);
					offset++;
				}
				if (!readOnly)
				{
					if (counters.check_number_counter(variable2))
					{
						counters.number_counter_equals(variable, rand()%counters.get_number_counter(variable2));
						counters.number_counter_add("random_iterations", 1);
					}
					else //I am really not sure what to do for a default case here... I guess it will default between 0 and 1
					{
						counters.number_counter_equals(variable, rand()%2); //not super happy with this solution, but we'll have to live with it
						counters.number_counter_add("random_iterations", 1);
					}
				}
			}
			break;
		default:
			variable += unParse->at(stringPos + offset);
			offset++;
			break;
		}
	}
	unParse->replace(stringPos - 1, offset + 2, "");
}
	





