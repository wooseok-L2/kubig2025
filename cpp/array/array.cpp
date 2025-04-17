#include "array.h"
#include <assert.h>

const int Array::ARRAY_SIZE = 100;       //특정 클래스와 관련된 전역변수

int Array::getDefaultArraySize()
{
    return Array::ARRAY_SIZE;
}

Array::Array(const int *pArr, int size)
: pArr_(new int[size]), size_(size)
{
    assert(pArr_);
    for (int i = 0; i < size; i++){
        pArr_[i] = pArr[i];
    }
}

Array::Array(int size)
: pArr_(new int[size]), size_(size)
{
    assert(pArr_);
}

Array::Array(const Array& rhs)
: pArr_(new int[rhs.size_]), size_(rhs.size_)
{
    assert(pArr_);
    for (int i = 0; i < size_; i++){
        pArr_[i] = rhs.pArr_[i];
    }
}

Array::~Array()
{
    delete[] pArr_;
}

Array& Array::operator = (const Array& rhs)
{
    if (this != &rhs){
        delete [] pArr_;
        pArr_ = new int[rhs.size_];
        assert(pArr_);
        for (int i = 0; i < size_; i++){
            pArr_[i] = rhs.pArr_[i];
        }

        size_ = rhs.size_;
    }

    return *this;
}
bool Array::operator == (const Array& rhs) const
{
    if (size_ != rhs.size_){
        return false;
    }

    int i;
    for (i = 0; i < rhs.size_; i++){
        if (pArr_[i] != rhs.pArr_[i]){
            break;
        }
    }

    return (i == rhs.size_);
}

int Array::size() const
{
    return size_;
}

int& Array::operator[](int index)
{
    return pArr_[index];
}

const int& Array::operator[](int index) const
{
    return pArr_[index];
}