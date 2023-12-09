#include <iostream>
#include <fstream>
#include <list>

std::list<std::string> getInputAsLines(std::istream &inputFile)
{
    std::list<std::string> lines;

    std::string line;
    while (std::getline(inputFile, line))
    {
        lines.push_back(line);
    }

    return lines;
}

std::list<std::string> getInputFromFile(const std::string &relativePathToFile)
{
    std::ifstream inputFile(relativePathToFile);
    if (!inputFile.is_open())
    {
        std::cerr << "Error opening file: " << relativePathToFile << std::endl;
        exit(EXIT_FAILURE);
    }

    const std::list<std::string> lines = getInputAsLines(inputFile);
    inputFile.close();

    return lines;
}