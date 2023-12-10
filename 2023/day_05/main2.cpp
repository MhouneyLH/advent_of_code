//! PROBLEM - NOT FINISHED!
// Everyone will starve if you only plant such a small number of seeds. Re-reading the almanac, it looks like the seeds: line actually describes ranges of seed numbers.

// The values on the initial seeds: line come in pairs. Within each pair, the first value is the start of the range and the second value is the length of the range. So, in the first line of the example above:

// seeds: 79 14 55 13
// This line describes two ranges of seed numbers to be planted in the garden. The first range starts with seed number 79 and contains 14 values: 79, 80, ..., 91, 92. The second range starts with seed number 55 and contains 13 values: 55, 56, ..., 66, 67.

// Now, rather than considering four seed numbers, you need to consider a total of 27 seed numbers.

// In the above example, the lowest location number can be obtained from seed number 82, which corresponds to soil 84, fertilizer 84, water 84, light 77, temperature 45, humidity 46, and location 46. So, the lowest location number is 46.

// Consider all of the initial seed numbers listed in the ranges on the first line of the almanac. What is the lowest location number that corresponds to any of the initial seed numbers?

#include <iostream>
#include <algorithm>
#include <vector>
#include "../inputReader.h"

static const std::string INPUT_FILE_PATH = "input.txt";

class MapItem;

std::list<int64_t> getSeeds(const std::list<std::string> &rawInput);
std::vector<int64_t> splitStringToInts(const std::string &stringToSplit, const char delimiter);
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
    const std::vector<int64_t> seeds = splitStringToInts(seedsAsString, ' ');

    std::list<int64_t> realSeeds;
    for (int i = 0; i < seeds.size(); i += 2)
    {
        const int64_t seedStart = seeds[i];
        const int64_t seedLength = seeds[i + 1];

        for (int64_t j = seedStart; j < seedStart + seedLength; j++)
        {
            realSeeds.push_back(j);
        }
    }

    return realSeeds;
}

std::vector<int64_t> splitStringToInts(const std::string &stringToSplit, const char delimiter)
{
    std::vector<int64_t> splitInts;

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
    const std::vector<int64_t> mapLineNumbers = splitStringToInts(mapLine, ' ');

    const int64_t destinationRangeStart = mapLineNumbers[0];
    const int64_t sourceRangeStart = mapLineNumbers[1];
    const int64_t rangeLength = mapLineNumbers[2];
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
