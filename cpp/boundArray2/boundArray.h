#ifndef BOUND_ARRAY_H
#define BOUND_ARRAY_H

#include "safeArray.h"

template <typename T>  
class BoundArray : /*private or*/public SafeArray<T>        // SafeArray 클래스 상속, Array public 멤버들이의 SafeArray 클래스 public or private로 상속받음
{      
private:
    int low_;

public:
    // explicit BoundArray(int end = Array::getDefaultArraySize());
    BoundArray(int size = Array<T>::ARRAY_SIZE);
    BoundArray(const BoundArray<T>& rhs);
    BoundArray(int low, int upper);
    virtual ~BoundArray();
    BoundArray<T>& operator=(const BoundArray<T>& rhs);
    bool operator==(const BoundArray<T>& rhs) const;
    virtual T& operator[](int index);
    virtual const T& operator[](int index) const;
    int lower();
    int upper();

    // int size();  //Array::size() is intherited(public)

    // SafeArray(const SafeArray& ) {}
    // ~SafeArray() {}
    // SafeArray& operator=(const SafeArray& ) {}
    // SafeArray *operator&() {return this;}
    // const SafeArray* operator&() const (retrun this;)
};

#include <cassert>

template <typename T> 
BoundArray<T>::BoundArray(int low, int upper)
: SafeArray<T>(upper - low), low_(low)
{
    
}

template <typename T> 
BoundArray<T>::BoundArray(int size)
: SafeArray<T>(size)
{
    
}

template <typename T> 
BoundArray<T>::BoundArray(const BoundArray<T>& rhs)
: SafeArray<T>((SafeArray<T>)rhs), low_(rhs.low_)     //slicing
{

}

template <typename T> 
BoundArray<T>::~BoundArray()
{

}

template <typename T> 
BoundArray<T>& BoundArray<T>::operator=(const BoundArray<T>& rhs)
{
    if (this != &rhs){
        this->SafeArray<T>::operator=((SafeArray<T>)rhs);
        low_ = rhs.low_;
    }

    return *this;
}

template <typename T> 
bool BoundArray<T>::operator==(const BoundArray<T>& rhs) const 
{
    return low_ == rhs.low_ && this->SafeArray<T>::operator == ((SafeArray<T>)rhs);
}

template <typename T> 
int BoundArray<T>::upper()
{
    return low_ + this->SafeArray<T>::size_;
}

template <typename T> 
T& BoundArray<T>::operator[](int index)
{
    return this->SafeArray<T>::operator[] (index - low_);
}

template <typename T> 
const T& BoundArray<T>::operator[](int index) const
{
    return this->SafeArray<T>::operator[] (index - low_);
}

template <typename T> 
int BoundArray<T>::lower()
{
    return low_;
}

#endif
