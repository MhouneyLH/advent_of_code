//! PROBLEM
// You take the boat and find the gardener right where you were told he would be: managing a giant "garden" that looks more to you like a farm.

// "A water source? Island Island is the water source!" You point out that Snow Island isn't receiving any water.

// "Oh, we had to stop the water because we ran out of sand to filter it with! Can't make snow with dirty water. Don't worry, I'm sure we'll get more sand soon; we only turned off the water a few days... weeks... oh no." His face sinks into a look of horrified realization.

// "I've been so busy making sure everyone here has food that I completely forgot to check why we stopped getting more sand! There's a ferry leaving soon that is headed over in that direction - it's much faster than your boat. Could you please go check it out?"

// You barely have time to agree to this request when he brings up another. "While you wait for the ferry, maybe you can help us with our food production problem. The latest Island Island Almanac just arrived and we're having trouble making sense of it."

// The almanac (your puzzle input) lists all of the seeds that need to be planted. It also lists what type of soil to use with each kind of seed, what type of fertilizer to use with each kind of soil, what type of water to use with each kind of fertilizer, and so on. Every type of seed, soil, fertilizer and so on is identified with a number, but numbers are reused by each category - that is, soil 123 and fertilizer 123 aren't necessarily related to each other.

// For example:

// seeds: 79 14 55 13

// seed-to-soil map:
// 50 98 2
// 52 50 48

// soil-to-fertilizer map:
// 0 15 37
// 37 52 2
// 39 0 15

// fertilizer-to-water map:
// 49 53 8
// 0 11 42
// 42 0 7
// 57 7 4

// water-to-light map:
// 88 18 7
// 18 25 70

// light-to-temperature map:
// 45 77 23
// 81 45 19
// 68 64 13

// temperature-to-humidity map:
// 0 69 1
// 1 0 69

// humidity-to-location map:
// 60 56 37
// 56 93 4
// The almanac starts by listing which seeds need to be planted: seeds 79, 14, 55, and 13.

// The rest of the almanac contains a list of maps which describe how to convert numbers from a source category into numbers in a destination category. That is, the section that starts with seed-to-soil map: describes how to convert a seed number (the source) to a soil number (the destination). This lets the gardener and his team know which soil to use with which seeds, which water to use with which fertilizer, and so on.

// Rather than list every source number and its corresponding destination number one by one, the maps describe entire ranges of numbers that can be converted. Each line within a map contains three numbers: the destination range start, the source range start, and the range length.

// Consider again the example seed-to-soil map:

// 50 98 2
// 52 50 48
// The first line has a destination range start of 50, a source range start of 98, and a range length of 2. This line means that the source range starts at 98 and contains two values: 98 and 99. The destination range is the same length, but it starts at 50, so its two values are 50 and 51. With this information, you know that seed number 98 corresponds to soil number 50 and that seed number 99 corresponds to soil number 51.

// The second line means that the source range starts at 50 and contains 48 values: 50, 51, ..., 96, 97. This corresponds to a destination range starting at 52 and also containing 48 values: 52, 53, ..., 98, 99. So, seed number 53 corresponds to soil number 55.

// Any source numbers that aren't mapped correspond to the same destination number. So, seed number 10 corresponds to soil number 10.

// So, the entire list of seed numbers and their corresponding soil numbers looks like this:

// seed  soil
// 0     0
// 1     1
// ...   ...
// 48    48
// 49    49
// 50    52
// 51    53
// ...   ...
// 96    98
// 97    99
// 98    50
// 99    51
// With this map, you can look up the soil number required for each initial seed number:

// Seed number 79 corresponds to soil number 81.
// Seed number 14 corresponds to soil number 14.
// Seed number 55 corresponds to soil number 57.
// Seed number 13 corresponds to soil number 13.
// The gardener and his team want to get started as soon as possible, so they'd like to know the closest location that needs a seed. Using these maps, find the lowest location number that corresponds to any of the initial seeds. To do this, you'll need to convert each seed number through other categories until you can find its corresponding location number. In this example, the corresponding types are:

// Seed 79, soil 81, fertilizer 81, water 81, light 74, temperature 78, humidity 78, location 82.
// Seed 14, soil 14, fertilizer 53, water 49, light 42, temperature 42, humidity 43, location 43.
// Seed 55, soil 57, fertilizer 57, water 53, light 46, temperature 82, humidity 82, location 86.
// Seed 13, soil 13, fertilizer 52, water 41, light 34, temperature 34, humidity 35, location 35.
// So, the lowest location number in this example is 35.

// What is the lowest location number that corresponds to any of the initial seed numbers?

#include <iostream>
#include <algorithm>
#include <vector>
#include "../inputReader.h"

static const std::string INPUT_FILE_PATH = "input.txt";

class MapItem;

std::list<int64_t> getSeeds(const std::list<std::string> &rawInput);
std::list<int64_t> splitStringToInts(const std::string &stringToSplit, const char delimiter);
std::list<std::string> getMapLines(const std::list<std::string> &rawInput, const std::string &mapName);
std::list<MapItem> getMapItems(const std::list<std::string> &mapLines);
MapItem getMapItem(const std::string &mapLine);
std::list<std::string> getOnlyMapRawInput(const std::list<std::string> &rawInput);
std::list<int64_t> getNumberListFromMapItems(const std::list<MapItem> mapItems, const std::list<int64_t> numbers);
int64_t getMappedNumber(const std::list<MapItem> mapItems, const int64_t number);

class MapItem
{
public:
    MapItem(int64_t destinationRangeStart, int64_t sourceRangeStart, int64_t rangeLength)
    {
        this->destinationRangeStart = destinationRangeStart;
        this->sourceRangeStart = sourceRangeStart;
        this->rangeLength = rangeLength;
    }

    bool isInSourceRange(int64_t number) const
    {
        return number >= sourceRangeStart && number < sourceRangeStart + rangeLength;
    }

    int64_t getDestinationNumber(int64_t sourceNumber) const
    {
        return destinationRangeStart + (sourceNumber - sourceRangeStart);
    }

    int64_t getDestinationRangeStart() const
    {
        return destinationRangeStart;
    }

    int64_t getSourceRangeStart() const
    {
        return sourceRangeStart;
    }

    int64_t getRangeLength() const
    {
        return rangeLength;
    }

private:
    int64_t destinationRangeStart;
    int64_t sourceRangeStart;
    int64_t rangeLength;
};

std::list<int64_t> getSeeds(const std::list<std::string> &rawInput)
{
    const std::string firstLine = rawInput.front();

    const int64_t colonIndex = firstLine.find(':');
    const std::string seedsAsString = firstLine.substr(colonIndex + 2, firstLine.length() - colonIndex - 2);
    const std::list<int64_t> seeds = splitStringToInts(seedsAsString, ' ');

    return seeds;
}

std::list<int64_t> splitStringToInts(const std::string &stringToSplit, const char delimiter)
{
    std::list<int64_t> splitInts;

    std::string currentNumberAsString;
    for (const char character : stringToSplit)
    {
        if (character == delimiter)
        {
            if (currentNumberAsString == "")
            {
                continue;
            }

            splitInts.push_back(std::stoull(currentNumberAsString));
            currentNumberAsString = "";
        }
        else
        {
            currentNumberAsString += character;
        }
    }

    splitInts.push_back(std::stoull(currentNumberAsString));

    return splitInts;
}

std::list<std::string> getMapLines(const std::list<std::string> &rawInput, const std::string &mapName)
{
    std::list<std::string> mapLines;

    bool mapLinesStarted = false;
    for (const std::string &line : rawInput)
    {
        if (line.find(mapName) != std::string::npos)
        {
            mapLinesStarted = true;
            continue;
        }

        if (!mapLinesStarted)
        {
            continue;
        }

        if (line == "")
        {
            break;
        }

        mapLines.push_back(line);
    }

    return mapLines;
}

std::list<MapItem> getMapItems(const std::list<std::string> &mapLines)
{
    std::list<MapItem> mapItems;

    for (const std::string &line : mapLines)
    {
        const MapItem mapItem = getMapItem(line);
        mapItems.push_back(mapItem);
    }

    return mapItems;
}

MapItem getMapItem(const std::string &mapLine)
{
    const std::list<int64_t> mapLineNumbers = splitStringToInts(mapLine, ' ');
    const std::vector<int64_t> mapLineNumbersVector(mapLineNumbers.begin(), mapLineNumbers.end());

    const int64_t destinationRangeStart = mapLineNumbersVector[0];
    const int64_t sourceRangeStart = mapLineNumbersVector[1];
    const int64_t rangeLength = mapLineNumbersVector[2];
    const MapItem mapItem(destinationRangeStart, sourceRangeStart, rangeLength);

    return mapItem;
}

std::list<std::string> getOnlyMapRawInput(const std::list<std::string> &rawInput)
{
    std::vector<std::string> lines(rawInput.begin(), rawInput.end());
    // skip the 2 first lines
    lines.erase(lines.begin());
    lines.erase(lines.begin());

    return std::list<std::string>(lines.begin(), lines.end());
}

std::list<int64_t> getNumberListFromMapItems(const std::list<MapItem> mapItems, const std::list<int64_t> numbers)
{
    std::list<int64_t> resultNumbers;

    for (const int64_t number : numbers)
    {
        const int64_t resultNumber = getMappedNumber(mapItems, number);
        resultNumbers.push_back(resultNumber);
    }

    return resultNumbers;
}

int64_t getMappedNumber(const std::list<MapItem> mapItems, const int64_t number)
{
    int64_t resultNumber = number;

    for (const MapItem &mapItem : mapItems)
    {
        if (mapItem.isInSourceRange(resultNumber))
        {
            resultNumber = mapItem.getDestinationNumber(resultNumber);
            break;
        }
    }

    return resultNumber;
}

int main(int argc, char *argv[])
{
    const std::list<std::string> rawInput = getInputFromFile(INPUT_FILE_PATH);
    std::list<int64_t> seeds = getSeeds(rawInput);

    const std::list<std::string> onlyMapRawInput = getOnlyMapRawInput(rawInput);

    std::list<MapItem> seedToSoilMap = getMapItems(getMapLines(onlyMapRawInput, "seed-to-soil map"));
    std::list<MapItem> soilToFertilizerMap = getMapItems(getMapLines(onlyMapRawInput, "soil-to-fertilizer map"));
    std::list<MapItem> fertilizerToWaterMap = getMapItems(getMapLines(onlyMapRawInput, "fertilizer-to-water map"));
    std::list<MapItem> waterToLightMap = getMapItems(getMapLines(onlyMapRawInput, "water-to-light map"));
    std::list<MapItem> lightToTemperatureMap = getMapItems(getMapLines(onlyMapRawInput, "light-to-temperature map"));
    std::list<MapItem> temperatureToHumidityMap = getMapItems(getMapLines(onlyMapRawInput, "temperature-to-humidity map"));
    std::list<MapItem> humidityToLocationMap = getMapItems(getMapLines(onlyMapRawInput, "humidity-to-location map"));

    std::list<int64_t> soilNumbers = getNumberListFromMapItems(seedToSoilMap, seeds);
    std::list<int64_t> fertilizerNumbers = getNumberListFromMapItems(soilToFertilizerMap, soilNumbers);
    std::list<int64_t> waterNumbers = getNumberListFromMapItems(fertilizerToWaterMap, fertilizerNumbers);
    std::list<int64_t> lightNumbers = getNumberListFromMapItems(waterToLightMap, waterNumbers);
    std::list<int64_t> temperatureNumbers = getNumberListFromMapItems(lightToTemperatureMap, lightNumbers);
    std::list<int64_t> humidityNumbers = getNumberListFromMapItems(temperatureToHumidityMap, temperatureNumbers);
    std::list<int64_t> locationNumbers = getNumberListFromMapItems(humidityToLocationMap, humidityNumbers);

    const int64_t minLocationNumber = *std::min_element(locationNumbers.begin(), locationNumbers.end());

    std::cout << "Result: " << minLocationNumber << std::endl;

    return EXIT_SUCCESS;
}
