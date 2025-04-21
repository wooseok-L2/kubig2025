#include "string.h"
#include <cassert>
#include <cstring>


String::String()
: str_(new char[1]), len_(0)
{
    // str_ = new char[1];
    assert(str_ );
    str_[0] = '\0';
    // len_ = 0;
}

String::String(const char *s)
: str_ (new char[strlen(s) + 1]), len_(strlen(s))
{
    // str_ = new char[strlen(s) + 1];
    assert(str_ );
    strcpy(str_, s);

    // len_ = strlen(s);
}

// String::~String()
// {
//     delete [] str_;
// }

String::String(const String& rhs)
: str_ (new char[rhs.len_ + 1]), len_(rhs.len_)
{
    // str_ = new char[rhs.len_ +1];
    assert(str_ );
    strcpy(str_, rhs.str_);
    // len_ = rhs.len_;
}

String& String::operator = (const String& rhs)
{
    if (this != &rhs) {    // 주소가 같은지 비교
        delete [] str_;
        str_ = new char[rhs.len_ + 1];
        assert(str_ );
        strcpy(str_, rhs.str_);
        
        len_ = rhs.len_;
    }

    return *this;
}

bool String::operator == (const String& rhs) const
{
    return strcmp(str_, rhs.str_) == 0;
}

const String String::operator + (const String& rhs) const
{
    char buf[strlen(str_) + strlen(rhs.str_) + 1];
    strcpy(buf, str_);
    strcat(buf, rhs.str_);

    String result(buf);
    return result;
}
