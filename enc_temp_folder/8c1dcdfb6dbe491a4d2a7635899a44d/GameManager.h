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
		std::string readFile(std::string file); //is being moved to counter manage
		bool isRightType(std::string filePath); //is being moved to counter manager
		void printText(std::string textToPrint);
		void listCounters();
		std::string currentChapter;
		TextParser Parser;
		CounterManager Counters;
	private:
};

