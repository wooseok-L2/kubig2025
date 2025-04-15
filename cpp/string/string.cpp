#include "string.h"
#include <cstring>
#include <cassert>

String::String()
{
    this->str = new char[1];
    this->str[0] = '\0';
    this->len = 0;
}

String::String(const char *s)
{
    this->str = new char[strlen(s) + 1];
    assert(this->str );
    strcpy(this->str, s);

    this->len = strlen(s);
}

String::String(const String& rhs)
{
    this->str = new char[rhs.len + 1];
    assert(this->str );
    strcpy(this->str, rhs.str);

    this->len = rhs.len;
}

String::~String()
{
    delete [] this->str;
}

const char * String::c_str()
{
    return this->str;
}

int String::size()
{
    return this->len;
}
