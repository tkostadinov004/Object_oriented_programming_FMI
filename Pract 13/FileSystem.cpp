#include "FileSystem.h"
#include <fstream>
#include <iostream>
#pragma warning (disable: 4996)

static void append(char*& currentDir, const char* suffix)
{
	if (!currentDir || !suffix) throw std::invalid_argument("Current dir name or suffix cannot be nullptr!");

	char* result = new char[strlen(currentDir) + strlen(suffix) + 2] {0};
	strcat(result, currentDir);
	strcat(result, suffix);
	strcat(result, "/");

	delete[] currentDir;
	currentDir = result;
}

static void removeLastSubdir(char*& currentDir)
{
	if (!currentDir) throw std::invalid_argument("Current dir name cannot be nullptr!");

	int lastSeparatorIndex = -1;
	for (size_t i = 0; currentDir[i] != '\0'; i++)
	{
		if (currentDir[i] == SUBDIRECTORY_DELIMITER) lastSeparatorIndex = i;
	}

	if (lastSeparatorIndex == -1) return;

	for (size_t i = lastSeparatorIndex + 1; currentDir[i] != '\0'; i++)
	{
		currentDir[i] = 0;
	}
}

FileObject* FileSystem::findRec(Directory* currDir, const char* name, bool extendSearch)
{
	FileObject* res = (*currDir)[name];
	if (res)
	{
		return res;
	}

	for (size_t i = 0; i < currDir->getObjectsCount(); i++)
	{
		FileObject* curr = (*currDir)[i];
		if (curr->getType() == Type::Dir
			&& (extendSearch || (!curr->is(Attribute::Hidden) && !curr->is(Attribute::System))))
		{
			if (res = findRec(reinterpret_cast<Directory*>(curr), name, extendSearch))
			{
				break;
			}
		}
	}
	return res;
}

void FileSystem::printArchiveable(std::ostream& ofs, const Directory* curr, char*& currentDir) const
{
	for (size_t i = 0; i < curr->getObjectsCount(); i++)
	{
		if ((*curr)[i]->is(Attribute::Archiveable))
		{
			ofs << currentDir << (*curr)[i]->getName() << std::endl;
		}
		if ((*curr)[i]->getType() == Type::Dir)
		{
			append(currentDir, (*curr)[i]->getName());
			const Directory* child = reinterpret_cast<const Directory*>((*curr)[i]);
			printArchiveable(ofs, child, currentDir);
			removeLastSubdir(currentDir);
		}
	}
}

FileSystem::FileSystem(Directory* root)
{
	if (!root) throw std::invalid_argument("Root directory cannot be nullptr!");

	this->root = this->curr = root;
}

void FileSystem::changeDir(const char* name)
{
	if (!name) throw std::invalid_argument("Name cannot be nullptr!");
	if (strcmp(name, "/") == 0)
	{
		curr = root;
		return;
	}

	FileObject* found = curr->operator[](name);
	if (!found || found->getType() != Type::Dir) throw std::logic_error("Directory with such a name doesn't exist!");
	
	curr = reinterpret_cast<Directory*>(found);
}

FileObject* FileSystem::findFile(const char* name, bool extendSearch)
{
	if (!name) throw std::invalid_argument("Name cannot be nullptr!");
	return findRec(curr, name, extendSearch);
}

void FileSystem::printArchiveable(const char* dest) const
{
	if (!dest) throw std::invalid_argument("Destination file name cannot be nullptr!");

	std::ofstream ofs(dest, std::ios::trunc);
	if (!ofs.is_open()) throw std::logic_error("File stream not open!");

	char* currentDir = new char[1] {0};
	append(currentDir, root->getName());
	printArchiveable(ofs, root, currentDir);
	delete[] currentDir;

	ofs.close();
}
