#pragma once
#include <list> 
#include <iterator> 
#include <vector>
#include "Portal.h"
#include "CounterManager.h"
#include "TextParser.h"
#include <map>

class GameManager
{
	public:
		void start();
		void setPortal(std::string fileName, std::string displayText);
		void choosePortal();
		std::string currentChapter;
		TextParser Parser;
		CounterManager Counters;
		std::vector <Portal> portals;
	private:
};

