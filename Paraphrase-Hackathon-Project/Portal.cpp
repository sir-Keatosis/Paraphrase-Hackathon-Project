#include "Portal.h"

Portal::Portal()
{
}

Portal::Portal(std::string _fileName, std::string _displayText)
{
	fileName = _fileName;
	displayText = _displayText;
}

std::string Portal::getfileName()
{
	return fileName;
}

void Portal::setFileName(std::string FileName)
{
	fileName = FileName;
}

std::string Portal::getDisplayText()
{
	return displayText;
}

void Portal::setDisplayText(std::string DisplayText)
{
	displayText = DisplayText;
}





