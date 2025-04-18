// #pragma once                  // at visual studio 
#ifndef QUEUE_H
#define QUEUE_H

#include "array.h"

// #define QUEUESIZE 100

class Queue{
private:
    // int array[QUEUESIZE];
    // int *parr_;
    // int size_;
    Array arr_;      // has-a
    int rear_;
    int front_;
    static const int QUEUE_SIZE;

    Queue(const Queue& );  // is not used
    Queue& operator=(const Queue& ); // is not used

public:
    explicit Queue(int size = QUEUE_SIZE);    // 생성자 만들기
    ~Queue();         // 소멸자 만들기
    int size() const;
    int remain() const;
    bool isEmpty() const;
    bool isFull() const;
    void push(int data);         // func. declaration
    int pop();
};                                // struct stack -> Stack


#endif
