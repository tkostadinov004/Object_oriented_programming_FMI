#pragma once

enum class Attribute
{
	Hidden = 1,
	System = 2,
	Archiveable = 4,
	ReadOnly = 8
};
enum class Type
{
	Dir,
	File
};

class Directory;

class FileObject
{
	char* name;
	size_t filesize;
	unsigned attributes;
	const Directory* dir = nullptr;
	void swap(FileObject& other);
public:
	FileObject(const char* name, size_t filesize, unsigned attributes);
	FileObject(const FileObject& other);
	FileObject& operator=(const FileObject& other);
	virtual ~FileObject();
	virtual FileObject* clone() const = 0;

	virtual const char* getName() const;
	void setName(const char* name);
	bool is(Attribute attr) const;
	virtual size_t getSize() const;
	void setDirectory(const Directory* dir);
	virtual Type getType() const = 0;

	void setSize(size_t filesize);
	void setAttribute(Attribute attr);

	virtual void print() const = 0;
};