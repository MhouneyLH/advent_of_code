#include <iostream>
#include <algorithm>
#include <vector>
#include <numeric>
#include "../inputReader.h"

static const std::string INPUT_FILE_PATH = "input2.txt";

std::list<int> splitStringToInts(const std::string &stringToSplit, const char delimiter);

int main(int argc, char *argv[])
{
    const std::list<std::string> rawInput = getInputFromFile(INPUT_FILE_PATH);

    std::vector<int> cardInstances(rawInput.size(), 1);
    int currentCard = 0;

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

            correctNumbers++;
        }

        for (int k = currentCard + 1; k < currentCard + correctNumbers + 1; k++)
        {
            cardInstances[k] += cardInstances[currentCard];
        }

        currentCard++;
    }

    const int sumOfcardInstances = std::accumulate(cardInstances.begin(), cardInstances.end(), 0);
    std::cout << "Result: " << sumOfcardInstances << std::endl;

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