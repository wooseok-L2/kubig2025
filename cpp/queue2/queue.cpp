#include "queue.h"
#include <cstdio>
// #include <stdlib.h>
#include <cassert>

const int Queue::QUEUE_SIZE = 100;

Queue::Queue(int size)
: front_(0), rear_(0), size_(size), parr_(new int[size])
{
    assert(parr_);       // 디버깅모드에서만 작동  assert(pq->parr != 0);   릴리즈 모드에서는 assert 함수 사라짐
}

Queue::~Queue()
{
    delete[] parr_;
}

int Queue::size() const
{
    return size_;
}

int Queue::remain() const
{
    return size_ - rear_;
}

bool Queue::isEmpty() const
{
    return rear_ == 0 || rear_ == front_;
}

bool Queue::isFull() const
{
    return rear_ == size_;
}

void Queue::push(int data)
{  
    assert(!isFull());
    
    parr_[rear_] = data;
    ++rear_;
}

int Queue::pop()
{  
    assert(rear_ != front_);
    
    int i = front_;

    ++front_;
    
    return parr_[i];
    
}

