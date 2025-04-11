#include "queue.h"
#include <cstdio>
// #include <stdlib.h>
#include <cassert>

Queue::Queue(int size)
{
    this->front = 0;
    this->rear = 0;
    this->size = size;
    this->parr = new int[size];
    assert(this->parr );       // 디버깅모드에서만 작동  assert(pq->parr != 0);   릴리즈 모드에서는 assert 함수 사라짐
}

Queue::~Queue()
{
    delete[] this->parr;
}

void Queue::push(int data)
{
    // pq->array[pq->rear] = data;
    
    // if ((this->rear) == this->size){
    // 	fprintf(stdout, "Queue is full \n");
    // 	exit(2);
    // }
    
    assert(!(this->rear == this->size));
    
    this->parr[this->rear] = data;
    ++this->rear;
}

int Queue::pop()
{
    // if ((this->rear) == this->front){
    // 	fprintf(stdout, "Queue is empty \n");
    // 	exit(2);
    // }
    
    assert(this->rear != this->front);
    
    int i = this->front;

    ++(this->front);
    
    return this->parr[i];
    
}

