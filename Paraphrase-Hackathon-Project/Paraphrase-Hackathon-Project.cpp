// Paraphrase-Hackathon-Project.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "TextParser.h"
#include "CounterManager.h"
#include "GameManager.h"
#include <cstdlib>
#include <fstream>
#include <string>

void testCounter();
void testTextParser();
std::ifstream stream;
std::string test;

bool isRightType(std::string filePath)
{

	return (filePath.substr(filePath.length() - 4) == ".txt" ? true : false);


}

std::string readFile(std::ifstream& stream, std::string file)
{
	const std::string failStmnt = "Sorry, unable to open file";

	if (isRightType(file) == true)
	{
		stream.open(file);
		if (stream.good() == true)
		{
			{
				std::string output = "";
				while (!stream.eof())
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

int main()
{
	GameManager gameManger;
	testTextParser();
	//
	test = readFile(stream, "./textfiles/Text.txt");

	// print something to the terminal
    std::cout << "Welcome to Paraphrase Text adventure tool!\n";
	std::cout << (('5' - '0') + 1) << std::endl;	
	std::cout << test << std::endl;

	// puase for user input
	std::cin.get();


	std::cout << std::endl << std::endl; 


	gameManger.start();
	std::cout << "Welcome to Paraphrase Text adventure tool!\n";


} 


void testTextParser()
{
	TextParser Parser;
	std::string testText = "Hello [name]a [name] [name] {key>0 You have [key] keys} its nice to meet you!";
	std::string testTextTwo = "I had [key] keys, but now I have #key+1# keys";

	Parser.counters.set_string_counter("name", "seaney");

	Parser.counters.number_counter_add("key",4);


	std::cout << Parser.ParseText("I had [key] keys, but now I have #key+1# keys");

}







/*
	This is a basic test for counterManger and should test all functionality.
*/
void testCounter()
{
	CounterManager counters;
	// adding variable wow
	counters.number_counter_add("wow", 1);

	std::cout << "wow : " << counters.get_number_counter("wow") << std::endl;

	// changing number
	counters.number_counter_equals("wow", 50);

	std::cout << "changing wow to 50" << std::endl;

	std::cout << "wow : " << counters.get_number_counter("wow") << std::endl;

	// changing number
	counters.number_counter_subtract("wow", 1);

	std::cout << "wow : " << counters.get_number_counter("wow") << std::endl;

	// changing number
	counters.number_counter_add("wow", 2);

	std::cout << "adding 2" << std::endl;

	std::cout << "wow : " << counters.get_number_counter("wow") << std::endl;

	// checking numebr

	std::cout << "is wow real?  " << counters.check_number_counter("wow") << std::endl;

	// adding variable wow

	std::cout << "is name real :" << counters.check_string_counter("name") << std::endl;

	std::cout << "setting name" << std::endl;
	counters.set_string_counter("name", "Seaney");

	std::cout << "is name real :" << counters.check_string_counter("name") << std::endl;
	std::cout << "name is : " << counters.get_string_counter("name") << std::endl;


	// changing number
	counters.set_string_counter("name", "...");

	std::cout << "name is : " << counters.get_string_counter("name") << std::endl;


	//
}


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
