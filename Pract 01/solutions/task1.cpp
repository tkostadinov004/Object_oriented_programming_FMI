#include <iostream>

bool isDigit(char c)
{
	return c >= '0' && c <= '9';
}

size_t countDigits(const char* str)
{
	if (!str)
	{
		return 0;
	}

	size_t count = 0;
	while (*str)
	{
		if (isDigit(*str))
		{
			count++;
		}
		str++;
	}
	return count;
}

char* filterDigits(const char* str)
{
	if (!str)
	{
		return nullptr;
	}

	size_t digitsCount = countDigits(str);
	char* result = new char[digitsCount + 1]; // +1 because of '\0'!!!

	int putIndex = 0;
	while (*str)
	{
		if (isDigit(*str))
		{
			result[putIndex++] = *str;
		}
		str++;
	}
	result[putIndex] = '\0';

	return result;
}

int main()
{
	char* filtered = filterDigits(")Lso!c6d%9ucpB*CED5su2DH%&7t4)*");
	std::cout << filtered << std::endl;

	delete[] filtered; //!!!
}
