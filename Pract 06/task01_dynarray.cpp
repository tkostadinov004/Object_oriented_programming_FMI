#include <iostream>
#pragma warning (disable: 4996)

enum class BookStatus {
	NOT_TAKEN,
	TAKEN
};

std::ostream& operator<<(std::ostream& os, BookStatus status) {
	switch (status) {
		case BookStatus::NOT_TAKEN:
			os << "Not taken";
			break;
		case BookStatus::TAKEN:
			os << "Taken";
			break;
	}

	return os;
}

class Book {
	static unsigned book_instances;

	unsigned id;
	char* title;
	char* author_name;
	BookStatus status;

	void copy_from(const Book& book);
	void free();
public:
	Book();
	Book(const char* title, const char* author_name);
	Book(const Book& other);
	Book& operator=(const Book& other);
	~Book();

	unsigned get_id() const { return id; }
	const char* get_title() const { return title; }
	const char* get_author_name() const { return author_name; }
	BookStatus get_status() const { return status; }

	void set_title(const char* title);
	void set_author_name(const char* author_name);
	bool take_book();
	bool return_book();
};
std::ostream& operator<<(std::ostream& os, const Book& book);

unsigned Book::book_instances = 0;

void Book::copy_from(const Book& book)
{
	set_title(book.title);
	set_author_name(book.author_name);
	id = book.id;
	status = book.status;
}

void Book::free()
{
	delete[] title;
	title = nullptr;
	delete[] author_name;
	author_name = nullptr;
}

Book::Book() : title(nullptr), author_name(nullptr), status(BookStatus::NOT_TAKEN)
{
	id = book_instances++;
}

Book::Book(const char* title, const char* author_name) : Book()
{
	set_title(title);
	set_author_name(author_name);
}

Book::Book(const Book& other) : Book()
{
	copy_from(other);
}

Book& Book::operator=(const Book& other)
{
	if (this != &other) {
		free();
		copy_from(other);
	}

	return *this;
}

Book::~Book()
{
	free();
}

void Book::set_title(const char* title)
{
	if (!title) {
		return;
	}

	char* new_title = new char[strlen(title) + 1];
	strcpy(new_title, title);

	delete[] this->title;
	this->title = new_title;
}

void Book::set_author_name(const char* author_name)
{
	if (!title) {
		return;
	}

	char* new_author_name = new char[strlen(author_name) + 1];
	strcpy(new_author_name, author_name);

	delete[] this->author_name;
	this->author_name = new_author_name;
}

bool Book::take_book()
{
	if (status == BookStatus::TAKEN) {
		return false;
	}

	status = BookStatus::TAKEN;
	return true;
}

bool Book::return_book()
{
	if (status == BookStatus::NOT_TAKEN) {
		return false;
	}

	status = BookStatus::NOT_TAKEN;
	return true;
}

std::ostream& operator<<(std::ostream& os, const Book& book)
{
	os << "Book #" << book.get_id() << std::endl;
	os << "Title: " << book.get_title() << std::endl;
	os << "Author: " << book.get_author_name() << std::endl;
	os << "Status: " << book.get_status();
	return os;
}

// ---------------------
// ---------------------
// --------USER---------
// ---------------------
// ---------------------

class User {
	static const unsigned USERNAME_MAX_LENGTH = 8;
	static const unsigned PHONE_NUMBER_MAX_LENGTH = 10;

	char username[USERNAME_MAX_LENGTH + 1];
	char phone_number[PHONE_NUMBER_MAX_LENGTH + 1];
public:
	User();
	User(const char* username, const char* phone_number);

	const char* get_username() const { return username; }
	const char* get_phone_number() const { return phone_number; }

	void set_username(const char* username);
	void set_phone_number(const char* phone_number);
};
std::ostream& operator<<(std::ostream& os, const User& user);

User::User() : User("", "")
{
}

User::User(const char* username, const char* phone_number)
{
	set_username(username);
	set_phone_number(phone_number);
}

void User::set_username(const char* username)
{
	if (!username || strlen(username) > USERNAME_MAX_LENGTH) {
		return;
	}

	strcpy(this->username, username);
}

void User::set_phone_number(const char* phone_number)
{
	if (!phone_number || strlen(phone_number) > PHONE_NUMBER_MAX_LENGTH) {
		return;
	}

	strcpy(this->phone_number, phone_number);
}

std::ostream& operator<<(std::ostream& os, const User& user)
{
	return os << "Username (" << user.get_username() << "), Phone number (" << user.get_phone_number() << ")";
}

// ---------------------
// ---------------------
// -------DYNARRAY------
// ---------------------
// ---------------------

template <class T>
class DynArray {
	static const unsigned RESIZE_FACTOR = 2;

	T* data = nullptr;
	unsigned size = 0;
	unsigned capacity = 1;

	void resize(unsigned new_capacity);
	void copy_from(const DynArray& other);
	void free();
public:
	DynArray();
	DynArray(unsigned initial_capacity);
	DynArray(const DynArray& other);
	DynArray& operator=(const DynArray& other);
	~DynArray();

	unsigned get_size() const { return size; }
	T& operator[](int index) { return data[index]; }
	const T& operator[](int index) const { return data[index]; }

	void add(const T& obj);
};


template<class T>
void DynArray<T>::resize(unsigned new_capacity)
{
	T* new_data = new T[new_capacity];
	for (unsigned i = 0; i < size; i++) {
		new_data[i] = data[i];
	}

	delete[] data;
	data = new_data;
	capacity = new_capacity;
}

template<class T>
void DynArray<T>::copy_from(const DynArray& other)
{
	data = new T[other.capacity];
	for (unsigned i = 0; i < size; i++) {
		data[i] = other.data[i];
	}
	size = other.size;
	capacity = other.capacity;
}

template<class T>
void DynArray<T>::free()
{
	delete[] data;
	size = 0;
	capacity = 0;
}

template<class T>
DynArray<T>::DynArray() : DynArray(1)
{
}

template<class T>
DynArray<T>::DynArray(unsigned initial_capacity) : capacity(initial_capacity), data(new T[initial_capacity])
{
}

template<class T>
DynArray<T>::DynArray(const DynArray& other)
{
	copy_from(other);
}

template<class T>
DynArray<T>& DynArray<T>::operator=(const DynArray& other)
{
	if (this != &other) {
		free();
		copy_from(other);
	}

	return *this;
}

template<class T>
DynArray<T>::~DynArray()
{
	free();
}

template<class T>
void DynArray<T>::add(const T& obj)
{
	if (size == capacity) {
		resize(capacity * RESIZE_FACTOR);
	}

	data[size++] = obj;
}

// ---------------------
// ---------------------
// -------LIBRARY-------
// ---------------------
// ---------------------

struct BookPair {
	Book book;
	const User* user;
};

class Library {
	DynArray<BookPair> books;
	DynArray<User> users;

	BookPair* find_by_id(unsigned id);
	const User* find_by_username(const char* username) const;
public:
	unsigned get_books_size() const { return books.get_size(); }
	BookPair& operator[](int index) { return books[index]; }
	const BookPair& operator[](int index) const { return books[index]; }

	bool add_user(const User& user);

	bool add_book(const Book& book);
	bool take_book(unsigned book_id, const char* username);
	bool return_book(unsigned book_id);
};

std::ostream& operator<<(std::ostream& os, const Library& library);

BookPair* Library::find_by_id(unsigned id)
{
	for (unsigned i = 0; i < books.get_size(); i++) {
		if (books[i].book.get_id() == id) {
			return &books[i];
		}
	}
	return nullptr;
}

const User* Library::find_by_username(const char* username) const
{
	for (unsigned i = 0; i < users.get_size(); i++) {
		if (strcmp(users[i].get_username(), username) == 0) {
			return &users[i];
		}
	}
	return nullptr;
}

bool Library::add_user(const User& user)
{
	if (find_by_username(user.get_username())) {
		return false;
	}

	users.add(user);
	return true;
}

bool Library::add_book(const Book& book)
{
	if (find_by_id(book.get_id())) {
		return false;
	}

	books.add(BookPair{ book, nullptr });
	return true;
}

bool Library::take_book(unsigned book_id, const char* username)
{
	if (!username) {
		return false;
	}

	BookPair* book = find_by_id(book_id);
	if (!book || book->book.get_status() == BookStatus::TAKEN) {
		return false;
	}
	const User* user = find_by_username(username);
	if (!user) {
		return false;
	}
	book->book.take_book();
	book->user = user;
	return true;
}

bool Library::return_book(unsigned book_id)
{
	BookPair* book = find_by_id(book_id);
	if (!book || book->book.get_status() == BookStatus::NOT_TAKEN) {
		return false;
	}
	book->book.return_book();
	book->user = nullptr;
	return true;
}

std::ostream& operator<<(std::ostream& os, const Library& library)
{
	os << "Library details" << std::endl << "--------------" << std::endl;
	for (unsigned i = 0; i < library.get_books_size(); i++) {
		os << library[i].book;
		if (library[i].user) {
			os << " by user: " << *library[i].user;
		}
		os << std::endl << "--------------" << std::endl;
	}
	os << "End of library" << std::endl;
	return os;
}

// ---------------------
// ---------------------
// --------MAIN---------
// ---------------------
// ---------------------

int main() {
	Book books[] = {
		Book("Pod igoto", "Ivan Vazov"),
		Book("Bai Ganyo", "Aleko Konstantinov")
	};
	User users[] = {
		User("gosho123", "29382"),
		User("ivan123", "92817"),
	};

	Library library;
	library.add_book(books[0]);
	library.add_book(books[0]);
	library.add_book(books[1]);

	library.add_user(users[0]);
	library.add_user(users[0]);
	library.add_user(users[1]);

	std::cout << library << std::endl;

	Book bookCopy = books[0];
	bookCopy.set_author_name("asdasd");
	bookCopy.set_title("asdasdasdasdasd");

	User userCopy = users[0];
	userCopy.set_phone_number("1238718937128937182973");
	userCopy.set_username("1238718937128937182973");

	library.take_book(0, "gosho123");
	std::cout << library << std::endl;
	library.take_book(0, "gosho123");
	library.take_book(0, "ivan123");
	library.take_book(1, "ivan123");
	std::cout << library << std::endl;
	library.return_book(0);
	std::cout << library << std::endl;
	library.return_book(1);
	std::cout << library << std::endl;
	library.return_book(1);
}
