#include <iostream>
#include "CounterManager.h"
#include "TextParser.h"
#include <cstdlib>
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

std::string readFile(std::ifstream stream, std::string file)
{
    const std::string failStmnt = "Sorry, unable to open file";

    if (isRightType(file) == true)
    {
        stream.open(file);
        if (stream.good() == true)
        {
            {
                char* str = {};
                std::string output = "";
                while (stream.get(str, 5000))
                {
                    output.append(str);
                }
                stream.close();
                return output;
            }
        }
        else
        {
            return failStmnt;
        }


    }
    else
    {
        return failStmnt;
    }
}






