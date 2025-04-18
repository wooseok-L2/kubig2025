#ifndef SAFE_ARRAY_H
#define SAFE_ARRAY_H

#include "array.h"

class SafeArray : /*private or*/public Array        // Array 클래스 상속, Array public 멤버들이의 SafeArray 클래스 public or private로 상속받음
{      
private:

public:
    explicit SafeArray(int size = Array::getDefaultArraySize());
    SafeArray(const int *pArr, int size);
    SafeArray(const SafeArray& rhs);
    
    SafeArray& operator=(const SafeArray& rhs);
    bool operator==(const SafeArray& rhs) const;
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