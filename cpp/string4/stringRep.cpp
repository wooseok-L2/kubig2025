#include "stringRep.h"
#include <cassert>

StringRep::StringRep()
: str_(new char [1]), len_(0)
{
    assert(str_);

    str_[0] = '\0';
}

StringRep::StringRep(const char *str)
: str_(new char[strlen(str)]), len_(strlen(str))
{
    assert(str_);

    strcpy(str_, str);
}

StringRep::~StringRep()
{
    delete[] str;
}