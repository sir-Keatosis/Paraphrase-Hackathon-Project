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


void GameManager::runChapter(std::string filename)
{
	TextParser parse;
	std::string output = "";
	output = readFile(Filestream, filename);
	std::cout << parse.ParseText(output);
	//choosePortal();
}

bool GameManager::isRightType(std::string filePath) // is being moved to counter manager
{
	return (filePath.substr(filePath.length() - 4) == ".txt" ? true : false);
}


std::string GameManager::readFile(std::ifstream& stream, std::string file) //is being moved to counter manager
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


void GameManager::choosePortal()
{
	/*
	for (int count = 0; count < portals.size(); count++))
	{
	std::cout << "Choice " << namedInt << +": " + portal.getDisplayText() << endl;
	}*/
}

