

#include <iostream>
#include "color.h"

int main()
{
    size_t size = 0;
    Color* arr = readColors("colors.txt", size);
    for (size_t i = 0; i < size; i++)
    {
        std::cout << arr[i].R << '|' << arr[i].G << '|' << arr[i].B << std::endl;
    }

    writeColors("colors2.txt", arr, size);

    delete[] arr;
}

