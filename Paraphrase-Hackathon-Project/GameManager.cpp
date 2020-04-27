#include "GameManager.h"
#include "iostream"
#include <string>
#include <chrono>
#include <thread>


/**
	This function starts the game sets the portals and counter manager to be the same in 
	both textParser and GameManager. After this it asks users if they want to load or start a new game,

	on new game this function starts running runChapter() with the given file name, 
	
	loading and saving is now functional (and should be given their own functions, however they're rolled into another function)


*/
const std::string AUTOSAVE = "autoSave";
const std::string failStmnt = "Sorry, unable to open file";
const std::string CONFIG_FILE_PATH = "./system/config.txt";

void GameManager::listCounters()
{
	for (auto const& x : Parser.counters.number_counters)
	{
		std::cout << x.first  // string (key)
		<< " "
		<< x.second
		<< "\n";
	}
	for (auto const& x : Parser.counters.string_counters)
	{
		std::cout << x.first  // string (key)
			<< " "
			<< x.second
			<< "\n";
	}
}

void GameManager::start()
{
	check_config();
	storyDirectory = "";
	char UserReponce;
	std::string fileName;
	bool wrongInput = true;

	std::cout << "Welcome to Paraphrase Text adventure tool v1.0!\n";
	std::cout << "Please enter a number \n 1. start a new story? \n 2. load from a specific save \n Choice : ";
	std::cin >> UserReponce;
	std::cin.ignore(10000, '\n');
	std::cin.clear();

	while (wrongInput)
	{
		switch (UserReponce)
		{
			/*
		case'1':
			break;
			if (Parser.counters.load(AUTOSAVE, currentChapter))
			{
				std::cout << AUTOSAVE << " Continuing where you left off...\n";
				Parser.readOnly = true;
				runChapter(currentChapter);
				//wrongInput = false; //This is currently broken as it's being worked on
			}
			else
			{
				std::cout << AUTOSAVE << " Failed to load (incorrect file name, or impropperly formatted save file)\n";
				wrongInput = true;
			}
			break;
			*/
		case '1':
			wrongInput = false;
			std::cout << "Please enter the name of the story you would like to run \n Folder name : ";
			std::cin >> fileName;
			storyDirectory = "./" + fileName + "/";
			//fileName = ".//" + fileName + "//" + fileName + ".txt";
			fileName.append(".txt");
			runChapter(fileName);
			break;
		case '2': //loading save file
			if (storyDirectory == "") //formatted this way because I will later have a "Default story" in the ini.txt file
			{
				std::cout << "Please Enter the name of the story you'd like to load: ";
				std::cin >> storyDirectory;
				storyDirectory = "./" + storyDirectory + "/";
			}
			std::cout << "Please enter the name of your save file: ";
			std::cin >> fileName;
			fileName = storyDirectory + "saves/" + fileName;
			if (Parser.counters.load(fileName, currentChapter))
			{
				std::cout << fileName << " Successfully loaded!\n";
				Parser.readOnly = true;
				runChapter(currentChapter);
				wrongInput = false;
			}
			else
			{
				std::cout << fileName << " Failed to load (incorrect file name, or impropperly formatted save file)\n";
				wrongInput = true;
			}
			//break; Break was removed so that you don't get stuck in an infinite loop of inputting the wrong file. Asking for the wrong file
			//will trigger the default condition and kick you back to the main menue
		default:
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
		std::this_thread::sleep_for(std::chrono::milliseconds(text_speed)); //defaults to 50, turned off for testing
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
	output = readFile((storyDirectory + filename));
	printText(Parser.ParseText(output));
	if (output == failStmnt) //checks to see if you're in a valid chapter, or not
	{
		std::cout << " You have reached a dead end and will be returned to the main menu \n";
		start();
	}
	//create autosave here
	Parser.counters.save((storyDirectory + "/saves/" + AUTOSAVE), currentChapter); 
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


void GameManager::choosePortal() //This function is probably too big, but it works and I am afraid to tear it appart 
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
			//listCounters(); //this was put in for testing purposes, but it is redundant and there is no reason to see it at run time
			//if you would like to see the variables in play, simply open your save file in notepad
			//call save function
			std::string save_file_name = "";
			std::cout << "Please enter the name you'd like to save to: ";
			//getline(std::cin, save_file_name);
			std::cin >> save_file_name;
			if (Parser.counters.save((storyDirectory + "saves/" + save_file_name), currentChapter))
			{
				std::cout << "\nsucessfully saved to " << save_file_name << "\n";
				choosePortal();
			}
			else
			{
				std::cout << "\n did not sucessfully save to " << save_file_name << "\n";
				choosePortal();
			}
		}
		else if (userInput == "l" or userInput == "L")
		{
			//call load function
			std::string save_file_name = "";
			std::cout << "Please enter the name of the file you'd like to load: ";
			//getline(std::cin, save_file_name);
			std::cin >> save_file_name;
			if (Parser.counters.load((storyDirectory + "saves\\" + save_file_name), currentChapter))
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
		else if (userInput == "q" or userInput == "Q") //Quit the program
		{
			std::cout << "Thank You for playing \n Shutting down";
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
			std::cout << ".";
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
			std::cout << ".";
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
			std::cout << ".";
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
			exit(0);
		}
		else if (userInput == "c" or userInput == "C") //Later cheats will have to be enabled in the config file
		{
			while (userInput != "1")  
			{
				std::cout << "--=={[DEBUG MENUE]}==-- \n"
					<< " 1. return to the story \n 2. list all counters \n 3. edit counter \n";
				std::cin >> userInput;
				std::string userInput2;
				switch (userInput.at(0))
				{
					case'1':
						break;
					case'2':
						listCounters();
						break;
					case'3': //okay here it's getting serious
						std::cout << "enter DONE to return to the debug/cheat menue \n";
						while (userInput != "DONE")
						{
							std::cout << "enter the name of the counter you would like to add/modify: ";
							std::cin >> userInput;
							if (userInput == "DONE" or userInput == "done")
							{
								break;
							}
							if (isdigit(userInput.at(0)))
							{
								std::cout << "counter names are not allowed to START with digits\n";
							}
							else
							{
								std::cout << "\nenter the name of the value for " << userInput << ": ";
								std::cin >> userInput2;
								if (isdigit(userInput2.at(0)) or userInput2.at(0) == '-')//determines if this will be a string counter or a number counter
								{
									//This means it's a number counter
									Parser.counters.number_counter_equals(userInput, std::stoi(userInput2));
								}
								else
								{
									//this means it's a string counter
									Parser.counters.set_string_counter(userInput, userInput2);
								}
							}

						}
						break;
					default:
						break;
				}
			}
			choosePortal();
		}
		else if (found != std::string::npos)
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

void GameManager::check_config()
{
	std::ifstream instream;
	instream.open(CONFIG_FILE_PATH);
	if (instream.good())
	{
		std::string setting_name;
		std::getline(instream, setting_name);
		instream >> text_speed;
	}
	else
	{
		std::cout << "configuration file not found, creating a new one\n";
		format_config();
		check_config(); //this is a little recursive... probably a bit risky
	}
}

void GameManager::format_config()
{
	std::ofstream outstream;
	outstream.open(CONFIG_FILE_PATH);
	if (outstream.good())
	{
		outstream << "Text_Speed\n"
			<< 50; //default text speed
		//more settings will be added as I encounter more use cases
		outstream.close();
	}
	else
	{
		std::cout << "failed to create an config file \n";
	}
}


