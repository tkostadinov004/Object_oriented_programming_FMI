#include "CarPart.h"

CarPart::CarPart(unsigned id, const char* name, const char* description)
{

    if (!id || !name || !description)
    {
        throw std::invalid_argument("Invalid argument");
    }
    
    this->id = id;

    size_t nameSize = strlen(name);
    size_t descSize = strlen(description);

    
    this->name = new(std::nothrow) char[nameSize + 1];
    this->description = new(std::nothrow) char[descSize + 1];

    if (!this->name || !this->description)
    {
        delete[] this->name;
        delete[] this->description;
        throw std::bad_alloc();
    }

    strcpy(this->name, name);
    strcpy(this->description, description);
}

CarPart::CarPart(const CarPart& other)
{
    copyDynamicly(other);
}

CarPart& CarPart::operator=(const CarPart& other) 
{
    if (this != &other)
    {
        CarPart temp(other);
        swapDynamicly(temp);
    }
    
    return *this;
}

void CarPart::copyDynamicly(const CarPart& other)
{
    size_t nameSize = strlen(other.name);
    size_t descSize = strlen(other.description);

    this->name = new(std::nothrow) char[nameSize + 1];
    this->description = new(std::nothrow) char[descSize + 1];

    if (!this->name || !this->description)
    {
        delete[] this->name;
        delete[] this->description;
        throw std::bad_alloc();
    }

    this->id = id;
    strcpy(this->name, name);
    strcpy(this->description, description);
}


void CarPart::freeDynamicly()
{
    delete[] name;
    delete[] description;

    name = nullptr;
    description = nullptr;
}

void CarPart::swapDynamicly(CarPart& other)
{
    std::swap(this->name, other.name);
    std::swap(this->description, other.description);
    std::swap(this->id, other.id);
}


CarPart::~CarPart()
{
    freeDynamicly();
}

void CarPart::setName(const char* name)
{
    if (!name)
        throw std::invalid_argument("Invalid name");

    size_t nameSize = strlen(name);
    char* newName = new(std::nothrow) char[nameSize + 1];

    if (!newName)
        throw std::bad_alloc();
    
    strcpy(newName, name);

    delete[] this->name;
    this->name = newName;
}

std::ostream& operator<<(std::ostream& os, const CarPart& obj)
{
    return os << obj.id << obj.name << obj.description;
}