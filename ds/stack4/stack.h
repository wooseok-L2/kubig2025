// #pragma once                         // at visual studio 
#ifndef STACK_H
#define STACK_H
// #define STACKSIZE 100

typedef struct stack{
    // int array[STACKSIZE];
    int *parr;
    int size;
    int tos;
} Stack;                                // struct stack -> Stack

void initStack(Stack *ps, int data);
void cleanupStack(Stack *ps);
void push(Stack *ps, int data);         // func. declaration
int pop(Stack *ps);

#endif
