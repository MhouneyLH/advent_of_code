#include <iostream>
#include "../inputReader.h"

static const std::string INPUT_FILE_PATH = "input.txt";

int main(int argc, char *argv[])
{
    const std::list<std::string> rawInput = getInputFromFile(INPUT_FILE_PATH);

    return EXIT_SUCCESS;
}
