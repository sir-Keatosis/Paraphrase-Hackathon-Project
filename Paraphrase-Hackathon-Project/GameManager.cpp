#include "GameManager.h"
#include "iostream"
#include <string>





void GameManager::start()
{
	Parser.counters = this->Counters;
	Parser.portals = this->portals;

	char UserReponce;
	std::string fileName;
	bool wrongInput = true;

	std::cout << "Welcome to Paraphrase Text adventure tool!\n";
	std::cout << "Please enter a number \n 1. start a new game? \n 2. load a saved game \n Choice : ";
	std::cin >> UserReponce;
	std::cin.ignore(10000, '\n');
	std::cin.clear();

	while (wrongInput)
	{
		switch (UserReponce)
		{
		case '1':
			wrongInput = false;
			std::cout << "Please enter the name of the start chapter for the game you would like to run \n file name : ";
			std::cin >> fileName;
			fileName.append(".txt");
			
			break;
		case '2':
			wrongInput = false;
			std::cout << "Please enter the name of your save file!";
			std::cin >> fileName;
			fileName.append(".txt");
			// This is where we will load a save game 
			break;
		default:
			std::cout << "Sorry you didn't enter 1 or 2. \n \n";
			std::cout << "Please enter a number \n 1. start a new game? \n 2. load a saved game \n Choice : ";
			std::cin >> UserReponce;
			std::cin.ignore(10000, '\n');
			std::cin.clear();
			break;
		}
	}
}
  

void GameManager::setPortal(std::string fileName, std::string displayText)
{
}



void GameManager::choosePortal()
{
	/*
	for (int count = 0; count < portals.size(); count++))
	{
	std::cout << "Choice " << namedInt << +": " + portal.getDisplayText() << endl;
	}*/
}

