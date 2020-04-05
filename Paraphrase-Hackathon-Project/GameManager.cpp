#include "GameManager.h"
#include "iostream"
#include <string>




struct GameManager::Portal
{
	Portal()
	{

	}
	Portal(std::string _fileName, std::string _displayText)
	{
		fileName = _fileName;
		displayText = _displayText;
	}
	std::string fileName; 
	std::string displayText;
};

void GameManager::start()
{
	std::string UserReponce;
	std::cout << "Welcome to Paraphrase Text adventure tool!\n";

	std::cout << "Please enter a number \n 1. start a new game? \n 2. load a new game \n";

	std::cin >> UserReponce;

}



void GameManager::setPortal(std::string fileName, std::string displayText)
{
	//Portals
}