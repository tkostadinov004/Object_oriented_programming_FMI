#include "ImmutableString.h"
#include "StringPool.h"
#include <cstring>

ImmutableString::ImmutableString(const char *str) {
    str = StringPool::getInstance().getStringRecord(str);
    length = strlen(str);
}

const char *ImmutableString::c_str() const { return str; }

size_t ImmutableString::getLength() const { return length; }

ImmutableString::ImmutableString(const ImmutableString& other) {
    copyFrom(other);
}

ImmutableString &ImmutableString::operator=(const ImmutableString& other) {
    if(this != &other) {
        free();
        copyFrom(other);
    }
    return *this;
}

ImmutableString::~ImmutableString() {
    free();
}

void ImmutableString::free() {
    StringPool::getInstance().releaseString(str);
}

void ImmutableString::copyFrom(const ImmutableString & other) {
    str = StringPool::getInstance().getStringRecord(other.str);
    length = other.length;
}

bool operator==(const ImmutableString &lhs, const ImmutableString &rhs) {
    return strcmp(lhs.c_str(), rhs.c_str()) == 0;
}

std::ostream &operator<<(std::ostream &os, const ImmutableString &str) {
    os << str.c_str();

    return os;
}
