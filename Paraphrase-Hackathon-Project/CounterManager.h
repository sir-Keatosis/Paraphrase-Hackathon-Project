#pragma once
#include<map>
class CounterManager
{
public:
	CounterManager();
	~CounterManager();
	bool check_number_counter(std::string name); //returns true if this counter already exists
	bool check_string_counter(std::string name); //returns true if this counter already exists
	void number_counter_equals(std::string name, int value); //sets a number counter to a value if it already exists, creates a new counter if it does not
	void number_counter_add(std::string name, int value); //adds to a number counter if it already exists, creates new counter if it does not
	void number_counter_subtract(std::string name, int value); //subtracts from a number counter if it already exists, creates a new counter if it does not
	int get_number_counter(std::string name); //gives value of a tracked counter, returns 0 if such a counter does not exist
	std::string get_string_counter(std::string name); //gives the value of a tracked string counter, returns what you thought the key was if that counter doesn't exist
	std::string set_string_counter(std::string name, std::string value); //sets the value of a tracked string if it already exists, creates a new counter if it does not
private:
	std::map<std::string, int> number_counters; //all of your number varriable names and values
	std::map<std::string, std::string> string_counters; //all of your text variable names and values
	void create_number_counter(std::string name, int value); //creates a new number value
	void create_sting_counter(std::string name, std::string value); //creates a text value
	void set_number_value(std::string name, int value); //changes a value in the number counter map


};

