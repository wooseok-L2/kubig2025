#ifndef BOUND_ARRAY_H
#define BOUND_ARRAY_H

#include "safeArray.h"
#include "array.h"

class BoundArray : /*private or*/public SafeArray        // SafeArray 클래스 상속, Array public 멤버들이의 SafeArray 클래스 public or private로 상속받음
{      
private:
    int low;

public:
    // explicit BoundArray(int end = Array::getDefaultArraySize());
    explicit BoundArray(int start = 0, int end = Array::getDefaultArraySize());
    BoundArray(const BoundArray& rhs);
    BoundArray& operator=(const BoundArray& rhs);
    bool operator==(const BoundArray& rhs) const;
    virtual int& operator[](int index);
    virtual const int& operator[](int index) const;

    // int size();  //Array::size() is intherited(public)

    // SafeArray(const SafeArray& ) {}
    // ~SafeArray() {}
    // SafeArray& operator=(const SafeArray& ) {}
    // SafeArray *operator&() {return this;}
    // const SafeArray* operator&() const (retrun this;)
};

#endif