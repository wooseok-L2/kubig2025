#ifndef BOUND_ARRAY_H
#define BOUND_ARRAY_H

#include "safeArray.h"

class BoundArray : /*private or*/public SafeArray        // SafeArray 클래스 상속, Array public 멤버들이의 SafeArray 클래스 public or private로 상속받음
{      
private:
    int low_;

public:
    // explicit BoundArray(int end = Array::getDefaultArraySize());
    BoundArray(int size = Array::ARRAY_SIZE);
    BoundArray(const BoundArray& rhs);
    BoundArray(int low, int upper);
    virtual ~BoundArray();
    BoundArray& operator=(const BoundArray& rhs);
    bool operator==(const BoundArray& rhs) const;
    virtual int& operator[](int index);
    virtual const int& operator[](int index) const;
    int lower();
    int upper();

    // int size();  //Array::size() is intherited(public)

    // SafeArray(const SafeArray& ) {}
    // ~SafeArray() {}
    // SafeArray& operator=(const SafeArray& ) {}
    // SafeArray *operator&() {return this;}
    // const SafeArray* operator&() const (retrun this;)
};

#endif