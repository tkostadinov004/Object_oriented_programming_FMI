#pragma once
#include "FileObject.h"

class RegularFile : public FileObject
{
	const static size_t EXTENSION_LENGTH = 5;

	char extension[EXTENSION_LENGTH + 1];
	void setFullName(const char* name, const char* extension);
	void setExtension(const char* extension);
public:
	RegularFile(const char* name, size_t filesize, unsigned char attributes, const char* extension);
	virtual FileObject* clone() const override;

	virtual Type getType() const override;
	RegularFile operator+(const char* name) const;
	RegularFile& operator+=(const char* name);
};