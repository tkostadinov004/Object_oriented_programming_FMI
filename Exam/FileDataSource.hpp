#pragma once
#include "DataSource.hpp"
#include <istream>

template <class T>
class FileDataSource : public DataSource<T>
{
	std::ifstream is;
	size_t filesize = 0;
	size_t pos = 0;
public:
	FileDataSource(const char* name) : is(name) { is.seekg(0, std::ios::end); filesize = is.tellg(); is.clear(); is.seekg(0, std::ios::beg); }
	FileDataSource(const FileDataSource&) = delete;
	FileDataSource& operator=(const FileDataSource&) = delete;

	bool hasNext(size_t count) const override;
	T* next() override;
	bool reset() override;
};

template<class T>
bool FileDataSource<T>::hasNext(size_t count) const
{
	if (is.eof()) return false;

	return filesize - pos >= count * sizeof(T);
}

template<class T>
T* FileDataSource<T>::next()
{
	T* buf = (T*)operator new(sizeof(T));
	is.read((char*)buf, sizeof(T));
	pos += sizeof(T);
	return buf;
}

template<class T>
bool FileDataSource<T>::reset()
{
	is.clear();
	is.seekg(0, std::ios::beg);
	return true;
}