#include <iostream>
#include <algorithm>
#include "../inputReader.h"

static const std::string INPUT_FILE_PATH = "input.txt";

std::list<int> splitStringToInts(const std::string &stringToSplit, const char delimiter);

int main(int argc, char *argv[])
{
    const std::list<std::string> rawInput = getInputFromFile(INPUT_FILE_PATH);

    int sum = 0;

    for (const std::string &line : rawInput)
    {
        const int colonIndex = line.find(':');
        const int verticalLineIndex = line.find('|');

        const std::string winningNumbersAsString = line.substr(colonIndex + 2, verticalLineIndex - colonIndex - 3);
        const std::string myNumbersAsString = line.substr(verticalLineIndex + 2, line.length() - verticalLineIndex - 2);

        const std::list<int> winningNumbers = splitStringToInts(winningNumbersAsString, ' ');
        const std::list<int> myNumbers = splitStringToInts(myNumbersAsString, ' ');

        int correctNumbers = 0;
        for (const int myNumber : myNumbers)
        {
            auto it = std::find(winningNumbers.begin(), winningNumbers.end(), myNumber);
            if (it == winningNumbers.end())
            {
                continue;
            }

            if (correctNumbers == 0)
            {
                correctNumbers++;
                continue;
            }

            correctNumbers *= 2;
        }

        sum += correctNumbers;
    }

    std::cout << "Result: " << sum << std::endl;

    return EXIT_SUCCESS;
}

std::list<int> splitStringToInts(const std::string &stringToSplit, const char delimiter)
{
    std::list<int> splitInts;

    std::string currentNumberAsString;
    for (const char character : stringToSplit)
    {
        if (character == delimiter)
        {
            if (currentNumberAsString == "")
            {
                continue;
            }

            splitInts.push_back(std::stoi(currentNumberAsString));
            currentNumberAsString = "";
        }
        else
        {
            currentNumberAsString += character;
        }
    }

    splitInts.push_back(std::stoi(currentNumberAsString));

    return splitInts;
}