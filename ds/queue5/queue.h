// #pragma once                  // at visual studio 
#ifndef QUEUE_H
#define QUEUE_H

// #define QUEUESIZE 100

typedef struct queue{
    // int array[QUEUESIZE];
    void *parr;
    int rear;
    int front;
    int size;
    int elesize;
} Queue;                                // struct stack -> Stack

void initQueue(Queue *pq, int size, int elesize);
void cleanupQueue(Queue *pq);
void push(Queue *pq, const void *pdata);        // func. declaration
void pop(Queue *pq, void *pdata);


#endif
