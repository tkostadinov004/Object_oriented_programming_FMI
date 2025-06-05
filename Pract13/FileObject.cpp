#include "FileObject.h"
#include <type_traits>
#include <utility>

void FileObject::swap(FileObject& other)
{
    std::swap(name, other.name);
    std::swap(filesize, other.filesize);
    std::swap(attributes, other.attributes);
}

FileObject::FileObject(const char* name, size_t filesize, unsigned attributes)
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
        FileObject* temp = other.clone();
        swap(*temp);
        delete temp;
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
    return attributes & (unsigned)attr;
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
    attributes |= (unsigned)attr;
}