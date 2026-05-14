#include <iostream>
#include "FileObject.h"
#include "RegularFile.h"
#include "FileSystem.h"
#include <cassert>

void removeRec(FileObject** arr, size_t size)
{
	for (size_t i = 0; i < size; i++)
	{
		delete arr[i];
	}
}

int main()
{
	Directory root("usr", 0);
	constexpr size_t OBJS_COUNT = 7;
	FileObject* objs[OBJS_COUNT] =
	{
		new RegularFile("Solution", 100, (unsigned char)Attribute::Archiveable, "cpp"),
		new RegularFile("Iron Maiden - The Number of the Beast", 200, (unsigned char)Attribute::Archiveable, "mp3"),
		new RegularFile("OS_HW", 300, (unsigned char)Attribute::Archiveable, "sh"),
	    &(new Directory("exercises", (unsigned char)Attribute::Archiveable))
			->operator+=(Directory("c", 0)
			.operator+=(RegularFile("OOP_PRACT", 150, (unsigned char)Attribute::Archiveable, "cpp")))
			.operator+=(RegularFile("Shell_Test", 100, (unsigned char)Attribute::Archiveable, "sh"))
			.operator+=(RegularFile("Shell_Test2", 300, 0, "sh")),
		new RegularFile("UP_Test", 300, 0, "docx"),
		new RegularFile("ImportantContract", 350, (unsigned char)Attribute::Hidden, "pdf"),
		new RegularFile("NotSoImportantContract", 350, (unsigned char)Attribute::Archiveable, "pdf"),
	};

	for (size_t i = 0; i < OBJS_COUNT; i++)
	{
		root += *objs[i];
	}

	try
	{
		root += RegularFile("Solution", 123, 0, "cpp");
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
	try
	{
		FileObject* maiden = root["Iron Maiden - The Number of the Beast.mp3"];
		maiden->setName("Solution.cpp");
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}

	root.print();

	FileSystem fs(&root);
	fs.printArchiveable("archiveable.txt");
	try
	{
		fs.changeDir("asdasdasd");
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
	fs.changeDir("exercises");

	FileObject* shell = fs.findFile("Shell_Test.sh", true);
	assert(shell != nullptr);
	FileObject* maiden = fs.findFile("Iron Maiden - The Number of the Beast.mp3", true);
	assert(maiden == nullptr);

	removeRec(objs, OBJS_COUNT);
}