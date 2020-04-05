#pragma once
#include <list> 
#include <iterator> 
#include <vector>
#include "Portal.h"
#include <map>

class GameManager
{
	public:
		void start();
		void setPortal(std::string fileName, std::string displayText);
		void choosePortal();
		std::string currentChapter;

	private:
		std::vector <Portal> portals;
		
};

