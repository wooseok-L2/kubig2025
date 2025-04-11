// #pragma once                         // at visual studio 
#ifndef STACK_H
#define STACK_H
// #define STACKSIZE 100

class Stack{
private:                // implementation
    // int array[STACKSIZE];
    int *parr;
    int size;
    int tos;
 
public:                 // interface 
    // void initStack(int size);
    Stack(int size);             // 생성자 만들기
    // void cleanupStack();
    ~Stack();         // 소멸자 만들기   
    void push(int data);         // func. declaration
    int pop();
};                                // struct stack -> Stack

#endif
