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

bool isEven(int x)
{
	return x % 2 == 0;
}
int main()
{
	constexpr size_t SIZE = 10;
	int arr[SIZE] = { 5,1,0,-2,4,1,6,3,9,7 };
	
	std::cout << getCountOfElementsSatisyingACondition(arr, SIZE, isEven) << std::endl; // ptr to function

	std::cout << getCountOfElementsSatisyingACondition(arr, SIZE, [](int a) { // lambda function
		return a % 2 == 0;
	}) << std::endl;	
}
