#pragma once
#include<map>
class CounterManager
{
public:
	CounterManager();
	~CounterManager();
	bool check_number_counter(std::string name, int value); //returns true if this value already exists
	bool check_text_counter(std::string name, std::string value);
private:
	std::map<std::string, int> number_counters; //all of your number varriable names and values
	std::map<std::string, std::string> text_counters; //all of your text variable names and values
	void create_number_counter(std::string name, int value); //creates a new number value
	void create_sting_counter(std::string name, std::string value); //creates a text value


};

