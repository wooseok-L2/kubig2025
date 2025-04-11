// #pragma once                  // at visual studio 
#ifndef QUEUE_H
#define QUEUE_H

// #define QUEUESIZE 100

class Queue{
    // int array[QUEUESIZE];
    int *parr;
    int rear;
    int front;
    int size;

public:
    Queue(int size);    // 생성자 만들기
    ~Queue();         // 소멸자 만들기
    void push(int data);         // func. declaration
    int pop();
};                                // struct stack -> Stack


#endif
