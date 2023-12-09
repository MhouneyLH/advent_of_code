//! PROBLEM
// The engineer finds the missing part and installs it in the engine! As the engine springs to life, you jump in the closest gondola, finally ready to ascend to the water source.

// You don't seem to be going very fast, though. Maybe something is still wrong? Fortunately, the gondola has a phone labeled "help", so you pick it up and the engineer answers.

// Before you can explain the situation, she suggests that you look out the window. There stands the engineer, holding a phone in one hand and waving with the other. You're going so slowly that you haven't even left the station. You exit the gondola.

// The missing part wasn't the only issue - one of the gears in the engine is wrong. A gear is any * symbol that is adjacent to exactly two part numbers. Its gear ratio is the result of multiplying those two numbers together.

// This time, you need to find the gear ratio of every gear and add them all up so that the engineer can figure out which gear needs to be replaced.

// Consider the same engine schematic again:

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
// In this schematic, there are two gears. The first is in the top left; it has part numbers 467 and 35, so its gear ratio is 16345. The second gear is in the lower right; its gear ratio is 451490. (The * adjacent to 617 is not a gear because it is only adjacent to one part number.) Adding up all of the gear ratios produces 467835.

// What is the sum of all of the gear ratios in your engine schematic?

#include <iostream>
#include "../inputReader.h"
#include <vector>
#include <list>
#include <numeric>
#include <algorithm>

static const std::string INPUT_FILE_PATH = "input.txt";
static const char SPACING_CHAR = '.';
static const char GEAR_CHAR = '*';

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
            if (c != GEAR_CHAR)
            {
                continue;
            }

            std::vector<std::pair<int, int>> gearNumberCoords;
            // hier sind jetzt nur noch die Symbole
            // um das Symbol schauen, wo Zahl ist
            // m = row
            for (int m : {i - 1, i, i + 1})
            {
                // n = columns
                for (int n : {j - 1, j, j + 1})
                {
                    if ((m < 0 || m >= input.size()) ||    // vertical bounds
                        (n < 0 || n >= input[m].size()) || // horizontal bounds
                        (!std::isdigit(input[m][n])))
                    {
                        continue;
                    }

                    // bis zu 1. Stelle von Zahl gehen
                    while (n > 0 && std::isdigit(input[m][n - 1]))
                    {
                        n--;
                    }

                    // no duplicate coords
                    auto it = std::find(gearNumberCoords.begin(), gearNumberCoords.end(), std::pair<int, int>(m, n));
                    if (it != gearNumberCoords.end())
                    {
                        continue;
                    }

                    gearNumberCoords.push_back(std::pair<int, int>(m, n));
                }
            }

            if (gearNumberCoords.size() == 2)
            {
                beginningOfNumberCoords.push_back(gearNumberCoords[0]);
                beginningOfNumberCoords.push_back(gearNumberCoords[1]);
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

    int sum = 0;
    for (int a = 0; a < numbers.size(); a += 2)
    {
        sum += numbers[a] * numbers[a + 1];
    }

    // const int sum = std::accumulate(numbers.begin(), numbers.end(), 0);
    std::cout << "Result: " << sum << std::endl;

    return EXIT_SUCCESS;
}
