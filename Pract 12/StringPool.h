#include <iostream>
#include <vector>

struct StringRecord {
    char* str = nullptr;
    int refCount = 0;
};

class StringPool {
public:
    static StringPool& getInstance();

    StringPool(const StringPool&) = delete;
    StringPool& operator=(const StringPool&) = delete; 
    
    const char* getStringRecord(const char* str);

    void releaseString(const char* str);

    ~StringPool();    
private:
    int findIndex(const char* str) const;

    StringPool() = default;

    std::vector<StringRecord> records;
};