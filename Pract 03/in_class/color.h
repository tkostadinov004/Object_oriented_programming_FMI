#include <fstream>

const char COLOR_DELIMITER = '|';

struct Color
{
    unsigned R:8;
    unsigned G:8;
    unsigned B:8;
};
unsigned getRgbValue(const Color& col);
void setColor(Color& obj, unsigned long rgb);


size_t getColorCount(std::ifstream& ifs);

void readColor(std::ifstream& ifs, Color& obj);
Color* readColors(std::ifstream& ifs, size_t& size);
Color* readColors(const char* fileName, size_t& size);


void writeColor(std::ofstream& ofs, const Color& col);
void writeColors(std::ofstream& ofs, const Color* colorArr, size_t size);
void writeColors(const char* fileName, const Color* colorArr, size_t size);
