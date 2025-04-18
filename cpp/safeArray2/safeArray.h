#ifndef SAFE_ARRAY_H
#define SAFE_ARRAY_H

#include "array.h"

template <typename T>  
class SafeArray : /*private or*/public Array<T>        // Array 클래스 상속, Array public 멤버들이의 SafeArray 클래스 public or private로 상속받음
{      
private:

public:
    explicit SafeArray(int size = Array<T>::getDefaultArraySize());
    SafeArray(const T *pArr, int size);
    SafeArray(const SafeArray<T>& rhs);
    
    SafeArray<T>& operator=(const SafeArray<T>& rhs);
    bool operator==(const SafeArray<T>& rhs) const;

    virtual T& operator[](int index);
    virtual const T& operator[](int index) const;
};


#include <cassert>

template <typename T>
SafeArray<T>::SafeArray(int size)
: Array<T>(size)
{
    
}

template <typename T>
SafeArray<T>::SafeArray(const T *pArr, int size)
: Array<T>(pArr, size)
{
    
}

template <typename T>
SafeArray<T>::SafeArray(const SafeArray<T>& rhs)
: Array<T>((Array<T>)rhs)     //slicing
{

}

template <typename T>
SafeArray<T>& SafeArray<T>::operator=(const SafeArray<T>& rhs)
{
    if (this != &rhs){
        this->Array<T>::operator=((Array<T>)rhs);
    }

    return *this;
}

template <typename T>
bool SafeArray<T>::operator==(const SafeArray<T>& rhs) const 
{
    return this->Array<T>::operator==((Array<T>)rhs);
}

template <typename T>
T& SafeArray<T>::operator[](int index)
{
    assert(index >= 0 && index < this->Array<T>::size());
    return this->Array<T>::operator[](index);
}

template <typename T>
const T& SafeArray<T>::operator[](int index) const
{
    assert(index >= 0 && index < this->Array<T>::size());
    return this->Array<T>::operator[](index);
}


#endif