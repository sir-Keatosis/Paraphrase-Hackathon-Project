#pragma once
#include <vector>
#include <string>



class Portal
{
public:
	Portal();
	Portal(std::string _fileName, std::string _displayText);

	std::string getfileName();
	void setFileName(std::string FileName);
	std::string getDisplayText();
	void setDisplayText(std::string DisplayText);
private:
	std::string fileName;
	std::string displayText;
};

