#pragma once
#include <list> 
#include <iterator> 
#include <vector>
#include "Portal.h"

class GameManager
{
	public:
		void start();
		void setPortal(std::string fileName, std::string displayText);
	private:
		std::vector <Portal> portals;
		
};

