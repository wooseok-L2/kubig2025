#include "queue.h"
#include <stdio.h>
#include <stdlib.h>

void initQueue(Queue *pq)
{
    pq->front = 0;
    pq->rear = 0;
}

void push(Queue *pq, int data)
{
    pq->array[pq->rear] = data;
    ++pq->rear;
}
int pop(Queue *pq)
{
    int i = pq->front;

    ++(pq->front);
    
    return pq->array[i];
    
}

