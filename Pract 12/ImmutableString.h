#include <iostream>

class ImmutableString {
public:
    ImmutableString(const char* str);

    const char* c_str() const;
    size_t getLength() const;

    ImmutableString(const ImmutableString& );

    ImmutableString& operator=(const ImmutableString&);

    ~ImmutableString();

private:
    void free();
    void copyFrom(const ImmutableString&);

    const char* str = nullptr;
    size_t length = 0;
};

bool operator==(const ImmutableString& lhs, const ImmutableString& rhs);
bool operator!=(const ImmutableString& lhs, const ImmutableString& rhs);
bool operator<=(const ImmutableString& lhs, const ImmutableString& rhs);
bool operator>=(const ImmutableString& lhs, const ImmutableString& rhs);
bool operator<(const ImmutableString& lhs, const ImmutableString& rhs);
bool operator>(const ImmutableString& lhs, const ImmutableString& rhs);

std::ostream& operator<<(std::ostream& os, const ImmutableString& str);