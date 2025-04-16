#ifndef STRING_H
#define STRING_H
#include <iostream>

class String {
friend std::ostream& operator<<(std::ostream& out, const String& rhs);

private:
    char *str;
    int len;

public:
    String();
    String(const char *s);
    String(const String& rhs);
    ~String();

    String& operator=(const String& rhs);
    bool operator==(const String& rhs);
    const String operator+(const String& rhs);

    const char *c_str();
    int size();
    
};

#endif