//! PROBLEM 1
// Something is wrong with global snow production, and you've been selected to take a look. The Elves have even given you a map; on it, they've used stars to mark the top fifty locations that are likely to be having problems.
// You've been doing this long enough to know that to restore snow operations, you need to check all fifty stars by December 25th.
// Collect stars by solving puzzles. Two puzzles will be made available on each day in the Advent calendar; the second puzzle is unlocked when you complete the first. Each puzzle grants one star. Good luck!
// You try to ask why they can't just use a weather machine ("not powerful enough") and where they're even sending you ("the sky") and why your map looks mostly blank ("you sure ask a lot of questions") and hang on did you just say the sky ("of course, where do you think snow comes from") when you realize that the Elves are already loading you into a trebuchet ("please hold still, we need to strap you in").
// As they're making the final adjustments, they discover that their calibration document (your puzzle input) has been amended by a very young Elf who was apparently just excited to show off her art skills. Consequently, the Elves are having trouble reading the values on the document.
// The newly-improved calibration document consists of lines of text; each line originally contained a specific calibration value that the Elves now need to recover. On each line, the calibration value can be found by combining the first digit and the last digit (in that order) to form a single two-digit number.
// For example:

// 1abc2
// pqr3stu8vwx
// a1b2c3d4e5f
// treb7uchet
// In this example, the calibration values of these four lines are 12, 38, 15, and 77. Adding these together produces 142.

// Consider your entire calibration document. What is the sum of all of the calibration values?

//! PROBLEM 2
// Your calculation isn't quite right. It looks like some of the digits are actually spelled out with letters: one, two, three, four, five, six, seven, eight, and nine also count as valid "digits".
// Equipped with this new information, you now need to find the real first and last digit on each line. For example:

// two1nine
// eightwothree
// abcone2threexyz
// xtwone3four
// 4nineeightseven2
// zoneight234
// 7pqrstsixteen
// In this example, the calibration values are 29, 83, 13, 24, 42, 14, and 76. Adding these together produces 281.

// What is the sum of all of the calibration values?

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
