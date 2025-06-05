#pragma once
#include "FileObject.h"

class RegularFile : public FileObject
{
	char extension[6];
	char* fullname = nullptr;
	void setFullName(const char* name, const char* extension);
	void setExtension(const char* extension);
	void swap(RegularFile& other);
public:
	RegularFile(const char* name, size_t filesize, unsigned attributes, const char* extension);
	RegularFile(const RegularFile& other);
	RegularFile& operator=(const RegularFile& other);
	virtual ~RegularFile();
	virtual FileObject* clone() const override;

	virtual const char* getName() const override;
	virtual Type getType() const override;
	virtual void print() const override;
	RegularFile operator+(const char* name) const;
	RegularFile& operator+=(const char* name);
};