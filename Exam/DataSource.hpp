#pragma once

template <class T>
struct FetchResult
{
	T** data;
	size_t size;
};

template <class T>
class DataSource
{
public:
	bool hasNext() const { return hasNext(1); }
	virtual bool hasNext(size_t count) const = 0;
	virtual T* next() = 0;
	FetchResult<T> next(size_t count);
	virtual bool reset() = 0;
	virtual T* operator()();
	operator bool() const;
	
	friend DataSource& operator>>(DataSource& obj, T& data);
};

template<class T>
FetchResult<T> DataSource<T>::next(size_t count)
{
	T** result = new T * [count];
	for (size_t i = 0; i < count; i++)
	{
		result[i] = next();
		if (!result[i])
		{
			for (size_t j = 0; j < i; j++)
			{
				delete result[i];
			}
			delete[] result;
		}
	}
	return FetchResult{ result, count };
}

template<class T>
T* DataSource<T>::operator()()
{
	return next();
}

template<class T>
DataSource<T>::operator bool() const
{
	return hasNext();
}

template <class T>
DataSource<T>& operator>>(DataSource<T>& obj, T& data)
{
	data = obj.next();
	return obj;
}