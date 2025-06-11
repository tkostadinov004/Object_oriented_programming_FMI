#include <iostream>
#include <fstream>
#include "AlternateDataSource.hpp"
#include "GeneratorDataSource.hpp"
#include "ArrayDataSource.hpp"
#include "FileDataSource.hpp"

void fillFib(size_t count, int** arr)
{
	int sll = 1, l = 1;
	arr[0] = arr[1] = new int(l);
	for (size_t i = 2; i < count; i++)
	{
		arr[i] = new int(sll + l);
		sll = l;
		l = *arr[i];
	}
}

struct Rand
{
	int* operator()() { return new int(rand()); } 
};

bool isPrime(int num)
{
	if (num < 2) return false;
	for (size_t i = 2; i <= sqrt(num); i++)
	{
		if (num % i == 0) return false;
	}
	return true;
}

class Primes
{
	int curr = 1;
public:
	int* operator()() 
	{
		while (!isPrime(curr))
		{
			curr++;
		}
		int* res = new int(curr);
		curr++;
		return res;
	}
};

int main()
{
	size_t n;
	std::cin >> n;

	int** nums = new int*[n];
	fillFib(n, nums);

	DataSource<int>* arr[3];
	arr[0] = new FileDataSource<int>("bin.dat");
	arr[1] = new GeneratorDataSource<int, Rand>();
	arr[2] = new ArrayDataSource<int>(nums, n);

	AlternateDataSource<int> ds(arr, 3);

	for (size_t i = 0; i < 90; i++)
	{
		int* next = ds.next();
		std::cout << *next << "\n";
		delete next;
	}
	delete arr[0];
	delete arr[1];
	delete arr[2];
	delete[] nums;
}