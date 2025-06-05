#include "RegularFile.h"
#include "string.h"
#include <stdexcept>
#include <iostream>
#pragma warning (disable: 4996)

void RegularFile::setFullName(const char* name, const char* extension)
{
    if (!name || !extension) throw std::invalid_argument("Invalid arguments");

    size_t extensionLen = strlen(extension);
    size_t size = strlen(name) + 1 + extensionLen + 1;
    char* temp = new char[size] {0};
    strcat(temp, name);
    if (extensionLen > 0)
    {
        strcat(temp, ".");
        strcat(temp, extension);
    }

    delete[] fullname;
    fullname = temp;
}

void RegularFile::setExtension(const char* extension)
{
    if (!extension || strlen(extension) > 5) throw 37;

    strcpy(this->extension, extension);
}

void RegularFile::swap(RegularFile& other)
{
    std::swap(fullname, other.fullname);
    std::swap(extension, other.extension);
}

RegularFile::RegularFile(const char* name, size_t filesize, unsigned attributes, const char* extension)
    : FileObject(name, filesize, attributes)
{
    setExtension(extension);
    setFullName(name, extension);
}

RegularFile::RegularFile(const RegularFile& other) : FileObject(other)
{
    setExtension(other.extension);
    setFullName(other.fullname, "");
}

RegularFile& RegularFile::operator=(const RegularFile& other)
{
    if (this != &other)
    {
        RegularFile temp(other);
        swap(temp);
    }
    return *this;
}

RegularFile::~RegularFile()
{
    delete[] fullname;
}

FileObject* RegularFile::clone() const
{
    return new RegularFile(*this);
}

const char* RegularFile::getName() const
{
    return fullname;
}

Type RegularFile::getType() const
{
    return Type::File;
}

void RegularFile::print() const
{
    std::cout << fullname << " " << getSize() << std::endl;
    std::cout << "Hidden: " << (is(Attribute::Hidden) ? "yes" : "no") << std::endl;
    std::cout << "Read only: " << (is(Attribute::ReadOnly) ? "yes" : "no") << std::endl;
    std::cout << "Archiveable: " << (is(Attribute::Archiveable) ? "yes" : "no") << std::endl;
    std::cout << "System: " << (is(Attribute::System) ? "yes" : "no") << std::endl;
}

RegularFile RegularFile::operator+(const char* content) const
{
    RegularFile temp(*this);
    temp += content;
    return temp;
}

RegularFile& RegularFile::operator+=(const char* content)
{
    if (is(Attribute::ReadOnly))
    {
        throw std::logic_error("File is read only!");
    }
    if (!content) throw std::invalid_argument("Content cannot be nullptr");

    size_t size = strlen(content);
    setSize(getSize() + size);
    return *this;
}
