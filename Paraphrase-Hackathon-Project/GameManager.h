#pragma once
#include <list> 
#include <iterator> 

class GameManager
{
	public:
		void start();
		void setPortal(std::string fileName, std::string displayText);
	private:
		std::list <Portal> portals;
};

