#include <iostream>
#include "CounterManager.h"
#include "TextParser.h"
#include <cstdlib>
#include <fstream>
#include <string>
#include <cmath>



/*
//bool isRightType(std::string filePath);
//std::string readFile(std::ifstream& stream, std::string file);

bool isRightType(std::string filePath)
{

    return (filePath.substr(filePath.length() - 4) == ".txt" ? true : false);


}

std::string readFile(std::ifstream& stream, std::string file)
{
    const std::string failStmnt = "Sorry, unable to open file";
    
    if (isRightType(file) == true)
    {
        stream.open(file);
        if (stream.good() == true)
        {
            {
                std::string output = "";
                while (!stream.eof())
                {
                    std::getline(stream, output);
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
}*/






