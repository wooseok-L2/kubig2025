#include "safeArray.h"
#include <cassert>

SafeArray::SafeArray(int size)
: Array(size)
{
    
}

SafeArray::SafeArray(const int *pArr, int size)
: Array(pArr, size)
{
    
}

SafeArray::SafeArray(const SafeArray& rhs)
: Array((Array)rhs)     //slicing
{

}

SafeArray& SafeArray::operator=(const SafeArray& rhs)
{
    if (this != &rhs){
        this->Array::operator=(rhs);
    }

    return *this;
}

bool SafeArray::operator==(const SafeArray& rhs) const 
{
    return this->Array::operator==((Array)rhs);
}

int& SafeArray::operator[](int index)
{
    assert(index >= 0 && index < this->Array::size());
    return this->Array::operator[](index);
}

const int& SafeArray::operator[](int index) const
{
    assert(index >= 0 && index < this->Array::size());
    return this->Array::operator[](index);
}
