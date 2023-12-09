//! PROBLEM 1
// You're launched high into the atmosphere! The apex of your trajectory just barely reaches the surface of a large island floating in the sky. You gently land in a fluffy pile of leaves. It's quite cold, but you don't see much snow. An Elf runs over to greet you.
// The Elf explains that you've arrived at Snow Island and apologizes for the lack of snow. He'll be happy to explain the situation, but it's a bit of a walk, so you have some time. They don't get many visitors up here; would you like to play a game in the meantime?
// As you walk, the Elf shows you a small bag and some cubes which are either red, green, or blue. Each time you play this game, he will hide a secret number of cubes of each color in the bag, and your goal is to figure out information about the number of cubes.
// To get information, once a bag has been loaded with cubes, the Elf will reach into the bag, grab a handful of random cubes, show them to you, and then put them back in the bag. He'll do this a few times per game.
// You play several games and record the information from each game (your puzzle input). Each game is listed with its ID number (like the 11 in Game 11: ...) followed by a semicolon-separated list of subsets of cubes that were revealed from the bag (like 3 red, 5 green, 4 blue).
// For example, the record of a few games might look like this:

// Game 1: 3 blue, 4 red; 1 red, 2 green, 6 blue; 2 green
// Game 2: 1 blue, 2 green; 3 green, 4 blue, 1 red; 1 green, 1 blue
// Game 3: 8 green, 6 blue, 20 red; 5 blue, 4 red, 13 green; 5 green, 1 red
// Game 4: 1 green, 3 red, 6 blue; 3 green, 6 red; 3 green, 15 blue, 14 red
// Game 5: 6 red, 1 blue, 3 green; 2 blue, 1 red, 2 green

// In game 1, three sets of cubes are revealed from the bag (and then put back again). The first set is 3 blue cubes and 4 red cubes; the second set is 1 red cube, 2 green cubes, and 6 blue cubes; the third set is only 2 green cubes.
// The Elf would first like to know which games would have been possible if the bag contained only 12 red cubes, 13 green cubes, and 14 blue cubes?
// In the example above, games 1, 2, and 5 would have been possible if the bag had been loaded with that configuration. However, game 3 would have been impossible because at one point the Elf showed you 20 red cubes at once; similarly, game 4 would also have been impossible because the Elf showed you 15 blue cubes at once. If you add up the IDs of the games that would have been possible, you get 8.

// Determine which games would have been possible if the bag had been loaded with only 12 red cubes, 13 green cubes, and 14 blue cubes. What is the sum of the IDs of those games?

//! PROBLEM 2
// The Elf says they've stopped producing snow because they aren't getting any water! He isn't sure why the water stopped; however, he can show you how to get to the water source to check it out for yourself. It's just up ahead!
// As you continue your walk, the Elf poses a second question: in each game you played, what is the fewest number of cubes of each color that could have been in the bag to make the game possible?
// Again consider the example games from earlier:

// Game 1: 3 blue, 4 red; 1 red, 2 green, 6 blue; 2 green
// Game 2: 1 blue, 2 green; 3 green, 4 blue, 1 red; 1 green, 1 blue
// Game 3: 8 green, 6 blue, 20 red; 5 blue, 4 red, 13 green; 5 green, 1 red
// Game 4: 1 green, 3 red, 6 blue; 3 green, 6 red; 3 green, 15 blue, 14 red
// Game 5: 6 red, 1 blue, 3 green; 2 blue, 1 red, 2 green

// In game 1, the game could have been played with as few as 4 red, 2 green, and 6 blue cubes. If any color had even one fewer cube, the game would have been impossible.
// Game 2 could have been played with a minimum of 1 red, 3 green, and 4 blue cubes.
// Game 3 must have been played with at least 20 red, 13 green, and 6 blue cubes.
// Game 4 required at least 14 red, 3 green, and 15 blue cubes.
// Game 5 needed no fewer than 6 red, 3 green, and 2 blue cubes in the bag.
// The power of a set of cubes is equal to the numbers of red, green, and blue cubes multiplied together. The power of the minimum set of cubes in game 1 is 48. In games 2-5 it was 12, 1560, 630, and 36, respectively. Adding up these five powers produces the sum 2286.

// For each game, find the minimum set of cubes that must have been present. What is the sum of the power of these sets?

#include <iostream>
#include <map>
#include <sstream>
#include <iterator>
#include "../inputReader.h"

static const std::string INPUT_FILE_PATH = "input.txt";
static const std::string LINE_DELIMITER = ":";
static const char PAYLOAD_DELIMITER = ';';
static const char PAYLOAD_ITEM_DELIMITER = ',';

static const int MAX_CUBES_RED = 12;
static const int MAX_CUBES_GREEN = 13;
static const int MAX_CUBES_BLUE = 14;

enum class Color
{
    RED = 0,
    GREEN = 1,
    BLUE = 2
};

struct Cube
{
    int amount = 0;
    Color color;
};

class Game
{
public:
    Game() {}
    ~Game() {}

    void fillWithLine(const std::string &line)
    {
        const int delimiterIndex = line.find(LINE_DELIMITER);
        const std::string header = line.substr(0, delimiterIndex);
        // +2 because of ": "
        const std::string payload = line.substr(delimiterIndex + 2, line.length() - 1);

        this->id = parseId(header);
        this->cubeSets = getCubeSetsOfPayload(payload);
    }

    bool isWorking(const int maxCubesRed, const int maxCubesGreen, const int maxCubesBlue)
    {
        for (const std::list<Cube> &cubeSet : cubeSets)
        {
            for (const Cube &cube : cubeSet)
            {
                if (cube.color == Color::RED && cube.amount > maxCubesRed)
                {
                    return false;
                }
                else if (cube.color == Color::GREEN && cube.amount > maxCubesGreen)
                {
                    return false;
                }
                else if (cube.color == Color::BLUE && cube.amount > maxCubesBlue)
                {
                    return false;
                }
            }
        }

        return true;
    }

    void printGameInformation()
    {
        std::cout << "Game " << this->id << std::endl;
        for (const std::list<Cube> &cubeSet : this->cubeSets)
        {
            for (const Cube &cube : cubeSet)
            {
                std::cout << cube.amount << PAYLOAD_ITEM_DELIMITER << static_cast<int>(cube.color) << PAYLOAD_DELIMITER;
            }
            std::cout << std::endl;
        }
    }

    int getId() const { return id; }
    std::list<std::list<Cube>> getCubeSets() const { return cubeSets; }

private:
    int parseId(const std::string &header)
    {
        const std::string idAsString = header.substr(header.find(" ") + 1, header.length() - 1);
        return std::stoi(idAsString);
    }

    std::list<std::string> split(const std::string &input, char delimiter)
    {
        std::list<std::string> result;

        std::stringstream ss(input);
        std::string item;
        while (std::getline(ss, item, delimiter))
        {
            result.push_back(item);
        }

        return result;
    }

    std::list<std::list<Cube>> getCubeSetsOfPayload(const std::string &payload)
    {
        std::list<std::list<Cube>> result;

        const std::list<std::string> payloadSplitted = split(payload, PAYLOAD_DELIMITER);
        for (const std::string &payloadItem : payloadSplitted)
        {
            std::list<Cube> cubes = getCubesFromPayloadItem(payloadItem);
            result.push_back(cubes);
        }

        return result;
    }

    std::list<Cube> getCubesFromPayloadItem(const std::string &payloadItem)
    {
        std::list<Cube> cubes;

        const std::list<std::string> cubeParts = split(payloadItem, PAYLOAD_ITEM_DELIMITER);
        for (const std::string &cubePart : cubeParts)
        {
            std::string cubePartWithoutUnnecessarySpaces = removeUnncecessarySpaces(cubePart);
            const std::list<std::string> amountAndColor = split(cubePartWithoutUnnecessarySpaces, ' ');

            Cube cube;
            cube.amount = std::stoi(amountAndColor.front());
            cube.color = getColorByString(amountAndColor.back());

            cubes.push_back(cube);
        }

        return cubes;
    }

    std::string removeUnncecessarySpaces(const std::string &input)
    {
        std::string result = input;

        if (input[0] == ' ')
        {
            // skip the first " "
            result = input.substr(1, input.length());
        }

        return result;
    }

    Color getColorByString(const std::string &colorAsString)
    {
        if (colorAsString == "red")
        {
            return Color::RED;
        }
        else if (colorAsString == "green")
        {
            return Color::GREEN;
        }
        else if (colorAsString == "blue")
        {
            return Color::BLUE;
        }
        else
        {
            std::cerr << "Unknown color: " << colorAsString << std::endl;
            exit(EXIT_FAILURE);
        }
    }

private:
    int id;
    std::list<std::list<Cube>> cubeSets;
};

int main(int argc, char *argv[])
{
    const std::list<std::string> rawInput = getInputFromFile(INPUT_FILE_PATH);
    std::list<Game> games;
    for (const std::string &line : rawInput)
    {
        Game game;
        game.fillWithLine(line);
        game.printGameInformation();

        games.push_back(game);
    }

    int idSum = 0;
    for (Game game : games)
    {
        if (game.isWorking(MAX_CUBES_RED, MAX_CUBES_GREEN, MAX_CUBES_BLUE))
        {
            idSum += game.getId();
        }
    }

    std::cout << "Result: " << idSum << std::endl;

    int powerSum = 0;
    for (Game game : games)
    {
        const std::list<std::list<Cube>> cubeSets = game.getCubeSets();
        int maxRedNumber = 0;
        int maxGreenNumber = 0;
        int maxBlueNumber = 0;

        for (const std::list<Cube> &cubeSet : cubeSets)
        {
            for (const Cube &cube : cubeSet)
            {
                if (cube.color == Color::RED && cube.amount > maxRedNumber)
                {
                    maxRedNumber = cube.amount;
                }
                else if (cube.color == Color::GREEN && cube.amount > maxGreenNumber)
                {
                    maxGreenNumber = cube.amount;
                }
                else if (cube.color == Color::BLUE && cube.amount > maxBlueNumber)
                {
                    maxBlueNumber = cube.amount;
                }
            }
        }
        powerSum += maxRedNumber * maxGreenNumber * maxBlueNumber;
    }

    std::cout << "Result: " << powerSum << std::endl;

    return EXIT_SUCCESS;
}
