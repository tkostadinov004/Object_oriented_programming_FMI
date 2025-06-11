#pragma once
#include "DataSource.hpp"

template <class T, class Generator>
class GeneratorDataSource : public DataSource<T>
{
	Generator generator;
public:
	bool hasNext(size_t count) const override;
	T* next() override;
	bool reset() override;
};

template<class T, class Generator>
bool GeneratorDataSource<T, Generator>::hasNext(size_t count) const
{
	return true;
}

template<class T, class Generator>
T* GeneratorDataSource<T, Generator>::next()
{
	return generator();
}

template<class T, class Generator>
bool GeneratorDataSource<T, Generator>::reset()
{
	return true;
}
