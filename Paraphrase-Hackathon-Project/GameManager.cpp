#include "GameManager.h"
#include "iostream"
#include <string>
#include <chrono>
#include <thread>


/**
	This function starts the game sets the portals and counter manager to be the same in 
	both textParser and GameManager. After this it asks users if they want to load or start a new game,

	on new game this function starts running runChapter() with the given file name, 
	
	on load game TODO(it will run the load command from CounterManger)


*/
void GameManager::start()
{

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
			runChapter(fileName);
			break;
		case '2': //loading save file
			wrongInput = false;
			std::cout << "Please enter the name of your save file!";
			std::cin >> fileName;
			if (Counters.load(fileName, currentChapter))
			{
				std::cout << fileName << " Successfully loaded!\n";
				wrongInput = false;
			}
			else
			{
				std::cout << fileName << " Failed to load (incorrect file name, or impropperly formatted save file)\n";
				wrongInput = true;
			}
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

/**
	prints text at a char by char speed.

	@param textToPrint the string to print out.
*/
void GameManager::printText(std::string textToPrint )
{
	int strPos = 0;
	while (strPos < textToPrint.length())
	{
		std::cout << textToPrint.at(strPos);
		std::this_thread::sleep_for(std::chrono::milliseconds(50));
		strPos++;
	}

}


void GameManager::setPortal(std::string fileName, std::string displayText)
{
	//not functional right now

}


/**
	handals all of the calls to actually run one chapter, this means that 
	this function will in order
		read the passed in file in
		get the parsed text form the parser
		tell the printer to print the text
		run the choosePortalcommand

	@param filename Name of file to run
*/
void GameManager::runChapter(std::string filename)
{
	currentChapter = filename;
	Parser.portals.clear();
	std::string output = "";
	output = readFile(filename);
	printText(Parser.ParseText(output));
	choosePortal();
}


/**
	Opens a file with the name of file

	@param file The name of the file to open
	@return if file is openable returns the raw text from the file as a string,
	@return other wise it will reutrn "Sorry, unable to open file"
*/
bool GameManager::isRightType(std::string filePath) // is being moved to counter manager
{
	return (filePath.substr(filePath.length() - 4) == ".txt" ? true : false);
}


/**
	Opens a file with the name of file and if the file can be opend 
	as is a txt file returns a string of the files contence

	@param file The name of the file to open
	@return if file is openable returns the raw text from the file as a string, 
	@return other wise it will reutrn "Sorry, unable to open file"
*/
std::string GameManager::readFile(std::string file) //is being moved to counter manager
{
	const std::string failStmnt = "Sorry, unable to open file";
	std::ifstream stream;
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
	std::string userInput;
	Portal portal;
	int choice;
	const std::string numString = "012346789";
	const std::string actionString = "sSlL";
	const std::string tryAgain = "Invalid input. Try Again.";

	std::map<int, std::string> choiceMap;
	for (int count = 0; count < Parser.portals.size(); count++)
	{
		portal = Parser.portals.at(count);
		choiceMap[count] = portal.getfileName();
	std::cout << "Choice " << count << +": " + portal.getDisplayText() << std::endl;
	}
	std::cin >> userInput;
	const int length = userInput.length();
	if (length == 1)
	{
		const size_t found = numString.find(userInput);
		if (userInput == "s" or userInput == "S")
		{
			//call save function
			std::string save_file_name = "";
			std::cout << "Please enter the name you'd like to save to: ";
			getline(std::cin, save_file_name);
			if (Counters.save(save_file_name, currentChapter))
			{
				std::cout << "\nsucessfully saved to " << save_file_name << "\n";
			}
			else
			{
				std::cout << "\n did not sucessfully save to " << save_file_name << "\n";
				choosePortal();
			}
		}
		if (userInput == "l" or userInput == "L")
		{
			//call load function
			std::string save_file_name = "";
			std::cout << "Please enter the name of the file you'd like to load: ";
			getline(std::cin, save_file_name);
			if (Counters.load(save_file_name, currentChapter))
			{
				std::cout << "\nsucessfully loaded " << save_file_name << "\n";
				//set read only flag
				Parser.readOnly = true;
				runChapter(currentChapter);
			}
			else
			{
				std::cout << "\nfailed to load " << save_file_name << "\n";
				choosePortal();
			}

		}
		if (found != std::string::npos)
		{
			choice = std::stoi(userInput);
			Parser.readOnly = false;
			runChapter(Parser.portals.at(choice).getfileName());
		}
		else
		{
			std::cout << tryAgain << std::endl;
			choosePortal();
		}

	}
	else
	{
		std::cout << tryAgain << std::endl;
		choosePortal();
	}

}

