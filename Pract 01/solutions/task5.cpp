#include <iostream>

void map(int* arr, size_t size, int(*mapper)(int))
{
	if (!arr || !mapper)
	{
		return;
	}

	for (size_t i = 0; i < size; i++)
	{
		arr[i] = mapper(arr[i]);
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

int multiplyBy2(int x)
{
	return x * 2;
}

int main()
{
	constexpr size_t SIZE = 5;
	{
		int arr[SIZE] = { 1,2,3,4,5 };

		map(arr, SIZE, [](int x) {
			return x * 2;
		});
		printArray(arr, SIZE);
	}
	{
		int arr[SIZE] = { 1,2,3,4,5 };

		map(arr, SIZE, multiplyBy2);
		printArray(arr, SIZE);
	}
}
