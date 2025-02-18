#include <iostream>

void swap(int& a, int& b)
{
	int temp = a;
	a = b;
	b = temp;
}

void selectionSort(int* arr, size_t size, bool(*comparator)(int, int))
{
	if (!arr || !comparator)
	{
		return;
	}

	for (size_t i = 0; i < size - 1; i++)
	{
		int compMinIndex = i;
		for (size_t j = i + 1; j < size; j++)
		{
			if (comparator(arr[j], arr[compMinIndex]))
			{
				compMinIndex = j;
			}
		}
		if (compMinIndex != i)
		{
			swap(arr[compMinIndex], arr[i]);
		}
	}
}
void printArr(const int* arr, size_t size)
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


bool ascendingComparator(int first, int second)
{
	return first < second;
}
bool descendingComparator(int first, int second)
{
	return first > second; // second < first
}
bool evensBeforeOddsComparator(int first, int second)
{
	return first % 2 == 0;
}
int main()
{
	constexpr size_t SIZE = 10;
	{
    // Sorting in ascending order
		int arr[SIZE] = { 5,1,0,-2,4,1,6,3,9,7 };

		selectionSort(arr, SIZE, ascendingComparator); // ptr to function
		selectionSort(arr, SIZE, [](int a, int b) { // lambda function
			return a < b;
		});

		printArr(arr, SIZE);
	}
	{
    // Sorting in descending order
		int arr[SIZE] = { 5,1,0,-2,4,1,6,3,9,7 };

		selectionSort(arr, SIZE, descendingComparator); // ptr to function
		selectionSort(arr, SIZE, [](int a, int b) { // lambda function
			return a > b; // b < a
		});

		printArr(arr, SIZE);
	}
	{
    // Reordering the array in a way such that all even numbers come before all odd numbers
		int arr[SIZE] = { 5,1,0,-2,4,1,6,3,9,7 };

		selectionSort(arr, SIZE, evensBeforeOddsComparator); // ptr to function
		selectionSort(arr, SIZE, [](int a, int b) { // lambda function
			return a % 2 == 0;
		});

		printArr(arr, SIZE);
	}
}
