#include "FileSystem.h"
#include <fstream>

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

FileSystem::FileSystem(Directory* root)
{
	if (!root)
	{
		throw std::invalid_argument("Root directory cannot be nullptr!");
	}
	this->root = this->curr = root;
}

void FileSystem::changeDir(const char* name)
{
	if (!name)
	{
		throw std::invalid_argument("Name cannot be nullptr!");
	}
	if (strcmp(name, "/") == 0)
	{
		curr = root;
		return;
	}

	FileObject* found = curr->operator[](name);
	if (!found || found->getType() != Type::Dir)
	{
		throw std::logic_error("Directory with such a name doesn't exist!");
	}
	curr = reinterpret_cast<Directory*>(found);
}

FileObject* FileSystem::findFile(const char* name, bool extendSearch)
{
	if (!name)
	{
		throw std::invalid_argument("Name cannot be nullptr!");
	}
	return findRec(curr, name, extendSearch);
}