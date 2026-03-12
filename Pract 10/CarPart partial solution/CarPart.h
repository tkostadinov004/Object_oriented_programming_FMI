#include <iostream>
#include <cstring>
#include <new>

class CarPart
{
private:
    unsigned id;
    char* name = nullptr;
    char* description = nullptr;

    void copyDynamicly(const CarPart& other);
    void freeDynamicly();
protected:
    void swapDynamicly(CarPart& other);
public:
    CarPart(unsigned id, const char* name, const char* description);
    CarPart(const CarPart& other);
    CarPart& operator=(const CarPart& other);
    ~CarPart();

    void setName(const char* name);

    friend std::ostream& operator<<(std::ostream& os, const CarPart& obj);
};
