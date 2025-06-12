#pragma once

enum class Attribute : unsigned char
{
	Hidden = 1,
	System = 2,
	Archiveable = 4,
	ReadOnly = 8
};
enum class Type : unsigned char
{
	Dir,
	File
};

class Directory;

class FileObject
{
	char* name = nullptr;
	size_t filesize;
	unsigned char attributes;
	const Directory* dir = nullptr;
protected:
	void printBasicData() const;
public:
	FileObject(const char* name, size_t filesize, unsigned char attributes);
	FileObject(const FileObject& other);
	FileObject& operator=(const FileObject& other);
	virtual ~FileObject();
	virtual FileObject* clone() const = 0;

	const char* getName() const;
	void setName(const char* name);
	bool is(Attribute attr) const;
	virtual size_t getSize() const;
	void setDirectory(const Directory* dir);
	virtual Type getType() const = 0;

	void setSize(size_t filesize);
	void setAttribute(Attribute attr);

	virtual void print() const;
};
