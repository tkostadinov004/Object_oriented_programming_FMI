#include <iostream>
#include <fstream>
#include "Session.h"

int main()
{
    constexpr size_t FILENAME_BUFFER_SIZE = 512;
    char filename[FILENAME_BUFFER_SIZE];
    std::cin >> filename;

    countIntervals(filename);
}