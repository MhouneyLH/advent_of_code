#include <iostream>
#include <list>
#include "../inputReader.h"

static const std::string INPUT_FILE_PATH = "input.txt";
static const char DEFAULT_NUMBER_AS_CHAR = '0';

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

    return DEFAULT_NUMBER_AS_CHAR;
}

char getLastNumberAsCharInLine(const std::string &line)
{
    // man hätte es auch mit normalen Iteratoren machen können
    // da aber darauf achten, dass begin() immer das erste Element ist
    // und end() immer das Element nach dem letzten Element
    for (auto it = line.rbegin(); it != line.rend(); it++)
    {
        if (std::isdigit(*it))
        {
            return *it;
        }
    }

    return DEFAULT_NUMBER_AS_CHAR;
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
