// Paraphrase-Hackathon-Project.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "TextParser.h"
#include "CounterManager.h"
#include "GameManager.h"
#include <cstdlib>
#include <fstream>
#include <string>



bool isRightType(std::string filePath);
void print_file_parser(std::string file_text);
void testCounter();
void testTextParser();
std::string readFile(std::ifstream& stream, std::string file);
std::ifstream stream;
std::string test;

void testSaving();
void testLoading();

int main()
{
	GameManager gameManger;
	//testLoading();
	gameManger.start();
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

void print_file_parser(std::string file_text)
{
	TextParser parse;
	std::string output = "";
	output = readFile(stream, file_text);
	std::cout << parse.ParseText(output);
	/*
		we should also print out the portals and ask for user input
	*/

}



bool isRightType(std::string filePath) //is being moved to counter manager
{

	return (filePath.substr(filePath.length() - 4) == ".txt" ? true : false);


}

std::string readFile(std::ifstream& stream, std::string file) //is being moved to counter manager
{
	const std::string failStmnt = "Sorry, unable to open file";

	if (isRightType(file) == true)
	{
		stream.open(file);
		if (stream.good() == true)
		{
			{
				std::string output = "";
				std::string temp = "";
				while (stream.good())
				{
					std::getline(stream, temp);
					output.append(temp + "\n");
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


void testSaving()
{
	CounterManager counters;
	GameManager Game;
	Game.currentChapter = "The magical Ball world";
	counters.number_counter_add("one", 1);
	counters.number_counter_add("two", 1);
	counters.number_counter_add("three", 1);
	counters.set_string_counter("name", "Barlo");
	if (counters.save("test_save.txt", Game.currentChapter))
	{
		std::cout << "Saved successfully\n";
	}
	else
	{
		std::cout << "Did not save successfully\n";
	}
}

void testLoading()
{
	CounterManager counters;
	GameManager Game;
	std::cout << "beginning load test \n";
	if (counters.load("test_save.txt", Game.currentChapter))
	{
		std::cout << "Test Loaded successfully \n";
	}
	else
	{
		std::cout << "Did not pass the loading test \n";
	}
	counters.set_string_counter("name", "Harlo");
	counters.number_counter_add("four", 40);
	if (counters.save("test_save_two.txt", Game.currentChapter))
	{
		std::cout << "and resaved successfully \n";
	}
	else
	{
		std::cout << "Somehow it failed to resave \n";
	}
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
