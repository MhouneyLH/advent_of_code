#include <iostream>
#include <list>
#include <map>
#include "../inputReader.h"

static const std::string INPUT_FILE_PATH = "input.txt";
static const char DEFAULT_NUMBER_AS_CHAR = '0';

std::map<std::string, std::string> digitMapping = {
    {"one", "o1e"},
    {"two", "t2o"},
    {"three", "t3e"},
    {"four", "f4r"},
    {"five", "f5e"},
    {"six", "s6x"},
    {"seven", "s7n"},
    {"eight", "e8t"},
    {"nine", "n9e"},
};

std::list<std::string> getParsedInput(const std::list<std::string> &input);
std::string replaceWrittenDigitsToActualDigits(const std::string &line);
char getFirstNumberOfLineAsChar(const std::string &line);
char getLastNumberOfLineAsChar(const std::string &line);
int getSummedNumbersFromInput(const std::list<std::string> &input);
std::string getNumberFrom2CharsAsString(const char firstChar, const char lastChar);

std::list<std::string> getParsedInput(const std::list<std::string> &input)
{
    std::list<std::string> result;

    for (const std::string &line : input)
    {
        const std::string parsedLine = replaceWrittenDigitsToActualDigits(line);
        std::cout << parsedLine << std::endl;
        result.push_back(parsedLine);
    }

    return result;
}

std::string replaceWrittenDigitsToActualDigits(const std::string &line)
{
    std::string result = line;

    for (const auto &entry : digitMapping)
    {
        size_t pos;
        while ((pos = result.find(entry.first)) != std::string::npos)
        {
            result = result.replace(pos, entry.first.length(), entry.second);
        }
    }

    return result;
}

char getFirstNumberOfLineAsChar(const std::string &line)
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

char getLastNumberOfLineAsChar(const std::string &line)
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
        const char firstChar = getFirstNumberOfLineAsChar(line);
        const char lastChar = getLastNumberOfLineAsChar(line);

        const int lineResult = std::stoi(getNumberFrom2CharsAsString(firstChar, lastChar));
        result += lineResult;
    }

    return result;
}

std::string getNumberFrom2CharsAsString(const char firstChar, const char lastChar)
{
    std::string result = std::string(1, firstChar) + lastChar;
    return result;
}

int main(int argc, char *argv[])
{
    const std::list<std::string> rawInput = getInputFromFile(INPUT_FILE_PATH);
    const std::list<std::string> parsedInputWithoutWrittenNumbers = getParsedInput(rawInput);
    const int result = getSummedNumbersFromInput(parsedInputWithoutWrittenNumbers);

    std::cout << "Result: " << result << std::endl;

    return EXIT_SUCCESS;
}
