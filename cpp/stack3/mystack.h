#ifndef MYSTACK_H
#define MYSTACK_H
#include "array.h"

// extern const int STACK_SIZE;

class Stack{
private:
    // int *pArr_;
    // int size_;
    Array arr_;   // 'has-a'
    int tos_;
    static const int STACK_SIZE;
    
    Stack(const Stack& );  // is not used
    Stack& operator=(const Stack& ); // is not used
public:
    explicit Stack(int size = STACK_SIZE);
    ~Stack();
    
    int size() const;
    int remain() const;
    bool isEmpty() const;
    bool isFull() const;
    void push(int data);
    int pop();

};



#endif