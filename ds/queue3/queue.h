// #pragma once                  // at visual studio 
#ifndef QUEUE_H
#define QUEUE_H

#define QUEUESIZE 100

typedef struct queue{
    int array[QUEUESIZE];
    int rear;
    int front;
} Queue;                                // struct stack -> Stack

void initQueue(Queue *pq);
void push(Queue *pq, int data);         // func. declaration
int pop(Queue *pq);


#endif
