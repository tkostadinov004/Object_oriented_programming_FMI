#include "RegularFile.h"
#include "string.h"
#include <stdexcept>
#pragma warning (disable: 4996)

static int find(const char* str, char c)
{
	if (!str) throw std::invalid_argument("String cannot be nullptr!");

	for (size_t i = 0; str[i] != '\0'; i++)
	{
		if (str[i] == c) return i;
	}
	return -1;
}

static char* substr(const char* str, int start, int end)
{
	if (!str) throw std::invalid_argument("String cannot be nullptr!");
	if (start > end) throw std::invalid_argument("Start cannot be after end!");

	size_t len = strlen(str);
	if (start < 0 || end < 0 || start >= len || end >= len) throw std::invalid_argument("Start and end cannot be out of bounds!");
	
	char* result = new char[end - start + 2];
	for (size_t i = start; i <= end; i++)
	{
		result[i - start] = str[start];
	}
	return result;
}

void RegularFile::setFullName(const char* name, const char* extension)
{
	if (!name || !extension || !(*extension)) throw std::invalid_argument("Invalid arguments");

	size_t extensionLen = strlen(extension);

	int dotIndex = find(name, '.');
	size_t nameSize = dotIndex != -1 ? dotIndex : strlen(name);
	size_t size = nameSize + 1 + extensionLen + 1;
	char* temp = new char[size] {0};

	try
	{
		if (dotIndex != -1)
		{
			char* realName = substr(name, 0, dotIndex - 1);
			strcat(temp, realName);
			delete[] realName;
		}
		else
		{
			strcat(temp, name);
		}
		strcat(temp, ".");
		strcat(temp, extension);
		setName(temp);
	}
	catch (const std::exception& e)
	{
		delete[] temp;
		throw e;
	}
}

void RegularFile::setExtension(const char* extension)
{
	if (!extension || strlen(extension) > 5) throw 37;

	strcpy(this->extension, extension);
	setFullName(getName(), extension);
}

RegularFile::RegularFile(const char* name, size_t filesize, unsigned char attributes, const char* extension)
	: FileObject(name, filesize, attributes)
{
	setExtension(extension);
	setFullName(name, extension);
}

FileObject* RegularFile::clone() const
{
	return new RegularFile(*this);
}

Type RegularFile::getType() const
{
	return Type::File;
}

RegularFile RegularFile::operator+(const char* content) const
{
	RegularFile temp(*this);
	temp += content;
	return temp;
}

RegularFile& RegularFile::operator+=(const char* content)
{
	if (is(Attribute::ReadOnly)) throw std::logic_error("File is read only!");
	if (!content) throw std::invalid_argument("Content cannot be nullptr");

	size_t size = strlen(content);
	setSize(getSize() + size);
	return *this;
}
