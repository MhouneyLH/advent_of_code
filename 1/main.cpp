#include <iostream>
#include <fstream>
#include <list>

static const std::string INPUT_FILE_PATH = "input.txt";

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

char getFirstNumberAsCharInLine(const std::string &line)
{
    std::string::const_iterator it = line.begin();
    for (; it != line.end(); it++)
    {
        if (std::isdigit(*it))
        {
            return *it;
        }
    }

    return '0';
}

char getLastNumberAsCharInLine(const std::string &line)
{
    // man hätte es auch mit normalen Iteratoren machen können
    // da aber darauf achten, dass begin() immer das erste Element ist
    // und end() immer das Element nach dem letzten Element
    for (auto it = line.rbegin(); it != line.rend(); it++)
    {
        std::cout << *it << std::endl;
        if (std::isdigit(*it))
        {
            return *it;
        }
    }

    return '0';
}

int getSummedNumbersFromInput(const std::list<std::string> &input)
{
    int result = 0;
    for (const std::string &line : input)
    {
        const char firstChar = getFirstNumberAsCharInLine(line);
        const char lastChar = getLastNumberAsCharInLine(line);

        std::string both;
        both.push_back(firstChar);
        both.push_back(lastChar);

        const int lineResult = std::stoi(both);
        result += lineResult;
    }

    return result;
}

int main(int argc, char *argv[])
{
    const std::list<std::string> input = getInputFromFile(INPUT_FILE_PATH);
    const int result = getSummedNumbersFromInput(input);
    std::cout << "Result: " << result << std::endl;

    return EXIT_SUCCESS;
}
