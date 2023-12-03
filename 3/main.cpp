#include <iostream>
#include "../inputReader.h"
#include <vector>
#include <list>

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

    int sum = 0;
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
                std::cout << "continueBefore: " << c << std::endl;
                continue;
            }
            std::cout << "c: " << c << std::endl;

            // hier sind jetzt nur noch die Symbole
            // um das Symbol schauen, wo Zahl ist
            // m = row
            for (int m = i - 1; m < i + 2; m++)
            {
                std::cout << "m: " << m << std::endl;
                // n = columns
                for (int n = j - 1; n < j + 2; n++)
                {
                    std::cout << "n: " << n << std::endl;
                    if ((m < 0 || m >= input.size()) ||
                        (n < 0 || n >= input[m].size()) ||
                        (!std::isdigit(input[m][n])))
                    {
                        std::cout << "continue" << std::endl;
                        continue;
                    }

                    // warum -1????
                    // diesen Part verstehe ich generell nicht ganz
                    // while (n > 0 && std::isdigit(input[m][n - 1]))
                    // {
                    //     n--;
                    // }

                    beginningOfNumberCoords.push_back(std::pair<int, int>(m, n));
                }
            }
        }
    }

    std::cout << "Beginning of number coords: " << std::endl;
    for (const std::pair<int, int> &coords : beginningOfNumberCoords)
    {
        std::cout << coords.first << ", " << coords.second << std::endl;
    }

    std::cout << "Result: " << sum << std::endl;

    return EXIT_SUCCESS;
}
