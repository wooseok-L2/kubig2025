#include "boundArray.h"
#include <cassert>

BoundArray::BoundArray(int end)
: Array(end)
{
    
}

BoundArray::BoundArray(int start, int end)
: Array(end)
{
    
}

BoundArray::BoundArray(const BoundArray& rhs)
: Array((Array)rhs)     //slicing
{

}

BoundArray& BoundArray::operator=(const BoundArray& rhs)
{
    if (this != &rhs){
        this->Array::operator=(rhs);
    }

    return *this;
}

bool BoundArray::operator==(const BoundArray& rhs) const 
{
    return this->Array::operator==((Array)rhs);
}

int& BoundArray::operator[](int index)
{
    assert(index >= 0 && index < this->Array::size());
    return this->Array::operator[](index);
}

const int& BoundArray::operator[](int index) const
{
    assert(index >= 0 && index < this->Array::size());
    return this->Array::operator[](index);
}

BoundArray::upper()
{

}

BoundArray::Lower()
{

}
