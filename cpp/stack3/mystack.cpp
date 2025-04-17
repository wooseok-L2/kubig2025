#include "mystack.h"
#include <assert.h>

const int Stack::STACK_SIZE = 100;

Stack::Stack(int size)
: arr_(size), tos_(0)
{
    // assert(!pArr_);
}

Stack::~Stack()
{
    // delete[] pArr_;
}

int Stack::size() const
{
    //return size_;
    return arr_.size();
}

int Stack::remain() const
{
    // return size_ - tos_;
    return arr_.size() - tos_;
}

bool Stack::isEmpty() const
{
    return tos_ == 0;
}

bool Stack::isFull() const
{
    return tos_ == arr_.size();
}

void Stack::push(int data)
{
    assert(!this->isFull());
    
    // pArr_[tos_] = data;
    arr_[tos_] = data;
    ++tos_;
}

int Stack::pop()
{
    assert(!this->isEmpty());

    --tos_;

    //  return pArr_[tos_];
    return arr_[tos_];
}

