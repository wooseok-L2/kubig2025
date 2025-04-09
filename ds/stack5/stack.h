// #pragma once                         // at visual studio 
#ifndef STACK_H
#define STACK_H
// #define STACKSIZE 100

typedef struct stack{
    // int array[STACKSIZE];
    void *parr;
    int elesize;
    int size;
    int tos;
} Stack;                                // struct stack -> Stack

void initStack(Stack *ps, int size, int elesize);
void cleanupStack(Stack *ps);
// void push(Stack *ps, int data);         // func. declaration
void push(Stack *ps, const void *pdata);
// int pop(Stack *ps);
void pop(Stack *ps, void *pdata);

#endif
