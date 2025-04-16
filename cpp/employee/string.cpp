#include <cstring>
#include <cassert>
#include "string.h"

std::ostream& operator<<(std::ostream& out, const String& rhs)
{
    return out << rhs.str;
}

String::String()
{
    this->str = new char[1];
    this->str[0] = '\0';
    this->len = 0;
}

String::String(const char *s)
{
    this->str = new char[strlen(s) + 1];
    assert(this->str);
    strcpy(this->str, s);

    this->len = strlen(s);
}

String::String(const String& rhs)
{
    this->str = new char[rhs.len + 1];
    assert(this->str);
    strcpy(this->str, rhs.str);

    this->len = rhs.len;
}

String::~String()
{
    delete [] this->str;
}

String& String::operator=(const String& rhs)
{
    delete [] this->str;
    this->str = new char[rhs.len];
    assert(this->str);
    strcpy(this->str, rhs.str);

    this->len = rhs.len;

    return *this;
}

bool String::operator==(const String& rhs)
{
    return strcmp(this->str, rhs.str) == 0;
}

const String String::operator+(const String& rhs)
{
    char buf[this->len + rhs.len + 1];
    strcpy(buf, this->str);
    strcat(buf, rhs.str);
    String result(buf);

    return result;
}

const char *String::c_str()
{
    return this->str;
}

int String::size()
{
    return this->len;
}