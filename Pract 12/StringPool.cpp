#include "StringPool.h"
#include <cstring>

StringPool &StringPool::getInstance() {
    static StringPool pool;

    return pool;
}

const char* StringPool::getStringRecord(const char *str) {
    int index = findIndex(str);

    if(index != -1) {
        records[index].refCount++;
        return records[index].str;
    }

    StringRecord rec;
    rec.str = new char[strlen(str) + 1];
    strcpy(rec.str, str);
    rec.refCount = 1;

    records.push_back(rec);
}

void StringPool::releaseString(const char *str) {
    int index = findIndex(str);

    if(index == -1) {
        return;
    }

    records[index].refCount--;

    if(records[index].refCount == 0) {
        delete[] records[index].str;
        records[index].str = nullptr;
        // records.erase(records.begin() + index);
        std::swap(records[index], records[records.size() - 1]);
        records.pop_back();
    }
}

StringPool::~StringPool() {
    for(auto& record : records) {
        delete[] record.str;
    }
}

int StringPool::findIndex(const char *str) const {
    for(int i = 0; i < records.size(); i++) {
        if(strcmp(records[i].str, str) == 0) {
            return i;
        }
    }
    return -1;
}
