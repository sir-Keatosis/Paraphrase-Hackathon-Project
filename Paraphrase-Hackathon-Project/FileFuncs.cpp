#include <iostream>
#include "CounterManager.h"
#include "TextParser.h"
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <string>
#include <cmath>

bool isRightType(std::string filePath)
{

    return (filePath.substr(filePath.length() - 4) == ".txt" ? true : false);


}

bool isValidFile(std::string filePath, std::fstream stream)
{
    stream.open(filePath);
    return stream.good();
}







