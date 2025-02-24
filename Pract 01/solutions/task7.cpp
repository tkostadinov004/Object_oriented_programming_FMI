#include <iostream>

void swap(int& a, int& b)
{
	int temp = a;
	a = b;
	b = temp;
}

void partition(int* arr, size_t size, bool(*pred)(int))
{
	if (!arr || !pred)
	{
		return;
	}

	int partitionIndex = 0;

	for (size_t i = 0; i < size; i++)
	{
		if (pred(arr[i]))
		{
			swap(arr[i], arr[partitionIndex]);
			partitionIndex++;
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
	constexpr size_t SIZE = 5;
	{
		int arr[SIZE] = { 1,2,3,4,5 };

		partition(arr, SIZE, [](int x) {
			return x % 2 == 0;
		});
		printArray(arr, SIZE);
	}
	{
		int arr[SIZE] = { 1,2,3,4,5 };

		partition(arr, SIZE, isEven);
		printArray(arr, SIZE);
	}
}
