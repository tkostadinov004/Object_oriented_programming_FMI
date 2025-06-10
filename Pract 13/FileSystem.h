#pragma once
#include "FileObject.h"
#include "Directory.h"
#include <stdexcept>

static constexpr char SUBDIRECTORY_DELIMITER = '/';
class FileSystem
{
	Directory* root;
	Directory* curr;

	FileObject* findRec(Directory* currDir, const char* name, bool extendSearch);
	void printArchiveable(std::ostream& ofs, const Directory* root, char*& currentDir) const;
public:
	FileSystem(Directory* root);
	void changeDir(const char* name);
	FileObject* findFile(const char* name, bool extendSearch);
	void printArchiveable(const char* dest) const;
};