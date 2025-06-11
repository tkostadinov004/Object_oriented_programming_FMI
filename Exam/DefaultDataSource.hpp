#pragma once
#include "DataSource.hpp"
#include <new>

template <class T>
class DefaultDataSource : public DataSource<T>
{
public:
	bool hasNext(size_t count) const override;
	T* next() override;
	bool reset() override;
};

template<class T>
bool DefaultDataSource<T>::hasNext(size_t count) const
{
	return true;
}

template<class T>
T* DefaultDataSource<T>::next()
{
	return new T();
}

template<class T>
bool DefaultDataSource<T>::reset()
{
	return true;
}
