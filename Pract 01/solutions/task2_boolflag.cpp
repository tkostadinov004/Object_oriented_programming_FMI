#include <iostream>

bool isLower(char c)
{
	return c >= 'a' && c <= 'z';
}

bool isUpper(char c)
{
	return c >= 'A' && c <= 'Z';
}

bool isLetter(char c)
{
	return isLower(c) || isUpper(c);
}

size_t countWords(const char* str)
{
	if (!str)
	{
		return 0;
	}

	bool isInWord = false;
	size_t count = 0;

	while (*str)
	{
		if (!isInWord && isLetter(*str))
		{
			isInWord = true;
		}
		else if (isInWord && !isLetter(*str))
		{
			count++;
			isInWord = false;
		}
		str++;
	}

	if (isInWord)
	{
		count++;
	}

	return count;
}

int main()
{
	std::cout << countWords("    ") << std::endl;
	std::cout << countWords("test") << std::endl;
	std::cout << countWords("Good morning, Vietnam!") << std::endl;
	std::cout << countWords("  Good  morning,     Vietnam!") << std::endl;
	std::cout << countWords("  Good  morning,     Vietnam!    ") << std::endl;
	std::cout << countWords("Good  morning, Vietnam!    ") << std::endl;
}
