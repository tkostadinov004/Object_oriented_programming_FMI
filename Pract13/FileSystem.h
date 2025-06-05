#pragma once
#include "FileObject.h"
#include "Directory.h"
#include <stdexcept>

class FileSystem
{
	Directory* root;
	Directory* curr;

	FileObject* findRec(Directory* currDir, const char* name, bool extendSearch);
public:
	FileSystem(Directory* root);
	void changeDir(const char* name);
	FileObject* findFile(const char* name, bool extendSearch);
};