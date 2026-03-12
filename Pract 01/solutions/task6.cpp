#include <iostream>

size_t getCountOfElementsSatisyingACondition(const int* arr, size_t size, bool(*pred)(int))
{
	if (!arr || !pred)
	{
		return 0;
	}

	size_t count = 0;
	for (size_t i = 0; i < size; i++)
	{
		if (pred(arr[i]))
		{
			count++;
		}
		// could also be count += pred(arr[i])
	}
	return count;
}

void filter(const int* arr, size_t size, int*& result, size_t& resultSize, bool(*pred)(int))
{
	if (!arr || !pred)
	{
		return;
	}

	delete[] result;
	resultSize = getCountOfElementsSatisyingACondition(arr, size, pred);
	result = new int[resultSize];
	int putIndex = 0;

	for (size_t i = 0; i < size; i++)
	{
		if (pred(arr[i]))
		{
			result[putIndex++] = arr[i];
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

bool isEven(int x)
{
	return x % 2 == 0;
}

int main()
{
	constexpr size_t SIZE = 6;
	{
		int arr[SIZE] = { 1,2,3,4,5,6 };
		int* result = nullptr;
		size_t resultSize = 0;

		filter(arr, SIZE, result, resultSize, [](int x) {
			return x % 2 == 0;
		});
		printArray(result, resultSize);
		
		delete[] result; // !!!
	}
	{
		int arr[SIZE] = { 1,2,3,4,5,6 };
		int* result = nullptr;
		size_t resultSize = 0;

		filter(arr, SIZE, result, resultSize, isEven);
		printArray(result, resultSize);

		delete[] result; // !!!
	}
}
