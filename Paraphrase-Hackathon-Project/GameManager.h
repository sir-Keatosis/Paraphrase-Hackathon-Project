#pragma once
#include <list> 
#include <iterator> 
#include <vector>
#include "Portal.h"
#include "CounterManager.h"
#include "TextParser.h"
#include <map>
#include <fstream>

class GameManager
{
	public:
		void start();
		void setPortal(std::string fileName, std::string displayText);
		void choosePortal();
		void runChapter(std::string filename);
		std::string readFile(std::string file); 
		bool isRightType(std::string filePath); 
		void printText(std::string textToPrint);
		void listCounters();
		std::string currentChapter;
		std::string storyDirectory;
		TextParser Parser;
	private:
		//Settings and config stuff: ==============================================================
		int text_speed;
		unsigned int random_seed;
		bool cheats;
		bool autosave;
		std::string autorun; //If this is defined then it will automatically open this story story when the game boots up
		void check_config(); //used to modify the config file
		void format_config(); //used to create a new config file if one is not already detected
		//=========================================================================================
};

