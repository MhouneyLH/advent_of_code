//! PROBLEM
// You and the Elf eventually reach a gondola lift station; he says the gondola lift will take you up to the water source, but this is as far as he can bring you. You go inside.

// It doesn't take long to find the gondolas, but there seems to be a problem: they're not moving.

// "Aaah!"

// You turn around to see a slightly-greasy Elf with a wrench and a look of surprise. "Sorry, I wasn't expecting anyone! The gondola lift isn't working right now; it'll still be a while before I can fix it." You offer to help.

// The engineer explains that an engine part seems to be missing from the engine, but nobody can figure out which one. If you can add up all the part numbers in the engine schematic, it should be easy to work out which part is missing.

// The engine schematic (your puzzle input) consists of a visual representation of the engine. There are lots of numbers and symbols you don't really understand, but apparently any number adjacent to a symbol, even diagonally, is a "part number" and should be included in your sum. (Periods (.) do not count as a symbol.)

// Here is an example engine schematic:

// 467..114..
// ...*......
// ..35..633.
// ......#...
// 617*......
// .....+.58.
// ..592.....
// ......755.
// ...$.*....
// .664.598..
// In this schematic, two numbers are not part numbers because they are not adjacent to a symbol: 114 (top right) and 58 (middle right). Every other number is adjacent to a symbol and so is a part number; their sum is 4361.

// Of course, the actual engine schematic is much larger. What is the sum of all of the part numbers in the engine schematic?

#include <iostream>
#include "../inputReader.h"
#include <vector>
#include <list>
#include <numeric>
#include <algorithm>

static const std::string INPUT_FILE_PATH = "input.txt";
static const char SPACING_CHAR = '.';
static const std::string SYMBOLS = "*/+-";

// 1. Daten in 2D-Array umwandeln
// 2. Durch iterieren und Zahlen erkennen
// 3. Nachbarn von den Zellen, die digits sind, anschauen
// 4. Wenn Nachbarn ein Zeichen sind (*/.....), dann zahl merken
// 5. Gemerkte Zahlen aufaddieren

int main(int argc, char *argv[])
{
    const std::list<std::string> rawInput = getInputFromFile(INPUT_FILE_PATH);

    std::vector<std::vector<char>> input;
    for (const std::string &line : rawInput)
    {
        std::vector<char> lineVector;
        for (const char &c : line)
        {
            if (c == '\r')
            {
                continue;
            }
            lineVector.push_back(c);
        }
        input.push_back(lineVector);
    }

    std::vector<std::pair<int, int>> beginningOfNumberCoords;

    // Rows
    for (int i = 0; i < input.size(); i++)
    {
        // Columns
        for (int j = 0; j < input[i].size(); j++)
        {
            const char c = input[i][j];
            if (std::isdigit(c) || c == SPACING_CHAR)
            {
                continue;
            }

            // hier sind jetzt nur noch die Symbole
            // um das Symbol schauen, wo Zahl ist
            // m = row
            for (int m : {i - 1, i, i + 1})
            {
                // std::cout << "m: " << m << std::endl;
                // n = columns
                for (int n : {j - 1, j, j + 1})
                {
                    // std::cout << "n: " << n << std::endl;
                    if ((m < 0 || m >= input.size()) ||
                        (n < 0 || n >= input[m].size()) ||
                        (!std::isdigit(input[m][n])))
                    {
                        continue;
                    }

                    // warum -1????
                    // diesen Part verstehe ich generell nicht ganz
                    while (n > 0 && std::isdigit(input[m][n - 1]))
                    {
                        n--;
                    }

                    // no duplicate coords
                    auto it = std::find(beginningOfNumberCoords.begin(), beginningOfNumberCoords.end(), std::pair<int, int>(m, n));
                    if (it != beginningOfNumberCoords.end())
                    {
                        continue;
                    }

                    beginningOfNumberCoords.push_back(std::pair<int, int>(m, n));
                }
            }
        }
    }

    // std::cout << "Beginning of number coords: " << std::endl;
    // for (const std::pair<int, int> &coords : beginningOfNumberCoords)
    // {
    //     std::cout << coords.first << ", " << coords.second << std::endl;
    // }

    std::vector<int> numbers = {};
    for (const std::pair<int, int> &coords : beginningOfNumberCoords)
    {
        int row = coords.first;
        int column = coords.second;

        std::string numberString = "";

        while (column < input[row].size() && std::isdigit(input[row][column]))
        {
            numberString += input[row][column];
            column++;
        }

        numbers.push_back(std::stoi(numberString));
    }

    const int sum = std::accumulate(numbers.begin(), numbers.end(), 0);
    std::cout << "Result: " << sum << std::endl;

    return EXIT_SUCCESS;
}
