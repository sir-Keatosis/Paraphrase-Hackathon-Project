#pragma once
#include<map>
#include <string>

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
	void number_counter_multiply(std::string name, int value); //multiplies a number counter that already exists, creates a new number counter at 0 if it does not
	void number_counter_divide(std::string name, int value); //divies a number counter that already exists, assumes you're dividing by 1 if you accidentally divide by 0, creates a new counter at 0 if it does not 
	int get_number_counter(std::string name); //gives value of a tracked counter, returns 0 if such a counter does not exist
	std::string get_string_counter(std::string name); //gives the value of a tracked string counter, returns what you thought the key was if that counter doesn't exist
	void set_string_counter(std::string name, std::string value); //sets the value of a tracked string if it already exists, creates a new counter if it does not
	bool save(std::string file_name); //used for saving //returns false if the file did not sucessfully save
	bool load(std::string file_name, std::string & my_game); //used for loading from a save file //has the side effect of loading from the save file, returns the loaded chapter to the game manager when called
private:
	std::map<std::string, int> number_counters; //all of your number varriable names and values
	std::map<std::string, std::string> string_counters; //all of your text variable names and values
	bool isRightType(std::string filePath); 
	std::string readFile(std::string file);
	/*
	void create_number_counter(std::string name, int value); //creates a new number value //not nesisary because add and equals can create initizalize a couter
	void create_sting_counter(std::string name, std::string value); //creates a text value //not nessisary because set_string_counter can create and initiailize a counter
	void set_number_value(std::string name, int value); //changes a value in the number counter map //not nessisary because number_counter_equals already does this
	*/


};

