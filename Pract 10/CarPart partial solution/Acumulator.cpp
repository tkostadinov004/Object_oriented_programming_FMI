#include "Acumulator.h"

void Acumulator::freeDynamicly()
{
    delete[] this->capacityId;
    this->capacityId = nullptr;
}

void Acumulator::copyDynamicly(const Acumulator& other)
{
    size_t capacitySize = strlen(other.capacityId);
    this->capacityId = new char[capacitySize + 1];

    this->capacity = other.capacity;
    strcpy(this->capacityId, other.capacityId);
}

void Acumulator::swapDynamicly(Acumulator& other)
{
    std::swap(other.capacity, this->capacity);
    std::swap(other.capacityId, this->capacityId);
}

Acumulator::Acumulator(unsigned id, const char* name, const char* description, unsigned capacity, const char* capactityId)
 : CarPart(id, name, description)
{
    if (!capacity || !capacityId)
        throw std::invalid_argument("Invalid parameters.");
    
    size_t capacitySize = strlen(capacityId);
    this->capacityId = new char[capacitySize + 1];

    this->capacity = capacity;
    strcpy(this->capacityId, capacityId);
}

Acumulator::Acumulator(const Acumulator& other) : CarPart(other)
{
    copyDynamicly(other);
}

Acumulator& Acumulator::operator=(const Acumulator& other)
{
    if (this != &other)
    {
        Acumulator temp(other);
        
        CarPart::swapDynamicly(temp);
        swapDynamicly(temp);
    }
}
Acumulator::~Acumulator()
{
    freeDynamicly();
}