#include "color.h"
#include "functions.h"

size_t getColorCount(std::ifstream& ifs)
{
    if (!ifs.is_open())
        return 0;

    return getOccurences(ifs, COLOR_DELIMITER) + 1;
}

void setColor(Color& obj, unsigned long rgb)
{
    obj.R = rgb / 65536;
    rgb -= obj.R * 65536;
    
    obj.G = rgb / 256;
    rgb -= obj.G * 256;

    obj.B = rgb;
}

void readColor(std::ifstream& ifs, Color& obj)
{
    unsigned rgb;
    ifs >> rgb;
    setColor(obj, rgb);
}


Color* readColors(std::ifstream& ifs, size_t& size)
{
    size = getColorCount(ifs);

    if(size == 0)
        return nullptr;

    Color* colorArr = new Color[size];

    for (size_t i = 0; i < size; i++)
    {
        readColor(ifs, colorArr[i]);
        ifs.ignore();
    }
    
    return colorArr;
}

Color* readColors(const char* fileName, size_t& size)
{
    std::ifstream ifs(fileName);

    if (!ifs.is_open())
        return nullptr;

    return readColors(ifs, size);
}

unsigned getRgbValue(const Color& col)
{
    return col.R == 0 && col.G == 0 && col.B == 0 ?
           256 * 256 * 256 :
           col.R * 256 * 256 + col.G * 256 + col.B;
}

void writeColor(std::ofstream& ofs, const Color& col)
{
    ofs << getRgbValue(col);
}


void writeColors(std::ofstream& ofs, const Color* colorArr, size_t size)
{
    for (size_t i = 0; i < size - 1; i++)
    {
        writeColor(ofs, colorArr[i]);
        ofs << COLOR_DELIMITER;
    }
    writeColor(ofs, colorArr[size - 1]);
}


void writeColors(const char* fileName, const Color* colorArr, size_t size)
{
    std::ofstream ofs(fileName);
    if(!ofs.is_open())
        return;

    writeColors(ofs, colorArr, size);
}
