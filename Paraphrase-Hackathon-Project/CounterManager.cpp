#include <string>
#include <map>
#include <fstream>
#include <iostream>
#include "CounterManager.h"


CounterManager::CounterManager()
{
}

CounterManager::~CounterManager()
{
}

bool CounterManager::check_number_counter(std::string name) //returns true if this counter already exists
{
	if (number_counters.find(name) == number_counters.end())
		return false;
	else
		return true;
}
bool CounterManager::check_string_counter(std::string name) //returns true if this counter already exists
{
	if (string_counters.find(name) == string_counters.end())
		return false;
	else
		return true;
}
void CounterManager::number_counter_equals(std::string name, int value) //sets a number counter to a value if it already exists, creates a new counter if it does not
{
	number_counters.insert_or_assign(name, value);
}
void CounterManager::number_counter_add(std::string name, int value) //adds to a number counter if it already exists, creates new counter if it does not
{
	if (check_number_counter(name))
		number_counters[name] += value;
	else
		number_counters.insert(std::make_pair(name, value));
}
void CounterManager::number_counter_subtract(std::string name, int value) //subtracts from a number counter if it already exists, creates a new counter if it does not
{
	if (check_number_counter(name))
		number_counters[name] -= value;
	else
		number_counters.insert(std::make_pair(name, -1 * value));
}

void CounterManager::number_counter_multiply(std::string name, int value) //multiplies a number counter that already exists, creates a new number counter at 0 if it does not
{
	if (check_number_counter(name))
		number_counters[name] *= value;
	else
		number_counters.insert(std::make_pair(name, 0));
}

void CounterManager::number_counter_divide(std::string name, int value) //divies a number counter that already exists, assumes you're dividing by 1 if you accidentally divide by 0, creates a new counter at 0 if it does not 
{
	if (value == 0)
		value = 1;
	if (check_number_counter(name))
		number_counters[name] /= value;
	else
		number_counters.insert(std::make_pair(name, 0));

}

int CounterManager::get_number_counter(std::string name) //gives value of a tracked counter, returns 0 if such a counter does not exist
{
	if (check_number_counter(name))
		return number_counters[name];
	else 
		return 0;
}
std::string CounterManager::get_string_counter(std::string name) //gives the value of a tracked string counter, returns what you thought the key was if that counter doesn't exist
{
	if (check_string_counter(name))
		return string_counters[name];
	else
		return name;
}
void CounterManager::set_string_counter(std::string name, std::string value) //sets the value of a tracked string if it already exists,
{
	string_counters.insert_or_assign(name, value);
}


bool CounterManager::isRightType(std::string filePath) //Checks to see if it's a txt or not
{

	return (filePath.substr(filePath.length() - 4) == ".txt" ? true : false); //returns true if it's a .txt


}

std::string CounterManager::readFile(std::string file)
{
	const std::string failStmnt = "Sorry, unable to open file";
	std::ifstream stream;

	if (isRightType(file) == true)
	{
		stream.open(file);
		if (stream.is_open() == true)
		{
			{
				std::string output = "";
				while (stream.good())
				{
					std::getline(stream, output);
				}
				stream.close();
				return output;
			}
		}
		else
		{
			return failStmnt;
		}


	}
	else
	{
		return failStmnt;
	}
}

bool CounterManager::save(std::string file_name, std::string & my_game)
{
	std::ofstream output;
	if (!isRightType(file_name))
	{
		file_name += ".txt";
	}
	output.open(file_name);
	if (output.good())
	{
		//current chapter would go here
		output << my_game << "\n"
			<< "NUMBERS\n";
		for (auto const& x : number_counters)
		{
			output << x.first  // string (key)
				<< " "
				<< x.second
				<< "\n";
		}
		output << "STRINGS\n";
		for (auto const& y : string_counters)
		{
			output << y.first
				<< " "
				<< y.second
				<< "\n";
		}
		output << "DONE";
		output.close();
	}
	else
	{
		return false;
	}
}
bool CounterManager::load(std::string file_name, std::string & my_game)
{

	std::ifstream input;
		std::map<std::string, int> temp_numbers;
	std::map<std::string, std::string> temp_strings;
	int i = 0;
	//Just innitializing all the temp varriables right here
	std::string counter_name, counter_value, current_line, temp_chapter;
	int mode = 0; //0 means you're in numbers mode, 1 means you're in string mode. An Enumerator would have been better here but since it's bianary I didn't see the point. Would have done a bool but we may off in the distant future want to add a third variable type so that's why it's an int oh my god this is a really long comment how are you doing today I'm doing pretty well but I could be better tbh
	if (!isRightType(file_name))
	{
		file_name += ".txt";
	}
	input.open(file_name);
	if (input.is_open())
	{
		getline(input, current_line);
		temp_chapter = current_line;
		getline(input, current_line);
		if (current_line != "NUMBERS")
		{
			std::cout << "This save file is not propperly formatted\n";
			return false;
		}
	}
	else
	{
		return false;
	}

	while (input.good())
	{
		getline(input, current_line);
		if (current_line == "DONE")
		{
			number_counters = temp_numbers;
			string_counters = temp_strings;
			my_game = temp_chapter;
			input.close();
			return true;
		}
		if (mode == 1) //for reading in string variables
		{
			i = 0;
			counter_name = "";
			while (i < current_line.length() and current_line.at(i) != ' ')
			{
				counter_name += current_line.at(i);
			}
			counter_value = "";
			i++;
			while (i < current_line.length())
			{
				counter_value += current_line.at(i);
			}
			temp_strings.insert_or_assign(counter_name, counter_value);
		}
		if (current_line == "STRINGS")
			mode = 1;
		if (mode == 0) //for reading in number variables
		{
			i = 0;
			counter_name = "";
			while (i < current_line.length() and current_line.at(i) != ' ')
			{
				counter_name += current_line.at(i);
				i++;
			}
			std::string counter_value = "";
			i++;
			while (i < current_line.length())
			{
				counter_value += current_line.at(i);
				i++;
			}
			temp_numbers.insert_or_assign(counter_name, std::stoi(counter_value));
		}
	}
}