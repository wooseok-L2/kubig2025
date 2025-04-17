#include "mystack.h"
#include <assert.h>

// const int STACK_SIZE = 100;
const int Stack::STACK_SIZE = 100;

Stack::Stack(int size)
: pArr_(new int[size]), size_(size), tos_(0)
{
    assert(pArr_);
}

Stack::~Stack()
{
    delete[] pArr_;
}

int Stack::size() const
{
    return size_;
}

int Stack::remain() const
{
    return size_ - tos_;
}

bool Stack::isEmpty() const
{
    return tos_ == 0;
}

bool Stack::isFull() const
{
    return tos_ == size_;
}

void Stack::push(int data)
{
    assert(!this->isFull());
    pArr_[tos_] = data;
    ++tos_;
}

int Stack::pop()
{
    assert(!this->isEmpty());

    --tos_;

    return pArr_[tos_];
}

