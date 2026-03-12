#include "CarPart.h"

class Acumulator : public CarPart {
    private:
        unsigned capacity;
        char* capacityId;

        void freeDynamicly();
        void copyDynamicly(const Acumulator& other);
        
    protected:
        void swapDynamicly(Acumulator& other);
    
    public:
        Acumulator(unsigned id, 
                   const char* name, 
                   const char* description,
                   unsigned capacity,
                   const char* capactityId);
        
        Acumulator(const Acumulator& other);
        Acumulator& operator=(const Acumulator& other);
        ~Acumulator();
};
    