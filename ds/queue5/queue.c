#include "queue.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

void initQueue(Queue *pq, int size, int elesize)
{
    pq->front = 0;
    pq->rear = 0;
    pq->size = size;
    pq->elesize = elesize;
    pq->parr = malloc(size * sizeof(int));
    assert(pq->parr != 0);
}

void cleanupQueue(Queue *pq)
{
    free(pq->parr);
}

void push(Queue *pq, int data)
{
    // pq->array[pq->rear] = data;
    
    if ((pq->rear) == pq->size){
    	fprintf(stdout, "Queue is full \n");
    	exit(2);
    }
    
    // assert(pq->rear != pq->size);
    
    pq->parr[pq->rear] = data;
    ++pq->rear;
}

int pop(Queue *pq)
{
    if ((pq->front) == pq->size){
    	fprintf(stdout, "Queue is empty \n");
    	exit(2);
    }
    
    // assert(pq->front != pq->size);
    
    int i = pq->front;

    ++(pq->front);
    
    return pq->parr[i];
    
}

