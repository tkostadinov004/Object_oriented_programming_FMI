#pragma once
#include "DataSource.hpp"
#include <new>

template <class T>
class AlternateDataSource : public DataSource<T>
{
	DataSource<T>** dataSources;
	size_t size;

	size_t get = 0;
	size_t emptyCount = 0;
public:
	AlternateDataSource(DataSource<T>** dataSources, size_t size) : dataSources(dataSources), size(size) {}
	bool hasNext(size_t count) const override;
	T* next() override;
	bool reset() override;
};

template<class T>
bool AlternateDataSource<T>::hasNext(size_t count) const
{
	for (size_t i = 0; i < size; i++)
	{
		for (size_t j = count; j > 0; j--)
		{
			if (dataSources[i]->hasNext(j)) 
			{
				count -= j;
				break;
			}
		}
		if (count == 0) return true;
	}
	return false;
}

template<class T>
T* AlternateDataSource<T>::next()
{
	while (!dataSources[get]->hasNext())
	{
		get = (get + 1) % size;
	}
	T* res = dataSources[get]->next();
	get = (get + 1) % size;
	return res;
}

template<class T>
bool AlternateDataSource<T>::reset()
{
	return false;
}
