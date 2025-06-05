#include "Directory.h"
#include <string.h>
#include <exception>
#include <iostream>
#include "RegularFile.h"
#pragma warning (disable: 4996)

void Directory::resize(size_t newCapacity)
{
	FileObject** newData = new FileObject * [newCapacity];
	for (size_t i = 0; i < objectsCount; i++)
	{
		newData[i] = data[i];
	}
	delete[] data;
	data = newData;
	capacity = newCapacity;
}

void Directory::swap(Directory& other)
{
	std::swap(other.data, data);
	std::swap(other.objectsCount, objectsCount);
	std::swap(other.capacity, capacity);
}

Directory::Directory(const char* name, unsigned attributes)
	: FileObject(name, 0, attributes)
{
	data = new FileObject * [capacity];
}

Directory::Directory(const Directory& other) : FileObject(other)
{
	data = new FileObject * [other.capacity];
	for (size_t i = 0; i < other.objectsCount; i++)
	{
		try
		{
			(*this) += *other.data[i];
		}
		catch (std::exception& e)
		{
			for (size_t j = 0; j < i; j++)
			{
				delete data[j];
			}
			delete[] data;
			throw e;
		}
	}
}

Directory& Directory::operator=(const Directory& other)
{
	if (this != &other)
	{
		Directory temp(other);
		swap(temp);
	}
	return *this;
}

Directory::~Directory()
{
	for (size_t i = 0; i < objectsCount; i++)
	{
		delete data[i];
	}
	delete[] data;
}

FileObject* Directory::clone() const
{
	return new Directory(*this);
}

size_t Directory::getSize() const
{
	size_t size = 0;
	for (size_t i = 0; i < objectsCount; i++)
	{
		size += data[i]->getSize();
	}
	return size;
}

Type Directory::getType() const
{
	return Type::Dir;
}

size_t Directory::getObjectsCount() const
{
	return objectsCount;
}

void Directory::print() const
{
	for (size_t i = 0; i < objectsCount; i++)
	{
		if (!is(Attribute::Hidden) && !is(Attribute::System))
		{
			data[i]->print();
			std::cout << std::endl;
		}
	}
}

Directory Directory::operator+(const char* name) const
{
	if (is(Attribute::ReadOnly))
	{
		throw std::logic_error("Directory is read-only!");
	}
	Directory temp(*this);
	temp += name;
	return temp;
}

Directory Directory::operator+(const FileObject& obj) const
{
	if (is(Attribute::ReadOnly))
	{
		throw std::logic_error("Directory is read-only!");
	}
	Directory temp(*this);
	FileObject* cp = obj.clone();
	temp += *cp;
	delete cp;
	return temp;
}

Directory& Directory::operator+=(const char* name)
{
	if (is(Attribute::ReadOnly))
	{
		throw std::logic_error("Directory is read-only!");
	}
	if (!name) throw std::invalid_argument("Name cannot be nullptr!");

	RegularFile file(name, 0, 0, "");
	(*this) += file;
	return *this;
}

Directory& Directory::operator+=(FileObject& obj)
{
	if (is(Attribute::ReadOnly))
	{
		throw std::logic_error("Directory is read-only!");
	}
	if ((*this)[obj.getName()] != nullptr)
	{
		throw std::logic_error("File with such a name already exists");
	}

	if (objectsCount == capacity)
	{
		resize(capacity * 2);
	}
	obj.setDirectory(this);
	data[objectsCount] = obj.clone();
	objectsCount++;
	return *this;
}

FileObject* Directory::operator[](const char* name)
{
	for (size_t i = 0; i < objectsCount; i++)
	{
		if (strcmp(name, data[i]->getName()) == 0) return data[i];
	}
	return nullptr;
}

const FileObject* Directory::operator[](const char* name) const
{
	for (size_t i = 0; i < objectsCount; i++)
	{
		if (strcmp(name, data[i]->getName()) == 0) return data[i];
	}
	return nullptr;
}

FileObject* Directory::operator[](int index)
{
	return data[index];
}

const FileObject* Directory::operator[](int index) const
{
	return data[index];
}

void FileObject::setName(const char* name)
{
	if (this->name && strcmp(this->name, name) == 0)
	{
		return;
	}
	if (dir && (*dir)[name] != nullptr)
	{
		throw std::logic_error("File with such a name already exists!");
	}
	char* temp = new char[strlen(name) + 1];
	strcpy(temp, name);
	delete[] this->name;
	this->name = temp;
}