#include "functions.h"

size_t getOccurences(std::ifstream& ifs, char ch)
{
    size_t count = 0;
    size_t currIndex = ifs.tellg();
    ifs.seekg(0);
    char curr;
    while (true)
    {
        curr = ifs.get();
        if (ifs.eof())
            break;

        if (curr == ch)
            count++;
    }

    ifs.clear();
    ifs.seekg(currIndex);
    return count;
}
