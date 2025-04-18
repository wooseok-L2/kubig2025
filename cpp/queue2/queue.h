// #pragma once                  // at visual studio 
#ifndef QUEUE_H
#define QUEUE_H

// #define QUEUE_SIZE 100
// extern const int QUEUE_SIZE;

class Queue{
private:
    // int array[QUEUESIZE];
    int *parr_;
    int rear_;
    int front_;
    int size_;
    static const int QUEUE_SIZE;            // only use on class cpp

    Queue(const Queue& );                   // 복사 연산자 중복 not use
    Queue& operator=(const Queue& );        // 대입연산자 중복 not use

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
