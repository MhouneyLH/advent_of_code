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
