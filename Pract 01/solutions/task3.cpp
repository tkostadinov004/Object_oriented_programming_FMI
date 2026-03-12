#include <iostream>

size_t countDivisiblesByK(const int* arr, size_t size, int k)
{
	if (!arr || k == 0)
	{
		return 0;
	}

	size_t count = 0;

	for (size_t i = 0; i < size; i++)
	{
		if (arr[i] % k == 0)
		{
			count++;
		}
	}
	return count;
}

void getDivisiblesByK(int*& result, size_t& resultSize,
	const int* first, size_t firstSize,
	const int* second, size_t secondSize, int k)
{
	if (!first || !second || k == 0)
	{
		return;
	}

	delete[] result;

	resultSize = countDivisiblesByK(first, firstSize, k) + countDivisiblesByK(second, secondSize, k);
	result = new int[resultSize];

	int putIndex = 0;
	for (size_t i = 0; i < firstSize; i++)
	{
		if (first[i] % k == 0)
		{
			result[putIndex++] = first[i];
		}
	}
	for (size_t i = 0; i < secondSize; i++)
	{
		if (second[i] % k == 0)
		{
			result[putIndex++] = second[i];
		}
	}
}

void printArray(const int* arr, size_t size)
{
	if (!arr)
	{
		return;
	}

	for (size_t i = 0; i < size; i++)
	{
		std::cout << arr[i] << " ";
	}
	std::cout << std::endl;
}

int main()
{
	constexpr size_t FIRST_SIZE = 5;
	int first[FIRST_SIZE] = { 2, 8, 3, 15, 27 };
	constexpr size_t SECOND_SIZE = 3;
	int second[SECOND_SIZE] = { 5, 9, 4 };

	constexpr size_t K = 3;

	int* result = nullptr;
	size_t resultSize = 0;
	getDivisiblesByK(result, resultSize, first, FIRST_SIZE, second, SECOND_SIZE, K);
	printArray(result, resultSize);
	
	delete[] result; //!!!
}
