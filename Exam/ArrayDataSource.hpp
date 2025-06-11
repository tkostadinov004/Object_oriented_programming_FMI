#pragma once
#include "DataSource.hpp"
#include <new>

template <class T>
class ArrayDataSource : public DataSource<T>
{
	T** arr;
	size_t size = 0;
	size_t capacity = 1;

	size_t get = 0;
	void resize(size_t newCapacity);
	void swap(ArrayDataSource& other);
public:
	ArrayDataSource(const T** arr, size_t size);
	ArrayDataSource(const ArrayDataSource& other);
	ArrayDataSource& operator=(const ArrayDataSource& other);
	~ArrayDataSource();

	bool hasNext(size_t count) const override;
	T* next() override;
	bool reset() override;
	ArrayDataSource operator+(const T& obj) const;
	ArrayDataSource& operator+=(const T& obj);

	ArrayDataSource& operator--();
	ArrayDataSource operator--(int dummy);
};

template<class T>
void ArrayDataSource<T>::resize(size_t newCapacity)
{
	T** newData = new T * [newCapacity];
	for (size_t i = 0; i < size; i++)
	{
		newData[i] = arr[i];
	}
	delete[] arr;
	arr = newData;
	capacity = newCapacity;
}

template<class T>
void ArrayDataSource<T>::swap(ArrayDataSource& other)
{
	std::swap(arr, other.arr);
	std::swap(size, other.size);
	std::swap(capacity, other.capacity);
}

template<class T>
ArrayDataSource<T>::ArrayDataSource(const T** arr, size_t size) : capacity(size)
{
	this->arr = new T * [size];
	for (size_t i = 0; i < size; i++)
	{
		this->operator+=(*arr[i]);
	}
}

template<class T>
ArrayDataSource<T>::ArrayDataSource(const ArrayDataSource& other) : DataSource(other), size(other.size), capacity(other.capacity)
{
	this->arr = new T * [other.capacity];
	for (size_t i = 0; i < size; i++)
	{
		this->operator+=(*other.arr[i]);
	}
}

template<class T>
ArrayDataSource<T>& ArrayDataSource<T>::operator=(const ArrayDataSource& other)
{
	if (this != &other)
	{
		ArrayDataSource temp(other);
		swap(temp);
	}
	return *this;
}

template<class T>
ArrayDataSource<T>::~ArrayDataSource()
{
	for (size_t i = 0; i < size; i++)
	{
		delete arr[i];
	}
	delete[] arr;
}

template<class T>
bool ArrayDataSource<T>::hasNext(size_t count) const
{
	return count == 0 || get + count - 1 < size;
}

template<class T>
T* ArrayDataSource<T>::next()
{
	return new T(*arr[get++]);
}

template<class T>
bool ArrayDataSource<T>::reset()
{
	get = 0;
	return true;
}

template<class T>
ArrayDataSource<T> ArrayDataSource<T>::operator+(const T& obj) const
{
	ArrayDataSource<T> temp(*this);
	temp += obj;

	return temp;
}

template<class T>
ArrayDataSource<T>& ArrayDataSource<T>::operator+=(const T& obj)
{
	if (size == capacity) resize(capacity * 2);

	arr[size++] = new T(obj);
	return *this;
}

template<class T>
ArrayDataSource<T>& ArrayDataSource<T>::operator--()
{
	if (get == 0) throw 123;

	get--;
	return *this;
}

template<class T>
ArrayDataSource<T> ArrayDataSource<T>::operator--(int dummy)
{
	ArrayDataSource<T> temp(*this);
	--(*this);

	return temp;
}