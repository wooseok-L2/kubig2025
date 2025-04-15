#ifndef STRING_H
#define STRING_H

class String {
private:
    char *str;
    int len;

public:
    String();
    String(const char *s);
    String(const String& rhs);
    ~String();

    String& operator = (const String& rhs);
    bool operator == (const String& rhs);

    const char *c_str();
    // int length();
    int size();
};

#endif