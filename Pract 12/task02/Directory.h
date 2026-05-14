#pragma once
#include "FileObject.h"

class Directory : public FileObject
{
	FileObject** data;
	size_t objectsCount = 0;
	size_t capacity = 1;

	void resize(size_t newCapacity);
	void swap(Directory& other);
public:
	Directory(const char* name, unsigned char attributes);
	Directory(const Directory& other);
	Directory& operator=(const Directory& other);
	virtual ~Directory();
	virtual FileObject* clone() const override;

	virtual size_t getSize() const override;
	virtual Type getType() const override;
	size_t getObjectsCount() const;
	virtual void print() const override;

	Directory operator+(const char* name) const;
	Directory operator+(const FileObject& obj) const;

	Directory& operator+=(const char* name);
	Directory& operator+=(const FileObject& obj);

	FileObject* operator[](const char* name);
	const FileObject* operator[](const char* name) const;

	FileObject* operator[](int index);
	const FileObject* operator[](int index) const;
};