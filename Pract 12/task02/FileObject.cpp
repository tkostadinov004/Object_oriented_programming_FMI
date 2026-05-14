#include "FileObject.h"
#include <type_traits>
#include <utility>
#include <string.h>
#include <iostream>
#pragma warning (disable: 4996)

void FileObject::printBasicData() const
{
    std::cout << getName() << " " << getSize() << std::endl;
    std::cout << "Hidden: " << (is(Attribute::Hidden) ? "yes" : "no") << std::endl;
    std::cout << "Read only: " << (is(Attribute::ReadOnly) ? "yes" : "no") << std::endl;
    std::cout << "Archiveable: " << (is(Attribute::Archiveable) ? "yes" : "no") << std::endl;
    std::cout << "System: " << (is(Attribute::System) ? "yes" : "no") << std::endl;
}

FileObject::FileObject(const char* name, size_t filesize, unsigned char attributes)
{
    setName(name);
    setSize(filesize);
    this->attributes = attributes;
}

FileObject::FileObject(const FileObject& other)
    : filesize(other.filesize), attributes(other.attributes)
{
    setName(other.name);
}

FileObject& FileObject::operator=(const FileObject& other)
{
    if (this != &other)
    {
        char* tempName = new char[strlen(other.name) + 1];
        try
        {
            strcpy(tempName, other.name);
        }
        catch (const std::exception& e)
        {
            delete[] tempName;
            throw e;
        }
        delete[] name;
        name = tempName;

        filesize = other.filesize;
        attributes = other.attributes;
    }
    return *this;
}

FileObject::~FileObject()
{
    delete[] name;
}

const char* FileObject::getName() const
{
    return name;
}

bool FileObject::is(Attribute attr) const
{
    return attributes & (unsigned char)attr;
}

size_t FileObject::getSize() const
{
    return filesize;
}

void FileObject::setDirectory(const Directory* dir)
{
    this->dir = dir;
}

void FileObject::setSize(size_t filesize)
{
    this->filesize = filesize;
}

void FileObject::setAttribute(Attribute attr)
{
    attributes |= (unsigned char)attr;
}

void FileObject::print() const
{
    printBasicData();
}
