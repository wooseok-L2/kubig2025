#include "queue.h"
#include <cstdio>
// #include <stdlib.h>
#include <cassert>

const int Queue::QUEUE_SIZE = 100;

Queue::Queue(int size)
: front_(0), rear_(0),arr_(size)
{
    //assert(this->parr_);       // 디버깅모드에서만 작동  assert(pq->parr != 0);   릴리즈 모드에서는 assert 함수 사라짐
}

Queue::~Queue()
{
    //delete[] parr_;
}

int Queue::size() const
{
    return arr_.size();
}

int Queue::remain() const
{
    return arr_.size() - rear_;
}

bool Queue::isEmpty() const
{
    return rear_ == 0 || rear_ == front_;
}

bool Queue::isFull() const
{
    return rear_ == arr_.size();
}

void Queue::push(int data)
{  
    assert(!isFull());
    
    arr_[rear_] = data;
    ++rear_;
}

int Queue::pop()
{  
    assert(rear_ != front_);
    
    int i = front_;

    ++front_;
    
    return arr_[i];
    
}

